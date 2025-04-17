
#pragma once

#include <zephyr/device.h>

int internal_flash_read(uint32_t offset, void *buf, size_t len);
int internal_flash_write(uint32_t offset, const void *buf, size_t len);
int internal_flash_erase(uint32_t offset, size_t len);
