#ifdef UBNT_SUPPORT_CLASS_WIFI
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_wifi_cpu_rev_id_sec(void) { return fs_read_config_be32toh(fs_get_config_offset_cpu_rev_id_sec()); }
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_wifi_radio1_mac_rev_id_sec(void) { return fs_read_config_be32toh(fs_get_config_offset_radio1_rev_id_sec()); }
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_wifi_radio2_mac_rev_id_sec(void) { return fs_read_config_be32toh(fs_get_config_offset_radio2_rev_id_sec()); }
__FS_FUNCTION_PREFER_INLINE void      fs_read_wifi_radio1_mac_address_sec(u_int8_t* dest, size_t dest_len) { fs_read_config(dest, dest_len, fs_get_config_offset_radio1_mac_address_sec(), MAC_ADDRESS_SIZE); }
__FS_FUNCTION_PREFER_INLINE void      fs_read_wifi_radio2_mac_address_sec(u_int8_t* dest, size_t dest_len) { fs_read_config(dest, dest_len, fs_get_config_offset_radio2_mac_address_sec(), MAC_ADDRESS_SIZE); }
#endif // #ifdef UBNT_SUPPORT_CLASS_WIFI

