#if (defined(UBNT_ARM_STM32F30x) && UBNT_ARM_STM32F30x)

extern uint8_t sFLASH_ReadByte(void);
extern uint8_t sFLASH_SendByte(uint8_t byte);
extern uint16_t sFLASH_SendHalfWord(uint16_t HalfWord);
extern void sFLASH_WriteEnable(void);
extern void sFLASH_WaitForWriteEnd(void);
extern void sFLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
extern void sFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);

__FS_FUNCTION_PREFER_INLINE void fs_read_config(__ATTRIB_UNUSED void* dest_buffer, __ATTRIB_UNUSED size_t dest_buffer_len, __ATTRIB_UNUSED uintptr_t offset, __ATTRIB_UNUSED size_t bytes_to_copy) {
    if (bytes_to_copy > dest_buffer_len) {
        fs_low_level_failure(FS_FAILURE_fs_read_config_9);
    } else {
        sFLASH_ReadBuffer(dest_buffer, offset, bytes_to_copy);
    }
}

#ifdef HELPER_BUILD
__FS_FUNCTION_PREFER_INLINE void fs_write_config(__ATTRIB_UNUSED uintptr_t offset, __ATTRIB_UNUSED void* src_buffer, __ATTRIB_UNUSED size_t bytes_to_copy) {
	__FS_LOCAL_STATIC_OPTION u_int8_t* fsv_t1;

    /* On every invocation, allocate new buffer */
	fsv_t1 = (u_int8_t*)fs_zalloc(MAX_EEPROM_SIZE);
    /* Check memory allocation failure */
    if (NULL == fsv_t1) {
		fs_low_level_failure(FS_FAILURE_fs_write_config_5)
        goto done;
	}
    /* Check requested write length within buffer length */
    if ((offset+bytes_to_copy) >= MAX_EEPROM_SIZE) {
        fs_low_level_failure(FS_FAILURE_fs_write_config_6);
    }
    /* Read the entire (current) EEPROM */
    fs_read_config(fsv_t1, MAX_EEPROM_SIZE, 0, BLOCK_64K); // NB: This only works because all product classes on this target use 64KB "EEPROM" blocks
    /* Apply the writes */
    memcpy( &fsv_t1[offset], src_buffer, bytes_to_copy );
    /* Write the entire (modified) EEPROM */
    sFLASH_WriteBuffer(fsv_t1, 0, BLOCK_64K);              // NB: This only works because all product classes on this target use 64KB "EEPROM" blocks

done:
    fs_safe_shred_and_free(&fsv_t1, MAX_EEPROM_SIZE);
}

#endif // #ifdef HELPER_BUILD

#endif // #if (defined(UBNT_ARM_STM32F30x) && UBNT_ARM_STM32F30x)
