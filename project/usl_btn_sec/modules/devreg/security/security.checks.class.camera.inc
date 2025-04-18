#ifdef UBNT_SUPPORT_CLASS_CAMERA

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_bi__class_camera(void) {
    // NB: Nothing to do here
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw_no_pci__class_camera(void) {
    _fs_check_camera_eth_mac_rev_id_sec_vs_hw();
    _fs_check_camera_ahb_rev_id_sec_vs_hw();
    _fs_check_camera_gpio_summary_id_sec_vs_hw();
    _fs_check_camera_i2c_controller_rev_id_sec_vs_hw();
    _fs_check_camera_int_controller_summary_id_sec_vs_hw();
    _fs_check_camera_sd_card_reader_rev_id_sec_vs_hw();
    _fs_check_camera_timer_summary_id_sec_vs_hw();
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw__class_camera() {
    // NB: Check with owner
    // _fs_check_camera_eth0_mac_address_sec_vs_hw( );
    // _fs_check_camera_eth1_mac_address_sec_vs_hw( );
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_fbd__class_camera(void) {
    // NB: UNKNOWN can change? - _fs_check_camera_eth0_mac_address_sec_vs_fbd();
    // NB: UNKNOWN can change? - _fs_check_camera_eth1_mac_address_sec_vs_fbd();
    _fs_check_subsystem_id_sec_vs_fbd();
    _fs_check_subvendor_id_sec_vs_fbd();
}

#else // #ifdef UBNT_SUPPORT_CLASS_CAMERA

#undef _fs_check_sec_vs_bi__class_camera
#undef _fs_check_sec_vs_hw_no_pci__class_camera
#undef _fs_check_sec_vs_hw__class_camera
#undef _fs_check_sec_vs_fbd__class_camera

#define _fs_check_sec_vs_bi__class_camera()        fs_failure(FS_FAILURE_fs_check_sec_vs_bi_1)
#define _fs_check_sec_vs_hw_no_pci__class_camera() fs_failure(FS_FAILURE_fs_check_sec_vs_hw_no_pci_1)
#define _fs_check_sec_vs_hw__class_camera()        fs_failure(FS_FAILURE_fs_check_sec_vs_hw_1)
#define _fs_check_sec_vs_fbd__class_camera()       fs_failure(FS_FAILURE_fs_check_sec_vs_fbd_1)

#endif // #ifdef UBNT_SUPPORT_CLASS_CAMERA
