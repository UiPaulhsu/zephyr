#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_MIPS_RTL838x) || SECURITY_ENABLE_SIMULATION)

// CPU revision ID register
#define __RTL838x_REV_ID                     ((uintptr_t)(0x1b0000D4))

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_RTL838x_cpu_rev_id_hw(void) {
	return (fs_read_mem32( __RTL838x_REV_ID ) >> 16);
}

#if !SECURITY_ENABLE_SIMULATION
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_cpu_rev_id_hw(void) {
	return fs_read_RTL838x_cpu_rev_id_hw();
}
#endif // #if !SECURITY_ENABLE_SIMULATION


#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_MIPS_RTL838x) || SECURITY_ENABLE_SIMULATION)
