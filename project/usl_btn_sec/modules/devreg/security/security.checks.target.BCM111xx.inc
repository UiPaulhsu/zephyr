#if SECURITY_IS_TARGET_BUILD && defined(UBNT_ARM_BCM111xx)

__FS_FUNCTION_PREFER_INLINE void _fs_check_univox_cpu_rev_id_sec_vs_hw(void)                      { __fs_check_generic_sec_vs_hw(u_int32_t,univox_cpu_rev_id,BCM111xx_cpu_rev_id); }

#endif // #if SECURITY_IS_TARGET_BUILD && defined(UBNT_ARM_BCM111xx)
