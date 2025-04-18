#ifdef UBNT_MIPS_CN50xx

#define SECURITY_HAVE_DIRECT_BITBANG_SPI_FLASH_HARDWARE 0
#define SECURITY_HAVE_SPI_FLASH_HARDWARE                1
#define SECURITY_HAVE_LINUX_SPI_DRIVER                  0

#define SECURITY_IS_TARGET_BUILD                        1
#define SECURITY_READ_CONFIG_USES_MMAP                  1
#define SECURITY_ENABLE_FS_LOCK                         1
#define SECURITY_ENABLE_TOUGHER_INI_VALIDATION          0 // Need sign off from product team before enabling

#undef SECURITY_FLASH_HWREV
#define SECURITY_FLASH_HWREV                            SECURITY_FLASH_HWREV_6

static inline __attribute__( ( always_inline ) ) u_int8_t _fs_spi_get_secure_flash_spi_bus_number(void) {
	return 0; // _FS_SPI_BUS0
}

static inline __attribute__( ( always_inline ) ) u_int8_t _fs_spi_get_secure_flash_chip_select(void) {
	return 0; // _FS_SPI_CS0
}

#ifdef __KERNEL__
/* This assumes MIPS N64 ABI */
static inline uint64_t CN50xx_read_csr(uint64_t addr) {
	return *((uint64_t *) addr);
}

static inline void CN50xx_write_csr(uint64_t addr, uint64_t val) {
	*((uint64_t *) addr) = val;
}
#else  /* !__KERNEL__ */
/* This assumes MIPS O32 ABI */
#include <sys/sysmips.h>

static int _sysmips_init = 0;

static inline void init_sysmips(void) {
	if (_sysmips_init) {
		return;
	}

	_sysmips_init = 1;
	sysmips(2011, getpid(), 3, 0); /* return ignored */
}

static inline uint64_t CN50xx_read_csr(uint64_t addr) {
	uint32_t csr_addrh = addr >> 32;
	uint32_t csr_addrl = addr;
	uint32_t valh;
	uint32_t vall;

	init_sysmips();

	asm volatile (
		".set push\n"
		".set mips64\n"
		"dsll   %[valh], %[csrh], 32\n"
		"dsll   %[vall], %[csrl], 32\n"
		"dsrl   %[vall], %[vall], 32\n"
		"or     %[valh], %[valh], %[vall]\n"
		"ld     %[vall], 0(%[valh])\n"
		"dsrl   %[valh], %[vall], 32\n"
		"sll    %[vall], 0\n"
		"sll    %[valh], 0\n"
		".set pop\n"
		: [valh] "=&r" (valh), [vall] "=&r" (vall)
		: [csrh] "r" (csr_addrh), [csrl] "r" (csr_addrl)
	);
	return ((uint64_t) valh << 32) | vall;
}

static inline void CN50xx_write_csr(uint64_t addr, uint64_t val) {
	uint32_t csr_addrh = addr >> 32;
	uint32_t csr_addrl = addr;
	uint32_t valh = val >> 32;
	uint32_t vall = val;
	uint32_t tmp1;
	uint32_t tmp2;
	uint32_t tmp3;

	init_sysmips();

	asm volatile (
		".set push\n"
		".set mips64\n"
		"dsll   %[tmp1], %[valh], 32\n"
		"dsll   %[tmp2], %[csrh], 32\n"
		"dsll   %[tmp3], %[vall], 32\n"
		"dsrl   %[tmp3], %[tmp3], 32\n"
		"or     %[tmp1], %[tmp1], %[tmp3]\n"
		"dsll   %[tmp3], %[csrl], 32\n"
		"dsrl   %[tmp3], %[tmp3], 32\n"
		"or     %[tmp2], %[tmp2], %[tmp3]\n"
		"sd     %[tmp1], 0(%[tmp2])\n"
		".set pop\n"
		: [tmp1] "=&r" (tmp1), [tmp2] "=&r" (tmp2), [tmp3] "=&r" (tmp3)
		: [valh] "r" (valh), [vall] "r" (vall),
		[csrh] "r" (csr_addrh), [csrl] "r" (csr_addrl)
	);
}
#endif /* __KERNEL__ */

#endif // #ifdef UBNT_MIPS_CN50xx
