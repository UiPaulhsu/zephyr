#if (defined(UBNT_MIPS_RTL838x) && UBNT_MIPS_RTL838x)
#include <mtd/mtd-user.h>

#define SECURE_MTD_NUM 6

uint32_t sFLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite);
uint32_t sFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead);

uint32_t sFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead)
{
    uint8_t read_buf[MAX_EEPROM_SIZE];
    int fd, len=0;
    char        test_mtd[32];

    sprintf(test_mtd,"/dev/mtdchar%d", SECURE_MTD_NUM*2);
    fd = open(test_mtd, O_RDWR); /* mtd6: 00010000 00010000 "SECINFO", 6x2 for RTL*/

    if (fd < 0)
	return 0;

    len = read(fd, read_buf, sizeof(read_buf));

    if (len < 0) {
        close(fd);
	return 0;
    }

    close(fd);
    memcpy(pBuffer, &read_buf[ReadAddr], NumByteToRead);

    return 0;
}


uint32_t sFLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite) 
{
    erase_info_t erase_info;
    int fd;
    char        test_mtd[32];

    sprintf(test_mtd,"/dev/mtdchar%d", SECURE_MTD_NUM*2);
    fd = open(test_mtd, O_RDWR); /* mtd6: 00010000 00010000 "SECINFO", 6x2 for RTL*/
    
    if (fd < 0)
        return 1;

    /* Erase flash */
    erase_info.start = WriteAddr;
    erase_info.length = MAX_EEPROM_SIZE;
    if (ioctl(fd, MEMERASE, &erase_info) < 0)
    {
        close(fd);
        return 1;
    }

    if (write(fd, pBuffer, NumByteToWrite) < 0)
    {
        close(fd);
        printf("Error in write\n");
        return 1;
    }

    close(fd);

    return 0;
}

#ifndef UNIFI_LAYOUT
__FS_FUNCTION_PREFER_INLINE void fs_read_config(__ATTRIB_UNUSED void* dest_buffer, __ATTRIB_UNUSED size_t dest_buffer_len, __ATTRIB_UNUSED uintptr_t offset, __ATTRIB_UNUSED size_t bytes_to_copy) {
    if (bytes_to_copy > dest_buffer_len) {
        fs_low_level_failure(FS_FAILURE_fs_read_config_9);
    } else {
        sFLASH_ReadBuffer(dest_buffer, offset, bytes_to_copy);
    }
}
#endif

#ifdef HELPER_BUILD
__FS_FUNCTION_PREFER_INLINE void fs_write_config(__ATTRIB_UNUSED uintptr_t offset, __ATTRIB_UNUSED void* src_buffer, __ATTRIB_UNUSED size_t bytes_to_copy) {
	__FS_LOCAL_STATIC_OPTION u_int8_t* fsv_t1;

    /* On every invocation, allocate new buffer */
    fsv_t1 = (u_int8_t*)fs_zalloc(MAX_EEPROM_SIZE);
    /* Check memory allocation failure */
    if (NULL == fsv_t1) {
	fs_low_level_failure(FS_FAILURE_fs_write_config_5);
        goto done;
    }

    /* Check requested write length within buffer length */
    if ((offset+bytes_to_copy) > MAX_EEPROM_SIZE) {
        fs_low_level_failure(FS_FAILURE_fs_write_config_6);
    }
    /* Read the entire (current) EEPROM */
    fs_read_config(fsv_t1, MAX_EEPROM_SIZE, 0, BLOCK_64K); // NB: This only works because all product classes on this target use 64KB "EEPROM" blocks

    /* Apply the writes */
    memcpy( &fsv_t1[offset], src_buffer, bytes_to_copy );
    /* Write the entire (modified) EEPROM */
 
    sFLASH_WriteBuffer(fsv_t1, 0, BLOCK_64K); // NB: This only works because all product classes on this target use 64KB "EEPROM" blocks

done:
    fs_safe_shred_and_free(&fsv_t1, MAX_EEPROM_SIZE);
}

#endif // #ifdef HELPER_BUILD

#endif // #if (defined(UBNT_MIPS_RTL838x) && UBNT_MIPS_RTL838x)
