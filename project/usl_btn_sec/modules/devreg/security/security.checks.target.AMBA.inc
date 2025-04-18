#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_AMBA) || SECURITY_ENABLE_SIMULATION)

__FS_FUNCTION_PREFER_INLINE void _fs_check_camera2_ssi_ident_id_sec_vs_hw(void)                      { __fs_check_generic_sec_vs_hw(u_int32_t,camera2_ssi_ident_id,AMBA_ssi_ident_id); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_camera2_ssi_version_id_sec_vs_hw(void)                    { __fs_check_generic_sec_vs_hw(u_int32_t,camera2_ssi_version_id,AMBA_ssi_version_id); }

#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_A5S) || SECURITY_ENABLE_SIMULATION)

