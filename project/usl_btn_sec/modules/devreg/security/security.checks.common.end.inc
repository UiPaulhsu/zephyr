
#if SECURITY_ENABLE_INI_SUPPORT
__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_bi(void) {
    if(fs_file_exists_bi()) {
        _fs_check_subsystem_id_sec_vs_system_id_bi();
        // NB: We always are at version >= 1 so all the rev 1 checks are always run
        // NB: version 2 only adds the version workaround on most of the product classes, so there are no version 2 checks for most classes
        // NB: version 3 only adds QR code on most of the product classes, and this is not validated at runtime against anything.
        switch(fs_read_security_data_format_sec()) {
        CASE_DATA_FORMAT_AIRFIBER           ( _fs_check_sec_vs_bi__class_airfiber();     )
        CASE_DATA_FORMAT_BCMWIFI            ( _fs_check_sec_vs_bi__class_bcmwifi();      )
        CASE_DATA_FORMAT_CAMERA2            ( _fs_check_sec_vs_bi__class_camera2();      )
        CASE_DATA_FORMAT_CAMERA             ( _fs_check_sec_vs_bi__class_camera();       )
        CASE_DATA_FORMAT_NVR                ( _fs_check_sec_vs_bi__class_nvr();          )
        CASE_DATA_FORMAT_QCASWITCH          ( _fs_check_sec_vs_bi__class_qcaswitch();    )
        CASE_DATA_FORMAT_BCMSWITCH          ( _fs_check_sec_vs_bi__class_bcmswitch();    )
        CASE_DATA_FORMAT_CLOUDKEY           ( _fs_check_sec_vs_bi__class_cloudkey();     )
        CASE_DATA_FORMAT_ROUTER             ( _fs_check_sec_vs_bi__class_router();       )
        CASE_DATA_FORMAT_SWITCH             ( _fs_check_sec_vs_bi__class_switch();       )
        CASE_DATA_FORMAT_BASIC              ( _fs_check_sec_vs_bi__class_basic();        )
        CASE_DATA_FORMAT_BASIC4K            ( _fs_check_sec_vs_bi__class_basic4k();      )
        CASE_DATA_FORMAT_UNIVOX             ( _fs_check_sec_vs_bi__class_univox();       )
        CASE_DATA_FORMAT_WIFI_DIGITAL_BOARD ( _fs_check_sec_vs_bi__class_wifi_digital(); )
        CASE_DATA_FORMAT_WIFI_FLASH         ( _fs_check_sec_vs_bi__class_wifi();         )
        CASE_DATA_FORMAT_WIFI_RADIO_EEPROM  ( _fs_check_sec_vs_bi__class_wifi_radio();   )
        CASE_DATA_FORMAT_INVERTER           ( _fs_check_sec_vs_bi__class_inverter();     )
        CASE_DATA_FORMAT_SOLARGATEWAY       ( _fs_check_sec_vs_bi__class_solargateway(); )
        default:                             fs_failure(FS_FAILURE_fs_check_sec_vs_bi_1); break;
        }
    } else {
        fs_debug_printf("board.info file was not found.  Checks skipped.\n");
    }
}
#else
#undef _fs_check_sec_vs_bi
#define _fs_check_sec_vs_bi(...)
#endif // #if SECURITY_ENABLE_INI_SUPPORT

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw_no_pci(void) {
        _fs_check_flash_security_format();
        _fs_check_flash_type_id_sec_vs_hw();
        _fs_check_flash_uid_sec_vs_hw();
        // NB: We always are at version >= 1 so all the rev 1 checks are always run
        // NB: version 2 only adds the version workaround on most of the product classes, so there are no version 2 checks for most classes
        // NB: version 3 only adds QR code on most of the product classes, and this is not validated at runtime against anything.
        switch(fs_read_security_data_format_sec()) {
        CASE_DATA_FORMAT_AIRFIBER           ( _fs_check_sec_vs_hw_no_pci__class_airfiber();    )
        CASE_DATA_FORMAT_BCMWIFI            ( _fs_check_sec_vs_hw_no_pci__class_bcmwifi();     )
        CASE_DATA_FORMAT_CAMERA2            ( _fs_check_sec_vs_hw_no_pci__class_camera2();     )
        CASE_DATA_FORMAT_CAMERA             ( _fs_check_sec_vs_hw_no_pci__class_camera();      )
        CASE_DATA_FORMAT_NVR                ( _fs_check_sec_vs_hw_no_pci__class_nvr();         )
        CASE_DATA_FORMAT_QCASWITCH          ( _fs_check_sec_vs_hw_no_pci__class_qcaswitch();   )
        CASE_DATA_FORMAT_BCMSWITCH          ( _fs_check_sec_vs_hw_no_pci__class_bcmswitch();   )
        CASE_DATA_FORMAT_CLOUDKEY           ( _fs_check_sec_vs_hw_no_pci__class_cloudkey();    )
        CASE_DATA_FORMAT_ROUTER             ( _fs_check_sec_vs_hw_no_pci__class_router();      )
        CASE_DATA_FORMAT_SWITCH             ( _fs_check_sec_vs_hw_no_pci__class_switch();      )
        CASE_DATA_FORMAT_BASIC              ( _fs_check_sec_vs_hw_no_pci__class_basic();       )
        CASE_DATA_FORMAT_BASIC4K            ( _fs_check_sec_vs_hw_no_pci__class_basic4k();     )
        CASE_DATA_FORMAT_UNIVOX             ( _fs_check_sec_vs_hw_no_pci__class_univox();      )
        CASE_DATA_FORMAT_WIFI_DIGITAL_BOARD ( _fs_check_sec_vs_hw_no_pci__class_wifi_digital();)
        CASE_DATA_FORMAT_WIFI_FLASH         ( _fs_check_sec_vs_hw_no_pci__class_wifi();        )
        CASE_DATA_FORMAT_WIFI_RADIO_EEPROM  ( _fs_check_sec_vs_hw_no_pci__class_wifi_radio();  )
        CASE_DATA_FORMAT_SOLARGATEWAY       ( _fs_check_sec_vs_hw_no_pci__class_router();      )
        CASE_DATA_FORMAT_INVERTER           ( _fs_check_sec_vs_hw_no_pci__class_inverter();    )
        default:                               fs_failure(FS_FAILURE_fs_check_sec_vs_hw_no_pci_1);   break;
        }
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_hw(void) {
        _fs_check_sec_vs_hw_no_pci();
        // NB: We always are at version >= 1 so all the rev 1 checks are always run
        // NB: version 2 only adds the version workaround on most of the product classes, so there are no version 2 checks for most classes
        // NB: version 3 only adds QR code on most of the product classes, and this is not validated at runtime against anything.
        switch(fs_read_security_data_format_sec()) {
        CASE_DATA_FORMAT_AIRFIBER           ( _fs_check_sec_vs_hw__class_airfiber();            )
        CASE_DATA_FORMAT_BCMWIFI            ( _fs_check_sec_vs_hw__class_bcmwifi();             )
        CASE_DATA_FORMAT_CAMERA2            ( _fs_check_sec_vs_hw__class_camera2();             )
        CASE_DATA_FORMAT_CAMERA             ( _fs_check_sec_vs_hw__class_camera();              )
        CASE_DATA_FORMAT_NVR                ( _fs_check_sec_vs_hw__class_nvr();                 )
        CASE_DATA_FORMAT_QCASWITCH          ( _fs_check_sec_vs_hw__class_qcaswitch();           )
        CASE_DATA_FORMAT_BCMSWITCH          ( _fs_check_sec_vs_hw__class_bcmswitch();           )
        CASE_DATA_FORMAT_CLOUDKEY           ( _fs_check_sec_vs_hw__class_cloudkey();            )
        CASE_DATA_FORMAT_ROUTER             ( _fs_check_sec_vs_hw__class_router();              )
        CASE_DATA_FORMAT_SWITCH             ( _fs_check_sec_vs_hw__class_switch();              )
        CASE_DATA_FORMAT_BASIC              ( _fs_check_sec_vs_hw__class_basic();               )
        CASE_DATA_FORMAT_BASIC4K            ( _fs_check_sec_vs_hw__class_basic4k();             )
        CASE_DATA_FORMAT_UNIVOX             ( _fs_check_sec_vs_hw__class_univox();              )
        CASE_DATA_FORMAT_WIFI_DIGITAL_BOARD ( _fs_check_sec_vs_hw__class_wifi_digital();        )
        CASE_DATA_FORMAT_WIFI_FLASH         ( _fs_check_sec_vs_hw__class_wifi();                )
        CASE_DATA_FORMAT_WIFI_RADIO_EEPROM  ( _fs_check_sec_vs_hw__class_wifi_radio();          )
        CASE_DATA_FORMAT_INVERTER           ( _fs_check_sec_vs_hw__class_inverter();            )
        CASE_DATA_FORMAT_SOLARGATEWAY       ( _fs_check_sec_vs_hw__class_solargateway();        )
        default:                              fs_failure(FS_FAILURE_fs_check_sec_vs_hw_1);      break;
        }
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_vs_fbd(void) {
        _fs_check_flash_security_format();
        _fs_check_pcba_sec_vs_fbd(); // NB: Will automatically skip check on old boards without PCBA
        switch(fs_read_security_data_format_sec()) {
        CASE_DATA_FORMAT_AIRFIBER           ( _fs_check_sec_vs_fbd__class_airfiber();           )
        CASE_DATA_FORMAT_BCMWIFI            ( _fs_check_sec_vs_fbd__class_bcmwifi();            )
        CASE_DATA_FORMAT_CAMERA2            ( _fs_check_sec_vs_fbd__class_camera2();            )
        CASE_DATA_FORMAT_CAMERA             ( _fs_check_sec_vs_fbd__class_camera();             )
        CASE_DATA_FORMAT_NVR                ( _fs_check_sec_vs_fbd__class_nvr();                )
        CASE_DATA_FORMAT_QCASWITCH          ( _fs_check_sec_vs_fbd__class_qcaswitch();          )
        CASE_DATA_FORMAT_BCMSWITCH          ( _fs_check_sec_vs_fbd__class_bcmswitch();          )
        CASE_DATA_FORMAT_CLOUDKEY           ( _fs_check_sec_vs_fbd__class_cloudkey();           )
        CASE_DATA_FORMAT_ROUTER             ( _fs_check_sec_vs_fbd__class_router();             )
        CASE_DATA_FORMAT_SWITCH             ( _fs_check_sec_vs_fbd__class_switch();             )
        CASE_DATA_FORMAT_BASIC              ( _fs_check_sec_vs_fbd__class_basic();              )
        CASE_DATA_FORMAT_BASIC4K            ( _fs_check_sec_vs_fbd__class_basic4k();            )
        CASE_DATA_FORMAT_UNIVOX             ( _fs_check_sec_vs_fbd__class_univox();             )
        CASE_DATA_FORMAT_WIFI_DIGITAL_BOARD ( _fs_check_sec_vs_fbd__class_wifi_digital();       )
        CASE_DATA_FORMAT_WIFI_FLASH         ( _fs_check_sec_vs_fbd__class_wifi();               )
        CASE_DATA_FORMAT_WIFI_RADIO_EEPROM  ( _fs_check_sec_vs_fbd__class_wifi_radio();         )
        CASE_DATA_FORMAT_INVERTER           ( _fs_check_sec_vs_fbd__class_inverter();           )
        CASE_DATA_FORMAT_SOLARGATEWAY       ( _fs_check_sec_vs_fbd__class_solargateway();       )
        default:                              fs_failure(FS_FAILURE_fs_check_sec_vs_fbd_1);     break;
        }
}

#define FS_LOWLEVEL_ERRORS        ((SET_VAR(GET_VAR(fsv_failure)) & SET_VAR_OK())  != SET_VAR(GET_VAR(fsv_failure)))
#define FS_CHECKS_PASSED          ((SET_VAR(GET_VAR(fsv_failure)) & SET_VAR_HLF()) != SET_VAR(GET_VAR(fsv_failure)))
#define FS_CHECKS_FAILED          ((SET_VAR(GET_VAR(fsv_failure)) & SET_VAR_HLF()) == SET_VAR(GET_VAR(fsv_failure)))
#define FS_CHECKS_FAILED_SIGNED   (_fs_is_security_data_present()  && FS_CHECKS_FAILED)
#define FS_CHECKS_FAILED_UNSIGNED (!_fs_is_security_data_present() && FS_CHECKS_FAILED)
#define FS_CHECKS_PASSED_SIGNED   (_fs_is_security_data_present()  && FS_CHECKS_PASSED)
#define FS_CHECKS_PASSED_UNSIGNED (!_fs_is_security_data_present() && FS_CHECKS_PASSED)

#if SECURITY_ENABLE_RETRIES
#define FS_SECURITY_CHECK_FUNCTION(__name) \
__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void __name(void) { \
        fsv_failure_index = SET_VAR(0);  \
        fsv_failure       = SET_VAR_OK(); \
        memset(fsv_failure_codes,0xff,sizeof(fsv_failure_codes)); \
        fs_output_off(); \
        _ ## __name(); \
        fs_output_on(); \
        if ((SET_VAR(GET_VAR(fsv_failure)) & SET_VAR_OK()) != SET_VAR(GET_VAR(fsv_failure))) { \
                fs_output_off(); \
\
                fs_delay(SECURITY_RETRY_DELAY_S); \
                fsv_failure_index = SET_VAR(GET_VAR(fsv_failure_index)+1); \
                _ ## __name(); \
\
                fs_delay(SECURITY_RETRY_DELAY_S); \
                fsv_failure_index = SET_VAR(GET_VAR(fsv_failure_index)+1); \
                _ ## __name(); \
\
                fs_delay(SECURITY_RETRY_DELAY_S); \
                fsv_failure_index = SET_VAR(GET_VAR(fsv_failure_index)+1); \
                fs_output_on(); \
                _ ## __name(); \
        } \
}
#else // SECURITY_ENABLE_RETRIES
#define FS_SECURITY_CHECK_FUNCTION(__name) \
__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void __name(void) { \
        fsv_failure_index = SET_VAR(0);  \
        fsv_failure       = SET_VAR_OK(); \
        memset(fsv_failure_codes,0xff,sizeof(fsv_failure_codes)); \
        fs_output_off(); \
        _ ## __name(); \
        fs_output_on(); \
        if ((SET_VAR(GET_VAR(fsv_failure)) & SET_VAR_OK()) != SET_VAR(GET_VAR(fsv_failure))) { \
            _ ## __name(); \
            PRINT_LOCKDOWN_NOTICE(__failure_code); \
            DEBUG_DUMP_BITSET(FS_FAILURE_CODE_BITSET_IDX()); \
            fsv_failure = SET_VAR_HLF(); \
            fs_lockdown(); \
        } \
}
#endif // SECURITY_ENABLE_RETRIES

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec(void)
{
        _fs_check_sec_vs_hw();
        _fs_check_sec_vs_bi();
        _fs_check_sec_vs_fbd();
        _fs_check_esn_signature();
        _fs_check_ubnt_signature();
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_sec_no_pci(void) 
{
        _fs_check_sec_vs_hw_no_pci();
        _fs_check_sec_vs_bi();
        _fs_check_sec_vs_fbd();
        _fs_check_esn_signature();
       _fs_check_ubnt_signature();
}

#if SECURITY_ENABLE_ESN_SIGNATURE_CHECKS
FS_SECURITY_CHECK_FUNCTION(fs_check_esn_signature)
#endif // #if SECURITY_ENABLE_ESN_SIGNATURE_CHECKS
FS_SECURITY_CHECK_FUNCTION(fs_check_flash_security_format)
#if SECURITY_ENABLE_INI_SUPPORT
FS_SECURITY_CHECK_FUNCTION(fs_check_sec_vs_bi)
#endif // #if SECURITY_ENABLE_INI_SUPPORT
FS_SECURITY_CHECK_FUNCTION(fs_check_sec_vs_hw_no_pci)
FS_SECURITY_CHECK_FUNCTION(fs_check_sec_vs_hw)
FS_SECURITY_CHECK_FUNCTION(fs_check_ubnt_signature)
FS_SECURITY_CHECK_FUNCTION(fs_check_sec)
FS_SECURITY_CHECK_FUNCTION(fs_check_sec_no_pci)
