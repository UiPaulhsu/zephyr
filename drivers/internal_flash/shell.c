
#include <zephyr/shell/shell.h>
#include <stdlib.h>
#include <string.h>
#include <zephyr/storage/flash_map.h>
#include <zephyr/devicetree.h>
#include <drivers/internal_flash.h>
#include <zephyr/fs/nvs.h>
#include <zephyr/drivers/flash.h>

static int hexstr_to_bin(const char *hexstr, uint8_t *out_buf, size_t max_len)
{
    size_t len = strlen(hexstr);
    if (len % 2 != 0 || len / 2 > max_len) {
        return -EINVAL;
    }
    for (size_t i = 0; i < len / 2; i++) {
        sscanf(&hexstr[i * 2], "%2hhx", &out_buf[i]);
    }
    return len / 2;
}

static int cmd_flash_read(const struct shell *shell, size_t argc, char **argv)
{
    uint32_t offset = strtoul(argv[1], NULL, 0);
    uint32_t len = strtoul(argv[2], NULL, 0);
    uint8_t buf[256] = {0};

    if (len > sizeof(buf)) {
        shell_error(shell, "len too big");
        return -EINVAL;
    }

    int ret = internal_flash_read(offset, buf, len);
    if (ret) {
        shell_error(shell, "read failed: %d", ret);
        return ret;
    }

    shell_hexdump(shell, buf, len);
    return 0;
}

static int cmd_flash_write(const struct shell *shell, size_t argc, char **argv)
{
    uint32_t offset = strtoul(argv[1], NULL, 0);
    const char *data = argv[2];
    size_t len = strlen(data);

    int ret = internal_flash_write(offset, data, len);
    if (ret) {
        shell_error(shell, "write failed: %d", ret);
        return ret;
    }

    shell_print(shell, "Wrote string to flash at 0x%08x", offset);
    return 0;
}

static int cmd_flash_write_hex(const struct shell *shell, size_t argc, char **argv)
{
    uint32_t offset = strtoul(argv[1], NULL, 0);
    uint8_t buf[256];
    int len = hexstr_to_bin(argv[2], buf, sizeof(buf));

    if (len < 0) {
        shell_error(shell, "invalid hex string");
        return -EINVAL;
    }

    int ret = internal_flash_write(offset, buf, len);
    if (ret) {
        shell_error(shell, "write failed: %d", ret);
        return ret;
    }

    shell_print(shell, "Wrote %d bytes to flash at 0x%08x", len, offset);
    return 0;
}

static int cmd_flash_erase(const struct shell *shell, size_t argc, char **argv)
{
    uint32_t offset = strtoul(argv[1], NULL, 0);
    uint32_t len = strtoul(argv[2], NULL, 0);

    int ret = internal_flash_erase(offset, len);
    if (ret) {
        shell_error(shell, "erase failed: %d", ret);
        return ret;
    }

    shell_print(shell, "Erased flash at 0x%08x (%d bytes)", offset, len);
    return 0;
}

/**
 * flash_area storage read 0 32
 * flash_area storage erase 0 8192
 * flash_area storage write 0 DEADBEEFDEADBEEFDEADBEEFDEADBEEF
 * flash_read 0x0807E000 4
 * flash_area_info storage
 */

static int cmd_flash_area(const struct shell *shell, size_t argc, char **argv)
{
    const struct flash_area *fa;
    int id = -1;
    /**Partioin table
     * fiile name: nucleo_wba55cg.dts
     *  &flash0 {
     *  	partitions {
     *  		compatible = "fixed-partitions";
     *  		#address-cells = <1>;
     *  		#size-cells = <1>;
     *
     *  		boot_partition: partition@0 {
     *  			label = "mcuboot";
     *  			reg = <0x00000000 DT_SIZE_K(64)>;
     *  		};
     *  		slot0_partition: partition@10000 {
     *  			label = "image-0";
     *  			reg = <0x00010000 DT_SIZE_K(456)>;
     *  		};
     *  		slot1_partition: partition@82000 {
     *  			label = "image-1";
     *  			reg = <0x00082000 DT_SIZE_K(448)>;
     *  		};
     *  		storage_partition: partition@f2000 {
     *  			label = "storage";
     *  			reg = <0x000f2000 DT_SIZE_K(56)>;
     *  		};
     *  	};
     *  };
     */

    if (!strcmp(argv[1], "mcuboot")) {
        id = FIXED_PARTITION_ID(boot_partition);
    } else if (!strcmp(argv[1], "image-0")) {
        id = FIXED_PARTITION_ID(slot0_partition);
    } else if (!strcmp(argv[1], "image-1")) {
        id = FIXED_PARTITION_ID(slot1_partition);
    } else if (!strcmp(argv[1], "storage")) {
        id = FIXED_PARTITION_ID(storage_partition);
    }

    if (id < 0) {
        shell_error(shell, "Unknown area label: %s", argv[1]);
        return -EINVAL;
    }

    int ret = flash_area_open(id, &fa);
    if (ret) {
        shell_error(shell, "Failed to open area: %d", ret);
        return ret;
    }

    if (strcmp(argv[2], "read") == 0) {
        uint8_t buf[256];
        uint32_t off = strtoul(argv[3], NULL, 0);
        uint32_t len = strtoul(argv[4], NULL, 0);
        if (len > sizeof(buf)) len = sizeof(buf);
        flash_area_read(fa, off, buf, len);
        shell_hexdump(shell, buf, len);
    } else if (strcmp(argv[2], "erase") == 0) {
        uint32_t off = strtoul(argv[3], NULL, 0);
        uint32_t len = strtoul(argv[4], NULL, 0);
        flash_area_erase(fa, off, len);
        shell_print(shell, "Area erased");
    } else if (strcmp(argv[2], "write") == 0) {
        uint32_t off = strtoul(argv[3], NULL, 0);
        uint8_t buf[256];
        int len = hexstr_to_bin(argv[4], buf, sizeof(buf));
        if (len < 0) {
            shell_error(shell, "invalid hex string");
            flash_area_close(fa);
            return -EINVAL;
        }
        flash_area_write(fa, off, buf, len);
        shell_print(shell, "Wrote %d bytes to area at 0x%08x", len, off);
    } else {
        shell_error(shell, "Unknown command: %s", argv[2]);
    }

    flash_area_close(fa);
    return 0;
}

static int cmd_flash_area_info(const struct shell *shell, size_t argc, char **argv)
{
    const struct flash_area *fa;
    int id = -1;

    if (!strcmp(argv[1], "mcuboot")) {
        id = FIXED_PARTITION_ID(boot_partition);
    } else if (!strcmp(argv[1], "image-0")) {
        id = FIXED_PARTITION_ID(slot0_partition);
    } else if (!strcmp(argv[1], "image-1")) {
        id = FIXED_PARTITION_ID(slot1_partition);
    } else if (!strcmp(argv[1], "storage")) {
        id = FIXED_PARTITION_ID(storage_partition);
    }

    if (id < 0) {
        shell_error(shell, "Unknown area label: %s", argv[1]);
        return -EINVAL;
    }

    int ret = flash_area_open(id, &fa);
    if (ret) {
        shell_error(shell, "Failed to open area: %d", ret);
        return ret;
    }

    shell_print(shell, "Flash area info:");
    shell_print(shell, "  ID:     %d", fa->fa_id);
    shell_print(shell, "  Device: %s", fa->fa_dev->name);
    shell_print(shell, "  Offset: 0x%08x", (uint32_t)fa->fa_off);
    shell_print(shell, "  Size:   %u bytes", (uint32_t)fa->fa_size);

    flash_area_close(fa);
    return 0;
}


SHELL_CMD_ARG_REGISTER(flash_read, NULL, "Read internal flash", cmd_flash_read, 3, 0);
SHELL_CMD_ARG_REGISTER(flash_write, NULL, "Write string to flash", cmd_flash_write, 3, 0);
SHELL_CMD_ARG_REGISTER(flash_write_hex, NULL, "Write hex bytes to flash", cmd_flash_write_hex, 3, 0);
SHELL_CMD_ARG_REGISTER(flash_erase, NULL, "Erase internal flash", cmd_flash_erase, 3, 0);
SHELL_CMD_ARG_REGISTER(flash_area, NULL, "Operate on flash area: storage read|erase <offset> <len>", cmd_flash_area, 5, 0);
SHELL_CMD_ARG_REGISTER(flash_area_info, NULL, "Show info for flash area <name>", cmd_flash_area_info, 2, 0);


/**
 *  nvs_init
 *  nvs_write 1 hello
 *  nvs_read 1
 */
static struct nvs_fs nvs;

static int cmd_nvs_init(const struct shell *shell, size_t argc, char **argv)
{
    const struct flash_area *fa;
    struct flash_pages_info info;
    int rc = flash_area_open(FIXED_PARTITION_ID(storage_partition), &fa);
    if (rc) {
        shell_error(shell, "Failed to open flash area: %d", rc);
        return rc;
    }


    nvs.flash_device = flash_area_get_device(fa);
    nvs.offset = fa->fa_off;
    nvs.sector_count = 2;  // Adjust according to your partition size

    rc = flash_get_page_info_by_offs(nvs.flash_device, fa->fa_off, &info);
    if (rc) {
        shell_error(shell, "Failed to get page info: %d", rc);
        return rc;
    }
    nvs.sector_size = info.size;

    rc = nvs_mount(&nvs);
    if (rc) {
        shell_error(shell, "Failed to mount NVS: %d", rc);
        return rc;
    }

    shell_print(shell, "NVS mounted at offset 0x%x", nvs.offset);
    return 0;
}

static int cmd_nvs_write(const struct shell *shell, size_t argc, char **argv)
{
    uint16_t id = (uint16_t)strtoul(argv[1], NULL, 0);
    const char *data = argv[2];

    int rc = nvs_write(&nvs, id, data, strlen(data));
    if (rc < 0) {
        shell_error(shell, "Write failed: %d", rc);
        return rc;
    }

    shell_print(shell, "Wrote key %d: %s", id, data);
    return 0;
}

static int cmd_nvs_read(const struct shell *shell, size_t argc, char **argv)
{
    uint16_t id = (uint16_t)strtoul(argv[1], NULL, 0);
    char buf[128] = {0};

    int rc = nvs_read(&nvs, id, buf, sizeof(buf));
    if (rc < 0) {
        shell_error(shell, "Read failed: %d", rc);
        return rc;
    }

    shell_print(shell, "Read key %d: %s", id, buf);
    return 0;
}

SHELL_CMD_ARG_REGISTER(nvs_init, NULL, "Initialize NVS from storage partition", cmd_nvs_init, 1, 0);
SHELL_CMD_ARG_REGISTER(nvs_write, NULL, "Write to NVS <id> <string>", cmd_nvs_write, 3, 0);
SHELL_CMD_ARG_REGISTER(nvs_read, NULL, "Read from NVS <id>", cmd_nvs_read, 2, 0);
