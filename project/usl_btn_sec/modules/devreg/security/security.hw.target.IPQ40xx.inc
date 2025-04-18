#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_IPQ40xx) || SECURITY_ENABLE_SIMULATION)
/*
If we aren't simulating and we're on the IPQ40xx platform then we are using platform-specific
replacements for the fs_read_* functions.  

When we are running in simulated mode, these names already implemented in security.hw.target.ARxxxx.inc.

To keep things simple, special case for IPQ40xx.  Set CPU_ID to 0x0003d0ex (i.e. 0x0003d0e1) and CPU, radio1 and radio2 IDs will be return that CPU ID.
*/

#define __IPQ40xx_REV_ID_MASK_MAJOR 0x00FFFFFF
#define __IPQ40xx_REV_ID_MASK_MINOR 0xFF000000
#define __IPQ4029_DAKOTA_CPU_MAJOR  0x0003d0e1
#define __IPQ4028_DAKOTA_CPU_MAJOR  0x000150e1
#define __IPQ40XX_DAKOTA_CPU_MINOR(__R) (__R << 24)

#define __IPQ4028_DAKOTA_CPU_REV_0  (__IPQ40XX_DAKOTA_CPU_MINOR(0) | __IPQ4028_DAKOTA_CPU_MAJOR)
#define __IPQ4028_DAKOTA_CPU_REV_1  (__IPQ40XX_DAKOTA_CPU_MINOR(1) | __IPQ4028_DAKOTA_CPU_MAJOR)
#define __IPQ4028_DAKOTA_CPU_REV_2  (__IPQ40XX_DAKOTA_CPU_MINOR(2) | __IPQ4028_DAKOTA_CPU_MAJOR)
#define __IPQ4028_DAKOTA_CPU_REV_3  (__IPQ40XX_DAKOTA_CPU_MINOR(3) | __IPQ4028_DAKOTA_CPU_MAJOR)
#define __IPQ4028_DAKOTA_CPU_REV_4  (__IPQ40XX_DAKOTA_CPU_MINOR(4) | __IPQ4028_DAKOTA_CPU_MAJOR)
#define __IPQ4028_DAKOTA_CPU_REV_5  (__IPQ40XX_DAKOTA_CPU_MINOR(5) | __IPQ4028_DAKOTA_CPU_MAJOR)

#define __IPQ4029_DAKOTA_CPU_REV_0  (__IPQ40XX_DAKOTA_CPU_MINOR(0) | __IPQ4029_DAKOTA_CPU_MAJOR)
#define __IPQ4029_DAKOTA_CPU_REV_1  (__IPQ40XX_DAKOTA_CPU_MINOR(1) | __IPQ4029_DAKOTA_CPU_MAJOR)
#define __IPQ4029_DAKOTA_CPU_REV_2  (__IPQ40XX_DAKOTA_CPU_MINOR(2) | __IPQ4029_DAKOTA_CPU_MAJOR)
#define __IPQ4029_DAKOTA_CPU_REV_3  (__IPQ40XX_DAKOTA_CPU_MINOR(3) | __IPQ4029_DAKOTA_CPU_MAJOR)
#define __IPQ4029_DAKOTA_CPU_REV_4  (__IPQ40XX_DAKOTA_CPU_MINOR(4) | __IPQ4029_DAKOTA_CPU_MAJOR)
#define __IPQ4029_DAKOTA_CPU_REV_5  (__IPQ40XX_DAKOTA_CPU_MINOR(5) | __IPQ4029_DAKOTA_CPU_MAJOR)
// ... 

__FS_FUNCTION_PREFER_INLINE int fs_is_ipq40xx(u_int32_t fsa_cpu_silicon_revision) { 
    switch(fsa_cpu_silicon_revision & __IPQ40xx_REV_ID_MASK_MAJOR) {
    case __IPQ4028_DAKOTA_CPU_MAJOR:
    case __IPQ4029_DAKOTA_CPU_MAJOR:
        return 1;
    }
    return 0;
}

#if !SECURITY_ENABLE_SIMULATION
#define _read_ipq40xx_cpuid_in_kernel()   \
    ({                                    \
        unsigned int __val;               \
        asm("mrc p15, 0, %0, c0, c0, 0"   \
            : "=r" (__val)                \
            :                             \
            : "cc");                      \
        __val;                            \
    })

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_cpu_rev_id_hw(void) {
#ifdef __KERNEL__
    return _read_ipq40xx_cpuid_in_kernel();
#else
    FILE* fp;
    char line[128];
    u_int32_t cpu_id = 0;

    fp = fopen("/proc/ubnthal/board.info", "r");
    if(fp) {
        while (fgets(line, sizeof(line), fp)) {
            if (sscanf(line, "board.cpurevision=%x\n", &cpu_id)) {
                break;
            }
        }
        fclose(fp);
    }
    return cpu_id;
#endif
}

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_wifi_radio1_mac_rev_id_hw(void) {
	return fs_read_cpu_rev_id_hw();
}

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_wifi_radio2_mac_rev_id_hw(void) {
	return fs_read_cpu_rev_id_hw();
}

#endif // #if !SECURITY_ENABLE_SIMULATION


#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_IPQ40xx) || SECURITY_ENABLE_SIMULATION)

