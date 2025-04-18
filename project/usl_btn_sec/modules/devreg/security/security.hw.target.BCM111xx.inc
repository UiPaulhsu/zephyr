#define BCM111xx_CPU_REV      0x111400a2

#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_BCM111xx) || SECURITY_ENABLE_SIMULATION)

#define __BCM111xx_CPU_REV_ID 0x35004000

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_BCM111xx_cpu_rev_id_hw(void) {
        return fs_read_mem32( __BCM111xx_CPU_REV_ID );
}
#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_BCM111xx) || SECURITY_ENABLE_SIMULATION)
