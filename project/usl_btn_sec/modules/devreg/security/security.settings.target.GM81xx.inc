#ifdef UBNT_ARM_GM81xx

#define SECURITY_HAVE_DIRECT_BITBANG_SPI_FLASH_HARDWARE 1
#define SECURITY_HAVE_LINUX_SPI_DRIVER                  0
#define SECURITY_HAVE_SPI_FLASH_HARDWARE                1

#define SECURITY_IS_TARGET_BUILD                        1
#define SECURITY_READ_CONFIG_USES_MMAP                  1
#define SECURITY_ENABLE_TOUGHER_INI_VALIDATION          0 // Need sign off from product team before enabling

#endif // #ifdef UBNT_ARM_GM81xx
