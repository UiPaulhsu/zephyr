#if SECURITY_HAVE_LINUX_SPI_DRIVER

#define _FS_SPI_BUS0      0
#define _FS_SPI_BUS1      1

#define _FS_SPI_CS0       0
#define _FS_SPI_CS1       1
#define _FS_SPI_CS2       2
#define _FS_SPI_CS3       3
#define _FS_SPI_CS4       4
#define _FS_SPI_CS5       5
#define _FS_SPI_CS6       6
#define _FS_SPI_CS7       7
#define _FS_SPI_CS8       8

#if !defined( UBNT_ARM_BCM5334x ) && !defined( UBNT_ARM_BCM5341x ) && !defined( UBNT_ARM_BCM5616x )
u_int32_t __invalid_size_argument_for_IOC;
#endif

#ifndef __KERNEL__
typedef struct fsctx {
	int   spidev_fd;
} fsctx_t;
#else 
typedef struct fsctx {
	struct spi_master* p_master;
	struct device*     p_slave_dev;
	struct spi_device* p_spi;
} fsctx_t;
#endif // #ifndef __KERNEL__

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void _fs_spi_disable_access_and_chip_select(__ATTRIB_UNUSED fsctx_t* p_ctx, __ATTRIB_UNUSED u_int8_t chip_select) {}
__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void _fs_spi_enable_access_and_chip_select(__ATTRIB_UNUSED fsctx_t* p_ctx, __ATTRIB_UNUSED u_int8_t chip_select) {}
__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE int  _fs_spi_check_preempted(__ATTRIB_UNUSED fsctx_t* p_ctx, __ATTRIB_UNUSED u_int8_t chip_select) { return 0;}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_write_then_read(fsctx_t* p_ctx, __ATTRIB_UNUSED u_int8_t chip_select, u_int8_t* tx, size_t tx_len, u_int8_t* rx, size_t rx_len) {
#ifdef __KERNEL__
/////	__FS_LOCAL_STATIC_OPTION int fsv_t1;
/////	fsv_t1 = spi_write_then_read(p_ctx->p_spi, tx, tx_len, rx, rx_len);
/////	if (fsv_t1 < 0) {
/////		fs_debug_printf("Error sending spi commands, %d.\n", fsv_t1);
/////		return
/////	}
#else  // #ifdef __KERNEL__
	__FS_LOCAL_STATIC_OPTION struct spi_ioc_transfer fsv_t1[2];
	__FS_LOCAL_STATIC_OPTION size_t fsv_t2;
	__FS_LOCAL_STATIC_OPTION size_t fsv_t3;
	__FS_LOCAL_STATIC_OPTION int    fsv_t4;

	// Re-initialize static stack data on every pass
	memset(&fsv_t1, 0, sizeof fsv_t1);
	fsv_t2 = 0;
	fsv_t3 = 0;	// num transfers
	fsv_t4 = 0;
	fsv_t1[0].delay_usecs   = fsv_t1[1].delay_usecs   = 2;		  // 2 ns should always be OK
	fsv_t1[0].speed_hz      = fsv_t1[1].speed_hz      = 1000000;  // 1MHz ok for this 
	fsv_t1[0].bits_per_word = fsv_t1[1].bits_per_word = 8;

	if (tx_len) {
		fsv_t1[fsv_t3].len    = tx_len;
		fsv_t1[fsv_t3].tx_buf = (uintptr_t)tx;
		fsv_t3++;
	}
	if (rx_len) {
		memset(rx,0x0,rx_len);
		fsv_t1[fsv_t3].len    = rx_len;
		fsv_t1[fsv_t3].rx_buf = (uintptr_t)rx;
		fsv_t3++;
	}
	if (tx_len == 0 && rx_len == 0) {
		fs_debug_printf( "SPI transfer request with no transmit or receive bytes!\n");
		return;
	}
	fsv_t4 = ioctl(p_ctx->spidev_fd, SPI_IOC_MESSAGE(fsv_t3), &fsv_t1);
	if (fsv_t4 < 0) {
		fs_debug_printf("Error sending spi commands, %d.\n", fsv_t4);
		return;
	}
#endif // #ifdef __KERNEL__
}

__FS_FUNCTION_PREFER_INLINE void fs_init_fsctx(fsctx_t* p_ctx) {
	__FS_LOCAL_STATIC_OPTION char fsv_t1[128];
	if (p_ctx == NULL) {
		return;
	}
	memset( fsv_t1, 0, sizeof fsv_t1 );
	memset( p_ctx, 0, sizeof(fsctx_t) );
#ifdef __KERNEL__
/////	p_ctx->p_master = spi_busnum_to_master(_fs_spi_get_secure_flash_spi_bus_number());
/////	if (NULL == p_ctx->p_master) {
/////		fs_debug_printf( "Failed to find SPI master.\n");
/////		return;
/////	}
/////// Increment reference counter
/////	spi_master_get(p_ctx->p_master);
/////// Build the device name of the slave we want to access
/////	snprintf(fsv_t1, sizeof fsv_t1, "%s.%u", dev_name(&p_ctx->p_master->dev), _fs_spi_get_secure_flash_chip_select());
/////// Find the device for the SPI slave device
/////	p_ctx->p_slave_dev = bus_find_device_by_name(&spi_bus_type, NULL, fsv_t1);
/////	if (NULL == p_ctx->p_slave_dev) {
/////		fs_debug_printf( "Failed to find SPI slave device, '%s'.\n", fsv_t1);
/////		goto master_put;
/////	}
/////// Lookup the SPI device for the slave
/////	p_ctx->p_spi = to_spi_device(p_ctx->p_slave_dev);
/////	if (NULL == p_ctx->p_spi) {
/////		fs_debug_printf( "Failed to convert SPI slave device to spi_device*, '%s'.\n", fsv_t1);
/////		goto master_put;
/////	}
/////// Reference counter bump
/////	spi_dev_get(p_ctx->p_spi);
/////	master_put:
#else // #ifdef __KERNEL__
// Build the device name of the slave we want to access
	snprintf(fsv_t1, sizeof fsv_t1, "/dev/spidev%u.%u", _fs_spi_get_secure_flash_spi_bus_number(), _fs_spi_get_secure_flash_chip_select());
	p_ctx->spidev_fd = open(fsv_t1, O_RDWR);
	if (p_ctx->spidev_fd < 0) {
		fs_debug_printf( "Failed to open SPI slave device, '%s'.  Error %d.\n", fsv_t1, p_ctx->spidev_fd);
		return;
	}
#endif // #ifdef __KERNEL__
}


__FS_FUNCTION_PREFER_INLINE void fs_close_fsctx(fsctx_t* p_ctx) {
	if (p_ctx == NULL) {
		return;
	}
#ifdef __KERNEL__
/////	if (p_ctx->p_spi != NULL) {
/////		spi_dev_put(p_ctx->p_spi);
/////		p_ctx->p_spi = NULL;
/////	}
/////	if (p_ctx->p_master != NULL) {
/////		spi_master_put(p_ctx->p_master);
/////		p_ctx->p_master = NULL;
/////	}
#else // #ifdef __KERNEL__
	if (p_ctx->spidev_fd != -1) {
		close(p_ctx->spidev_fd);
		p_ctx->spidev_fd = -1;
	}
#endif // #ifdef __KERNEL__
}

#endif // #if SECURITY_HAVE_LINUX_SPI_DRIVER

