#ifndef __INC_SECURITY_CONFIG_INC__
#define __INC_SECURITY_CONFIG_INC__

/*

EEPROM MAP:

See https://docs.google.com/spreadsheets/d/18hqzWQowU-3KRXN-N3BlWYDUyQ7WKnELLQrevznXOKA/edit#gid=0 for current EEPROM mappings.

*/

/*

 #####     ##    #    #   ####   ######  #####
 #    #   #  #   ##   #  #    #  #       #    #  #
 #    #  #    #  # #  #  #       #####   #    #
 #    #  ######  #  # #  #  ###  #       #####
 #    #  #    #  #   ##  #    #  #       #   #   #
 #####   #    #  #    #   ####   ######  #    #

Do NOT use minor revision field on the subset of flash formats as indicated below.

Old firmware for these product classes only supported format revision 1, with the assumption
that new fields should be mandatory and not bypassed by downgrade... in the interest of not requiring
an anti-downgrade rule for every format revision, new product classes will ignore additional fields
added after the time of manufacturer (i.e. with newer formats, new fields are ignored).

Changing minor version on these product classes and then loading an old firmware would result in a
bricked device with false positive for counterfeit.  Therefore, we have added another 4 bytes to these
product classes' EEPROM contents.  Three bytes "magic" value (improbable accidental occurance) plus a 1
byte minor revision, to replace the one in the data format field.

(RESTRICTIONS AS NOTED BELOW)

*/

typedef u_int8_t  fs_security_data_format_id_t;

#define MAGIC_4K_MARKER_OFFSET 0x06
#define MAGIC_4K_MARKER_VALUE  0x40344b42 /* "@4KB" */

/* WARNING: DO NOT CHANGE ID - DATABASE MUST MATCH */
#define FS_SECURITY_DATA_FORMAT_INVALID                         0x00
#define FS_SECURITY_DATA_FORMAT_WIFI_FLASH                      0x01 // MINOR REV LOCKED. WORKAROUND.
#define FS_SECURITY_DATA_FORMAT_WIFI_RADIO_EEPROM               0x02 // No longer supported
#define FS_SECURITY_DATA_FORMAT_WIFI_DIGITAL_BOARD              0x03 // No longer supported
#define FS_SECURITY_DATA_FORMAT_CAMERA                          0x04 // MINOR REV LOCKED. WORKAROUND.
#define FS_SECURITY_DATA_FORMAT_WIFI_DUAL_RF                    0x05 // No longer supported
#define FS_SECURITY_DATA_FORMAT_SWITCH                          0x06 // MINOR REV LOCKED. WORKAROUND.
#define FS_SECURITY_DATA_FORMAT_ROUTER                          0x07 // MINOR REV LOCKED. WORKAROUND.
#define FS_SECURITY_DATA_FORMAT_AIRFIBER                        0x08 // MINOR REV LOCKED. WORKAROUND.
#define FS_SECURITY_DATA_FORMAT_UNIVOX                          0x09 // MINOR REV LOCKED. WORKAROUND.
#define FS_SECURITY_DATA_FORMAT_CAMERA2                         0x0A // MINOR REV LOCKED. WORKAROUND.
#define FS_SECURITY_DATA_FORMAT_BCMWIFI                         0x0B // MINOR REV LOCKED. WORKAROUND.
#define FS_SECURITY_DATA_FORMAT_QCASWITCH                       0x0C // MINOR REV LOCKED. WORKAROUND.
#define FS_SECURITY_DATA_FORMAT_NVR                             0x0D // MINOR REV LOCKED. WORKAROUND.
#define FS_SECURITY_DATA_FORMAT_BCMSWITCH                       0x0E // No MINOR rev bug.
#define FS_SECURITY_DATA_FORMAT_INVERTER                        0x0F // No MINOR rev bug.
#define FS_SECURITY_DATA_FORMAT_CLOUDKEY                        0x10 // No MINOR rev bug.
#define FS_SECURITY_DATA_FORMAT_SOLARGATEWAY                    0x11 // No MINOR rev bug.
#define FS_SECURITY_DATA_FORMAT_BASIC                           0x12 // No MINOR rev bug.
#define FS_SECURITY_DATA_FORMAT_BASIC4K                         0x13 // No MINOR rev bug.
#define FS_SECURITY_DATA_FORMAT_MISSING                         0xFF

#if SECURITY_ENABLE_DEBUG_OUTPUT || defined(SERVER_BUILD) || defined(CLIENT_BUILD)
#define FS_SECURITY_DATA_FORMAT_LABEL_INVALID                   "invalid/unknown"
#define FS_SECURITY_DATA_FORMAT_LABEL_WIFI_FLASH                "radio"
#define FS_SECURITY_DATA_FORMAT_LABEL_WIFI_RADIO_EEPROM         "wifi_radio_eeprom"
#define FS_SECURITY_DATA_FORMAT_LABEL_WIFI_DIGITAL_BOARD        "wifi_digital"
#define FS_SECURITY_DATA_FORMAT_LABEL_CAMERA                    "camera"
#define FS_SECURITY_DATA_FORMAT_LABEL_WIFI_DUAL_RF              "wifi_dual_rf"
#define FS_SECURITY_DATA_FORMAT_LABEL_SWITCH                    "switch"
#define FS_SECURITY_DATA_FORMAT_LABEL_BASIC                     "basic"
#define FS_SECURITY_DATA_FORMAT_LABEL_BASIC4K                   "basic4k"
#define FS_SECURITY_DATA_FORMAT_LABEL_ROUTER                    "router"
#define FS_SECURITY_DATA_FORMAT_LABEL_SOLARGATEWAY              "solargateway"
#define FS_SECURITY_DATA_FORMAT_LABEL_AIRFIBER                  "airfiber"
#define FS_SECURITY_DATA_FORMAT_LABEL_UNIVOX                    "univox"
#define FS_SECURITY_DATA_FORMAT_LABEL_CAMERA2                   "camera2"
#define FS_SECURITY_DATA_FORMAT_LABEL_BCMWIFI                   "bcmwifi"
#define FS_SECURITY_DATA_FORMAT_LABEL_QCASWITCH                 "qcaswitch"
#define FS_SECURITY_DATA_FORMAT_LABEL_NVR                       "nvr"
#define FS_SECURITY_DATA_FORMAT_LABEL_BCMSWITCH                 "bcmswitch"
#define FS_SECURITY_DATA_FORMAT_LABEL_CLOUDKEY                  "cloudkey"
#define FS_SECURITY_DATA_FORMAT_LABEL_INVERTER                  "inverter"
#endif // #if SECURITY_ENABLE_DEBUG_OUTPUT || defined(SERVER_BUILD) || defined(CLIENT_BUILD)

#define WRITE_DATA_FORMAT_REV_WAR_MAGIC(__variable) do { uint8_t* buf = (__variable); buf[0] = DATA_FORMAT_REV_WAR_MAGIC_B0; buf[1] = DATA_FORMAT_REV_WAR_MAGIC_B1; buf[2] = DATA_FORMAT_REV_WAR_MAGIC_B2; } while(0)
#define HAS_DATA_FORMAT_REV_WAR_MAGIC(__variable) ((__variable[0] == DATA_FORMAT_REV_WAR_MAGIC_B0) && (__variable[1] == DATA_FORMAT_REV_WAR_MAGIC_B1) && (__variable[2] == DATA_FORMAT_REV_WAR_MAGIC_B2))

#define CHECK_STRUCT_SIZE(__label__,__type__,__size__) \
    typedef struct { \
        u_int8_t __label__ ## _size_is_correct[(sizeof(__type__) == (__size__)) ? 0 : -1]; \
    } __label__ ## __size_check __ATTRIB_UNUSED;

#define member_size(__TYPE__,__MEMBER__)                        sizeof(((__TYPE__*)0)->__MEMBER__)

#define FS_SECURITY_DATA_FORMAT_BLANK                           0xFF
#define SIG_IV_AREA_SIZE                                        ((size_t)128)     /* 1024 bits */
#define MIN_FLASH_UID_SIZE                                      ((size_t)8)       /* 64   bits */
#define MAX_FLASH_UID_SIZE                                      ((size_t)128)     /* 1024 bits */
#define MAX_EEPROM_SIZE                                         BLOCK_64K
#define MIN_FLASH_EEPROM_SIZE                                   BLOCK_4K
#define MAX_FLASH_EEPROM_SIZE                                   BLOCK_64K
#define MIN_RADIO_EEPROM_SIZE                                   BLOCK_32K
#define MAX_RADIO_EEPROM_SIZE                                   BLOCK_64K
#define QR_CODE_SIZE                                            ((size_t)6)
#define ROUTER_VPD_SIZE                                         ((size_t)128)
#define BCMSWITCH_VPD_SIZE                                      ((size_t)256)
#define DATA_REV_WAR_MAGIC_SIZE                                 ((size_t)3)
#define DATA_FORMAT_REV_SIZE                                    ((size_t)1)
#define DATA_FORMAT_REV_WAR_MAGIC_B0                            0x24
#define DATA_FORMAT_REV_WAR_MAGIC_B1                            0x11
#define DATA_FORMAT_REV_WAR_MAGIC_B2                            0x42

#define MAX_TEST_NAME_SIZE                                      ((size_t)256)
#define MAX_TEST_OUTPUT_SIZE                                    ((size_t)0x40000) /* 256k */

#define JEDEC_ID_32_SIZE                                        sizeof(u_int32_t)
#define MAC_ADDRESS_SIZE                                        ((size_t)6)
#define MAC_OUI_SIZE                                            ((size_t)3)

#define FS_PRODUCT_CLASS_ID_SIZE                                sizeof(u_int16_t)
#define SUBSYSTEM_ID_SIZE                                       sizeof(u_int16_t)
#define SUBVENDOR_ID_SIZE                                       sizeof(u_int16_t)
#define CPU_REV_ID_SIZE                                         sizeof(u_int32_t)
#define RADIO_REV_ID_SIZE                                       sizeof(u_int32_t)
#define FCD_ID_SIZE                                             sizeof(u_int16_t)
#define FCD_VERSION_SIZE                                        sizeof(u_int32_t)
#define SW_ID_SIZE                                              sizeof(u_int16_t)
#define SW_VERSION_SIZE                                         sizeof(u_int32_t)

#define BITS_IN_HASH                                            ((size_t)512)
#define ESN_SIGNATURE_SIZE                                      ((size_t)64) /* signature is symmetric block encrypted SHA512 output (512/8) */
#define SHA512_HASH_SIZE                                        ((size_t)512/8)
#define BITS_IN_RSA_KEY                                         ((size_t)4096)
#define BYTES_IN_RSA_KEY                                        ((size_t)512) /* (BITS_IN_RSA_KEY/8) */
#define RSA_SIGNATURE_SIZE                                      ((size_t)512) /* (BITS_IN_RSA_KEY/8) */
#define BYTES_IN_DER_ENCODED_RSA_KEY                            ((size_t)BYTES_IN_RSA_KEY+14) /* Not 100% sure about the +14, but validation rules will fail before a buffer overflow */
#define BIT_FOR_UID_STEGO_DATA                                  3
#define REVERSE_UID_STEGO_DATA                                  TRUE
#define BIT_FOR_PUBLIC_KEY_STEGO_DATA                           6
#define REVERSE_PUBLIC_KEY_STEGO_DATA                           TRUE
#define RADIO_CALDATA_MAGIC                                     ((u_int16_t)0xa55a)

#define BYTES_IN_UID_LENGTH_AND_LONGEST_VALUE                   (MAX_FLASH_UID_SIZE+1)
#define BITS_IN_UID_LENGTH_AND_LONGEST_VALUE                    (BYTES_IN_UID_LENGTH_AND_LONGEST_VALUE*8)

__ATTRIB_UNUSED static u_int8_t fs_empty_qr_code_FF[QR_CODE_SIZE]          = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
__ATTRIB_UNUSED static u_int8_t fs_empty_qr_code_00[QR_CODE_SIZE]          = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
__ATTRIB_UNUSED static u_int8_t fs_empty_fcd_id_FF[FCD_ID_SIZE]            = { 0xFF, 0xFF };
__ATTRIB_UNUSED static u_int8_t fs_empty_fcd_version_FF[FCD_VERSION_SIZE]  = { 0xFF, 0xFF, 0xFF, 0xFF };
__ATTRIB_UNUSED static u_int8_t fs_empty_sw_id_FF[SW_ID_SIZE]              = { 0xFF, 0xFF };
__ATTRIB_UNUSED static u_int8_t fs_empty_sw_version_FF[SW_VERSION_SIZE]    = { 0xFF, 0xFF, 0xFF, 0xFF };

// NB: This offset is for the copy in the first 4k, just after MAC0+MAC1+SSID+SVID (6+6+2+2)
// AirFiber and AirCam2 are using 16-bit value
// All others are using 32-bit value
#define PCBA_SIZE                                               sizeof(u_int32_t)
#define FLASH_BOARD_DATA_OFFSET_PCBA                            0x10
#define FLASH_BOARD_DATA_PCBA_SIZE                              PCBA_SIZE
#define FLASH_BOARD_DATA_OFFSET_BCMSWITCH_VPD                   0x20
#define FLASH_BOARD_DATA_OFFSET_ROUTER_VPD                      0x20

#define SEC_BLOCK_SIZE_64KB_EEPROM                              BLOCK_8K
#define SEC_BLOCK_SIZE_32KB_EEPROM                              SEC_BLOCK_SIZE_64KB_EEPROM
#define SEC_BLOCK_SIZE_4KB_EEPROM                               BLOCK_3K

// DETERMINE WHICH EEPROM SIZES WE NEED ---------------------------------------------------------------------------------------------------------------------------------------------------------------

#define UBNT_SUPPORT_64K_EEPROM 1
#if defined(UBNT_SUPPORT_CLASS_BASIC4K)
    #define UBNT_SUPPORT_4K_EEPROM 1
#else // #if defined(UBNT_SUPPORT_CLASS_BASIC4K)
    #define UBNT_SUPPORT_4K_EEPROM 0
#endif // #if defined(UBNT_SUPPORT_CLASS_BASIC4K)

// GENERIC STRUCTURES ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef __ATTRIB_PACKED_PRE struct reserved4k {
    __ATTRIB_PACKED_PRE union {
        u_int8_t raw[BLOCK_4K];
        __ATTRIB_PACKED_PRE struct {
            u_int8_t reserved[BLOCK_4K];
        } __ATTRIB_PACKED_POST;
    };
} __ATTRIB_PACKED_POST reserved4k_t;

typedef __ATTRIB_PACKED_PRE struct reserved8k {
    __ATTRIB_PACKED_PRE  union {
        u_int8_t raw[BLOCK_8K];
        __ATTRIB_PACKED_PRE struct {
            u_int8_t reserved[BLOCK_8K];
        } __ATTRIB_PACKED_POST;
    };
} __ATTRIB_PACKED_POST reserved8k_t;

typedef __ATTRIB_PACKED_PRE struct reserved16k {
    __ATTRIB_PACKED_PRE union {
        u_int8_t raw[BLOCK_16K];
        __ATTRIB_PACKED_PRE struct {
            u_int8_t reserved[BLOCK_16K];
        } __ATTRIB_PACKED_POST;
    };
} __ATTRIB_PACKED_POST reserved16k_t;

typedef __ATTRIB_PACKED_PRE struct reserved20k {
    __ATTRIB_PACKED_PRE union {
        u_int8_t raw[BLOCK_20K];
        __ATTRIB_PACKED_PRE struct {
            u_int8_t reserved[BLOCK_20K];
        } __ATTRIB_PACKED_POST;
    };
} __ATTRIB_PACKED_POST reserved20k_t;

typedef __ATTRIB_PACKED_PRE struct reserved28k {
    __ATTRIB_PACKED_PRE union {
        u_int8_t raw[BLOCK_28K];
        __ATTRIB_PACKED_PRE struct {
            u_int8_t reserved[BLOCK_28K];
        } __ATTRIB_PACKED_POST;
    };
} __ATTRIB_PACKED_POST reserved28k_t;

typedef __ATTRIB_PACKED_PRE struct reserved32k {
    __ATTRIB_PACKED_PRE union {
        u_int8_t raw[BLOCK_32K];
        __ATTRIB_PACKED_PRE struct {
            u_int8_t reserved[BLOCK_32K];
        } __ATTRIB_PACKED_POST;
    };
} __ATTRIB_PACKED_POST reserved32k_t;

typedef __ATTRIB_PACKED_PRE struct reserved36k {
    __ATTRIB_PACKED_PRE union {
        u_int8_t raw[BLOCK_36K];
        __ATTRIB_PACKED_PRE struct {
            u_int8_t reserved[BLOCK_36K];
        } __ATTRIB_PACKED_POST;
    };
} __ATTRIB_PACKED_POST reserved36k_t;

typedef __ATTRIB_PACKED_PRE struct calibration_data {
    __ATTRIB_PACKED_PRE union {
        u_int8_t raw[BLOCK_16K];
        __ATTRIB_PACKED_PRE struct {
            u_int16_t magic;
            u_int8_t  reserved[BLOCK_16K - 2];
#if (defined(__GNUG__) && (__GNUC__ >= 6))
        } __ATTRIB_PACKED_POST;
#else
        } __ATTRIB_PACKED_POST calibration_data;
#endif
    } __ATTRIB_PACKED_POST;
}  __ATTRIB_PACKED_POST calibration_data_t;

typedef __ATTRIB_PACKED_PRE struct board_data_4k {
    __ATTRIB_PACKED_PRE union {
        u_int8_t raw[BLOCK_4K];
        __ATTRIB_PACKED_PRE struct {
            u_int8_t reserved[BLOCK_4K];
#if (defined(__GNUG__) && (__GNUC__ >= 6))
        } __ATTRIB_PACKED_POST;
#else
        } __ATTRIB_PACKED_POST board_data;
#endif
    } __ATTRIB_PACKED_POST;
}  __ATTRIB_PACKED_POST board_data_4k_t;

typedef __ATTRIB_PACKED_PRE struct board_data_512 {
    __ATTRIB_PACKED_PRE union {
        u_int8_t raw[BLOCK_512];
        __ATTRIB_PACKED_PRE struct {
              u_int8_t reserved[512];
        } __ATTRIB_PACKED_POST;
    } __ATTRIB_PACKED_POST;
}  __ATTRIB_PACKED_POST board_data_512_t;

// COMMON ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define FLASH_SECURITY_DATA_LEADING_COMMON_FIELDS               /* [All Revisions] */ \
     u_int8_t   format;                                         /*     1 bytes - NA - format */ \
     u_int8_t   revision;                                       /*     1 bytes - NA - revision */ \
     u_int16_t  manufacturer_id;                                /*     2 bytes - BE - manufacturer ID */ \
     u_int64_t  device_id;                                      /*     8 bytes - BE - unique device identifier */ \
     u_int64_t  registration_id;                                /*     8 bytes - BE - registration transaction ID */ \
     u_int64_t  registration_timestamp;                         /*     8 bytes - BE - seconds elapsed since 00:00 hours, Jan 1, 1970 UTC */ \
     u_int16_t  product_class_id;                               /*     2 bytes - BE - see protocol.h */ \
     u_int16_t  subsystem_id;                                   /*     2 bytes - BE - subsystem ID */ \
     u_int16_t  subvendor_id;                                   /*     2 bytes - BE - subvendor ID */ \
     u_int8_t   eth0_mac_address[MAC_ADDRESS_SIZE];             /*     6 bytes - BE - eth0 MAC */ \
     u_int8_t   eth1_mac_address[MAC_ADDRESS_SIZE];             /*     6 bytes - BE - eth1 MAC */ \
     u_int32_t  flash_jedec_id;                                 /*     4 bytes - BE - see protocol-rev1.h */ \
     u_int8_t   flash_uid_length;                               /*     1 bytes - NA - Length of UID data */ \
     u_int8_t   flash_uid[MAX_FLASH_UID_SIZE];                  /*   128 bytes - NA - Flash UID byte array */

#define FLASH_SECURITY_DATA_TRAILING_COMMON_FIELDS              /* [All Revisions] */ \
     u_int8_t   esn_sig_iv_area[SIG_IV_AREA_SIZE];              /*   128 bytes - NA - Initialization vector for digital signature using symmetric cryptography based on ESN. */ \
     u_int8_t   esn_signature[ESN_SIGNATURE_SIZE];              /*    64 bytes - NA - Digital signature using symmetric cryptography based on ESN */ \
     u_int8_t   ubnt_signature[RSA_SIGNATURE_SIZE];             /*   512 bytes - NA - RSA signature */

/* These structs are unused exept for size calculations */
__ATTRIB_PACKED_PRE struct __sz_flash_security_data_leading_common_fields {
    FLASH_SECURITY_DATA_LEADING_COMMON_FIELDS
} __ATTRIB_PACKED_POST;

__ATTRIB_PACKED_PRE struct __sz_flash_security_data_trailing_common_fields {
    FLASH_SECURITY_DATA_TRAILING_COMMON_FIELDS
} __ATTRIB_PACKED_POST;

#if UBNT_LINUX
    #define DECLARE_FLASH_SECURITY_DATA_STRUCTURES_SANITY_CHECK(__CLASS__, __FIELDS__,__SEC_BLOCK_SIZE__) \
        /* Check that the field structure size is correct and the final struct size is correct */ \
        typedef struct { \
            u_int8_t __CLASS__ ## _fields_size_ok[(sizeof(struct __sz_check_ ## __CLASS__ ## _fields) == __SEC_BLOCK_SIZE__ ) ? 0 : -1]; \
            u_int8_t __CLASS__ ## _flash_eeprom_security_data_ok[(sizeof(struct __CLASS__ ## _flash_eeprom_security_data) == __SEC_BLOCK_SIZE__ ) ? 0 : -1]; \
        } __CLASS__ ## _check_struct_sizes; \

#else // #if UBNT_LINUX
    #define DECLARE_FLASH_SECURITY_DATA_STRUCTURES_SANITY_CHECK(__CLASS__, __FIELDS__,__SEC_BLOCK_SIZE__)
#endif // #if UBNT_LINUX

#define DECLARE_FLASH_SECURITY_DATA_STRUCTURES(__CLASS__, __FIELDS__,__SEC_BLOCK_SIZE__) \
    /* Used to calculate size of all class-specific fields */ \
    __ATTRIB_PACKED_PRE struct __sz_ ## __CLASS__ ## _fields { __FIELDS__ } __ATTRIB_PACKED_POST; \
    /* Used to validate that size of fields is calculated correctly (struct above is not padded) */ \
    __ATTRIB_PACKED_PRE struct __sz_check_ ## __CLASS__ ## _fields { \
        /* First add leading common fields */ \
        FLASH_SECURITY_DATA_LEADING_COMMON_FIELDS \
        /* Now add class-specific fields (if any) */ \
        __FIELDS__ \
        /* Automatically pad the reserved area member */ \
        u_int8_t reserved[__SEC_BLOCK_SIZE__ - sizeof(struct __sz_flash_security_data_leading_common_fields) - sizeof(struct __sz_flash_security_data_trailing_common_fields) - sizeof(struct __sz_ ## __CLASS__ ## _fields)]; \
        /* Now add trailing common fields */ \
        FLASH_SECURITY_DATA_TRAILING_COMMON_FIELDS \
    } __ATTRIB_PACKED_POST; \
    \
    /* This is the data structure we are really trying to define here */ \
    typedef __ATTRIB_PACKED_PRE struct __CLASS__ ## _flash_eeprom_security_data { \
        __ATTRIB_PACKED_PRE union { \
            u_int8_t raw[__SEC_BLOCK_SIZE__]; \
            __ATTRIB_PACKED_PRE struct { \
                /* First add leading common fields */ \
                FLASH_SECURITY_DATA_LEADING_COMMON_FIELDS \
                /* Now add class-specific fields (if any) */ \
                __FIELDS__ \
                /* Automatically pad the reserved area member */ \
                u_int8_t reserved[__SEC_BLOCK_SIZE__ - sizeof(struct __sz_flash_security_data_leading_common_fields) - sizeof(struct __sz_flash_security_data_trailing_common_fields) - sizeof(struct __sz_ ## __CLASS__ ## _fields)]; \
                /* Now add trailing common fields */ \
                FLASH_SECURITY_DATA_TRAILING_COMMON_FIELDS \
            } __ATTRIB_PACKED_POST; \
        } __ATTRIB_PACKED_POST; \
    } __ATTRIB_PACKED_POST __CLASS__ ## _flash_eeprom_security_data_t; \
    \
    /* On some compilers, we can do a sanity check... */ \
    DECLARE_FLASH_SECURITY_DATA_STRUCTURES_SANITY_CHECK(__CLASS__,__FIELDS__,__SEC_BLOCK_SIZE__)

#define __FLASH_SECTION_OFFSET(__CLASS__,__SECTION__)                    ((uintptr_t)(offsetof(struct __CLASS__ ## _flash_eeprom, __SECTION__)))
#define __FLASH_CLASS_SPECIFIC_SEC_OFFSET(__CLASS__,__FIELD__)            ((uintptr_t)(__FLASH_SECTION_OFFSET(__CLASS__, security_data) + offsetof(struct __CLASS__ ## _flash_eeprom_security_data,__FIELD__))) /* Security data is 40k from start of flash config block */

/* 
   This guys' job is to find a security field offset based on the EEPROM we have,
   without exceeding the limits of the EEPROM.
 
   If we only have 4K or 64K then it's easy, but if we have both then we can do a check for magic.
*/
#if UBNT_SUPPORT_4K_EEPROM && UBNT_SUPPORT_64K_EEPROM
    #define fs_get_config_size() \
        ((fs_read_config_be32toh(MAGIC_4K_MARKER_OFFSET) == MAGIC_4K_MARKER_VALUE) \
            ? BLOCK_4K \
            : BLOCK_64K)
    #define __FLASH_COMMON_SEC_OFFSET(__FIELD__) \
        ((fs_read_config_be32toh(MAGIC_4K_MARKER_OFFSET) == MAGIC_4K_MARKER_VALUE) \
            ? __FLASH_CLASS_SPECIFIC_SEC_OFFSET(generic4k,__FIELD__) \
            : __FLASH_CLASS_SPECIFIC_SEC_OFFSET(generic64k,__FIELD__))
#elif UBNT_SUPPORT_4K_EEPROM
    #define fs_get_config_size() (BLOCK_4K)
    #define __FLASH_COMMON_SEC_OFFSET(__FIELD__) __FLASH_CLASS_SPECIFIC_SEC_OFFSET(generic4k,__FIELD__)
#else
    #define fs_get_config_size() (BLOCK_64K)
    #define __FLASH_COMMON_SEC_OFFSET(__FIELD__) __FLASH_CLASS_SPECIFIC_SEC_OFFSET(generic64k,__FIELD__)
#endif

// NB: We have to have at least one byte of class-specific data, since an empty
// structure, when used to determine fields size, will compile to size 0 in C
// and size 1 in C++.  Also, we must NOT use all available space because some
// compilers will barf on a "reserved" field size of zero.
#define GENERIC_FLASH_SECURITY_DATA_FIELDS \
    u_int8_t  class_specific[1];

DECLARE_FLASH_SECURITY_DATA_STRUCTURES(generic64k, GENERIC_FLASH_SECURITY_DATA_FIELDS, SEC_BLOCK_SIZE_64KB_EEPROM)
DECLARE_FLASH_SECURITY_DATA_STRUCTURES(generic4k, GENERIC_FLASH_SECURITY_DATA_FIELDS, SEC_BLOCK_SIZE_4KB_EEPROM)

#define FLASH_SECURITY_OFFSET_FORMAT                                    __FLASH_COMMON_SEC_OFFSET(format)
#define FLASH_SECURITY_OFFSET_REVISION                                  __FLASH_COMMON_SEC_OFFSET(revision)
#define FLASH_SECURITY_OFFSET_MANUFACTURER_ID                           __FLASH_COMMON_SEC_OFFSET(manufacturer_id)
#define FLASH_SECURITY_OFFSET_DEVICE_ID                                 __FLASH_COMMON_SEC_OFFSET(device_id)
#define FLASH_SECURITY_OFFSET_REGISTRATION_ID                           __FLASH_COMMON_SEC_OFFSET(registration_id)
#define FLASH_SECURITY_OFFSET_REGISTRATION_TIMESTAMP                    __FLASH_COMMON_SEC_OFFSET(registration_timestamp)
#define FLASH_SECURITY_OFFSET_PRODUCT_CLASS_ID                          __FLASH_COMMON_SEC_OFFSET(product_class_id)
#define FLASH_SECURITY_OFFSET_SUBSYSTEM_ID                              __FLASH_COMMON_SEC_OFFSET(subsystem_id)
#define FLASH_SECURITY_OFFSET_SUBVENDOR_ID                              __FLASH_COMMON_SEC_OFFSET(subvendor_id)
#define FLASH_SECURITY_OFFSET_ETH0_MAC_ADDRESS                          __FLASH_COMMON_SEC_OFFSET(eth0_mac_address)
#define FLASH_SECURITY_OFFSET_ETH1_MAC_ADDRESS                          __FLASH_COMMON_SEC_OFFSET(eth1_mac_address)
#define FLASH_SECURITY_OFFSET_FLASH_JEDEC_ID                            __FLASH_COMMON_SEC_OFFSET(flash_jedec_id)
#define FLASH_SECURITY_OFFSET_FLASH_UID_LENGTH                          __FLASH_COMMON_SEC_OFFSET(flash_uid_length)
#define FLASH_SECURITY_OFFSET_FLASH_UID                                 __FLASH_COMMON_SEC_OFFSET(flash_uid)
#define FLASH_SECURITY_OFFSET_ESN_SIG_IV_AREA                           __FLASH_COMMON_SEC_OFFSET(esn_sig_iv_area)
#define FLASH_SECURITY_OFFSET_ESN_SIGNATURE                             __FLASH_COMMON_SEC_OFFSET(esn_signature)
#define FLASH_SECURITY_OFFSET_UBNT_SIGNATURE                            __FLASH_COMMON_SEC_OFFSET(ubnt_signature)
/* ESN signature covers everything from 4K up to the signature itself */
#define FLASH_SECURITY_OFFSET_ESN_SIGNED_START(__CLASS__)               __FLASH_SECTION_OFFSET(__CLASS__, device_data)
#define FLASH_SECURITY_OFFSET_ESN_SIGNED_END(__CLASS__)                 __FLASH_CLASS_SPECIFIC_SEC_OFFSET(__CLASS__,esn_sig_iv_area)

/* UBNT signature covers everything from 4K up to the signature itself */
#define FLASH_SECURITY_OFFSET_UBNT_SIGNED_START(__CLASS__)              __FLASH_SECTION_OFFSET(__CLASS__, device_data)
#define FLASH_SECURITY_OFFSET_UBNT_SIGNED_END(__CLASS__)                __FLASH_CLASS_SPECIFIC_SEC_OFFSET(__CLASS__,ubnt_signature)

typedef __ATTRIB_PACKED_PRE struct hidden_data {
    __ATTRIB_PACKED_PRE union {
        u_int8_t raw[BLOCK_4K];
        __ATTRIB_PACKED_PRE struct {
            u_int8_t hidden_key[BITS_IN_RSA_KEY]; // 4K
        } __ATTRIB_PACKED_POST;
        __ATTRIB_PACKED_PRE struct {
            u_int8_t __hidden_uid_pad[BITS_IN_RSA_KEY-BITS_IN_UID_LENGTH_AND_LONGEST_VALUE];
            u_int8_t hidden_uid[BITS_IN_UID_LENGTH_AND_LONGEST_VALUE];
        } __ATTRIB_PACKED_POST;
    } __ATTRIB_PACKED_POST;
} __ATTRIB_PACKED_POST hidden_data_t;

typedef __ATTRIB_PACKED_PRE struct generic64k_flash_eeprom {
    __ATTRIB_PACKED_PRE union {
        // Whole EEPROM as a byte array
        u_int8_t raw[BLOCK_64K];
        // EEPROM map breakdown
        __ATTRIB_PACKED_PRE struct {
            board_data_4k_t                            board_data;                  //  4K - Unsigned
            u_int8_t                                   device_data[BLOCK_32K];      // 32K - Signed
            hidden_data_t                              hidden_data;                 //  4K - Signed (random data with RSA public key and flash UID hidden in it).
            generic64k_flash_eeprom_security_data_t    security_data;               //  8K - Signed
            reserved16k_t                              reserved2;                   // 16K - Unsigned
        } __ATTRIB_PACKED_POST;
    } __ATTRIB_PACKED_POST;
} __ATTRIB_PACKED_POST generic64k_flash_eeprom_t;

typedef __ATTRIB_PACKED_PRE struct generic4k_flash_eeprom {
    __ATTRIB_PACKED_PRE union {
        // Whole EEPROM as a byte array
        u_int8_t raw[BLOCK_4K];
        // EEPROM map breakdown
        __ATTRIB_PACKED_PRE struct {
            board_data_512_t                           board_data;                  // 512 - Unsigned
            u_int8_t                                   device_data[BLOCK_512];      // 512 - Signed
            generic4k_flash_eeprom_security_data_t     security_data;               //  3K - Signed
        } __ATTRIB_PACKED_POST;
    } __ATTRIB_PACKED_POST;
} __ATTRIB_PACKED_POST generic4k_flash_eeprom_t;

// WIFI -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define WIFI_FLASH_SECURITY_DATA_FIELDS \
                                                                /* [Revision 1+] */ \
    u_int32_t  cpu_rev_id;                                      /*     4 bytes - BE - cpu rev ID */ \
    u_int32_t  radio1_rev_id;                                   /*     4 bytes - BE - radio 1 silicon revision */ \
    u_int32_t  radio2_rev_id;                                   /*     4 bytes - BE - radio 2 silicon revision */ \
    u_int8_t   radio1_mac_address[MAC_ADDRESS_SIZE];            /*     6 bytes - NA - radio 1 MAC address */ \
    u_int8_t   radio2_mac_address[MAC_ADDRESS_SIZE];            /*     6 bytes - NA - radio 1 MAC address */ \
                                                                /* [Revision 2+] */ \
    u_int8_t   revision_war_magic[DATA_REV_WAR_MAGIC_SIZE];     /*     3 bytes - NA - magic value used to indicate data format revision workaround */ \
    u_int8_t   alt_revision;                                    /*     1 bytes - NA - data format revision (supercedes revision in common location due to workaround) */ \
    u_int32_t  pcba;                                            /*     4 bytes - BE - PCBA (Format - high 24-bits BE PCBA part number, low 8 bits PCBA revision) */ \
    u_int8_t   qr_code[QR_CODE_SIZE];                           /*     6 bytes - NA - Adoption QR code */ \
                                                                /* [Revision 3+] */ \
    u_int16_t  fcd_id;                                          /*     2 bytes - BE - encoded FCD ID (see docs) */ \
    u_int32_t  fcd_version;                                     /*     4 bytes - BE - encoded FCD version */ \
    u_int16_t  sw_id;                                           /*     2 bytes - BE - encoded SW ID (see docs) */ \
    u_int32_t  sw_version;                                      /*     4 bytes - BE - encoded initial firmware version */

DECLARE_FLASH_SECURITY_DATA_STRUCTURES(wifi,WIFI_FLASH_SECURITY_DATA_FIELDS,SEC_BLOCK_SIZE_64KB_EEPROM)

#define FLASH_SECURITY_OFFSET_WIFI_CPU_REV_ID                   __FLASH_CLASS_SPECIFIC_SEC_OFFSET(wifi,cpu_rev_id)
#define FLASH_SECURITY_OFFSET_WIFI_RADIO1_REV_ID                __FLASH_CLASS_SPECIFIC_SEC_OFFSET(wifi,radio1_rev_id)
#define FLASH_SECURITY_OFFSET_WIFI_RADIO2_REV_ID                __FLASH_CLASS_SPECIFIC_SEC_OFFSET(wifi,radio2_rev_id)
#define FLASH_SECURITY_OFFSET_WIFI_RADIO1_MAC_ADDRESS           __FLASH_CLASS_SPECIFIC_SEC_OFFSET(wifi,radio1_mac_address)
#define FLASH_SECURITY_OFFSET_WIFI_RADIO2_MAC_ADDRESS           __FLASH_CLASS_SPECIFIC_SEC_OFFSET(wifi,radio2_mac_address)
#define FLASH_SECURITY_OFFSET_WIFI_REVISION_WAR_MAGIC           __FLASH_CLASS_SPECIFIC_SEC_OFFSET(wifi,revision_war_magic)
#define FLASH_SECURITY_OFFSET_WIFI_ALT_REVISION                 __FLASH_CLASS_SPECIFIC_SEC_OFFSET(wifi,alt_revision)
#define FLASH_SECURITY_OFFSET_WIFI_PCBA                         __FLASH_CLASS_SPECIFIC_SEC_OFFSET(wifi,pcba)
#define FLASH_SECURITY_OFFSET_WIFI_QR_CODE                      __FLASH_CLASS_SPECIFIC_SEC_OFFSET(wifi,qr_code)
#define FLASH_SECURITY_OFFSET_WIFI_FCD_ID                       __FLASH_CLASS_SPECIFIC_SEC_OFFSET(wifi,fcd_id)
#define FLASH_SECURITY_OFFSET_WIFI_FCD_VERSION                  __FLASH_CLASS_SPECIFIC_SEC_OFFSET(wifi,fcd_version)
#define FLASH_SECURITY_OFFSET_WIFI_SW_ID                        __FLASH_CLASS_SPECIFIC_SEC_OFFSET(wifi,sw_id)
#define FLASH_SECURITY_OFFSET_WIFI_SW_VERSION                   __FLASH_CLASS_SPECIFIC_SEC_OFFSET(wifi,sw_version)
#define FLASH_SECURITY_OFFSET_WIFI_RESERVED                     __FLASH_CLASS_SPECIFIC_SEC_OFFSET(wifi,reserved)

typedef __ATTRIB_PACKED_PRE struct wifi_flash_eeprom {
    __ATTRIB_PACKED_PRE union {
        // Whole EEPROM as a byte array
        u_int8_t raw[BLOCK_64K];
        // EEPROM map breakdown
        __ATTRIB_PACKED_PRE struct {
            board_data_4k_t                            board_data;              //  4K - Unsigned
            __ATTRIB_PACKED_PRE union {
                u_int8_t                               device_data[BLOCK_32K];
                __ATTRIB_PACKED_PRE struct {
                    calibration_data_t                 radio1_calibration_data; // 16K - Signed (except if it's a digital board)
                    calibration_data_t                 radio2_calibration_data; // 16K - Signed (except if it's a digital board)
                } __ATTRIB_PACKED_POST;
            } __ATTRIB_PACKED_POST;
            hidden_data_t                              hidden_data;             //  4K - Signed (random data with RSA public key and flash UID hidden in it).
            wifi_flash_eeprom_security_data_t          security_data;           //  8K - Signed
            reserved16k_t                              reserved2;               // 16K - Unsigned
        } __ATTRIB_PACKED_POST;
    } __ATTRIB_PACKED_POST;
} __ATTRIB_PACKED_POST wifi_flash_eeprom_t;

// WIFI RADIO 32K EEPROM ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define WIFI_RADIO_32K_EEPROM_SECURITY_DATA_FIELDS \
                                                                /* [Revision 1+] */ \
    u_int8_t   format;                                          /*     1 bytes - NA - format */ \
    u_int8_t   revision;                                        /*     1 bytes - NA - revision */ \
    u_int16_t  manufacturer_id;                                 /*     2 bytes - BE - manufacturer ID */ \
    u_int64_t  device_id;                                       /*     8 bytes - BE - unique device identifier */ \
    u_int64_t  registration_id;                                 /*     8 bytes - BE - registration transaction ID */ \
    u_int64_t  registration_timestamp;                          /*     8 bytes - BE - seconds elapsed since 00:00 hours, Jan 1, 1970 UTC */ \
    u_int16_t  product_class_id;                                /*     2 bytes - BE - see protocol.h */ \
    u_int16_t  subsystem_id;                                    /*     2 bytes - BE - subsystem ID */ \
    u_int16_t  subvendor_id;                                    /*     2 bytes - BE - subvendor ID */ \
    u_int32_t  radio_rev_id;                                    /*     4 bytes - BE - radio silicon revision */ \
    u_int8_t   radio_mac_address[MAC_ADDRESS_SIZE];             /*     6 bytes - NA - radio 1 MAC address */ \
                                                                /* [Revision 2+] */ \
    u_int8_t   revision_war_magic[DATA_REV_WAR_MAGIC_SIZE];     /*     3 bytes - NA - magic value used to indicate data format revision workaround */ \
    u_int8_t   alt_revision;                                    /*     1 bytes - NA - data format revision (supercedes revision in common location due to workaround) */ \
    u_int32_t  pcba;                                            /*     4 bytes - BE - PCBA (Format - high 24-bits BE PCBA part number, low 8 bits PCBA revision) */ \
    u_int8_t   qr_code[QR_CODE_SIZE];                           /*     6 bytes - NA - Adoption QR code */ \
                                                                /* [Revision 3+] */ \
    u_int16_t  fcd_id;                                          /*     2 bytes - BE - encoded FCD ID (see docs) */ \
    u_int32_t  fcd_version;                                     /*     4 bytes - BE - encoded FCD version */ \
    u_int16_t  sw_id;                                           /*     2 bytes - BE - encoded SW ID (see docs) */ \
    u_int32_t  sw_version;                                      /*     4 bytes - BE - encoded initial firmware version */


__ATTRIB_PACKED_PRE struct __sz_wifi_radio_32k_fields { WIFI_RADIO_32K_EEPROM_SECURITY_DATA_FIELDS } __ATTRIB_PACKED_POST;
typedef __ATTRIB_PACKED_PRE struct wifi_radio_32k_eeprom_security_data {
        __ATTRIB_PACKED_PRE union {
            u_int8_t raw[SEC_BLOCK_SIZE_32KB_EEPROM];
           __ATTRIB_PACKED_PRE struct {
                WIFI_RADIO_32K_EEPROM_SECURITY_DATA_FIELDS
                u_int8_t reserved[SEC_BLOCK_SIZE_32KB_EEPROM - sizeof(struct __sz_wifi_radio_32k_fields) - RSA_SIGNATURE_SIZE]; /* Automatically pad the reserved area member */
                u_int8_t ubnt_signature [RSA_SIGNATURE_SIZE];   /*   512 bytes - NA - RSA signature */
            } __ATTRIB_PACKED_POST;
        } __ATTRIB_PACKED_POST;
    } __ATTRIB_PACKED_POST wifi_radio_32k_eeprom_security_data_t;

#define __32K_EEPROM_SEC_OFFSET(__FIELD__)                       ((uintptr_t)(BLOCK_24K + offsetof(wifi_radio_32k_eeprom_security_data_t,__FIELD__))) /* Security data is 24K from start of 32K EEPROM block */

#define RADIO_EEPROM_SECURITY_OFFSET_FORMAT                     __32K_EEPROM_SEC_OFFSET(format)
#define RADIO_EEPROM_SECURITY_OFFSET_REVISION                   __32K_EEPROM_SEC_OFFSET(revision)
#define RADIO_EEPROM_SECURITY_OFFSET_MANUFACTURER_ID            __32K_EEPROM_SEC_OFFSET(manufacturer_id)
#define RADIO_EEPROM_SECURITY_OFFSET_DEVICE_ID                  __32K_EEPROM_SEC_OFFSET(device_id)
#define RADIO_EEPROM_SECURITY_OFFSET_REGISTRATION_ID            __32K_EEPROM_SEC_OFFSET(registration_id)
#define RADIO_EEPROM_SECURITY_OFFSET_REGISTRATION_TIMESTAMP     __32K_EEPROM_SEC_OFFSET(registration_timestamp)
#define RADIO_EEPROM_SECURITY_OFFSET_PRODUCT_CLASS_ID           __32K_EEPROM_SEC_OFFSET(product_class_id)
#define RADIO_EEPROM_SECURITY_OFFSET_SUBSYSTEM_ID               __32K_EEPROM_SEC_OFFSET(subsystem_id)
#define RADIO_EEPROM_SECURITY_OFFSET_SUBVENDOR_ID               __32K_EEPROM_SEC_OFFSET(subvendor_id)
#define RADIO_EEPROM_SECURITY_OFFSET_RADIO_REV_ID               __32K_EEPROM_SEC_OFFSET(radio_rev_id)
#define RADIO_EEPROM_SECURITY_OFFSET_RADIO_MAC_ADDRESS          __32K_EEPROM_SEC_OFFSET(radio_mac_address)
#define RADIO_EEPROM_SECURITY_OFFSET_REVISION_WAR_MAGIC         __32K_EEPROM_SEC_OFFSET(revision_war_magic)
#define RADIO_EEPROM_SECURITY_OFFSET_ALT_REVISION               __32K_EEPROM_SEC_OFFSET(alt_revision)
#define RADIO_EEPROM_SECURITY_OFFSET_BOARD_REV_ID               __32K_EEPROM_SEC_OFFSET(pcba)
#define RADIO_EEPROM_SECURITY_OFFSET_QR_CODE                    __32K_EEPROM_SEC_OFFSET(qr_code)
#define RADIO_EEPROM_SECURITY_OFFSET_SWITCH_FCD_ID              __32K_EEPROM_SEC_OFFSET(fcd_id)
#define RADIO_EEPROM_SECURITY_OFFSET_SWITCH_FCD_VERSION         __32K_EEPROM_SEC_OFFSET(fcd_version)
#define RADIO_EEPROM_SECURITY_OFFSET_SWITCH_SW_ID               __32K_EEPROM_SEC_OFFSET(sw_id)
#define RADIO_EEPROM_SECURITY_OFFSET_SWITCH_SW_VERSION          __32K_EEPROM_SEC_OFFSET(sw_version)
#define RADIO_EEPROM_SECURITY_OFFSET_RESERVED                   __32K_EEPROM_SEC_OFFSET(reserved)
#define RADIO_EEPROM_SECURITY_OFFSET_UBNT_SIGNATURE             __32K_EEPROM_SEC_OFFSET(ubnt_signature)
#define RADIO_EEPROM_SECURITY_OFFSET_UBNT_SIGNED_START           ((uintptr_t)(0)) // Seems we signed the 24k of unused area too?
#define RADIO_EEPROM_SECURITY_OFFSET_UBNT_SIGNED_END             ((uintptr_t)(RADIO_EEPROM_SECURITY_OFFSET_UBNT_SIGNATURE))
#define RADIO_EEPROM_SECURITY_OFFSET_UBNT_SIGNED_LENGTH          ((uintptr_t)(RADIO_EEPROM_SECURITY_OFFSET_UBNT_SIGNED_END - RADIO_EEPROM_SECURITY_OFFSET_UBNT_SIGNED_START))

typedef __ATTRIB_PACKED_PRE struct wifi_radio_32k_eeprom {
    __ATTRIB_PACKED_PRE union {
        // Whole EEPROM as a byte array (maximum standalone EEPROM size)
        u_int8_t raw[BLOCK_32K];
        // EEPROM map breakdown
        __ATTRIB_PACKED_PRE struct {
            calibration_data_t                         radio_calibration_data;  // 16K - Signed
            reserved4k_t                               device_data;             //  4K - Signed
            hidden_data_t                              hidden_data;             //  4K - Signed (Random data with RSA public key and flash UID hidden in it).
            wifi_radio_32k_eeprom_security_data_t      security_data;           //  8K - Signed
        } __ATTRIB_PACKED_POST;
    } __ATTRIB_PACKED_POST;
} __ATTRIB_PACKED_POST wifi_radio_32k_eeprom_t;

typedef __ATTRIB_PACKED_PRE struct wifi_radio_eeprom {
    size_t eeprom_size;
    __ATTRIB_PACKED_PRE union {
        u_int8_t                                       raw[BLOCK_32K];
        wifi_radio_32k_eeprom_t                        eeprom_32k;
        // ... others ...
    } __ATTRIB_PACKED_POST;
} __ATTRIB_PACKED_POST wifi_radio_eeprom_t;

// SWITCH ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define SWITCH_FLASH_SECURITY_DATA_FIELDS \
                                                                /* [Revision 1+] */ \
    u_int32_t  cpu_rev_id;                                      /*     4 bytes - BE - cpu rev ID */ \
                                                                /* [Revision 2+] */ \
    u_int8_t   revision_war_magic[DATA_REV_WAR_MAGIC_SIZE];     /*     3 bytes - NA - magic value used to indicate data format revision workaround */ \
    u_int8_t   alt_revision;                                    /*     1 bytes - NA - data format revision (supercedes revision in common location due to workaround) */ \
    u_int32_t  pcba;                                            /*     4 bytes - BE - PCBA (Format - high 24-bits BE PCBA part number, low 8 bits PCBA revision) */ \
    u_int8_t   qr_code[QR_CODE_SIZE];                           /*     6 bytes - NA - Adoption QR code */ \
                                                                /* [Revision 3+] */ \
    u_int16_t  fcd_id;                                          /*     2 bytes - BE - encoded FCD ID (see docs) */ \
    u_int32_t  fcd_version;                                     /*     4 bytes - BE - encoded FCD version */ \
    u_int16_t  sw_id;                                           /*     2 bytes - BE - encoded SW ID (see docs) */ \
    u_int32_t  sw_version;                                      /*     4 bytes - BE - encoded initial firmware version */

DECLARE_FLASH_SECURITY_DATA_STRUCTURES(switch,SWITCH_FLASH_SECURITY_DATA_FIELDS,SEC_BLOCK_SIZE_64KB_EEPROM)

#define FLASH_SECURITY_OFFSET_SWITCH_CPU_REV_ID                 __FLASH_CLASS_SPECIFIC_SEC_OFFSET(switch,cpu_rev_id)
#define FLASH_SECURITY_OFFSET_SWITCH_REVISION_WAR_MAGIC         __FLASH_CLASS_SPECIFIC_SEC_OFFSET(switch,revision_war_magic)
#define FLASH_SECURITY_OFFSET_SWITCH_ALT_REVISION               __FLASH_CLASS_SPECIFIC_SEC_OFFSET(switch,alt_revision)
#define FLASH_SECURITY_OFFSET_SWITCH_PCBA                       __FLASH_CLASS_SPECIFIC_SEC_OFFSET(switch,pcba)
#define FLASH_SECURITY_OFFSET_SWITCH_QR_CODE                    __FLASH_CLASS_SPECIFIC_SEC_OFFSET(switch,qr_code)
#define FLASH_SECURITY_OFFSET_SWITCH_FCD_ID                     __FLASH_CLASS_SPECIFIC_SEC_OFFSET(switch,fcd_id)
#define FLASH_SECURITY_OFFSET_SWITCH_FCD_VERSION                __FLASH_CLASS_SPECIFIC_SEC_OFFSET(switch,fcd_version)
#define FLASH_SECURITY_OFFSET_SWITCH_SW_ID                      __FLASH_CLASS_SPECIFIC_SEC_OFFSET(switch,sw_id)
#define FLASH_SECURITY_OFFSET_SWITCH_SW_VERSION                 __FLASH_CLASS_SPECIFIC_SEC_OFFSET(switch,sw_version)
#define FLASH_SECURITY_OFFSET_SWITCH_RESERVED                   __FLASH_CLASS_SPECIFIC_SEC_OFFSET(switch,reserved)

typedef __ATTRIB_PACKED_PRE struct switch_device_data {
    __ATTRIB_PACKED_PRE union {
        u_int8_t raw[BLOCK_32K];
        __ATTRIB_PACKED_PRE struct {
            u_int16_t magic;
            u_int8_t  reserved[BLOCK_32K - 2];
        } __ATTRIB_PACKED_POST;
    } __ATTRIB_PACKED_POST;
}  __ATTRIB_PACKED_POST switch_device_data_t;

typedef __ATTRIB_PACKED_PRE struct switch_flash_eeprom {
    __ATTRIB_PACKED_PRE union {
        // Whole EEPROM as a byte array
        u_int8_t raw[BLOCK_64K];
        // EEPROM map breakdown
        __ATTRIB_PACKED_PRE struct {
            board_data_4k_t                            board_data;              //  4K - Unsigned
            switch_device_data_t                       device_data;             // 32K - Signed
            hidden_data_t                              hidden_data;             //  4K - Signed (Random data with RSA public key and flash UID hidden in it).
            switch_flash_eeprom_security_data_t        security_data;           //  8K - Signed
            reserved16k_t                              reserved2;               // 16K - Unsigned
        } __ATTRIB_PACKED_POST;
    } __ATTRIB_PACKED_POST;
} __ATTRIB_PACKED_POST switch_flash_eeprom_t;

// BASIC ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define BASIC_FLASH_SECURITY_DATA_FIELDS \
                                                                /* [Revision 2+] */ \
    u_int32_t  cpu_rev_id;                                      /*     4 bytes - BE - cpu rev ID */ \
    u_int32_t  pcba;                                            /*     4 bytes - BE - PCBA (Format - high 24-bits BE PCBA part number, low 8 bits PCBA revision) */ \
    u_int8_t   qr_code[QR_CODE_SIZE];                           /*     6 bytes - NA - Adoption QR code */ \
                                                                /* [Revision 3+] */ \
    u_int16_t  fcd_id;                                          /*     2 bytes - BE - encoded FCD ID (see docs) */ \
    u_int32_t  fcd_version;                                     /*     4 bytes - BE - encoded FCD version */ \
    u_int16_t  sw_id;                                           /*     2 bytes - BE - encoded SW ID (see docs) */ \
    u_int32_t  sw_version;                                      /*     4 bytes - BE - encoded initial firmware version */

DECLARE_FLASH_SECURITY_DATA_STRUCTURES(basic,BASIC_FLASH_SECURITY_DATA_FIELDS,SEC_BLOCK_SIZE_64KB_EEPROM)

#define FLASH_SECURITY_OFFSET_BASIC_CPU_REV_ID                 __FLASH_CLASS_SPECIFIC_SEC_OFFSET(basic,cpu_rev_id)
#define FLASH_SECURITY_OFFSET_BASIC_PCBA                       __FLASH_CLASS_SPECIFIC_SEC_OFFSET(basic,pcba)
#define FLASH_SECURITY_OFFSET_BASIC_QR_CODE                    __FLASH_CLASS_SPECIFIC_SEC_OFFSET(basic,qr_code)
#define FLASH_SECURITY_OFFSET_BASIC_FCD_ID                     __FLASH_CLASS_SPECIFIC_SEC_OFFSET(basic,fcd_id)
#define FLASH_SECURITY_OFFSET_BASIC_FCD_VERSION                __FLASH_CLASS_SPECIFIC_SEC_OFFSET(basic,fcd_version)
#define FLASH_SECURITY_OFFSET_BASIC_SW_ID                      __FLASH_CLASS_SPECIFIC_SEC_OFFSET(basic,sw_id)
#define FLASH_SECURITY_OFFSET_BASIC_SW_VERSION                 __FLASH_CLASS_SPECIFIC_SEC_OFFSET(basic,sw_version)
#define FLASH_SECURITY_OFFSET_BASIC_RESERVED                   __FLASH_CLASS_SPECIFIC_SEC_OFFSET(basic,reserved)

typedef __ATTRIB_PACKED_PRE struct basic_device_data {
    __ATTRIB_PACKED_PRE union {
        u_int8_t raw[BLOCK_32K];
        __ATTRIB_PACKED_PRE struct {
            u_int16_t magic;
            u_int8_t  reserved[BLOCK_32K - 2];
        } __ATTRIB_PACKED_POST;
    } __ATTRIB_PACKED_POST;
}  __ATTRIB_PACKED_POST basic_device_data_t;

typedef __ATTRIB_PACKED_PRE struct basic_flash_eeprom {
    __ATTRIB_PACKED_PRE union {
        // Whole EEPROM as a byte array
        u_int8_t raw[BLOCK_64K];
        // EEPROM map breakdown
        __ATTRIB_PACKED_PRE struct {
            board_data_4k_t                            board_data;              //  4K - Unsigned
            basic_device_data_t                        device_data;             // 32K - Signed
            hidden_data_t                              hidden_data;             //  4K - Signed (Random data with RSA public key and flash UID hidden in it).
            basic_flash_eeprom_security_data_t         security_data;           //  8K - Signed
            reserved16k_t                              reserved2;               // 16K - Unsigned
        } __ATTRIB_PACKED_POST;
    } __ATTRIB_PACKED_POST;
} __ATTRIB_PACKED_POST basic_flash_eeprom_t;


// BASIC4K -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define BASIC4K_FLASH_SECURITY_DATA_FIELDS \
                                                                /* [Revision 2+] */ \
    u_int32_t  cpu_rev_id;                                      /*     4 bytes - BE - cpu rev ID */ \
    u_int32_t  pcba;                                            /*     4 bytes - BE - PCBA (Format - high 24-bits BE PCBA part number, low 8 bits PCBA revision) */ \
    u_int8_t   qr_code[QR_CODE_SIZE];                           /*     6 bytes - NA - Adoption QR code */ \
                                                                /* [Revision 3+] */ \
    u_int16_t  fcd_id;                                          /*     2 bytes - BE - encoded FCD ID (see docs) */ \
    u_int32_t  fcd_version;                                     /*     4 bytes - BE - encoded FCD version */ \
    u_int16_t  sw_id;                                           /*     2 bytes - BE - encoded SW ID (see docs) */ \
    u_int32_t  sw_version;                                      /*     4 bytes - BE - encoded initial firmware version */

DECLARE_FLASH_SECURITY_DATA_STRUCTURES(basic4k,BASIC4K_FLASH_SECURITY_DATA_FIELDS,SEC_BLOCK_SIZE_4KB_EEPROM)

#define FLASH_SECURITY_OFFSET_BASIC4K_CPU_REV_ID                __FLASH_CLASS_SPECIFIC_SEC_OFFSET(basic4k,cpu_rev_id)
#define FLASH_SECURITY_OFFSET_BASIC4K_PCBA                      __FLASH_CLASS_SPECIFIC_SEC_OFFSET(basic4k,pcba)
#define FLASH_SECURITY_OFFSET_BASIC4K_QR_CODE                   __FLASH_CLASS_SPECIFIC_SEC_OFFSET(basic4k,qr_code)
#define FLASH_SECURITY_OFFSET_BASIC4K_FCD_ID                    __FLASH_CLASS_SPECIFIC_SEC_OFFSET(basic4k,fcd_id)
#define FLASH_SECURITY_OFFSET_BASIC4K_FCD_VERSION               __FLASH_CLASS_SPECIFIC_SEC_OFFSET(basic4k,fcd_version)
#define FLASH_SECURITY_OFFSET_BASIC4K_SW_ID                     __FLASH_CLASS_SPECIFIC_SEC_OFFSET(basic4k,sw_id)
#define FLASH_SECURITY_OFFSET_BASIC4K_SW_VERSION                __FLASH_CLASS_SPECIFIC_SEC_OFFSET(basic4k,sw_version)
#define FLASH_SECURITY_OFFSET_BASIC4K_RESERVED                  __FLASH_CLASS_SPECIFIC_SEC_OFFSET(basic4k,reserved)

typedef __ATTRIB_PACKED_PRE struct basic4k_device_data {
    __ATTRIB_PACKED_PRE union {
        u_int8_t raw[BLOCK_512];
        __ATTRIB_PACKED_PRE struct {
            u_int8_t  reserved[BLOCK_512];
        } __ATTRIB_PACKED_POST;
    } __ATTRIB_PACKED_POST;
}  __ATTRIB_PACKED_POST basic4k_device_data_t;

typedef __ATTRIB_PACKED_PRE struct basic4k_flash_eeprom {
    __ATTRIB_PACKED_PRE union {
        // Whole EEPROM as a byte array
        u_int8_t raw[BLOCK_4K];
        // EEPROM map breakdown
        __ATTRIB_PACKED_PRE struct {
            board_data_512_t                           board_data;              //  512 - Unsigned
            basic4k_device_data_t                      device_data;             //  512 - Signed
            basic4k_flash_eeprom_security_data_t       security_data;           //   3K - Signed
        } __ATTRIB_PACKED_POST;
    } __ATTRIB_PACKED_POST;
} __ATTRIB_PACKED_POST basic4k_flash_eeprom_t;

// INVERTER -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define INVERTER_FLASH_SECURITY_DATA_FIELDS \
                                                                /* [Revision 1+] */ \
    u_int32_t  pcba;                                            /*     4 bytes - BE - PCBA (Format - high 24-bits BE PCBA part number, low 8 bits PCBA revision) */ \
    u_int8_t   qr_code[QR_CODE_SIZE];                           /*     6 bytes - NA - Adoption QR code */ \
                                                                /* [Revision 3+] */ \
    u_int16_t  fcd_id;                                          /*     2 bytes - BE - encoded FCD ID (see docs) */ \
    u_int32_t  fcd_version;                                     /*     4 bytes - BE - encoded FCD version */ \
    u_int16_t  sw_id;                                           /*     2 bytes - BE - encoded SW ID (see docs) */ \
    u_int32_t  sw_version;                                      /*     4 bytes - BE - encoded initial firmware version */

DECLARE_FLASH_SECURITY_DATA_STRUCTURES(inverter,INVERTER_FLASH_SECURITY_DATA_FIELDS,SEC_BLOCK_SIZE_64KB_EEPROM)

#define FLASH_SECURITY_OFFSET_INVERTER_PCBA                       __FLASH_CLASS_SPECIFIC_SEC_OFFSET(inverter,pcba)
#define FLASH_SECURITY_OFFSET_INVERTER_QR_CODE                    __FLASH_CLASS_SPECIFIC_SEC_OFFSET(inverter,qr_code)
#define FLASH_SECURITY_OFFSET_INVERTER_FCD_ID                     __FLASH_CLASS_SPECIFIC_SEC_OFFSET(inverter,fcd_id)
#define FLASH_SECURITY_OFFSET_INVERTER_FCD_VERSION                __FLASH_CLASS_SPECIFIC_SEC_OFFSET(inverter,fcd_version)
#define FLASH_SECURITY_OFFSET_INVERTER_SW_ID                      __FLASH_CLASS_SPECIFIC_SEC_OFFSET(inverter,sw_id)
#define FLASH_SECURITY_OFFSET_INVERTER_SW_VERSION                 __FLASH_CLASS_SPECIFIC_SEC_OFFSET(inverter,sw_version)
#define FLASH_SECURITY_OFFSET_INVERTER_RESERVED                   __FLASH_CLASS_SPECIFIC_SEC_OFFSET(inverter,reserved)

typedef __ATTRIB_PACKED_PRE struct inverter_device_data {
    __ATTRIB_PACKED_PRE union {
        u_int8_t raw[BLOCK_32K];
        __ATTRIB_PACKED_PRE struct {
            u_int8_t  reserved[BLOCK_32K];
        } __ATTRIB_PACKED_POST;
    } __ATTRIB_PACKED_POST;
}  __ATTRIB_PACKED_POST inverter_device_data_t;

typedef __ATTRIB_PACKED_PRE struct inverter_flash_eeprom {
    __ATTRIB_PACKED_PRE union {
        // Whole EEPROM as a byte array
        u_int8_t raw[BLOCK_64K];
        // EEPROM map breakdown
        __ATTRIB_PACKED_PRE struct {
            board_data_4k_t                            board_data;              //  4K - Unsigned
            inverter_device_data_t                     device_data;             // 32K - Signed
            hidden_data_t                              hidden_data;             //  4K - Signed (Random data with RSA public key and flash UID hidden in it).
            inverter_flash_eeprom_security_data_t      security_data;           //  8K - Signed
            reserved16k_t                              reserved2;               // 16K - Unsigned
        } __ATTRIB_PACKED_POST;
    } __ATTRIB_PACKED_POST;
} __ATTRIB_PACKED_POST inverter_flash_eeprom_t;

// CAMERA ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define CAMERA_FLASH_SECURITY_DATA_FIELDS \
                                                                /* [Revision 1+] */ \
    u_int32_t  eth_mac_rev_id;                                  /*     4 bytes - BE - Internal Ethernet MAC silicon revision */ \
    u_int32_t  ahb_rev_id;                                      /*     4 bytes - BE - Internal AHB bus controller silicon revision */ \
    u_int32_t  gpio_summary_id;                                 /*     4 bytes - BE - Internal GPIO controller silicon revision */ \
    u_int32_t  i2c_controller_rev_id;                           /*     4 bytes - BE - Internal I2C controller silicon revision */ \
    u_int32_t  int_controller_summary_id;                       /*     4 bytes - BE - Internal interrupt controller silicon revision */ \
    u_int32_t  sd_card_reader_rev_id;                           /*     4 bytes - BE - Internal SD card reader silicon revision */ \
    u_int32_t  timer_summary_id;                                /*     4 bytes - BE - Internal timer controller silicon revision */ \
                                                                /* [Revision 2+] */ \
    u_int8_t   revision_war_magic[DATA_REV_WAR_MAGIC_SIZE];     /*     3 bytes - NA - magic value used to indicate data format revision workaround */ \
    u_int8_t   alt_revision;                                    /*     1 bytes - NA - data format revision (supercedes revision in common location due to workaround) */ \
    u_int32_t  pcba;                                            /*     4 bytes - BE - PCBA (Format - high 24-bits BE PCBA part number, low 8 bits PCBA revision) */ \
    u_int8_t   qr_code[QR_CODE_SIZE];                           /*     6 bytes - NA - Adoption QR code */ \
                                                                /* [Revision 3+] */ \
    u_int16_t  fcd_id;                                          /*     2 bytes - BE - encoded FCD ID (see docs) */ \
    u_int32_t  fcd_version;                                     /*     4 bytes - BE - encoded FCD version */ \
    u_int16_t  sw_id;                                           /*     2 bytes - BE - encoded SW ID (see docs) */ \
    u_int32_t  sw_version;                                      /*     4 bytes - BE - encoded initial firmware version */

DECLARE_FLASH_SECURITY_DATA_STRUCTURES(camera,CAMERA_FLASH_SECURITY_DATA_FIELDS,SEC_BLOCK_SIZE_64KB_EEPROM)

#define FLASH_SECURITY_OFFSET_CAMERA_ETH_MAC_REV_ID             __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera,eth_mac_rev_id)
#define FLASH_SECURITY_OFFSET_CAMERA_AHB_REV_ID                 __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera,ahb_rev_id)
#define FLASH_SECURITY_OFFSET_CAMERA_GPIO_SUMMARY_ID            __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera,gpio_summary_id)
#define FLASH_SECURITY_OFFSET_CAMERA_I2C_CONTROLLER_REV_ID      __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera,i2c_controller_rev_id)
#define FLASH_SECURITY_OFFSET_CAMERA_INT_CONTROLLER_SUMMARY_ID  __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera,int_controller_summary_id)
#define FLASH_SECURITY_OFFSET_CAMERA_SD_CARD_READER_REV_ID      __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera,sd_card_reader_rev_id)
#define FLASH_SECURITY_OFFSET_CAMERA_TIMER_SUMMARY_ID           __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera,timer_summary_id)
#define FLASH_SECURITY_OFFSET_CAMERA_REVISION_WAR_MAGIC         __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera,revision_war_magic)
#define FLASH_SECURITY_OFFSET_CAMERA_ALT_REVISION               __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera,alt_revision)
#define FLASH_SECURITY_OFFSET_CAMERA_PCBA                       __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera,pcba)
#define FLASH_SECURITY_OFFSET_CAMERA_QR_CODE                    __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera,qr_code)
#define FLASH_SECURITY_OFFSET_CAMERA_FCD_ID                     __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera,fcd_id)
#define FLASH_SECURITY_OFFSET_CAMERA_FCD_VERSION                __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera,fcd_version)
#define FLASH_SECURITY_OFFSET_CAMERA_SW_ID                      __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera,sw_id)
#define FLASH_SECURITY_OFFSET_CAMERA_SW_VERSION                 __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera,sw_version)
#define FLASH_SECURITY_OFFSET_CAMERA_RESERVED                   __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera,reserved)

typedef __ATTRIB_PACKED_PRE struct camera_flash_eeprom {
    __ATTRIB_PACKED_PRE union {
        // Whole EEPROM as a byte array
        u_int8_t raw[BLOCK_64K];
        // EEPROM map breakdown
        __ATTRIB_PACKED_PRE struct {
            board_data_4k_t                            board_data;              //  4K - Unsigned
            reserved32k_t                              device_data;             // 32K - Signed
            hidden_data_t                              hidden_data;             //  4K - Signed (Random data with RSA public key and flash UID hidden in it).
            camera_flash_eeprom_security_data_t        security_data;           //  8K - Signed
            reserved16k_t                              reserved2;               // 16K - Unsigned
        } __ATTRIB_PACKED_POST;
    } __ATTRIB_PACKED_POST;
} __ATTRIB_PACKED_POST camera_flash_eeprom_t;

// CAMERA2 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define CAMERA2_FLASH_SECURITY_DATA_FIELDS \
                                                                /* [Revision 1+] */ \
    u_int32_t  ssi_ident_id;                                    /*     4 bytes - BE - SSI identification ID */ \
    u_int32_t  ssi_version_id;                                  /*     4 bytes - BE - SSI silicon revision ID */ \
                                                                /* [Revision 2+] */ \
    u_int8_t   revision_war_magic[DATA_REV_WAR_MAGIC_SIZE];     /*     3 bytes - NA - magic value used to indicate data format revision workaround */ \
    u_int8_t   alt_revision;                                    /*     1 bytes - NA - data format revision (supercedes revision in common location due to workaround) */ \
    u_int32_t  pcba;                                            /*     4 bytes - BE - PCBA (Format - high 24-bits BE PCBA part number, low 8 bits PCBA revision) */ \
    u_int8_t   qr_code[QR_CODE_SIZE];                           /*     6 bytes - NA - Adoption QR code */ \
                                                                /* [Revision 3+] */ \
    u_int16_t  fcd_id;                                          /*     2 bytes - BE - encoded FCD ID (see docs) */ \
    u_int32_t  fcd_version;                                     /*     4 bytes - BE - encoded FCD version */ \
    u_int16_t  sw_id;                                           /*     2 bytes - BE - encoded SW ID (see docs) */ \
    u_int32_t  sw_version;                                      /*     4 bytes - BE - encoded initial firmware version */

DECLARE_FLASH_SECURITY_DATA_STRUCTURES(camera2,CAMERA2_FLASH_SECURITY_DATA_FIELDS,SEC_BLOCK_SIZE_64KB_EEPROM)

#define FLASH_SECURITY_OFFSET_CAMERA2_SSI_IDENT_ID              __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera2,ssi_ident_id)
#define FLASH_SECURITY_OFFSET_CAMERA2_SSI_VERSION_ID            __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera2,ssi_version_id)
#define FLASH_SECURITY_OFFSET_CAMERA2_REVISION_WAR_MAGIC        __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera2,revision_war_magic)
#define FLASH_SECURITY_OFFSET_CAMERA2_ALT_REVISION              __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera2,alt_revision)
#define FLASH_SECURITY_OFFSET_CAMERA2_PCBA                      __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera2,pcba)
#define FLASH_SECURITY_OFFSET_CAMERA2_QR_CODE                   __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera2,qr_code)
#define FLASH_SECURITY_OFFSET_CAMERA2_FCD_ID                    __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera2,fcd_id)
#define FLASH_SECURITY_OFFSET_CAMERA2_FCD_VERSION               __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera2,fcd_version)
#define FLASH_SECURITY_OFFSET_CAMERA2_FCD_ID                    __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera2,fcd_id)
#define FLASH_SECURITY_OFFSET_CAMERA2_SW_VERSION                __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera2,sw_version)
#define FLASH_SECURITY_OFFSET_CAMERA2_RESERVED                  __FLASH_CLASS_SPECIFIC_SEC_OFFSET(camera2,reserved)

typedef __ATTRIB_PACKED_PRE struct camera2_calibration_data {
    __ATTRIB_PACKED_PRE union {
        u_int8_t raw[BLOCK_4K];
        __ATTRIB_PACKED_PRE struct {
            u_int8_t calibration_data[0x10];
            u_int8_t reserved[BLOCK_4K - 0x10];
        } __ATTRIB_PACKED_POST;
    } __ATTRIB_PACKED_POST;
}  __ATTRIB_PACKED_POST camera2_calibration_data_t;

typedef __ATTRIB_PACKED_PRE struct camera2_flash_eeprom {
    __ATTRIB_PACKED_PRE union {
        // Whole EEPROM as a byte array
        u_int8_t raw[BLOCK_64K];
        // EEPROM map breakdown
        __ATTRIB_PACKED_PRE struct {
            board_data_4k_t                            board_data;               //  4K - Unsigned
            camera2_calibration_data_t                 device_data;              //  4K - Signed
            reserved28k_t                              reserved1;                // 28K - Signed
            hidden_data_t                              hidden_data;              //  4K - Signed (Random data with RSA public key and flash UID hidden in it).
            camera2_flash_eeprom_security_data_t       security_data;            //  8K - Signed
            reserved16k_t                              reserved2;                // 16K - Unsigned
        } __ATTRIB_PACKED_POST;
    } __ATTRIB_PACKED_POST;
} __ATTRIB_PACKED_POST camera2_flash_eeprom_t;

// ROUTER ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define ROUTER_FLASH_SECURITY_DATA_FIELDS \
                                                                /* [Revision 1+] */ \
    u_int32_t  cpu_rev_id;                                      /*     4 bytes - BE - cpu rev ID */ \
                                                                /* [Revision 2+] */ \
    u_int8_t   revision_war_magic[DATA_REV_WAR_MAGIC_SIZE];     /*     3 bytes - NA - magic value used to indicate data format revision workaround */ \
    u_int8_t   alt_revision;                                    /*     1 bytes - NA - data format revision (supercedes revision in common location due to workaround) */ \
    u_int32_t  pcba;                                            /*     4 bytes - BE - PCBA (Format - high 24-bits BE PCBA part number, low 8 bits PCBA revision) */ \
    u_int8_t   qr_code[QR_CODE_SIZE];                           /*     6 bytes - NA - Adoption QR code */ \
    u_int8_t   vpd[ROUTER_VPD_SIZE];                            /*   128 bytes - NA - Router "Vital Product Data" (binary blob). Applies to MediaTek (ssid 0xee41 and 0xee42) */ \
                                                                /* [Revision 3+] */ \
    u_int16_t  fcd_id;                                          /*     2 bytes - BE - encoded FCD ID (see docs) */ \
    u_int32_t  fcd_version;                                     /*     4 bytes - BE - encoded FCD version */ \
    u_int16_t  sw_id;                                           /*     2 bytes - BE - encoded SW ID (see docs) */ \
    u_int32_t  sw_version;                                      /*     4 bytes - BE - encoded initial firmware version */

// router_flash_eeprom_security_data_t
DECLARE_FLASH_SECURITY_DATA_STRUCTURES(router,ROUTER_FLASH_SECURITY_DATA_FIELDS,SEC_BLOCK_SIZE_64KB_EEPROM)

#define FLASH_SECURITY_OFFSET_ROUTER_CPU_REV_ID                 __FLASH_CLASS_SPECIFIC_SEC_OFFSET(router,cpu_rev_id)
#define FLASH_SECURITY_OFFSET_ROUTER_REVISION_WAR_MAGIC         __FLASH_CLASS_SPECIFIC_SEC_OFFSET(router,revision_war_magic)
#define FLASH_SECURITY_OFFSET_ROUTER_ALT_REVISION               __FLASH_CLASS_SPECIFIC_SEC_OFFSET(router,alt_revision)
#define FLASH_SECURITY_OFFSET_ROUTER_PCBA                       __FLASH_CLASS_SPECIFIC_SEC_OFFSET(router,pcba)
#define FLASH_SECURITY_OFFSET_ROUTER_QR_CODE                    __FLASH_CLASS_SPECIFIC_SEC_OFFSET(router,qr_code)
#define FLASH_SECURITY_OFFSET_ROUTER_VPD                        __FLASH_CLASS_SPECIFIC_SEC_OFFSET(router,vpd)
#define FLASH_SECURITY_OFFSET_ROUTER_FCD_ID                     __FLASH_CLASS_SPECIFIC_SEC_OFFSET(router,fcd_id)
#define FLASH_SECURITY_OFFSET_ROUTER_FCD_VERSION                __FLASH_CLASS_SPECIFIC_SEC_OFFSET(router,fcd_version)
#define FLASH_SECURITY_OFFSET_ROUTER_SW_ID                      __FLASH_CLASS_SPECIFIC_SEC_OFFSET(router,sw_id)
#define FLASH_SECURITY_OFFSET_ROUTER_SW_VERSION                 __FLASH_CLASS_SPECIFIC_SEC_OFFSET(router,sw_version)
#define FLASH_SECURITY_OFFSET_ROUTER_RESERVED                   __FLASH_CLASS_SPECIFIC_SEC_OFFSET(router,reserved)

typedef __ATTRIB_PACKED_PRE struct router_flash_eeprom {
    __ATTRIB_PACKED_PRE union {
        // Whole EEPROM as a byte array
        u_int8_t raw[BLOCK_64K];
        // EEPROM map breakdown
        __ATTRIB_PACKED_PRE struct {
            board_data_4k_t                            board_data;              //  4K - Unsigned
            reserved4k_t                               device_data;             //  4K - Signed - stuff specific to router product that must be secured
            reserved28k_t                              reserved1;               // 28K - Signed
            hidden_data_t                              hidden_data;             //  4K - Signed (Random data with RSA public key and flash UID hidden in it).
            router_flash_eeprom_security_data_t        security_data;           //  8K - Signed
            reserved16k_t                              reserved2;               // 16K - Unsigned
        } __ATTRIB_PACKED_POST;
    } __ATTRIB_PACKED_POST;
} __ATTRIB_PACKED_POST router_flash_eeprom_t;

// SOLARGATEWAY ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define SOLARGATEWAY_FLASH_SECURITY_DATA_FIELDS \
                                                                /* [Revision 1+] */ \
    u_int32_t  cpu_rev_id;                                      /*     4 bytes - BE - cpu rev ID */ \
                                                                /* [Revision 2+] */ \
    u_int32_t  pcba;                                            /*     4 bytes - BE - PCBA (Format - high 24-bits BE PCBA part number, low 8 bits PCBA revision) */ \
    u_int8_t   qr_code[QR_CODE_SIZE];                           /*     6 bytes - NA - Adoption QR code */ \
                                                                /* [Revision 3+] */ \
    u_int16_t  fcd_id;                                          /*     2 bytes - BE - encoded FCD ID (see docs) */ \
    u_int32_t  fcd_version;                                     /*     4 bytes - BE - encoded FCD version */ \
    u_int16_t  sw_id;                                           /*     2 bytes - BE - encoded SW ID (see docs) */ \
    u_int32_t  sw_version;                                      /*     4 bytes - BE - encoded initial firmware version */

// solargateway_flash_eeprom_security_data_t
DECLARE_FLASH_SECURITY_DATA_STRUCTURES(solargateway,SOLARGATEWAY_FLASH_SECURITY_DATA_FIELDS,SEC_BLOCK_SIZE_64KB_EEPROM)

#define FLASH_SECURITY_OFFSET_SOLARGATEWAY_CPU_REV_ID                 __FLASH_CLASS_SPECIFIC_SEC_OFFSET(solargateway,cpu_rev_id)
#define FLASH_SECURITY_OFFSET_SOLARGATEWAY_PCBA                       __FLASH_CLASS_SPECIFIC_SEC_OFFSET(solargateway,pcba)
#define FLASH_SECURITY_OFFSET_SOLARGATEWAY_QR_CODE                    __FLASH_CLASS_SPECIFIC_SEC_OFFSET(solargateway,qr_code)
#define FLASH_SECURITY_OFFSET_SOLARGATEWAY_FCD_ID                     __FLASH_CLASS_SPECIFIC_SEC_OFFSET(solargateway,fcd_id)
#define FLASH_SECURITY_OFFSET_SOLARGATEWAY_FCD_VERSION                __FLASH_CLASS_SPECIFIC_SEC_OFFSET(solargateway,fcd_version)
#define FLASH_SECURITY_OFFSET_SOLARGATEWAY_SW_ID                      __FLASH_CLASS_SPECIFIC_SEC_OFFSET(solargateway,sw_id)
#define FLASH_SECURITY_OFFSET_SOLARGATEWAY_SW_VERSION                 __FLASH_CLASS_SPECIFIC_SEC_OFFSET(solargateway,sw_version)
#define FLASH_SECURITY_OFFSET_SOLARGATEWAY_RESERVED                   __FLASH_CLASS_SPECIFIC_SEC_OFFSET(solargateway,reserved)

typedef __ATTRIB_PACKED_PRE struct solargateway_flash_eeprom {
    __ATTRIB_PACKED_PRE union {
        // Whole EEPROM as a byte array
        u_int8_t raw[BLOCK_64K];
        // EEPROM map breakdown
        __ATTRIB_PACKED_PRE struct {
            board_data_4k_t                            board_data;              //  4K - Unsigned
            reserved4k_t                               solargateway_board_data; //  4K - Signed - stuff specific to solargateway product that must be secured
            reserved28k_t                              device_data;             // 28K - Signed
            hidden_data_t                              hidden_data;             //  4K - Signed (Random data with RSA public key and flash UID hidden in it).
            solargateway_flash_eeprom_security_data_t  security_data;           //  8K - Signed
            reserved16k_t                              reserved2;               // 16K - Unsigned
        } __ATTRIB_PACKED_POST;
    } __ATTRIB_PACKED_POST;
} __ATTRIB_PACKED_POST solargateway_flash_eeprom_t;

// NVR ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define NVR_FLASH_SECURITY_DATA_FIELDS \
                                                                /* [Revision 1+] */ \
    u_int32_t  pcba;                                            /*     4 bytes - BE - PCBA (Format - high 24-bits BE PCBA part number, low 8 bits PCBA revision) */ \
                                                                /* [Revision 2+] */ \
    u_int8_t   revision_war_magic[DATA_REV_WAR_MAGIC_SIZE];     /*     3 bytes - NA - magic value used to indicate data format revision workaround */ \
    u_int8_t   alt_revision;                                    /*     1 bytes - NA - data format revision (supercedes revision in common location due to workaround) */ \
    u_int8_t   qr_code[QR_CODE_SIZE];                           /*     6 bytes - NA - Adoption QR code */ \
                                                                /* [Revision 3+] */ \
    u_int16_t  fcd_id;                                          /*     2 bytes - BE - encoded FCD ID (see docs) */ \
    u_int32_t  fcd_version;                                     /*     4 bytes - BE - encoded FCD version */ \
    u_int16_t  sw_id;                                           /*     2 bytes - BE - encoded SW ID (see docs) */ \
    u_int32_t  sw_version;                                      /*     4 bytes - BE - encoded initial firmware version */

DECLARE_FLASH_SECURITY_DATA_STRUCTURES(nvr,NVR_FLASH_SECURITY_DATA_FIELDS,SEC_BLOCK_SIZE_64KB_EEPROM)

#define FLASH_SECURITY_OFFSET_NVR_PCBA                          __FLASH_CLASS_SPECIFIC_SEC_OFFSET(nvr,pcba)
#define FLASH_SECURITY_OFFSET_NVR_REVISION_WAR_MAGIC            __FLASH_CLASS_SPECIFIC_SEC_OFFSET(nvr,revision_war_magic)
#define FLASH_SECURITY_OFFSET_NVR_ALT_REVISION                  __FLASH_CLASS_SPECIFIC_SEC_OFFSET(nvr,alt_revision)
#define FLASH_SECURITY_OFFSET_NVR_QR_CODE                       __FLASH_CLASS_SPECIFIC_SEC_OFFSET(nvr,qr_code)
#define FLASH_SECURITY_OFFSET_NVR_FCD_ID                        __FLASH_CLASS_SPECIFIC_SEC_OFFSET(nvr,fcd_id)
#define FLASH_SECURITY_OFFSET_NVR_FCD_VERSION                   __FLASH_CLASS_SPECIFIC_SEC_OFFSET(nvr,fcd_version)
#define FLASH_SECURITY_OFFSET_NVR_SW_ID                         __FLASH_CLASS_SPECIFIC_SEC_OFFSET(nvr,sw_id)
#define FLASH_SECURITY_OFFSET_NVR_SW_VERSION                    __FLASH_CLASS_SPECIFIC_SEC_OFFSET(nvr,sw_version)
#define FLASH_SECURITY_OFFSET_NVR_RESERVED                      __FLASH_CLASS_SPECIFIC_SEC_OFFSET(nvr,reserved)

typedef __ATTRIB_PACKED_PRE struct nvr_binary_blob {
        u_int8_t binary_blob[BLOCK_32K];
} __ATTRIB_PACKED_POST nvr_binary_blob_t;

typedef __ATTRIB_PACKED_PRE struct nvr_flash_eeprom {
    __ATTRIB_PACKED_PRE union {
        // Whole EEPROM as a byte array
        u_int8_t raw[BLOCK_64K];
        // EEPROM map breakdown
        __ATTRIB_PACKED_PRE struct {
            board_data_4k_t                            board_data;              //  4K - Unsigned
            nvr_binary_blob_t                          device_data;             // 32K - Signed
            hidden_data_t                              hidden_data;             //  4K - Signed (Random data with RSA public key and flash UID hidden in it).
            nvr_flash_eeprom_security_data_t           security_data;           //  8K - Signed
            reserved16k_t                              reserved2;               // 16K - Unsigned
        } __ATTRIB_PACKED_POST;
    } __ATTRIB_PACKED_POST;
} __ATTRIB_PACKED_POST nvr_flash_eeprom_t;

// QCASWITCH ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define QCASWITCH_FLASH_SECURITY_DATA_FIELDS \
                                                                /* [Revision 1+] */ \
    u_int32_t  pcba;                                            /*     4 bytes - BE - PCBA (Format - high 24-bits BE PCBA part number, low 8 bits PCBA revision) */ \
                                                                /* [Revision 2+] */ \
    u_int8_t   revision_war_magic[DATA_REV_WAR_MAGIC_SIZE];     /*     3 bytes - NA - magic value used to indicate data format revision workaround */ \
    u_int8_t   alt_revision;                                    /*     1 bytes - NA - data format revision (supercedes revision in common location due to workaround) */ \
    u_int8_t   qr_code[QR_CODE_SIZE];                           /*     6 bytes - NA - Adoption QR code */ \
                                                                /* [Revision 3+] */ \
    u_int16_t  fcd_id;                                          /*     2 bytes - BE - encoded FCD ID (see docs) */ \
    u_int32_t  fcd_version;                                     /*     4 bytes - BE - encoded FCD version */ \
    u_int16_t  sw_id;                                           /*     2 bytes - BE - encoded SW ID (see docs) */ \
    u_int32_t  sw_version;                                      /*     4 bytes - BE - encoded initial firmware version */

DECLARE_FLASH_SECURITY_DATA_STRUCTURES(qcaswitch,QCASWITCH_FLASH_SECURITY_DATA_FIELDS,SEC_BLOCK_SIZE_64KB_EEPROM)

#define FLASH_SECURITY_OFFSET_QCASWITCH_PCBA                    __FLASH_CLASS_SPECIFIC_SEC_OFFSET(qcaswitch,pcba)
#define FLASH_SECURITY_OFFSET_QCASWITCH_REVISION_WAR_MAGIC      __FLASH_CLASS_SPECIFIC_SEC_OFFSET(qcaswitch,revision_war_magic)
#define FLASH_SECURITY_OFFSET_QCASWITCH_ALT_REVISION            __FLASH_CLASS_SPECIFIC_SEC_OFFSET(qcaswitch,alt_revision)
#define FLASH_SECURITY_OFFSET_QCASWITCH_QR_CODE                 __FLASH_CLASS_SPECIFIC_SEC_OFFSET(qcaswitch,qr_code)
#define FLASH_SECURITY_OFFSET_QCASWITCH_FCD_ID                  __FLASH_CLASS_SPECIFIC_SEC_OFFSET(qcaswitch,fcd_id)
#define FLASH_SECURITY_OFFSET_QCASWITCH_FCD_VERSION             __FLASH_CLASS_SPECIFIC_SEC_OFFSET(qcaswitch,fcd_version)
#define FLASH_SECURITY_OFFSET_QCASWITCH_SW_ID                   __FLASH_CLASS_SPECIFIC_SEC_OFFSET(qcaswitch,sw_id)
#define FLASH_SECURITY_OFFSET_QCASWITCH_SW_VERSION              __FLASH_CLASS_SPECIFIC_SEC_OFFSET(qcaswitch,sw_version)
#define FLASH_SECURITY_OFFSET_QCASWITCH_RESERVED                __FLASH_CLASS_SPECIFIC_SEC_OFFSET(qcaswitch,reserved)

typedef __ATTRIB_PACKED_PRE struct qcaswitch_flash_eeprom {
    __ATTRIB_PACKED_PRE union {
        // Whole EEPROM as a byte array
        u_int8_t raw[BLOCK_64K];
        // EEPROM map breakdown
        __ATTRIB_PACKED_PRE struct {
            board_data_4k_t                            board_data;              //  4K - Unsigned
            reserved32k_t                              device_data;             // 32K - Signed
            hidden_data_t                              hidden_data;             //  4K - Signed (Random data with RSA public key and flash UID hidden in it).
            qcaswitch_flash_eeprom_security_data_t     security_data;           //  8K - Signed
            reserved16k_t                              reserved2;               // 16K - Unsigned
        } __ATTRIB_PACKED_POST;
    } __ATTRIB_PACKED_POST;
} __ATTRIB_PACKED_POST qcaswitch_flash_eeprom_t;

// BCMSWITCH ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define BCMSWITCH_FLASH_SECURITY_DATA_FIELDS \
                                                                /* [Revision 1+] */ \
    u_int32_t  cpu_rev_id;                                      /*     4 bytes - BE - cpu rev ID */ \
    u_int8_t   vpd[BCMSWITCH_VPD_SIZE];                         /*   256 bytes - NA - Broadcom "Vital Product Data" (binary blob) */ \
    u_int32_t  pcba;                                            /*     4 bytes - BE - PCBA (Format - high 24-bits BE PCBA part number, low 8 bits PCBA revision) */ \
    u_int8_t   qr_code[QR_CODE_SIZE];                           /*     6 bytes - NA - Adoption QR code */ \
                                                                /* [Revision 3+] */ \
    u_int16_t  fcd_id;                                          /*     2 bytes - BE - encoded FCD ID (see docs) */ \
    u_int32_t  fcd_version;                                     /*     4 bytes - BE - encoded FCD version */ \
    u_int16_t  sw_id;                                           /*     2 bytes - BE - encoded SW ID (see docs) */ \
    u_int32_t  sw_version;                                      /*     4 bytes - BE - encoded initial firmware version */

DECLARE_FLASH_SECURITY_DATA_STRUCTURES(bcmswitch,BCMSWITCH_FLASH_SECURITY_DATA_FIELDS,SEC_BLOCK_SIZE_64KB_EEPROM)

#define FLASH_SECURITY_OFFSET_BCMSWITCH_CPU_REV_ID              __FLASH_CLASS_SPECIFIC_SEC_OFFSET(bcmswitch,cpu_rev_id)
#define FLASH_SECURITY_OFFSET_BCMSWITCH_VPD                     __FLASH_CLASS_SPECIFIC_SEC_OFFSET(bcmswitch,vpd)
#define FLASH_SECURITY_OFFSET_BCMSWITCH_PCBA                    __FLASH_CLASS_SPECIFIC_SEC_OFFSET(bcmswitch,pcba)
#define FLASH_SECURITY_OFFSET_BCMSWITCH_QR_CODE                 __FLASH_CLASS_SPECIFIC_SEC_OFFSET(bcmswitch,qr_code)
#define FLASH_SECURITY_OFFSET_BCMSWITCH_FCD_ID                  __FLASH_CLASS_SPECIFIC_SEC_OFFSET(bcmswitch,fcd_id)
#define FLASH_SECURITY_OFFSET_BCMSWITCH_FCD_VERSION             __FLASH_CLASS_SPECIFIC_SEC_OFFSET(bcmswitch,fcd_version)
#define FLASH_SECURITY_OFFSET_BCMSWITCH_SW_ID                   __FLASH_CLASS_SPECIFIC_SEC_OFFSET(bcmswitch,sw_id)
#define FLASH_SECURITY_OFFSET_BCMSWITCH_SW_VERSION              __FLASH_CLASS_SPECIFIC_SEC_OFFSET(bcmswitch,sw_version)
#define FLASH_SECURITY_OFFSET_BCMSWITCH_RESERVED                __FLASH_CLASS_SPECIFIC_SEC_OFFSET(bcmswitch,reserved)

typedef __ATTRIB_PACKED_PRE struct bcmswitch_flash_eeprom {
    __ATTRIB_PACKED_PRE union {
        // Whole EEPROM as a byte array
        u_int8_t raw[BLOCK_64K];
        // EEPROM map breakdown
        __ATTRIB_PACKED_PRE struct {
            board_data_4k_t                            board_data;              //  4K - Unsigned
            reserved32k_t                              device_data;             // 32K - Signed
            hidden_data_t                              hidden_data;             //  4K - Signed (Random data with RSA public key and flash UID hidden in it).
            bcmswitch_flash_eeprom_security_data_t     security_data;           //  8K - Signed
            reserved16k_t                              reserved2;               // 16K - Unsigned
        }  __ATTRIB_PACKED_POST;
    } __ATTRIB_PACKED_POST;
} __ATTRIB_PACKED_POST bcmswitch_flash_eeprom_t;

// CLOUDKEY ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define CLOUDKEY_FLASH_SECURITY_DATA_FIELDS \
                                                                /* [Revision 1+] */ \
    u_int32_t  cpu_rev_id;                                      /*     4 bytes - BE - cpu rev ID */ \
    u_int32_t  pcba;                                            /*     4 bytes - BE - PCBA (Format - high 24-bits BE PCBA part number, low 8 bits PCBA revision) */ \
    u_int8_t   qr_code[QR_CODE_SIZE];                           /*     6 bytes - NA - Adoption QR code */ \
                                                                /* [Revision 3+] */ \
    u_int16_t  fcd_id;                                          /*     2 bytes - BE - encoded FCD ID (see docs) */ \
    u_int32_t  fcd_version;                                     /*     4 bytes - BE - encoded FCD version */ \
    u_int16_t  sw_id;                                           /*     2 bytes - BE - encoded SW ID (see docs) */ \
    u_int32_t  sw_version;                                      /*     4 bytes - BE - encoded initial firmware version */

DECLARE_FLASH_SECURITY_DATA_STRUCTURES(cloudkey,CLOUDKEY_FLASH_SECURITY_DATA_FIELDS,SEC_BLOCK_SIZE_64KB_EEPROM)

#define FLASH_SECURITY_OFFSET_CLOUDKEY_CPU_REV_ID              __FLASH_CLASS_SPECIFIC_SEC_OFFSET(cloudkey,cpu_rev_id)
#define FLASH_SECURITY_OFFSET_CLOUDKEY_PCBA                    __FLASH_CLASS_SPECIFIC_SEC_OFFSET(cloudkey,pcba)
#define FLASH_SECURITY_OFFSET_CLOUDKEY_QR_CODE                 __FLASH_CLASS_SPECIFIC_SEC_OFFSET(cloudkey,qr_code)
#define FLASH_SECURITY_OFFSET_CLOUDKEY_FCD_ID                  __FLASH_CLASS_SPECIFIC_SEC_OFFSET(cloudkey,fcd_id)
#define FLASH_SECURITY_OFFSET_CLOUDKEY_FCD_VERSION             __FLASH_CLASS_SPECIFIC_SEC_OFFSET(cloudkey,fcd_version)
#define FLASH_SECURITY_OFFSET_CLOUDKEY_SW_ID                   __FLASH_CLASS_SPECIFIC_SEC_OFFSET(cloudkey,sw_id)
#define FLASH_SECURITY_OFFSET_CLOUDKEY_SW_VERSION              __FLASH_CLASS_SPECIFIC_SEC_OFFSET(cloudkey,sw_version)
#define FLASH_SECURITY_OFFSET_CLOUDKEY_RESERVED                __FLASH_CLASS_SPECIFIC_SEC_OFFSET(cloudkey,reserved)

typedef struct cloudkey_flash_eeprom {
    union {
        // Whole EEPROM as a byte array
        u_int8_t raw[BLOCK_64K];
        // EEPROM map breakdown
        struct {
            board_data_4k_t                            board_data;              //  4K - Unsigned
            reserved32k_t                              device_data;             // 32K - Signed
            hidden_data_t                              hidden_data;             //  4K - Signed (Random data with RSA public key and flash UID hidden in it).
            cloudkey_flash_eeprom_security_data_t      security_data;           //  8K - Signed
            reserved16k_t                              reserved2;               // 16K - Unsigned
        }  __ATTRIB_PACKED_POST;
    } __ATTRIB_PACKED_POST;
} __ATTRIB_PACKED_POST cloudkey_flash_eeprom_t;

// BCMWIFI --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define BCMWIFI_FLASH_SECURITY_DATA_FIELDS \
                                                                /* [Revision 1+] */ \
    u_int32_t  cpu_rev_id;                                      /*     4 bytes - BE - cpu rev ID */ \
    u_int32_t  radio1_rev_id;                                   /*     4 bytes - BE - radio 1 silicon revision */ \
    u_int32_t  radio2_rev_id;                                   /*     4 bytes - BE - radio 2 silicon revision */ \
    u_int8_t   radio1_mac_address[MAC_ADDRESS_SIZE];                           /*     6 bytes - NA - radio 1 MAC address */ \
    u_int8_t   radio2_mac_address[MAC_ADDRESS_SIZE];                           /*     6 bytes - NA - radio 1 MAC address */ \
    u_int32_t  pcba;                                            /*     4 bytes - BE - PCBA (Format - high 24-bits BE PCBA part number, low 8 bits PCBA revision) */ \
                                                                /* [Revision 2+] */ \
    u_int8_t   revision_war_magic[DATA_REV_WAR_MAGIC_SIZE];     /*     3 bytes - NA - magic value used to indicate data format revision workaround */ \
    u_int8_t   alt_revision;                                    /*     1 bytes - NA - data format revision (supercedes revision in common location due to workaround) */ \
    u_int8_t   qr_code[QR_CODE_SIZE];                           /*     6 bytes - NA - Adoption QR code */ \
                                                                /* [Revision 3+] */ \
    u_int16_t  fcd_id;                                          /*     2 bytes - BE - encoded FCD ID (see docs) */ \
    u_int32_t  fcd_version;                                     /*     4 bytes - BE - encoded FCD version */ \
    u_int16_t  sw_id;                                           /*     2 bytes - BE - encoded SW ID (see docs) */ \
    u_int32_t  sw_version;                                      /*     4 bytes - BE - encoded initial firmware version */

DECLARE_FLASH_SECURITY_DATA_STRUCTURES(bcmwifi,BCMWIFI_FLASH_SECURITY_DATA_FIELDS,SEC_BLOCK_SIZE_64KB_EEPROM)

#define FLASH_SECURITY_OFFSET_BCMWIFI_CPU_REV_ID                __FLASH_CLASS_SPECIFIC_SEC_OFFSET(bcmwifi,cpu_rev_id)
#define FLASH_SECURITY_OFFSET_BCMWIFI_RADIO1_REV_ID             __FLASH_CLASS_SPECIFIC_SEC_OFFSET(bcmwifi,radio1_rev_id)
#define FLASH_SECURITY_OFFSET_BCMWIFI_RADIO2_REV_ID             __FLASH_CLASS_SPECIFIC_SEC_OFFSET(bcmwifi,radio2_rev_id)
#define FLASH_SECURITY_OFFSET_BCMWIFI_RADIO1_MAC_ADDRESS        __FLASH_CLASS_SPECIFIC_SEC_OFFSET(bcmwifi,radio1_mac_address)
#define FLASH_SECURITY_OFFSET_BCMWIFI_RADIO2_MAC_ADDRESS        __FLASH_CLASS_SPECIFIC_SEC_OFFSET(bcmwifi,radio2_mac_address)
#define FLASH_SECURITY_OFFSET_BCMWIFI_PCBA                      __FLASH_CLASS_SPECIFIC_SEC_OFFSET(bcmwifi,pcba)
#define FLASH_SECURITY_OFFSET_BCMWIFI_REVISION_WAR_MAGIC        __FLASH_CLASS_SPECIFIC_SEC_OFFSET(bcmwifi,revision_war_magic)
#define FLASH_SECURITY_OFFSET_BCMWIFI_ALT_REVISION              __FLASH_CLASS_SPECIFIC_SEC_OFFSET(bcmwifi,alt_revision)
#define FLASH_SECURITY_OFFSET_BCMWIFI_QR_CODE                   __FLASH_CLASS_SPECIFIC_SEC_OFFSET(bcmwifi,qr_code)
#define FLASH_SECURITY_OFFSET_BCMWIFI_FCD_ID                    __FLASH_CLASS_SPECIFIC_SEC_OFFSET(bcmwifi,fcd_id)
#define FLASH_SECURITY_OFFSET_BCMWIFI_FCD_VERSION               __FLASH_CLASS_SPECIFIC_SEC_OFFSET(bcmwifi,fcd_version)
#define FLASH_SECURITY_OFFSET_BCMWIFI_SW_ID                     __FLASH_CLASS_SPECIFIC_SEC_OFFSET(bcmwifi,sw_id)
#define FLASH_SECURITY_OFFSET_BCMWIFI_SW_VERSION                __FLASH_CLASS_SPECIFIC_SEC_OFFSET(bcmwifi,sw_version)
#define FLASH_SECURITY_OFFSET_BCMWIFI_RESERVED                  __FLASH_CLASS_SPECIFIC_SEC_OFFSET(bcmwifi,reserved)

typedef __ATTRIB_PACKED_PRE struct bcmwifi_flash_eeprom {
    __ATTRIB_PACKED_PRE union {
        // Whole EEPROM as a byte array
        u_int8_t raw[BLOCK_64K];
        // EEPROM map breakdown
        __ATTRIB_PACKED_PRE struct {
            board_data_4k_t                            board_data;              //  4K - Unsigned
            reserved32k_t                              device_data;             // 32K - Signed
            hidden_data_t                              hidden_data;             //  4K - Signed (Random data with RSA public key and flash UID hidden in it).
            bcmwifi_flash_eeprom_security_data_t       security_data;           //  8K - Signed
            reserved16k_t                              reserved2;               // 16K - Unsigned
        } __ATTRIB_PACKED_POST;
    } __ATTRIB_PACKED_POST;
} __ATTRIB_PACKED_POST bcmwifi_flash_eeprom_t;

// AIRFIBER -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define AIRFIBER_FLASH_SECURITY_DATA_FIELDS \
                                                                /* [Revision 1+] */ \
    u_int32_t  cpu_rev_id;                                      /*     4 bytes - BE - cpu rev ID */ \
    u_int16_t  old_board_rev_id;                                /*     2 bytes - BE - old 16-bit PCBA revision only */ \
                                                                /* [Revision 2+] */ \
    u_int8_t   revision_war_magic[DATA_REV_WAR_MAGIC_SIZE];     /*     3 bytes - NA - magic value used to indicate data format revision workaround */ \
    u_int8_t   alt_revision;                                    /*     1 bytes - NA - data format revision (supercedes revision in common location due to workaround) */ \
    u_int32_t  pcba;                                            /*     4 bytes - BE - PCBA (Format - high 24-bits BE PCBA part number, low 8 bits PCBA revision) */ \
    u_int8_t   qr_code[QR_CODE_SIZE];                           /*     6 bytes - NA - Adoption QR code */ \
                                                                /* [Revision 3+] */ \
    u_int16_t  fcd_id;                                          /*     2 bytes - BE - encoded FCD ID (see docs) */ \
    u_int32_t  fcd_version;                                     /*     4 bytes - BE - encoded FCD version */ \
    u_int16_t  sw_id;                                           /*     2 bytes - BE - encoded SW ID (see docs) */ \
    u_int32_t  sw_version;                                      /*     4 bytes - BE - encoded initial firmware version */

DECLARE_FLASH_SECURITY_DATA_STRUCTURES(airfiber,AIRFIBER_FLASH_SECURITY_DATA_FIELDS,SEC_BLOCK_SIZE_64KB_EEPROM)

#define FLASH_SECURITY_OFFSET_AIRFIBER_CPU_REV_ID               __FLASH_CLASS_SPECIFIC_SEC_OFFSET(airfiber,cpu_rev_id)
#define FLASH_SECURITY_OFFSET_AIRFIBER_OLD_BOARD_REV_ID         __FLASH_CLASS_SPECIFIC_SEC_OFFSET(airfiber,old_board_rev_id)
#define FLASH_SECURITY_OFFSET_AIRFIBER_REVISION_WAR_MAGIC       __FLASH_CLASS_SPECIFIC_SEC_OFFSET(airfiber,revision_war_magic)
#define FLASH_SECURITY_OFFSET_AIRFIBER_ALT_REVISION             __FLASH_CLASS_SPECIFIC_SEC_OFFSET(airfiber,alt_revision)
#define FLASH_SECURITY_OFFSET_AIRFIBER_PCBA                     __FLASH_CLASS_SPECIFIC_SEC_OFFSET(airfiber,pcba)
#define FLASH_SECURITY_OFFSET_AIRFIBER_QR_CODE                  __FLASH_CLASS_SPECIFIC_SEC_OFFSET(airfiber,qr_code)
#define FLASH_SECURITY_OFFSET_AIRFIBER_FCD_ID                   __FLASH_CLASS_SPECIFIC_SEC_OFFSET(airfiber,fcd_id)
#define FLASH_SECURITY_OFFSET_AIRFIBER_FCD_VERSION              __FLASH_CLASS_SPECIFIC_SEC_OFFSET(airfiber,fcd_version)
#define FLASH_SECURITY_OFFSET_AIRFIBER_SW_ID                    __FLASH_CLASS_SPECIFIC_SEC_OFFSET(airfiber,sw_id)
#define FLASH_SECURITY_OFFSET_AIRFIBER_SW_VERSION               __FLASH_CLASS_SPECIFIC_SEC_OFFSET(airfiber,sw_version)
#define FLASH_SECURITY_OFFSET_AIRFIBER_RESERVED                 __FLASH_CLASS_SPECIFIC_SEC_OFFSET(airfiber,reserved)

typedef __ATTRIB_PACKED_PRE struct airfiber_device_data {
    __ATTRIB_PACKED_PRE union {
        u_int8_t raw[BLOCK_32K];
        __ATTRIB_PACKED_PRE struct {
            u_int32_t magic;
            u_int32_t crc;
            u_int16_t length; // length of CRC protected area, which starts at &length and goes to last byte used in data.caldata
           __ATTRIB_PACKED_PRE struct {
                uint16_t ccode;
                uint8_t  caldata[BLOCK_16K-12];
            } __ATTRIB_PACKED_POST data;
            reserved16k_t reserved1;
        } __ATTRIB_PACKED_POST;
    } __ATTRIB_PACKED_POST;
} __ATTRIB_PACKED_POST airfiber_device_data_t;

typedef __ATTRIB_PACKED_PRE struct airfiber_flash_eeprom {
    __ATTRIB_PACKED_PRE union {
        // Whole EEPROM as a byte array
        u_int8_t raw[BLOCK_64K];
        // EEPROM map breakdown
        __ATTRIB_PACKED_PRE struct {
            board_data_4k_t                            board_data;              //  4K - Unsigned
            airfiber_device_data_t                     device_data;             // 32K - Signed
            hidden_data_t                              hidden_data;             //  4K - Signed (Random data with RSA public key and flash UID hidden in it).
            airfiber_flash_eeprom_security_data_t      security_data;           //  8K - Signed
            reserved16k_t                              reserved2;               // 16K - Unsigned
        } __ATTRIB_PACKED_POST;
    } __ATTRIB_PACKED_POST;
} __ATTRIB_PACKED_POST airfiber_flash_eeprom_t;

// UNIVOX ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define UNIVOX_FLASH_SECURITY_DATA_FIELDS \
                                                                /* [Revision 1+] */ \
    u_int32_t  cpu_rev_id;                                      /*     4 bytes - BE - cpu rev ID */ \
    u_int32_t  pcba;                                            /*     4 bytes - BE - PCBA (Format - high 24-bits BE PCBA part number, low 8 bits PCBA revision) */ \
                                                                /* [Revision 2+] */ \
    u_int8_t   revision_war_magic[DATA_REV_WAR_MAGIC_SIZE];     /*     3 bytes - NA - magic value used to indicate data format revision workaround */ \
    u_int8_t   alt_revision;                                    /*     1 bytes - NA - data format revision (supercedes revision in common location due to workaround) */ \
    u_int8_t   qr_code[QR_CODE_SIZE];                           /*     6 bytes - NA - Adoption QR code */ \
                                                                /* [Revision 3+] */ \
    u_int16_t  fcd_id;                                          /*     2 bytes - BE - encoded FCD ID (see docs) */ \
    u_int32_t  fcd_version;                                     /*     4 bytes - BE - encoded FCD version */ \
    u_int16_t  sw_id;                                           /*     2 bytes - BE - encoded SW ID (see docs) */ \
    u_int32_t  sw_version;                                      /*     4 bytes - BE - encoded initial firmware version */

DECLARE_FLASH_SECURITY_DATA_STRUCTURES(univox,UNIVOX_FLASH_SECURITY_DATA_FIELDS,SEC_BLOCK_SIZE_64KB_EEPROM)

#define FLASH_SECURITY_OFFSET_UNIVOX_CPU_REV_ID                 __FLASH_CLASS_SPECIFIC_SEC_OFFSET(univox,cpu_rev_id)
#define FLASH_SECURITY_OFFSET_UNIVOX_PCBA                       __FLASH_CLASS_SPECIFIC_SEC_OFFSET(univox,pcba)
#define FLASH_SECURITY_OFFSET_UNIVOX_REVISION_WAR_MAGIC         __FLASH_CLASS_SPECIFIC_SEC_OFFSET(univox,revision_war_magic)
#define FLASH_SECURITY_OFFSET_UNIVOX_ALT_REVISION               __FLASH_CLASS_SPECIFIC_SEC_OFFSET(univox,alt_revision)
#define FLASH_SECURITY_OFFSET_UNIVOX_QR_CODE                    __FLASH_CLASS_SPECIFIC_SEC_OFFSET(univox,qr_code)
#define FLASH_SECURITY_OFFSET_UNIVOX_FCD_ID                     __FLASH_CLASS_SPECIFIC_SEC_OFFSET(univox,fcd_id)
#define FLASH_SECURITY_OFFSET_UNIVOX_FCD_VERSION                __FLASH_CLASS_SPECIFIC_SEC_OFFSET(univox,fcd_version)
#define FLASH_SECURITY_OFFSET_UNIVOX_SW_ID                      __FLASH_CLASS_SPECIFIC_SEC_OFFSET(univox,sw_id)
#define FLASH_SECURITY_OFFSET_UNIVOX_SW_VERSION                 __FLASH_CLASS_SPECIFIC_SEC_OFFSET(univox,sw_version)
#define FLASH_SECURITY_OFFSET_UNIVOX_RESERVED                   __FLASH_CLASS_SPECIFIC_SEC_OFFSET(univox,reserved)

typedef __ATTRIB_PACKED_PRE struct univox_flash_eeprom {
    __ATTRIB_PACKED_PRE union {
        // Whole EEPROM as a byte array
        u_int8_t raw[BLOCK_64K];
        // EEPROM map breakdown
        __ATTRIB_PACKED_PRE struct {
            board_data_4k_t                            board_data;              //  4K - Unsigned
            reserved32k_t                              device_data;             // 32K - Signed (randomized)
            hidden_data_t                              hidden_data;             //  4K - Signed (Random data with RSA public key and flash UID hidden in it).
            univox_flash_eeprom_security_data_t        security_data;           //  8K - Signed
            reserved16k_t                              reserved2;               // 16K - Unsigned
        } __ATTRIB_PACKED_POST;
    } __ATTRIB_PACKED_POST;
} __ATTRIB_PACKED_POST univox_flash_eeprom_t;

// Identification helper macros

#define IS_MEDIATEK_ROUTER_SSID(__ssid__) !((((__ssid__+0x1100) + 0xbf) & 0xFFFFFFFE) ^ 0x10000)

// END ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



#endif // #ifndef __INC_SECURITY_CONFIG_INC__
