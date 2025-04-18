
#include <zephyr/device.h>
#include <zephyr/drivers/flash.h>
#include "devreg.h"

#define FLASH_DEV_NODE DT_CHOSEN(zephyr_flash_controller)
static const struct device *flash_dev = DEVICE_DT_GET(FLASH_DEV_NODE);

static int internal_flash_read(off_t offset, void *buf, size_t len) {
    return flash_read(flash_dev, offset, buf, len);
}

static int internal_flash_write(off_t offset, const void *buf, size_t len) {
    return flash_write(flash_dev, offset, buf, len);
}

static int internal_flash_erase(off_t offset, size_t size) {
    const struct flash_pages_info *info;
    if (flash_get_page_info_by_offs(flash_dev, offset, &info) != 0) return -EINVAL;
    if ((offset % info->size != 0) || (size % info->size != 0)) return -EINVAL;
    return flash_erase(flash_dev, offset, size);
}

static struct devreg_api internal_flash_api = {
    .read  = internal_flash_read,
    .write = internal_flash_write,
    .erase = internal_flash_erase,
};

int devreg_flash_internal_register(void) {
    if (!device_is_ready(flash_dev)) {
        return -ENODEV;
    }
    return devreg_init(&internal_flash_api);
}
