#if SECURITY_ENABLE_INI_SUPPORT

__FS_FUNCTION_PREFER_INLINE int       fs_file_exists_bi(void)                                        { return fs_file_exists(fs_get_boardinfo_pathname()); }
__FS_FUNCTION_PREFER_INLINE int       fs_has_cpu_rev_id_bi(void)                                     { return fs_file_exists_bi() && fs_has_ini_key( fs_get_boardinfo_pathname(),    fs_get_boardinfo_key__board_cpu_rev_id() ); }
__FS_FUNCTION_PREFER_INLINE u_int16_t fs_read_system_id_bi(void)                                     { return fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid()         , 1, 0xffff ); }
__FS_FUNCTION_PREFER_INLINE u_int16_t fs_read_vendor_id_bi(void)                                     { return fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_vendid()        , 1, 0xffff ); }
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_cpu_rev_id_bi(void)                                    { return fs_read_ini_hex32( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_cpu_rev_id()    , 0, 0xffffffff ); }
__FS_FUNCTION_PREFER_INLINE void      fs_read_hwaddr_bi(u_int8_t* dest, size_t dest_len)             { fs_read_ini_hex_raw(dest, dest_len, fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_hwaddr(), MAC_ADDRESS_SIZE, MAC_ADDRESS_SIZE, 1); }
__FS_FUNCTION_PREFER_INLINE void      fs_read_eth0_mac_address_bi(u_int8_t* dest, size_t dest_len)   { fs_read_ini_hex_raw(dest, dest_len, fs_get_boardinfo_pathname(), fs_get_boardinfo_key__eth0_mac_address(), MAC_ADDRESS_SIZE, MAC_ADDRESS_SIZE, 1); }
__FS_FUNCTION_PREFER_INLINE void      fs_read_eth1_mac_address_bi(u_int8_t* dest, size_t dest_len)   { fs_read_ini_hex_raw(dest, dest_len, fs_get_boardinfo_pathname(), fs_get_boardinfo_key__eth1_mac_address(), MAC_ADDRESS_SIZE, MAC_ADDRESS_SIZE, 1); }
__FS_FUNCTION_PREFER_INLINE int       fs_has_eth0_mac_address_bi(void)                               { return fs_has_ini_key( fs_get_boardinfo_pathname(),    fs_get_boardinfo_key__eth0_mac_address() ); }
__FS_FUNCTION_PREFER_INLINE int       fs_has_eth1_mac_address_bi(void)                               { return fs_has_ini_key( fs_get_boardinfo_pathname(),    fs_get_boardinfo_key__eth1_mac_address() ); }
__FS_FUNCTION_PREFER_INLINE int       fs_has_vendor_id_bi(void)                                      { return fs_has_ini_key( fs_get_boardinfo_pathname(),    fs_get_boardinfo_key__board_vendid() ); }
__FS_FUNCTION_PREFER_INLINE int       fs_has_system_id_bi(void)                                      { return fs_has_ini_key( fs_get_boardinfo_pathname(),    fs_get_boardinfo_key__board_sysid() ); }

#if defined(UBNT_SUPPORT_CLASS_WIFI) || defined(UBNT_SUPPORT_CLASS_BCMWIFI)
__FS_FUNCTION_PREFER_INLINE u_int16_t fs_read_wifi_radio1_subvendor_id_bi(void)                      { return fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__wifi_radio_1_subvendorid() , 1, 0xffff ); }
__FS_FUNCTION_PREFER_INLINE u_int16_t fs_read_wifi_radio2_subvendor_id_bi(void)                      { return fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__wifi_radio_2_subvendorid() , 1, 0xffff ); }
__FS_FUNCTION_PREFER_INLINE u_int16_t fs_read_wifi_radio1_subsystem_id_bi(void)                      { return fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__wifi_radio_1_subsystemid() , 1, 0xffff ); }
__FS_FUNCTION_PREFER_INLINE u_int16_t fs_read_wifi_radio2_subsystem_id_bi(void)                      { return fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__wifi_radio_2_subsystemid() , 1, 0xffff ); }
__FS_FUNCTION_PREFER_INLINE u_int16_t fs_read_wifi_radio1_vendor_id_bi(void)                         { return fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__wifi_radio_1_vendorid()    , 1, 0xffff ); }
__FS_FUNCTION_PREFER_INLINE u_int16_t fs_read_wifi_radio2_vendor_id_bi(void)                         { return fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__wifi_radio_2_vendorid()    , 1, 0xffff ); }
__FS_FUNCTION_PREFER_INLINE u_int16_t fs_read_wifi_radio1_device_id_bi(void)                         { return fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__wifi_radio_1_deviceid()    , 1, 0xffff ); }
__FS_FUNCTION_PREFER_INLINE u_int16_t fs_read_wifi_radio2_device_id_bi(void)                         { return fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__wifi_radio_2_deviceid()    , 1, 0xffff ); }
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_wifi_radio1_id_bi(void)                                { return fs_read_ini_hex32( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__wifi_radio_1_id()          , 1, 0xffffffff ); }
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_wifi_radio2_id_bi(void)                                { return fs_read_ini_hex32( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__wifi_radio_2_id()          , 1, 0xffffffff ); }
__FS_FUNCTION_PREFER_INLINE void      fs_read_wifi_radio1_mac_address_bi(u_int8_t* dest, size_t dest_len) { fs_read_ini_hex_raw(dest, dest_len, fs_get_boardinfo_pathname(), fs_get_boardinfo_key__wifi_radio1_mac_address(), MAC_ADDRESS_SIZE, MAC_ADDRESS_SIZE, 1); }
__FS_FUNCTION_PREFER_INLINE void      fs_read_wifi_radio2_mac_address_bi(u_int8_t* dest, size_t dest_len) { fs_read_ini_hex_raw(dest, dest_len, fs_get_boardinfo_pathname(), fs_get_boardinfo_key__wifi_radio2_mac_address(), MAC_ADDRESS_SIZE, MAC_ADDRESS_SIZE, 1); }
__FS_FUNCTION_PREFER_INLINE int       fs_has_wifi_radio1_mac_address_bi(void)                        { return fs_has_ini_key( fs_get_boardinfo_pathname(),    fs_get_boardinfo_key__wifi_radio1_mac_address() ); }
__FS_FUNCTION_PREFER_INLINE int       fs_has_wifi_radio2_mac_address_bi(void)                        { return fs_has_ini_key( fs_get_boardinfo_pathname(),    fs_get_boardinfo_key__wifi_radio2_mac_address() ); }
#endif // #if defined(UBNT_SUPPORT_CLASS_WIFI) || defined(UBNT_SUPPORT_CLASS_BCMWIFI)

#endif // #if SECURITY_ENABLE_INI_SUPPORT
