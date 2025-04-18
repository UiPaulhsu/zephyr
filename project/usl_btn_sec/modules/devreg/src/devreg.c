
#include "stdbool.h"
#include "stdio.h"

#include "devreg.h"
/* Devreg    ------------------------------------------------------------------*/
#define UBNT_ST50H 1
#include <security.inc>

#define DEVREG_DEFAULT_ADDRESS 0x00000000

static const struct devreg_api *g_devreg_api = NULL;

int devreg_init(const struct devreg_api *api) {
    if (!api || !api->read || !api->write || !api->erase) {
        return -EINVAL;
    }
    g_devreg_api = api;

    fs_check_sec();
    return 0;
}

int devreg_read(off_t offset, void *buf, size_t len) {
    if (!g_devreg_api) return -ENODEV;
    return g_devreg_api->read(offset, buf, len);
}

int devreg_write(off_t offset, const void *buf, size_t len) {
    if (!g_devreg_api) return -ENODEV;
    return g_devreg_api->write(offset, buf, len);
}

int devreg_erase(off_t offset, size_t size) {
    if (!g_devreg_api) return -ENODEV;
    return g_devreg_api->erase(offset, size);
}

void devreg_read_flash_ReadBuffer(uint8_t* buffer, uint32_t addr, uint16_t bytes_to_read)
{
}

uint32_t devreg_read_cpu_id(void)
{
    uint32_t id = 0x0d2b0278;
    return id;
}

uint32_t devreg_read_flash_jedec_id(void)
{
    uint32_t id = 0x00c22814;
    return id;
}

bool devreg_check_support_flash_jedec_id(void)
{
    if (devreg_read_flash_jedec_id() == MXIC_8M_JEDEC_ID2) {
        return true;
    }

    return false;
}

uint16_t devreg_read_flash_unique_id(uint8_t *buffer, uint8_t bufSize)
{
    buffer[ 0] = 0xc2;
    buffer[ 1] = 0xf5;
    buffer[ 2] = 0x08;
    buffer[ 3] = 0x0d;
    buffer[ 4] = 0x05;
    buffer[ 5] = 0x04;
    buffer[ 6] = 0x07;
    buffer[ 7] = 0x04;
    buffer[ 8] = 0x00;
    buffer[ 9] = 0x00;
    buffer[10] = 0x04;
    buffer[11] = 0x88;
    buffer[12] = 0x26;
    buffer[13] = 0x01;
    buffer[14] = 0x09;
    buffer[15] = 0xff;
    buffer[16] = 0x1f;
    buffer[17] = 0x29;
    buffer[18] = 0x4b;
    buffer[19] = 0xec;
    buffer[20] = 0x1b;
    buffer[21] = 0xbd;
    buffer[22] = 0xff;
    buffer[23] = 0xfe;
    buffer[24] = 0x1f;
    buffer[25] = 0x29;
    buffer[26] = 0x4b;
    return 27;
}