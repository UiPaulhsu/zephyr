#ifdef UBNT_ARM_MT8117

#define SECURITY_HAVE_DIRECT_BITBANG_SPI_FLASH_HARDWARE 0
#define SECURITY_HAVE_LINUX_SPI_DRIVER                  1
#define SECURITY_HAVE_SPI_FLASH_HARDWARE                1

#define SECURITY_IS_TARGET_BUILD                        1
#define SECURITY_READ_CONFIG_USES_MMAP                  1
#define SECURITY_ENABLE_FS_LOCK                         1

#undef  SECURITY_FLASH_HWREV
#define SECURITY_FLASH_HWREV                            SECURITY_FLASH_HWREV_4
#define SECURITY_ENABLE_TOUGHER_INI_VALIDATION          0 // Need sign off from product team before enabling

static inline __attribute__( ( always_inline ) ) u_int8_t _fs_spi_get_secure_flash_spi_bus_number(void) {
	return 0; // _FS_SPI_BUS0
}

static inline __attribute__( ( always_inline ) ) u_int8_t _fs_spi_get_secure_flash_chip_select(void) {
	return 0; // _FS_SPI_CS0
}

#endif // #ifdef UBNT_ARM_MT8117
