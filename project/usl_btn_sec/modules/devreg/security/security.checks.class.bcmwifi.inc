#ifdef UBNT_SUPPORT_CLASS_BCMWIFI

__FS_FUNCTION_PREFER_INLINE void _fs_check_bcmwifi_cpu_rev_id_sec_vs_cpu_rev_id_bi(void)             { __fs_check_generic_sec_vs_bi(u_int32_t,bcmwifi_cpu_rev_id,cpu_rev_id); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_bcmwifi_eth0_mac_address_sec_vs_hw(void)                  { __fs_check_sec_array_vs_hw_array(eth0_mac_address,eth0_mac_address,MAC_ADDRESS_SIZE); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_bcmwifi_eth0_mac_address_sec_vs_fbd(void)                 { __fs_check_sec_array_vs_fbd_array(eth0_mac_address,bcmwifi_eth0_mac_address,MAC_ADDRESS_SIZE); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_bcmwifi_eth1_mac_address_sec_vs_fbd(void)                 { __fs_check_sec_array_vs_fbd_array(eth1_mac_address,bcmwifi_eth1_mac_address,MAC_ADDRESS_SIZE); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_bcmwifi_wifi_radio1_mac_address_sec_vs_fbd(void)               { __fs_check_sec_array_vs_fbd_array(bcmwifi_wifi_radio1_mac_address,bcmwifi_wifi_radio1_mac_address,MAC_ADDRESS_SIZE); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_bcmwifi_wifi_radio2_mac_address_sec_vs_fbd(void)               { __fs_check_sec_array_vs_fbd_array(bcmwifi_wifi_radio2_mac_address,bcmwifi_wifi_radio2_mac_address,MAC_ADDRESS_SIZE); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_bcmwifi_wifi_radio1_mac_address_sec_vs_bi(void)                { __fs_check_sec_array_vs_bi_array_if_bcmwifi_wifi_radio_exists(bcmwifi_wifi_radio1_mac_address,wifi_radio1_mac_address,MAC_ADDRESS_SIZE,1); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_bcmwifi_wifi_radio2_mac_address_sec_vs_bi(void)                { __fs_check_sec_array_vs_bi_array_if_bcmwifi_wifi_radio_exists(bcmwifi_wifi_radio2_mac_address,wifi_radio2_mac_address,MAC_ADDRESS_SIZE,2); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_bcmwifi_eth0_mac_address_sec_vs_bi(void)                  { __fs_check_sec_array_vs_bi_array(eth0_mac_address,eth0_mac_address,MAC_ADDRESS_SIZE); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_bcmwifi_eth1_mac_address_sec_vs_bi(void)                  { __fs_check_sec_array_vs_bi_array(eth1_mac_address,eth1_mac_address,MAC_ADDRESS_SIZE); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_bcmwifi_wifi_radio1_id_sec_vs_wifi_radio1_id_bi(void)          { __fs_check_generic_sec_vs_bi(u_int32_t,bcmwifi_wifi_radio1_id,wifi_radio1_id); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_bcmwifi_wifi_radio2_id_sec_vs_wifi_radio2_id_bi(void)          { __fs_check_generic_sec_vs_bi(u_int32_t,bcmwifi_wifi_radio2_id,wifi_radio2_id); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_bcmwifi_wifi_radio1_id_sec_vs_wifi_radio1_vendor_id_bi(void)   { __fs_check_generic_sec_vs_bi(u_int32_t,bcmwifi_wifi_radio1_vendor_id,wifi_radio1_vendor_id); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_bcmwifi_wifi_radio2_id_sec_vs_wifi_radio2_vendor_id_bi(void)   { __fs_check_generic_sec_vs_bi(u_int32_t,bcmwifi_wifi_radio2_vendor_id,wifi_radio2_vendor_id); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_bcmwifi_wifi_radio1_id_sec_vs_wifi_radio1_device_id_bi(void)   { __fs_check_generic_sec_vs_bi(u_int32_t,bcmwifi_wifi_radio1_device_id,wifi_radio1_device_id); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_bcmwifi_wifi_radio2_id_sec_vs_wifi_radio2_device_id_bi(void)   { __fs_check_generic_sec_vs_bi(u_int32_t,bcmwifi_wifi_radio2_device_id,wifi_radio2_device_id); }

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_bi__class_bcmwifi(void) {
    // NB: Subsystem ID is checked above
    _fs_check_bcmwifi_cpu_rev_id_sec_vs_cpu_rev_id_bi( );
    _fs_check_subvendor_id_sec_vs_vendor_id_bi( );
    _fs_check_bcmwifi_wifi_radio1_mac_address_sec_vs_bi();
    _fs_check_bcmwifi_wifi_radio2_mac_address_sec_vs_bi();
    _fs_check_bcmwifi_eth0_mac_address_sec_vs_bi();
    _fs_check_bcmwifi_eth1_mac_address_sec_vs_bi();
    _fs_check_bcmwifi_wifi_radio1_id_sec_vs_wifi_radio1_id_bi();
    _fs_check_bcmwifi_wifi_radio2_id_sec_vs_wifi_radio2_id_bi();
    _fs_check_bcmwifi_wifi_radio1_id_sec_vs_wifi_radio1_vendor_id_bi();
    _fs_check_bcmwifi_wifi_radio1_id_sec_vs_wifi_radio1_device_id_bi();
    _fs_check_bcmwifi_wifi_radio2_id_sec_vs_wifi_radio2_vendor_id_bi();
    _fs_check_bcmwifi_wifi_radio2_id_sec_vs_wifi_radio2_device_id_bi();
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw_no_pci__class_bcmwifi(void) {
    _fs_check_bcmwifi_cpu_rev_id_sec_vs_hw();
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw__class_bcmwifi(void) {
    _fs_check_bcmwifi_eth0_mac_address_sec_vs_hw();
    _fs_check_bcmwifi_wifi_radio1_mac_address_sec_vs_hw( );
    _fs_check_bcmwifi_wifi_radio2_mac_address_sec_vs_hw( );
    _fs_check_bcmwifi_wifi_radio1_id_sec_vs_hw();
    _fs_check_bcmwifi_wifi_radio2_id_sec_vs_hw();
}
__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_fbd__class_bcmwifi(void) {
    // NB: eth0 and eth1 MAC are NOT allowed to be changed for MAC clone
    _fs_check_bcmwifi_eth0_mac_address_sec_vs_fbd();
    _fs_check_bcmwifi_eth1_mac_address_sec_vs_fbd();
    _fs_check_subsystem_id_sec_vs_fbd();
    _fs_check_subvendor_id_sec_vs_fbd();
    _fs_check_bcmwifi_wifi_radio1_mac_address_sec_vs_fbd();
    _fs_check_bcmwifi_wifi_radio2_mac_address_sec_vs_fbd();
}

#else // #ifdef UBNT_SUPPORT_CLASS_BCMWIFI

#undef _fs_check_sec_vs_bi__class_bcmwifi
#undef _fs_check_sec_vs_hw_no_pci__class_bcmwifi
#undef _fs_check_sec_vs_hw__class_bcmwifi
#undef _fs_check_sec_vs_fbd__class_bcmwifi

#define _fs_check_sec_vs_bi__class_bcmwifi()        fs_failure(FS_FAILURE_fs_check_sec_vs_bi_1)
#define _fs_check_sec_vs_hw_no_pci__class_bcmwifi() fs_failure(FS_FAILURE_fs_check_sec_vs_hw_no_pci_1)
#define _fs_check_sec_vs_hw__class_bcmwifi()        fs_failure(FS_FAILURE_fs_check_sec_vs_hw_1)
#define _fs_check_sec_vs_fbd__class_bcmwifi()       fs_failure(FS_FAILURE_fs_check_sec_vs_fbd_1)

#endif // #ifdef UBNT_SUPPORT_CLASS_BCMWIFI


