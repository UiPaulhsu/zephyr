#if SECURITY_IS_TARGET_BUILD && defined(UBNT_MIPS_MT7621)
__FS_FUNCTION_PREFER_INLINE void _fs_check_router_cpu_rev_id_sec_vs_hw(void)                      { __fs_check_generic_sec_vs_hw(u_int32_t,router_cpu_rev_id,cpu_rev_id); }
#endif // #if SECURITY_IS_TARGET_BUILD && defined(UBNT_MIPS_MT7621)

#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_MIPS_MT7621) || SECURITY_ENABLE_SIMULATION)
__FS_FUNCTION_PREFER_INLINE void _fs_check_solargateway_cpu_rev_id_sec_vs_hw(void)                { __fs_check_generic_sec_vs_hw(u_int32_t,solargateway_cpu_rev_id,cpu_rev_id); }
#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_MIPS_MT7621) || SECURITY_ENABLE_SIMULATION)

