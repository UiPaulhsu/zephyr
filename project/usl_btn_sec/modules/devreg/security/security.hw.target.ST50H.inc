#if SECURITY_IS_TARGET_BUILD && defined(UBNT_ST50H)

extern uint32_t devreg_read_cpu_id(void);

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_cpu_rev_id_hw(void) {
    return devreg_read_cpu_id();
}

#endif // #if SECURITY_IS_TARGET_BUILD && defined(UBNT_ST50H)
