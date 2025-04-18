#ifdef UBNT_SUPPORT_CLASS_AIRFIBER

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_airfiber_board_rev_id_fbd(void)                                     { return fs_read_config_be16toh(0x10); }
__FS_FUNCTION_PREFER_INLINE void      fs_read_airfiber_eth0_mac_address_fbd(u_int8_t* dest, size_t dest_len)      { fs_read_eth0_mac_address_fbd(dest, dest_len); }
__FS_FUNCTION_PREFER_INLINE void      fs_read_airfiber_air0_mac_address_fbd(u_int8_t* dest, size_t dest_len)      { fs_read_eth1_mac_address_fbd(dest, dest_len); }

#endif // #ifdef UBNT_SUPPORT_CLASS_AIRFIBER

