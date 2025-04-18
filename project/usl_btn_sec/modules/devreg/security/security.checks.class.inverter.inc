#ifdef UBNT_SUPPORT_CLASS_INVERTER


__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw_no_pci__class_inverter(void) {
    // NB: Does not apply to inverters
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_bi__class_inverter(void) {
    // NB: Does not apply to inverters
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw__class_inverter(void) {
    // NB: See _fs_check_sec_vs_hw_no_pci__class_inverter
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_fbd__class_inverter(void) {
    _fs_check_subsystem_id_sec_vs_fbd();
    _fs_check_subvendor_id_sec_vs_fbd();
    _fs_check_pcba_sec_vs_fbd();
}

#else // #ifdef UBNT_SUPPORT_CLASS_INVERTER

#undef _fs_check_sec_vs_bi__class_inverter
#undef _fs_check_sec_vs_hw_no_pci__class_inverter
#undef _fs_check_sec_vs_hw__class_inverter
#undef _fs_check_sec_vs_fbd__class_inverter

#define _fs_check_sec_vs_bi__class_inverter()        fs_failure(FS_FAILURE_fs_check_sec_vs_bi_1)
#define _fs_check_sec_vs_hw_no_pci__class_inverter() fs_failure(FS_FAILURE_fs_check_sec_vs_hw_no_pci_1)
#define _fs_check_sec_vs_hw__class_inverter()        fs_failure(FS_FAILURE_fs_check_sec_vs_hw_1)
#define _fs_check_sec_vs_fbd__class_inverter()       fs_failure(FS_FAILURE_fs_check_sec_vs_fbd_1)

#endif // #ifdef UBNT_SUPPORT_CLASS_INVERTER
