#ifdef UBNT_SUPPORT_CLASS_WIFI

#define __fs_begin_if_wifi_radio_exists(__radionum) \
        if (fs_read_wifi_radio##__radionum##_mac_rev_id_sec() != 0xffffffff) { \

#define __fs_end_if_wifi_radio_exists(__radionum) \
        }

#define __fs_check_generic_sec_vs_bi_if_wifi_radio_exists(__type, __name_sec,__name_bi,__radionum) do { \
                __fs_begin_if_wifi_radio_exists(__radionum) \
                __fs_check_generic_sec_vs_bi(__type,__name_sec, __name_bi ); \
                __fs_end_if_wifi_radio_exists( __radionum) \
        } while(0)

#define __fs_check_generic_sec_vs_hw_if_wifi_radio_exists(__type, __name_sec,__name_hw,__radionum) do { \
        __fs_begin_if_wifi_radio_exists(__radionum) \
        __fs_check_generic_sec_vs_hw(__type,__name_sec,__name_hw); \
        __fs_end_if_wifi_radio_exists( __radionum) \
    } while(0)

#define __fs_check_sec_array_vs_hw_array_if_wifi_radio_exists(__name_sec,__name_hw,__len,__radionum) do { \
                u_int8_t __fs_check_generic_sec[__len]; \
                u_int8_t __fs_check_generic_hw[__len]; \
                __fs_begin_if_wifi_radio_exists(__radionum) \
                fs_read_ ## __name_sec ## _sec( __fs_check_generic_sec, sizeof __fs_check_generic_sec ); \
                fs_read_ ## __name_hw ## _hw( __fs_check_generic_hw, sizeof __fs_check_generic_hw ); \
                if(memcmp( &__fs_check_generic_sec, &__fs_check_generic_hw, __len) != 0 \
                && memcmp( &__fs_check_generic_hw, fsv_mac_all_ones, __len) != 0) { \
                                fs_failure(FS_FAILURE_fs_check_ ## __name_sec ## _sec_vs_ ## __name_hw ## _hw__if_radio_ ## __radionum ## _exists_1); \
                } \
        __fs_end_if_wifi_radio_exists( __radionum) \
    } while(0)

#define __fs_check_sec_array_vs_bi_array_if_wifi_radio_exists(__name_sec,__name_bi,__len,__radionum) do { \
        u_int8_t __fs_check_generic_sec[__len]; \
        u_int8_t __fs_check_generic_bi[__len]; \
        __fs_begin_if_wifi_radio_exists(__radionum) \
        fs_read_ ## __name_sec ## _sec( __fs_check_generic_sec, sizeof __fs_check_generic_sec ); \
        fs_read_ ## __name_bi ## _bi( __fs_check_generic_bi, sizeof __fs_check_generic_bi ); \
        if(memcmp( &__fs_check_generic_sec,  &__fs_check_generic_bi, __len) != 0) { \
                fs_failure(FS_FAILURE_fs_check_ ## __name_sec ## _sec_vs_ ## __name_bi ## _bi__if_radio_ ## __radionum ## _exists_1); \
        } \
        __fs_end_if_wifi_radio_exists(__radionum) \
    } while(0)

__FS_FUNCTION_PREFER_INLINE void _fs_check_wifi_cpu_rev_id_sec_vs_cpu_rev_id_bi(void)                { __fs_check_generic_sec_vs_bi(u_int32_t,wifi_cpu_rev_id,cpu_rev_id); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_subsystem_id_sec_vs_wifi_radio1_subsystem_id_bi(void)     { __fs_check_generic_sec_vs_bi_if_wifi_radio_exists(u_int16_t,subsystem_id,wifi_radio1_subsystem_id,1); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_subsystem_id_sec_vs_wifi_radio2_subsystem_id_bi(void)     { __fs_check_generic_sec_vs_bi_if_wifi_radio_exists(u_int16_t,subsystem_id,wifi_radio2_subsystem_id,2); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_subvendor_id_sec_vs_wifi_radio1_subvendor_id_bi(void)     { __fs_check_generic_sec_vs_bi_if_wifi_radio_exists(u_int16_t,subvendor_id,wifi_radio1_subvendor_id,1); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_subvendor_id_sec_vs_wifi_radio2_subvendor_id_bi(void)     { __fs_check_generic_sec_vs_bi_if_wifi_radio_exists(u_int16_t,subvendor_id,wifi_radio2_subvendor_id,2); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_wifi_radio1_rev_id_sec_vs_hw(void)                        { __fs_check_generic_sec_vs_hw_if_wifi_radio_exists(u_int32_t,wifi_radio1_mac_rev_id,wifi_radio1_mac_rev_id,1); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_wifi_radio2_rev_id_sec_vs_hw(void)                        { __fs_check_generic_sec_vs_hw_if_wifi_radio_exists(u_int32_t,wifi_radio2_mac_rev_id,wifi_radio2_mac_rev_id,2); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_wifi_cpu_rev_id_sec_vs_hw(void)                           { __fs_check_generic_sec_vs_hw(u_int32_t,wifi_cpu_rev_id,cpu_rev_id); }

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_bi__class_wifi(void) {
    _fs_check_subsystem_id_sec_vs_wifi_radio1_subsystem_id_bi( );
    _fs_check_subsystem_id_sec_vs_wifi_radio2_subsystem_id_bi( );
    _fs_check_subvendor_id_sec_vs_wifi_radio1_subvendor_id_bi( );
    _fs_check_subvendor_id_sec_vs_wifi_radio2_subvendor_id_bi( );
    if(fs_has_cpu_rev_id_bi()) {
            _fs_check_wifi_cpu_rev_id_sec_vs_cpu_rev_id_bi( );
    }
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_bi__class_wifi_radio(void) {
    fs_failure(FS_FAILURE_fs_check_sec_vs_bi_1);
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_bi__class_wifi_digital(void) {
    fs_failure(FS_FAILURE_fs_check_sec_vs_bi_1);
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw_no_pci__class_wifi(void) {
    _fs_check_wifi_cpu_rev_id_sec_vs_hw();
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw_no_pci__class_wifi_radio(void) {
    fs_failure(FS_FAILURE_fs_check_sec_vs_hw_no_pci_1);
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw_no_pci__class_wifi_digital(void) {
    fs_failure(FS_FAILURE_fs_check_sec_vs_hw_no_pci_1);
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw__class_wifi_digital(void) {
    fs_failure(FS_FAILURE_fs_check_sec_vs_hw_1);
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw__class_wifi(void) {
    _fs_check_wifi_radio1_rev_id_sec_vs_hw();
    _fs_check_wifi_radio2_rev_id_sec_vs_hw();
    // NB: Allow MAC cloning - _fs_check_wifi_radio1_mac_address_sec_vs_hw( );
    // NB: Allow MAC cloning - _fs_check_wifi_radio2_mac_address_sec_vs_hw( );
    // NB: Allow MAC cloning - _fs_check_wifi_eth0_mac_address_sec_vs_hw( );
    // NB: Allow MAC cloning - _fs_check_wifi_eth1_mac_address_sec_vs_hw( );
}
__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw__class_wifi_radio(void) {
    fs_failure(FS_FAILURE_fs_check_sec_vs_hw_1);
}
__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_fbd__class_wifi_digital(void) {
    fs_failure(FS_FAILURE_fs_check_sec_vs_fbd_1);
}
__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_fbd__class_wifi(void) {
    // NB: eth0 and eth1 MAC are allowed to be changed!
    // NB: board data should NOT have ssid and svid for some radios!
    // NB: Need to check with owners before enabling these:
    //if(fs_has_ssid_fbd() || fs_has_svid_fbd()) {
    //        _fs_check_subsystem_id_sec_vs_fbd();
    //        _fs_check_subvendor_id_sec_vs_fbd();
    //}
}
__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_fbd__class_wifi_radio(void) {
    fs_failure(FS_FAILURE_fs_check_sec_vs_fbd_1);
}

#else // #ifdef UBNT_SUPPORT_CLASS_WIFI

#undef _fs_check_sec_vs_bi__class_wifi
#undef _fs_check_sec_vs_hw_no_pci__class_wifi
#undef _fs_check_sec_vs_hw__class_wifi
#undef _fs_check_sec_vs_fbd__class_wifi

#define _fs_check_sec_vs_bi__class_wifi()                      fs_failure(FS_FAILURE_fs_check_sec_vs_bi_1)
#define _fs_check_sec_vs_hw_no_pci__class_wifi()               fs_failure(FS_FAILURE_fs_check_sec_vs_hw_no_pci_1)
#define _fs_check_sec_vs_hw__class_wifi()                      fs_failure(FS_FAILURE_fs_check_sec_vs_hw_1)
#define _fs_check_sec_vs_fbd__class_wifi()                     fs_failure(FS_FAILURE_fs_check_sec_vs_fbd_1)

#undef _fs_check_sec_vs_bi__class_wifi_digital
#undef _fs_check_sec_vs_hw_no_pci__class_wifi_digital
#undef _fs_check_sec_vs_hw__class_wifi_digital
#undef _fs_check_sec_vs_fbd__class_wifi_digital

#define _fs_check_sec_vs_bi__class_wifi_digital()              fs_failure(FS_FAILURE_fs_check_sec_vs_bi_1)
#define _fs_check_sec_vs_hw_no_pci__class_wifi_digital()       fs_failure(FS_FAILURE_fs_check_sec_vs_hw_no_pci_1)
#define _fs_check_sec_vs_hw__class_wifi_digital()              fs_failure(FS_FAILURE_fs_check_sec_vs_hw_1)
#define _fs_check_sec_vs_fbd__class_wifi_digital()             fs_failure(FS_FAILURE_fs_check_sec_vs_fbd_1)

#undef _fs_check_sec_vs_bi__class_wifi_radio
#undef _fs_check_sec_vs_hw_no_pci__class_wifi_radio
#undef _fs_check_sec_vs_hw__class_wifi_radio
#undef _fs_check_sec_vs_fbd__class_wifi_radio

#define _fs_check_sec_vs_bi__class_wifi_radio()                fs_failure(FS_FAILURE_fs_check_sec_vs_bi_1)
#define _fs_check_sec_vs_hw_no_pci__class_wifi_radio()         fs_failure(FS_FAILURE_fs_check_sec_vs_hw_no_pci_1)
#define _fs_check_sec_vs_hw__class_wifi_radio()                fs_failure(FS_FAILURE_fs_check_sec_vs_hw_1)
#define _fs_check_sec_vs_fbd__class_wifi_radio()               fs_failure(FS_FAILURE_fs_check_sec_vs_fbd_1)

#endif // #ifdef UBNT_SUPPORT_CLASS_WIFI
