#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_GM81xx) || SECURITY_ENABLE_SIMULATION)

__FS_FUNCTION_PREFER_INLINE void _fs_check_camera_eth_mac_rev_id_sec_vs_hw(void)                     { __fs_check_generic_sec_vs_hw(u_int32_t,camera_eth_mac_rev_id,GM81xx_eth_mac_rev_id); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_camera_ahb_rev_id_sec_vs_hw(void)                         { __fs_check_generic_sec_vs_hw(u_int32_t,camera_ahb_rev_id,GM81xx_ahb_rev_id); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_camera_gpio_summary_id_sec_vs_hw(void)                    { __fs_check_generic_sec_vs_hw(u_int32_t,camera_gpio_summary_id,GM81xx_gpio_summary_id); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_camera_i2c_controller_rev_id_sec_vs_hw(void)              { __fs_check_generic_sec_vs_hw(u_int32_t,camera_i2c_controller_rev_id,GM81xx_i2c_controller_rev_id); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_camera_int_controller_summary_id_sec_vs_hw(void)          { __fs_check_generic_sec_vs_hw(u_int32_t,camera_int_controller_summary_id,GM81xx_int_controller_summary_id); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_camera_sd_card_reader_rev_id_sec_vs_hw(void)              { __fs_check_generic_sec_vs_hw(u_int32_t,camera_sd_card_reader_rev_id,GM81xx_sd_card_reader_rev_id); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_camera_timer_summary_id_sec_vs_hw(void)                   { __fs_check_generic_sec_vs_hw(u_int32_t,camera_timer_summary_id,GM81xx_timer_summary_id); }

#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_GM81xx) || SECURITY_ENABLE_SIMULATION)
