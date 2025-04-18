#ifdef __KERNEL__
#define fs_have_ctime() 0
#define fs_ctime(...)   ""
#else // #ifdef __KERNEL__
#define fs_have_ctime() 1
#define fs_ctime(__val) ctime(__val)
#endif // #ifdef __KERNEL__

#if SECURITY_ENABLE_DIAGNOSTIC_DUMPS

typedef struct fs_dump_everything_data {
#ifdef UBNT_SUPPORT_CLASS_WIFI
    u_int32_t wifi_radio1_mac_rev_hw;
    u_int32_t wifi_radio2_mac_rev_hw;
    u_int32_t wifi_radio1_mac_rev_sec;
    u_int32_t wifi_radio2_mac_rev_sec;
    u_int8_t  wifi_radio1_mac_address_sec          [MAC_ADDRESS_SIZE];
    u_int8_t  wifi_radio2_mac_address_sec          [MAC_ADDRESS_SIZE];
    u_int8_t  wifi_radio1_mac_address_hw           [MAC_ADDRESS_SIZE];
    u_int8_t  wifi_radio2_mac_address_hw           [MAC_ADDRESS_SIZE];
#endif // #ifdef UBNT_SUPPORT_CLASS_WIFI
#ifdef UBNT_SUPPORT_CLASS_BCMWIFI
    u_int8_t  bcmwifi_wifi_radio1_mac_address_sec  [MAC_ADDRESS_SIZE];
    u_int8_t  bcmwifi_wifi_radio2_mac_address_sec  [MAC_ADDRESS_SIZE];
    u_int8_t  bcmwifi_wifi_radio1_mac_address_fbd  [MAC_ADDRESS_SIZE];
    u_int8_t  bcmwifi_wifi_radio2_mac_address_fbd  [MAC_ADDRESS_SIZE];
    u_int8_t  BCM4706_wifi_radio1_mac_address_hw   [MAC_ADDRESS_SIZE];
    u_int8_t  BCM4706_wifi_radio2_mac_address_hw   [MAC_ADDRESS_SIZE];
#endif // #ifdef UBNT_SUPPORT_CLASS_BCMWIFI
#ifdef UBNT_SUPPORT_CLASS_ROUTER
    u_int8_t  router_vpd_sec                       [ROUTER_VPD_SIZE];
    u_int8_t  router_vpd_fbd                       [ROUTER_VPD_SIZE];
#endif // #ifdef UBNT_SUPPORT_CLASS_ROUTER
#ifdef UBNT_SUPPORT_CLASS_BCMSWITCH
    u_int8_t  bcmswitch_vpd_sec                    [BCMSWITCH_VPD_SIZE];
    u_int8_t  bcmswitch_vpd_fbd                    [BCMSWITCH_VPD_SIZE];
#endif // #ifdef UBNT_SUPPORT_CLASS_BCMSWITCH
    u_int8_t  qr_code_sec                          [QR_CODE_SIZE];
    u_int16_t fcd_id_sec;
    u_int32_t fcd_version_sec;
    u_int16_t sw_id_sec;
    u_int32_t sw_version_sec;
    u_int8_t  hwaddr_bi                            [MAC_ADDRESS_SIZE];
    u_int8_t  ubnt_signature_sec                   [RSA_SIGNATURE_SIZE];
#if SECURITY_ENABLE_ESN_SIGNATURE_CHECKS           
    u_int8_t  esn_sig_iv_area_sec                  [SIG_IV_AREA_SIZE];
    u_int8_t  esn_signature_sec                    [ESN_SIGNATURE_SIZE];
#endif // #if SECURITY_ENABLE_ESN_SIGNATURE_CHECKS
    u_int8_t  flash_uid_hw                         [MAX_FLASH_UID_SIZE];
    u_int8_t  flash_uid_sec                        [MAX_FLASH_UID_SIZE];
    u_int8_t  eth0_mac_address_sec                 [MAC_ADDRESS_SIZE];
    u_int8_t  eth1_mac_address_sec                 [MAC_ADDRESS_SIZE];
    u_int8_t  eth0_mac_address_hw                  [MAC_ADDRESS_SIZE];
    u_int8_t  eth1_mac_address_hw                  [MAC_ADDRESS_SIZE];
    u_int8_t  eth0_mac_address_fbd                 [MAC_ADDRESS_SIZE];
    u_int8_t  eth1_mac_address_fbd                 [MAC_ADDRESS_SIZE];
    u_int8_t  eth0_mac_address_bi                  [MAC_ADDRESS_SIZE];
    u_int8_t  eth1_mac_address_bi                  [MAC_ADDRESS_SIZE];
    u_int8_t  wifi_radio1_mac_address_bi           [MAC_ADDRESS_SIZE];
    u_int8_t  wifi_radio2_mac_address_bi           [MAC_ADDRESS_SIZE];
    u_int8_t  security_data_revision_raw_sec;
    u_int8_t  security_data_revision_sec;
    u_int8_t  security_data_format_sec;
    u_int8_t  flash_uid_len_sec;
    time_t    mfg_timestamp;
    u_int8_t  flash_uid_len_hw;
    int       secinfo_exists;
    int       boardinfo_exists;
} fs_dump_everything_data_t;

#define FS_DUMP__INDENT_WIDTH                         4
#define FS_DUMP__PAD_CHAR                            '.'
#define FS_DUMP__MAX_PAD_WIDTH_UPPER_LIMIT           80
#define FS_DUMP__MAX_PAD_WIDTH                       40
#define FS_DUMP__MIN_PAD_WIDTH                        3
#define FS_DUMP__MAX_LABEL_LENGTH                    (FS_DUMP__INDENT_WIDTH+FS_DUMP__MAX_PAD_WIDTH_UPPER_LIMIT)

#define FS_DUMP__FORMAT_HEX_DUAL8                   "0x%02" PRIx8 "%02" PRIx8
#define FS_DUMP__FORMAT_PCBA_RAW32                  "%02" PRIx8 ":%02" PRIx8 ":%02" PRIx8 ":%02" PRIx8
#define FS_DUMP__FORMAT_PCBA_RAW16                  "%02" PRIx8 ":%02" PRIx8
#define FS_DUMP__FORMAT_PCBA_REV                    "13-XXXXX-%02" PRId8
#define FS_DUMP__FORMAT_PCBA                        "13-%05" PRId32 "-%02" PRId8

#define FS_DUMP__FORMAT_VERSION_RAW32               "%02" PRIx8 ":%02" PRIx8 ":%02" PRIx8 ":%02" PRIx8
#define FS_DUMP__FORMAT_VERSION_LOGICAL             "v%" PRId8 ".%" PRId8 ".%" PRId8

#define FS_DUMP__DESC_NOT_PROGRAMMED                "[Not Programmed]"
#define FS_DUMP__DESC_NOT_VALID                     "[Not Valid]"
#define FS_DUMP__DESC_NOT_RECOGNIZED                "[Not Recognized]"
#define FS_DUMP__DESC_NOT_SPECIFIED                 "[Unspecified]"
#define FS_DUMP__DESC_NOT_SUPPORTED_BY_REVX         "[Not Supported In Rev %d]"
#define FS_DUMP__DESC_1BYTE                         "[Legacy 1-byte Rev-Only PCBA]"
#define FS_DUMP__DESC_2BYTE                         "[Legacy 2-byte Rev-Only PCBA]"
#define FS_DUMP__DESC_4BYTE                         "[Legacy 4-byte Rev-Only PCBA]"

#define FS_DUMP__FORMAT_DESC_NOT_VALID              "[" FS_SECURITY_DATA_FORMAT_LABEL_INVALID                "]"
#define FS_DUMP__FORMAT_DESC_WIFI_FLASH             "[" FS_SECURITY_DATA_FORMAT_LABEL_WIFI_FLASH             "]"
#define FS_DUMP__FORMAT_DESC_WIFI_RADIO_EEPROM      "[" FS_SECURITY_DATA_FORMAT_LABEL_WIFI_RADIO_EEPROM      "]"
#define FS_DUMP__FORMAT_DESC_WIFI_DIGITAL_BOARD     "[" FS_SECURITY_DATA_FORMAT_LABEL_WIFI_DIGITAL_BOARD     "]"
#define FS_DUMP__FORMAT_DESC_CAMERA                 "[" FS_SECURITY_DATA_FORMAT_LABEL_CAMERA                 "]"
#define FS_DUMP__FORMAT_DESC_WIFI_DUAL_RF           "[" FS_SECURITY_DATA_FORMAT_LABEL_WIFI_DUAL_RF           "]"
#define FS_DUMP__FORMAT_DESC_SWITCH                 "[" FS_SECURITY_DATA_FORMAT_LABEL_SWITCH                 "]"
#define FS_DUMP__FORMAT_DESC_BASIC                  "[" FS_SECURITY_DATA_FORMAT_LABEL_BASIC                  "]"
#define FS_DUMP__FORMAT_DESC_BASIC4K                "[" FS_SECURITY_DATA_FORMAT_LABEL_BASIC4K                "]"
#define FS_DUMP__FORMAT_DESC_ROUTER                 "[" FS_SECURITY_DATA_FORMAT_LABEL_ROUTER                 "]"
#define FS_DUMP__FORMAT_DESC_AIRFIBER               "[" FS_SECURITY_DATA_FORMAT_LABEL_AIRFIBER               "]"
#define FS_DUMP__FORMAT_DESC_UNIVOX                 "[" FS_SECURITY_DATA_FORMAT_LABEL_UNIVOX                 "]"
#define FS_DUMP__FORMAT_DESC_CAMERA2                "[" FS_SECURITY_DATA_FORMAT_LABEL_CAMERA2                "]"
#define FS_DUMP__FORMAT_DESC_INVERTER               "[" FS_SECURITY_DATA_FORMAT_LABEL_INVERTER               "]"
#define FS_DUMP__FORMAT_DESC_BCMWIFI                "[" FS_SECURITY_DATA_FORMAT_LABEL_BCMWIFI                "]"
#define FS_DUMP__FORMAT_DESC_QCASWITCH              "[" FS_SECURITY_DATA_FORMAT_LABEL_QCASWITCH              "]"
#define FS_DUMP__FORMAT_DESC_NVR                    "[" FS_SECURITY_DATA_FORMAT_LABEL_NVR                    "]"
#define FS_DUMP__FORMAT_DESC_BCMSWITCH              "[" FS_SECURITY_DATA_FORMAT_LABEL_BCMSWITCH              "]"
#define FS_DUMP__FORMAT_DESC_CLOUDKEY               "[" FS_SECURITY_DATA_FORMAT_LABEL_CLOUDKEY               "]"
#define FS_DUMP__FORMAT_DESC_SOLARGATEWAY           "[" FS_SECURITY_DATA_FORMAT_LABEL_SOLARGATEWAY           "]"
#define FS_DUMP__FORMAT_DESC_MISSING                FS_DUMP__DESC_NOT_PROGRAMMED
#define FS_DUMP__FORMAT_DESC_NOT_RECOGNIZED         FS_DUMP__DESC_NOT_RECOGNIZED

#define FS_DUMP__PRODUCT_CLASS_DESC_INVALID         "[" FS_PRODUCT_CLASS_LABEL_INVALID
#define FS_DUMP__PRODUCT_CLASS_DESC_RADIO           "[" FS_PRODUCT_CLASS_LABEL_RADIO                         "]"
#define FS_DUMP__PRODUCT_CLASS_DESC_RF_BOARD        "[" FS_PRODUCT_CLASS_LABEL_RF_BOARD                      "]"
#define FS_DUMP__PRODUCT_CLASS_DESC_DIGITAL_BOARD   "[" FS_PRODUCT_CLASS_LABEL_DIGITAL_BOARD                 "]"
#define FS_DUMP__PRODUCT_CLASS_DESC_CAMERA          "[" FS_PRODUCT_CLASS_LABEL_CAMERA                        "]"
#define FS_DUMP__PRODUCT_CLASS_DESC_RF_BOARD_DUAL   "[" FS_PRODUCT_CLASS_LABEL_RF_BOARD_DUAL                 "]"
#define FS_DUMP__PRODUCT_CLASS_DESC_INVERTER        "[" FS_PRODUCT_CLASS_LABEL_INVERTER                      "]"
#define FS_DUMP__PRODUCT_CLASS_DESC_SWITCH          "[" FS_PRODUCT_CLASS_LABEL_SWITCH                        "]"
#define FS_DUMP__PRODUCT_CLASS_DESC_BASIC           "[" FS_PRODUCT_CLASS_LABEL_BASIC                         "]"
#define FS_DUMP__PRODUCT_CLASS_DESC_BASIC4K         "[" FS_PRODUCT_CLASS_LABEL_BASIC4K                       "]"
#define FS_DUMP__PRODUCT_CLASS_DESC_ROUTER          "[" FS_PRODUCT_CLASS_LABEL_ROUTER                        "]"
#define FS_DUMP__PRODUCT_CLASS_DESC_AIRFIBER        "[" FS_PRODUCT_CLASS_LABEL_AIRFIBER                      "]"
#define FS_DUMP__PRODUCT_CLASS_DESC_UNIVOX          "[" FS_PRODUCT_CLASS_LABEL_UNIVOX                        "]"
#define FS_DUMP__PRODUCT_CLASS_DESC_CAMERA2         "[" FS_PRODUCT_CLASS_LABEL_CAMERA2                       "]"
#define FS_DUMP__PRODUCT_CLASS_DESC_BCMWIFI         "[" FS_PRODUCT_CLASS_LABEL_BCMWIFI                       "]"
#define FS_DUMP__PRODUCT_CLASS_DESC_QCASWITCH       "[" FS_PRODUCT_CLASS_LABEL_QCASWITCH                     "]"
#define FS_DUMP__PRODUCT_CLASS_DESC_LEGACY          "[" FS_PRODUCT_CLASS_LABEL_LEGACY                        "]"
#define FS_DUMP__PRODUCT_CLASS_DESC_NVR             "[" FS_PRODUCT_CLASS_LABEL_NVR                           "]"
#define FS_DUMP__PRODUCT_CLASS_DESC_SAMPLE          "[" FS_PRODUCT_CLASS_LABEL_SAMPLE                        "]"
#define FS_DUMP__PRODUCT_CLASS_DESC_BCMSWITCH       "[" FS_PRODUCT_CLASS_LABEL_BCMSWITCH                     "]"
#define FS_DUMP__PRODUCT_CLASS_DESC_CLOUDKEY        "[" FS_PRODUCT_CLASS_LABEL_CLOUDKEY                      "]"
#define FS_DUMP__PRODUCT_CLASS_DESC_SOLARGATEWAY    "[" FS_PRODUCT_CLASS_LABEL_SOLARGATEWAY                  "]"
#define FS_DUMP__PRODUCT_CLASS_DESC_MISSING         FS_DUMP__DESC_NOT_RECOGNIZED
#define FS_DUMP__PRODUCT_CLASS_DESC_NOT_RECOGNIZED  FS_DUMP__DESC_NOT_RECOGNIZED

#define FS_DUMP__BYTE_FIELDS_32(value)              ((value) >> 24) & 0xFF, ((value) >> 16) & 0xFF, ((value) >> 8) & 0xFF, (value) & 0xFF
#define FS_DUMP__BYTE_FIELDS_16(value)              ((value) >>  8) & 0xFF, (value) & 0xFF
#define FS_DUMP__BYTE_FIELDS_VERSION(value)         ((value) >> 16) & 0xFFFF, ((value) >> 8) & 0xFF, (value) & 0xFF

#define FS_DUMP__MAX(a,b)                           ((a)>(b)?(a):(b))
#define FS_DUMP__MIN(a,b)                           ((a)>(b)?(b):(a))

#if SECURITY_ENABLE_DEBUG_OUTPUT && defined(UBNT_SUPPORT_CLASS_WIFI)
__FS_FUNCTION_PREFER_INLINE const char* fs_identify_wifi_cpu_family(u_int32_t hardware_revision) {
#if (defined(UBNT_MIPS_ARxxxx) || SECURITY_ENABLE_SIMULATION)
        switch((hardware_revision & __ARxxxx_REV_ID_MASK_MAJOR)) {
        case __AR7240_REV_1_x:
            return fs_get_decoded_family_hydra();
        case __AR7241_REV_1_x:
            return fs_get_decoded_family_virian_old();
        case __AR7242_REV_1_x:
            return fs_get_decoded_family_virian();
        case __AR9330_REV_1_x:
        case __AR9331_REV_1_x:
            return fs_get_decoded_family_hornet();
        case __AR9341_REV_1_x:
        case __AR9342_REV_1_x:
        case __AR9344_REV_1_x:
            return fs_get_decoded_family_wasp();
        case __QCA955x_REV_1_x:
            return fs_get_decoded_family_scorpion();
        case __QCA956x_REV_1_x:
            return fs_get_decoded_family_dragonfly();
        default:
            break;
        }
#endif // #if (defined(UBNT_MIPS_ARxxxx) || SECURITY_ENABLE_SIMULATION)
#if (defined(UBNT_ARM_IPQ40xx) || SECURITY_ENABLE_SIMULATION)
        switch((hardware_revision & __IPQ40xx_REV_ID_MASK_MAJOR)) {
        // NB: Don't know the mask yet.
        case __IPQ4028_DAKOTA_CPU_MAJOR:
        case __IPQ4029_DAKOTA_CPU_MAJOR:
            return fs_get_decoded_family_dakota();
        default:
            break;
        }
#endif // #if (defined(UBNT_ARM_IPQ40xx) || SECURITY_ENABLE_SIMULATION)
        return fs_get_decoded_family_unknown();
}
#endif // #if SECURITY_ENABLE_DEBUG_OUTPUT && defined(UBNT_SUPPORT_CLASS_WIFI)

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE const char* fs_dump__format_label_ex(
      char* buffer
    , size_t buffer_size
    , size_t indent
    , const char* label
    , size_t min_pad_width
    , size_t max_pad_width
    , u_int8_t truncate
    )
{
    static char pad_buffer[FS_DUMP__MAX_PAD_WIDTH_UPPER_LIMIT+1];
    static u_int8_t pad_buffer_initialized = 0;

    if(buffer && buffer_size) {
        // Lazy populate buffer full of padding
        if(!pad_buffer_initialized) {
            memset(pad_buffer, FS_DUMP__PAD_CHAR, FS_DUMP__MAX_PAD_WIDTH_UPPER_LIMIT);
            pad_buffer[FS_DUMP__MAX_PAD_WIDTH_UPPER_LIMIT] = '\0';
            pad_buffer_initialized = 1;
        }
        // Place upper limit on padding
        max_pad_width = FS_DUMP__MIN(FS_DUMP__MAX_PAD_WIDTH_UPPER_LIMIT, max_pad_width);
        // Build our message
        snprintf(
              buffer
            , (int)FS_DUMP__MIN(
                  buffer_size
                , truncate
                  ? (indent + max_pad_width + 1)
                  : FS_DUMP__MAX((indent + max_pad_width + 1),(indent + min_pad_width + strlen(label) + 1)) /* UNTRUNCATED FS_DUMP__MIN WIDTH */
            )
            , "%*s%s%s"
            , (int)indent, ""
            , label
            , pad_buffer
            );
        return buffer;
    }
    else {
        return "<ERROR>";
    }
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE const char* fs_dump__format_label(char* buffer, size_t buffer_size, const char* label) {
    return fs_dump__format_label_ex(buffer, buffer_size, FS_DUMP__INDENT_WIDTH, label, FS_DUMP__MIN_PAD_WIDTH, FS_DUMP__MAX_PAD_WIDTH, 0);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE const char* fs_dump__format_label_s(const char* label) {
    static char buffer[FS_DUMP__MAX_LABEL_LENGTH+1];
    return fs_dump__format_label_ex(buffer, sizeof buffer, FS_DUMP__INDENT_WIDTH, label, FS_DUMP__MIN_PAD_WIDTH, FS_DUMP__MAX_PAD_WIDTH, 0);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__string(const char* label, const char* value) {
    fs_debug_printf("%s%s\n", fs_dump__format_label_s(label), value);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__unsupported(const char* label, u_int8_t security_data_revision_sec) {
    fs_debug_printf("%s" FS_DUMP__DESC_NOT_SUPPORTED_BY_REVX "\n", fs_dump__format_label_s(label), security_data_revision_sec);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__hex(const char* label, u_int8_t* data, size_t data_size) {
    fs_debug_printf("%s", fs_dump__format_label_s(label));
    fs_hexdump(data, data_size);
    fs_debug_printf("\n");
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__hex_truncated(const char* label, u_int8_t* data, size_t data_size) {
    if (data_size <= 8) {
        fs_dump__hex(label,data,data_size);
    } else {
        fs_debug_printf("%s", fs_dump__format_label_s(label));
        fs_hexdump(data, 4);
        fs_debug_printf("...");
        fs_hexdump(data + data_size - 4, 4);
        fs_debug_printf("\n");
    }
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__message_ex(const char* prefix, const char* message, int32_t indent) {
    fs_debug_printf("%*s%s: %s\n", indent, "", prefix, message);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__error(const char* message) {
    fs_dump__message_ex("ERROR", message, FS_DUMP__INDENT_WIDTH);
}
__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__timestamp64(const char* label, u_int64_t value) {
    fs_debug_printf("%s0x%016" PRIx64 "%s%s", fs_dump__format_label_s(label), value, (fs_have_ctime() ? " - " : "\n"), fs_ctime((const time_t *)&value));
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__hex64(const char* label, u_int64_t value) {
    fs_debug_printf("%s0x%016" PRIx64 "\n", fs_dump__format_label_s(label), value);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__hex32(const char* label, u_int32_t value) {
    fs_debug_printf("%s0x%08" PRIx32 "\n", fs_dump__format_label_s(label), value);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__hex24(const char* label, u_int32_t value) {
    fs_debug_printf("%s0x%06" PRIx32 "\n", fs_dump__format_label_s(label), value);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__hex16(const char* label, u_int16_t value) {
    fs_debug_printf("%s0x%04" PRIx16 "\n", fs_dump__format_label_s(label), value);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__hex8(const char* label, u_int8_t value) {
    fs_debug_printf("%s0x%02" PRIx8 "\n", fs_dump__format_label_s(label), value);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__int64(const char* label, int64_t value) {
    fs_debug_printf("%s%" PRId64 "\n", fs_dump__format_label_s(label), value);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__int32(const char* label, int32_t value) {
    fs_debug_printf("%s%" PRId32 "\n", fs_dump__format_label_s(label), value);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__int16(const char* label, int16_t value) {
    fs_debug_printf("%s%" PRId16 "\n", fs_dump__format_label_s(label), value);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__uint64(const char* label, u_int64_t value) {
    fs_debug_printf("%s%" PRIu64 "\n", fs_dump__format_label_s(label), value);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__uint32(const char* label, u_int32_t value) {
    fs_debug_printf("%s%" PRIu32 "\n", fs_dump__format_label_s(label), value);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__uint16(const char* label, u_int16_t value) {
    fs_debug_printf("%s%" PRIu16 "\n", fs_dump__format_label_s(label), value);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__hex64_desc(const char* label, u_int64_t value, const char* desc) {
    fs_debug_printf("%s0x%016" PRIx64 " %s\n", fs_dump__format_label_s(label), value, desc);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__hex32_desc(const char* label, u_int32_t value, const char* desc) {
    fs_debug_printf("%s0x%08" PRIx32 " %s\n", fs_dump__format_label_s(label), value, desc);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__hex24_desc(const char* label, u_int32_t value, const char* desc) {
    fs_debug_printf("%s0x%06" PRIx32 " %s\n", fs_dump__format_label_s(label), value, desc);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__hex16_desc(const char* label, u_int16_t value, const char* desc) {
    fs_debug_printf("%s0x%04" PRIx16 " %s\n", fs_dump__format_label_s(label), value, desc);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__hex8_desc(const char* label, u_int8_t value, const char* desc) {
    fs_debug_printf("%s0x%02" PRIx8  " %s\n", fs_dump__format_label_s(label), value, desc);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__hex16_dual8_desc2(const char* label, u_int8_t value1, u_int8_t value2, const char* desc1, const char* desc2) {
    fs_debug_printf("%s0x%02" PRIx8 "%02" PRIx8 " %s %s\n", fs_dump__format_label_s(label), value1, value2, desc1, desc2);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__hex16_dual8_desc(const char* label, u_int8_t value1, u_int8_t value2, const char* desc) {
    fs_debug_printf("%s0x%02" PRIx8 "%02" PRIx8 " %s\n", fs_dump__format_label_s(label), value1, value2, desc);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__int64_desc(const char* label, int64_t value, const char* desc) {
    fs_debug_printf("%s%" PRId64 " %s\n", fs_dump__format_label_s(label), value, desc);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__int32_desc(const char* label, int32_t value, const char* desc) {
    fs_debug_printf("%s%" PRId32 " %s\n", fs_dump__format_label_s(label), value, desc);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__int16_desc(const char* label, int16_t value, const char* desc) {
    fs_debug_printf("%s%" PRId16 " %s\n", fs_dump__format_label_s(label), value, desc);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__int8_desc(const char* label, int8_t value, const char* desc) {
    fs_debug_printf("%s%" PRId8 " %s\n", fs_dump__format_label_s(label), value, desc);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__uint64_desc(const char* label, u_int64_t value, const char* desc) {
    fs_debug_printf("%s%" PRIu64 " %s\n", fs_dump__format_label_s(label), value, desc);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__uint32_desc(const char* label, u_int32_t value, const char* desc) {
    fs_debug_printf("%s%" PRIu32 " %s\n", fs_dump__format_label_s(label), value, desc);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__uint16_desc(const char* label, u_int16_t value, const char* desc) {
    fs_debug_printf("%s%" PRIu16 " %s\n", fs_dump__format_label_s(label), value, desc);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__uint8_desc(const char* label, u_int8_t value, const char* desc) {
    fs_debug_printf("%s%" PRIu8 " %s\n", fs_dump__format_label_s(label), value, desc);
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__pcba32(const char* label, u_int32_t pcba) {
    char label_raw_unpadded[FS_DUMP__MAX_LABEL_LENGTH+1];
    char label_semantic_unpadded[FS_DUMP__MAX_LABEL_LENGTH+1];
    char label_raw[FS_DUMP__MAX_LABEL_LENGTH+1];
    char label_semantic[FS_DUMP__MAX_LABEL_LENGTH+1];

    snprintf(label_raw_unpadded, sizeof label_raw_unpadded, "%s [raw]", label);
    snprintf(label_semantic_unpadded, sizeof label_semantic_unpadded, "%s [semantic]", label);
    fs_dump__format_label_ex(label_raw, sizeof label_raw, FS_DUMP__INDENT_WIDTH, label_raw_unpadded, FS_DUMP__MIN_PAD_WIDTH, FS_DUMP__MAX_PAD_WIDTH, 0);
    fs_dump__format_label_ex(label_semantic, sizeof label_semantic, FS_DUMP__INDENT_WIDTH, label_semantic_unpadded, FS_DUMP__MIN_PAD_WIDTH, FS_DUMP__MAX_PAD_WIDTH, 0);

    if (pcba == 0xFFFFFFFF
     || pcba == 0x00FFFFFF
     || pcba == 0x0000FFFF
     || pcba == 0x000000FF
     || pcba == 0x00000000)
    {
        fs_debug_printf("%s" FS_DUMP__FORMAT_PCBA_RAW32 " " FS_DUMP__DESC_NOT_PROGRAMMED "\n", label_raw, FS_DUMP__BYTE_FIELDS_32(pcba));
    } else if ((pcba & 0x00FFFFFF) == 0x00FFFFFF) {
        /* 1 byte value + 3 0xFF's */
        fs_debug_printf("%s" FS_DUMP__FORMAT_PCBA_RAW32 " " FS_DUMP__DESC_1BYTE "\n", label_raw, FS_DUMP__BYTE_FIELDS_32(pcba));
        pcba = (pcba >> 24) & 0xFF;
        fs_debug_printf("%s" FS_DUMP__FORMAT_PCBA_REV "\n", label_semantic, pcba);
    } else if ((pcba & 0x0000FFFF) == 0x0000FFFF) {
        /* 2 byte value + 2 0xFF's */
        fs_debug_printf("%s" FS_DUMP__FORMAT_PCBA_RAW32 " " FS_DUMP__DESC_2BYTE "\n", label_raw, FS_DUMP__BYTE_FIELDS_32(pcba));
        pcba = (pcba >> 16) & 0xFFFF;
        fs_debug_printf("%s" FS_DUMP__FORMAT_PCBA_REV "\n", label_semantic, pcba);
    } else if ((pcba & 0xFFFFFF00) == 0x00000000) {
        /* 3 0x00's + one byte value */
        fs_debug_printf("%s" FS_DUMP__FORMAT_PCBA_RAW32 " " FS_DUMP__DESC_4BYTE "\n", label_raw, FS_DUMP__BYTE_FIELDS_32(pcba));
        fs_debug_printf("%s" FS_DUMP__FORMAT_PCBA_REV "\n", label_semantic, pcba);
    } else {
        u_int32_t part = (pcba >> 8) & 0xFFFFFF;
        u_int32_t rev  = (pcba & 0xff);
        fs_debug_printf("%s" FS_DUMP__FORMAT_PCBA_RAW32 "\n", label_raw, FS_DUMP__BYTE_FIELDS_32(pcba));
        fs_debug_printf("%s" FS_DUMP__FORMAT_PCBA "\n", label_semantic, part, rev);
    }
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__pcba16(const char* label, u_int16_t pcba) {
    char label_raw_unpadded[FS_DUMP__MAX_LABEL_LENGTH+1];
    char label_semantic_unpadded[FS_DUMP__MAX_LABEL_LENGTH+1];
    char label_raw[FS_DUMP__MAX_LABEL_LENGTH+1];
    char label_semantic[FS_DUMP__MAX_LABEL_LENGTH+1];

    snprintf(label_raw_unpadded, sizeof label_raw_unpadded, "%s [raw]", label);
    snprintf(label_semantic_unpadded, sizeof label_semantic_unpadded, "%s [semantic]", label);
    fs_dump__format_label_ex(label_raw, sizeof label_raw, FS_DUMP__INDENT_WIDTH, label_raw_unpadded, FS_DUMP__MIN_PAD_WIDTH, FS_DUMP__MAX_PAD_WIDTH, 0);
    fs_dump__format_label_ex(label_semantic, sizeof label_semantic, FS_DUMP__INDENT_WIDTH, label_semantic_unpadded, FS_DUMP__MIN_PAD_WIDTH, FS_DUMP__MAX_PAD_WIDTH, 0);

    if (pcba == 0xFFFF
     || pcba == 0x00FF
     || pcba == 0x0000)
    {
        fs_debug_printf("%s" FS_DUMP__FORMAT_PCBA_RAW16 " " FS_DUMP__DESC_NOT_PROGRAMMED "\n", label_raw, FS_DUMP__BYTE_FIELDS_16(pcba));
    }
    else if ((pcba & 0x00FF) == 0x00FF)
    {
        /* 1 byte value + 1 0xFF's */
        fs_debug_printf("%s" FS_DUMP__FORMAT_PCBA_RAW16 " " FS_DUMP__DESC_1BYTE "\n", label_raw, FS_DUMP__BYTE_FIELDS_16(pcba));
        fs_debug_printf("%s" FS_DUMP__FORMAT_PCBA_REV "\n", label_semantic, (pcba >> 8) & 0xFF);
    }
    else
    {
        /* */
        fs_debug_printf("%s" FS_DUMP__FORMAT_PCBA_RAW16 " " FS_DUMP__DESC_2BYTE "\n", label_raw, FS_DUMP__BYTE_FIELDS_16(pcba));
        fs_debug_printf("%s" FS_DUMP__FORMAT_PCBA_REV "\n", label_semantic, pcba & 0xFF);
    }
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump__version(const char* label, u_int32_t version, u_int8_t security_data_revision) {
    char label_raw_unpadded[FS_DUMP__MAX_LABEL_LENGTH+1];
    char label_semantic_unpadded[FS_DUMP__MAX_LABEL_LENGTH+1];
    char label_raw[FS_DUMP__MAX_LABEL_LENGTH+1];
    char label_semantic[FS_DUMP__MAX_LABEL_LENGTH+1];

    snprintf(label_raw_unpadded, sizeof label_raw_unpadded, "%s [raw]", label);
    snprintf(label_semantic_unpadded, sizeof label_semantic_unpadded, "%s [semantic]", label);
    fs_dump__format_label_ex(label_raw, sizeof label_raw, FS_DUMP__INDENT_WIDTH, label_raw_unpadded, FS_DUMP__MIN_PAD_WIDTH, FS_DUMP__MAX_PAD_WIDTH, 0);
    fs_dump__format_label_ex(label_semantic, sizeof label_semantic, FS_DUMP__INDENT_WIDTH, label_semantic_unpadded, FS_DUMP__MIN_PAD_WIDTH, FS_DUMP__MAX_PAD_WIDTH, 0);

    if (version == 0xFFFFFFFF) {
        fs_debug_printf("%s%s\n", label_raw,      FS_DUMP__DESC_NOT_PROGRAMMED);
        fs_debug_printf("%s%s\n", label_semantic, FS_DUMP__DESC_NOT_PROGRAMMED);
    } else if (version == 0x00000000) {
        fs_dump__unsupported(label_raw_unpadded,      security_data_revision);
        fs_dump__unsupported(label_semantic_unpadded, security_data_revision);
    } else {
        fs_debug_printf("%s" FS_DUMP__FORMAT_VERSION_RAW32 "\n", label_raw, FS_DUMP__BYTE_FIELDS_32(version));
        fs_debug_printf("%s" FS_DUMP__FORMAT_VERSION_LOGICAL "\n", label_semantic, FS_DUMP__BYTE_FIELDS_VERSION(version));
    }
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE const char* fs_dump__get_security_data_format_desc(u_int8_t format) {
    switch(format) {
    CASE_DATA_FORMAT_AIRFIBER           ( return FS_DUMP__FORMAT_DESC_AIRFIBER;           )
    CASE_DATA_FORMAT_BCMSWITCH          ( return FS_DUMP__FORMAT_DESC_BCMSWITCH;          )
    CASE_DATA_FORMAT_CLOUDKEY           ( return FS_DUMP__FORMAT_DESC_CLOUDKEY;           )
    CASE_DATA_FORMAT_BCMWIFI            ( return FS_DUMP__FORMAT_DESC_BCMWIFI;            )
    CASE_DATA_FORMAT_CAMERA             ( return FS_DUMP__FORMAT_DESC_CAMERA;             )
    CASE_DATA_FORMAT_CAMERA2            ( return FS_DUMP__FORMAT_DESC_CAMERA2;            )
    CASE_DATA_FORMAT_INVALID            ( return FS_DUMP__FORMAT_DESC_NOT_VALID;          )
    CASE_DATA_FORMAT_INVERTER           ( return FS_DUMP__FORMAT_DESC_INVERTER;           )
    CASE_DATA_FORMAT_MISSING            ( return FS_DUMP__FORMAT_DESC_MISSING;            )
    CASE_DATA_FORMAT_NVR                ( return FS_DUMP__FORMAT_DESC_NVR;                )
    CASE_DATA_FORMAT_QCASWITCH          ( return FS_DUMP__FORMAT_DESC_QCASWITCH;          )
    CASE_DATA_FORMAT_ROUTER             ( return FS_DUMP__FORMAT_DESC_ROUTER;             )
    CASE_DATA_FORMAT_SOLARGATEWAY       ( return FS_DUMP__FORMAT_DESC_SOLARGATEWAY;       )
    CASE_DATA_FORMAT_SWITCH             ( return FS_DUMP__FORMAT_DESC_SWITCH;             )
    CASE_DATA_FORMAT_BASIC              ( return FS_DUMP__FORMAT_DESC_BASIC;              )
    CASE_DATA_FORMAT_BASIC4K            ( return FS_DUMP__FORMAT_DESC_BASIC4K;            )
    CASE_DATA_FORMAT_UNIVOX             ( return FS_DUMP__FORMAT_DESC_UNIVOX;             )
    CASE_DATA_FORMAT_WIFI_DIGITAL_BOARD ( return FS_DUMP__FORMAT_DESC_WIFI_DIGITAL_BOARD; )
    CASE_DATA_FORMAT_WIFI_DUAL_RF       ( return FS_DUMP__FORMAT_DESC_WIFI_DUAL_RF;       )
    CASE_DATA_FORMAT_WIFI_FLASH         ( return FS_DUMP__FORMAT_DESC_WIFI_FLASH;         )
    CASE_DATA_FORMAT_WIFI_RADIO_EEPROM  ( return FS_DUMP__FORMAT_DESC_WIFI_RADIO_EEPROM;  )
    default:                              return FS_DUMP__FORMAT_DESC_NOT_RECOGNIZED;
    }
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE const char* fs_dump__get_product_class_desc(u_int16_t product_class_id) {
    switch (product_class_id) {
    CASE_PRODUCT_CLASS_ID_AIRFIBER               ( return FS_DUMP__PRODUCT_CLASS_DESC_AIRFIBER;           )
    CASE_PRODUCT_CLASS_ID_BCMSWITCH              ( return FS_DUMP__PRODUCT_CLASS_DESC_BCMSWITCH;          )
    CASE_PRODUCT_CLASS_ID_CLOUDKEY               ( return FS_DUMP__PRODUCT_CLASS_DESC_CLOUDKEY;           )
    CASE_PRODUCT_CLASS_ID_BCMWIFI                ( return FS_DUMP__PRODUCT_CLASS_DESC_BCMWIFI;            )
    CASE_PRODUCT_CLASS_ID_CAMERA                 ( return FS_DUMP__PRODUCT_CLASS_DESC_CAMERA;             )
    CASE_PRODUCT_CLASS_ID_CAMERA2                ( return FS_DUMP__PRODUCT_CLASS_DESC_CAMERA2;            )
    CASE_PRODUCT_CLASS_ID_DIGITAL_BOARD          ( return FS_DUMP__PRODUCT_CLASS_DESC_DIGITAL_BOARD;      )
    CASE_PRODUCT_CLASS_ID_INVALID                ( return FS_DUMP__PRODUCT_CLASS_DESC_INVALID;            )
    CASE_PRODUCT_CLASS_ID_INVERTER               ( return FS_DUMP__PRODUCT_CLASS_DESC_INVERTER;           )
    CASE_PRODUCT_CLASS_ID_LEGACY                 ( return FS_DUMP__PRODUCT_CLASS_DESC_LEGACY;             )
    CASE_PRODUCT_CLASS_ID_MISSING                ( return FS_DUMP__PRODUCT_CLASS_DESC_MISSING;            )
    CASE_PRODUCT_CLASS_ID_NVR                    ( return FS_DUMP__PRODUCT_CLASS_DESC_NVR;                )
    CASE_PRODUCT_CLASS_ID_QCASWITCH              ( return FS_DUMP__PRODUCT_CLASS_DESC_QCASWITCH;          )
    CASE_PRODUCT_CLASS_ID_RADIO                  ( return FS_DUMP__PRODUCT_CLASS_DESC_RADIO;              )
    CASE_PRODUCT_CLASS_ID_RF_BOARD               ( return FS_DUMP__PRODUCT_CLASS_DESC_RF_BOARD;           )
    CASE_PRODUCT_CLASS_ID_RF_BOARD_DUAL          ( return FS_DUMP__PRODUCT_CLASS_DESC_RF_BOARD_DUAL;      )
    CASE_PRODUCT_CLASS_ID_ROUTER                 ( return FS_DUMP__PRODUCT_CLASS_DESC_ROUTER;             )
    CASE_PRODUCT_CLASS_ID_SAMPLE                 ( return FS_DUMP__PRODUCT_CLASS_DESC_SAMPLE;             )
    CASE_PRODUCT_CLASS_ID_SWITCH                 ( return FS_DUMP__PRODUCT_CLASS_DESC_SWITCH;             )
    CASE_PRODUCT_CLASS_ID_BASIC                  ( return FS_DUMP__PRODUCT_CLASS_DESC_BASIC;              )
    CASE_PRODUCT_CLASS_ID_BASIC4K                ( return FS_DUMP__PRODUCT_CLASS_DESC_BASIC4K;            )
    CASE_PRODUCT_CLASS_ID_UNIVOX                 ( return FS_DUMP__PRODUCT_CLASS_DESC_UNIVOX;             )
    CASE_PRODUCT_CLASS_ID_SOLARGATEWAY           ( return FS_DUMP__PRODUCT_CLASS_DESC_SOLARGATEWAY;       )
    default:                                       return FS_DUMP__PRODUCT_CLASS_DESC_NOT_RECOGNIZED;
    }
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump(void) {
    __FS_LOCAL_STATIC_OPTION fs_dump_everything_data_t* fsv_t1;

    fsv_t1 = (fs_dump_everything_data_t*)fs_malloc(sizeof(fs_dump_everything_data_t));
    if (NULL == fsv_t1) {
        goto done;
    }
    fs_debug_printf("\n\n[SECURITY DATA]\n" );
    memset(fsv_t1,0xff,sizeof(*fsv_t1));
    fsv_failure_index = SET_VAR(0);  \
    fsv_failure       = SET_VAR_OK(); \
    fsv_t1->secinfo_exists          = 0;
    fsv_t1->boardinfo_exists        = 0;
    fsv_t1->flash_uid_len_sec       = 0;
    fsv_t1->mfg_timestamp           = 0;
    fsv_t1->flash_uid_len_hw        = 0;
    fs_output_off(); fsv_t1->security_data_format_sec       = fs_read_security_data_format_sec();       fs_output_on();
    fs_output_off(); fsv_t1->security_data_revision_sec     = fs_read_security_data_revision_sec();     fs_output_on();
    fs_output_off(); fsv_t1->security_data_revision_raw_sec = fs_read_security_data_revision_raw_sec(); fs_output_on();
    if (FS_LOWLEVEL_ERRORS) {
        fs_dump__string("security_data_format_sec", "0x???? [UNREADABLE]");
        fsv_failure       = SET_VAR_OK(); \
    } else {
        switch (fsv_t1->security_data_format_sec) {
            CASE_SUPPORTED_FORMATS
                fsv_t1->secinfo_exists = 1;
                fs_dump__hex16_dual8_desc2(
                    "security_data_format_sec"
                     , fsv_t1->security_data_format_sec
                     , fsv_t1->security_data_revision_sec
                     , fs_dump__get_security_data_format_desc(fsv_t1->security_data_format_sec)
                     , (fsv_t1->security_data_revision_sec != fsv_t1->security_data_revision_raw_sec) ? "[REV WAR] [RECOGNIZED]" : "[RECOGNIZED]"
                    );
                fs_dump__hex8_desc("security_format_sec", fsv_t1->security_data_format_sec, fs_dump__get_security_data_format_desc(fsv_t1->security_data_format_sec));
                fs_dump__int32("security_revision_sec", fsv_t1->security_data_revision_sec);
                break;
            case FS_SECURITY_DATA_FORMAT_BLANK:
                fs_dump__hex16_dual8_desc("security_data_format_sec", fsv_t1->security_data_format_sec, fsv_t1->security_data_revision_raw_sec, "[BLANK]");
                break;
            default:
                fs_dump__hex16_dual8_desc("security_data_format_sec", fsv_t1->security_data_format_sec, fsv_t1->security_data_revision_raw_sec, "[UNRECOGNIZED]");
                fs_dump__hex8_desc("security_format_sec", fsv_t1->security_data_format_sec, fs_dump__get_security_data_format_desc(fsv_t1->security_data_format_sec));
                fs_dump__int32_desc("security_revision_sec", fsv_t1->security_data_revision_sec, "????");
                goto done;/* for non-fail mode */
        }
    }
    fsv_t1->boardinfo_exists        = fs_file_exists_bi();
    fsv_t1->flash_uid_len_hw        = fs_read_flash_uid_hw(fsv_t1->flash_uid_hw, sizeof fsv_t1->flash_uid_hw);
    fsv_t1->flash_uid_len_sec       = fs_read_flash_uid_sec(fsv_t1->flash_uid_sec, sizeof fsv_t1->flash_uid_sec);
    fs_read_eth0_mac_address_hw     ( fsv_t1->eth0_mac_address_hw, sizeof fsv_t1->eth0_mac_address_hw  );
    fs_read_eth1_mac_address_hw     ( fsv_t1->eth1_mac_address_hw, sizeof fsv_t1->eth1_mac_address_hw  );
    if (fsv_t1->secinfo_exists) {
        fs_read_ubnt_signature_sec     ( fsv_t1->ubnt_signature_sec   , sizeof fsv_t1->ubnt_signature_sec   );
#if SECURITY_ENABLE_ESN_SIGNATURE_CHECKS
        fs_read_esn_sig_iv_area_sec    ( fsv_t1->esn_sig_iv_area_sec  , sizeof fsv_t1->esn_sig_iv_area_sec  );
        fs_read_esn_signature_sec      ( fsv_t1->esn_signature_sec    , sizeof fsv_t1->esn_signature_sec    );
#endif // #if SECURITY_ENABLE_ESN_SIGNATURE_CHECKS
        fs_read_eth0_mac_address_sec   ( fsv_t1->eth0_mac_address_sec, sizeof fsv_t1->eth0_mac_address_sec );
        fs_read_eth1_mac_address_sec   ( fsv_t1->eth1_mac_address_sec, sizeof fsv_t1->eth1_mac_address_sec );
        fsv_t1->mfg_timestamp = fs_read_registration_timestamp_sec();
    }

    if (fsv_t1->secinfo_exists) {
        fs_dump__uint16("manufacturer_id_sec", fs_read_manufacturer_id_sec());
        fs_dump__uint64("device_id_sec", fs_read_device_id_sec());
        fs_dump__uint64("registration_id_sec", fs_read_registration_id_sec());
        fs_dump__timestamp64("registration_timestamp_sec", fs_read_registration_timestamp_sec());
        fs_dump__hex16_desc("product_class_id_sec", fs_read_product_class_id_sec(), fs_dump__get_product_class_desc(fs_read_product_class_id_sec()));
        fs_dump__hex16("subsystem_id_sec", fs_read_subsystem_id_sec());
    }
    if(fs_has_subsystem_id_fbd()) {
        fs_dump__hex16("subsystem_id_fbd", fs_read_subsystem_id_fbd());
    }
    if (fsv_t1->boardinfo_exists && fs_has_system_id_bi()) {
        u_int16_t subsystem_id_bi = 0;
        fs_output_off();
        subsystem_id_bi = fs_read_system_id_bi();
        fs_output_on();
        fs_dump__hex16("subsystem_id_bi", subsystem_id_bi);
    }
    if (fsv_t1->secinfo_exists) {
        fs_dump__hex16("subvendor_id_sec", fs_read_subvendor_id_sec());
    }
    if (fs_has_subvendor_id_fbd()) {
        fs_dump__hex16("subvendor_id_fbd", fs_read_subvendor_id_fbd());
    }
    if (fsv_t1->boardinfo_exists && fs_has_vendor_id_bi()) {
        u_int16_t subvendor_id_bi = 0;
        fs_output_off();
        subvendor_id_bi = fs_read_vendor_id_bi();
        fs_output_on();
        fs_dump__hex16("subvendor_id_bi", subvendor_id_bi);
    }
    if (fsv_t1->secinfo_exists) {
        fs_dump__hex("eth0_mac_address_sec", fsv_t1->eth0_mac_address_sec, MAC_ADDRESS_SIZE);
    }
    fs_read_eth0_mac_address_fbd(fsv_t1->eth0_mac_address_fbd, MAC_ADDRESS_SIZE);
    fs_dump__hex("eth0_mac_address_fbd", fsv_t1->eth0_mac_address_fbd, MAC_ADDRESS_SIZE);
    if (fsv_t1->boardinfo_exists && fs_has_eth0_mac_address_bi()) {
        fs_output_off();
        fs_read_eth0_mac_address_bi(fsv_t1->eth0_mac_address_bi, MAC_ADDRESS_SIZE);
        fs_output_on();
        fs_dump__hex("eth0_mac_address_bi", fsv_t1->eth0_mac_address_bi, MAC_ADDRESS_SIZE);
    }
    fs_dump__hex("eth0_mac_address_hw", fsv_t1->eth0_mac_address_hw,  MAC_ADDRESS_SIZE);
    if (fsv_t1->security_data_format_sec != FS_SECURITY_DATA_FORMAT_QCASWITCH
        && fsv_t1->security_data_format_sec != FS_SECURITY_DATA_FORMAT_BCMSWITCH
        && fsv_t1->security_data_format_sec != FS_SECURITY_DATA_FORMAT_CLOUDKEY)
    {
        if (fsv_t1->secinfo_exists) {
            fs_dump__hex("eth1_mac_address_sec", fsv_t1->eth1_mac_address_sec, MAC_ADDRESS_SIZE);
        }
        fs_read_eth1_mac_address_fbd(fsv_t1->eth1_mac_address_fbd, MAC_ADDRESS_SIZE);
        fs_dump__hex("eth1_mac_address_fbd", fsv_t1->eth1_mac_address_fbd, MAC_ADDRESS_SIZE);
        if (fsv_t1->boardinfo_exists && fs_has_eth1_mac_address_bi()) {
            fs_output_off();
            fs_read_eth1_mac_address_bi(fsv_t1->eth1_mac_address_bi, MAC_ADDRESS_SIZE);
            fs_output_on();
            fs_dump__hex("eth1_mac_address_bi", fsv_t1->eth1_mac_address_bi, MAC_ADDRESS_SIZE);
        }
        fs_dump__hex("eth1_mac_address_hw", fsv_t1->eth1_mac_address_hw,  MAC_ADDRESS_SIZE);
    }
    if (fsv_t1->secinfo_exists) {
        fs_dump__hex24("flash_type_id_sec", fs_read_flash_type_id_sec());
    }
    fs_dump__hex24("flash_type_id_hw", fs_read_flash_type_id_hw());
    if (fsv_t1->secinfo_exists) {
        fs_dump__uint32("flash_uid_length_sec", fsv_t1->flash_uid_len_sec);
    }
    fs_dump__uint32("flash_uid_length_hw", fsv_t1->flash_uid_len_hw);
    if (fsv_t1->secinfo_exists) {
        fs_dump__hex("flash_uid_sec", fsv_t1->flash_uid_sec, fsv_t1->flash_uid_len_sec);
    }
    fs_dump__hex("flash_uid_hw", fsv_t1->flash_uid_hw,  fsv_t1->flash_uid_len_hw);

/*
Special case - not calibrated but we can figure out it's a radio...
*/
    if (!fsv_t1->secinfo_exists) {
        if (fsv_t1->boardinfo_exists) {
            fs_output_off();
/*
Set the format based on whether it's an Atheros board or an AirFiber board.
*/
#ifdef UBNT_MIPS_ARxxxx
            if (0 != fs_read_wifi_radio1_subsystem_id_bi()) {
                fsv_t1->security_data_format_sec = FS_SECURITY_DATA_FORMAT_WIFI_FLASH;
            }
#endif // #ifdef UBNT_MIPS_ARxxxx
#ifdef UBNT_ARM_AM18xx
            fsv_t1->security_data_format_sec = FS_SECURITY_DATA_FORMAT_AIRFIBER;
#endif // #ifdef UBNT_ARM_AM18xx
#ifdef UBNT_ARM_AM3xxx
            fsv_t1->security_data_format_sec = FS_SECURITY_DATA_FORMAT_UNIVOX;
#endif // #ifdef UBNT_ARM_AM3xxx
#ifdef UBNT_ARM_BCM111xx
            fsv_t1->security_data_format_sec = FS_SECURITY_DATA_FORMAT_UNIVOX;
#endif // #ifdef UBNT_ARM_BCM111xx
#ifdef UBNT_ARM_MT8117
            fsv_t1->security_data_format_sec = FS_SECURITY_DATA_FORMAT_UNIVOX;
#endif // #ifdef UBNT_ARM_MT8117
            fs_output_on();
        }
    }
    switch (fsv_t1->security_data_format_sec) {
    case FS_SECURITY_DATA_FORMAT_WIFI_DIGITAL_BOARD:
    case FS_SECURITY_DATA_FORMAT_WIFI_RADIO_EEPROM:
#ifndef UBNT_SUPPORT_CLASS_WIFI
        fs_dump__error("No support for product class wifi on this platform.");
#endif
        goto done;
    case FS_SECURITY_DATA_FORMAT_WIFI_FLASH:
#ifdef UBNT_SUPPORT_CLASS_WIFI
        {
            if (fsv_t1->secinfo_exists) {
                fsv_t1->wifi_radio1_mac_rev_sec = fs_read_wifi_radio1_mac_rev_id_sec();
                fsv_t1->wifi_radio2_mac_rev_sec = fs_read_wifi_radio2_mac_rev_id_sec();
                fs_read_wifi_radio1_mac_address_sec ( fsv_t1->wifi_radio1_mac_address_sec, sizeof fsv_t1->wifi_radio1_mac_address_sec );
                fs_read_wifi_radio2_mac_address_sec ( fsv_t1->wifi_radio2_mac_address_sec, sizeof fsv_t1->wifi_radio2_mac_address_sec );
                fs_dump__hex32_desc("wifi_cpu_rev_id_sec", fs_read_wifi_cpu_rev_id_sec(), fs_identify_wifi_cpu_family(fs_read_wifi_cpu_rev_id_sec()));
            }
            if (fsv_t1->boardinfo_exists) {
                if (fs_has_cpu_rev_id_bi()) {
                    u_int32_t   cpu_rev_id_bi;
                    const char* cpu_rev_id_bi_family;
                    fs_output_off();
                    cpu_rev_id_bi = fs_read_cpu_rev_id_bi();
                    cpu_rev_id_bi_family = fs_identify_wifi_cpu_family(cpu_rev_id_bi);
                    fs_output_on();
                    fs_dump__hex32_desc("cpu_rev_id_bi", cpu_rev_id_bi, cpu_rev_id_bi_family);
                } else {
/* NB: Pre-5.5 firmware did not generate this key */
                    fs_dump__string("cpu_rev_id_bi", FS_DUMP__DESC_NOT_SPECIFIED);
                }
            }
            fs_dump__hex32_desc("wifi_cpu_rev_id_hw", fs_read_cpu_rev_id_hw(), fs_identify_wifi_cpu_family(fs_read_cpu_rev_id_hw()));
            fs_output_off();
            fsv_t1->wifi_radio1_mac_rev_hw = fs_read_wifi_radio1_mac_rev_id_hw();
            fs_output_on();
            if (fsv_t1->wifi_radio1_mac_rev_sec != 0xffffffff || fsv_t1->wifi_radio1_mac_rev_hw != 0x0) {
                fs_read_wifi_radio1_mac_address_hw( fsv_t1->wifi_radio1_mac_address_hw, sizeof fsv_t1->wifi_radio1_mac_address_hw );
                if (fsv_t1->boardinfo_exists) {
                    u_int16_t radio1_subvendor_id_bi = 0;
                    u_int16_t radio1_subsystem_id_bi = 0;
                    fs_output_off();
                    fs_read_hwaddr_bi( fsv_t1->hwaddr_bi, sizeof fsv_t1->hwaddr_bi );
                    radio1_subvendor_id_bi = fs_read_wifi_radio1_subvendor_id_bi();
                    radio1_subsystem_id_bi = fs_read_wifi_radio1_subsystem_id_bi();
                    fs_output_on();
                    fs_dump__hex16("wifi_radio1_subvendor_id_bi", radio1_subvendor_id_bi);
                    fs_dump__hex16("wifi_radio1_subsystem_id_bi", radio1_subsystem_id_bi);
                }
                if (fsv_t1->secinfo_exists) {
                    fs_dump__hex32("wifi_radio1_mac_rev_id_sec", fsv_t1->wifi_radio1_mac_rev_sec);
                }
                fs_dump__hex32("wifi_radio1_mac_rev_id_hw", fsv_t1->wifi_radio1_mac_rev_hw);
                if (fsv_t1->secinfo_exists) {
                    fs_dump__hex("wifi_radio1_mac_address_sec", fsv_t1->wifi_radio1_mac_address_sec, sizeof fsv_t1->wifi_radio1_mac_address_sec );
                }
                fs_dump__hex("wifi_radio1_mac_address_hw", fsv_t1->wifi_radio1_mac_address_hw, MAC_ADDRESS_SIZE);
                if (fsv_t1->boardinfo_exists) {
                    fs_dump__hex("hwaddr_bi", fsv_t1->hwaddr_bi, sizeof fsv_t1->hwaddr_bi);
                }
            }
            fs_output_off();
            fsv_t1->wifi_radio2_mac_rev_hw = fs_read_wifi_radio2_mac_rev_id_hw();
            fs_output_on();
            if (fsv_t1->wifi_radio2_mac_rev_sec != 0xffffffff || fsv_t1->wifi_radio2_mac_rev_hw != 0x0) {
                fs_read_wifi_radio2_mac_address_hw( fsv_t1->wifi_radio2_mac_address_hw, sizeof fsv_t1->wifi_radio2_mac_address_hw );
                if (fsv_t1->boardinfo_exists) {
                    u_int16_t radio2_subvendor_id_bi = 0;
                    u_int16_t radio2_subsystem_id_bi = 0;
                    fs_output_off();
                    radio2_subvendor_id_bi = fs_read_wifi_radio2_subvendor_id_bi();
                    radio2_subsystem_id_bi = fs_read_wifi_radio2_subsystem_id_bi();
                    fs_output_on();
                    fs_dump__hex16("wifi_radio2_subvendor_id_bi", radio2_subvendor_id_bi);
                    fs_dump__hex16("wifi_radio2_subsystem_id_bi", radio2_subsystem_id_bi);
                }
                if (fsv_t1->secinfo_exists) {
                    fs_dump__hex32("wifi_radio2_mac_rev_id_sec", fsv_t1->wifi_radio2_mac_rev_sec);
                }
                fs_dump__hex32("wifi_radio2_mac_rev_id_hw", fsv_t1->wifi_radio2_mac_rev_hw);
                if (fsv_t1->secinfo_exists) {
                    fs_dump__hex("wifi_radio2_mac_address_sec", fsv_t1->wifi_radio2_mac_address_sec, sizeof fsv_t1->wifi_radio2_mac_address_sec);
                }
                fs_dump__hex("wifi_radio2_mac_address_hw", fsv_t1->wifi_radio2_mac_address_hw, MAC_ADDRESS_SIZE);
            }
        }
#else // #ifdef UBNT_SUPPORT_CLASS_WIFI
        fs_dump__error("No support for product class wifi on this platform.");
        goto done;
#endif // #ifdef UBNT_SUPPORT_CLASS_WIFI
        break;
    case FS_SECURITY_DATA_FORMAT_CAMERA:
#ifdef UBNT_SUPPORT_CLASS_CAMERA
        {
            if (fsv_t1->secinfo_exists) {
                fs_dump__hex32("camera_eth_mac_rev_id_sec", fs_read_camera_eth_mac_rev_id_sec());
            }
            fs_dump__hex32("GM81xx_eth_mac_rev_id_hw", fs_read_GM81xx_eth_mac_rev_id_hw());
            if (fsv_t1->secinfo_exists) {
                fs_dump__hex32("camera_ahb_rev_id_sec", fs_read_camera_ahb_rev_id_sec());
            }
            fs_dump__hex32("GM81xx_ahb_rev_id_hw", fs_read_GM81xx_ahb_rev_id_hw());
            if (fsv_t1->secinfo_exists) {
                fs_dump__hex32("camera_gpio_summary_id_sec", fs_read_camera_gpio_summary_id_sec());
            }
            fs_dump__hex32("GM81xx_gpio_summary_id_hw", fs_read_GM81xx_gpio_summary_id_hw());
            if (fsv_t1->secinfo_exists) {
                fs_dump__hex32("camera_i2c_ctrl_rev_id_sec", fs_read_camera_i2c_controller_rev_id_sec());
            }
            fs_dump__hex32("GM81xx_i2c_ctrl_rev_id_hw", fs_read_GM81xx_i2c_controller_rev_id_hw());
            if (fsv_t1->secinfo_exists) {
                fs_dump__hex32("camera_int_ctl_summary_id_sec", fs_read_camera_int_controller_summary_id_sec());
            }
            fs_dump__hex32("GM81xx_int_ctrl_summary_id_hw", fs_read_GM81xx_int_controller_summary_id_hw());
            if (fsv_t1->secinfo_exists) {
                fs_dump__hex32("camera_sd_card_rdr_rev_id_sec", fs_read_camera_sd_card_reader_rev_id_sec());
            }
            fs_dump__hex32("GM81xx_sd_card_rdr_rev_id_hw", fs_read_GM81xx_sd_card_reader_rev_id_hw());
            if (fsv_t1->secinfo_exists) {
                fs_dump__hex32("camera_timer_summary_id_sec", fs_read_camera_timer_summary_id_sec());
            }
            fs_dump__hex32("GM81xx_timer_summary_id_hw", fs_read_GM81xx_timer_summary_id_hw());
        }
#else // #ifdef UBNT_SUPPORT_CLASS_CAMERA
        fs_dump__error("No support for product class camera on this platform.");
        goto done;
#endif // #ifdef UBNT_SUPPORT_CLASS_CAMERA
        break;
    case FS_SECURITY_DATA_FORMAT_CAMERA2:
#ifdef UBNT_SUPPORT_CLASS_CAMERA2
        {
            if (fsv_t1->secinfo_exists) {
                fs_dump__hex32("camera2_ssi_ident_id_sec", fs_read_camera2_ssi_ident_id_sec());
            }
            fs_dump__hex32("AMBA_ssi_ident_id_hw", fs_read_AMBA_ssi_ident_id_hw());
            if (fsv_t1->secinfo_exists) {
                fs_dump__hex32("camera2_ssi_version_id_sec", fs_read_camera2_ssi_version_id_sec());
            }
            fs_dump__hex32("AMBA_ssi_version_id_hw", fs_read_AMBA_ssi_version_id_hw());
        }
#else // #ifdef UBNT_SUPPORT_CLASS_CAMERA2
        fs_dump__error("No support for product class camera2 on this platform.");
        goto done;
#endif // #ifdef UBNT_SUPPORT_CLASS_CAMERA2
        break;
    case FS_SECURITY_DATA_FORMAT_SWITCH:
#ifdef UBNT_SUPPORT_CLASS_SWITCH
        {
            if (fsv_t1->secinfo_exists) {
                fs_dump__hex32("switch_cpu_rev_id_sec", fs_read_switch_cpu_rev_id_sec());
            }
            if (fsv_t1->boardinfo_exists) {
                u_int32_t cpu_rev_id_bi = 0;
                fs_output_off();
                cpu_rev_id_bi = fs_read_cpu_rev_id_bi();
                fs_output_on();
                fs_dump__hex32("cpu_rev_id_bi", cpu_rev_id_bi);
            }
            fs_dump__hex32("cpu_rev_id_hw", fs_read_cpu_rev_id_hw());
        }
#else // #ifdef UBNT_SUPPORT_CLASS_SWITCH
        fs_dump__error("No support for product class switch on this platform.");
        goto done;
#endif // #ifdef UBNT_SUPPORT_CLASS_SWITCH
        break;
    case FS_SECURITY_DATA_FORMAT_BASIC:
#ifdef UBNT_SUPPORT_CLASS_BASIC
        {
            if (fsv_t1->secinfo_exists) {
                fs_dump__hex32("cpu_rev_id_sec", fs_read_basic_cpu_rev_id_sec());
            }
            if (fsv_t1->boardinfo_exists) {
                u_int32_t cpu_rev_id_bi = 0;
                fs_output_off();
                cpu_rev_id_bi = fs_read_cpu_rev_id_bi();
                fs_output_on();
                fs_dump__hex32("cpu_rev_id_bi", cpu_rev_id_bi);
            }
            fs_dump__hex32("cpu_rev_id_hw", fs_read_cpu_rev_id_hw());
        }
#else // #ifdef UBNT_SUPPORT_CLASS_BASIC
        fs_dump__error("No support for product class basic on this platform.");
        goto done;
#endif // #ifdef UBNT_SUPPORT_CLASS_BASIC
        break;
    case FS_SECURITY_DATA_FORMAT_BASIC4K:
#ifdef UBNT_SUPPORT_CLASS_BASIC4K
        {
            if (fsv_t1->secinfo_exists) {
                fs_dump__hex32("cpu_rev_id_sec", fs_read_basic4k_cpu_rev_id_sec());
            }
            if (fsv_t1->boardinfo_exists) {
                u_int32_t cpu_rev_id_bi = 0;
                fs_output_off();
                cpu_rev_id_bi = fs_read_cpu_rev_id_bi();
                fs_output_on();
                fs_dump__hex32("cpu_rev_id_bi", cpu_rev_id_bi);
            }
            fs_dump__hex32("cpu_rev_id_hw", fs_read_cpu_rev_id_hw());
        }
#else // #ifdef UBNT_SUPPORT_CLASS_BASIC4K
        fs_dump__error("No support for product class basic4k on this platform.");
        goto done;
#endif // #ifdef UBNT_SUPPORT_CLASS_BASIC4K
        break;
    case FS_SECURITY_DATA_FORMAT_ROUTER:
#ifdef UBNT_SUPPORT_CLASS_ROUTER
        {
            if (fsv_t1->secinfo_exists) {
                fs_dump__hex32("router_cpu_rev_id_sec", fs_read_router_cpu_rev_id_sec());
            }
            fs_dump__hex32("cpu_rev_id_hw", fs_read_cpu_rev_id_hw());
            if (fsv_t1->boardinfo_exists) {
                fs_dump__hex32("cpu_rev_id_bi", fs_read_cpu_rev_id_bi());
            }
            if (IS_MEDIATEK_ROUTER_SSID(fs_read_subsystem_id_sec()) || (fs_has_subsystem_id_fbd() && IS_MEDIATEK_ROUTER_SSID(fs_read_subsystem_id_fbd()))) {
                fs_read_router_vpd_fbd(fsv_t1->router_vpd_fbd, sizeof fsv_t1->router_vpd_fbd);
                fs_dump__hex_truncated("router_vpd_fbd", fsv_t1->router_vpd_fbd, sizeof fsv_t1->router_vpd_fbd);
                fs_read_router_vpd_sec(fsv_t1->router_vpd_sec, sizeof fsv_t1->router_vpd_sec);
                fs_dump__hex_truncated("router_vpd_sec", fsv_t1->router_vpd_sec, sizeof fsv_t1->router_vpd_sec);
            }
        }
#else // #ifdef UBNT_SUPPORT_CLASS_ROUTER
        fs_dump__error("No support for product class router on this platform.");
        goto done;
#endif // #ifdef UBNT_SUPPORT_CLASS_ROUTER
        break;
    case FS_SECURITY_DATA_FORMAT_SOLARGATEWAY:
#ifdef UBNT_SUPPORT_CLASS_SOLARGATEWAY
        {
            if (fsv_t1->secinfo_exists) {
                fs_dump__hex32("solargateway_cpu_rev_id_sec", fs_read_solargateway_cpu_rev_id_sec());
            }
            fs_dump__hex32("cpu_rev_id_hw", fs_read_cpu_rev_id_hw());
            if (fsv_t1->boardinfo_exists) {
                fs_dump__hex32("cpu_rev_id_bi", fs_read_cpu_rev_id_bi());
            }
        }
#else // #ifdef UBNT_SUPPORT_CLASS_SOLARGATEWAY
        fs_dump__error("No support for product class solargateway on this platform.");
        goto done;
#endif // #ifdef UBNT_SUPPORT_CLASS_SOLARGATEWAY
        break;
    case FS_SECURITY_DATA_FORMAT_NVR:
#ifdef UBNT_SUPPORT_CLASS_NVR
        {
            // Nothing NVR-specific here
        }
#else // #ifdef UBNT_SUPPORT_CLASS_NVR
        fs_dump__error("No support for product class nvr on this platform.");
        goto done;
#endif // #ifdef UBNT_SUPPORT_CLASS_NVR
        break;
    case FS_SECURITY_DATA_FORMAT_BCMWIFI:
#ifdef UBNT_SUPPORT_CLASS_BCMWIFI
        {
            if (fsv_t1->secinfo_exists) {
                fs_dump__hex32("bcmwifi_cpu_rev_id_sec", fs_read_bcmwifi_cpu_rev_id_sec());
            }
            fs_dump__hex32("BCM4706_cpu_rev_id_hw", fs_read_BCM4706_cpu_rev_id_hw());
        }
        {
            if (fsv_t1->secinfo_exists) {
                fs_dump__hex32("bcmwifi_wifi_radio1_id_sec", fs_read_bcmwifi_wifi_radio1_id_sec());
            }
            fs_dump__hex32("BCM4706_wifi_radio1_mac_id_hw", fs_read_BCM4706_wifi_radio1_id_hw());
            if (fsv_t1->boardinfo_exists) {
                fs_dump__hex32("bcmwifi_wifi_radio1_id_bi", fs_read_wifi_radio1_id_bi());
                fs_dump__hex16("bcmwifi_wifi_radio1_vendor_id_bi", fs_read_wifi_radio1_vendor_id_bi());
                fs_dump__hex16("bcmwifi_wifi_radio1_device_id_bi", fs_read_wifi_radio1_device_id_bi());
            }
        }
        {
            if (fsv_t1->secinfo_exists) {
                fs_dump__hex32("bcmwifi_wifi_radio2_id_sec", fs_read_bcmwifi_wifi_radio2_id_sec());
            }
            fs_dump__hex32("BCM4706_wifi_radio2_mac_id_hw", fs_read_BCM4706_wifi_radio2_id_hw());
            if (fsv_t1->boardinfo_exists) {
                fs_dump__hex32("bcmwifi_wifi_radio2_id_bi", fs_read_wifi_radio2_id_bi());
                fs_dump__hex16("bcmwifi_wifi_radio2_vendor_id_bi", fs_read_wifi_radio2_vendor_id_bi());
                fs_dump__hex16("bcmwifi_wifi_radio2_device_id_bi", fs_read_wifi_radio2_device_id_bi());
            }
        }
        {
            fs_read_BCM4706_wifi_radio1_mac_address_hw( fsv_t1->BCM4706_wifi_radio1_mac_address_hw, MAC_ADDRESS_SIZE  );
            fs_read_BCM4706_wifi_radio2_mac_address_hw( fsv_t1->BCM4706_wifi_radio2_mac_address_hw, MAC_ADDRESS_SIZE  );
            fs_read_bcmwifi_wifi_radio1_mac_address_fbd( fsv_t1->bcmwifi_wifi_radio1_mac_address_fbd, MAC_ADDRESS_SIZE  );
            fs_read_bcmwifi_wifi_radio2_mac_address_fbd( fsv_t1->bcmwifi_wifi_radio2_mac_address_fbd, MAC_ADDRESS_SIZE  );
            if (fsv_t1->secinfo_exists) {
                fs_read_bcmwifi_wifi_radio1_mac_address_sec ( fsv_t1->bcmwifi_wifi_radio1_mac_address_sec, MAC_ADDRESS_SIZE );
                fs_read_bcmwifi_wifi_radio2_mac_address_sec ( fsv_t1->bcmwifi_wifi_radio2_mac_address_sec, MAC_ADDRESS_SIZE );
            }
            fs_dump__hex("bcmwifi_wifi_radio1_mac_address_sec", fsv_t1->bcmwifi_wifi_radio1_mac_address_sec, MAC_ADDRESS_SIZE );
            fs_dump__hex("bcmwifi_wifi_radio1_mac_address_fbd", fsv_t1->bcmwifi_wifi_radio1_mac_address_fbd, MAC_ADDRESS_SIZE );
            if (fsv_t1->boardinfo_exists && fs_has_wifi_radio1_mac_address_bi()) {
                fs_output_off();
                fs_read_wifi_radio1_mac_address_bi(fsv_t1->wifi_radio1_mac_address_bi, MAC_ADDRESS_SIZE);
                fs_output_on();
                fs_dump__hex("bcmwifi_wifi_radio1_mac_address_bi", fsv_t1->wifi_radio1_mac_address_bi, MAC_ADDRESS_SIZE );
            }
            fs_dump__hex("BCM4706_wifi_radio1_mac_address_hw", fsv_t1->BCM4706_wifi_radio1_mac_address_hw, MAC_ADDRESS_SIZE );
            fs_dump__hex("bcmwifi_wifi_radio2_mac_address_sec", fsv_t1->bcmwifi_wifi_radio2_mac_address_sec, MAC_ADDRESS_SIZE );
            fs_dump__hex("bcmwifi_wifi_radio2_mac_address_fbd", fsv_t1->bcmwifi_wifi_radio2_mac_address_fbd, MAC_ADDRESS_SIZE );
            if (fsv_t1->boardinfo_exists && fs_has_wifi_radio2_mac_address_bi()) {
                fs_output_off();
                fs_read_wifi_radio2_mac_address_bi(fsv_t1->wifi_radio2_mac_address_bi, MAC_ADDRESS_SIZE);
                fs_output_on();
                fs_dump__hex("bcmwifi_wifi_radio2_mac_address_bi", fsv_t1->wifi_radio2_mac_address_bi, MAC_ADDRESS_SIZE);
            }
            fs_dump__hex("BCM4706_wifi_radio2_mac_address_hw", fsv_t1->BCM4706_wifi_radio2_mac_address_hw, MAC_ADDRESS_SIZE );
        }
#else // #ifdef UBNT_SUPPORT_CLASS_BCMWIFI
        fs_dump__error("No support for product class bcmwifi on this platform.");
        goto done;
#endif // #ifdef UBNT_SUPPORT_CLASS_BCMWIFI
        break;
    case FS_SECURITY_DATA_FORMAT_QCASWITCH:
#ifdef UBNT_SUPPORT_CLASS_QCASWITCH
        {
            // Nothing QCA switch related here
        }
#else // #ifdef UBNT_SUPPORT_CLASS_QCASWITCH
        fs_dump__error("No support for product class qcaswitch on this platform.");
        goto done;
#endif // #ifdef UBNT_SUPPORT_CLASS_QCASWITCH
        break;
    case FS_SECURITY_DATA_FORMAT_BCMSWITCH:
#ifdef UBNT_SUPPORT_CLASS_BCMSWITCH
        {
            fs_dump__hex32("bcmswitch_cpu_rev_id_sec", fs_read_bcmswitch_cpu_rev_id_sec());
#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_BCM5334x) || SECURITY_ENABLE_SIMULATION)
#if SECURITY_ENABLE_SIMULATION
            if (fs_read_bcmswitch_cpu_rev_id_sec() == BCM5334x_CPU_REV)
#endif // #if SECURITY_ENABLE_SIMULATION
                fs_dump__hex32("BCM5334x_cpu_rev_id_hw", fs_read_BCM5334x_cpu_rev_id_hw());
#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_BCM5334x) || SECURITY_ENABLE_SIMULATION)
#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_BCM5341x) || SECURITY_ENABLE_SIMULATION)
#if SECURITY_ENABLE_SIMULATION
            if (fs_read_bcmswitch_cpu_rev_id_sec() == BCM5341x_CPU_REV)
#endif // #if SECURITY_ENABLE_SIMULATION
                fs_dump__hex32("cpu_rev_id_hw", fs_read_BCM5341x_cpu_rev_id_hw());
#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_BCM5341x) || SECURITY_ENABLE_SIMULATION)
#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_BCM5616x) || SECURITY_ENABLE_SIMULATION)
#if SECURITY_ENABLE_SIMULATION
            if (fs_read_bcmswitch_cpu_rev_id_sec() == BCM5616x_CPU_REV) 
#endif // #if SECURITY_ENABLE_SIMULATION
                fs_dump__hex32("cpu_rev_id_hw", fs_read_BCM5616x_cpu_rev_id_hw());
#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_BCM5616x) || SECURITY_ENABLE_SIMULATION)
            fs_read_bcmswitch_vpd_fbd(fsv_t1->bcmswitch_vpd_fbd, sizeof fsv_t1->bcmswitch_vpd_fbd);
            fs_dump__hex_truncated("bcmswitch_vpd_fbd", fsv_t1->bcmswitch_vpd_fbd, sizeof fsv_t1->bcmswitch_vpd_fbd);
            fs_read_bcmswitch_vpd_sec(fsv_t1->bcmswitch_vpd_sec, sizeof fsv_t1->bcmswitch_vpd_sec);
            fs_dump__hex_truncated("bcmswitch_vpd_sec", fsv_t1->bcmswitch_vpd_sec, sizeof fsv_t1->bcmswitch_vpd_sec);
        }
#else // #ifdef UBNT_SUPPORT_CLASS_BCMSWITCH
        fs_dump__error("No support for product class bcmswitch on this platform.");
        goto done;
#endif // #ifdef UBNT_SUPPORT_CLASS_BCMSWITCH
        break;
    case FS_SECURITY_DATA_FORMAT_CLOUDKEY:
#ifdef UBNT_SUPPORT_CLASS_CLOUDKEY
        {
            fs_dump__hex32("cloudkey_cpu_rev_id_sec", fs_read_cloudkey_cpu_rev_id_sec());
            fs_dump__hex32("MT7623_cpu_rev_id_hw", fs_read_MT7623_cpu_rev_id_hw());
        }
#else // #ifdef UBNT_SUPPORT_CLASS_CLOUDKEY
        fs_dump__error("No support for product class cloudkey on this platform.");
        goto done;
#endif // #ifdef UBNT_SUPPORT_CLASS_CLOUDKEY
        break;
    case FS_SECURITY_DATA_FORMAT_UNIVOX:
#ifdef UBNT_SUPPORT_CLASS_UNIVOX
        {
            if (fsv_t1->secinfo_exists) {
                fs_dump__hex32("univox_cpu_rev_id_sec", fs_read_univox_cpu_rev_id_sec());
            }
#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_BCM111xx) || SECURITY_ENABLE_SIMULATION)
#if SECURITY_ENABLE_SIMULATION
            if (fs_read_univox_cpu_rev_id_sec() == BCM111xx_CPU_REV)
#endif // #if SECURITY_ENABLE_SIMULATION
                fs_dump__hex32("BCM111xx_cpu_rev_id_hw", fs_read_BCM111xx_cpu_rev_id_hw());
#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_BCM111xx) || SECURITY_ENABLE_SIMULATION)
#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_MT8117) || SECURITY_ENABLE_SIMULATION)
#if SECURITY_ENABLE_SIMULATION
            if (fs_read_univox_cpu_rev_id_sec() == MT8117_CPU_REV)
#endif // #if SECURITY_ENABLE_SIMULATION
                fs_dump__hex32("MT8117_cpu_rev_id_hw", fs_read_MT8117_cpu_rev_id_hw());
#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_MT8117) || SECURITY_ENABLE_SIMULATION)
            if (fsv_t1->boardinfo_exists) {
                fs_dump__hex32("cpu_rev_id_bi", fs_read_cpu_rev_id_bi());
            }
        }
#else // #ifdef UBNT_SUPPORT_CLASS_UNIVOX
        fs_dump__error("No support for product class univox on this platform.");
        goto done;
#endif // #ifdef UBNT_SUPPORT_CLASS_UNIVOX
        break;
    case FS_SECURITY_DATA_FORMAT_AIRFIBER:
#ifdef UBNT_SUPPORT_CLASS_AIRFIBER
        {
            if (fsv_t1->secinfo_exists) {
                fs_dump__hex32("airfiber_cpu_rev_id_sec", fs_read_airfiber_cpu_rev_id_sec());
            }
            if (fsv_t1->boardinfo_exists) {
                u_int32_t cpu_rev_id_bi = 0;
                fs_output_off();
                cpu_rev_id_bi = fs_read_cpu_rev_id_bi();
                fs_output_on();
                fs_dump__hex32("airfiber_cpu_rev_id_bi", cpu_rev_id_bi);
            }
            fs_dump__hex32("AM18xx_cpu_rev_id_hw", fs_read_AM18xx_cpu_rev_id_hw());
        }
#else // #ifdef UBNT_SUPPORT_CLASS_AIRFIBER
        fs_dump__error("No support for product class airfiber on this platform.");
        goto done;
#endif // #ifdef UBNT_SUPPORT_CLASS_AIRFIBER
        break;
    default:
        break;
    }

    if (fsv_t1->secinfo_exists) {
        if (fs_get_config_offset_pcba_sec()) {
            fs_dump__pcba32("pcba_sec", fs_read_pcba_sec());
#ifdef UBNT_SUPPORT_CLASS_AIRFIBER
        } else if (fs_read_security_data_format_sec() == FS_SECURITY_DATA_FORMAT_AIRFIBER) {
            fs_dump__pcba16("pcba_sec", fs_read_airfiber_old_board_rev_id_sec());
#endif // #ifdef UBNT_SUPPORT_CLASS_AIRFIBER
        } else {
            fs_dump__unsupported("pcba_sec", fsv_t1->security_data_revision_sec);
        }
    }
    /*
       For signed units with PCBA field, we will find FBD copy of PCBA using the security data to determine where to look
       For airfiber units, we will use the old 2-byte FBD

       For uncalibrated units, we'll try directly accessing at 0x10 to show whatever we found anyway.
    */
    if (fs_get_config_offset_pcba_sec()) {
        fs_dump__pcba32("pcba_fbd", fs_read_pcba_fbd());
    } else {
        fs_dump__pcba32("pcba_fbd", fs_read_config_be32toh(FLASH_BOARD_DATA_OFFSET_PCBA));
    }

    if (fsv_t1->secinfo_exists) {
        if (fs_read_qr_code_sec(fsv_t1->qr_code_sec, sizeof fsv_t1->qr_code_sec)) {
            fs_dump__hex("qr_code_sec", fsv_t1->qr_code_sec, sizeof fsv_t1->qr_code_sec);
        } else if(fsv_t1->security_data_revision_sec >= 2) {
            fs_dump__string("qr_code_sec", FS_DUMP__DESC_NOT_PROGRAMMED);
        } else {
            fs_dump__unsupported("qr_code_sec", fsv_t1->security_data_revision_sec);
        }
        fsv_t1->fcd_id_sec = fs_read_fcd_id_sec();// NB: 0 if unsupported, 0xffff if not specified/programmed
        if (fsv_t1->fcd_id_sec != 0 && fsv_t1->fcd_id_sec != 0xFFFF) {
            fs_dump__hex16("fcd_id_sec", fsv_t1->fcd_id_sec);
        } else if(fsv_t1->security_data_revision_sec >= 3) {
            fs_dump__string("fcd_id_sec", FS_DUMP__DESC_NOT_PROGRAMMED);
        } else  {
            fs_dump__unsupported("fcd_id_sec", fsv_t1->security_data_revision_sec);
        }
        fsv_t1->fcd_version_sec = fs_read_fcd_version_sec();// NB: 0 if unsupported, 0xffffffff if not specified/programmed
        fs_dump__version("fcd_version_sec", fsv_t1->fcd_version_sec, fsv_t1->security_data_revision_sec /* in case it's unsupported */);
        fsv_t1->sw_id_sec = fs_read_sw_id_sec();// NB: 0 if unsupported, 0xffffffff if not specified/programmed
        if (fsv_t1->sw_id_sec != 0 && fsv_t1->sw_id_sec != 0xFFFF) {
            fs_dump__hex16("sw_id_sec", fsv_t1->sw_id_sec);
        } else if(fsv_t1->security_data_revision_sec >= 3) {
            fs_dump__string("sw_id_sec", FS_DUMP__DESC_NOT_PROGRAMMED);
        } else  {
            fs_dump__unsupported("sw_id_sec", fsv_t1->security_data_revision_sec);
        }
        fsv_t1->sw_version_sec = fs_read_sw_version_sec(); // NB: 0 if unsupported, 0xffffffff if not specified/programmed
        fs_dump__version("sw_version_sec", fsv_t1->sw_version_sec, fsv_t1->security_data_revision_sec /* in case it's unsupported */);
#if SECURITY_ENABLE_ESN_SIGNATURE_CHECKS
        fs_dump__hex("esn_sig_iv_area_sec", fsv_t1->esn_sig_iv_area_sec, sizeof fsv_t1->esn_sig_iv_area_sec);
        fs_dump__hex("esn_signature_sec", fsv_t1->esn_signature_sec, sizeof fsv_t1->esn_signature_sec);
#endif // #if SECURITY_ENABLE_ESN_SIGNATURE_CHECKS
        fs_dump__hex("ubnt_signature_sec", fsv_t1->ubnt_signature_sec, sizeof fsv_t1->ubnt_signature_sec);
    }
    fs_dump__string("git_commit_hash", FS_GIT_COMMIT_HASH);
    fs_dump__string("build_date", FS_BUILD_DATE);
    fs_dump__uint32("hw_support_level", SECURITY_FLASH_HWREV);
    fs_debug_printf("%s", fs_dump__format_label_s("Security Check Result"));
    fs_output_off();
    fs_check_sec();
    fs_output_on();
    if (FS_CHECKS_PASSED_SIGNED) {
        fs_debug_printf("PASS");
    } else if (FS_CHECKS_PASSED) {
        fs_debug_printf("PASS [EXEMPTED]");
    } else {
        fs_debug_printf("FAIL");
    }
    fs_debug_printf("\n\n");
    done:
    fs_safe_shred_and_free(&fsv_t1, sizeof(*fsv_t1));
}

#else // #if SECURITY_ENABLE_DIAGNOSTIC_DUMPS
//__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_dump(void) {}
#undef fs_dump
#define fs_dump(...)
#endif // #if SECURITY_ENABLE_DIAGNOSTIC_DUMPS
