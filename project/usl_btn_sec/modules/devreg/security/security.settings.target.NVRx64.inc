#ifdef UBNT_NVRx64

/* NB: We have custom handler for flash ID access on NVR box */
#define SECURITY_HAVE_DIRECT_BITBANG_SPI_FLASH_HARDWARE 0
#define SECURITY_HAVE_LINUX_SPI_DRIVER                  0
#define SECURITY_HAVE_SPI_FLASH_HARDWARE                0

#define SECURITY_IS_TARGET_BUILD                        1
#define SECURITY_READ_CONFIG_USES_READ_MEM              0
#define SECURITY_WRITE_CONFIG_USES_FILE                 0
#define SECURITY_ENABLE_TOUGHER_INI_VALIDATION          0 // Need sign off from product team before enabling

#endif // #ifdef UBNT_NVRx64
