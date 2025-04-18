#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_MIPS_BCM4706) || SECURITY_ENABLE_SIMULATION)

#define __fs_begin_if_bcmwifi_wifi_radio_exists(__radionum) \
        if (fs_read_bcmwifi_wifi_radio##__radionum##_id_sec() != 0xffffffff) { \

#define __fs_end_if_bcmwifi_wifi_radio_exists(__radionum) \
        }

#define __fs_check_generic_sec_vs_hw_if_bcmwifi_wifi_radio_exists(__type, __name_sec,__name_hw,__radionum) do { \
        __fs_begin_if_bcmwifi_wifi_radio_exists(__radionum) \
        __fs_check_generic_sec_vs_hw(__type,__name_sec,__name_hw); \
        __fs_end_if_bcmwifi_wifi_radio_exists( __radionum) \
    } while(0)

#define __fs_check_generic_sec_vs_bi_if_bcmwifi_wifi_radio_exists(__type, __name_sec,__name_bi,__radionum) do { \
                __fs_begin_if_bcmwifi_wifi_radio_exists(__radionum) \
                __fs_check_generic_sec_vs_bi(__type,__name_sec, __name_bi ); \
                __fs_end_if_bcmwifi_wifi_radio_exists( __radionum) \
        } while(0)

#define __fs_check_sec_array_vs_hw_array_if_bcmwifi_wifi_radio_exists(__name_sec,__name_hw,__len,__radionum) do { \
                u_int8_t __fs_check_generic_sec[__len]; \
                u_int8_t __fs_check_generic_hw[__len]; \
                __fs_begin_if_bcmwifi_wifi_radio_exists(__radionum) \
                fs_read_ ## __name_sec ## _sec( __fs_check_generic_sec, sizeof __fs_check_generic_sec ); \
                fs_read_ ## __name_hw ## _hw( __fs_check_generic_hw, sizeof __fs_check_generic_hw ); \
                if(memcmp( &__fs_check_generic_sec, &__fs_check_generic_hw, __len) != 0 \
                && memcmp( &__fs_check_generic_hw, fsv_mac_all_ones, __len) != 0) { \
                        fs_failure(FS_FAILURE_fs_check_ ## __name_sec ## _sec_vs_ ## __name_hw ## _hw__if_radio_ ## __radionum ## _exists_1); \
                } \
        __fs_end_if_bcmwifi_wifi_radio_exists( __radionum) \
    } while(0)

#define __fs_check_sec_array_vs_bi_array_if_bcmwifi_wifi_radio_exists(__name_sec,__name_bi,__len,__radionum) do { \
        u_int8_t __fs_check_generic_sec[__len]; \
        u_int8_t __fs_check_generic_bi[__len]; \
        __fs_begin_if_bcmwifi_wifi_radio_exists(__radionum) \
        fs_read_ ## __name_sec ## _sec( __fs_check_generic_sec, sizeof __fs_check_generic_sec ); \
        fs_read_ ## __name_bi ## _bi( __fs_check_generic_bi, sizeof __fs_check_generic_bi ); \
        if(memcmp( &__fs_check_generic_sec,  &__fs_check_generic_bi, __len) != 0) { \
                fs_failure(FS_FAILURE_fs_check_ ## __name_sec ## _sec_vs_ ## __name_bi ## _bi__if_radio_ ## __radionum ## _exists_1); \
        } \
        __fs_end_if_bcmwifi_wifi_radio_exists(__radionum) \
    } while(0)

__FS_FUNCTION_PREFER_INLINE void _fs_check_bcmwifi_cpu_rev_id_sec_vs_hw(void)                     { __fs_check_generic_sec_vs_hw(u_int32_t,bcmwifi_cpu_rev_id,BCM4706_cpu_rev_id); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_bcmwifi_wifi_radio1_mac_address_sec_vs_hw(void)             { __fs_check_sec_array_vs_hw_array_if_bcmwifi_wifi_radio_exists(bcmwifi_wifi_radio1_mac_address,BCM4706_wifi_radio1_mac_address,MAC_ADDRESS_SIZE,1); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_bcmwifi_wifi_radio2_mac_address_sec_vs_hw(void)             { __fs_check_sec_array_vs_hw_array_if_bcmwifi_wifi_radio_exists(bcmwifi_wifi_radio2_mac_address,BCM4706_wifi_radio2_mac_address,MAC_ADDRESS_SIZE,2); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_bcmwifi_wifi_radio1_id_sec_vs_hw(void)                      { __fs_check_generic_sec_vs_hw(u_int32_t,bcmwifi_wifi_radio1_id,BCM4706_wifi_radio1_id); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_bcmwifi_wifi_radio2_id_sec_vs_hw(void)                      { __fs_check_generic_sec_vs_hw(u_int32_t,bcmwifi_wifi_radio2_id,BCM4706_wifi_radio2_id); }

#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_MIPS_BCM4706) || SECURITY_ENABLE_SIMULATION)

