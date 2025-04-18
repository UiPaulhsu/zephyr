#if SECURITY_IS_TARGET_BUILD && defined(UBNT_MIPS_CN50xx)

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_cpu_rev_id_hw(void) {
#ifdef __KERNEL__
	u_int32_t ret = 0;
	asm volatile ("mfc0 %[val], $15" : [val] "=r" (ret));
	return ret;
#else /* !__KERNEL__ */
#define PRID_MARKER     "processor_id:"
#define PRID_MARKER_LEN 13
	u_int32_t ret = 0;
	char buf[64];
	FILE *f = fopen("/proc/octeon_info", "r");
	if (!f) {
		fs_debug_printf("Error opening proc\n");
		goto done;
	}
	while (fgets(buf, 64, f)) {
		char *s = buf + PRID_MARKER_LEN;
		if (strncmp(buf, PRID_MARKER, PRID_MARKER_LEN) != 0) {
			continue;
		}
		ret = strtoul(s, NULL, 16);
		break;
	}

done:
	if (f) {
		fclose(f);
	}
	return ret;
#endif /* __KERNEL__ */
}

#endif // #if SECURITY_IS_TARGET_BUILD && defined(UBNT_MIPS_CN50xx)

