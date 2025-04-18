#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_IPQ806x) || SECURITY_ENABLE_SIMULATION)

#define IPQ806x_RTC_SOC_REG_BASE_ADDRESS  (0x80000)
#define IPQ806x_SOC_CHIP_ID_ADDRESS       (0xec + IPQ806x_RTC_SOC_REG_BASE_ADDRESS)

#define _read_ipq806x_cpuid_in_kernel()   \
    ({                                    \
        unsigned int __val;               \
        asm("mrc p15, 0, %0, c0, c0, 0"   \
            : "=r" (__val)                \
            :                             \
            : "cc");                      \
        __val;                            \
    })

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_IPQ806x_cpu_rev_id_hw(void) {
#ifdef __KERNEL__
    return _read_ipq806x_cpuid_in_kernel();
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
	return fs_read_IPQ806x_cpu_rev_id_hw();
}
#endif // #if !SECURITY_ENABLE_SIMULATION

#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_IPQ806x) || SECURITY_ENABLE_SIMULATION)
