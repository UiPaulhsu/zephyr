#ifdef UBNT_SUPPORT_CLASS_BASIC

__FS_FUNCTION_PREFER_INLINE void _fs_check_basic_cpu_rev_id_sec_vs_cpu_rev_id_bi(void)         { __fs_check_generic_sec_vs_bi(u_int32_t,basic_cpu_rev_id,cpu_rev_id); }

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_bi__class_basic(void) {
    if(fs_has_cpu_rev_id_bi()) {
            _fs_check_basic_cpu_rev_id_sec_vs_cpu_rev_id_bi( );
    }
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_basic_cpu_rev_id_sec_vs_hw(void) {
    __fs_check_generic_sec_vs_hw(u_int32_t,basic_cpu_rev_id,cpu_rev_id);
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw_no_pci__class_basic(void) {
    _fs_check_basic_cpu_rev_id_sec_vs_hw();
    // NB: We are not validating that eth0 and eth1 MAC addresses haven't changed from security data in order to avoid breaking products where MAC cloning is supported.
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw__class_basic(void) {
    // Nothing to do here
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_fbd__class_basic(void) {
    // NB: We are not validating that eth0 and eth1 MAC addresses haven't changed from security data in order to avoid breaking products where MAC cloning is supported.
    _fs_check_subsystem_id_sec_vs_fbd();
    _fs_check_subvendor_id_sec_vs_fbd();
}

#else // #ifdef UBNT_SUPPORT_CLASS_BASIC

#undef _fs_check_sec_vs_bi__class_basic
#undef _fs_check_sec_vs_hw_no_pci__class_basic
#undef _fs_check_sec_vs_hw__class_basic
#undef _fs_check_sec_vs_fbd__class_basic

#define _fs_check_sec_vs_bi__class_basic()        fs_failure(FS_FAILURE_fs_check_sec_vs_bi_1)
#define _fs_check_sec_vs_hw_no_pci__class_basic() fs_failure(FS_FAILURE_fs_check_sec_vs_hw_no_pci_1)
#define _fs_check_sec_vs_hw__class_basic()        fs_failure(FS_FAILURE_fs_check_sec_vs_hw_1)
#define _fs_check_sec_vs_fbd__class_basic()       fs_failure(FS_FAILURE_fs_check_sec_vs_fbd_1)

#endif // #ifdef UBNT_SUPPORT_CLASS_BASIC
