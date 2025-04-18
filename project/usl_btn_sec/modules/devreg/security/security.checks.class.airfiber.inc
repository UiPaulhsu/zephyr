#ifdef UBNT_SUPPORT_CLASS_AIRFIBER

__FS_FUNCTION_PREFER_INLINE void _fs_check_airfiber_board_rev_id_sec_vs_fbd(void) {
        if(fs_read_airfiber_old_board_rev_id_sec() != fs_read_airfiber_board_rev_id_fbd()) {
                fs_failure(FS_FAILURE_fs_check_airfiber_board_rev_id_sec_vs_airfiber_board_rev_id_fbd_1);
        }
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_airfiber_cpu_rev_id_sec_vs_cpu_rev_id_bi(void)       { __fs_check_generic_sec_vs_bi(u_int32_t,airfiber_cpu_rev_id,cpu_rev_id); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_airfiber_eth0_mac_address_sec_vs_hw(void)              { __fs_check_sec_array_vs_hw_array(eth0_mac_address,eth0_mac_address,MAC_ADDRESS_SIZE); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_airfiber_eth0_mac_address_sec_vs_fbd(void)             { __fs_check_sec_array_vs_fbd_array(eth0_mac_address,airfiber_eth0_mac_address,MAC_ADDRESS_SIZE); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_airfiber_air0_mac_address_sec_vs_hw(void)              { __fs_check_sec_array_vs_hw_array(airfiber_air0_mac_address,airfiber_air0_mac_address,MAC_ADDRESS_SIZE); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_airfiber_air0_mac_address_sec_vs_fbd(void)             { __fs_check_sec_array_vs_fbd_array(airfiber_air0_mac_address,airfiber_air0_mac_address,MAC_ADDRESS_SIZE); }

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_bi__class_airfiber(void) {
    if(fs_has_cpu_rev_id_bi()) {
        _fs_check_airfiber_cpu_rev_id_sec_vs_cpu_rev_id_bi( );
    }
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw_no_pci__class_airfiber(void) {
    _fs_check_airfiber_cpu_rev_id_sec_vs_hw();
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw__class_airfiber(void) {
    _fs_check_airfiber_eth0_mac_address_sec_vs_hw();
    _fs_check_airfiber_air0_mac_address_sec_vs_hw();
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_fbd__class_airfiber(void) {
    _fs_check_airfiber_eth0_mac_address_sec_vs_fbd();
    _fs_check_airfiber_air0_mac_address_sec_vs_fbd();
    _fs_check_subsystem_id_sec_vs_fbd();
    _fs_check_subvendor_id_sec_vs_fbd();
    _fs_check_airfiber_board_rev_id_sec_vs_fbd();
}

#else // #ifdef UBNT_SUPPORT_CLASS_AIRFIBER

#undef _fs_check_sec_vs_bi__class_airfiber
#undef _fs_check_sec_vs_hw_no_pci__class_airfiber
#undef _fs_check_sec_vs_hw__class_airfiber
#undef _fs_check_sec_vs_fbd__class_airfiber

#define _fs_check_sec_vs_bi__class_airfiber()        fs_failure(FS_FAILURE_fs_check_sec_vs_bi_1)
#define _fs_check_sec_vs_hw_no_pci__class_airfiber() fs_failure(FS_FAILURE_fs_check_sec_vs_hw_no_pci_1)
#define _fs_check_sec_vs_hw__class_airfiber()        fs_failure(FS_FAILURE_fs_check_sec_vs_hw_1)
#define _fs_check_sec_vs_fbd__class_airfiber()       fs_failure(FS_FAILURE_fs_check_sec_vs_fbd_1)

#endif // #ifdef UBNT_SUPPORT_CLASS_AIRFIBER
