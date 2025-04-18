#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM64_IPQ807x) || SECURITY_ENABLE_SIMULATION)

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_IPQ807x_cpu_rev_id_hw(void) {
#ifdef __KERNEL__
    u_int32_t soc_id = 0;

    void *soc_id_addr = ioremap_nocache(0x01110010, 8);
    if (soc_id_addr) {
        soc_id = readl_relaxed((volatile void __iomem *)soc_id_addr);
        iounmap(soc_id_addr);
    }

    return soc_id;
#else
    FILE* fp;
    char line[128];
    u_int32_t cpu_id = 0;

    fp = fopen("/proc/ubnthal/system.info", "r");
    if(fp) {
        while (fgets(line, sizeof(line), fp)) {
            if (sscanf(line, "cpuid=%x\n", &cpu_id)) {
                break;
            }
        }
        fclose(fp);
    }
    return cpu_id;
#endif
}

#if !SECURITY_ENABLE_SIMULATION
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_cpu_rev_id_hw(void) {
	return fs_read_IPQ807x_cpu_rev_id_hw();
}
#endif // #if !SECURITY_ENABLE_SIMULATION

#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM64_IPQ807x) || SECURITY_ENABLE_SIMULATION)
