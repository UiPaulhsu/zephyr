#ifdef UBNT_SUPPORT_CLASS_BCMWIFI


__FS_FUNCTION_PREFER_INLINE void      fs_read_bcmwifi_eth0_mac_address_fbd(u_int8_t* dest, size_t dest_len)       { fs_read_eth0_mac_address_fbd(dest, dest_len); }
__FS_FUNCTION_PREFER_INLINE void      fs_read_bcmwifi_eth1_mac_address_fbd(u_int8_t* dest, size_t dest_len)       { fs_read_eth1_mac_address_fbd(dest, dest_len); }
__FS_FUNCTION_PREFER_INLINE void      fs_read_bcmwifi_wifi_radio1_mac_address_fbd(u_int8_t* dest, size_t dest_len)     { fs_read_config(dest, dest_len, 0x14, MAC_ADDRESS_SIZE); }
__FS_FUNCTION_PREFER_INLINE void      fs_read_bcmwifi_wifi_radio2_mac_address_fbd(u_int8_t* dest, size_t dest_len)     { fs_read_config(dest, dest_len, 0x1a, MAC_ADDRESS_SIZE); }

#endif // #ifdef UBNT_SUPPORT_CLASS_BCMWIFI

