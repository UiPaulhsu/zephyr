#ifdef UBNT_SUPPORT_CLASS_SWITCH

__FS_FUNCTION_PREFER_INLINE void _fs_check_switch_cpu_rev_id_sec_vs_hw(void)                         { __fs_check_generic_sec_vs_hw(u_int32_t,switch_cpu_rev_id,cpu_rev_id); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_switch_cpu_rev_id_sec_vs_cpu_rev_id_bi(void)         { __fs_check_generic_sec_vs_bi(u_int32_t,switch_cpu_rev_id,cpu_rev_id); }

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_bi__class_switch(void) {
    if(fs_has_cpu_rev_id_bi()) {
            _fs_check_switch_cpu_rev_id_sec_vs_cpu_rev_id_bi( );
    }
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw_no_pci__class_switch(void) {
    _fs_check_switch_cpu_rev_id_sec_vs_hw();
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw__class_switch(void) {
    // Nothing to do here
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_fbd__class_switch(void) {
    // NB: UNKNOWN can change? - _fs_check_switch_eth0_mac_address_sec_vs_fbd();
    // NB: UNKNOWN can change? - _fs_check_switch_eth1_mac_address_sec_vs_fbd();
    _fs_check_subsystem_id_sec_vs_fbd();
    _fs_check_subvendor_id_sec_vs_fbd();
}

#else // #ifdef UBNT_SUPPORT_CLASS_SWITCH

#undef _fs_check_sec_vs_bi__class_switch
#undef _fs_check_sec_vs_hw_no_pci__class_switch
#undef _fs_check_sec_vs_hw__class_switch
#undef _fs_check_sec_vs_fbd__class_switch

#define _fs_check_sec_vs_bi__class_switch()        fs_failure(FS_FAILURE_fs_check_sec_vs_bi_1)
#define _fs_check_sec_vs_hw_no_pci__class_switch() fs_failure(FS_FAILURE_fs_check_sec_vs_hw_no_pci_1)
#define _fs_check_sec_vs_hw__class_switch()        fs_failure(FS_FAILURE_fs_check_sec_vs_hw_1)
#define _fs_check_sec_vs_fbd__class_switch()       fs_failure(FS_FAILURE_fs_check_sec_vs_fbd_1)

#endif // #ifdef UBNT_SUPPORT_CLASS_SWITCH
