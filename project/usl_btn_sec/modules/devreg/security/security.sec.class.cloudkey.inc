#ifdef UBNT_SUPPORT_CLASS_CLOUDKEY
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_cloudkey_cpu_rev_id_sec(void)                     { return fs_read_config_be32toh(fs_get_config_offset_cpu_rev_id_sec()); }
#endif // #ifdef UBNT_SUPPORT_CLASS_CLOUDKEY

