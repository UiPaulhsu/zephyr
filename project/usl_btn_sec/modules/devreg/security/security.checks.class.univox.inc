#ifdef UBNT_SUPPORT_CLASS_UNIVOX

__FS_FUNCTION_PREFER_INLINE void _fs_check_univox_cpu_rev_id_sec_vs_cpu_rev_id_bi(void)         { __fs_check_generic_sec_vs_bi(u_int32_t,univox_cpu_rev_id,cpu_rev_id); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_univox_eth0_mac_address_sec_vs_hw(void)                { __fs_check_sec_array_vs_hw_array(eth0_mac_address,eth0_mac_address,MAC_ADDRESS_SIZE); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_univox_eth0_mac_address_sec_vs_fbd(void)               { __fs_check_sec_array_vs_fbd_array(eth0_mac_address,univox_eth0_mac_address,MAC_ADDRESS_SIZE); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_univox_eth1_mac_address_sec_vs_fbd(void)               { __fs_check_sec_array_vs_fbd_array(eth1_mac_address,univox_eth1_mac_address,MAC_ADDRESS_SIZE); }

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_bi__class_univox(void) {
    if(fs_has_cpu_rev_id_bi()) {
            _fs_check_univox_cpu_rev_id_sec_vs_cpu_rev_id_bi( );
    }
}

#if SECURITY_IS_TARGET_BUILD && SECURITY_ENABLE_SIMULATION && !defined(UBNT_MIPS_BCM4706) && !defined(UBNT_ARM_MT8117)
__FS_FUNCTION_PREFER_INLINE void _fs_check_univox_cpu_rev_id_sec_vs_hw(void) { 
    if (fs_read_univox_cpu_rev_id_sec() == BCM111xx_CPU_REV) {
        __fs_check_generic_sec_vs_hw(u_int32_t, univox_cpu_rev_id, BCM111xx_cpu_rev_id);
    } else if (fs_read_univox_cpu_rev_id_sec() == MT8117_CPU_REV) {
        __fs_check_generic_sec_vs_hw(u_int32_t, univox_cpu_rev_id, MT8117_cpu_rev_id);
    } else {
        fs_failure(FS_FAILURE_fs_check_univox_cpu_rev_id_sec_vs_hw_1);
    }
}
#endif // #if SECURITY_IS_TARGET_BUILD && SECURITY_ENABLE_SIMULATION && !defined(UBNT_MIPS_BCM4706) && !defined(UBNT_ARM_MT8117)

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw_no_pci__class_univox(void) {
    _fs_check_univox_cpu_rev_id_sec_vs_hw();
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw__class_univox() {
    _fs_check_univox_eth0_mac_address_sec_vs_hw();
    // _fs_check_univox_eth1_mac_address_sec_vs_hw();
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_fbd__class_univox(void) {
    _fs_check_univox_eth0_mac_address_sec_vs_fbd();
    _fs_check_univox_eth1_mac_address_sec_vs_fbd();
    _fs_check_subsystem_id_sec_vs_fbd();
    _fs_check_subvendor_id_sec_vs_fbd();
}
#else // #ifdef UBNT_SUPPORT_CLASS_UNIVOX

#undef _fs_check_sec_vs_bi__class_univox
#undef _fs_check_sec_vs_hw_no_pci__class_univox
#undef _fs_check_sec_vs_hw__class_univox
#undef _fs_check_sec_vs_fbd__class_univox

#define _fs_check_sec_vs_bi__class_univox()        fs_failure(FS_FAILURE_fs_check_sec_vs_bi_1)
#define _fs_check_sec_vs_hw_no_pci__class_univox() fs_failure(FS_FAILURE_fs_check_sec_vs_hw_no_pci_1)
#define _fs_check_sec_vs_hw__class_univox()        fs_failure(FS_FAILURE_fs_check_sec_vs_hw_1)
#define _fs_check_sec_vs_fbd__class_univox()       fs_failure(FS_FAILURE_fs_check_sec_vs_fbd_1)

#endif // #ifdef UBNT_SUPPORT_CLASS_UNIVOX
