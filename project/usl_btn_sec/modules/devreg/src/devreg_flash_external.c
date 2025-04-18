
#include <zephyr/device.h>
#include <zephyr/drivers/flash.h>
#include "devreg.h"

#define EXT_FLASH_LABEL "MX25R64"
static const struct device *ext_flash_dev;

static int external_flash_read(off_t offset, void *buf, size_t len) {
    return flash_read(ext_flash_dev, offset, buf, len);
}

static int external_flash_write(off_t offset, const void *buf, size_t len) {
    return flash_write(ext_flash_dev, offset, buf, len);
}

static int external_flash_erase(off_t offset, size_t size) {
    const struct flash_pages_info *info;
    if (flash_get_page_info_by_offs(ext_flash_dev, offset, &info) != 0) return -EINVAL;
    if ((offset % info->size != 0) || (size % info->size != 0)) return -EINVAL;
    return flash_erase(ext_flash_dev, offset, size);
}

static struct devreg_api external_flash_api = {
    .read  = external_flash_read,
    .write = external_flash_write,
    .erase = external_flash_erase,
};

int devreg_flash_external_register(void) {
    ext_flash_dev = device_get_binding(EXT_FLASH_LABEL);
    if (!ext_flash_dev || !device_is_ready(ext_flash_dev)) {
        return -ENODEV;
    }
    return devreg_init(&external_flash_api);
}
