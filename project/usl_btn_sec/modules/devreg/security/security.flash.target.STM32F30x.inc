#ifdef UBNT_ARM_STM32F30x

extern u_int32_t sFLASH_ReadID(void);
extern void sFLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
extern void sFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
extern u_int8_t sFLASH_ReadMXICSecurity(void);
extern u_int16_t sFLASH_ReadLockCaps(void);
extern void sFLASH_EnterSA(void);
extern void sFLASH_ExitSA(void);

__FS_FUNCTION_PREFER_INLINE u_int32_t
fs_read_flash_type_id_hw(void) {
	return sFLASH_ReadID();
}

__FS_FUNCTION_PREFER_INLINE size_t
fs_read_flash_uid_hw(__ATTRIB_UNUSED u_int8_t* dest, __ATTRIB_UNUSED size_t dest_len) {
    __FS_LOCAL_STATIC_OPTION size_t fsv_t1;
    fsv_t1 = 0;
    if (dest_len < MAX_FLASH_UID_SIZE) {
        fs_low_level_failure(FS_FAILURE_fs_read_flash_uid_hw_2);
    }
    if (   (fs_read_flash_type_id_hw() == MXIC_1M_JEDEC_ID1) 
        && ((sFLASH_ReadMXICSecurity() & 0x1) == 0x1) 
        && ((sFLASH_ReadLockCaps() & 0x3800) == 0x0800) )
    {
        sFLASH_EnterSA();
        sFLASH_ReadBuffer(dest, 0, 64); 
        sFLASH_ExitSA();
        fsv_t1 = 64;
    }
    return fsv_t1;
}

#endif // #ifdef BUNT_STM32F30x

