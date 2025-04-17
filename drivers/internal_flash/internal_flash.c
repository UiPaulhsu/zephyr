
#include <zephyr/device.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/init.h>
#include <zephyr/logging/log.h>
#include <drivers/internal_flash.h>

LOG_MODULE_REGISTER(internal_flash, CONFIG_INTERNAL_FLASH_LOG_LEVEL);

#define FLASH_DEV DT_CHOSEN(zephyr_flash_controller)

static const struct device *flash_dev;

int internal_flash_read(uint32_t offset, void *buf, size_t len)
{
    return flash_read(flash_dev, offset, buf, len);
}

int internal_flash_write(uint32_t offset, const void *buf, size_t len)
{
    return flash_write(flash_dev, offset, buf, len);
}

int internal_flash_erase(uint32_t offset, size_t len)
{
    return flash_erase(flash_dev, offset, len);
}

static int internal_flash_init(const struct device *dev)
{
    ARG_UNUSED(dev);

    flash_dev = DEVICE_DT_GET(FLASH_DEV);
    if (!device_is_ready(flash_dev)) {
        LOG_ERR("Flash device not ready");
        return -ENODEV;
    }

    LOG_INF("internal_flash module init OK");
    return 0;
}

DEVICE_DEFINE(internal_flash, "internal_flash",
              internal_flash_init, NULL, NULL, NULL,
              POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, NULL);
