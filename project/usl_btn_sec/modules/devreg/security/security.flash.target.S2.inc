#ifdef UBNT_ARM_S2

typedef struct fsctx {
#ifndef __KERNEL__
	int   devmem_fd;
	void* devmem_mmap_spi;
	void* devmem_mmap_ssi;
#else // #ifndef __KERNEL__
	volatile void __iomem * iomapping_spi;
	volatile void __iomem * iomapping_ssi;
#endif // #ifndef __KERNEL__
} fsctx_t;

#if 0
#define _FS_SPI_BASE            0x7000e000  /* GPIO2 base */
#define _FS_SPI_SIZE            0x1000
#define _FS_SSI_BASE            0x7000f000  /* SSI2 base */
#define _FS_SSI_SIZE            0x1000
#define _FS_SSI_SSIENR          (_FS_SSI_BASE + 0x08)
#define _FS_GPIO_DATA           (_FS_SPI_BASE + 0x00)
#define _FS_GPIO_DIRECTION      (_FS_SPI_BASE + 0x04)
#define _FS_GPIO_AFSEL          (_FS_SPI_BASE + 0x18)
#define _FS_GPIO_MASK           (_FS_SPI_BASE + 0x28)
#define _FS_GPIO_ENABLE         (_FS_SPI_BASE + 0x2c)
#define _FS_GPIO_DATA_REG(v)    (v-64)
#define _FS_SPI_CLK_LINE        _FS_GPIO_DATA_REG(88)  /* GPIO88 -- GPIO2_DATA[24] */
#define _FS_SPI_TX_LINE         _FS_GPIO_DATA_REG(89)  /* GPIO89 -- GPIO2_DATA[25] */
#define _FS_SPI_RX_LINE         _FS_GPIO_DATA_REG(90)  /* GPIO90 -- GPIO2_DATA[26] */
#define _FS_SPI_FSO_LINE        _FS_GPIO_DATA_REG(91)  /* GPIO91 -- GPIO2_DATA[27] */
#define _FS_SPI_FSO0_LINE       _FS_GPIO_DATA_REG(91)  /* GPIO91 -- GPIO2_DATA[27] */
#else
#define _FS_SPI_BASE            0x70009000  /* GPIO0 base */
#define _FS_SPI_SIZE            0x1000
#define _FS_SSI_BASE            0x70002000  /* SSI base */
#define _FS_SSI_SIZE            0x1000
#define _FS_SSI_SSIENR          (_FS_SSI_BASE + 0x08)
#define _FS_GPIO_DATA           (_FS_SPI_BASE + 0x00)
#define _FS_GPIO_DIRECTION      (_FS_SPI_BASE + 0x04)
#define _FS_GPIO_AFSEL          (_FS_SPI_BASE + 0x18)
#define _FS_GPIO_MASK           (_FS_SPI_BASE + 0x28)
#define _FS_GPIO_ENABLE         (_FS_SPI_BASE + 0x2c)
#define _FS_GPIO_DATA_REG(v)    (v)
#define _FS_SPI_CLK_LINE        _FS_GPIO_DATA_REG(2)  /* GPIO2 -- GPIO0_DATA[2] */
#define _FS_SPI_TX_LINE         _FS_GPIO_DATA_REG(3)  /* GPIO3 -- GPIO0_DATA[3] */
#define _FS_SPI_RX_LINE         _FS_GPIO_DATA_REG(4)  /* GPIO4 -- GPIO0_DATA[4] */
#define _FS_SPI_FSO_LINE        _FS_GPIO_DATA_REG(6)  /* GPIO5 -- GPIO0_DATA[5] */
#define _FS_SPI_FSO0_LINE       _FS_GPIO_DATA_REG(5)  /* GPIO6 -- GPIO0_DATA[6] */
#endif

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE u_int8_t _fs_spi_get_secure_flash_chip_select(void) {
    return 0; /* FS0 */
}

__FS_FUNCTION_PREFER_INLINE uintptr_t _fs_spi_get_spi_register_address(fsctx_t* p_ctx, uintptr_t physical_address) {
#ifndef __KERNEL__
	return (uintptr_t)(((u_int8_t*)(p_ctx->devmem_mmap_spi)) + (physical_address - _FS_SPI_BASE));
#else // #ifndef __KERNEL__
	return (uintptr_t)(p_ctx->iomapping_spi + (physical_address - _FS_SPI_BASE));
#endif // #ifndef __KERNEL__
}

__FS_FUNCTION_PREFER_INLINE uintptr_t _fs_spi_get_ssi_register_address(fsctx_t* p_ctx, uintptr_t physical_address) {
#ifndef __KERNEL__
    return (uintptr_t)(((u_int8_t*)(p_ctx->devmem_mmap_ssi)) + (physical_address - _FS_SSI_BASE));
#else // #ifndef __KERNEL__
    return (uintptr_t)(p_ctx->iomapping_ssi + (physical_address - _FS_SSI_BASE));
#endif // #ifndef __KERNEL__
}

__FS_FUNCTION_PREFER_INLINE fs_spi_register_t _fs_spi_ssi_register_read(fsctx_t* p_ctx, uintptr_t physical_address) {
	return ( *( (volatile fs_spi_register_t __force *)_fs_spi_get_ssi_register_address(p_ctx, physical_address) ) );
}

__FS_FUNCTION_PREFER_INLINE fs_spi_register_t _fs_spi_register_read(fsctx_t* p_ctx, uintptr_t physical_address) {
	return ( *( (volatile fs_spi_register_t __force *)_fs_spi_get_spi_register_address(p_ctx, physical_address) ) );
}

__FS_FUNCTION_PREFER_INLINE fs_spi_register_t _fs_spi_register_write_nf(fsctx_t* p_ctx, uintptr_t physical_address, fs_spi_register_t value) {
	return ( *( (volatile fs_spi_register_t __force *)_fs_spi_get_spi_register_address(p_ctx, physical_address) ) = (value) );
}

__FS_FUNCTION_PREFER_INLINE fs_spi_register_t _fs_spi_register_write(fsctx_t* p_ctx, uintptr_t physical_address, fs_spi_register_t value) {
	_fs_spi_register_write_nf(p_ctx, physical_address, value);
	return _fs_spi_register_read(p_ctx, physical_address);
}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_register_set_bits(fsctx_t* p_ctx, uintptr_t physical_address, fs_spi_register_t bits) {
	_fs_spi_register_write_nf(p_ctx, (physical_address), (_fs_spi_register_read(p_ctx, (physical_address)) | (bits)));
	_fs_spi_register_read(p_ctx, (physical_address));
}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_register_clear_bits(fsctx_t* p_ctx, uintptr_t physical_address, fs_spi_register_t bits) {
    _fs_spi_register_write_nf(p_ctx, (physical_address), (_fs_spi_register_read(p_ctx, (physical_address)) & ~(bits)));
    _fs_spi_register_read(p_ctx, (physical_address));
}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_line_set(fsctx_t* p_ctx, int offset, int bit) {
	_fs_spi_register_write_nf(p_ctx, _FS_GPIO_MASK, 1 << offset);
	_fs_spi_register_write_nf(p_ctx, _FS_GPIO_DATA, (bit ? 0xffffffff : 0x0));
}

__FS_FUNCTION_PREFER_INLINE int _fs_spi_line_get(fsctx_t* p_ctx, int offset) {
    _fs_spi_register_write_nf(p_ctx, _FS_GPIO_MASK, (0x1 << offset));
    return ((_fs_spi_register_read(p_ctx, _FS_GPIO_DATA) >> offset) & 0x1);
}

__FS_FUNCTION_PREFER_INLINE int _fs_spi_bit_bang_bit(fsctx_t* p_ctx, __attribute__((unused)) u_int8_t chip_select, int bit) {
	int rx_bit = 0;
	_fs_spi_line_set(p_ctx, _FS_SPI_TX_LINE, bit);
	_fs_spi_line_set(p_ctx, _FS_SPI_CLK_LINE, 0x0);
	_fs_spi_line_set(p_ctx, _FS_SPI_CLK_LINE, 0x1);
	rx_bit = _fs_spi_line_get(p_ctx, _FS_SPI_RX_LINE);
	return rx_bit & 0x1;
}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_disable_all_cs(fsctx_t* p_ctx) {
	_fs_spi_line_set(p_ctx, _FS_SPI_FSO_LINE, 1);
}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_go(fsctx_t* p_ctx) {
	_fs_spi_disable_all_cs(p_ctx);
}

__FS_FUNCTION_PREFER_INLINE int _fs_spi_check_cs(fsctx_t* p_ctx, int cs_line) {
	return (((_fs_spi_register_read(p_ctx, _FS_GPIO_AFSEL) >> cs_line) & 0x1) || _fs_spi_line_get(p_ctx, cs_line));
}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_check_ssi(fsctx_t* p_ctx, int check_itself) {
	return;
	while (1) {
		if (!(_fs_spi_ssi_register_read(p_ctx, _FS_SSI_SSIENR) & 0x1) &&
			(_fs_spi_check_cs(p_ctx, _FS_SPI_FSO0_LINE)) &&
			(!check_itself || _fs_spi_check_cs(p_ctx, _FS_SPI_FSO_LINE)))
		{
			break;
		}
#ifdef __KERNEL__
		udelay(1000);
#else
		usleep(1000);
#endif
	}
}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_enable_access_and_chip_select(fsctx_t* p_ctx, __attribute__((unused)) u_int8_t chip_select) {
	_fs_spi_check_ssi(p_ctx, 1);

	_fs_spi_register_clear_bits(p_ctx, _FS_GPIO_AFSEL, (1 << _FS_SPI_FSO_LINE));
	_fs_spi_register_set_bits(p_ctx, _FS_GPIO_DIRECTION, (0x1 << _FS_SPI_FSO_LINE));
	_fs_spi_line_set(p_ctx, _FS_SPI_FSO_LINE, 1);

	_fs_spi_register_clear_bits(p_ctx, _FS_GPIO_AFSEL, (1 << _FS_SPI_CLK_LINE));
    _fs_spi_register_set_bits(p_ctx, _FS_GPIO_DIRECTION, (0x1 << _FS_SPI_CLK_LINE));
	_fs_spi_line_set(p_ctx, _FS_SPI_CLK_LINE, 1);

	_fs_spi_register_clear_bits(p_ctx, _FS_GPIO_AFSEL, (1 << _FS_SPI_TX_LINE));
	_fs_spi_register_set_bits(p_ctx, _FS_GPIO_DIRECTION, (0x1 << _FS_SPI_TX_LINE));
	_fs_spi_line_set(p_ctx, _FS_SPI_TX_LINE, 1);

	_fs_spi_register_clear_bits(p_ctx, _FS_GPIO_AFSEL, (1 << _FS_SPI_RX_LINE));
	_fs_spi_register_clear_bits(p_ctx, _FS_GPIO_DIRECTION, 0x1 << _FS_SPI_RX_LINE);

	_fs_spi_line_set(p_ctx, _FS_SPI_FSO_LINE, 0);

	// TODO Uncomment in production when flash will be put on separate CS line
#if 0
	_fs_spi_check_ssi(p_ctx, 0);
#endif
}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_disable_access_and_chip_select(fsctx_t* p_ctx, __attribute__((unused)) u_int8_t chip_select) {
	_fs_spi_register_set_bits(p_ctx, _FS_GPIO_AFSEL, (1 << _FS_SPI_CLK_LINE) | (1 << _FS_SPI_TX_LINE) | (1 << _FS_SPI_RX_LINE));
	_fs_spi_disable_all_cs(p_ctx);
}

__FS_FUNCTION_PREFER_INLINE int _fs_spi_check_preempted(__attribute__((unused)) fsctx_t* p_ctx, __attribute__((unused)) u_int8_t chip_select) {
	/*
	If kernel preempts user space and makes use of security code on SPI, it
	will correctly enable and use SPI, access, and then disable.  This works
	even if user space is already in the middle of SPI operation.
	The kernel will disable the access at the end, which allows us to detect
	that we have been trampled on and restart our SPI operation. */
	return 0;
}

__FS_FUNCTION_PREFER_INLINE void fs_close_fsctx(fsctx_t* p_ctx) {
#ifdef __KERNEL__
	if (p_ctx != NULL) {
		if (p_ctx->iomapping_spi != NULL) {
			iounmap(p_ctx->iomapping_spi);
			p_ctx->iomapping_spi = NULL;
		}
		if (p_ctx->iomapping_ssi != NULL) {
			iounmap(p_ctx->iomapping_ssi);
			p_ctx->iomapping_ssi = NULL;
		}
	}
#else // #ifdef __KERNEL__
	if (p_ctx != NULL) {
		if (p_ctx->devmem_mmap_spi != NULL) {
			munmap(p_ctx->devmem_mmap_spi, _FS_SPI_SIZE);
			p_ctx->devmem_mmap_spi = NULL;
		}
		if (p_ctx->devmem_mmap_ssi != NULL) {
			munmap(p_ctx->devmem_mmap_ssi, _FS_SSI_SIZE);
			p_ctx->devmem_mmap_ssi = NULL;
		}
		if (p_ctx->devmem_fd != -1) {
			fs_close(p_ctx->devmem_fd);
			p_ctx->devmem_fd = -1;
		}
	}
#endif // #ifdef __KERNEL__
}

__FS_FUNCTION_PREFER_INLINE void fs_init_fsctx(fsctx_t* p_ctx) {
	if(p_ctx == NULL) {
		return;
	}
#ifndef __KERNEL__
	memset( p_ctx, 0, sizeof(fsctx_t) );
	p_ctx->devmem_fd = fs_open(fs_get_decoded_dev_mem(), O_RDWR | O_SYNC);
	if (p_ctx->devmem_fd < 0) {
		fs_debug_printf("Failed opening %s: %s", fs_get_decoded_dev_mem(), strerror(errno));
		fs_close_fsctx( p_ctx );
		return;
	}
	p_ctx->devmem_mmap_spi = mmap(NULL, _FS_SPI_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, (p_ctx)->devmem_fd, _FS_SPI_BASE);
	if ((p_ctx)->devmem_mmap_spi == MAP_FAILED) {
		fs_debug_printf("Failed mmapping kernel memory area at offset 0x%x: %s", _FS_SPI_BASE, strerror(errno));
		fs_close_fsctx(p_ctx);
		return;
	}
	p_ctx->devmem_mmap_ssi = mmap(NULL, _FS_SSI_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, (p_ctx)->devmem_fd, _FS_SSI_BASE);
	if ((p_ctx)->devmem_mmap_ssi == MAP_FAILED) {
		fs_debug_printf("Failed mmapping kernel memory area at offset 0x%x: %s", _FS_SSI_BASE, strerror(errno));
		fs_close_fsctx(p_ctx);
		return;
	}
#else // #ifndef __KERNEL__
	memset( p_ctx, 0, sizeof(fsctx_t) );
	p_ctx->iomapping_spi = ioremap_nocache(_FS_SPI_BASE, _FS_SPI_SIZE);
	if (p_ctx->iomapping_spi == NULL) {
	    fs_debug_printf("Failed ioremapping SPI.");
	    fs_close_fsctx( p_ctx );
	    return;
	}
	p_ctx->iomapping_ssi = ioremap_nocache(_FS_SSI_BASE, _FS_SSI_SIZE);
	if (p_ctx->iomapping_ssi == NULL) {
	    fs_debug_printf("Failed ioremapping SSI.");
	    fs_close_fsctx( p_ctx );
	    return;
	}
#endif // #ifndef __KERNEL__
}

#endif // #ifdef UBNT_ARM_S2
