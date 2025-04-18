#ifdef UBNT_MIPS_BCM4706

#ifdef __KERNEL__
#define _FS_BCM4706_CHIPC_BASE      0x18000000
#define _FS_BCM4706_CHIPC_SIZE      0x10000
#define _FS_BCM4706_CHIPID          (_FS_BCM4706_CHIPC_BASE + 0) 
#define _FS_BCM4706_FLASH_CONTROL   (_FS_BCM4706_CHIPC_BASE + 0x40)
#define _FS_BCM4706_FLASH_ADDR      (_FS_BCM4706_CHIPC_BASE + 0x44)
#define _FS_BCM4706_FLASH_DATA      (_FS_BCM4706_CHIPC_BASE + 0x48)

/* Start/busy bit in flashcontrol */
#define _FS_BCM4706_SFLASH_OPCODE       0x000000ff
#define _FS_BCM4706_SFLASH_ACTION       0x00000700
#define	_FS_BCM4706_SFLASH_CS_ACTIVE    0x00001000	/* Chip Select Active, rev >= 20 */
#define _FS_BCM4706_SFLASH_START        0x80000000
#define _FS_BCM4706_SFLASH_BUSY         _FS_BCM4706_SFLASH_START

/* flashcontrol action codes */
#define	_FS_BCM4706_SFLASH_ACT_OPONLY   0x0000		/* Issue opcode only */
#define	_FS_BCM4706_SFLASH_ACT_OP1D     0x0100		/* opcode + 1 data byte */
#define	_FS_BCM4706_SFLASH_ACT_OP3A     0x0200		/* opcode + 3 addr bytes */
#define	_FS_BCM4706_SFLASH_ACT_OP3A1D   0x0300		/* opcode + 3 addr & 1 data bytes */
#define	_FS_BCM4706_SFLASH_ACT_OP3A4D   0x0400		/* opcode + 3 addr & 4 data bytes */
#define	_FS_BCM4706_SFLASH_ACT_OP3A4X4D 0x0500		/* opcode + 3 addr, 4 don't care & 4 data bytes */
#define	_FS_BCM4706_SFLASH_ACT_OP3A1X4D 0x0700		/* opcode + 3 addr, 1 don't care & 4 data bytes */

#define SFLASH_CONTINUE_READ        
typedef struct fsctx {
    volatile void __iomem * iomapping_chipc;
} fsctx_t;

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE int  _fs_spi_check_preempted(__ATTRIB_UNUSED fsctx_t* p_ctx) { return 0;}

__FS_FUNCTION_PREFER_INLINE uintptr_t _fs_bcm4706_get_chipc_register_address(fsctx_t* p_ctx, uintptr_t physical_address) {
	return (uintptr_t)(p_ctx->iomapping_chipc + (physical_address - _FS_BCM4706_CHIPC_BASE));
}

__FS_FUNCTION_PREFER_INLINE fs_spi_register_t _fs_bcm4706_chipc_register_read(fsctx_t* p_ctx, uintptr_t physical_address) {
	return ( *( (volatile fs_spi_register_t __force *)_fs_bcm4706_get_chipc_register_address(p_ctx, physical_address) ) );
}

__FS_FUNCTION_PREFER_INLINE fs_spi_register_t _fs_bcm4706_chipc_register_write(fsctx_t* p_ctx, uintptr_t physical_address, fs_spi_register_t value) {
	return ( *( (volatile fs_spi_register_t __force *)_fs_bcm4706_get_chipc_register_address(p_ctx, physical_address) ) = (value) );
}

__FS_FUNCTION_PREFER_INLINE void fs_close_fsctx(fsctx_t* p_ctx) {
	if (p_ctx != NULL) {
		if (p_ctx->iomapping_chipc != NULL) {
			iounmap(p_ctx->iomapping_chipc);
			p_ctx->iomapping_chipc = NULL;
		}
	}
}

__FS_FUNCTION_PREFER_INLINE void fs_init_fsctx(fsctx_t* p_ctx) {
	if(p_ctx == NULL) {
		return;
	}
	memset( p_ctx, 0, sizeof(fsctx_t) );
	p_ctx->iomapping_chipc = ioremap_nocache(_FS_BCM4706_CHIPC_BASE, _FS_BCM4706_CHIPC_SIZE);
	if (p_ctx->iomapping_chipc == NULL) {
	    fs_debug_printf("Failed ioremapping CHIP common registers.");
	    fs_close_fsctx( p_ctx );
	    return;
	}
}

__FS_FUNCTION_PREFER_INLINE void _fs_bcm4706_issue_flash_cmd(fsctx_t* p_ctx, uint32_t opcode)
{
    _fs_bcm4706_chipc_register_write(p_ctx, _FS_BCM4706_FLASH_CONTROL, _FS_BCM4706_SFLASH_START | opcode);
    while (_fs_bcm4706_chipc_register_read(p_ctx, _FS_BCM4706_FLASH_CONTROL) & _FS_BCM4706_SFLASH_BUSY);
}

__FS_FUNCTION_PREFER_INLINE void _fs_bcm4706_set_flash_addr(fsctx_t* p_ctx, fs_spi_register_t addr)
{
    _fs_bcm4706_chipc_register_write(p_ctx, _FS_BCM4706_FLASH_ADDR, addr);
}

__FS_FUNCTION_PREFER_INLINE fs_spi_register_t _fs_bcm4706_read_flash_data(fsctx_t* p_ctx)
{
    return (_fs_bcm4706_chipc_register_read(p_ctx, _FS_BCM4706_FLASH_DATA));
}

__FS_FUNCTION_PREFER_INLINE void _fs_bcm4706_flash_write_then_read(fsctx_t* p_ctx, u_int32_t cmd, u_int32_t address, size_t skip_len, u_int8_t* rx, size_t rx_len) {
    uint32_t opcode;
    size_t i, total;
    int clr_addr_before_read;
    fs_spi_register_t data;

    total = skip_len + rx_len;
    if (total == 0) {
        opcode = _FS_BCM4706_SFLASH_ACT_OPONLY | cmd;
        _fs_bcm4706_issue_flash_cmd(p_ctx, opcode);
        return;
    }

    /* need to read something back */    
    opcode = _FS_BCM4706_SFLASH_CS_ACTIVE | cmd;

    if (address) {
        clr_addr_before_read = 1;
        _fs_bcm4706_set_flash_addr(p_ctx, address);
    } else {
        clr_addr_before_read = 0;
    }

    _fs_bcm4706_issue_flash_cmd(p_ctx, opcode);

    if (clr_addr_before_read) {
        _fs_bcm4706_set_flash_addr(p_ctx, 0);
    }

    for (i = 0; i < skip_len; i++) {
        _fs_bcm4706_issue_flash_cmd(p_ctx, _FS_BCM4706_SFLASH_CS_ACTIVE | _FS_BCM4706_SFLASH_ACT_OPONLY | _FS_CMD_READ);
    }

    for (i = 0; i < rx_len; i++) {
        data = _fs_bcm4706_read_flash_data(p_ctx);
        *(rx + i) = data & 0xff;
        if ( (i+1) == rx_len) {
            _fs_bcm4706_issue_flash_cmd(p_ctx, _FS_BCM4706_SFLASH_ACT_OP3A1D | _FS_CMD_READ);
        } else {
            _fs_bcm4706_issue_flash_cmd(p_ctx, _FS_BCM4706_SFLASH_CS_ACTIVE | _FS_BCM4706_SFLASH_ACT_OPONLY | _FS_CMD_READ);
        }
    }
}

__FS_FUNCTION_PREFER_INLINE void _fs_bcm4706_flash_mxic_read_otp(fsctx_t* p_ctx, u_int8_t* dest, size_t bytes_to_read) {
	memset( dest, 0, bytes_to_read );
	_fs_bcm4706_flash_write_then_read(p_ctx, _FS_BCM4706_SFLASH_ACT_OPONLY | _FS_CMD_MXIC_ENSO, 0, 0, 0, 0);
    _fs_bcm4706_flash_write_then_read(p_ctx, _FS_BCM4706_SFLASH_ACT_OP3A1D | _FS_CMD_READ, 0, 0, dest, bytes_to_read);
	_fs_bcm4706_flash_write_then_read(p_ctx, _FS_BCM4706_SFLASH_ACT_OPONLY | _FS_CMD_MXIC_EXSO, 0, 0, 0, 0);
}

__FS_FUNCTION_PREFER_INLINE u_int8_t fs_bcm4706_flash_mxic_rdscur(fsctx_t* p_ctx) {
	__FS_LOCAL_STATIC_OPTION u_int8_t fsv_t2[] = { 0x0 };
	do {
		memset(fsv_t2, 0, sizeof fsv_t2);
		_fs_bcm4706_flash_write_then_read(p_ctx, _FS_BCM4706_SFLASH_ACT_OP3A1D | _FS_CMD_MXIC_RDSCUR, 0, 0, fsv_t2, sizeof fsv_t2);
	} while (_fs_spi_check_preempted(p_ctx));
	return fsv_t2[0];
}

__FS_FUNCTION_PREFER_INLINE void fs_bcm4706_flash_mxic_read_uid_from_sfdp(fsctx_t* p_ctx, u_int8_t* dest, size_t bytes_to_read) {
	do {
		memset( dest, 0, bytes_to_read );
		_fs_bcm4706_flash_write_then_read(p_ctx, _FS_BCM4706_SFLASH_ACT_OP3A1D | _FS_CMD_MXIC_RDSFDP, 0x8c, 1, dest, bytes_to_read);
	} while (_fs_spi_check_preempted(p_ctx));
}

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_bcm4706_flash_rdid(fsctx_t* p_ctx) {
	__FS_LOCAL_STATIC_OPTION u_int8_t fsv_t2[] = { 0x0, 0x0, 0x0 };
	__FS_LOCAL_STATIC_OPTION u_int32_t fsv_t3;

	fsv_t3 = 0;
	do {
		memset(fsv_t2, 0, sizeof fsv_t2);
		_fs_bcm4706_flash_write_then_read(p_ctx, _FS_BCM4706_SFLASH_ACT_OP1D | _FS_CMD_RDID, 0, 0, fsv_t2, sizeof fsv_t2);
		fsv_t3 |= fsv_t2[0] << 16;
		fsv_t3 |= fsv_t2[1] << 8;
		fsv_t3 |= fsv_t2[2] << 0;
	} while (_fs_spi_check_preempted(p_ctx));
	return fsv_t3;
}

__FS_FUNCTION_PREFER_INLINE void fs_bcm4706_flash_mxic_read_otp(fsctx_t* p_ctx, u_int8_t* dest, size_t bytes_to_read) {
	do {
		_fs_bcm4706_flash_mxic_read_otp(p_ctx, dest, bytes_to_read);
	} while (_fs_spi_check_preempted(p_ctx));
}

__FS_FUNCTION_PREFER_INLINE void fs_bcm4706_flash_winbond_read_uid(fsctx_t* p_ctx, u_int8_t* dest, size_t bytes_to_read) {
	do {
		memset( dest, 0, bytes_to_read );
		_fs_bcm4706_flash_write_then_read(p_ctx, _FS_BCM4706_SFLASH_ACT_OP1D | _FS_CMD_WINBOND_READ_UID, 0, 4, dest, bytes_to_read);
	} while (_fs_spi_check_preempted(p_ctx));
}

/*
__FS_FUNCTION_PREFER_INLINE void fs_bcm4706_flash_spansion_read_uid(fsctx_t* p_ctx, u_int8_t* dest, size_t bytes_to_read) {
	do {
		memset( dest, 0, bytes_to_read );
		_fs_bcm4706_flash_write_then_read(p_ctx, _FS_BCM4706_SFLASH_ACT_OP3A1D | _FS_CMD_WINBOND_READ_UID, 0, 1, dest, bytes_to_read);
	} while (_fs_spi_check_preempted(p_ctx));
} 
*/ 

__FS_FUNCTION_PREFER_INLINE void fs_bcm4706_flash_eon_read_uid(fsctx_t* p_ctx, u_int8_t* dest, size_t bytes_to_read) {
	do {
		memset( dest, 0, bytes_to_read );
		_fs_bcm4706_flash_write_then_read(p_ctx, _FS_BCM4706_SFLASH_ACT_OP3A1D | _FS_CMD_EON_READ_UID, 0x80, 1, dest, bytes_to_read);
	} while (_fs_spi_check_preempted(p_ctx));
}

__FS_FUNCTION_PREFER_INLINE void fs_spi_numonyx_read_uid(fsctx_t* p_ctx, u_int8_t* dest, size_t bytes_to_read) {
	do {
		memset( dest, 0, bytes_to_read );
		_fs_bcm4706_flash_write_then_read(p_ctx, _FS_BCM4706_SFLASH_ACT_OP1D | _FS_CMD_NUMONYX_EXTENDED_RDID, 0, 6, dest, bytes_to_read);
	} while (_fs_spi_check_preempted(p_ctx));
}

__FS_FUNCTION_PREFER_INLINE size_t fs_bcm4706_flash_read_uid(fsctx_t* p_ctx, u_int8_t* dest, size_t dest_len) {
	__FS_LOCAL_STATIC_OPTION u_int32_t fsv_t1;
	__FS_LOCAL_STATIC_OPTION size_t    fsv_t2;
	__FS_LOCAL_STATIC_OPTION size_t    fsv_t3;
	fsv_t1 = 0;
	fsv_t2 = 0;
	fsv_t3 = 0;
	memset( dest, 0xff, sizeof dest);

	fsv_t1 = fs_bcm4706_flash_rdid(p_ctx);
    if (0 
     || fsv_t1 == MXIC_8M_JEDEC_ID
#if SECURITY_FLASH_HWREV >= SECURITY_FLASH_HWREV_2
	 || fsv_t1 == MXIC_16M_JEDEC_ID
#endif 
    ) {
		u_int8_t sec = 0;
		fsv_t2 = (512/8);
		sec = fs_bcm4706_flash_mxic_rdscur(p_ctx);
		if ((sec & 0x3) == 0x3) {
			if (dest_len < fsv_t2) {
				fs_debug_printf( "Destination buffer length was %zu but needed %zu.\n", (dest_len), fsv_t2);
			} else {
				fs_bcm4706_flash_mxic_read_otp(p_ctx, dest, fsv_t2);
				fsv_t3 = fsv_t2;
			}
#if SECURITY_FLASH_HWREV >= SECURITY_FLASH_HWREV_2
		} else if(sec == 0) {
            fsv_t2 = 13;
            if (dest_len < fsv_t2) {
                fs_debug_printf( "Destination buffer length was %zu but needed %zu.\n", (dest_len), fsv_t2);
            } else {
                // 0x8C to 0x98 (140-152)
                fs_bcm4706_flash_mxic_read_uid_from_sfdp(p_ctx, dest, fsv_t2);
                if (dest[0] == MXIC_MFR_ID) {
                    fsv_t3 = fsv_t2; 
                } else {
                    fsv_t3 = 0;
                }
            }
#endif // #if >= SECURITY_FLASH_HWREV_2
        } else {
            fsv_t3 = 0;
        }
/*
	if (fsv_t1 == MXIC_8M_JEDEC_ID) {
		u_int8_t sec = 0;
		fsv_t2 = (512/8);
		sec = fs_bcm4706_flash_mxic_rdscur(p_ctx);
		if ((sec & 0x3) == 0x3) {
			if (dest_len < fsv_t2) {
				fs_debug_printf( "Destination buffer length was %zu but needed %zu.\n", (dest_len), fsv_t2);
			} else {
				fs_bcm4706_flash_mxic_read_otp(p_ctx, dest, fsv_t2);
				fsv_t3 = fsv_t2;
			}
		} else {
			fsv_t3 = 0;
		}
*/
	} else if (fsv_t1 == WINBOND_W25X05CL_JEDEC_ID || fsv_t1 == WINBOND_8M_JEDEC_ID || fsv_t1 == WINBOND_16M_JEDEC_ID) {
		fsv_t2 = (64/8);
		if (dest_len < fsv_t2) {
			fs_debug_printf( "Destination buffer length was %zu but needed %zu.\n", (dest_len), fsv_t2);
		} else {
			fs_bcm4706_flash_winbond_read_uid(p_ctx, dest, fsv_t2);
			fsv_t3 = fsv_t2;
		}
/* 
    } else if (fsv_t1 == SPANSION_16M_JEDEC_ID) {
		fsv_t2 = (64/8);
		if (dest_len < fsv_t2) {
			fs_debug_printf( "Destination buffer length was %zu but needed %zu.\n", (dest_len), fsv_t2);
		} else {
			fs_bcm4706_flash_spansion_read_uid(p_ctx, dest, fsv_t2);
			fsv_t3 = fsv_t2;
        }
*/
	} else if (fsv_t1 == NUMONYX_JEDEC_ID) {
		fsv_t2 = 14;
		if (dest_len < fsv_t2) {
			fs_debug_printf( "Destination buffer length was %zu but needed %zu.\n", (dest_len), fsv_t2);
		} else {
			fs_spi_numonyx_read_uid(p_ctx, dest, fsv_t2);
			fsv_t3 = fsv_t2;
		}
	} else if (fsv_t1 == EON_8M_JEDEC_ID) {
		fsv_t2 = (64/8);
		if (dest_len < fsv_t2) {
			fs_debug_printf( "Destination buffer length was %zu but needed %zu.\n", (dest_len), fsv_t2);
		} else {
			fs_bcm4706_flash_eon_read_uid(p_ctx, dest, fsv_t2);
			fsv_t3 = fsv_t2;
		}
	} else if (fsv_t1 == EON_16M_JEDEC_ID) {
		fsv_t2 = (96/8);
		if (dest_len < fsv_t2) {
			fs_debug_printf( "Destination buffer length was %zu but needed %zu.\n", (dest_len), fsv_t2);
		} else {
			fs_bcm4706_flash_eon_read_uid(p_ctx, dest, fsv_t2);
			fsv_t3 = fsv_t2;
		}
	}
	return fsv_t3;
}
#else
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_unifihal_rdid(void);
__FS_FUNCTION_PREFER_INLINE size_t fs_unifihal_read_uid(u_int8_t *dest, size_t dest_len);
#endif
/*
 * fs_read_flash_uid_hw is the main entry point of this file
 *  Flash should have an UID, unique ID,  
 */
__FS_FUNCTION_PREFER_INLINE size_t fs_read_flash_uid_hw(u_int8_t* dest, size_t dest_len) {
	__FS_LOCAL_STATIC_OPTION size_t fsv_t1;
#ifdef __KERNEL__
	__FS_LOCAL_STATIC_OPTION fsctx_t fsv_t2;
#endif
	fsv_t1 = 0;

	FS_LOCK
#ifdef __KERNEL__
	fs_init_fsctx(&fsv_t2);
	if (dest_len < MAX_FLASH_UID_SIZE) {
		fs_low_level_failure(FS_FAILURE_fs_read_flash_uid_hw_1);
	}
    fsv_t1 = fs_bcm4706_flash_read_uid(&fsv_t2, dest, dest_len);
	fs_close_fsctx(&fsv_t2);
#else
	if (dest_len < MAX_FLASH_UID_SIZE) {
		fs_low_level_failure(FS_FAILURE_fs_read_flash_uid_hw_1);
	}
    fsv_t1 = fs_unifihal_read_uid(dest, dest_len);
#endif
	FS_UNLOCK

	return fsv_t1;
}

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_flash_type_id_hw(void) {
	__FS_LOCAL_STATIC_OPTION u_int32_t fsv_t1;
#ifdef __KERNEL__
	__FS_LOCAL_STATIC_OPTION fsctx_t   fsv_t2;
#endif
	fsv_t1 = 0xffffffff;

	FS_LOCK
#ifdef __KERNEL__
	fs_init_fsctx(&fsv_t2);
    fsv_t1 = fs_bcm4706_flash_rdid(&fsv_t2);
	fs_close_fsctx(&fsv_t2);
#else
    fsv_t1 = fs_unifihal_rdid();
#endif
	FS_UNLOCK

	return fsv_t1;
}

#endif // #ifdef UBNT_MIPS_BCM4706
