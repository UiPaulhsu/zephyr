#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_GM81xx) || SECURITY_ENABLE_SIMULATION)

/*
Name    Bits    Register        Value
 APBR    23:0    0x920000c8      0x00010800
 MAC     23:0    0x92500034      0x00000700
 ISP     7:0     0x92300008      0x0F000010
 SDC     31:0    0x928000a0      0x00030401
 I2C     31:0    0x99600030      0x00011001
 GPIO    31:0    0x9940007c      0x00010700
 INTC    23:0    0x99500050      0x00010900
 TMR     31:0    0x9910003c      0x00010801
*/
#define GM81xx_APBR_ADDR ((uintptr_t)0x920000c8)
#define GM81xx_MAC_ADDR  ((uintptr_t)0x92500034)
#define GM81xx_ISP_ADDR  ((uintptr_t)0x92300008)
#define GM81xx_SDC_ADDR  ((uintptr_t)0x928000a0)
#define GM81xx_I2C_ADDR  ((uintptr_t)0x99600030)
#define GM81xx_GPIO_ADDR ((uintptr_t)0x9940007c)
#define GM81xx_INTC_ADDR ((uintptr_t)0x99500050)
#define GM81xx_TMR_ADDR  ((uintptr_t)0x9910003c)

#define GM81xx_APBR_MASK 0x00ffffff
#define GM81xx_MAC_MASK  0x00ffffff
#define GM81xx_SDC_MASK  0xffffffff
#define GM81xx_I2C_MASK  0xffffffff
#define GM81xx_GPIO_MASK 0xffffffff
#define GM81xx_INTC_MASK 0x00ffffff
#define GM81xx_TMR_MASK  0xffffffff

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_GM81xx_ahb_rev_id_hw(void)                  { return fs_read_mem32(GM81xx_APBR_ADDR ) & GM81xx_APBR_MASK; }
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_GM81xx_eth_mac_rev_id_hw(void)              { return fs_read_mem32(GM81xx_MAC_ADDR  ) & GM81xx_MAC_MASK ; }
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_GM81xx_gpio_summary_id_hw(void)             { return fs_read_mem32(GM81xx_GPIO_ADDR ) & GM81xx_GPIO_MASK; }
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_GM81xx_i2c_controller_rev_id_hw(void)       { return fs_read_mem32(GM81xx_I2C_ADDR  ) & GM81xx_I2C_MASK ; }
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_GM81xx_int_controller_summary_id_hw(void)   { return fs_read_mem32(GM81xx_INTC_ADDR ) & GM81xx_INTC_MASK; }
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_GM81xx_sd_card_reader_rev_id_hw(void)       { return fs_read_mem32(GM81xx_SDC_ADDR  ) & GM81xx_SDC_MASK ; }
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_GM81xx_timer_summary_id_hw(void)            { return fs_read_mem32(GM81xx_TMR_ADDR  ) & GM81xx_TMR_MASK ; }

#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_GM81xx) || SECURITY_ENABLE_SIMULATION)

