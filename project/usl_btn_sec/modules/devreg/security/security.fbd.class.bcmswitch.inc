#ifdef UBNT_SUPPORT_CLASS_BCMSWITCH
__FS_FUNCTION_PREFER_INLINE void      fs_read_bcmswitch_eth0_mac_address_fbd(u_int8_t* dest, size_t dest_len)        { fs_read_eth0_mac_address_fbd(dest, dest_len); }
//__FS_FUNCTION_PREFER_INLINE void      fs_read_bcmswitch_eth1_mac_address_fbd(u_int8_t* dest, size_t dest_len)        { fs_read_eth1_mac_address_fbd(dest, dest_len); }
__FS_FUNCTION_PREFER_INLINE void      fs_read_bcmswitch_vpd_fbd(u_int8_t* dest, size_t dest_len)                     { fs_read_config(dest, dest_len, FLASH_BOARD_DATA_OFFSET_BCMSWITCH_VPD, BCMSWITCH_VPD_SIZE); }
#endif // #ifdef UBNT_SUPPORT_CLASS_BCMSWITCH

