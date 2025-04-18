#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM64_AL324) || SECURITY_ENABLE_SIMULATION)

#if SECURITY_ENABLE_SIMULATION

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_AL324_cpu_rev_id_hw(void) {
	/* FIXME: KMLUOH */
	return 0x411fd073;
}

#else // #if SECURITY_ENABLE_SIMULATION

#ifdef __KERNEL__

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_AL324_cpu_rev_id_hw(void) {
	/* FIXME: KMLUOH */
	return 0x411fd073;
}

#else /* ifdef __KERNEL__ */

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_AL324_cpu_rev_id_hw(void) {
	int fd;
	char buf[16];
	u_int32_t cpu_id = 0xffffffff;

	memset(buf, 0, 16);
	fd = open("/proc/cpumidr", O_RDONLY);
	if (fd < 0)
		return cpu_id;

	if (read(fd, buf, sizeof(buf)) < 0) {
		close(fd);
		return cpu_id;
	}
	close(fd);
	cpu_id = strtol(buf, NULL, 16);

	return cpu_id;
}

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_cpu_rev_id_hw(void) {
	return fs_read_AL324_cpu_rev_id_hw();
}

#endif /* ifdef __KERNEL__ */

#endif // #if SECURITY_ENABLE_SIMULATION

#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM64_AL324) || SECURITY_ENABLE_SIMULATION)
