#ifdef UBNT_ARM_IPQ806x

#define SECURITY_HAVE_DIRECT_BITBANG_SPI_FLASH_HARDWARE 0
#define SECURITY_HAVE_LINUX_SPI_DRIVER                  0
#define SECURITY_HAVE_SPI_FLASH_HARDWARE                1
#define SECURITY_HAVE_PROPRIETARY_SPI_CONTROLLER        1
#define SECURITY_READ_JEDECID_UUID_FROM_UNIFIHAL	1

#define SECURITY_READ_CONFIG_USES_MMAP    1

#define SECURITY_IS_TARGET_BUILD                        1

#define SECURITY_ENABLE_TOUGHER_INI_VALIDATION          0 // Need sign off from product team before enabling

#if !defined(SECURITY_FLASH_HWREV)
    #define SECURITY_FLASH_HWREV SECURITY_FLASH_HWREV_7
#endif // #if !defined(SECURITY_FLASH_HWREV)

#define SECURITY_ENABLE_FS_LOCK                         0
#endif // #ifdef UBNT_ARM_IPQ806x

