#ifdef UBNT_SUPPORT_CLASS_NVR

__FS_FUNCTION_PREFER_INLINE void _fs_check_nvr_eth0_mac_address_sec_vs_hw(void)                   { __fs_check_sec_array_vs_hw_array(eth0_mac_address,eth0_mac_address,MAC_ADDRESS_SIZE); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_nvr_eth0_mac_address_sec_vs_fbd(void)                  { __fs_check_sec_array_vs_fbd_array(eth0_mac_address,nvr_eth0_mac_address,MAC_ADDRESS_SIZE); }

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_bi__class_nvr(void) {
    // NB: Nothing to do here
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw_no_pci__class_nvr(void) {
    // Nothing to do here
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw__class_nvr(void) {
    _fs_check_nvr_eth0_mac_address_sec_vs_hw();
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_fbd__class_nvr(void) {
    _fs_check_nvr_eth0_mac_address_sec_vs_fbd();
    _fs_check_subsystem_id_sec_vs_fbd();
    _fs_check_subvendor_id_sec_vs_fbd();
}

#else // #ifdef UBNT_SUPPORT_CLASS_NVR

#undef _fs_check_sec_vs_bi__class_nvr
#undef _fs_check_sec_vs_hw_no_pci__class_nvr
#undef _fs_check_sec_vs_hw__class_nvr
#undef _fs_check_sec_vs_fbd__class_nvr

#define _fs_check_sec_vs_bi__class_nvr()        fs_failure(FS_FAILURE_fs_check_sec_vs_bi_1)
#define _fs_check_sec_vs_hw_no_pci__class_nvr() fs_failure(FS_FAILURE_fs_check_sec_vs_hw_no_pci_1)
#define _fs_check_sec_vs_hw__class_nvr()        fs_failure(FS_FAILURE_fs_check_sec_vs_hw_1)
#define _fs_check_sec_vs_fbd__class_nvr()       fs_failure(FS_FAILURE_fs_check_sec_vs_fbd_1)

#endif // #ifdef UBNT_SUPPORT_CLASS_NVR
