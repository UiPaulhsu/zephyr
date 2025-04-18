#if SECURITY_IS_TARGET_BUILD && defined(UBNT_EFR32xG13)

extern uint32_t sCPU_Read_ID(void);

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_cpu_rev_id_hw(void) {
    return sCPU_Read_ID();
}

#endif // #if SECURITY_IS_TARGET_BUILD && defined(UBNT_EFR32xG13)
