#if SECURITY_IS_TARGET_BUILD

#define GENERATE_SIMPLE_GET_CONFIG_SECTION_OFFSET_FUNCTION_CASE_STATEMENTS(__SECTION__) \
        CASE_DATA_FORMAT_WIFI_FLASH   ( fsv_t1 = __FLASH_SECTION_OFFSET(wifi,__SECTION__);          ) \
        CASE_DATA_FORMAT_CAMERA       ( fsv_t1 = __FLASH_SECTION_OFFSET(camera,__SECTION__);        ) \
        CASE_DATA_FORMAT_SWITCH       ( fsv_t1 = __FLASH_SECTION_OFFSET(switch,__SECTION__);        ) \
        CASE_DATA_FORMAT_BASIC        ( fsv_t1 = __FLASH_SECTION_OFFSET(basic,__SECTION__);         ) \
        CASE_DATA_FORMAT_BASIC4K      ( fsv_t1 = __FLASH_SECTION_OFFSET(basic4k,__SECTION__);       ) \
        CASE_DATA_FORMAT_ROUTER       ( fsv_t1 = __FLASH_SECTION_OFFSET(router,__SECTION__);        ) \
        CASE_DATA_FORMAT_SOLARGATEWAY ( fsv_t1 = __FLASH_SECTION_OFFSET(solargateway,__SECTION__);  ) \
        CASE_DATA_FORMAT_AIRFIBER     ( fsv_t1 = __FLASH_SECTION_OFFSET(airfiber,__SECTION__);      ) \
        CASE_DATA_FORMAT_UNIVOX       ( fsv_t1 = __FLASH_SECTION_OFFSET(univox,__SECTION__);        ) \
        CASE_DATA_FORMAT_CAMERA2      ( fsv_t1 = __FLASH_SECTION_OFFSET(camera2,__SECTION__);       ) \
        CASE_DATA_FORMAT_BCMWIFI      ( fsv_t1 = __FLASH_SECTION_OFFSET(bcmwifi,__SECTION__);       ) \
        CASE_DATA_FORMAT_QCASWITCH    ( fsv_t1 = __FLASH_SECTION_OFFSET(qcaswitch,__SECTION__);     ) \
        CASE_DATA_FORMAT_BCMSWITCH    ( fsv_t1 = __FLASH_SECTION_OFFSET(bcmswitch,__SECTION__);     ) \
        CASE_DATA_FORMAT_CLOUDKEY     ( fsv_t1 = __FLASH_SECTION_OFFSET(cloudkey,__SECTION__);      ) \
        CASE_DATA_FORMAT_INVERTER     ( fsv_t1 = __FLASH_SECTION_OFFSET(inverter,__SECTION__);      ) \
        CASE_DATA_FORMAT_NVR          ( fsv_t1 = __FLASH_SECTION_OFFSET(nvr,__SECTION__);           )

#define GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_CASE_STATEMENTS_CLASS_SPECIFIC(__SEC_FIELD__) \
        CASE_DATA_FORMAT_WIFI_FLASH   ( fsv_t1 = __FLASH_CLASS_SPECIFIC_SEC_OFFSET(wifi,__SEC_FIELD__);          ) \
        CASE_DATA_FORMAT_CAMERA       ( fsv_t1 = __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera,__SEC_FIELD__);        ) \
        CASE_DATA_FORMAT_SWITCH       ( fsv_t1 = __FLASH_CLASS_SPECIFIC_SEC_OFFSET(switch,__SEC_FIELD__);        ) \
        CASE_DATA_FORMAT_BASIC        ( fsv_t1 = __FLASH_CLASS_SPECIFIC_SEC_OFFSET(basic,__SEC_FIELD__);         ) \
        CASE_DATA_FORMAT_BASIC4K      ( fsv_t1 = __FLASH_CLASS_SPECIFIC_SEC_OFFSET(basic4k,__SEC_FIELD__);       ) \
        CASE_DATA_FORMAT_ROUTER       ( fsv_t1 = __FLASH_CLASS_SPECIFIC_SEC_OFFSET(router,__SEC_FIELD__);        ) \
        CASE_DATA_FORMAT_SOLARGATEWAY ( fsv_t1 = __FLASH_CLASS_SPECIFIC_SEC_OFFSET(solargateway,__SEC_FIELD__);  ) \
        CASE_DATA_FORMAT_AIRFIBER     ( fsv_t1 = __FLASH_CLASS_SPECIFIC_SEC_OFFSET(airfiber,__SEC_FIELD__);      ) \
        CASE_DATA_FORMAT_UNIVOX       ( fsv_t1 = __FLASH_CLASS_SPECIFIC_SEC_OFFSET(univox,__SEC_FIELD__);        ) \
        CASE_DATA_FORMAT_CAMERA2      ( fsv_t1 = __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera2,__SEC_FIELD__);       ) \
        CASE_DATA_FORMAT_BCMWIFI      ( fsv_t1 = __FLASH_CLASS_SPECIFIC_SEC_OFFSET(bcmwifi,__SEC_FIELD__);       ) \
        CASE_DATA_FORMAT_QCASWITCH    ( fsv_t1 = __FLASH_CLASS_SPECIFIC_SEC_OFFSET(qcaswitch,__SEC_FIELD__);     ) \
        CASE_DATA_FORMAT_BCMSWITCH    ( fsv_t1 = __FLASH_CLASS_SPECIFIC_SEC_OFFSET(bcmswitch,__SEC_FIELD__);     ) \
        CASE_DATA_FORMAT_CLOUDKEY     ( fsv_t1 = __FLASH_CLASS_SPECIFIC_SEC_OFFSET(cloudkey,__SEC_FIELD__);      ) \
        CASE_DATA_FORMAT_INVERTER     ( fsv_t1 = __FLASH_CLASS_SPECIFIC_SEC_OFFSET(inverter,__SEC_FIELD__);      ) \
        CASE_DATA_FORMAT_NVR          ( fsv_t1 = __FLASH_CLASS_SPECIFIC_SEC_OFFSET(nvr,__SEC_FIELD__);           )

#define GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_CLASS_SPECIFIC(__FN__,__SEC_FIELD__,__MIN_FORMAT_REVISION__,__FAIL_IF_NOT_IN_THIS_REVISION__) \
    __FS_FUNCTION_PREFER_INLINE size_t __FN__(void) { \
        __FS_LOCAL_STATIC_OPTION size_t fsv_t1; \
        \
        fsv_t1 = 0; \
        if(fs_read_security_data_revision_sec() >= __MIN_FORMAT_REVISION__) { \
            SWITCH_DATA_FORMAT(fs_read_security_data_format_sec(), \
                GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_CASE_STATEMENTS_CLASS_SPECIFIC(__SEC_FIELD__) \
                DEFAULT_FS_FAILURE(FS_FAILURE_ ## __FN__ ## _1) \
            ) \
        } \
        if (__FAIL_IF_NOT_IN_THIS_REVISION__) { \
            fs_failure(FS_FAILURE_ ## __FN__ ## _2); \
        } \
        return fsv_t1; \
    }

#define GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_COMMON(__FN__,__SEC_FIELD__) \
    __FS_FUNCTION_PREFER_INLINE size_t __FN__(void) { \
        return __FLASH_COMMON_SEC_OFFSET(__SEC_FIELD__); \
    }

#define GENERATE_SIMPLE_GET_CONFIG_SECTION_OFFSET_FUNCTION(__FN__,__SECTION__,__MIN_FORMAT_REVISION__) \
    __FS_FUNCTION_PREFER_INLINE size_t __FN__(void) { \
        __FS_LOCAL_STATIC_OPTION size_t fsv_t1; \
        \
        fsv_t1 = 0; \
        if(fs_read_security_data_revision_sec() >= __MIN_FORMAT_REVISION__) { \
            SWITCH_DATA_FORMAT(fs_read_security_data_format_sec(), \
                GENERATE_SIMPLE_GET_CONFIG_SECTION_OFFSET_FUNCTION_CASE_STATEMENTS(__SECTION__) \
                DEFAULT_FS_FAILURE(FS_FAILURE_ ## __FN__ ## _1) \
            ) \
        } else { \
            fs_failure(FS_FAILURE_ ## __FN__ ## _2); \
        } \
        return fsv_t1; \
    }

// BEGIN - These functions are done in a simpler way and early in the file because they are needed to check format/version and implement all others.
__FS_FUNCTION_PREFER_INLINE size_t fs_get_config_offset_security_data_format_sec(void) { return __FLASH_COMMON_SEC_OFFSET(format); }
__FS_FUNCTION_PREFER_INLINE u_int8_t  fs_read_security_data_format_sec(void) { return fs_read_config8(fs_get_config_offset_security_data_format_sec()); }
GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_COMMON(fs_get_config_offset_security_data_revision_raw_sec, revision)
__FS_FUNCTION_PREFER_INLINE u_int8_t  fs_read_security_data_revision_raw_sec(void) { return fs_read_config8(fs_get_config_offset_security_data_revision_raw_sec()); }
// END - These functions are done in a simpler way and early in the file because they are needed to check format/version and implement all others.

__FS_FUNCTION_PREFER_INLINE u_int8_t fs_read_security_data_revision_sec(void) {
#if defined(UBNT_SUPPORT_CLASS_AIRFIBER) || defined(UBNT_SUPPORT_CLASS_BCMWIFI) || defined(UBNT_SUPPORT_CLASS_CAMERA) || defined(UBNT_SUPPORT_CLASS_CAMERA2) || defined(UBNT_SUPPORT_CLASS_NVR) || defined(UBNT_SUPPORT_CLASS_QCASWITCH) || defined(UBNT_SUPPORT_CLASS_ROUTER) || defined(UBNT_SUPPORT_CLASS_SWITCH) || defined(UBNT_SUPPORT_CLASS_UNIVOX) || defined(UBNT_SUPPORT_CLASS_WIFI)
    u_int8_t data_format   = fs_read_security_data_format_sec();
    u_int8_t data_revision = fs_read_security_data_revision_raw_sec();
    u_int8_t buf[3] = {0,0,0};

    /*
    Workaround for bug in old firmware affecting certain product classes
    created before 2014.  Old firmware is matching on major+minor version and
    will report false positive if the data format field does not match rev 1.
    Workaround is a magic value in the product-class specific data areas for these
    product classes, followed by a minor revision number.
    (32 bits - 3 bytes magic, 1 byte minor rev)

    ONLY affected product classes have the workaround.  Others can work with minor
    revision changed in the original location.
    */
#define __DATA_FORMAT_REV_WAR(__MAGIC_OFFSET__,__ALT_REVISION_OFFSET__) do { \
        fs_read_config(buf, sizeof(buf), __MAGIC_OFFSET__, DATA_REV_WAR_MAGIC_SIZE); \
        if (HAS_DATA_FORMAT_REV_WAR_MAGIC(buf)) { \
            data_revision = fs_read_config8(__ALT_REVISION_OFFSET__); \
        } \
    } while(0)

    /*
    Switch table faster than a series of if statements...
    NOTE: This table should never grow only the stuff listed here pre-dates the format revision bug
    */
    SWITCH_DATA_FORMAT(data_format,
        CASE_DATA_FORMAT_AIRFIBER     ( __DATA_FORMAT_REV_WAR(FLASH_SECURITY_OFFSET_AIRFIBER_REVISION_WAR_MAGIC , FLASH_SECURITY_OFFSET_AIRFIBER_ALT_REVISION ); )
        CASE_DATA_FORMAT_BCMWIFI      ( __DATA_FORMAT_REV_WAR(FLASH_SECURITY_OFFSET_BCMWIFI_REVISION_WAR_MAGIC  , FLASH_SECURITY_OFFSET_BCMWIFI_ALT_REVISION  ); )
        CASE_DATA_FORMAT_CAMERA       ( __DATA_FORMAT_REV_WAR(FLASH_SECURITY_OFFSET_CAMERA_REVISION_WAR_MAGIC   , FLASH_SECURITY_OFFSET_CAMERA_ALT_REVISION   ); )
        CASE_DATA_FORMAT_CAMERA2      ( __DATA_FORMAT_REV_WAR(FLASH_SECURITY_OFFSET_CAMERA2_REVISION_WAR_MAGIC  , FLASH_SECURITY_OFFSET_CAMERA2_ALT_REVISION  ); )
        CASE_DATA_FORMAT_NVR          ( __DATA_FORMAT_REV_WAR(FLASH_SECURITY_OFFSET_NVR_REVISION_WAR_MAGIC      , FLASH_SECURITY_OFFSET_NVR_ALT_REVISION      ); )
        CASE_DATA_FORMAT_QCASWITCH    ( __DATA_FORMAT_REV_WAR(FLASH_SECURITY_OFFSET_QCASWITCH_REVISION_WAR_MAGIC, FLASH_SECURITY_OFFSET_QCASWITCH_ALT_REVISION); )
        CASE_DATA_FORMAT_ROUTER       ( __DATA_FORMAT_REV_WAR(FLASH_SECURITY_OFFSET_ROUTER_REVISION_WAR_MAGIC   , FLASH_SECURITY_OFFSET_ROUTER_ALT_REVISION   ); )
        CASE_DATA_FORMAT_SWITCH       ( __DATA_FORMAT_REV_WAR(FLASH_SECURITY_OFFSET_SWITCH_REVISION_WAR_MAGIC   , FLASH_SECURITY_OFFSET_SWITCH_ALT_REVISION   ); )
        CASE_DATA_FORMAT_UNIVOX       ( __DATA_FORMAT_REV_WAR(FLASH_SECURITY_OFFSET_UNIVOX_REVISION_WAR_MAGIC   , FLASH_SECURITY_OFFSET_UNIVOX_ALT_REVISION   ); )
        CASE_DATA_FORMAT_WIFI_FLASH   ( __DATA_FORMAT_REV_WAR(FLASH_SECURITY_OFFSET_WIFI_REVISION_WAR_MAGIC     , FLASH_SECURITY_OFFSET_WIFI_ALT_REVISION     ); )
        default:
            break;
    )
    return data_revision;
#else // #if defined(UBNT_SUPPORT_CLASS_AIRFIBER) || defined(UBNT_SUPPORT_CLASS_BCMWIFI) || defined(UBNT_SUPPORT_CLASS_CAMERA) || defined(UBNT_SUPPORT_CLASS_CAMERA2) || defined(UBNT_SUPPORT_CLASS_NVR) || defined(UBNT_SUPPORT_CLASS_QCASWITCH) || defined(UBNT_SUPPORT_CLASS_ROUTER) || defined(UBNT_SUPPORT_CLASS_SWITCH) || defined(UBNT_SUPPORT_CLASS_UNIVOX) || defined(UBNT_SUPPORT_CLASS_WIFI)
    return fs_read_security_data_revision_raw_sec();
#endif // #if defined(UBNT_SUPPORT_CLASS_AIRFIBER) || defined(UBNT_SUPPORT_CLASS_BCMWIFI) || defined(UBNT_SUPPORT_CLASS_CAMERA) || defined(UBNT_SUPPORT_CLASS_CAMERA2) || defined(UBNT_SUPPORT_CLASS_NVR) || defined(UBNT_SUPPORT_CLASS_QCASWITCH) || defined(UBNT_SUPPORT_CLASS_ROUTER) || defined(UBNT_SUPPORT_CLASS_SWITCH) || defined(UBNT_SUPPORT_CLASS_UNIVOX) || defined(UBNT_SUPPORT_CLASS_WIFI)
}

#if SECURITY_ENABLE_ESN_SIGNATURE_CHECKS
GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_COMMON(fs_get_config_offset_esn_sig_iv_area_sec, esn_sig_iv_area)
GENERATE_SIMPLE_GET_CONFIG_SECTION_OFFSET_FUNCTION(fs_get_config_offset_esn_signed_start, device_data, 1)   // signature starts with device data section
GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_COMMON(fs_get_config_offset_esn_signed_end, esn_sig_iv_area) // signature ends where iv data begins, which is followed by the signature
GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_COMMON(fs_get_config_offset_esn_signature_sec, esn_signature)
#endif // #if SECURITY_ENABLE_ESN_SIGNATURE_CHECKS

GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_COMMON(fs_get_config_offset_ubnt_signature_sec, ubnt_signature)
GENERATE_SIMPLE_GET_CONFIG_SECTION_OFFSET_FUNCTION(fs_get_config_offset_ubnt_signed_start, device_data, 1)  // signature starts with device data section
GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_COMMON(fs_get_config_offset_ubnt_signed_end, ubnt_signature) // ubnt RSA signature ends at the start of the signature itself
GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_COMMON(fs_get_config_offset_flash_uid_sec, flash_uid)
GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_COMMON(fs_get_config_offset_flash_uid_length_sec, flash_uid_length)
GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_COMMON(fs_get_config_offset_flash_type_id_sec, flash_jedec_id)
GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_COMMON(fs_get_config_offset_product_class_id_sec, product_class_id)
GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_COMMON(fs_get_config_offset_manufacturer_id_sec, manufacturer_id)
GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_COMMON(fs_get_config_offset_registration_timestamp_sec, registration_timestamp)
GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_COMMON(fs_get_config_offset_device_id_sec, device_id)
GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_COMMON(fs_get_config_offset_registration_id_sec, registration_id)
GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_COMMON(fs_get_config_offset_subvendor_id_sec, subvendor_id)
GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_COMMON(fs_get_config_offset_subsystem_id_sec, subsystem_id)
GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_COMMON(fs_get_config_offset_eth0_mac_address_sec, eth0_mac_address)
GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_COMMON(fs_get_config_offset_eth1_mac_address_sec, eth1_mac_address)
GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_COMMON(fs_get_config_offset_flash_jedec_id_sec, flash_jedec_id)
GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_CLASS_SPECIFIC(fs_get_config_offset_qr_code_sec, qr_code, 2, 0 /* no error if missing */)
GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_CLASS_SPECIFIC(fs_get_config_offset_fcd_id_sec, fcd_id, 3, 0 /* no error if missing */)
GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_CLASS_SPECIFIC(fs_get_config_offset_fcd_version_sec, fcd_version, 3, 0 /* no error if missing */)
GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_CLASS_SPECIFIC(fs_get_config_offset_sw_id_sec, sw_id, 3, 0 /* no error if missing */)
GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_CLASS_SPECIFIC(fs_get_config_offset_sw_version_sec, sw_version, 3, 0 /* no error if missing */)

__FS_FUNCTION_PREFER_INLINE size_t fs_get_config_offset_cpu_rev_id_sec(void) {
    __FS_LOCAL_STATIC_OPTION size_t fsv_t1;
    __FS_LOCAL_STATIC_OPTION u_int8_t fsv_t2;
    fsv_t1 = 0;
    fsv_t2 = 0;

    fsv_t2 = fs_read_security_data_revision_sec();
    if(fsv_t2 >= 1) {
        SWITCH_DATA_FORMAT(fs_read_security_data_format_sec(),
            CASE_DATA_FORMAT_AIRFIBER             ( return FLASH_SECURITY_OFFSET_AIRFIBER_CPU_REV_ID; )
            CASE_DATA_FORMAT_BCMSWITCH            ( return FLASH_SECURITY_OFFSET_BCMSWITCH_CPU_REV_ID; )
            CASE_DATA_FORMAT_CLOUDKEY             ( return FLASH_SECURITY_OFFSET_CLOUDKEY_CPU_REV_ID; )
            CASE_DATA_FORMAT_BCMWIFI              ( return FLASH_SECURITY_OFFSET_BCMWIFI_CPU_REV_ID; )
            CASE_DATA_FORMAT_CAMERA2              ( /* not present, so offset 0 is ok */; )
            CASE_DATA_FORMAT_CAMERA               ( /* not present, so offset 0 is ok */; )
            CASE_DATA_FORMAT_NVR                  ( /* not present, so offset 0 is ok */; )
            CASE_DATA_FORMAT_QCASWITCH            ( /* not present, so offset 0 is ok */; )
            CASE_DATA_FORMAT_ROUTER               ( return FLASH_SECURITY_OFFSET_ROUTER_CPU_REV_ID; )
            CASE_DATA_FORMAT_SOLARGATEWAY         ( return FLASH_SECURITY_OFFSET_SOLARGATEWAY_CPU_REV_ID; )
            CASE_DATA_FORMAT_SWITCH               ( return FLASH_SECURITY_OFFSET_SWITCH_CPU_REV_ID; )
            CASE_DATA_FORMAT_UNIVOX               ( return FLASH_SECURITY_OFFSET_UNIVOX_CPU_REV_ID; )
            CASE_DATA_FORMAT_WIFI_FLASH           ( return FLASH_SECURITY_OFFSET_WIFI_CPU_REV_ID; )
            CASE_DATA_FORMAT_INVERTER             ( /* not present, so offset 0 is ok */; )
            CASE_DATA_FORMAT_BASIC                ( return (fsv_t2 >= 2) ? FLASH_SECURITY_OFFSET_BASIC_CPU_REV_ID : 0; )
            CASE_DATA_FORMAT_BASIC4K              ( return FLASH_SECURITY_OFFSET_BASIC4K_CPU_REV_ID; )
            DEFAULT_FS_FAILURE(FS_FAILURE_fs_get_config_offset_cpu_rev_id_sec_1)
        )
    }
    return fsv_t1;
}

__FS_FUNCTION_PREFER_INLINE size_t    fs_read_flash_uid_length_sec(void)                               { return fs_read_config8(fs_get_config_offset_flash_uid_length_sec()); }
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_flash_type_id_sec(void)                                  { return fs_read_config_be32toh(fs_get_config_offset_flash_type_id_sec()); }
__FS_FUNCTION_PREFER_INLINE u_int16_t fs_read_product_class_id_sec(void)                               { return fs_read_config_be16toh(fs_get_config_offset_product_class_id_sec()); }
__FS_FUNCTION_PREFER_INLINE u_int16_t fs_read_manufacturer_id_sec(void)                                { return fs_read_config_be16toh(fs_get_config_offset_manufacturer_id_sec()); }
__FS_FUNCTION_PREFER_INLINE u_int64_t fs_read_registration_timestamp_sec(void)                         { return fs_read_config_be64toh(fs_get_config_offset_registration_timestamp_sec()); }
__FS_FUNCTION_PREFER_INLINE u_int64_t fs_read_device_id_sec(void)                                      { return fs_read_config_be64toh(fs_get_config_offset_device_id_sec()); }
__FS_FUNCTION_PREFER_INLINE u_int64_t fs_read_registration_id_sec(void)                                { return fs_read_config_be64toh(fs_get_config_offset_registration_id_sec()); }
__FS_FUNCTION_PREFER_INLINE u_int16_t fs_read_subsystem_id_sec(void)                                   { return fs_read_config_be16toh(fs_get_config_offset_subsystem_id_sec()); }
__FS_FUNCTION_PREFER_INLINE u_int16_t fs_read_subvendor_id_sec(void)                                   { return fs_read_config_be16toh(fs_get_config_offset_subvendor_id_sec()); }
__FS_FUNCTION_PREFER_INLINE void      fs_read_eth0_mac_address_sec(u_int8_t* dest, size_t dest_len)    { fs_read_config(dest, dest_len, fs_get_config_offset_eth0_mac_address_sec(), MAC_ADDRESS_SIZE); }
__FS_FUNCTION_PREFER_INLINE void      fs_read_eth1_mac_address_sec(u_int8_t* dest, size_t dest_len)    { fs_read_config(dest, dest_len, fs_get_config_offset_eth1_mac_address_sec(), MAC_ADDRESS_SIZE); }
__FS_FUNCTION_PREFER_INLINE size_t    fs_read_flash_uid_sec(u_int8_t* dest, size_t dest_len)           { fs_read_config(dest, dest_len, fs_get_config_offset_flash_uid_sec(), MAX_FLASH_UID_SIZE); return fs_read_flash_uid_length_sec(); }

__FS_FUNCTION_PREFER_INLINE void fs_read_ubnt_signature_sec(u_int8_t* dest, size_t dest_len) {
        fs_read_config(dest, dest_len, fs_get_config_offset_ubnt_signature_sec(), RSA_SIGNATURE_SIZE);
}

#if SECURITY_ENABLE_ESN_SIGNATURE_CHECKS
__FS_FUNCTION_PREFER_INLINE void fs_read_esn_sig_iv_area_sec(u_int8_t* dest, size_t dest_len) {
        fs_read_config(dest, dest_len, fs_get_config_offset_esn_sig_iv_area_sec(), SIG_IV_AREA_SIZE);
}

__FS_FUNCTION_PREFER_INLINE void fs_read_esn_signature_sec(u_int8_t* dest, size_t dest_len) {
        fs_read_config(dest, dest_len, fs_get_config_offset_esn_signature_sec(), ESN_SIGNATURE_SIZE);
}
#endif // #if SECURITY_ENABLE_ESN_SIGNATURE_CHECKS

typedef struct fs_check_flash_uid_data {
        u_int8_t buf_hw [MAX_FLASH_UID_SIZE];
        u_int8_t buf_sec[MAX_FLASH_UID_SIZE];
        u_int8_t len_sec;
        u_int8_t len_hw;
} fs_check_flash_uid_t;

__FS_FUNCTION_PREFER_INLINE void _fs_check_flash_uid_sec_vs_hw(void) {
        __FS_LOCAL_STATIC_OPTION fs_check_flash_uid_t* fsv_t1;

        fsv_t1 = (fs_check_flash_uid_t*)fs_zalloc(sizeof(fs_check_flash_uid_t));
        if (NULL == fsv_t1) {
                goto done;
        }
        fsv_t1->len_sec = fs_read_flash_uid_sec(fsv_t1->buf_hw,sizeof (fsv_t1->buf_hw));
        fsv_t1->len_hw  = fs_read_flash_uid_hw(fsv_t1->buf_sec,sizeof (fsv_t1->buf_sec));
        if(0
                || (fsv_t1->len_hw  > MAX_FLASH_UID_SIZE)
                || (fsv_t1->len_sec > MAX_FLASH_UID_SIZE)
                || (fsv_t1->len_hw != fsv_t1->len_sec)
                || (0 != memcmp( fsv_t1->buf_hw, fsv_t1->buf_sec, fsv_t1->len_hw)))
        {
                fs_failure(FS_FAILURE_fs_check_flash_uid_sec_vs_hw_1);
        }
done:
        fs_safe_shred_and_free(&fsv_t1, sizeof(*fsv_t1));
}

__FS_FUNCTION_PREFER_INLINE int32_t fs_is_empty_qr_code(u_int8_t* dest, __ATTRIB_UNUSED size_t dest_len) {
    return dest_len == QR_CODE_SIZE
        && (
           0 == memcmp(dest,fs_empty_qr_code_00,sizeof fs_empty_qr_code_00)
        || 0 == memcmp(dest,fs_empty_qr_code_FF,sizeof fs_empty_qr_code_FF)
           );
}

__FS_FUNCTION_PREFER_INLINE int32_t fs_is_empty_fcd_id(u_int8_t* dest, __ATTRIB_UNUSED size_t dest_len) {
    return dest_len == FCD_ID_SIZE && 0 == memcmp(dest,fs_empty_fcd_id_FF,sizeof fs_empty_fcd_id_FF);
}

__FS_FUNCTION_PREFER_INLINE int32_t fs_is_empty_fcd_version(u_int8_t* dest, __ATTRIB_UNUSED size_t dest_len) {
    return dest_len == FCD_VERSION_SIZE && 0 == memcmp(dest,fs_empty_fcd_version_FF,sizeof fs_empty_fcd_version_FF);
}

__FS_FUNCTION_PREFER_INLINE int32_t fs_is_empty_sw_id(u_int8_t* dest, __ATTRIB_UNUSED size_t dest_len) {
    return dest_len == SW_ID_SIZE && 0 == memcmp(dest,fs_empty_sw_id_FF,sizeof fs_empty_sw_id_FF);
}

__FS_FUNCTION_PREFER_INLINE int32_t fs_is_empty_sw_version(u_int8_t* dest, __ATTRIB_UNUSED size_t dest_len) {
    return dest_len == SW_VERSION_SIZE && 0 == memcmp(dest,fs_empty_sw_version_FF,sizeof fs_empty_sw_version_FF);
}

/*
Return 1 if QR code was read
Return 0 if no QR code is available
*/
__FS_FUNCTION_PREFER_INLINE int32_t fs_read_qr_code_sec(u_int8_t* dest, size_t dest_len) {
    if(dest != NULL) {
        memset(dest,0xFF,dest_len);
        if ((fs_read_security_data_revision_sec() >= 2 || (fs_read_security_data_format_sec() == FS_SECURITY_DATA_FORMAT_INVERTER)) && (fs_get_config_offset_qr_code_sec() != 0)) {
            fs_read_config(dest, dest_len, fs_get_config_offset_qr_code_sec(), QR_CODE_SIZE);
            if(fs_is_empty_qr_code(dest, dest_len)) {
                memset(dest,0xFF,dest_len);
                return 0;
            }
            return 1;
        }
    }
    return 0;
}

__FS_FUNCTION_PREFER_INLINE int32_t fs_has_qr_code_sec(void) {
    __FS_LOCAL_STATIC_OPTION u_int8_t qr[QR_CODE_SIZE];
    return fs_read_qr_code_sec(qr, sizeof qr) != 0;
}

__FS_FUNCTION_PREFER_INLINE size_t fs_get_config_offset_pcba_sec(void) {
    __FS_LOCAL_STATIC_OPTION size_t fsv_t1;

    fsv_t1 = 0;
    /*
    In rev1, not all products had a PCBA field in security area and in rev2 airfiber rev was relocated and expanded.
    */
    if ( fs_read_security_data_revision_sec() == 0xff
      && fs_read_security_data_format_sec() == FS_SECURITY_DATA_FORMAT_BLANK)
    {
        /* Not signed board */
        return 0;
    } else if ( fs_read_security_data_revision_sec() == 1) {
        SWITCH_DATA_FORMAT(fs_read_security_data_format_sec(),
            CASE_DATA_FORMAT_AIRFIBER             ( fsv_t1 = 0; /* V1 had an old 16-bit board rev ID stored */                         )
            CASE_DATA_FORMAT_BCMSWITCH            ( fs_failure(FS_FAILURE_fs_get_config_offset_pcba_sec_1); return 0; /* v1 Never used */  )
            CASE_DATA_FORMAT_CLOUDKEY             ( fs_failure(FS_FAILURE_fs_get_config_offset_pcba_sec_1); return 0; /* v1 Never used */  )
            CASE_DATA_FORMAT_BCMWIFI              ( fsv_t1 = FLASH_SECURITY_OFFSET_BCMWIFI_PCBA;                                       )
            CASE_DATA_FORMAT_CAMERA2              ( fsv_t1 = 0; /* V1 had no board rev ID */                                           )
            CASE_DATA_FORMAT_CAMERA               ( fsv_t1 = 0; /* V1 had no board rev ID */                                           )
            CASE_DATA_FORMAT_NVR                  ( fsv_t1 = FLASH_SECURITY_OFFSET_NVR_PCBA;                                           )
            CASE_DATA_FORMAT_QCASWITCH            ( fsv_t1 = FLASH_SECURITY_OFFSET_QCASWITCH_PCBA;                                     )
            CASE_DATA_FORMAT_ROUTER               ( fsv_t1 = 0; /* V1 had no board rev ID */                                           )
            CASE_DATA_FORMAT_SWITCH               ( fsv_t1 = 0; /* V1 had no board rev ID */                                           )
            CASE_DATA_FORMAT_UNIVOX               ( fsv_t1 = FLASH_SECURITY_OFFSET_UNIVOX_PCBA;                                        )
            CASE_DATA_FORMAT_WIFI_FLASH           ( fsv_t1 = 0; /* V1 had no board rev ID */                                           )
            CASE_DATA_FORMAT_INVERTER             ( fsv_t1 = FLASH_SECURITY_OFFSET_INVERTER_PCBA;                                      )
            CASE_DATA_FORMAT_SOLARGATEWAY         ( fs_failure(FS_FAILURE_fs_get_config_offset_pcba_sec_1); return 0; /* v1 Never used */  )
            CASE_DATA_FORMAT_BASIC                ( fs_failure(FS_FAILURE_fs_get_config_offset_pcba_sec_1); return 0; /* v1 Never used */  )
            CASE_DATA_FORMAT_BASIC4K              ( fs_failure(FS_FAILURE_fs_get_config_offset_pcba_sec_1); return 0; /* v1 Never used */  )
            DEFAULT_FS_FAILURE(FS_FAILURE_fs_get_config_offset_pcba_sec_2)
        )
    } else {
        // Format revisons 2 and higher (always has board rev ID)
        SWITCH_DATA_FORMAT(fs_read_security_data_format_sec(),
            GENERATE_SIMPLE_GET_CONFIG_SEC_OFFSET_FUNCTION_CASE_STATEMENTS_CLASS_SPECIFIC(pcba)
            DEFAULT_FS_FAILURE(FS_FAILURE_fs_get_config_offset_pcba_sec_3)
        )
    }
    return fsv_t1;
}

__FS_FUNCTION_PREFER_INLINE size_t fs_get_config_offset_radio1_rev_id_sec(void) {
    __FS_LOCAL_STATIC_OPTION size_t fsv_t1;
    fsv_t1 = 0;

    if(fs_read_security_data_revision_sec() >= 1) {
        SWITCH_DATA_FORMAT(fs_read_security_data_format_sec(),
            CASE_DATA_FORMAT_BCMWIFI              ( return FLASH_SECURITY_OFFSET_BCMWIFI_RADIO1_REV_ID; )
            CASE_DATA_FORMAT_WIFI_FLASH           ( return FLASH_SECURITY_OFFSET_WIFI_RADIO1_REV_ID; )
            DEFAULT_RETURN_ZERO()
        )
    }
    return fsv_t1;
}

__FS_FUNCTION_PREFER_INLINE size_t fs_get_config_offset_radio2_rev_id_sec(void) {
    __FS_LOCAL_STATIC_OPTION size_t fsv_t1;
    fsv_t1 = 0;

    if(fs_read_security_data_revision_sec() >= 1) {
        SWITCH_DATA_FORMAT(fs_read_security_data_format_sec(),
            CASE_DATA_FORMAT_BCMWIFI              ( return FLASH_SECURITY_OFFSET_BCMWIFI_RADIO2_REV_ID; )
            CASE_DATA_FORMAT_WIFI_FLASH           ( return FLASH_SECURITY_OFFSET_WIFI_RADIO2_REV_ID; )
            DEFAULT_RETURN_ZERO()
        )
    }
    return fsv_t1;
}

__FS_FUNCTION_PREFER_INLINE size_t fs_get_config_offset_radio1_mac_address_sec(void) {
    __FS_LOCAL_STATIC_OPTION size_t fsv_t1;
    fsv_t1 = 0;

    if(fs_read_security_data_revision_sec() >= 1) {
        SWITCH_DATA_FORMAT(fs_read_security_data_format_sec(),
            CASE_DATA_FORMAT_BCMWIFI              ( return FLASH_SECURITY_OFFSET_BCMWIFI_RADIO1_MAC_ADDRESS; )
            CASE_DATA_FORMAT_WIFI_FLASH           ( return FLASH_SECURITY_OFFSET_WIFI_RADIO1_MAC_ADDRESS; )
            DEFAULT_RETURN_ZERO()
        )
    }
    return fsv_t1;
}

__FS_FUNCTION_PREFER_INLINE size_t fs_get_config_offset_radio2_mac_address_sec(void) {
    __FS_LOCAL_STATIC_OPTION size_t fsv_t1;
    fsv_t1 = 0;

    if(fs_read_security_data_revision_sec() >= 1) {
        SWITCH_DATA_FORMAT(fs_read_security_data_format_sec(),
            CASE_DATA_FORMAT_BCMWIFI              ( return FLASH_SECURITY_OFFSET_BCMWIFI_RADIO2_MAC_ADDRESS; )
            CASE_DATA_FORMAT_WIFI_FLASH           ( return FLASH_SECURITY_OFFSET_WIFI_RADIO2_MAC_ADDRESS; )
            DEFAULT_RETURN_ZERO()
        )
    }
    return fsv_t1;
}

__FS_FUNCTION_PREFER_INLINE size_t fs_get_config_offset_vpd_sec(void) {
    __FS_LOCAL_STATIC_OPTION size_t fsv_t1;
    fsv_t1 = 0;

    if(fs_read_security_data_revision_sec() == 1) {
        SWITCH_DATA_FORMAT(fs_read_security_data_format_sec(),
            CASE_DATA_FORMAT_BCMSWITCH            ( return FLASH_SECURITY_OFFSET_BCMSWITCH_VPD; )
            DEFAULT_RETURN_ZERO()
        )
    } else if(fs_read_security_data_revision_sec() >= 2) {
        SWITCH_DATA_FORMAT(fs_read_security_data_format_sec(),
            CASE_DATA_FORMAT_BCMSWITCH            ( return FLASH_SECURITY_OFFSET_BCMSWITCH_VPD; )
            CASE_DATA_FORMAT_ROUTER               ( return FLASH_SECURITY_OFFSET_ROUTER_VPD; )
            DEFAULT_RETURN_ZERO()
        )
    }
    return fsv_t1;
}

// NB: This function will only return a value if the current security data format has a value for this field.
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_pcba_sec(void) {
    if (fs_get_config_offset_pcba_sec() != 0) {
        return fs_read_config_be32toh(fs_get_config_offset_pcba_sec());
    }
    return 0;
}

// NB: This function will only return a value if the current security data format has a value for this field.
__FS_FUNCTION_PREFER_INLINE u_int16_t fs_read_fcd_id_sec(void) {
    if (fs_get_config_offset_fcd_id_sec() != 0) {
        return fs_read_config_be16toh(fs_get_config_offset_fcd_id_sec());
    }
    return 0;
}

// NB: This function will only return a value if the current security data format has a value for this field.
__FS_FUNCTION_PREFER_INLINE u_int16_t fs_read_sw_id_sec(void) {
    if (fs_get_config_offset_sw_id_sec() != 0) {
        return fs_read_config_be16toh(fs_get_config_offset_sw_id_sec());
    }
    return 0;
}

// NB: This function will only return a value if the current security data format has a value for this field.
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_fcd_version_sec(void) {
    if (fs_get_config_offset_fcd_version_sec() != 0) {
        return fs_read_config_be32toh(fs_get_config_offset_fcd_version_sec());
    }
    return 0;
}

// NB: This function will only return a value if the current security data format has a value for this field.
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_sw_version_sec(void) {
    if (fs_get_config_offset_sw_version_sec() != 0) {
        return fs_read_config_be32toh(fs_get_config_offset_sw_version_sec());
    }
    return 0;
}

#include "security.sec.class.airfiber.inc"
#include "security.sec.class.bcmwifi.inc"
#include "security.sec.class.camera.inc"
#include "security.sec.class.camera2.inc"
#include "security.sec.class.nvr.inc"
#include "security.sec.class.qcaswitch.inc"
#include "security.sec.class.bcmswitch.inc"
#include "security.sec.class.cloudkey.inc"
#include "security.sec.class.router.inc"
#include "security.sec.class.solargateway.inc"
#include "security.sec.class.switch.inc"
#include "security.sec.class.basic.inc"
#include "security.sec.class.basic4k.inc"
#include "security.sec.class.univox.inc"
#include "security.sec.class.wifi.inc"
#include "security.sec.class.inverter.inc"

#endif // #ifdef SECURITY_IS_TARGET_BUILD
