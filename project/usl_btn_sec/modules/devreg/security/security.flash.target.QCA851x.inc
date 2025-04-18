#ifdef UBNT_MIPS_QCA851x

typedef struct fsctx {
#ifndef __KERNEL__
	int   devmem_fd;
	void* devmem_mmap_spi;
#endif // #ifndef __KERNEL__
} fsctx_t;

#define _FS_SPI_CS0  0x0001
#define _FS_SPI_CS1  0x0002
#define _FS_SPI_CS2  0x0004

#define _FS_SPI_BASE                      0x19000000
#define _FS_SPI_FUNC_SELECT               0x19000000 /* _FS_SPI_BASE+0 */
#define _FS_SPI_CONTROL                   0x19000004 /* _FS_SPI_BASE+4 */
#define _FS_SPI_IO_CONTROL                0x19000008 /* _FS_SPI_BASE+8 */
#define _FS_SPI_READ_DATA                 0x1900000C /* _FS_SPI_BASE+12 - SPI bit is clocked into register pos 0 every clock, shifting all other bits left one bit position */
#define _FS_SPI_SIZE                      16         /* First 4 32-bit addresses */
 
#define _FS_SPI_FUNC_SELECT_FUNC_HWSPI    (0)
#define _FS_SPI_FUNC_SELECT_FUNC_SWSPI    (1)
#define _FS_SPI_FUNC_SELECT_FUNC_MASK     (1)

#define _FS_SPI_CONTROL_REMAP_DISABLE     (1<<6)
#define _FS_SPI_CONTROL_CLOCK_DIVIDER_M   0x3f
#define _FS_SPI_CONTROL_CLOCK_DIVIDER_S   0

#define _FS_SPI_IO_CONTROL_IO_DO_HIGH     (1<< 0) /* SPI_IO_CONTROL/IO_DO     */
#define _FS_SPI_IO_CONTROL_IO_CLOCK_HIGH  (1<< 8) /* SPI_IO_CONTROL/IO_CLOCK  */
#define _FS_SPI_IO_CONTROL_IO_CLOCK_LOW   (0)     /* SPI_IO_CONTROL/IO_CLOCK  */

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE u_int8_t _fs_spi_get_secure_flash_chip_select(void) {
	return _FS_SPI_CS0; /* CS0 */
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE u_int32_t _fs_spi_get_secure_flash_chip_select_enable_bits(u_int8_t chip_select) {
	return ((~chip_select) & 0x7) << 16; /* Three possible CS in bits CS0=bit0, CS1=bit1, CS2=bit2.  CS are active low so invert and mask, then shift. */
}

__FS_FUNCTION_PREFER_INLINE uintptr_t _fs_spi_get_spi_register_address(fsctx_t* p_ctx, uintptr_t physical_address) {
#ifndef __KERNEL__
	return (uintptr_t)(((u_int8_t*)((p_ctx)->devmem_mmap_spi)) + (physical_address - _FS_SPI_BASE));
#else // #ifndef __KERNEL__
	return (uintptr_t)(KSEG1ADDR(physical_address));
#endif // #ifndef __KERNEL__
}

__FS_FUNCTION_PREFER_INLINE fs_spi_register_t _fs_spi_register_read(fsctx_t* p_ctx, uintptr_t physical_address) {
	return ( *( (volatile fs_spi_register_t __force *)_fs_spi_get_spi_register_address(p_ctx, physical_address) ) );
}

__FS_FUNCTION_PREFER_INLINE fs_spi_register_t fs_spi_register_write_nf(fsctx_t* p_ctx, uintptr_t physical_address, fs_spi_register_t value) {
	return ( *( (volatile fs_spi_register_t __force *)_fs_spi_get_spi_register_address(p_ctx, physical_address) ) = (value) );
}

__FS_FUNCTION_PREFER_INLINE fs_spi_register_t _fs_spi_register_write(fsctx_t* p_ctx, uintptr_t physical_address, fs_spi_register_t value) {
	fs_spi_register_write_nf(p_ctx, physical_address, value);
	return _fs_spi_register_read(p_ctx, physical_address);
}

__FS_FUNCTION_PREFER_INLINE int _fs_spi_bit_bang_bit(fsctx_t* p_ctx, u_int8_t chip_select, u_int8_t bit) {
	bit = !!bit;
	fs_spi_register_write_nf(p_ctx, _FS_SPI_IO_CONTROL, _fs_spi_get_secure_flash_chip_select_enable_bits(chip_select) | _FS_SPI_IO_CONTROL_IO_CLOCK_LOW | bit);
	fs_spi_register_write_nf(p_ctx, _FS_SPI_IO_CONTROL, _fs_spi_get_secure_flash_chip_select_enable_bits(chip_select) | _FS_SPI_IO_CONTROL_IO_CLOCK_HIGH | bit);
	return (_fs_spi_register_read(p_ctx, _FS_SPI_READ_DATA) & 0x1);
}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_disable_all_cs(fsctx_t* p_ctx) {
	fs_spi_register_write_nf(p_ctx, _FS_SPI_IO_CONTROL, _fs_spi_get_secure_flash_chip_select_enable_bits(0) /* Disable all CS */);
}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_go(fsctx_t* p_ctx, u_int8_t chip_select) {
	fs_spi_register_write_nf(p_ctx, _FS_SPI_IO_CONTROL, _fs_spi_get_secure_flash_chip_select_enable_bits(chip_select) | _FS_SPI_IO_CONTROL_IO_CLOCK_LOW);
	_fs_spi_disable_all_cs(p_ctx);
}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_enable_access_and_chip_select(fsctx_t* p_ctx, __attribute__((unused)) u_int8_t chip_select) {
	fs_spi_register_write_nf(p_ctx, _FS_SPI_FUNC_SELECT, _FS_SPI_FUNC_SELECT_FUNC_SWSPI);
	fs_spi_register_write_nf(p_ctx, _FS_SPI_IO_CONTROL, _fs_spi_get_secure_flash_chip_select_enable_bits(0));
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE int _fs_spi_check_preempted(fsctx_t* p_ctx, __ATTRIB_UNUSED u_int8_t chip_select) {
	/*
	If kernel preempts user space and makes use of security code on SPI, it 
	will correctly enable and use SPI, access, and then disable.  This works 
	even if user space is already in the middle of SPI operation. 
	The kernel will disable the access at the end, which allows us to detect 
	that we have been trampled on and restart our SPI operation. */
#if SECURITY_ENABLE_DEBUG_OUTPUT
	int preempted = 
#else
	return
#endif
		((_fs_spi_register_read(p_ctx, _FS_SPI_FUNC_SELECT) & _FS_SPI_FUNC_SELECT_FUNC_MASK) != _FS_SPI_FUNC_SELECT_FUNC_SWSPI);
#if SECURITY_ENABLE_DEBUG_OUTPUT
	if (preempted) {
		fs_debug_printf("WARNING: SPI operation was pre-empted by kernel.\n");
	}
	return preempted;
#endif
}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_disable_access_and_chip_select(fsctx_t* p_ctx, u_int8_t chip_select) {
	fs_spi_register_write_nf(p_ctx, _FS_SPI_IO_CONTROL, _fs_spi_get_secure_flash_chip_select_enable_bits(chip_select) | _FS_SPI_IO_CONTROL_IO_CLOCK_LOW);
	fs_spi_register_write_nf(p_ctx, _FS_SPI_IO_CONTROL, _fs_spi_get_secure_flash_chip_select_enable_bits(0) /* Disable all CS */);
	_fs_spi_register_write(p_ctx, _FS_SPI_FUNC_SELECT, _FS_SPI_FUNC_SELECT_FUNC_HWSPI);
}

__FS_FUNCTION_PREFER_INLINE void fs_close_fsctx(fsctx_t* p_ctx) {
	if(p_ctx == NULL) {
		goto done;
	}
#ifndef __KERNEL__
	if (p_ctx->devmem_mmap_spi != NULL) {
		munmap(p_ctx->devmem_mmap_spi, _FS_SPI_SIZE);
		p_ctx->devmem_mmap_spi = NULL;
	}
	if (p_ctx->devmem_fd != -1) {
		fs_close(p_ctx->devmem_fd);
		p_ctx->devmem_fd = -1;
	}
#endif // #ifdef __KERNEL__
done:
	return;
}

__FS_FUNCTION_PREFER_INLINE void fs_init_fsctx(fsctx_t* p_ctx) {
	if(p_ctx == NULL) {
		goto done;
	}
#ifndef __KERNEL__
	memset( p_ctx, 0, sizeof(fsctx_t) );
	p_ctx->devmem_fd = fs_open(fs_get_decoded_dev_mem(), O_RDWR);
	if (p_ctx->devmem_fd < 0) {
		fs_debug_printf("Failed opening %s: %s", fs_get_decoded_dev_mem(), strerror(errno));
		fs_close_fsctx(p_ctx);
		p_ctx = NULL;
		goto done;
	}
	p_ctx->devmem_mmap_spi = mmap(NULL, _FS_SPI_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, p_ctx->devmem_fd, _FS_SPI_BASE);
	if ((p_ctx)->devmem_mmap_spi == MAP_FAILED) {
		fs_debug_printf("Failed mmapping kernel memory area at offset 0x%x: %s", _FS_SPI_BASE, strerror(errno));
		fs_close_fsctx(p_ctx);
		p_ctx = NULL;
		goto done;
	}
#endif // #ifndef __KERNEL__
done:
	return;
}

#endif // #ifdef UBNT_MIPS_QCA851x
