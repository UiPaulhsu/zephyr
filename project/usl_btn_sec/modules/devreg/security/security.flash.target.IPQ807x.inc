#ifdef UBNT_ARM64_IPQ807x

#define FLASH_CMD_DEVNAME   "sflash"
#define FLASH_CMD_DEVNUM    200

/* SPI flash command */
#define SPI_FLASH_IOCTL_READ_ID     _IOR(FLASH_CMD_DEVNUM, 0, char *)
#define SPI_FLASH_IOCTL_READ_UID    _IOR(FLASH_CMD_DEVNUM, 1, char *)

enum flash_op_status {
    FLASH_OP_SUCCESS = 0,
    FLASH_OP_FAILED = 1,
};

struct spi_flash_cmd_opt {
    size_t          len;
    void            *data;
    enum flash_op_status  result;
};


/*
   SPI controller for Qualcomm AP160/AP161 based systme.
   Qualcomm document: 80-Y6477-15_IPQ806X GSBI INTERFACE PROGRAMMING REFERENCE

   IPQ4018/IPQ4019/IPQ4028/IPQ4029 GCC Registers Reference Manual
   Qualcomm document: 80-Y9349-5BX Rev. A
*/

#define _FS_SPI_CS0  39

/* QUP */
#define _FS_QUP_BASE                  0x78b5000
#define _FS_QUP_SIZE                  0x600
#define QUP_OUTPUT_FIFO_SIZE          16

/* Register offsets */
#define QUP_CONFIG                    0x00000000
#define QUP_STATE                     0x00000004
#define QUP_IO_MODES                  0x00000008
#define QUP_SW_RESET                  0x0000000C
#define QUP_OPERATIONAL               0x00000018
#define QUP_OPERATIONAL_MASK          0x00000028
#define QUP_MX_OUTPUT_COUNT           0x00000100
#define QUP_OUTPUT_FIFO               0x00000110
#define QUP_MX_WRITE_COUNT            0x00000150
#define QUP_MX_INPUT_COUNT            0x00000200
#define QUP_MX_READ_COUNT             0x00000208
#define QUP_INPUT_FIFO                0x00000218
#define SPI_CONFIG                    0x00000300
#define SPI_IO_CONTROL                0x00000304

/*QUP_CONFIG fields */
#define QUP_CFG_MINI_CORE_SPI         0x00000100
#define QUP_CFG_N_8                   0x00000007

/*QUP_STATE fields */
#define QUP_STATE_MASK                0x00000003
#define QUP_STATE_RESET               0x00000000
#define QUP_STATE_RUN                 0x00000001
#define QUP_STATE_PAUSE               0x00000003
#define QUP_STATE_VALID               0x00000004

/* QUP_IO_MODES fields */
#define QUP_IO_MODE_PACK_EN           0x00008000
#define QUP_IO_MODE_UNPACK_EN         0x00004000
#define QUP_IO_MODE_INPUT_MODE        0x00003000
#define QUP_IO_MODE_OUTPUT_MODE       0x00000C00
#define QUP_IO_MODE_INPUT_FIFO_SIZE   0x00000380
#define QUP_IO_MODE_INPUT_BLOCK_SIZE  0x00000060
#define QUP_IO_MODE_OUTPUT_FIFO_SIZE  0x0000001C
#define QUP_IO_MODE_OUTPUT_BLOCK_SIZE 0x00000003

#define QUP_IO_MODE_FIFO              0
#define QUP_IO_MODE_OUTPUT_MODE_SHIFT 10
#define QUP_IO_MODE_INPUT_MODE_SHIFT  12

/* QUP_OPERATIONAL fields */
#define QUP_OP_MAX_INPUT_DONE_FLAG    0x00000800
#define QUP_OP_MAX_OUTPUT_DONE_FLAG   0x00000400
#define QUP_OP_INPUT_SERVICE_FLAG     0x00000200
#define QUP_OP_OUTPUT_SERVICE_FLAG    0x00000100
#define QUP_OP_INPUT_FIFO_FULL        0x00000080
#define QUP_OP_OUTPUT_FIFO_FULL       0x00000040
#define QUP_OP_INPUT_FIFO_NOT_EMPTY   0x00000020
#define QUP_OP_OUPUT_FIFO_NOT_EMPTY   0x00000010

/* SPI_CONFIG fields */
#define SPI_CFG_INPUT_FIRST           0x00000200

#define LOCAL_BUF_SIZE 64

#ifdef __KERNEL__

extern int ubnt_lock_nor_flash(int debug_info);
extern int ubnt_unlock_nor_flash(int debug_info);
#define _fs_udelay unifi_system_udelay

#define DEBUG_LOCK_NOR_FLASH 0
#define LOCK_NOR_FLASH     do { ubnt_lock_nor_flash( DEBUG_LOCK_NOR_FLASH ); } while(0);
#define UNLOCK_NOR_FLASH   do { ubnt_unlock_nor_flash( DEBUG_LOCK_NOR_FLASH ); } while(0);

typedef struct fsctx {
    volatile void __iomem * iomapping_qup;
    u_int32_t cur_iface_clk_ns;
} fsctx_t;

__FS_FUNCTION_PREFER_INLINE u_int32_t read_reg( volatile void __iomem *addr) {
    return readl_relaxed((volatile void __iomem *)addr);
}

__FS_FUNCTION_PREFER_INLINE void write_reg( u_int32_t val, volatile void __iomem *addr) {
    writel_relaxed(val, (volatile void __iomem *)addr);
}

__FS_FUNCTION_PREFER_INLINE int set_qup_state(
    u_int64_t qup_addr_base,
    u_int32_t state
    )
{
    u_int32_t reg_value;
    u_int32_t loop_count;

    reg_value = read_reg(qup_addr_base + QUP_STATE);
    reg_value = (reg_value & ~QUP_STATE_MASK) | state;
    write_reg(reg_value, qup_addr_base + QUP_STATE);
    loop_count = 0;
    while(loop_count < 1000) {
        loop_count ++;
        reg_value = read_reg(qup_addr_base + QUP_STATE);
        if (reg_value & QUP_STATE_VALID) {
            return 0;
        }
        _fs_udelay(2);
    }
    fs_debug_printf("set_qup_state, wait valid state timeout.\n");
    return -1;
}

__FS_FUNCTION_PREFER_INLINE int prepare_transfer(
    fsctx_t* p_ctx,
    u_int64_t qup_addr_base,
    u_int32_t read_count
    )
{
    u_int32_t reg_value;

    set_qup_state(qup_addr_base, QUP_STATE_RESET);

    //write a bigger value to prevent interrupt from triggering
    write_reg(read_count+2, qup_addr_base + QUP_MX_READ_COUNT);
    write_reg(read_count+2, qup_addr_base + QUP_MX_WRITE_COUNT);
    write_reg(0, qup_addr_base + QUP_MX_INPUT_COUNT);
    write_reg(0, qup_addr_base + QUP_MX_OUTPUT_COUNT);

    //QUP_IO_MODES
    reg_value = read_reg(qup_addr_base + QUP_IO_MODES);
    reg_value &= ~(QUP_IO_MODE_INPUT_MODE | QUP_IO_MODE_OUTPUT_MODE);
    reg_value = (reg_value | (QUP_IO_MODE_FIFO << QUP_IO_MODE_OUTPUT_MODE_SHIFT));
    reg_value = (reg_value | (QUP_IO_MODE_FIFO << QUP_IO_MODE_INPUT_MODE_SHIFT));
    reg_value &= ~(QUP_IO_MODE_PACK_EN | QUP_IO_MODE_UNPACK_EN);
    write_reg(reg_value, qup_addr_base + QUP_IO_MODES);

    //SPI_CONFIG
    reg_value = SPI_CFG_INPUT_FIRST;
    write_reg(reg_value, qup_addr_base + SPI_CONFIG);
    reg_value = QUP_CFG_MINI_CORE_SPI | QUP_CFG_N_8;
    write_reg(reg_value, qup_addr_base + QUP_CONFIG);

    write_reg(0, qup_addr_base + QUP_OPERATIONAL_MASK);

    set_qup_state(qup_addr_base, QUP_STATE_RUN);
    set_qup_state(qup_addr_base, QUP_STATE_PAUSE);

    return 0;
}

__FS_FUNCTION_PREFER_INLINE void cleanup_transfer(
    fsctx_t* p_ctx, u_int64_t qup_addr_base)
{
    set_qup_state(qup_addr_base, QUP_STATE_RESET);
}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_write_then_read(
    fsctx_t* p_ctx,
    __ATTRIB_UNUSED u_int8_t chip_select,
    u_int8_t* tx_buf,
    size_t tx_len,
    u_int8_t* rx_buf,
    size_t rx_len)
{
    u_int64_t qup_addr_base;
    u_int32_t reg_value;
    u_int8_t  data_buf[LOCAL_BUF_SIZE];
    u_int32_t i, loop_count, bytes_sent, bytes_to_send;
    u_int32_t read_count = tx_len+rx_len;
    int ret;

    if(read_count >= LOCAL_BUF_SIZE) {
        fs_debug_printf("read_count(%d) too big.\n", read_count);
        return;
    }

    memcpy(data_buf, tx_buf, tx_len);

    qup_addr_base = (u_int64_t __force)p_ctx->iomapping_qup;

    if (qup_addr_base == 0) {
        fs_debug_printf("invalid spi address: 0x%x\n", qup_addr_base);
        return;
    }

    LOCK_NOR_FLASH

    ret = prepare_transfer(p_ctx, qup_addr_base, read_count);
    if ( ret ) {
        fs_debug_printf("_fs_spi_write_then_read, prepare_transfer failed.\n");
        goto spi_done; //DO NOT use return here, need to unlock SPI
    }

    /* Chip select */
    reg_value = read_reg(qup_addr_base + SPI_IO_CONTROL);
    reg_value |= (1 << 11);
    write_reg(reg_value, qup_addr_base + SPI_IO_CONTROL);

    // write to output buffer
    bytes_to_send = read_count;
    if ( bytes_to_send > QUP_OUTPUT_FIFO_SIZE ) {
        bytes_to_send = QUP_OUTPUT_FIFO_SIZE;
    }
    for (i = 0; i < bytes_to_send; i++) {
        reg_value = (data_buf[i] << 24) & 0xFF000000;
        write_reg(reg_value, qup_addr_base + QUP_OUTPUT_FIFO);
    }
    bytes_sent = bytes_to_send;

    // kick start h/w by writing QUP_STATE_RUN
    ret = set_qup_state(qup_addr_base, QUP_STATE_RUN);

    if ( ret ) {
        fs_debug_printf("_fs_spi_write_then_read, no valid state detected after QUP_STATE_RUN.\n");
        goto spi_done; //DO NOT use return here, need to unlock SPI
    }

    // read/write FIFO
    i = 0;
    while ( i < read_count) {
        loop_count = 0;
        while ( 1) {
            reg_value = read_reg(qup_addr_base + QUP_OPERATIONAL);
            if (reg_value & QUP_OP_INPUT_FIFO_NOT_EMPTY ) {
                break;
            } else {
                _fs_udelay(2);
            }
            if( loop_count++ > 1000) {
                break;
            }
        }
        if (loop_count < 1000) {
            reg_value = read_reg(qup_addr_base + QUP_INPUT_FIFO);
            data_buf[i] = reg_value & 0xFF;
            i++;

            if ( bytes_sent < read_count ) {
                reg_value = (data_buf[bytes_sent++] << 24) & 0xFF000000;
                write_reg(reg_value, qup_addr_base + QUP_OUTPUT_FIFO);
            }
        } else {
            fs_debug_printf("_fs_spi_write_then_read, Read timeout.\n");
            break;
        }
    }

    memcpy(rx_buf, &data_buf[tx_len], rx_len);

spi_done:
    /* Chip select */
    reg_value = read_reg(qup_addr_base + SPI_IO_CONTROL);
    reg_value &= ~(1 << 11);
    write_reg(reg_value, qup_addr_base + SPI_IO_CONTROL);

    cleanup_transfer(p_ctx, qup_addr_base);
    UNLOCK_NOR_FLASH
}

__FS_FUNCTION_PREFER_INLINE void fs_close_fsctx(fsctx_t* p_ctx) {
    if(p_ctx != NULL) {
        if (p_ctx->iomapping_qup != NULL) {
            iounmap(p_ctx->iomapping_qup);
            p_ctx->iomapping_qup = NULL;
        }
    }
    return;
}

__FS_FUNCTION_PREFER_INLINE void fs_init_fsctx(fsctx_t* p_ctx) {
    if(p_ctx == NULL) {
        return;
    }

    memset( p_ctx, 0, sizeof(fsctx_t) );

    p_ctx->iomapping_qup = ioremap_nocache(_FS_QUP_BASE, _FS_QUP_SIZE);
    if (p_ctx->iomapping_qup == NULL) {
        fs_debug_printf("Failed ioremapping SPI.");
        fs_close_fsctx( p_ctx );
        return;
    }
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE u_int8_t _fs_spi_get_secure_flash_chip_select(void) {
    return _FS_SPI_CS0; /* CS0 */
}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_enable_access_and_chip_select(__attribute__((unused)) fsctx_t* p_ctx, __attribute__((unused)) u_int8_t chip_select) {
    /* enable access and chip select is done in read-and-write function */
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE int _fs_spi_check_preempted(__attribute__((unused)) fsctx_t* p_ctx, __ATTRIB_UNUSED u_int8_t chip_select) {
    /* function not used */
    return 0;
}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_disable_access_and_chip_select(__attribute__((unused)) fsctx_t* p_ctx, __ATTRIB_UNUSED u_int8_t chip_select) {
    /* enable access and chip select is done in read-and-write function */
}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_mxic_read_otp(fsctx_t* p_ctx, u_int8_t chip_select, u_int8_t* dest, size_t bytes_to_read) {
    __FS_LOCAL_STATIC_OPTION u_int8_t fsv_t1[] = { _FS_CMD_FAST_READ, 0x0, 0x0, 0x0, 0x0 };
    do {
        memset( dest, 0, bytes_to_read );
        _fs_spi_enable_access_and_chip_select(p_ctx, chip_select);
        _fs_spi_write_then_read(p_ctx, chip_select, fsv_t1, sizeof fsv_t1, dest, bytes_to_read);
    } while (_fs_spi_check_preempted(p_ctx, chip_select));
    _fs_spi_disable_access_and_chip_select(p_ctx, chip_select);
}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_mxic_enso(fsctx_t* p_ctx, u_int8_t chip_select) {
    __FS_LOCAL_STATIC_OPTION u_int8_t fsv_t1[] = { _FS_CMD_MXIC_ENSO };
    do {
        _fs_spi_enable_access_and_chip_select(p_ctx, chip_select);
        _fs_spi_write_then_read(p_ctx, chip_select, fsv_t1, sizeof fsv_t1, 0, 0);
    } while (_fs_spi_check_preempted(p_ctx, chip_select));
    _fs_spi_disable_access_and_chip_select(p_ctx, chip_select);
}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_mxic_exso(fsctx_t* p_ctx, u_int8_t chip_select) {
    __FS_LOCAL_STATIC_OPTION u_int8_t fsv_t1[] = { _FS_CMD_MXIC_EXSO };
    do {
        _fs_spi_enable_access_and_chip_select(p_ctx, chip_select);
        _fs_spi_write_then_read(p_ctx, chip_select, fsv_t1, sizeof fsv_t1, 0, 0);
    } while (_fs_spi_check_preempted(p_ctx, chip_select));
    _fs_spi_disable_access_and_chip_select(p_ctx, chip_select);
}

__FS_FUNCTION_PREFER_INLINE u_int8_t fs_spi_mxic_rdscur(fsctx_t* p_ctx, u_int8_t chip_select) {
    __FS_LOCAL_STATIC_OPTION u_int8_t fsv_t1[] = { _FS_CMD_MXIC_RDSCUR };
    __FS_LOCAL_STATIC_OPTION u_int8_t fsv_t2[] = { 0x0 };
    do {
        memset(fsv_t2, 0, sizeof fsv_t2);
        _fs_spi_enable_access_and_chip_select(p_ctx, chip_select);
        _fs_spi_write_then_read(p_ctx, chip_select, fsv_t1, sizeof fsv_t1, fsv_t2, sizeof fsv_t2);
    } while (_fs_spi_check_preempted(p_ctx, chip_select));
    _fs_spi_disable_access_and_chip_select(p_ctx, chip_select);
    return fsv_t2[0];
}

__FS_FUNCTION_PREFER_INLINE void fs_spi_mxic_read_otp(fsctx_t* p_ctx, u_int8_t chip_select, u_int8_t* dest, size_t bytes_to_read) {
    _fs_spi_mxic_enso(p_ctx, chip_select);
    _fs_spi_mxic_read_otp(p_ctx, chip_select, dest, bytes_to_read);
    _fs_spi_mxic_exso(p_ctx, chip_select);
}

__FS_FUNCTION_PREFER_INLINE void fs_spi_mxic_read_uid_from_sfdp(fsctx_t* p_ctx, u_int8_t chip_select, u_int8_t* dest, size_t bytes_to_read) {
    __FS_LOCAL_STATIC_OPTION u_int8_t fsv_t1[] = { _FS_CMD_MXIC_RDSFDP, 0x0, 0x0, 0x8c, 0x0 };
    do {
        _fs_spi_enable_access_and_chip_select(p_ctx, chip_select);
        memset( dest, 0, bytes_to_read );
        _fs_spi_write_then_read(p_ctx, chip_select, fsv_t1, sizeof fsv_t1, dest, bytes_to_read);
    } while (_fs_spi_check_preempted(p_ctx,chip_select));
    _fs_spi_disable_access_and_chip_select(p_ctx, chip_select);
}

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_spi_rdid(fsctx_t* p_ctx, u_int8_t chip_select) {
    __FS_LOCAL_STATIC_OPTION u_int8_t fsv_t1[] = { _FS_CMD_RDID };
    __FS_LOCAL_STATIC_OPTION u_int8_t fsv_t2[] = { 0x0, 0x0, 0x0 };
    __FS_LOCAL_STATIC_OPTION u_int32_t fsv_t3;

    fsv_t3 = 0;
    do {
        memset(fsv_t2, 0, sizeof fsv_t2);
        _fs_spi_enable_access_and_chip_select(p_ctx, chip_select);
        _fs_spi_write_then_read(p_ctx, chip_select, fsv_t1, sizeof fsv_t1, fsv_t2, sizeof fsv_t2);
        fsv_t3 |= fsv_t2[0] << 16;
        fsv_t3 |= fsv_t2[1] << 8;
        fsv_t3 |= fsv_t2[2] << 0;
    } while (_fs_spi_check_preempted(p_ctx,chip_select));
    _fs_spi_disable_access_and_chip_select(p_ctx, chip_select);
    return fsv_t3;
}

__FS_FUNCTION_PREFER_INLINE size_t fs_read_uid(fsctx_t* p_ctx, u_int8_t chip_select, u_int8_t* dest, size_t dest_len) {
    __FS_LOCAL_STATIC_OPTION u_int32_t fsv_t1;
    __FS_LOCAL_STATIC_OPTION size_t    fsv_t2;
    __FS_LOCAL_STATIC_OPTION size_t    fsv_t3;
    fsv_t1 = 0;
    fsv_t2 = 0;
    fsv_t3 = 0;
    memset( dest, 0xff, dest_len);

    fsv_t1 = fs_spi_rdid(p_ctx, chip_select);
    if (0
        || fsv_t1 == MXIC_8M_JEDEC_ID
#if SECURITY_FLASH_HWREV >= SECURITY_FLASH_HWREV_2
        || fsv_t1 == MXIC_16M_JEDEC_ID
#endif
#if SECURITY_FLASH_HWREV >= SECURITY_FLASH_HWREV_3
        || fsv_t1 == MXIC_32M_JEDEC_ID1
#endif
#if SECURITY_FLASH_HWREV >= SECURITY_FLASH_HWREV_4
        || fsv_t1 == MXIC_2M_JEDEC_ID1
        || fsv_t1 == MXIC_2M_JEDEC_ID2
#endif
#if SECURITY_FLASH_HWREV >= SECURITY_FLASH_HWREV_5
        || fsv_t1 == MXIC_1M_JEDEC_ID1
#endif
#if SECURITY_FLASH_HWREV >= SECURITY_FLASH_HWREV_7
        || fsv_t1 == MXIC_32M_JEDEC_ID2
#endif
#if SECURITY_FLASH_HWREV >= SECURITY_FLASH_HWREV_8
        || fsv_t1 == MXIC_8M_JEDEC_ID1
#endif
        ) {
        u_int8_t sec = 0;
        fsv_t2 = (512/8);
        sec = fs_spi_mxic_rdscur(p_ctx, chip_select);
        if ((sec & 0x3) == 0x3) {
            if (dest_len < fsv_t2) {
                fs_debug_printf( "Destination buffer length was %zu but needed %zu.\n", (dest_len), fsv_t2);
            } else {
                fs_spi_mxic_read_otp(p_ctx, chip_select, dest, fsv_t2);
                fsv_t3 = fsv_t2;
            }
#if SECURITY_FLASH_HWREV >= SECURITY_FLASH_HWREV_2
        } else if(sec == 0) {
            fsv_t2 = 13;
            if (dest_len < fsv_t2) {
                fs_debug_printf( "Destination buffer length was %zu but needed %zu.\n", (dest_len), fsv_t2);
            } else {
                // 0x8C to 0x98 (140-152)
                fs_spi_mxic_read_uid_from_sfdp(p_ctx, chip_select, dest, fsv_t2);
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
    }
    return fsv_t3;
}

#else  /* #ifdef __KERNEL__ */
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_spi_rdid(void) {

    struct spi_flash_cmd_opt spi_flash;
    int fd;
    u_int32_t id;

    spi_flash.len = sizeof(id);
    spi_flash.data = (void *)(&id);
    spi_flash.result = FLASH_OP_FAILED;

    fd = open("/dev/"FLASH_CMD_DEVNAME, O_RDONLY);
    if (fd < 0) {
        return 0;
    }

    if (ioctl(fd, SPI_FLASH_IOCTL_READ_ID, &spi_flash) < 0) {
        close(fd);
        return 0;
    }

    close(fd);

    if (spi_flash.result != FLASH_OP_SUCCESS) {
        return 0;
    }

    return id;
}

__FS_FUNCTION_PREFER_INLINE size_t fs_read_uid(u_int8_t* dest, size_t dest_len) {
    uint8_t uid[MAX_FLASH_UID_SIZE];
    struct spi_flash_cmd_opt spi_flash;
    int fd;

    spi_flash.len   = sizeof(uid);
    spi_flash.data  = (void *)uid;
    spi_flash.result = FLASH_OP_FAILED;

    fd = open("/dev/"FLASH_CMD_DEVNAME, O_RDONLY);

    if (fd < 0) {
        return 0;
    }

    if (ioctl(fd, SPI_FLASH_IOCTL_READ_UID, &spi_flash) < 0) {
        close(fd);
        return 0;
    }

    close(fd);

    if (spi_flash.result != FLASH_OP_SUCCESS) {
        return 0;
    }

    if (spi_flash.len > dest_len) {
        return 0;
    }

    memcpy(dest, uid, spi_flash.len);
    return spi_flash.len;
}

#endif /* #ifdef __KERNEL__ */

/*
 * fs_read_flash_uid_hw is the main entry point of this file
 * fs_read_flash_uid_hw -> fs_read_uid -> fs_spi_rdid
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
    fsv_t1 = fs_read_uid(&fsv_t2, _fs_spi_get_secure_flash_chip_select(), dest, dest_len);
    fs_close_fsctx(&fsv_t2);
#else  /* #ifdef __KERNEL__ */
    if (dest_len < MAX_FLASH_UID_SIZE) {
        fs_low_level_failure(FS_FAILURE_fs_read_flash_uid_hw_1);
    }
    fsv_t1 = fs_read_uid(dest, dest_len);
#endif /* #ifdef __KERNEL__ */
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
    fsv_t1 = fs_spi_rdid(&fsv_t2, _fs_spi_get_secure_flash_chip_select());
    fs_close_fsctx(&fsv_t2);
#else  /* #ifdef __KERNEL__ */
    fsv_t1 = fs_spi_rdid();
#endif /* #ifdef __KERNEL__ */
    FS_UNLOCK

    return fsv_t1;
}

#endif /* #ifdef UBNT_ARM64_IPQ807x */
