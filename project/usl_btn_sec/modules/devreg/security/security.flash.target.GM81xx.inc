#ifdef UBNT_ARM_GM81xx

typedef struct fsctx {
#ifndef __KERNEL__
	int   devmem_fd;
	void* devmem_mmap_spi;
	void* devmem_mmap_pmu;
#else // #ifndef __KERNEL__
    volatile void __iomem * iomapping_spi;
    volatile void __iomem * iomapping_pmu;
#endif // #ifndef __KERNEL__
} fsctx_t;

#define _FS_SPI_CS0  0x0001
#define _FS_SPI_CS1  0x0002
#define _FS_SPI_CS2  0x0004

#define _FS_SPI_BASE         0x99400000 /* GPIO_0 base */
#define _FS_GPIO_OUTPUT      (_FS_SPI_BASE + 0)
#define _FS_GPIO_INPUT       (_FS_SPI_BASE + 0x4)
#define _FS_GPIO_DIRECTION   (_FS_SPI_BASE + 0x8)
#define _FS_GPIO_SETBIT      (_FS_SPI_BASE + 0x10)
#define _FS_GPIO_CLEARBIT    (_FS_SPI_BASE + 0x14)
#define _FS_SPI_SIZE         0x1000
#define _FS_PMU_BASE         0x99000000
#define _FS_PMU_MUX1         (_FS_PMU_BASE + 0x50)
#define _FS_PMU_MUX2         (_FS_PMU_BASE + 0x54)
#define _FS_PMU_SIZE         0x1000
#define _FS_PMU_MUX1_MASK    ((3 << 30) | (3 << 28) | (3 << 26)) /* GPIO_0[18][17][16] */
#define _FS_PMU_MUX2_MASK    ((3 << 4) | (3 << 6)) /* GPIO_0[15][14] */
#define _FS_PMU_MUX1_RESTORE ((1 << 30) | (1 << 28) | (1 << 26)) /* TX CLK RX */
#define _FS_PMU_MUX2_RESTORE ((0 << 4) | (0 << 6)) /* FS1 FS0 */
#define _FS_SPI_RX_LINE      16 /* GPIO_0[16] */
#define _FS_SPI_TX_LINE      18
#define _FS_SPI_CLK_LINE     17
#define _FS_SPI_FS0_LINE     14
#define _FS_SPI_FS1_LINE     15

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE u_int8_t _fs_spi_get_secure_flash_chip_select(void) {
	return _FS_SPI_CS0; /* FS0 */
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE u_int32_t _fs_spi_get_chip_select_bitmask_to_gpio_bits(u_int8_t chip_select) {
        return (chip_select & 0x3) << 14; /* Two possible CS bits FS0 and FS1 at bit 14 and 15 */
}

__FS_FUNCTION_PREFER_INLINE uintptr_t _fs_spi_get_pmu_register_address(fsctx_t* p_ctx, uintptr_t physical_address) {
#ifndef __KERNEL__
	return (uintptr_t)(((u_int8_t*)(p_ctx->devmem_mmap_pmu)) + (physical_address - _FS_PMU_BASE));
#else // #ifndef __KERNEL__
	return (uintptr_t)(p_ctx->iomapping_pmu + (physical_address - _FS_PMU_BASE));
#endif // #ifndef __KERNEL__
}

__FS_FUNCTION_PREFER_INLINE uintptr_t _fs_spi_get_spi_register_address(fsctx_t* p_ctx, uintptr_t physical_address) {
#ifndef __KERNEL__
	return (uintptr_t)(((u_int8_t*)(p_ctx->devmem_mmap_spi)) + (physical_address - _FS_SPI_BASE));
#else // #ifndef __KERNEL__
	return (uintptr_t)(p_ctx->iomapping_spi + (physical_address - _FS_SPI_BASE));
#endif // #ifndef __KERNEL__
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

__FS_FUNCTION_PREFER_INLINE fs_spi_register_t _fs_spi_pmu_register_read(fsctx_t* p_ctx, uintptr_t physical_address) {
	return ( *( (volatile fs_spi_register_t __force *)_fs_spi_get_pmu_register_address(p_ctx, physical_address) ) );
}

__FS_FUNCTION_PREFER_INLINE fs_spi_register_t _fs_spi_pmu_register_write_nf(fsctx_t* p_ctx, uintptr_t physical_address, fs_spi_register_t value) {
	return ( *( (volatile fs_spi_register_t __force *)_fs_spi_get_pmu_register_address( p_ctx, physical_address) ) = (value) );
}

__FS_FUNCTION_PREFER_INLINE fs_spi_register_t _fs_spi_pmu_register_write(fsctx_t* p_ctx, uintptr_t physical_address, fs_spi_register_t value) {
	_fs_spi_pmu_register_write_nf(p_ctx, physical_address, value);
	return _fs_spi_pmu_register_read(p_ctx, physical_address);
}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_pmu_register_set_bits(fsctx_t* p_ctx, uintptr_t physical_address, fs_spi_register_t bits) {
	_fs_spi_pmu_register_write_nf(p_ctx, (physical_address), (_fs_spi_pmu_register_read(p_ctx, (physical_address)) | (bits)));
	_fs_spi_pmu_register_read(p_ctx, (physical_address));
}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_register_set_bits(fsctx_t* p_ctx, uintptr_t physical_address, fs_spi_register_t bits) {
	_fs_spi_register_write_nf(p_ctx, (physical_address), (_fs_spi_register_read(p_ctx, (physical_address)) | (bits)));
	_fs_spi_register_read(p_ctx, (physical_address));
}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_pmu_register_clear_bits(fsctx_t* p_ctx, uintptr_t physical_address, fs_spi_register_t bits) {
    _fs_spi_pmu_register_write_nf(p_ctx, (physical_address), (_fs_spi_pmu_register_read(p_ctx, (physical_address)) & ~(bits)));
    _fs_spi_pmu_register_read(p_ctx, (physical_address));
}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_register_clear_bits(fsctx_t* p_ctx, uintptr_t physical_address, fs_spi_register_t bits) {
    _fs_spi_register_write_nf(p_ctx, (physical_address), (_fs_spi_register_read(p_ctx, (physical_address)) & ~(bits)));
    _fs_spi_register_read(p_ctx, (physical_address));
}

__FS_FUNCTION_PREFER_INLINE int _fs_spi_bit_bang_bit(fsctx_t* p_ctx, u_int8_t chip_select, u_int8_t bit) {
	int rx_bit = 0;
	_fs_spi_register_write_nf(p_ctx, _FS_GPIO_CLEARBIT, _fs_spi_get_chip_select_bitmask_to_gpio_bits(chip_select));
	if (bit) {
		_fs_spi_register_write_nf(p_ctx, _FS_GPIO_SETBIT, 1 << _FS_SPI_TX_LINE);
	} else {
		_fs_spi_register_write_nf(p_ctx, _FS_GPIO_CLEARBIT, 1 << _FS_SPI_TX_LINE);
	}
	_fs_spi_register_write_nf(p_ctx, _FS_GPIO_SETBIT, 1 << _FS_SPI_CLK_LINE);
	rx_bit = (_fs_spi_register_read(p_ctx, _FS_GPIO_INPUT) >> _FS_SPI_RX_LINE);
	_fs_spi_register_write_nf(p_ctx, _FS_GPIO_CLEARBIT, 1 << _FS_SPI_CLK_LINE);
	return rx_bit & 1;
}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_disable_all_cs(fsctx_t* p_ctx) {
	_fs_spi_register_write_nf(p_ctx, _FS_GPIO_SETBIT, _fs_spi_get_chip_select_bitmask_to_gpio_bits(0x3));
}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_go(fsctx_t* p_ctx, __ATTRIB_UNUSED u_int8_t chip_select) {
	_fs_spi_disable_all_cs(p_ctx);
}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_enable_access_and_chip_select(fsctx_t* p_ctx, u_int8_t chip_select) {
	_fs_spi_pmu_register_clear_bits(p_ctx, _FS_PMU_MUX1, _FS_PMU_MUX1_MASK);
	_fs_spi_pmu_register_clear_bits(p_ctx, _FS_PMU_MUX2, _FS_PMU_MUX2_MASK);
	_fs_spi_register_clear_bits(p_ctx, _FS_GPIO_DIRECTION, 1 << _FS_SPI_RX_LINE);
	_fs_spi_register_set_bits(p_ctx, _FS_GPIO_DIRECTION, (1 << _FS_SPI_TX_LINE) | (1 << _FS_SPI_CLK_LINE) | _fs_spi_get_chip_select_bitmask_to_gpio_bits(chip_select));
	_fs_spi_register_write_nf(p_ctx, _FS_GPIO_CLEARBIT, _fs_spi_get_chip_select_bitmask_to_gpio_bits(chip_select));
	_fs_spi_register_write_nf(p_ctx, _FS_GPIO_CLEARBIT, 1 << _FS_SPI_CLK_LINE);
}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_disable_access_and_chip_select(fsctx_t* p_ctx, __ATTRIB_UNUSED u_int8_t chip_select) {
	_fs_spi_disable_all_cs( p_ctx );
	_fs_spi_pmu_register_set_bits(p_ctx, _FS_PMU_MUX1, _FS_PMU_MUX1_RESTORE);
	_fs_spi_pmu_register_set_bits(p_ctx, _FS_PMU_MUX2, _FS_PMU_MUX2_RESTORE);
	_fs_spi_disable_all_cs( p_ctx );
}

__FS_FUNCTION_PREFER_INLINE int _fs_spi_check_preempted(fsctx_t* p_ctx, __ATTRIB_UNUSED u_int8_t chip_select) {
	/*
	If kernel preempts user space and makes use of security code on SPI, it 
	will correctly enable and use SPI, access, and then disable.  This works 
	even if user space is already in the middle of SPI operation. 
	The kernel will disable the access at the end, which allows us to detect 
	that we have been trampled on and restart our SPI operation. */
	return (_fs_spi_pmu_register_read(p_ctx,_FS_PMU_MUX1) & _FS_PMU_MUX1_MASK) == (_FS_PMU_MUX1_RESTORE & _FS_PMU_MUX1_MASK);
}

__FS_FUNCTION_PREFER_INLINE void fs_close_fsctx(fsctx_t* p_ctx) {
#ifdef __KERNEL__
	if (p_ctx != NULL) {
		if (p_ctx->iomapping_pmu != NULL) {
			iounmap(p_ctx->iomapping_pmu);
			p_ctx->iomapping_pmu = NULL;
		}
		if (p_ctx->iomapping_spi != NULL) {
			iounmap(p_ctx->iomapping_spi);
			p_ctx->iomapping_spi = NULL;
		}
	}
#else // #ifdef __KERNEL__
	if (p_ctx != NULL) {
		if (p_ctx->devmem_mmap_pmu != NULL) {
			munmap(p_ctx->devmem_mmap_pmu, _FS_PMU_SIZE);
			p_ctx->devmem_mmap_pmu = NULL;
		}
		if (p_ctx->devmem_mmap_spi != NULL) {
			munmap(p_ctx->devmem_mmap_spi, _FS_SPI_SIZE);
			p_ctx->devmem_mmap_spi = NULL;
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
	p_ctx->devmem_mmap_pmu = mmap(NULL, _FS_PMU_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, p_ctx->devmem_fd, _FS_PMU_BASE);
	if (p_ctx->devmem_mmap_pmu == MAP_FAILED) {
		fs_debug_printf("Failed mmapping kernel memory area at offset 0x%x: %s", _FS_PMU_BASE, strerror(errno));
		fs_close_fsctx( p_ctx );
		return;
	}
#else // #ifndef __KERNEL__
	memset( p_ctx, 0, sizeof(fsctx_t) );
	p_ctx->iomapping_pmu = ioremap_nocache(_FS_PMU_BASE, _FS_PMU_SIZE);
	if (p_ctx->iomapping_pmu == NULL) {
	    fs_debug_printf("Failed ioremapping PMU.");
	    fs_close_fsctx( p_ctx );
	    return;
	}
	p_ctx->iomapping_spi = ioremap_nocache(_FS_SPI_BASE, _FS_SPI_SIZE);
	if (p_ctx->iomapping_spi == NULL) {
	    fs_debug_printf("Failed ioremapping SPI.");
	    fs_close_fsctx( p_ctx );
	    return;
	}
#endif // #ifndef __KERNEL__
}

#endif // #ifdef UBNT_ARM_GM81xx
