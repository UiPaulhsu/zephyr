#if SECURITY_ENABLE_SIMULATION

__FS_FUNCTION_PREFER_INLINE size_t fs_read_flash_uid_hw(u_int8_t* dest, size_t dest_len) {
    return fs_read_ini_hex_raw(dest, dest_len, g_simulation_ini_filename, "FLASH_UID", 0, MAX_FLASH_UID_SIZE, 1);
}

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_flash_type_id_hw() {
	__FS_LOCAL_STATIC_OPTION u_int32_t fsv_t1;

	fsv_t1 = 0;
	fs_read_ini_hex_raw(
					   ((u_int8_t*)&fsv_t1), 
					   sizeof fsv_t1, 
					   g_simulation_ini_filename,
					   "FLASH_TYPE_ID", 
					   3,/* bytes, not characters */ 
                       4,
					   1); 
	return be32toh(fsv_t1);
}

#endif // #if SECURITY_ENABLE_SIMULATION

