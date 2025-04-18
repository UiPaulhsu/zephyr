
#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_MIPS_RTL838x) || SECURITY_ENABLE_SIMULATION)
#if !SECURITY_ENABLE_SIMULATION
__FS_FUNCTION_PREFER_INLINE void _fs_check_cpu_rev_id_sec_vs_hw(void)                      { __fs_check_generic_sec_vs_hw(u_int32_t,basic_cpu_rev_id,cpu_rev_id); }
#endif
#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_MIPS_RTL838x) || SECURITY_ENABLE_SIMULATION)

