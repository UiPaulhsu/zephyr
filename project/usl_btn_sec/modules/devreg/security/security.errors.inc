typedef enum fs_failure_code {
        FS_FAILURE_fs_acquire_file_based_lock_1,
        FS_FAILURE_fs_acquire_file_based_lock_2,
        FS_FAILURE_fs_check_wifi_cpu_rev_id_sec_vs_cpu_rev_id_bi_1,
        FS_FAILURE_fs_check_wifi_cpu_rev_id_sec_vs_cpu_rev_id_hw_1,
        FS_FAILURE_fs_check_wifi_radio1_mac_address_sec_vs_wifi_radio1_mac_address_hw__if_radio_1_exists_1,
        FS_FAILURE_fs_check_wifi_radio1_mac_address_sec_vs_hwaddr_bi__if_radio_1_exists_1,
        FS_FAILURE_fs_check_wifi_radio1_mac_rev_id_sec_vs_wifi_radio1_mac_rev_id_hw_1,
        FS_FAILURE_fs_check_wifi_radio2_mac_address_sec_vs_wifi_radio2_mac_address_hw__if_radio_2_exists_1,
        FS_FAILURE_fs_check_camera_ahb_rev_id_sec_vs_GM81xx_ahb_rev_id_hw_1,
        FS_FAILURE_fs_check_camera_eth_mac_rev_id_sec_vs_GM81xx_eth_mac_rev_id_hw_1,
        FS_FAILURE_fs_check_camera_gpio_summary_id_sec_vs_GM81xx_gpio_summary_id_hw_1,
        FS_FAILURE_fs_check_camera_i2c_controller_rev_id_sec_vs_GM81xx_i2c_controller_rev_id_hw_1,
        FS_FAILURE_fs_check_camera_int_controller_summary_id_sec_vs_GM81xx_int_controller_summary_id_hw_1,
        FS_FAILURE_fs_check_camera_sd_card_reader_rev_id_sec_vs_GM81xx_sd_card_reader_rev_id_hw_1,
        FS_FAILURE_fs_check_camera_timer_summary_id_sec_vs_GM81xx_timer_summary_id_hw_1,
        FS_FAILURE_fs_check_camera2_ssi_ident_id_sec_vs_AMBA_ssi_ident_id_hw_1,
        FS_FAILURE_fs_check_camera2_ssi_version_id_sec_vs_AMBA_ssi_version_id_hw_1,
        FS_FAILURE_fs_check_esn_signature_1,
        FS_FAILURE_fs_check_esn_signature_2,
        FS_FAILURE_fs_check_flash_security_format_1,
        FS_FAILURE_fs_check_flash_type_id_sec_vs_flash_type_id_hw_1,
        FS_FAILURE_fs_check_flash_uid_sec_vs_hw_1,
        FS_FAILURE_fs_check_sec_vs_bi_1,
        FS_FAILURE_fs_check_sec_vs_hw_1,
        FS_FAILURE_fs_check_sec_vs_hw_no_pci_1,
        FS_FAILURE_fs_check_subsystem_id_sec_vs_wifi_radio1_subsystem_id_bi_1,
        FS_FAILURE_fs_check_subsystem_id_sec_vs_wifi_radio2_subsystem_id_bi_1,
        FS_FAILURE_fs_check_subsystem_id_sec_vs_system_id_bi_1,
        FS_FAILURE_fs_check_subvendor_id_sec_vs_wifi_radio1_subvendor_id_bi_1,
        FS_FAILURE_fs_check_subvendor_id_sec_vs_wifi_radio2_subvendor_id_bi_1,
        FS_FAILURE_fs_read_wifi_radio1_mac_rev_id_hw_1,
        FS_FAILURE_fs_read_wifi_radio1_mac_rev_id_hw_2,
        FS_FAILURE_fs_read_wifi_radio1_mac_rev_id_hw_3,
        FS_FAILURE_fs_read_wifi_radio2_mac_rev_id_hw_1,
        FS_FAILURE_fs_read_wifi_radio2_mac_rev_id_hw_2,
        FS_FAILURE_fs_read_wifi_radio2_mac_rev_id_hw_3,
        FS_FAILURE_fs_read_config_1,
        FS_FAILURE_fs_read_config_2,
        FS_FAILURE_fs_read_config_3,
        FS_FAILURE_fs_read_config_4,
        FS_FAILURE_fs_read_config_5,
        FS_FAILURE_fs_read_config_6,
        FS_FAILURE_fs_read_config_7,
        FS_FAILURE_fs_read_config_8,
        FS_FAILURE_fs_read_file_into_buffer_1,
        FS_FAILURE_fs_read_file_into_buffer_10,
        FS_FAILURE_fs_read_file_into_buffer_11,
        FS_FAILURE_fs_read_file_into_buffer_12,
        FS_FAILURE_fs_read_file_into_buffer_13,
        FS_FAILURE_fs_read_file_into_buffer_14,
        FS_FAILURE_fs_read_file_into_buffer_2,
        FS_FAILURE_fs_read_file_into_buffer_3,
        FS_FAILURE_fs_read_file_into_buffer_4,
        FS_FAILURE_fs_read_file_into_buffer_5,
        FS_FAILURE_fs_read_file_into_buffer_6,
        FS_FAILURE_fs_read_file_into_buffer_7,
        FS_FAILURE_fs_read_file_into_buffer_8,
        FS_FAILURE_fs_read_file_into_buffer_9,
        FS_FAILURE_fs_read_flash_uid_hw_1,
        FS_FAILURE_fs_read_from_mmapped_file_1,
        FS_FAILURE_fs_read_from_mmapped_file_2,
        FS_FAILURE_fs_read_from_mmapped_file_3,
        FS_FAILURE_fs_read_from_mmapped_file_4,
        FS_FAILURE_fs_read_ini_hex16_1,
        FS_FAILURE_fs_read_ini_hex32_1,
        FS_FAILURE_fs_read_ini_hex_raw_1,
        FS_FAILURE_fs_read_ini_hex_raw_2,
        FS_FAILURE_fs_read_ini_key_1,
        FS_FAILURE_fs_read_ini_key_2,
        FS_FAILURE_fs_read_ini_key_3,
        FS_FAILURE_fs_read_mac_address_hw_1,
        FS_FAILURE_fs_read_mem_1,
        FS_FAILURE_fs_read_mem_2,
        FS_FAILURE_fs_read_mem_3,
        FS_FAILURE_fs_read_mem_4,
        FS_FAILURE_fs_read_mem_5,
        FS_FAILURE_fs_get_config_offset_esn_sig_iv_area_sec_1,
        FS_FAILURE_fs_get_config_offset_esn_signature_sec_1,
        FS_FAILURE_fs_get_config_offset_esn_signed_end_1,
        FS_FAILURE_fs_get_config_offset_esn_signed_start_1,
        FS_FAILURE_fs_get_config_offset_ubnt_signature_sec_1,
        FS_FAILURE_fs_get_config_offset_ubnt_signed_end_1,
        FS_FAILURE_fs_get_config_offset_ubnt_signed_start_1,
        FS_FAILURE_fs_release_file_based_lock_1,
        FS_FAILURE_fs_check_ubnt_signature_2,
        FS_FAILURE_fs_check_ubnt_signature_1,
        FS_FAILURE_fs_save_buffer_to_file_1,
        FS_FAILURE_fs_save_buffer_to_file_2,
        FS_FAILURE_fs_save_buffer_to_file_3,
        FS_FAILURE_fs_save_buffer_to_file_4,
        FS_FAILURE_fs_save_buffer_to_file_5,
        FS_FAILURE_fs_save_buffer_to_file_6,
        FS_FAILURE_fs_save_buffer_to_file_7,
        FS_FAILURE_fs_save_buffer_to_file_8,
        FS_FAILURE_fs_check_wifi_radio2_mac_rev_id_sec_vs_wifi_radio2_mac_rev_id_hw_1,
        FS_FAILURE_fs_check_router_cpu_rev_id_sec_vs_cpu_rev_id_hw_1,
        FS_FAILURE_fs_check_airfiber_cpu_rev_id_sec_vs_AM18xx_cpu_rev_id_hw_1,
        FS_FAILURE_fs_check_switch_cpu_rev_id_sec_vs_cpu_rev_id_hw_1,
        FS_FAILURE_fs_check_switch_cpu_rev_id_sec_vs_cpu_rev_id_bi_1,
        FS_FAILURE_fs_check_router_cpu_rev_id_sec_vs_cpu_rev_id_bi_1,
        FS_FAILURE_fs_check_airfiber_cpu_rev_id_sec_vs_cpu_rev_id_bi_1,
        FS_FAILURE_fs_write_mem_1,
        FS_FAILURE_fs_write_to_mmapped_file_1,
        FS_FAILURE_fs_write_to_mmapped_file_2,
        FS_FAILURE_fs_write_to_mmapped_file_3,
        FS_FAILURE_fs_write_to_mmapped_file_4,
        FS_FAILURE_fs_check_airfiber_board_rev_id_sec_vs_airfiber_board_rev_id_fbd_1,
        FS_FAILURE_fs_check_eth0_mac_address_sec_vs_eth0_mac_address_hw_1,
        FS_FAILURE_fs_check_eth0_mac_address_sec_vs_airfiber_eth0_mac_address_fbd_1,
        FS_FAILURE_fs_check_airfiber_air0_mac_address_sec_vs_airfiber_air0_mac_address_hw_1,
        FS_FAILURE_fs_check_airfiber_air0_mac_address_sec_vs_airfiber_air0_mac_address_fbd_1,
        FS_FAILURE_fs_check_univox_board_rev_id_sec_vs_univox_board_rev_id_fbd_1,
        FS_FAILURE_fs_check_univox_cpu_rev_id_sec_vs_AM3xxx_cpu_rev_id_hw_1,
        FS_FAILURE_fs_check_univox_cpu_rev_id_sec_vs_cpu_rev_id_bi_1,
        FS_FAILURE_fs_check_eth0_mac_address_sec_vs_univox_eth0_mac_address_fbd_1,
        FS_FAILURE_fs_check_eth1_mac_address_sec_vs_eth1_mac_address_hw_2,
        FS_FAILURE_fs_check_eth1_mac_address_sec_vs_univox_eth1_mac_address_fbd_1,
        FS_FAILURE_fs_check_bcmwifi_board_rev_id_sec_vs_bcmwifi_board_rev_id_fbd_1,
        FS_FAILURE_fs_check_bcmwifi_cpu_rev_id_sec_vs_BCM4706_cpu_rev_id_hw_1,
        FS_FAILURE_fs_check_bcmwifi_cpu_rev_id_sec_vs_cpu_rev_id_bi_1,
        FS_FAILURE_fs_check_eth0_mac_address_sec_vs_bcmwifi_eth0_mac_address_fbd_1,
        FS_FAILURE_fs_check_subvendor_id_sec_vs_vendor_id_bi_1,
        FS_FAILURE_fs_check_bcmwifi_board_rev_id_sec_vs_board_rev_id_bi_1,
        FS_FAILURE_fs_check_eth1_mac_address_sec_vs_bcmwifi_eth1_mac_address_fbd_1,
        FS_FAILURE_fs_check_bcmwifi_wifi_radio1_mac_address_sec_vs_BCM4706_wifi_radio1_mac_address_hw__if_radio_1_exists_1,
        FS_FAILURE_fs_check_bcmwifi_wifi_radio2_mac_address_sec_vs_BCM4706_wifi_radio2_mac_address_hw__if_radio_2_exists_1,
        FS_FAILURE_fs_check_bcmwifi_wifi_radio1_mac_address_sec_vs_bcmwifi_wifi_radio1_mac_address_fbd_1,
        FS_FAILURE_fs_check_bcmwifi_wifi_radio2_mac_address_sec_vs_bcmwifi_wifi_radio2_mac_address_fbd_1,
        FS_FAILURE_fs_check_eth0_mac_address_sec_vs_eth0_mac_address_bi_1,
        FS_FAILURE_fs_check_eth1_mac_address_sec_vs_eth1_mac_address_bi_1,
        FS_FAILURE_fs_check_bcmwifi_wifi_radio1_mac_address_sec_vs_wifi_radio1_mac_address_bi__if_radio_1_exists_1,
        FS_FAILURE_fs_check_bcmwifi_wifi_radio2_mac_address_sec_vs_wifi_radio2_mac_address_bi__if_radio_2_exists_1,
        FS_FAILURE_fs_check_eth0_mac_address_sec_vs_eth0_mac_address_fbd_1,
        FS_FAILURE_fs_check_eth1_mac_address_sec_vs_eth1_mac_address_fbd_1,
        FS_FAILURE_fs_check_bcmwifi_wifi_radio1_id_sec_vs_wifi_radio1_id_bi_1,
        FS_FAILURE_fs_check_bcmwifi_wifi_radio2_id_sec_vs_wifi_radio2_id_bi_1,
        FS_FAILURE_fs_check_bcmwifi_wifi_radio1_vendor_id_sec_vs_wifi_radio1_vendor_id_bi_1,
        FS_FAILURE_fs_check_bcmwifi_wifi_radio2_vendor_id_sec_vs_wifi_radio2_vendor_id_bi_1,
        FS_FAILURE_fs_check_bcmwifi_wifi_radio1_device_id_sec_vs_wifi_radio1_device_id_bi_1,
        FS_FAILURE_fs_check_bcmwifi_wifi_radio2_device_id_sec_vs_wifi_radio2_device_id_bi_1,
        FS_FAILURE_fs_check_bcmwifi_wifi_radio1_id_sec_vs_BCM4706_wifi_radio1_id_hw_1,
        FS_FAILURE_fs_check_bcmwifi_wifi_radio2_id_sec_vs_BCM4706_wifi_radio2_id_hw_1,
        FS_FAILURE_fs_check_qcaswitch_board_rev_id_sec_vs_qcaswitch_board_rev_id_fbd_1,
        FS_FAILURE_fs_check_eth0_mac_address_sec_vs_qcaswitch_eth0_mac_address_fbd_1,
        FS_FAILURE_fs_check_qcaswitch_board_rev_id_sec_vs_board_rev_id_bi_1,
        FS_FAILURE_fs_check_eth0_mac_address_sec_vs_router_eth0_mac_address_fbd_1,
        FS_FAILURE_fs_check_eth1_mac_address_sec_vs_router_eth1_mac_address_fbd_1,
        FS_FAILURE_fs_check_subvendor_id_sec_vs_subvendor_id_fbd_1,
        FS_FAILURE_fs_check_subsystem_id_sec_vs_subsystem_id_fbd_1,
        FS_FAILURE_fs_check_sec_vs_fbd_1,
        FS_FAILURE_fs_write_config_1,
        FS_FAILURE_fs_write_config_2,
        FS_FAILURE_fs_write_config_3,
        FS_FAILURE_fs_check_eth0_mac_address_sec_vs_nvr_eth0_mac_address_fbd_1,
        FS_FAILURE_fs_check_eth1_mac_address_sec_vs_nvr_eth1_mac_address_fbd_1,
        FS_FAILURE_fs_check_univox_cpu_rev_id_sec_vs_BCM111xx_cpu_rev_id_hw_1,
        FS_FAILURE_fs_get_config_offset_qr_code_1,
        FS_FAILURE_fs_check_bcmswitch_vpd_sec_vs_fbd_1,
        FS_FAILURE_fs_check_eth0_mac_address_sec_vs_bcmswitch_eth0_mac_address_fbd_1,
        FS_FAILURE_fs_get_config_offset_pcba_sec_1,
        FS_FAILURE_fs_get_config_offset_pcba_sec_2,
        FS_FAILURE_fs_check_pcba_sec_vs_pcba_fbd_1,
        FS_FAILURE_fs_check_bcmswitch_cpu_rev_id_sec_vs_BCM5334x_cpu_rev_id_hw_1,
        FS_FAILURE_fs_strip_quotes_1,
        FS_FAILURE_fs_read_mac_address_hw_2,
        FS_FAILURE_fs_read_ini_hex_raw_3,
        FS_FAILURE_fs_read_ini_key_4,
        FS_FAILURE_fs_check_router_vpd_sec_vs_fbd_1,
        FS_FAILURE_fs_read_ini_hex_raw_4,
        FS_FAILURE_fs_read_ini_hex_raw_5,
        FS_FAILURE_fs_read_ini_hex_raw_6,
        FS_FAILURE_fs_read_ini_hex16_2,
        FS_FAILURE_fs_read_ini_hex32_2,
        FS_FAILURE_fs_read_ini_key_5,
        FS_FAILURE_fs_check_univox_cpu_rev_id_sec_vs_MT8117_cpu_rev_id_hw_1,
        FS_FAILURE_fs_read_config_9,
        FS_FAILURE_fs_read_flash_uid_hw_2,
        FS_FAILURE_fs_check_univox_cpu_rev_id_sec_vs_hw_1,
        FS_FAILURE_fs_write_config_4,
        FS_FAILURE_fs_write_config_5,
        FS_FAILURE_fs_write_config_6,
        FS_FAILURE_fs_sha512_sha512_sec_1,
        FS_FAILURE_fs_check_eth0_mac_address_sec_vs_cloudkey_eth0_mac_address_fbd_1,
        FS_FAILURE_fs_check_cloudkey_cpu_rev_id_sec_vs_MT7623_cpu_rev_id_hw_1,
        FS_FAILURE_fs_check_eth0_mac_address_sec_vs_solargateway_eth0_mac_address_fbd_1,
        FS_FAILURE_fs_check_eth1_mac_address_sec_vs_solargateway_eth1_mac_address_fbd_1,
        FS_FAILURE_fs_check_eth1_mac_address_sec_vs_eth1_mac_address_hw_1,
        FS_FAILURE_fs_check_solargateway_cpu_rev_id_sec_vs_cpu_rev_id_hw_1,
        FS_FAILURE_fs_check_solargateway_cpu_rev_id_sec_vs_MT7621_cpu_rev_id_hw_1,
        FS_FAILURE_fs_check_router_cpu_rev_id_sec_vs_MT7621_cpu_rev_id_hw_1,
        FS_FAILURE_fs_check_bcmswitch_cpu_rev_id_sec_vs_BCM5341x_cpu_rev_id_hw_1,
        FS_FAILURE_fs_check_bcmswitch_cpu_rev_id_sec_vs_BCM5616x_cpu_rev_id_hw_1,
        FS_FAILURE_fs_check_basic_cpu_rev_id_sec_vs_cpu_rev_id_hw_1,
        FS_FAILURE_fs_check_basic_cpu_rev_id_sec_vs_cpu_rev_id_bi_1,
        FS_FAILURE_fs_check_ubnt_signature_3,
        FS_FAILURE_fs_compute_ubnt_hash_1,
        FS_FAILURE_fs_compute_esn_hash_1,
        FS_FAILURE_fs_sha512_sha512_sec_2,
        FS_FAILURE_fs_sha512_sha512_1,
        FS_FAILURE_fs_get_config_offset_fcd_id_sec_1,
        FS_FAILURE_fs_get_config_offset_fcd_version_sec_1,
        FS_FAILURE_fs_get_config_offset_sw_version_sec_1,
        FS_FAILURE_fs_read_eth0_mac_address_hw_1,
        FS_FAILURE_fs_read_eth1_mac_address_hw_1,
        FS_FAILURE_fs_read_wifi_radio1_mac_address_hw_1,
        FS_FAILURE_fs_read_wifi_radio2_mac_address_hw_1,
        FS_FAILURE_fs_get_config_offset_flash_uid_sec_1,
        FS_FAILURE_fs_get_config_offset_flash_uid_length_sec_1,
        FS_FAILURE_fs_get_config_offset_flash_type_id_sec_1,
        FS_FAILURE_fs_get_config_offset_eth0_mac_address_sec_1,
        FS_FAILURE_fs_get_config_offset_eth1_mac_address_sec_1,
        FS_FAILURE_fs_get_config_offset_subvendor_id_sec_1,
        FS_FAILURE_fs_get_config_offset_security_data_revision_raw_sec_1,
        FS_FAILURE_fs_get_config_offset_product_class_id_sec_1,
        FS_FAILURE_fs_get_config_offset_device_id_sec_1,
        FS_FAILURE_fs_get_config_offset_registration_id_sec_1,
        FS_FAILURE_fs_get_config_offset_subsystem_id_sec_1,
        FS_FAILURE_fs_get_config_offset_cpu_rev_id_sec_1,
        FS_FAILURE_fs_get_config_offset_vpd_sec_1,
        FS_FAILURE_fs_get_config_offset_manufacturer_id_sec_1,
        FS_FAILURE_fs_get_config_offset_registration_timestamp_sec_1,
        FS_FAILURE_fs_get_config_offset_qr_code_sec_1,
        FS_FAILURE_fs_get_config_offset_flash_jedec_id_sec_1,
        FS_FAILURE_fs_get_config_offset_fcd_version_1,
        FS_FAILURE_fs_get_config_offset_sw_version_1,
        FS_FAILURE_fs_get_config_offset_pcba_sec_3,
        FS_FAILURE_fs_get_config_offset_fcd_version_sec_2,
        FS_FAILURE_fs_get_config_offset_esn_signed_start_2,
        FS_FAILURE_fs_get_config_offset_ubnt_signed_start_2,
        FS_FAILURE_fs_get_config_offset_qr_code_sec_2,
        FS_FAILURE_fs_get_config_offset_fcd_id_sec_2,
        FS_FAILURE_fs_get_config_offset_sw_version_sec_2,
        FS_FAILURE_fs_get_config_offset_sw_id_sec_1,
        FS_FAILURE_fs_get_config_offset_sw_id_sec_2,
        FS_FAILURE_fs_check_basic4k_cpu_rev_id_sec_vs_cpu_rev_id_hw_1,
        FS_FAILURE_fs_check_basic4k_cpu_rev_id_sec_vs_cpu_rev_id_bi_1,
        FS_FAILURE_NUM_FAILURE_CODES
} fs_failure_code_t;

#if SECURITY_ENABLE_DEBUG_OUTPUT

#ifndef __cplusplus
#define MESSAGE(__CONSTANT) [__CONSTANT] = ((#__CONSTANT)+11),
static const char* fs_error_messages[] = {
#else
#define MESSAGE(__CONSTANT) fs_error_messages[__CONSTANT] = ((#__CONSTANT)+11);
static const char* fs_error_messages[FS_FAILURE_NUM_FAILURE_CODES];

static bool _err_init = false;

class fs_error_init {
public:
	fs_error_init() {
		if (_err_init)
			return;
		_err_init = true;

#endif
        MESSAGE(FS_FAILURE_fs_acquire_file_based_lock_1)
        MESSAGE(FS_FAILURE_fs_acquire_file_based_lock_2)
        MESSAGE(FS_FAILURE_fs_check_wifi_cpu_rev_id_sec_vs_cpu_rev_id_bi_1)
        MESSAGE(FS_FAILURE_fs_check_wifi_cpu_rev_id_sec_vs_cpu_rev_id_hw_1)
        MESSAGE(FS_FAILURE_fs_check_wifi_radio1_mac_address_sec_vs_wifi_radio1_mac_address_hw__if_radio_1_exists_1)
        MESSAGE(FS_FAILURE_fs_check_wifi_radio1_mac_address_sec_vs_hwaddr_bi__if_radio_1_exists_1)
        MESSAGE(FS_FAILURE_fs_check_wifi_radio1_mac_rev_id_sec_vs_wifi_radio1_mac_rev_id_hw_1)
        MESSAGE(FS_FAILURE_fs_check_wifi_radio2_mac_address_sec_vs_wifi_radio2_mac_address_hw__if_radio_2_exists_1)
        MESSAGE(FS_FAILURE_fs_check_wifi_radio2_mac_rev_id_sec_vs_wifi_radio2_mac_rev_id_hw_1)
        MESSAGE(FS_FAILURE_fs_check_camera_ahb_rev_id_sec_vs_GM81xx_ahb_rev_id_hw_1)
        MESSAGE(FS_FAILURE_fs_check_camera_eth_mac_rev_id_sec_vs_GM81xx_eth_mac_rev_id_hw_1)
        MESSAGE(FS_FAILURE_fs_check_camera_gpio_summary_id_sec_vs_GM81xx_gpio_summary_id_hw_1)
        MESSAGE(FS_FAILURE_fs_check_camera_i2c_controller_rev_id_sec_vs_GM81xx_i2c_controller_rev_id_hw_1)
        MESSAGE(FS_FAILURE_fs_check_camera_int_controller_summary_id_sec_vs_GM81xx_int_controller_summary_id_hw_1)
        MESSAGE(FS_FAILURE_fs_check_camera_sd_card_reader_rev_id_sec_vs_GM81xx_sd_card_reader_rev_id_hw_1)
        MESSAGE(FS_FAILURE_fs_check_camera_timer_summary_id_sec_vs_GM81xx_timer_summary_id_hw_1)
        MESSAGE(FS_FAILURE_fs_check_camera2_ssi_ident_id_sec_vs_AMBA_ssi_ident_id_hw_1)
        MESSAGE(FS_FAILURE_fs_check_camera2_ssi_version_id_sec_vs_AMBA_ssi_version_id_hw_1)
        MESSAGE(FS_FAILURE_fs_check_esn_signature_1)
        MESSAGE(FS_FAILURE_fs_check_esn_signature_2)
        MESSAGE(FS_FAILURE_fs_check_flash_security_format_1)
        MESSAGE(FS_FAILURE_fs_check_flash_type_id_sec_vs_flash_type_id_hw_1)
        MESSAGE(FS_FAILURE_fs_check_flash_uid_sec_vs_hw_1)
        MESSAGE(FS_FAILURE_fs_check_sec_vs_bi_1)
        MESSAGE(FS_FAILURE_fs_check_sec_vs_hw_1)
        MESSAGE(FS_FAILURE_fs_check_sec_vs_hw_no_pci_1)
        MESSAGE(FS_FAILURE_fs_check_subsystem_id_sec_vs_wifi_radio1_subsystem_id_bi_1)
        MESSAGE(FS_FAILURE_fs_check_subsystem_id_sec_vs_wifi_radio2_subsystem_id_bi_1)
        MESSAGE(FS_FAILURE_fs_check_subsystem_id_sec_vs_system_id_bi_1)
        MESSAGE(FS_FAILURE_fs_check_subvendor_id_sec_vs_wifi_radio1_subvendor_id_bi_1)
        MESSAGE(FS_FAILURE_fs_check_subvendor_id_sec_vs_wifi_radio2_subvendor_id_bi_1)
        MESSAGE(FS_FAILURE_fs_read_wifi_radio1_mac_rev_id_hw_1)
        MESSAGE(FS_FAILURE_fs_read_wifi_radio1_mac_rev_id_hw_2)
        MESSAGE(FS_FAILURE_fs_read_wifi_radio1_mac_rev_id_hw_3)
        MESSAGE(FS_FAILURE_fs_read_wifi_radio2_mac_rev_id_hw_1)
        MESSAGE(FS_FAILURE_fs_read_wifi_radio2_mac_rev_id_hw_2)
        MESSAGE(FS_FAILURE_fs_read_wifi_radio2_mac_rev_id_hw_3)
        MESSAGE(FS_FAILURE_fs_read_config_1)
        MESSAGE(FS_FAILURE_fs_read_config_2)
        MESSAGE(FS_FAILURE_fs_read_config_3)
        MESSAGE(FS_FAILURE_fs_read_config_4)
        MESSAGE(FS_FAILURE_fs_read_config_5)
        MESSAGE(FS_FAILURE_fs_read_config_6)
        MESSAGE(FS_FAILURE_fs_read_config_7)
        MESSAGE(FS_FAILURE_fs_read_config_8)
        MESSAGE(FS_FAILURE_fs_read_file_into_buffer_1)
        MESSAGE(FS_FAILURE_fs_read_file_into_buffer_10)
        MESSAGE(FS_FAILURE_fs_read_file_into_buffer_11)
        MESSAGE(FS_FAILURE_fs_read_file_into_buffer_12)
        MESSAGE(FS_FAILURE_fs_read_file_into_buffer_13)
        MESSAGE(FS_FAILURE_fs_read_file_into_buffer_14)
        MESSAGE(FS_FAILURE_fs_read_file_into_buffer_2)
        MESSAGE(FS_FAILURE_fs_read_file_into_buffer_3)
        MESSAGE(FS_FAILURE_fs_read_file_into_buffer_4)
        MESSAGE(FS_FAILURE_fs_read_file_into_buffer_5)
        MESSAGE(FS_FAILURE_fs_read_file_into_buffer_6)
        MESSAGE(FS_FAILURE_fs_read_file_into_buffer_7)
        MESSAGE(FS_FAILURE_fs_read_file_into_buffer_8)
        MESSAGE(FS_FAILURE_fs_read_file_into_buffer_9)
        MESSAGE(FS_FAILURE_fs_read_flash_uid_hw_1)
        MESSAGE(FS_FAILURE_fs_read_from_mmapped_file_1)
        MESSAGE(FS_FAILURE_fs_read_from_mmapped_file_2)
        MESSAGE(FS_FAILURE_fs_read_from_mmapped_file_3)
        MESSAGE(FS_FAILURE_fs_read_from_mmapped_file_4)
        MESSAGE(FS_FAILURE_fs_read_ini_hex16_1)
        MESSAGE(FS_FAILURE_fs_read_ini_hex32_1)
        MESSAGE(FS_FAILURE_fs_read_ini_hex_raw_1)
        MESSAGE(FS_FAILURE_fs_read_ini_hex_raw_2)
        MESSAGE(FS_FAILURE_fs_read_ini_key_1)
        MESSAGE(FS_FAILURE_fs_read_ini_key_2)
        MESSAGE(FS_FAILURE_fs_read_ini_key_3)
        MESSAGE(FS_FAILURE_fs_read_mac_address_hw_1)
        MESSAGE(FS_FAILURE_fs_read_mem_1)
        MESSAGE(FS_FAILURE_fs_read_mem_2)
        MESSAGE(FS_FAILURE_fs_read_mem_3)
        MESSAGE(FS_FAILURE_fs_read_mem_4)
        MESSAGE(FS_FAILURE_fs_read_mem_5)
        MESSAGE(FS_FAILURE_fs_get_config_offset_esn_sig_iv_area_sec_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_esn_signature_sec_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_esn_signed_end_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_esn_signed_start_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_ubnt_signature_sec_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_ubnt_signed_end_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_ubnt_signed_start_1)
        MESSAGE(FS_FAILURE_fs_release_file_based_lock_1)
        MESSAGE(FS_FAILURE_fs_check_ubnt_signature_2)
        MESSAGE(FS_FAILURE_fs_check_ubnt_signature_1)
        MESSAGE(FS_FAILURE_fs_save_buffer_to_file_1)
        MESSAGE(FS_FAILURE_fs_save_buffer_to_file_2)
        MESSAGE(FS_FAILURE_fs_save_buffer_to_file_3)
        MESSAGE(FS_FAILURE_fs_save_buffer_to_file_4)
        MESSAGE(FS_FAILURE_fs_save_buffer_to_file_5)
        MESSAGE(FS_FAILURE_fs_save_buffer_to_file_6)
        MESSAGE(FS_FAILURE_fs_save_buffer_to_file_7)
        MESSAGE(FS_FAILURE_fs_save_buffer_to_file_8)
        MESSAGE(FS_FAILURE_fs_check_router_cpu_rev_id_sec_vs_cpu_rev_id_hw_1)
        MESSAGE(FS_FAILURE_fs_check_airfiber_cpu_rev_id_sec_vs_AM18xx_cpu_rev_id_hw_1)
        MESSAGE(FS_FAILURE_fs_check_switch_cpu_rev_id_sec_vs_cpu_rev_id_hw_1)
        MESSAGE(FS_FAILURE_fs_check_switch_cpu_rev_id_sec_vs_cpu_rev_id_bi_1)
        MESSAGE(FS_FAILURE_fs_check_airfiber_cpu_rev_id_sec_vs_cpu_rev_id_bi_1)
        MESSAGE(FS_FAILURE_fs_write_mem_1)
        MESSAGE(FS_FAILURE_fs_write_to_mmapped_file_1)
        MESSAGE(FS_FAILURE_fs_write_to_mmapped_file_2)
        MESSAGE(FS_FAILURE_fs_write_to_mmapped_file_3)
        MESSAGE(FS_FAILURE_fs_write_to_mmapped_file_4)
        MESSAGE(FS_FAILURE_fs_check_eth0_mac_address_sec_vs_eth0_mac_address_hw_1)
        MESSAGE(FS_FAILURE_fs_check_eth0_mac_address_sec_vs_airfiber_eth0_mac_address_fbd_1)
        MESSAGE(FS_FAILURE_fs_check_airfiber_air0_mac_address_sec_vs_airfiber_air0_mac_address_hw_1)
        MESSAGE(FS_FAILURE_fs_check_airfiber_air0_mac_address_sec_vs_airfiber_air0_mac_address_fbd_1)
        MESSAGE(FS_FAILURE_fs_check_airfiber_board_rev_id_sec_vs_airfiber_board_rev_id_fbd_1)
        MESSAGE(FS_FAILURE_fs_check_univox_board_rev_id_sec_vs_univox_board_rev_id_fbd_1)
        MESSAGE(FS_FAILURE_fs_check_univox_cpu_rev_id_sec_vs_AM3xxx_cpu_rev_id_hw_1)
        MESSAGE(FS_FAILURE_fs_check_univox_cpu_rev_id_sec_vs_cpu_rev_id_bi_1)
        MESSAGE(FS_FAILURE_fs_check_eth0_mac_address_sec_vs_univox_eth0_mac_address_fbd_1)
        MESSAGE(FS_FAILURE_fs_check_eth1_mac_address_sec_vs_eth1_mac_address_hw_2)
        MESSAGE(FS_FAILURE_fs_check_eth1_mac_address_sec_vs_univox_eth1_mac_address_fbd_1)
        MESSAGE(FS_FAILURE_fs_check_bcmwifi_board_rev_id_sec_vs_bcmwifi_board_rev_id_fbd_1)
        MESSAGE(FS_FAILURE_fs_check_bcmwifi_cpu_rev_id_sec_vs_BCM4706_cpu_rev_id_hw_1)
        MESSAGE(FS_FAILURE_fs_check_bcmwifi_cpu_rev_id_sec_vs_cpu_rev_id_bi_1)
        MESSAGE(FS_FAILURE_fs_check_eth0_mac_address_sec_vs_bcmwifi_eth0_mac_address_fbd_1)
        MESSAGE(FS_FAILURE_fs_check_subvendor_id_sec_vs_vendor_id_bi_1)
        MESSAGE(FS_FAILURE_fs_check_bcmwifi_board_rev_id_sec_vs_board_rev_id_bi_1)
        MESSAGE(FS_FAILURE_fs_check_eth1_mac_address_sec_vs_bcmwifi_eth1_mac_address_fbd_1)
        MESSAGE(FS_FAILURE_fs_check_bcmwifi_wifi_radio1_mac_address_sec_vs_BCM4706_wifi_radio1_mac_address_hw__if_radio_1_exists_1)
        MESSAGE(FS_FAILURE_fs_check_bcmwifi_wifi_radio2_mac_address_sec_vs_BCM4706_wifi_radio2_mac_address_hw__if_radio_2_exists_1)
        MESSAGE(FS_FAILURE_fs_check_bcmwifi_wifi_radio1_mac_address_sec_vs_bcmwifi_wifi_radio1_mac_address_fbd_1)
        MESSAGE(FS_FAILURE_fs_check_bcmwifi_wifi_radio2_mac_address_sec_vs_bcmwifi_wifi_radio2_mac_address_fbd_1)
        MESSAGE(FS_FAILURE_fs_check_eth0_mac_address_sec_vs_eth0_mac_address_bi_1)
        MESSAGE(FS_FAILURE_fs_check_eth1_mac_address_sec_vs_eth1_mac_address_bi_1)
        MESSAGE(FS_FAILURE_fs_check_bcmwifi_wifi_radio1_mac_address_sec_vs_wifi_radio1_mac_address_bi__if_radio_1_exists_1)
        MESSAGE(FS_FAILURE_fs_check_bcmwifi_wifi_radio2_mac_address_sec_vs_wifi_radio2_mac_address_bi__if_radio_2_exists_1)
        MESSAGE(FS_FAILURE_fs_check_eth0_mac_address_sec_vs_eth0_mac_address_fbd_1)
        MESSAGE(FS_FAILURE_fs_check_eth1_mac_address_sec_vs_eth1_mac_address_fbd_1)
        MESSAGE(FS_FAILURE_fs_check_bcmwifi_wifi_radio1_id_sec_vs_wifi_radio1_id_bi_1)
        MESSAGE(FS_FAILURE_fs_check_bcmwifi_wifi_radio2_id_sec_vs_wifi_radio2_id_bi_1)
        MESSAGE(FS_FAILURE_fs_check_bcmwifi_wifi_radio1_vendor_id_sec_vs_wifi_radio1_vendor_id_bi_1)
        MESSAGE(FS_FAILURE_fs_check_bcmwifi_wifi_radio2_vendor_id_sec_vs_wifi_radio2_vendor_id_bi_1)
        MESSAGE(FS_FAILURE_fs_check_bcmwifi_wifi_radio1_device_id_sec_vs_wifi_radio1_device_id_bi_1)
        MESSAGE(FS_FAILURE_fs_check_bcmwifi_wifi_radio2_device_id_sec_vs_wifi_radio2_device_id_bi_1)
        MESSAGE(FS_FAILURE_fs_check_bcmwifi_wifi_radio1_id_sec_vs_BCM4706_wifi_radio1_id_hw_1)
        MESSAGE(FS_FAILURE_fs_check_bcmwifi_wifi_radio2_id_sec_vs_BCM4706_wifi_radio2_id_hw_1)
        MESSAGE(FS_FAILURE_fs_check_eth0_mac_address_sec_vs_router_eth0_mac_address_fbd_1)
        MESSAGE(FS_FAILURE_fs_check_eth1_mac_address_sec_vs_router_eth1_mac_address_fbd_1)
        MESSAGE(FS_FAILURE_fs_check_subvendor_id_sec_vs_subvendor_id_fbd_1)
        MESSAGE(FS_FAILURE_fs_check_subsystem_id_sec_vs_subsystem_id_fbd_1)
        MESSAGE(FS_FAILURE_fs_check_sec_vs_fbd_1)
        MESSAGE(FS_FAILURE_fs_write_config_1)
        MESSAGE(FS_FAILURE_fs_write_config_2)
        MESSAGE(FS_FAILURE_fs_write_config_3)
        MESSAGE(FS_FAILURE_fs_check_eth0_mac_address_sec_vs_nvr_eth0_mac_address_fbd_1)
        MESSAGE(FS_FAILURE_fs_check_qcaswitch_board_rev_id_sec_vs_qcaswitch_board_rev_id_fbd_1)
        MESSAGE(FS_FAILURE_fs_check_eth0_mac_address_sec_vs_qcaswitch_eth0_mac_address_fbd_1)
        MESSAGE(FS_FAILURE_fs_check_eth1_mac_address_sec_vs_nvr_eth1_mac_address_fbd_1)
        MESSAGE(FS_FAILURE_fs_check_univox_cpu_rev_id_sec_vs_BCM111xx_cpu_rev_id_hw_1)
        MESSAGE(FS_FAILURE_fs_check_univox_cpu_rev_id_sec_vs_MT8117_cpu_rev_id_hw_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_qr_code_1)
        MESSAGE(FS_FAILURE_fs_check_bcmswitch_vpd_sec_vs_fbd_1)
        MESSAGE(FS_FAILURE_fs_check_eth0_mac_address_sec_vs_bcmswitch_eth0_mac_address_fbd_1)
        MESSAGE(FS_FAILURE_fs_check_qcaswitch_board_rev_id_sec_vs_board_rev_id_bi_1)
        MESSAGE(FS_FAILURE_fs_check_router_cpu_rev_id_sec_vs_cpu_rev_id_bi_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_pcba_sec_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_pcba_sec_2)
        MESSAGE(FS_FAILURE_fs_check_pcba_sec_vs_pcba_fbd_1)
        MESSAGE(FS_FAILURE_fs_check_bcmswitch_cpu_rev_id_sec_vs_BCM5334x_cpu_rev_id_hw_1)
        MESSAGE(FS_FAILURE_fs_strip_quotes_1)
        MESSAGE(FS_FAILURE_fs_read_mac_address_hw_2)
        MESSAGE(FS_FAILURE_fs_read_ini_hex_raw_3)
        MESSAGE(FS_FAILURE_fs_read_ini_key_4)
        MESSAGE(FS_FAILURE_fs_check_router_vpd_sec_vs_fbd_1)
        MESSAGE(FS_FAILURE_fs_read_ini_hex_raw_4)
        MESSAGE(FS_FAILURE_fs_read_ini_hex_raw_5)
        MESSAGE(FS_FAILURE_fs_read_ini_hex_raw_6)
        MESSAGE(FS_FAILURE_fs_read_ini_hex16_2)
        MESSAGE(FS_FAILURE_fs_read_ini_hex32_2)
        MESSAGE(FS_FAILURE_fs_read_ini_key_5)
        MESSAGE(FS_FAILURE_fs_read_config_9)
        MESSAGE(FS_FAILURE_fs_read_flash_uid_hw_2)
        MESSAGE(FS_FAILURE_fs_check_univox_cpu_rev_id_sec_vs_hw_1)
        MESSAGE(FS_FAILURE_fs_write_config_4)
        MESSAGE(FS_FAILURE_fs_write_config_5)
        MESSAGE(FS_FAILURE_fs_write_config_6)
        MESSAGE(FS_FAILURE_fs_sha512_sha512_sec_1)
        MESSAGE(FS_FAILURE_fs_check_eth0_mac_address_sec_vs_cloudkey_eth0_mac_address_fbd_1)
        MESSAGE(FS_FAILURE_fs_check_cloudkey_cpu_rev_id_sec_vs_MT7623_cpu_rev_id_hw_1)
        MESSAGE(FS_FAILURE_fs_check_eth0_mac_address_sec_vs_solargateway_eth0_mac_address_fbd_1)
        MESSAGE(FS_FAILURE_fs_check_eth1_mac_address_sec_vs_solargateway_eth1_mac_address_fbd_1)
        MESSAGE(FS_FAILURE_fs_check_eth1_mac_address_sec_vs_eth1_mac_address_hw_1)
        MESSAGE(FS_FAILURE_fs_check_solargateway_cpu_rev_id_sec_vs_cpu_rev_id_hw_1)
        MESSAGE(FS_FAILURE_fs_check_bcmswitch_cpu_rev_id_sec_vs_BCM5341x_cpu_rev_id_hw_1)
        MESSAGE(FS_FAILURE_fs_check_bcmswitch_cpu_rev_id_sec_vs_BCM5616x_cpu_rev_id_hw_1)
        MESSAGE(FS_FAILURE_fs_check_basic_cpu_rev_id_sec_vs_cpu_rev_id_hw_1)
        MESSAGE(FS_FAILURE_fs_check_basic_cpu_rev_id_sec_vs_cpu_rev_id_bi_1)
        MESSAGE(FS_FAILURE_fs_check_basic4k_cpu_rev_id_sec_vs_cpu_rev_id_hw_1)
        MESSAGE(FS_FAILURE_fs_check_basic4k_cpu_rev_id_sec_vs_cpu_rev_id_bi_1)
        MESSAGE(FS_FAILURE_fs_compute_ubnt_hash_1)
        MESSAGE(FS_FAILURE_fs_compute_esn_hash_1)
        MESSAGE(FS_FAILURE_fs_sha512_sha512_sec_2)
        MESSAGE(FS_FAILURE_fs_sha512_sha512_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_fcd_id_sec_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_fcd_version_sec_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_sw_version_sec_1)
        MESSAGE(FS_FAILURE_fs_read_eth0_mac_address_hw_1)
        MESSAGE(FS_FAILURE_fs_read_eth1_mac_address_hw_1)
        MESSAGE(FS_FAILURE_fs_read_wifi_radio1_mac_address_hw_1)
        MESSAGE(FS_FAILURE_fs_read_wifi_radio2_mac_address_hw_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_flash_uid_sec_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_flash_uid_length_sec_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_flash_type_id_sec_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_eth0_mac_address_sec_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_eth1_mac_address_sec_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_subvendor_id_sec_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_security_data_revision_raw_sec_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_product_class_id_sec_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_device_id_sec_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_registration_id_sec_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_subsystem_id_sec_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_cpu_rev_id_sec_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_vpd_sec_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_manufacturer_id_sec_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_registration_timestamp_sec_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_qr_code_sec_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_flash_jedec_id_sec_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_fcd_version_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_sw_version_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_pcba_sec_3)
        MESSAGE(FS_FAILURE_fs_check_ubnt_signature_3)
        MESSAGE(FS_FAILURE_fs_get_config_offset_fcd_version_sec_2)
        MESSAGE(FS_FAILURE_fs_get_config_offset_esn_signed_start_2)
        MESSAGE(FS_FAILURE_fs_get_config_offset_ubnt_signed_start_2)
        MESSAGE(FS_FAILURE_fs_get_config_offset_qr_code_sec_2)
        MESSAGE(FS_FAILURE_fs_get_config_offset_fcd_id_sec_2)
        MESSAGE(FS_FAILURE_fs_get_config_offset_sw_version_sec_2)
        MESSAGE(FS_FAILURE_fs_get_config_offset_sw_id_sec_1)
        MESSAGE(FS_FAILURE_fs_get_config_offset_sw_id_sec_2)
#ifndef __cplusplus                                                  
};
#else
	}

	~fs_error_init() {};
};

static fs_error_init _fs_error_init;
#endif

#if 0
UNREACHABLE:FS_FAILURE_fs_check_bcmwifi_board_rev_id_sec_vs_bcmwifi_board_rev_id_fbd_1                                        // DEPRECATED
UNREACHABLE:FS_FAILURE_fs_check_bcmwifi_board_rev_id_sec_vs_board_rev_id_bi_1                                                 // DEPRECATED
UNREACHABLE:FS_FAILURE_fs_check_eth1_mac_address_sec_vs_eth1_mac_address_hw_1                                                 // not checked / cloning allowed
UNREACHABLE:FS_FAILURE_fs_check_eth1_mac_address_sec_vs_eth1_mac_address_hw_2                                                 // not checked / cloning allowed
UNREACHABLE:FS_FAILURE_fs_check_eth1_mac_address_sec_vs_nvr_eth1_mac_address_fbd_1                                            // eth1 is not stored in flash board data after all
UNREACHABLE:FS_FAILURE_fs_check_eth1_mac_address_sec_vs_router_eth1_mac_address_fbd_1                                         // Router is not using eth1 FBD (even though it is populatd, we do not copy it to security area or use it in any way)
UNREACHABLE:FS_FAILURE_fs_check_qcaswitch_board_rev_id_sec_vs_board_rev_id_bi_1                                               // DEPRECATED
UNREACHABLE:FS_FAILURE_fs_check_qcaswitch_board_rev_id_sec_vs_qcaswitch_board_rev_id_fbd_1                                    // DEPRECATED
UNREACHABLE:FS_FAILURE_fs_check_univox_cpu_rev_id_sec_vs_AM3xxx_cpu_rev_id_hw_1                                               // DEPRECATED
UNREACHABLE:FS_FAILURE_fs_check_univox_board_rev_id_sec_vs_univox_board_rev_id_fbd_1                                          // DEPRECATED
UNREACHABLE:FS_FAILURE_fs_check_wifi_radio1_mac_address_sec_vs_wifi_radio1_mac_address_hw__if_radio_1_exists_1                // MAC cloning is not blocked
UNREACHABLE:FS_FAILURE_fs_check_wifi_radio1_mac_address_sec_vs_hwaddr_bi__if_radio_1_exists_1                                 // not checked / cloning allowed
UNREACHABLE:FS_FAILURE_fs_check_wifi_radio2_mac_address_sec_vs_wifi_radio2_mac_address_hw__if_radio_2_exists_1                // MAC cloning is not blocked
UNREACHABLE:FS_FAILURE_fs_read_wifi_radio1_mac_rev_id_hw_3                                                                    // DEPRECATED
UNREACHABLE:FS_FAILURE_fs_write_to_mmapped_file_1                                                                             // DEPRECATED
UNREACHABLE:FS_FAILURE_fs_acquire_file_based_lock_1                                                                           // Failure of open call for lock file - non-simulation code (can't really happen unless on-target compound failure
UNREACHABLE:FS_FAILURE_fs_acquire_file_based_lock_2                                                                           // Cascade error message from fs_acquire_file_based_lock failure
UNREACHABLE:FS_FAILURE_fs_check_esn_signature_1                                                                               // CODE SANITY CHECK - Blowfish code failure
UNREACHABLE:FS_FAILURE_fs_check_eth0_mac_address_sec_vs_eth0_mac_address_fbd_1                                                // Not presently checked by any product classes
UNREACHABLE:FS_FAILURE_fs_check_eth1_mac_address_sec_vs_eth1_mac_address_fbd_1                                                // Not presently checked by any product classes
UNREACHABLE:FS_FAILURE_fs_read_wifi_radio2_mac_rev_id_hw_2                                                                    // find_pci_bar0 call failed
UNREACHABLE:FS_FAILURE_fs_read_config_1                                                                                       // CODE SANITY CHECK - read size > destination buffer size
UNREACHABLE:FS_FAILURE_fs_read_config_2                                                                                       // CODE SANITY CHECK - EEPROM read > max EEPROM size constant
UNREACHABLE:FS_FAILURE_fs_read_config_3                                                                                       // CODE SANITY CHECK - kernel code - read more config data than available.
UNREACHABLE:FS_FAILURE_fs_read_config_4                                                                                       // CODE SANITY CHECK - read length > destination length
UNREACHABLE:FS_FAILURE_fs_read_config_5                                                                                       // CODE SANITY CHECK - read length > destination length
UNREACHABLE:FS_FAILURE_fs_read_config_6                                                                                       // CODE SANITY CHECK - read length > destination length
UNREACHABLE:FS_FAILURE_fs_read_config_7                                                                                       // CODE SANITY CHECK - read length > destination length
UNREACHABLE:FS_FAILURE_fs_read_config_8                                                                                       // CODE SANITY CHECK - read length > max EEPROM size
UNREACHABLE:FS_FAILURE_fs_read_file_into_buffer_1                                                                             // CODE SANITY CHECK - destination pointer is NULL
UNREACHABLE:FS_FAILURE_fs_read_file_into_buffer_10                                                                            // CODE SANITY CHECK - destination pointer is NULL
UNREACHABLE:FS_FAILURE_fs_read_file_into_buffer_11                                                                            // CODE SANITY CHECK - length pointer is NULL
UNREACHABLE:FS_FAILURE_fs_read_file_into_buffer_12                                                                            // CODE SANITY CHECK - pathame is NULL
UNREACHABLE:FS_FAILURE_fs_read_file_into_buffer_14                                                                            // file read from kernel VFS failed
UNREACHABLE:FS_FAILURE_fs_read_file_into_buffer_2                                                                             // CODE SANITY CHECK - length pointer is NULL
UNREACHABLE:FS_FAILURE_fs_read_file_into_buffer_3                                                                             // CODE SANITY CHECK - pathame is NULL
UNREACHABLE:FS_FAILURE_fs_read_file_into_buffer_5                                                                             // fseek to end failed
UNREACHABLE:FS_FAILURE_fs_read_file_into_buffer_6                                                                             // ftell after seek to end returned < 0
UNREACHABLE:FS_FAILURE_fs_read_file_into_buffer_7                                                                             // fseek to 0 failed
UNREACHABLE:FS_FAILURE_fs_read_file_into_buffer_8                                                                             // CODE SANITY CHECK - size to read exceeds destination buffer size
UNREACHABLE:FS_FAILURE_fs_read_file_into_buffer_9                                                                             // CODE SANITY CHECK - read returned different number of bytes from expected
UNREACHABLE:FS_FAILURE_fs_read_flash_uid_hw_1                                                                                 // CODE SANITY CHECK - destination size < max UID size
UNREACHABLE:FS_FAILURE_fs_read_from_mmapped_file_1                                                                            // CODE SANITY CHECK - Read size > destination buffer size
UNREACHABLE:FS_FAILURE_fs_read_from_mmapped_file_2                                                                            // CODE SANITY CHECK - Area to be read exceeds bounds of file
UNREACHABLE:FS_FAILURE_fs_read_from_mmapped_file_4                                                                            // mmap call failed
UNREACHABLE:FS_FAILURE_fs_read_ini_key_3                                                                                      // CODE SANITY CHECK - memory allocation failure
UNREACHABLE:FS_FAILURE_fs_read_ini_key_4                                                                                      // CODE SANITY CHECK - LOOKING for key that is too long (i.e. bad request in the code)
UNREACHABLE:FS_FAILURE_fs_read_mac_address_hw_1                                                                               // socket call failure creating DGRAM socket
UNREACHABLE:FS_FAILURE_fs_read_mac_address_hw_2                                                                               // CODE SANITY CHECK - Interface name too long or unterminated
UNREACHABLE:FS_FAILURE_fs_read_mem_1                                                                                          // CODE SANITY CHECK - read size > dst buffer size
UNREACHABLE:FS_FAILURE_fs_read_mem_2                                                                                          // CODE SANITY CHECK - read size > dst buffer size
UNREACHABLE:FS_FAILURE_fs_read_mem_3                                                                                          // ioremap_nocache call failure
UNREACHABLE:FS_FAILURE_fs_read_mem_4                                                                                          // CODE SANITY CHECK - read size > dst buffer size
UNREACHABLE:FS_FAILURE_fs_read_mem_5                                                                                          // CODE SANITY CHECK - read size > dst buffer size
UNREACHABLE:FS_FAILURE_fs_get_config_offset_pcba_sec_1                                                                        // CODE SANITY CHECK - fs_get_config_offset_pcba_sec on EEPROM format rev1 for formats without PCBA in that rev.
UNREACHABLE:FS_FAILURE_fs_get_config_offset_qr_code_1                                                                         // Unsupported security data format, but we don't get here in that case.
UNREACHABLE:FS_FAILURE_fs_release_file_based_lock_1                                                                           // If fs_release_file_based_lock returns non-zero, but hard-coded to zero.
UNREACHABLE:FS_FAILURE_fs_check_ubnt_signature_2                                                                              // Low memory error.  If loading RSA key from file were enabled, also could be read failure. (can't really happen unless on-target compound failure
UNREACHABLE:FS_FAILURE_fs_check_ubnt_signature_3                                                                              // Low memory error.  If loading RSA key from file were enabled, also could be read failure. (can't really happen unless on-target compound failure
UNREACHABLE:FS_FAILURE_fs_save_buffer_to_file_1                                                                               // CODE SANITY CHECK - NULL buffer arg
UNREACHABLE:FS_FAILURE_fs_save_buffer_to_file_2                                                                               // CODE SANITY CHECK - NULL pathname
UNREACHABLE:FS_FAILURE_fs_save_buffer_to_file_3                                                                               // fs_open call failed (fs_open does not report error
UNREACHABLE:FS_FAILURE_fs_save_buffer_to_file_4                                                                               // fwrite call failure
UNREACHABLE:FS_FAILURE_fs_save_buffer_to_file_5                                                                               // CODE SANITY CHECK - NULL buffer
UNREACHABLE:FS_FAILURE_fs_save_buffer_to_file_6                                                                               // CODE SANITY CHECK - NULL pathname
UNREACHABLE:FS_FAILURE_fs_save_buffer_to_file_7                                                                               // _fs_file_open failure
UNREACHABLE:FS_FAILURE_fs_save_buffer_to_file_8                                                                               // _fs_file_write failure
UNREACHABLE:FS_FAILURE_fs_strip_quotes_1                                                                                      // CODE SANITY CHECK - Unterminated input to fs_strip_quotes
UNREACHABLE:FS_FAILURE_fs_write_config_1                                                                                      // CODE SANITY CHECK - Try to write more bytes to EEPROM than EEPROM max size
UNREACHABLE:FS_FAILURE_fs_write_config_2                                                                                      // CODE SANITY CHECK - EEPROM read would go beyond size of EEPROM read
UNREACHABLE:FS_FAILURE_fs_write_config_3                                                                                      // CASCADE - fs_save_buffer_to_file failed.
UNREACHABLE:FS_FAILURE_fs_write_mem_1                                                                                         // Kernel fail, ioremap_nocache returns NULL (can't really happen unless on-target compound failure
UNREACHABLE:FS_FAILURE_fs_write_to_mmapped_file_2                                                                             // CODE SANITY CHECK - Read attempted outside memory mapped area
UNREACHABLE:FS_FAILURE_fs_write_to_mmapped_file_3                                                                             // open call failure (can't really happen unless on-target compound failure
UNREACHABLE:FS_FAILURE_fs_write_to_mmapped_file_4                                                                             // mmap call failure (can't really happen unless on-target compound failure
UNREACHABLE:FS_FAILURE_fs_check_wifi_radio1_mac_address_sec_vs_hwaddr_bi__if_radio_1_exists_1                                 // after code changes, this error number is not currently in use
UNREACHABLE:FS_FAILURE_fs_check_wifi_radio1_mac_address_sec_vs_wifi_radio1_mac_address_hw__if_radio_1_exists_1                // after code changes, this error number is not currently in use
UNREACHABLE:FS_FAILURE_fs_check_wifi_radio2_mac_address_sec_vs_wifi_radio2_mac_address_hw__if_radio_2_exists_1                // after code changes, this error number is not currently in use

#endif

#endif // #if SECURITY_ENABLE_DEBUG_OUTPUT
