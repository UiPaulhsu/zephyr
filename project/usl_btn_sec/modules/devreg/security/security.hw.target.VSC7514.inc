#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_MIPS_VSC7514) || SECURITY_ENABLE_SIMULATION)

#if !SECURITY_ENABLE_SIMULATION
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_cpu_rev_id_hw(void) {
#ifdef __KERNEL__
	return readl(VTSS_DEVCPU_GCB_CHIP_REGS_CHIP_ID);
#else /* __KERNEL__ */

#define PRID_MARKER     "cpuid="
#define PRID_MARKER_LEN 6
	u_int32_t ret = 0;
	char buf[64];
	FILE *f = fopen("/proc/ubnthal/system.info", "r"); // NB: I'm not sure this is correct?!?!
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
#endif // #if !SECURITY_ENABLE_SIMULATION

#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_MIPS_VSC7514) || SECURITY_ENABLE_SIMULATION)
