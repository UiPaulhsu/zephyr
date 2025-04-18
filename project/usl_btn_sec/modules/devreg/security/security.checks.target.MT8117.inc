#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_MT8117))

__FS_FUNCTION_PREFER_INLINE void _fs_check_univox_cpu_rev_id_sec_vs_hw(void)                      { __fs_check_generic_sec_vs_hw(u_int32_t,univox_cpu_rev_id,MT8117_cpu_rev_id); }

#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_MT8117) || SECURITY_ENABLE_SIMULATION)
