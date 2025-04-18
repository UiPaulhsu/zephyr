#ifdef UBNT_SUPPORT_CLASS_BCMSWITCH
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_bcmswitch_cpu_rev_id_sec(void) { return fs_read_config_be32toh(fs_get_config_offset_cpu_rev_id_sec()); }
__FS_FUNCTION_PREFER_INLINE void      fs_read_bcmswitch_vpd_sec(uint8_t* dest, size_t dest_len) { fs_read_config(dest, dest_len, fs_get_config_offset_vpd_sec(), BCMSWITCH_VPD_SIZE ); }
#endif // #ifdef UBNT_SUPPORT_CLASS_BCMSWITCH

