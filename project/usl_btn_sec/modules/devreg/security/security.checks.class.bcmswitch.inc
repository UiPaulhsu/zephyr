#ifdef UBNT_SUPPORT_CLASS_BCMSWITCH

__FS_FUNCTION_PREFER_INLINE void _fs_check_bcmswitch_vpd_sec_vs_fbd(void) {
    __FS_LOCAL_STATIC_OPTION u_int8_t* fsv_t1;
    __FS_LOCAL_STATIC_OPTION u_int8_t* fsv_t2;

    fsv_t1 = (u_int8_t*)fs_zalloc(BCMSWITCH_VPD_SIZE);
    fsv_t2 = (u_int8_t*)fs_zalloc(BCMSWITCH_VPD_SIZE);
    fs_read_bcmswitch_vpd_sec(fsv_t1,BCMSWITCH_VPD_SIZE);
    fs_read_bcmswitch_vpd_fbd(fsv_t2,BCMSWITCH_VPD_SIZE);
    if(memcmp(fsv_t1, fsv_t2, BCMSWITCH_VPD_SIZE) != 0) {
        fs_safe_shred_and_free(&fsv_t1, BCMSWITCH_VPD_SIZE);
        fs_safe_shred_and_free(&fsv_t2, BCMSWITCH_VPD_SIZE);
        fs_failure(FS_FAILURE_fs_check_bcmswitch_vpd_sec_vs_fbd_1);
    }
    fs_safe_shred_and_free(&fsv_t1, BCMSWITCH_VPD_SIZE);
    fs_safe_shred_and_free(&fsv_t2, BCMSWITCH_VPD_SIZE);
}
__FS_FUNCTION_PREFER_INLINE void _fs_check_bcmswitch_eth0_mac_address_sec_vs_hw(void)             { __fs_check_sec_array_vs_hw_array(eth0_mac_address,eth0_mac_address,MAC_ADDRESS_SIZE); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_bcmswitch_eth0_mac_address_sec_vs_fbd(void)            { __fs_check_sec_array_vs_fbd_array(eth0_mac_address,bcmswitch_eth0_mac_address,MAC_ADDRESS_SIZE); }

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_bi__class_bcmswitch(void) {
    // NB: No board.info on this platform
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw_no_pci__class_bcmswitch(void) {
    _fs_check_bcmswitch_cpu_rev_id_sec_vs_hw();
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw__class_bcmswitch(void) {
    _fs_check_bcmswitch_eth0_mac_address_sec_vs_hw();
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_fbd__class_bcmswitch(void) {
    _fs_check_bcmswitch_eth0_mac_address_sec_vs_fbd();
    _fs_check_subsystem_id_sec_vs_fbd();
    _fs_check_subvendor_id_sec_vs_fbd();
    _fs_check_bcmswitch_vpd_sec_vs_fbd();
}

#else // #ifdef UBNT_SUPPORT_CLASS_BCMSWITCH

#undef _fs_check_sec_vs_bi__class_bcmswitch
#undef _fs_check_sec_vs_hw_no_pci__class_bcmswitch
#undef _fs_check_sec_vs_hw__class_bcmswitch
#undef _fs_check_sec_vs_fbd__class_bcmswitch

#define _fs_check_sec_vs_bi__class_bcmswitch()        fs_failure(FS_FAILURE_fs_check_sec_vs_bi_1)
#define _fs_check_sec_vs_hw_no_pci__class_bcmswitch() fs_failure(FS_FAILURE_fs_check_sec_vs_hw_no_pci_1)
#define _fs_check_sec_vs_hw__class_bcmswitch()        fs_failure(FS_FAILURE_fs_check_sec_vs_hw_1)
#define _fs_check_sec_vs_fbd__class_bcmswitch()       fs_failure(FS_FAILURE_fs_check_sec_vs_fbd_1)

#endif // #ifdef UBNT_SUPPORT_CLASS_BCMSWITCH
