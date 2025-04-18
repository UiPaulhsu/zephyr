#if SECURITY_HAVE_DIRECT_BITBANG_SPI_FLASH_HARDWARE

////////////////////////////////////////////////////////////////////////////////
/// Internal Macros
////////////////////////////////////////////////////////////////////////////////

__FS_FUNCTION_PREFER_INLINE u_int8_t _fs_spi_bit_bang_byte(fsctx_t* p_ctx, u_int8_t chip_select, u_int8_t byte) {
	__FS_LOCAL_STATIC_OPTION int      fsv_t1;
	__FS_LOCAL_STATIC_OPTION u_int8_t fsv_t2;

	fsv_t2 = 0;
	fsv_t1 = 0;
	for(fsv_t1 = 7; fsv_t1 >= 0; fsv_t1--) {
		fsv_t2 |= (_fs_spi_bit_bang_bit(p_ctx, chip_select, (byte & (1 << fsv_t1))) << fsv_t1);
	}

// 	fs_debug_printf("fs_spi_bit_bang_byte[CS%u] Sent 0x%02x.  Rcvd 0x%02x.\n", chip_select, byte, fsv_t2);
	return fsv_t2;
}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_write_then_read(fsctx_t* p_ctx, u_int8_t chip_select, u_int8_t* tx, size_t tx_len, u_int8_t* rx, size_t rx_len) {
	__FS_LOCAL_STATIC_OPTION size_t fsv_t1;
        for (fsv_t1 = 0; fsv_t1 < tx_len; fsv_t1++) {
				_fs_spi_bit_bang_byte(p_ctx, chip_select, tx[fsv_t1]);
        }
        for (fsv_t1 = 0; fsv_t1 < rx_len; fsv_t1++) {
                rx[fsv_t1] = _fs_spi_bit_bang_byte(p_ctx, chip_select, 0);
        }
}

#endif // #if SECURITY_HAVE_DIRECT_BITBANG_SPI_FLASH_HARDWARE
