#ifdef UBNT_EFR32xG13

extern uint32_t sFLASH_Read_JEDEC_ID(void);
extern uint16_t sFLASH_Read_UID(uint8_t* pBuffer);

__FS_FUNCTION_PREFER_INLINE u_int32_t
fs_read_flash_type_id_hw(void) {
	return sFLASH_Read_JEDEC_ID();
}

__FS_FUNCTION_PREFER_INLINE size_t
fs_read_flash_uid_hw(__ATTRIB_UNUSED u_int8_t* dest, __ATTRIB_UNUSED size_t dest_len) {
    __FS_LOCAL_STATIC_OPTION size_t fsv_t1;
    fsv_t1 = 0;
    if (dest_len < MAX_FLASH_UID_SIZE) {
        fs_low_level_failure(FS_FAILURE_fs_read_flash_uid_hw_2);
    }
    if ((fs_read_flash_type_id_hw() == MXIC_8M_JEDEC_ID2)) {
    	fsv_t1 = sFLASH_Read_UID(dest);
    	if(fsv_t1 == 0) {
    		fs_low_level_failure(FS_FAILURE_fs_read_flash_uid_hw_2);
    	}
    }
    return fsv_t1;/* Should be fixed 64 */
}

#endif // #ifdef UBNT_EFR32xG13
