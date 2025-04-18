#if (defined(UBNT_EFR32xG13) && UBNT_EFR32xG13)

extern void sFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);

__FS_FUNCTION_PREFER_INLINE void fs_read_config(__ATTRIB_UNUSED void* dest_buffer, __ATTRIB_UNUSED size_t dest_buffer_len, __ATTRIB_UNUSED uintptr_t offset, __ATTRIB_UNUSED size_t bytes_to_copy) {
    if (bytes_to_copy > dest_buffer_len) {
        fs_low_level_failure(FS_FAILURE_fs_read_config_9);
    } else {
    	sFLASH_ReadBuffer(dest_buffer, offset, bytes_to_copy);
    }
}

#endif // #if (defined(UBNT_EFR32xG13) && UBNT_EFR32xG13)
