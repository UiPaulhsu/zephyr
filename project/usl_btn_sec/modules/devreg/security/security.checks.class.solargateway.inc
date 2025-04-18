#ifdef UBNT_SUPPORT_CLASS_SOLARGATEWAY

__FS_FUNCTION_PREFER_INLINE void _fs_check_solargateway_eth0_mac_address_sec_vs_hw(void)                { __fs_check_sec_array_vs_hw_array(eth0_mac_address,eth0_mac_address,MAC_ADDRESS_SIZE); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_solargateway_eth0_mac_address_sec_vs_fbd(void)               { __fs_check_sec_array_vs_fbd_array(eth0_mac_address,solargateway_eth0_mac_address,MAC_ADDRESS_SIZE); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_solargateway_eth1_mac_address_sec_vs_hw(void)                { __fs_check_sec_array_vs_hw_array(eth1_mac_address,eth1_mac_address,MAC_ADDRESS_SIZE); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_solargateway_eth1_mac_address_sec_vs_fbd(void)               { __fs_check_sec_array_vs_fbd_array(eth1_mac_address,solargateway_eth1_mac_address,MAC_ADDRESS_SIZE); }

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_bi__class_solargateway(void) {
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw_no_pci__class_solargateway(void) {
    _fs_check_solargateway_cpu_rev_id_sec_vs_hw();
    _fs_check_solargateway_eth0_mac_address_sec_vs_hw();
    _fs_check_solargateway_eth1_mac_address_sec_vs_hw();
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw__class_solargateway(void) {
    // Nothing to do here
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_fbd__class_solargateway(void) {
    _fs_check_solargateway_eth0_mac_address_sec_vs_fbd();
    _fs_check_solargateway_eth1_mac_address_sec_vs_fbd();
    _fs_check_subsystem_id_sec_vs_fbd();
    _fs_check_subvendor_id_sec_vs_fbd();
    _fs_check_pcba_sec_vs_fbd();
}

#else // #ifdef UBNT_SUPPORT_CLASS_SOLARGATEWAY

#undef _fs_check_sec_vs_bi__class_solargateway
#undef _fs_check_sec_vs_hw_no_pci__class_solargateway
#undef _fs_check_sec_vs_hw__class_solargateway
#undef _fs_check_sec_vs_fbd__class_solargateway
#undef _fs_check_sec_vs_fbd__class_solargateway_rev2

#define _fs_check_sec_vs_bi__class_solargateway()        fs_failure(FS_FAILURE_fs_check_sec_vs_bi_1)
#define _fs_check_sec_vs_hw_no_pci__class_solargateway() fs_failure(FS_FAILURE_fs_check_sec_vs_hw_no_pci_1)
#define _fs_check_sec_vs_hw__class_solargateway()        fs_failure(FS_FAILURE_fs_check_sec_vs_hw_1)
#define _fs_check_sec_vs_fbd__class_solargateway()       fs_failure(FS_FAILURE_fs_check_sec_vs_fbd_1)
#define _fs_check_sec_vs_fbd__class_solargateway_rev2()       fs_failure(FS_FAILURE_fs_check_sec_vs_fbd_1)

#endif // #ifdef UBNT_SUPPORT_CLASS_SOLARGATEWAY
