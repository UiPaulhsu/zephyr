#if SECURITY_ENABLE_SIMULATION
	#define SECURITY_IS_TARGET_BUILD                    1
	#define SECURITY_READ_CONFIG_USES_MMAP              1
	#define SECURITY_HAVE_LINUX_SPI_DRIVER              0
	#undef  SECURITY_FLASH_HWREV
	#define SECURITY_FLASH_HWREV SECURITY_FLASH_HWREV_MAX // NB: Always include the latest hardware support when building simulation build.
	#define SECURITY_ENABLE_TOUGHER_INI_VALIDATION      1
#endif // #if SECURITY_ENABLE_SIMULATION



