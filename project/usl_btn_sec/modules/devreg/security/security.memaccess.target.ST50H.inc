#if (defined(UBNT_ST50H) && UBNT_ST50H)

extern void devreg_read_flash_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);

__FS_FUNCTION_PREFER_INLINE void fs_read_config(__ATTRIB_UNUSED void* dest_buffer, __ATTRIB_UNUSED size_t dest_buffer_len, __ATTRIB_UNUSED uintptr_t offset, __ATTRIB_UNUSED size_t bytes_to_copy) {
    if (bytes_to_copy > dest_buffer_len) {
        fs_low_level_failure(FS_FAILURE_fs_read_config_9);
    } else {
    	devreg_read_flash_ReadBuffer(dest_buffer, offset, bytes_to_copy);
    }
}

#endif // #if (defined(UBNT_ST50H) && UBNT_ST50H)
