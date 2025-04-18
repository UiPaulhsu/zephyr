#ifdef UBNT_ARM_AM18xx

#define SECURITY_HAVE_DIRECT_BITBANG_SPI_FLASH_HARDWARE 0
#define SECURITY_HAVE_LINUX_SPI_DRIVER                  1
#define SECURITY_HAVE_SPI_FLASH_HARDWARE                1

#define SECURITY_IS_TARGET_BUILD                        1
#define SECURITY_READ_CONFIG_USES_MMAP                  1
#define SECURITY_ENABLE_TOUGHER_INI_VALIDATION          0 // Need sign off from product team before enabling

// NEVER lock out
#undef SECURITY_ENABLE_LOCKOUT
#define SECURITY_ENABLE_LOCKOUT 0

// Enable temp file marker if not disabled explicitly by make
#ifndef SECURITY_ENABLE_TMPTAG
#define SECURITY_ENABLE_TMPTAG 1
#endif // #ifndef SECURITY_ENABLE_TMPTAG

// Enable /etc/version alteration if not disabled explicitly by make
#ifndef SECURITY_ENABLE_TAG_ETC_VERSION
#define SECURITY_ENABLE_TAG_ETC_VERSION 1
#endif // #ifndef SECURITY_ENABLE_TAG_ETC_VERSION

// Enable /etc/counterfeit tag file if not disabled explicitly by make
#ifndef SECURITY_ENABLE_TAG_ETC_COUNTERFEIT
#define SECURITY_ENABLE_TAG_ETC_COUNTERFEIT 1
#endif // #ifndef SECURITY_ENABLE_TAG_ETC_COUNTERFEIT

// Enable host name change if not disabled explicitly by make
#ifndef SECURITY_ENABLE_SET_HOSTNAME_TO_COUNTERFEIT
#define SECURITY_ENABLE_SET_HOSTNAME_TO_COUNTERFEIT 1
#endif // #ifndef SECURITY_ENABLE_SET_HOSTNAME_TO_COUNTERFEIT

// Enable domain name change if not disabled explicitly by make
#ifndef SECURITY_ENABLE_SET_DOMAINNAME_TO_COUNTERFEIT
#define SECURITY_ENABLE_SET_DOMAINNAME_TO_COUNTERFEIT 1
#endif // #ifndef SECURITY_ENABLE_SET_DOMAINNAME_TO_COUNTERFEIT

// NEVER allow crashing the kernel or calling process
#undef SECURITY_ENABLE_CRASHING
#define SECURITY_ENABLE_CRASHING 0

// NEVER disable forwarding of IPv4 on AF (allow management traffic, disable the RF forwarding only)
#undef SECURITY_ENABLE_DISABLE_IPv4_FORWARDING
#define SECURITY_ENABLE_DISABLE_IPv4_FORWARDING 0

// Enable the ratelimit marker
#ifndef SECURITY_ENABLE_SET_PRINTK_RATELIMIT_TO_666
#define SECURITY_ENABLE_SET_PRINTK_RATELIMIT_TO_666 1
#endif // #ifndef SECURITY_ENABLE_SET_PRINTK_RATELIMIT_TO_666

static inline __attribute__( ( always_inline ) ) u_int8_t _fs_spi_get_secure_flash_spi_bus_number(void) {
	return 1; // _FS_SPI_BUS1
}

static inline __attribute__( ( always_inline ) ) u_int8_t _fs_spi_get_secure_flash_chip_select(void) {
	return 8; // _FS_SPI_CS8
}

#endif // #ifdef UBNT_ARM_AM18xx


