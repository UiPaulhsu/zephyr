#ifndef __INC_SECURITY_CLASSES_INC__
#define __INC_SECURITY_CLASSES_INC__

typedef u_int16_t fs_product_superclass_id_t;
typedef u_int16_t fs_product_class_id_t;

/* WARNING: DO NOT CHANGE ID - DATABASE MUST MATCH */
#define FS_PRODUCT_SUPERCLASS_ID_INVALID                           0x0000
#define FS_PRODUCT_SUPERCLASS_ID_WIFI                              0x0001
#define FS_PRODUCT_SUPERCLASS_ID_CAMERA                            0x0002
#define FS_PRODUCT_SUPERCLASS_ID_SWITCH                            0x0003
#define FS_PRODUCT_SUPERCLASS_ID_ROUTER                            0x0004
#define FS_PRODUCT_SUPERCLASS_ID_AIRFIBER                          0x0005
#define FS_PRODUCT_SUPERCLASS_ID_UNIVOX                            0x0006
#define FS_PRODUCT_SUPERCLASS_ID_CAMERA2                           0x0007
#define FS_PRODUCT_SUPERCLASS_ID_BCMWIFI                           0x0008
#define FS_PRODUCT_SUPERCLASS_ID_QCASWITCH                         0x0009
#define FS_PRODUCT_SUPERCLASS_ID_LEGACY                            0x000a
#define FS_PRODUCT_SUPERCLASS_ID_NVR                               0x000b
#define FS_PRODUCT_SUPERCLASS_ID_SAMPLE                            0x000c
#define FS_PRODUCT_SUPERCLASS_ID_BCMSWITCH                         0x000d
#define FS_PRODUCT_SUPERCLASS_ID_INVERTER                          0x000e
#define FS_PRODUCT_SUPERCLASS_ID_CLOUDKEY                          0x000f
#define FS_PRODUCT_SUPERCLASS_ID_SOLARGATEWAY                      0x0010
#define FS_PRODUCT_SUPERCLASS_ID_BASIC                             0x0011
#define FS_PRODUCT_SUPERCLASS_ID_ARRAY_LEN                         0x0012 /* Length needed for array of product classes (including invalid) */
#define FS_PRODUCT_SUPERCLASS_ID_MISSING                           0xFFFF

#if SECURITY_ENABLE_DEBUG_OUTPUT || defined(SERVER_BUILD) || defined(CLIENT_BUILD) || defined(HELPER_BUILD)
/* WARNING: DO NOT CHANGE LABEL - HELPER/FCD MUST MATCH. */
#define FS_PRODUCT_SUPERCLASS_LABEL_INVALID                     "invalid/unknown"
#define FS_PRODUCT_SUPERCLASS_LABEL_WIFI                        "wifi"
#define FS_PRODUCT_SUPERCLASS_LABEL_CAMERA                      "camera"
#define FS_PRODUCT_SUPERCLASS_LABEL_SWITCH                      "switch"
#define FS_PRODUCT_SUPERCLASS_LABEL_BASIC                       "basic"
#define FS_PRODUCT_SUPERCLASS_LABEL_BASIC4K                     "basic4k"
#define FS_PRODUCT_SUPERCLASS_LABEL_ROUTER                      "router"
#define FS_PRODUCT_SUPERCLASS_LABEL_AIRFIBER                    "airfiber"
#define FS_PRODUCT_SUPERCLASS_LABEL_UNIVOX                      "univox"
#define FS_PRODUCT_SUPERCLASS_LABEL_CAMERA2                     "camera2"
#define FS_PRODUCT_SUPERCLASS_LABEL_BCMWIFI                     "bcmwifi"
#define FS_PRODUCT_SUPERCLASS_LABEL_QCASWITCH                   "qcaswitch"
#define FS_PRODUCT_SUPERCLASS_LABEL_LEGACY                      "legacy"
#define FS_PRODUCT_SUPERCLASS_LABEL_NVR                         "nvr"
#define FS_PRODUCT_SUPERCLASS_LABEL_SAMPLE                      "sample"
#define FS_PRODUCT_SUPERCLASS_LABEL_BCMSWITCH                   "bcmswitch"
#define FS_PRODUCT_SUPERCLASS_LABEL_INVERTER                    "inverter"
#define FS_PRODUCT_SUPERCLASS_LABEL_CLOUDKEY                    "cloudkey"
#define FS_PRODUCT_SUPERCLASS_LABEL_SOLARGATEWAY                "solargateway"
#endif // #if SECURITY_ENABLE_DEBUG_OUTPUT || defined(SERVER_BUILD) || defined(CLIENT_BUILD) || defined(HELPER_BUILD)

#if defined(SERVER_BUILD) || defined(CLIENT_BUILD) || defined(HELPER_BUILD)
#define FS_PRODUCT_SUPERCLASS_DESC_INVALID                      "Invalid/unknown device class."
#define FS_PRODUCT_SUPERCLASS_DESC_WIFI                         "QCA based device (typically cpu/radio/flash/eth)."
#define FS_PRODUCT_SUPERCLASS_DESC_CAMERA                       "Video Camera"
#define FS_PRODUCT_SUPERCLASS_DESC_CAMERA2                      "Video Camera V2"
#define FS_PRODUCT_SUPERCLASS_DESC_SWITCH                       "Simple Network Switch"
#define FS_PRODUCT_SUPERCLASS_DESC_BASIC                        "General Networking Device"
#define FS_PRODUCT_SUPERCLASS_DESC_BASIC4K                      "General Networking Device, Reduced Flash Footprint"
#define FS_PRODUCT_SUPERCLASS_DESC_ROUTER                       "Edge Router"
#define FS_PRODUCT_SUPERCLASS_DESC_AIRFIBER                     "AirFiber"
#define FS_PRODUCT_SUPERCLASS_DESC_UNIVOX                       "UniVox"
#define FS_PRODUCT_SUPERCLASS_DESC_BCMWIFI                      "Broadcom 802.11ac Wifi Device"
#define FS_PRODUCT_SUPERCLASS_DESC_QCASWITCH                    "Qualcomm-Atheros QCA851x Switch"
#define FS_PRODUCT_SUPERCLASS_DESC_BCMSWITCH                    "Broadcom BCM5334x/BCM5341x/BCM5616x/MT7621 Switch"
#define FS_PRODUCT_SUPERCLASS_DESC_INVERTER                     "Inverter"
#define FS_PRODUCT_SUPERCLASS_DESC_LEGACY                       "Legacy (Non-Secure)"
#define FS_PRODUCT_SUPERCLASS_DESC_SAMPLE                       "Sample (Non-Secure)"
#define FS_PRODUCT_SUPERCLASS_DESC_NVR                          "NVR"
#define FS_PRODUCT_SUPERCLASS_DESC_CLOUDKEY                     "Cloud Key"
#define FS_PRODUCT_SUPERCLASS_DESC_SOLARGATEWAY                 "Solar Gateway"
#endif // #if defined(SERVER_BUILD) || defined(CLIENT_BUILD) || defined(HELPER_BUILD)

/* WARNING: DO NOT CHANGE ID - DATABASE MUST MATCH */
#define FS_PRODUCT_CLASS_ID_INVALID                                0x0000
#define FS_PRODUCT_CLASS_ID_RADIO                                  0x0001
#define FS_PRODUCT_CLASS_ID_RF_BOARD                               0x0002
#define FS_PRODUCT_CLASS_ID_DIGITAL_BOARD                          0x0003
#define FS_PRODUCT_CLASS_ID_CAMERA                                 0x0004
#define FS_PRODUCT_CLASS_ID_RF_BOARD_DUAL                          0x0005
#define FS_PRODUCT_CLASS_ID_SWITCH                                 0x0006
#define FS_PRODUCT_CLASS_ID_ROUTER                                 0x0007
#define FS_PRODUCT_CLASS_ID_AIRFIBER                               0x0008
#define FS_PRODUCT_CLASS_ID_UNIVOX                                 0x0009
#define FS_PRODUCT_CLASS_ID_CAMERA2                                0x000a
#define FS_PRODUCT_CLASS_ID_BCMWIFI                                0x000b
#define FS_PRODUCT_CLASS_ID_QCASWITCH                              0x000c
#define FS_PRODUCT_CLASS_ID_LEGACY                                 0x000d
#define FS_PRODUCT_CLASS_ID_NVR                                    0x000e
#define FS_PRODUCT_CLASS_ID_SAMPLE                                 0x000f
#define FS_PRODUCT_CLASS_ID_BCMSWITCH                              0x0010
#define FS_PRODUCT_CLASS_ID_INVERTER                               0x0011
#define FS_PRODUCT_CLASS_ID_CLOUDKEY                               0x0012
#define FS_PRODUCT_CLASS_ID_SOLARGATEWAY                           0x0013
#define FS_PRODUCT_CLASS_ID_BASIC                                  0x0014
#define FS_PRODUCT_CLASS_ID_BASIC4K                                0x0015
#define FS_PRODUCT_CLASS_ID_ARRAY_LEN                              0x0016 /* Length needed for array of product classes (including invalid) */
#define FS_PRODUCT_CLASS_ID_MISSING                                0xFFFF

#if SECURITY_ENABLE_DEBUG_OUTPUT || defined(SERVER_BUILD) || defined(CLIENT_BUILD) || defined(HELPER_BUILD)
/* WARNING: DO NOT CHANGE LABEL - HELPER/FCD MUST MATCH. */
#define FS_PRODUCT_CLASS_LABEL_INVALID                          FS_PRODUCT_SUPERCLASS_LABEL_INVALID
#define FS_PRODUCT_CLASS_LABEL_RADIO                            "radio"
#define FS_PRODUCT_CLASS_LABEL_RF_BOARD                         "rf_board"
#define FS_PRODUCT_CLASS_LABEL_RF_BOARD_DUAL                    "rf_board_dual"
#define FS_PRODUCT_CLASS_LABEL_DIGITAL_BOARD                    "digital_board"
#define FS_PRODUCT_CLASS_LABEL_CAMERA                           FS_PRODUCT_SUPERCLASS_LABEL_CAMERA
#define FS_PRODUCT_CLASS_LABEL_CAMERA2                          FS_PRODUCT_SUPERCLASS_LABEL_CAMERA2
#define FS_PRODUCT_CLASS_LABEL_SWITCH                           FS_PRODUCT_SUPERCLASS_LABEL_SWITCH
#define FS_PRODUCT_CLASS_LABEL_BASIC                            FS_PRODUCT_SUPERCLASS_LABEL_BASIC
#define FS_PRODUCT_CLASS_LABEL_BASIC4K                          FS_PRODUCT_SUPERCLASS_LABEL_BASIC4K
#define FS_PRODUCT_CLASS_LABEL_ROUTER                           FS_PRODUCT_SUPERCLASS_LABEL_ROUTER
#define FS_PRODUCT_CLASS_LABEL_AIRFIBER                         FS_PRODUCT_SUPERCLASS_LABEL_AIRFIBER
#define FS_PRODUCT_CLASS_LABEL_UNIVOX                           FS_PRODUCT_SUPERCLASS_LABEL_UNIVOX
#define FS_PRODUCT_CLASS_LABEL_BCMWIFI                          FS_PRODUCT_SUPERCLASS_LABEL_BCMWIFI
#define FS_PRODUCT_CLASS_LABEL_QCASWITCH                        FS_PRODUCT_SUPERCLASS_LABEL_QCASWITCH
#define FS_PRODUCT_CLASS_LABEL_BCMSWITCH                        FS_PRODUCT_SUPERCLASS_LABEL_BCMSWITCH
#define FS_PRODUCT_CLASS_LABEL_LEGACY                           FS_PRODUCT_SUPERCLASS_LABEL_LEGACY
#define FS_PRODUCT_CLASS_LABEL_SAMPLE                           FS_PRODUCT_SUPERCLASS_LABEL_SAMPLE
#define FS_PRODUCT_CLASS_LABEL_NVR                              FS_PRODUCT_SUPERCLASS_LABEL_NVR
#define FS_PRODUCT_CLASS_LABEL_INVERTER                         FS_PRODUCT_SUPERCLASS_LABEL_INVERTER
#define FS_PRODUCT_CLASS_LABEL_CLOUDKEY                         FS_PRODUCT_SUPERCLASS_LABEL_CLOUDKEY
#define FS_PRODUCT_CLASS_LABEL_SOLARGATEWAY                     FS_PRODUCT_SUPERCLASS_LABEL_SOLARGATEWAY
#endif // #if SECURITY_ENABLE_DEBUG_OUTPUT || defined(SERVER_BUILD) || defined(CLIENT_BUILD) || defined(HELPER_BUILD)


#if defined(SERVER_BUILD) || defined(CLIENT_BUILD) || defined(HELPER_BUILD)
#define FS_PRODUCT_CLASS_DESC_INVALID                           FS_PRODUCT_SUPERCLASS_DESC_INVALID
#define FS_PRODUCT_CLASS_DESC_RADIO                             "Device with CPU, Radio and FLASH."
#define FS_PRODUCT_CLASS_DESC_RF_BOARD                          "Daughterboard with one pair of radio and EEPROM IC."
#define FS_PRODUCT_CLASS_DESC_RF_BOARD_DUAL                     "Daughterboard with two pairs of radio and EEPROM IC."
#define FS_PRODUCT_CLASS_DESC_DIGITAL_BOARD                     "Device with CPU only (with FLASH)"
#define FS_PRODUCT_CLASS_DESC_CAMERA                            FS_PRODUCT_SUPERCLASS_DESC_CAMERA
#define FS_PRODUCT_CLASS_DESC_CAMERA2                           FS_PRODUCT_SUPERCLASS_DESC_CAMERA2
#define FS_PRODUCT_CLASS_DESC_SWITCH                            FS_PRODUCT_SUPERCLASS_DESC_SWITCH
#define FS_PRODUCT_CLASS_DESC_BASIC                             FS_PRODUCT_SUPERCLASS_DESC_BASIC
#define FS_PRODUCT_CLASS_DESC_BASIC4K                           FS_PRODUCT_SUPERCLASS_DESC_BASIC4K
#define FS_PRODUCT_CLASS_DESC_ROUTER                            FS_PRODUCT_SUPERCLASS_DESC_ROUTER
#define FS_PRODUCT_CLASS_DESC_AIRFIBER                          FS_PRODUCT_SUPERCLASS_DESC_AIRFIBER
#define FS_PRODUCT_CLASS_DESC_UNIVOX                            FS_PRODUCT_SUPERCLASS_DESC_UNIVOX
#define FS_PRODUCT_CLASS_DESC_BCMWIFI                           FS_PRODUCT_SUPERCLASS_DESC_BCMWIFI
#define FS_PRODUCT_CLASS_DESC_QCASWITCH                         FS_PRODUCT_SUPERCLASS_DESC_QCASWITCH
#define FS_PRODUCT_CLASS_DESC_BCMSWITCH                         FS_PRODUCT_SUPERCLASS_DESC_BCMSWITCH
#define FS_PRODUCT_CLASS_DESC_INVERTER                          FS_PRODUCT_SUPERCLASS_DESC_INVERTER
#define FS_PRODUCT_CLASS_DESC_LEGACY                            FS_PRODUCT_SUPERCLASS_DESC_LEGACY
#define FS_PRODUCT_CLASS_DESC_SAMPLE                            FS_PRODUCT_SUPERCLASS_DESC_SAMPLE
#define FS_PRODUCT_CLASS_DESC_NVR                               FS_PRODUCT_SUPERCLASS_DESC_NVR
#define FS_PRODUCT_CLASS_DESC_CLOUDKEY                          FS_PRODUCT_SUPERCLASS_DESC_CLOUDKEY
#define FS_PRODUCT_CLASS_DESC_SOLARGATEWAY                      FS_PRODUCT_SUPERCLASS_DESC_SOLARGATEWAY

#endif // defined(SERVER_BUILD) || defined(CLIENT_BUILD) || defined(HELPER_BUILD)

////////////////////////////////////////////////////////////////////////////////
/// Product class support
////////////////////////////////////////////////////////////////////////////////

#if defined(UBNT_X86)
    // Can only be for simulation... (this case covered below)
#elif defined(UBNT_X64)
    #if defined(UBNT_NVRx64)
        #define UBNT_SUPPORT_CLASS_NVR      1
    #else
        // Can only be for simulation... (this case covered below)
    #endif
#elif defined(UBNT_MIPS_CN50xx)
    #define UBNT_SUPPORT_CLASS_ROUTER       1
#elif defined(UBNT_MIPS_MT7621)
    #define UBNT_SUPPORT_CLASS_ROUTER       1
    #define UBNT_SUPPORT_CLASS_SOLARGATEWAY 1
    #define UBNT_SUPPORT_CLASS_BASIC        1
#elif defined(UBNT_MIPS_QCA851x)
    #define UBNT_SUPPORT_CLASS_QCASWITCH    1
#elif defined(UBNT_MIPS_ARxxxx)
    #define UBNT_SUPPORT_CLASS_WIFI         1
    #define UBNT_SUPPORT_CLASS_SWITCH       1
    #define UBNT_SUPPORT_CLASS_BASIC        1
#elif defined(UBNT_MIPS_RTL838x)
    #define UBNT_SUPPORT_CLASS_BASIC        1
#elif defined(UBNT_MIPS_BCM4706)
    #define UBNT_SUPPORT_CLASS_BCMWIFI      1
#elif defined(UBNT_ARM_BCM5334x) || defined(UBNT_ARM_BCM5341x) || defined(UBNT_ARM_BCM5616x)
    #define UBNT_SUPPORT_CLASS_BCMSWITCH    1
#elif defined(UBNT_MIPS_VSC7514)
    #define UBNT_SUPPORT_CLASS_BASIC        1
#elif defined(UBNT_ARM_MT7623)
    #define UBNT_SUPPORT_CLASS_CLOUDKEY     1
    #define UBNT_SUPPORT_CLASS_BASIC        1
#elif defined(UBNT_ARM_AM18xx)
    #define UBNT_SUPPORT_CLASS_AIRFIBER     1
#elif defined(UBNT_ARM_GM81xx)
    #define UBNT_SUPPORT_CLASS_CAMERA       1
#elif defined(UBNT_ARM_BCM111xx)
    #define UBNT_SUPPORT_CLASS_UNIVOX       1
#elif defined(UBNT_ARM_MT8117)
    #define UBNT_SUPPORT_CLASS_BASIC        1
    #define UBNT_SUPPORT_CLASS_UNIVOX       1
#elif defined(UBNT_ARM_A5S) || defined(UBNT_ARM_S2) || defined(UBNT_ARM_S2L) || defined(UBNT_ARM_S2LM) || defined(UBNT_ARM64_S5L) || defined(UBNT_ARM64_S5LM)
    #define UBNT_SUPPORT_CLASS_CAMERA2      1
#elif defined(UBNT_ARM_STM32F30x)
    #define UBNT_SUPPORT_CLASS_INVERTER     1
#elif defined(UBNT_ARM_IPQ40xx)
    #define UBNT_SUPPORT_CLASS_BASIC        1
    #define UBNT_SUPPORT_CLASS_WIFI         1
#elif defined(UBNT_ARM_IPQ806x)
    #define UBNT_SUPPORT_CLASS_BASIC        1
#elif defined(UBNT_ARM64_APQ8053)
    #define UBNT_SUPPORT_CLASS_BASIC        1
#elif defined(UBNT_ARM64_AL324)
    #define UBNT_SUPPORT_CLASS_BASIC        1
#elif defined(UBNT_ARM64_IPQ807x)
    #define UBNT_SUPPORT_CLASS_BASIC        1
#elif defined(UBNT_EFR32xG13)
    #define UBNT_SUPPORT_CLASS_BASIC        1
#elif defined(UBNT_ST50H)
    #define UBNT_SUPPORT_CLASS_BASIC        1
#elif !defined(UBNT_TARGET)
    #error "UBNT_TARGET was not identified correctly."
#else
    #error "Target is missing from UBNT product class support list."
#endif

#if (defined(SECURITY_ENABLE_SIMULATION) && SECURITY_ENABLE_SIMULATION) \
 || (defined(CLIENT_BUILD) && CLIENT_BUILD) \
 || (defined(SERVER_BUILD) && SERVER_BUILD)
    #define UBNT_SUPPORT_CLASS_AIRFIBER     1
    #define UBNT_SUPPORT_CLASS_BCMWIFI      1
    #define UBNT_SUPPORT_CLASS_CAMERA       1
    #define UBNT_SUPPORT_CLASS_CAMERA2      1
    #define UBNT_SUPPORT_CLASS_NVR          1
    #define UBNT_SUPPORT_CLASS_QCASWITCH    1
    #define UBNT_SUPPORT_CLASS_BCMSWITCH    1
    #define UBNT_SUPPORT_CLASS_CLOUDKEY     1
    #define UBNT_SUPPORT_CLASS_ROUTER       1
    #define UBNT_SUPPORT_CLASS_SOLARGATEWAY 1
    #define UBNT_SUPPORT_CLASS_SWITCH       1
    #define UBNT_SUPPORT_CLASS_BASIC        1
    #define UBNT_SUPPORT_CLASS_BASIC4K      1
    #define UBNT_SUPPORT_CLASS_UNIVOX       1
    #define UBNT_SUPPORT_CLASS_WIFI         1
    #define UBNT_SUPPORT_CLASS_INVERTER     1
#endif // #if simulated helper or devreg OR a client OR a server

#endif // #ifndef __INC_SECURITY_CLASSES_INC__
