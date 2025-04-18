#ifdef UBNT_SUPPORT_CLASS_CAMERA
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_camera_eth_mac_rev_id_sec(void)                { return fs_read_config_be32toh(FLASH_SECURITY_OFFSET_CAMERA_ETH_MAC_REV_ID            ); }
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_camera_ahb_rev_id_sec(void)                    { return fs_read_config_be32toh(FLASH_SECURITY_OFFSET_CAMERA_AHB_REV_ID                ); }
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_camera_gpio_summary_id_sec(void)               { return fs_read_config_be32toh(FLASH_SECURITY_OFFSET_CAMERA_GPIO_SUMMARY_ID           ); }
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_camera_i2c_controller_rev_id_sec(void)         { return fs_read_config_be32toh(FLASH_SECURITY_OFFSET_CAMERA_I2C_CONTROLLER_REV_ID     ); }
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_camera_int_controller_summary_id_sec(void)     { return fs_read_config_be32toh(FLASH_SECURITY_OFFSET_CAMERA_INT_CONTROLLER_SUMMARY_ID ); }
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_camera_sd_card_reader_rev_id_sec(void)         { return fs_read_config_be32toh(FLASH_SECURITY_OFFSET_CAMERA_SD_CARD_READER_REV_ID     ); }
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_camera_timer_summary_id_sec(void)              { return fs_read_config_be32toh(FLASH_SECURITY_OFFSET_CAMERA_TIMER_SUMMARY_ID          ); }
#endif // #ifdef UBNT_SUPPORT_CLASS_CAMERA

