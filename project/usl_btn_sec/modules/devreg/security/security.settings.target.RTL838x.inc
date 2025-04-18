#ifdef UBNT_MIPS_RTL838x

#define SECURITY_HAVE_DIRECT_BITBANG_SPI_FLASH_HARDWARE 0
#define SECURITY_HAVE_LINUX_SPI_DRIVER                  0
#define SECURITY_HAVE_SPI_FLASH_HARDWARE                0

#define SECURITY_IS_TARGET_BUILD                        1
#define SECURITY_READ_CONFIG_USES_READ_MEM              0
#ifdef UNIFI_LAYOUT
#define SECURITY_READ_CONFIG_USES_MMAP                  1
#endif
#define SECURITY_WRITE_CONFIG_USES_FILE                 0

#define SECURITY_ENABLE_TOUGHER_INI_VALIDATION          0 // Need sign off from product team before enabling

#endif // #ifdef UBNT_MIPS_RTL838x

