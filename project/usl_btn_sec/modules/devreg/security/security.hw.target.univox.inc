#if SECURITY_IS_TARGET_BUILD && SECURITY_ENABLE_SIMULATION && !defined(UBNT_ARM_BCM111xx) && !defined(UBNT_ARM_MT8117)

__FS_FUNCTION_PREFER_INLINE void _fs_check_univox_cpu_rev_id_sec_vs_hw(void) { 
    if (fs_read_univox_cpu_rev_id_sec() == BCM111xx_CPU_REV) {
        __fs_check_generic_sec_vs_hw(u_int32_t, univox_cpu_rev_id, BCM111xx_cpu_rev_id);
    } else if (fs_read_univox_cpu_rev_id_sec() == MT8117_CPU_REV) {
        __fs_check_generic_sec_vs_hw(u_int32_t, univox_cpu_rev_id, MT8117_cpu_rev_id);
    } else {
        fs_failure(FS_FAILURE_fs_check_univox_cpu_rev_id_sec_vs_hw_1);
    }
}

#endif

