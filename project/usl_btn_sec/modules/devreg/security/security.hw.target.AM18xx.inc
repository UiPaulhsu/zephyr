#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_AM18xx) || SECURITY_ENABLE_SIMULATION)

#define __AM18xx_CPU_REV_ID 0x01C14000

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_AM18xx_cpu_rev_id_hw(void) {
        return fs_read_mem32( __AM18xx_CPU_REV_ID );
}

#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_AM18xx) || SECURITY_ENABLE_SIMULATION)
