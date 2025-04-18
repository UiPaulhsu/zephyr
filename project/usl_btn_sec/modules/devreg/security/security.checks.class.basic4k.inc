#ifdef UBNT_SUPPORT_CLASS_BASIC4K

__FS_FUNCTION_PREFER_INLINE void _fs_check_basic4k_cpu_rev_id_sec_vs_cpu_rev_id_bi(void)         { __fs_check_generic_sec_vs_bi(u_int32_t,basic4k_cpu_rev_id,cpu_rev_id); }

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_bi__class_basic4k(void) {
    if(fs_has_cpu_rev_id_bi()) {
            _fs_check_basic4k_cpu_rev_id_sec_vs_cpu_rev_id_bi( );
    }
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_basic4k_cpu_rev_id_sec_vs_hw(void) {
    __fs_check_generic_sec_vs_hw(u_int32_t,basic4k_cpu_rev_id,cpu_rev_id);
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw_no_pci__class_basic4k(void) {
    _fs_check_basic4k_cpu_rev_id_sec_vs_hw();
      // NB: We do NOT validate eth0/eth1 from the start of flash against hardware address.  If you need this, you have to do it in an architecture-specific way, rather than a class-based way.
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw__class_basic4k(void) {
    // Nothing to do here
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_fbd__class_basic4k(void) {
      // NB: We do NOT validate eth0/eth1 from the start of flash against flash board data, for historical reasons.  Use the MAC from the security area if you need trusted data.
    _fs_check_subsystem_id_sec_vs_fbd();
    _fs_check_subvendor_id_sec_vs_fbd();
}

#else // #ifdef UBNT_SUPPORT_CLASS_BASIC4K

#undef _fs_check_sec_vs_bi__class_basic4k
#undef _fs_check_sec_vs_hw_no_pci__class_basic4k
#undef _fs_check_sec_vs_hw__class_basic4k
#undef _fs_check_sec_vs_fbd__class_basic4k

#define _fs_check_sec_vs_bi__class_basic4k()        fs_failure(FS_FAILURE_fs_check_sec_vs_bi_1)
#define _fs_check_sec_vs_hw_no_pci__class_basic4k() fs_failure(FS_FAILURE_fs_check_sec_vs_hw_no_pci_1)
#define _fs_check_sec_vs_hw__class_basic4k()        fs_failure(FS_FAILURE_fs_check_sec_vs_hw_1)
#define _fs_check_sec_vs_fbd__class_basic4k()       fs_failure(FS_FAILURE_fs_check_sec_vs_fbd_1)

#endif // #ifdef UBNT_SUPPORT_CLASS_BASIC4K
