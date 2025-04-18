#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_AM18xx) || SECURITY_ENABLE_SIMULATION)

__FS_FUNCTION_PREFER_INLINE void _fs_check_airfiber_cpu_rev_id_sec_vs_hw(void)                    { __fs_check_generic_sec_vs_hw(u_int32_t,airfiber_cpu_rev_id,AM18xx_cpu_rev_id); }

#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_AM18xx) || SECURITY_ENABLE_SIMULATION)
