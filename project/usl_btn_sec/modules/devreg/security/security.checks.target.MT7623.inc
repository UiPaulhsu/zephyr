#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_MT7623) || SECURITY_ENABLE_SIMULATION)
__FS_FUNCTION_PREFER_INLINE void _fs_check_cloudkey_cpu_rev_id_sec_vs_hw(void)                     { __fs_check_generic_sec_vs_hw(u_int32_t,cloudkey_cpu_rev_id,MT7623_cpu_rev_id); }

#if !SECURITY_ENABLE_SIMULATION
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_cpu_rev_id_hw(void) {
	return fs_read_MT7623_cpu_rev_id_hw();
}

#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_MT7623) || SECURITY_ENABLE_SIMULATION)
#endif // #if !SECURITY_ENABLE_SIMULATION

