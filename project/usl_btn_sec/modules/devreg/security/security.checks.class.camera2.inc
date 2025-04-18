#ifdef UBNT_SUPPORT_CLASS_CAMERA2

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_bi__class_camera2(void) {
    // NB: Nothing to do here
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw_no_pci__class_camera2(void) {
    _fs_check_camera2_ssi_ident_id_sec_vs_hw();
    _fs_check_camera2_ssi_version_id_sec_vs_hw();
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw__class_camera2(void) {
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_fbd__class_camera2(void) {
    // NB: UNKNOWN can change? - _fs_check_camera2_eth0_mac_address_sec_vs_fbd();
    // NB: UNKNOWN can change? - _fs_check_camera2_eth1_mac_address_sec_vs_fbd();
    _fs_check_subsystem_id_sec_vs_fbd();
    _fs_check_subvendor_id_sec_vs_fbd();
}

#else // #ifdef UBNT_SUPPORT_CLASS_CAMERA2

#undef _fs_check_sec_vs_bi__class_camera2
#undef _fs_check_sec_vs_hw_no_pci__class_camera2
#undef _fs_check_sec_vs_hw__class_camera2
#undef _fs_check_sec_vs_fbd__class_camera2

#define _fs_check_sec_vs_bi__class_camera2()        fs_failure(FS_FAILURE_fs_check_sec_vs_bi_1)
#define _fs_check_sec_vs_hw_no_pci__class_camera2() fs_failure(FS_FAILURE_fs_check_sec_vs_hw_no_pci_1)
#define _fs_check_sec_vs_hw__class_camera2()        fs_failure(FS_FAILURE_fs_check_sec_vs_hw_1)
#define _fs_check_sec_vs_fbd__class_camera2()       fs_failure(FS_FAILURE_fs_check_sec_vs_fbd_1)

#endif // #ifdef UBNT_SUPPORT_CLASS_CAMERA2
