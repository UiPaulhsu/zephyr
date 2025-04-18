#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM64_APQ8053) || SECURITY_ENABLE_SIMULATION)

#if SECURITY_ENABLE_SIMULATION

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_APQ8053_cpu_rev_id_hw(void) {
	/* FIXME: KMLUOH */
	return 0x410fd034;
}

#else // #if SECURITY_ENABLE_SIMULATION

#ifdef __KERNEL__

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_APQ8053_cpu_rev_id_hw(void) {
	/* FIXME: KMLUOH */
	return 0x410fd034;
}

#else /* ifdef __KERNEL__ */

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_APQ8053_cpu_rev_id_hw(void) {
	u_int8_t buf[16];
	size_t l;
	u_int32_t cpu_id = 0xffffffff;

	memset(buf, 0, 16);
	l = 0;
	fs_read_file_into_buffer(buf, 16, fs_get_sys_devices_system_cpu_cpu0_cpuid(), &l);
	if (l > 0) {
		sscanf((const char*)buf, "%x", &cpu_id);
	}
	return cpu_id;
}

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_cpu_rev_id_hw(void) {
	return fs_read_APQ8053_cpu_rev_id_hw();
}

#endif /* ifdef __KERNEL__ */

#endif // #if SECURITY_ENABLE_SIMULATION

#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM64_APQ8053) || SECURITY_ENABLE_SIMULATION)
