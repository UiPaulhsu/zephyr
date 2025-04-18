#ifdef UBNT_MIPS_QCA851x

#define SECURITY_HAVE_DIRECT_BITBANG_SPI_FLASH_HARDWARE 1
#define SECURITY_HAVE_LINUX_SPI_DRIVER                  0
#define SECURITY_HAVE_SPI_FLASH_HARDWARE                1
#define SECURITY_ENABLE_TOUGHER_INI_VALIDATION          0 // Need sign off from product team before enabling

#define SECURITY_IS_TARGET_BUILD                        1
#define CONFIG_PHYSICAL_ADDRESS                         0x19ff0000

#ifdef __KERNEL__
	#define SECURITY_READ_CONFIG_USES_DIRECT_MEMORY_ACCESS 1
#else
	#define SECURITY_READ_CONFIG_USES_READ_MEM             1
#endif

#ifdef UBNT_SWITCH_BUILD
	#define SECURITY_ENABLE_GRANDFATHER_AR7240_AR7241 0
#endif // #ifdef UBNT_SWITCH_BUILD

#endif // #ifdef UBNT_MIPS_QCA851x
