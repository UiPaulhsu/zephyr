#ifdef UBNT_ST50H

extern uint32_t devreg_read_flash_jedec_id(void);
extern uint16_t devreg_read_flash_unique_id(uint8_t* pBuffer, uint8_t bufSize);
extern bool devreg_check_support_flash_jedec_id(void);

__FS_FUNCTION_PREFER_INLINE u_int32_t
fs_read_flash_type_id_hw(void) {
	return devreg_read_flash_jedec_id();
}

__FS_FUNCTION_PREFER_INLINE size_t
fs_read_flash_uid_hw(__ATTRIB_UNUSED u_int8_t* dest, __ATTRIB_UNUSED size_t dest_len) {
    __FS_LOCAL_STATIC_OPTION size_t fsv_t1;
    fsv_t1 = 0;
    if (dest_len < MAX_FLASH_UID_SIZE) {
        fs_low_level_failure(FS_FAILURE_fs_read_flash_uid_hw_2);
    }
    if (devreg_check_support_flash_jedec_id()) {
        fsv_t1 = devreg_read_flash_unique_id(dest, dest_len);
    	if(fsv_t1 == 0) {
    		fs_low_level_failure(FS_FAILURE_fs_read_flash_uid_hw_2);
    	}
    }
    return fsv_t1;/* Should be fixed 64 */
}

#endif // #ifdef UBNT_ST50H
