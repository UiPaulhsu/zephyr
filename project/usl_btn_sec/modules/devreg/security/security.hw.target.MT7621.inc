#if SECURITY_IS_TARGET_BUILD && defined(UBNT_MIPS_MT7621)

#ifdef UNIFI_MT7621

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_cpu_rev_id_hw(void) {
#ifdef __KERNEL__
#if defined(UBNT_MIPS_MT7621_FIX_CPUID)
	return fs_read_mem32((uintptr_t)0x1E00000C);
#else
	u_int32_t ret;
	asm volatile ("mfc0 %[val], $15" : [val] "=r" (ret));
	return ret;
#endif // #if defined(UBNT_MIPS_MT7621_FIX_CPUID)
#else /* __KERNEL__ */

#define PRID_MARKER     "cpu_rev_id="
#define PRID_MARKER_LEN 11
	u_int32_t ret = 0;
	char buf[64];
	FILE *f = fopen("/proc/ubnthal/system.info", "r");
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

#else /* #ifdef UNIFI_MT7621 */

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_cpu_rev_id_hw(void) {
#ifdef __KERNEL__
	u_int32_t ret;
	asm volatile ("mfc0 %[val], $15" : [val] "=r" (ret));
	return ret;
#else /* __KERNEL__ */

#define PRID_MARKER     "processor_id:"
#define PRID_MARKER_LEN 13
	u_int32_t ret = 0;
	char buf[64];
	FILE *f = fopen("/proc/octeon_info", "r"); // NB: I'm not sure this is correct?!?!
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

#endif /* #ifdef UNIFI_MT7621 */

#endif // #if SECURITY_IS_TARGET_BUILD && defined(UBNT_MIPS_MT7621)
