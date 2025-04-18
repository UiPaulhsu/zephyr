#ifdef UBNT_ARM_BCM5341x

#define SECURITY_HAVE_DIRECT_BITBANG_SPI_FLASH_HARDWARE 0
#define SECURITY_HAVE_LINUX_SPI_DRIVER                  0
#define SECURITY_HAVE_SPI_FLASH_HARDWARE                0
#define SECURITY_HAVE_PROPRIETARY_SPI_CONTROLLER        1

#define SECURITY_IS_TARGET_BUILD                        1
#define SECURITY_READ_CONFIG_USES_MMAP                  1
#define SECURITY_ENABLE_FS_LOCK                         0
#define SECURITY_ENABLE_TOUGHER_INI_VALIDATION          0 // Need sign off from product team before enabling

/* platform-specific SPI implementation is used so HWREV isn't */
#undef  SECURITY_FLASH_HWREV
#define SECURITY_FLASH_HWREV                            SECURITY_FLASH_HWREV_3

static inline __attribute__( ( always_inline ) ) u_int8_t _fs_spi_get_secure_flash_spi_bus_number(void) {
	return 0; // _FS_SPI_BUS0
}

static inline __attribute__( ( always_inline ) ) u_int8_t _fs_spi_get_secure_flash_chip_select(void) {
	return 0; // _FS_SPI_CS0
}

#ifndef LUBDE_MAGIC
#define LUBDE_MAGIC 'L'
#endif

#define LUBDE_IPROC_CPU_REV_ID _IO(LUBDE_MAGIC, 29)
#define LUBDE_IPROC_FLASH_ID   _IO(LUBDE_MAGIC, 30)
#define LUBDE_IPROC_FLASH_UID  _IO(LUBDE_MAGIC, 31)

#ifndef __KERNEL__

/* this typedef is from linux-user-bde.h with
 * !SAL_BDE_32BIT_USER_64BIT_KERNEL && !PTRS_ARE_64BITS
 */
typedef uint32_t __bde_kernel_addr_t;

/* userspace */
typedef struct  {
	unsigned int dev;
	unsigned int rc;
	unsigned int d0;
	unsigned int d1;
	unsigned int d2;
	unsigned int d3;
	__bde_kernel_addr_t p0;
	union {
		unsigned int dw[2];
		unsigned char buf[64];
	} dx;
} __bde_ioctl_t;

static inline void __ioctl(unsigned int command, __bde_ioctl_t *pio)
{
	size_t i;
	unsigned char c;
	int fd = open("/dev/linux-user-bde",
		      O_RDWR | O_SYNC | O_DSYNC | O_RSYNC);

	if (fd < 0) {
		pio->rc = -1;
		return;
	}
	pio->d2 = rand() ^ (rand() << 16);
	if (ioctl(fd, command, pio) != 0) {
		pio->rc = -1;
	}
	close(fd);
	pio->d1 ^= pio->d2;
	c = pio->d3;
	for (i = 0; i < sizeof(pio->dx.buf); i++) {
		pio->dx.buf[i] ^= c;
	}
}
#endif /* ifndef __KERNEL__ */

#endif // #ifdef UBNT_ARM_BCM5341x
