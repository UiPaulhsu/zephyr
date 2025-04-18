#ifdef UBNT_SUPPORT_CLASS_CAMERA2
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_camera2_ssi_ident_id_sec(void)                 { return fs_read_config_be32toh(FLASH_SECURITY_OFFSET_CAMERA2_SSI_IDENT_ID             ); }
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_camera2_ssi_version_id_sec(void)               { return fs_read_config_be32toh(FLASH_SECURITY_OFFSET_CAMERA2_SSI_VERSION_ID           ); }
#endif // #ifdef UBNT_SUPPORT_CLASS_CAMERA2

