#ifdef UBNT_MIPS_BCM4706

#define SECURITY_READ_CONFIG_USES_MMAP                  1
#define SECURITY_ENABLE_FS_LOCK                         1

#define SECURITY_HAVE_DIRECT_BITBANG_SPI_FLASH_HARDWARE 0
#define SECURITY_HAVE_LINUX_SPI_DRIVER                  0
#define SECURITY_HAVE_SPI_FLASH_HARDWARE                1
#define SECURITY_HAVE_PROPRIETARY_SPI_CONTROLLER        1
#define SECURITY_READ_JEDECID_UUID_FROM_UNIFIHAL	1

#define SECURITY_IS_TARGET_BUILD                        1

/* FIXME, need a base address and offset from JEDEC? */
#define BCM4706_FLASH_BASE_ADDR                         0x1c000000
#define BCM4706_FLASH_SIZE                              0x1000000
#define BCM4706_EEPROM_SIZE                             0x10000
#define BCM4706_NVRAM_SIZE                              0x10000

#define CONFIG_PHYSICAL_ADDRESS                         (BCM4706_FLASH_BASE_ADDR + BCM4706_FLASH_SIZE - BCM4706_NVRAM_SIZE - BCM4706_EEPROM_SIZE)

#define SECURITY_ENABLE_TOUGHER_INI_VALIDATION          0 // Need sign off from product team before enabling

#endif // #ifdef UBNT_MIPS_BCM4706
