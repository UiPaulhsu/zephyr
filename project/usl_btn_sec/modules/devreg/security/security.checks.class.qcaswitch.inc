#ifdef UBNT_SUPPORT_CLASS_QCASWITCH

__FS_FUNCTION_PREFER_INLINE void _fs_check_qcaswitch_eth0_mac_address_sec_vs_hw(void)             { __fs_check_sec_array_vs_hw_array(eth0_mac_address,eth0_mac_address,MAC_ADDRESS_SIZE); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_qcaswitch_eth0_mac_address_sec_vs_fbd(void)            { __fs_check_sec_array_vs_fbd_array(eth0_mac_address,qcaswitch_eth0_mac_address,MAC_ADDRESS_SIZE); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_qcaswitch_eth0_mac_address_sec_vs_bi(void)             { __fs_check_sec_array_vs_bi_array(eth0_mac_address,eth0_mac_address,MAC_ADDRESS_SIZE); }

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_bi__class_qcaswitch(void) {
    // NB: Subsystem ID is checked above
    _fs_check_subvendor_id_sec_vs_vendor_id_bi( );
    _fs_check_qcaswitch_eth0_mac_address_sec_vs_bi();
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw_no_pci__class_qcaswitch(void) {
    // Nothing to do here
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw__class_qcaswitch(void) {
    _fs_check_qcaswitch_eth0_mac_address_sec_vs_hw();
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_fbd__class_qcaswitch(void) {
    _fs_check_qcaswitch_eth0_mac_address_sec_vs_fbd();
    _fs_check_subsystem_id_sec_vs_fbd();
    _fs_check_subvendor_id_sec_vs_fbd();
}

#else // #ifdef UBNT_SUPPORT_CLASS_QCASWITCH

#undef _fs_check_sec_vs_bi__class_qcaswitch
#undef _fs_check_sec_vs_hw_no_pci__class_qcaswitch
#undef _fs_check_sec_vs_hw__class_qcaswitch
#undef _fs_check_sec_vs_fbd__class_qcaswitch

#define _fs_check_sec_vs_bi__class_qcaswitch()        fs_failure(FS_FAILURE_fs_check_sec_vs_bi_1)
#define _fs_check_sec_vs_hw_no_pci__class_qcaswitch() fs_failure(FS_FAILURE_fs_check_sec_vs_hw_no_pci_1)
#define _fs_check_sec_vs_hw__class_qcaswitch()        fs_failure(FS_FAILURE_fs_check_sec_vs_hw_1)
#define _fs_check_sec_vs_fbd__class_qcaswitch()       fs_failure(FS_FAILURE_fs_check_sec_vs_fbd_1)

#endif // #ifdef UBNT_SUPPORT_CLASS_QCASWITCH
