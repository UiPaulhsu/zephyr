#ifdef UBNT_SUPPORT_CLASS_AIRFIBER
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_airfiber_cpu_rev_id_sec(void)                                         { return fs_read_config_be32toh(fs_get_config_offset_cpu_rev_id_sec()); }
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_airfiber_old_board_rev_id_sec(void)                                   { return fs_read_config_be16toh(FLASH_SECURITY_OFFSET_AIRFIBER_OLD_BOARD_REV_ID        ); }
__FS_FUNCTION_PREFER_INLINE void      fs_read_airfiber_eth0_mac_address_sec(u_int8_t* dest, size_t dest_len)        { fs_read_config(dest, dest_len, fs_get_config_offset_eth0_mac_address_sec(), MAC_ADDRESS_SIZE); }
__FS_FUNCTION_PREFER_INLINE void      fs_read_airfiber_air0_mac_address_sec(u_int8_t* dest, size_t dest_len)        { fs_read_config(dest, dest_len, fs_get_config_offset_eth1_mac_address_sec(), MAC_ADDRESS_SIZE); }
#endif // #ifdef UBNT_SUPPORT_CLASS_AIRFIBER

