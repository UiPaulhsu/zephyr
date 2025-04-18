typedef unsigned int fs_spi_register_t;

#define MXIC_MFR_ID                 0xc2
#define MXIC_1M_JEDEC_ID1           0x00c22014
#define MXIC_2M_JEDEC_ID1           0x00c22015
#define MXIC_2M_JEDEC_ID2           0x00c22535
#define MXIC_8M_JEDEC_ID            0x00c22017
#define MXIC_8M_JEDEC_ID1           0x00c22537
#define MXIC_8M_JEDEC_ID2           0x00c22814
#define MXIC_8M_JEDEC_ID3           0x00c22816
#define MXIC_16M_JEDEC_ID           0x00c22018
#define MXIC_32M_JEDEC_ID1          0x00c22019
#define MXIC_32M_JEDEC_ID2          0x00c22539
#define MXIC_32M_JEDEC_ID           MXIC_32M_JEDEC_ID1  /* for backward compatibility */
#define WINBOND_W25X05CL_JEDEC_ID   0x00ef3010
#define WINBOND_8M_JEDEC_ID         0x00ef4017
#define WINBOND_16M_JEDEC_ID        0x00ef4018
#define WINBOND_32M_JEDEC_ID        0x00ef4019
#define NUMONYX_JEDEC_ID            0x0020ba17
#define EON_2M_JEDEC_ID             0x001c7015  /* EN25QH16 */
#define EON_8M_JEDEC_ID             0x001c7017
#define EON_16M_JEDEC_ID            0x001c7018
#define EON_EN25S16_JEDEC_ID        0x001c3815
//#define SPANSION_16M_JEDEC_ID       0x00012018

/* Flash Commands */
#define _FS_CMD_RDSR                      0x05
#define _FS_CMD_FAST_READ                 0x0b
#define _FS_CMD_READ                      0x03
#define _FS_CMD_RDID                      0x9f

#define _FS_CMD_MXIC_ENSO                 0xb1
#define _FS_CMD_MXIC_EXSO                 0xc1
#define _FS_CMD_MXIC_RDSCUR               0x2b
#define _FS_CMD_MXIC_RDSFDP               0x5a

#define _FS_CMD_WINBOND_READ_UID          0x4B
#define _FS_CMD_NUMONYX_EXTENDED_RDID     0x9f
#define _FS_CMD_EON_READ_UID              0x5a

#include "security.flash.target.ARxxxx.inc"
#include "security.flash.target.RTL838x.inc"
#include "security.flash.target.GM81xx.inc"
#include "security.flash.target.CN50xx.inc"
#include "security.flash.target.MT7621.inc"
#include "security.flash.target.MT7623.inc"
#include "security.flash.target.AM18xx.inc"
#include "security.flash.target.AM3xxx.inc"
#include "security.flash.target.BCM111xx.inc"
#include "security.flash.target.A5S.inc"
#include "security.flash.target.S2.inc"
#include "security.flash.target.S2L.inc"
#include "security.flash.target.S2LM.inc"
#include "security.flash.target.S5L.inc"
#include "security.flash.target.S5LM.inc"
#include "security.flash.target.BCM4706.inc"
#include "security.flash.target.QCA851x.inc"
#include "security.flash.target.BCM5334x.inc"
#include "security.flash.target.VSC7514.inc"
#include "security.flash.target.BCM5341x.inc"
#include "security.flash.target.BCM5616x.inc"
#include "security.flash.target.NVRx64.inc"
#include "security.flash.target.STM32F30x.inc"
#include "security.flash.target.IPQ40xx.inc"
#include "security.flash.target.IPQ806x.inc"
#include "security.flash.target.APQ8053.inc"
#include "security.flash.target.AL324.inc"
#include "security.flash.target.IPQ807x.inc"
#include "security.flash.target.EFR32xG13.inc"
#include "security.flash.target.ST50H.inc"
#include "security.flash.target.sim.inc"
#include "security.flash.bitbang.inc"
#include "security.flash.spi.inc"

#ifdef SECURITY_READ_JEDECID_UUID_FROM_UNIFIHAL
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
	size_t len;
	void *data;
	enum flash_op_status  result;
};

#if !defined(__KERNEL__)
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_unifihal_rdid(void) {

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

__FS_FUNCTION_PREFER_INLINE size_t fs_unifihal_read_uid(u_int8_t* dest, size_t dest_len) {
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
#endif // #if !defined(__KERNEL__)

#endif // #ifdef SECURITY_READ_JEDECID_UUID_FROM_UNIFIHAL

#if SECURITY_HAVE_SPI_FLASH_HARDWARE && !SECURITY_HAVE_PROPRIETARY_SPI_CONTROLLER

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

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_spi_mxic_read_lock_capabilities(fsctx_t* p_ctx, u_int8_t chip_select) {
    __FS_LOCAL_STATIC_OPTION u_int8_t fsv_t1[] = { _FS_CMD_MXIC_RDSFDP, 0x0, 0x0, 0x6B, 0x0 };
    __FS_LOCAL_STATIC_OPTION u_int8_t fsv_t2[4];
    __FS_LOCAL_STATIC_OPTION u_int32_t fsv_t3 = 0;

    memset( fsv_t2, 0, sizeof fsv_t2 );
    do {
        _fs_spi_enable_access_and_chip_select(p_ctx, chip_select);
        _fs_spi_write_then_read(p_ctx, chip_select, fsv_t1, sizeof fsv_t1, fsv_t2, sizeof(fsv_t2));
    } while (_fs_spi_check_preempted(p_ctx,chip_select));
    _fs_spi_disable_access_and_chip_select(p_ctx, chip_select);
    fsv_t3 |= fsv_t2[0] << 24;
    fsv_t3 |= fsv_t2[1] << 16;
    fsv_t3 |= fsv_t2[2] << 8;
    fsv_t3 |= fsv_t2[3] << 0;
    return fsv_t3;
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

__FS_FUNCTION_PREFER_INLINE void fs_spi_mxic_read_otp(fsctx_t* p_ctx, u_int8_t chip_select, u_int8_t* dest, size_t bytes_to_read) {
    _fs_spi_mxic_enso(p_ctx, chip_select);
    _fs_spi_mxic_read_otp(p_ctx, chip_select, dest, bytes_to_read);
    _fs_spi_mxic_exso(p_ctx, chip_select);
}

__FS_FUNCTION_PREFER_INLINE void fs_spi_winbond_read_uid(fsctx_t* p_ctx, u_int8_t chip_select, u_int8_t* dest, size_t bytes_to_read) {
    __FS_LOCAL_STATIC_OPTION u_int8_t fsv_t1[] = { _FS_CMD_WINBOND_READ_UID, 0x0, 0x0, 0x0, 0x0 };
    do {
        _fs_spi_enable_access_and_chip_select(p_ctx, chip_select);
        memset( dest, 0, bytes_to_read );
        _fs_spi_write_then_read(p_ctx, chip_select, fsv_t1, sizeof fsv_t1, dest, bytes_to_read);
    } while (_fs_spi_check_preempted(p_ctx,chip_select));
    _fs_spi_disable_access_and_chip_select(p_ctx, chip_select);
}

__FS_FUNCTION_PREFER_INLINE void fs_spi_eon_read_uid(fsctx_t* p_ctx, u_int8_t chip_select, u_int8_t* dest, size_t bytes_to_read) {
    __FS_LOCAL_STATIC_OPTION u_int8_t fsv_t1[] = { _FS_CMD_EON_READ_UID, 0x0, 0x0, 0x80, 0x0 };
    do {
        _fs_spi_enable_access_and_chip_select(p_ctx, chip_select);
        memset( dest, 0, bytes_to_read );
        _fs_spi_write_then_read(p_ctx, chip_select, fsv_t1, sizeof fsv_t1, dest, bytes_to_read);
    } while (_fs_spi_check_preempted(p_ctx,chip_select));
    _fs_spi_disable_access_and_chip_select(p_ctx, chip_select);
}

__FS_FUNCTION_PREFER_INLINE void fs_spi_numonyx_read_uid(fsctx_t* p_ctx, u_int8_t chip_select, u_int8_t* dest, size_t bytes_to_read) {
    __FS_LOCAL_STATIC_OPTION u_int8_t  fsv_t1[] = { _FS_CMD_NUMONYX_EXTENDED_RDID };
    __FS_LOCAL_STATIC_OPTION u_int8_t  fsv_t2[6];
    do {
        _fs_spi_enable_access_and_chip_select(p_ctx, chip_select);
        memset( fsv_t2, 0, sizeof fsv_t2);
        memset( dest, 0, bytes_to_read );
        _fs_spi_write_then_read(p_ctx, chip_select, fsv_t1, sizeof fsv_t1, fsv_t2, sizeof fsv_t2);
        if (fsv_t2[0] == 0x20 && fsv_t2[1] == 0xBA && fsv_t2[2] == 0x17 && fsv_t2[3] == 0x10 && fsv_t2[4] == 0x00 && fsv_t2[5] == 0x00) {
            _fs_spi_write_then_read(p_ctx, chip_select, 0, 0, dest, bytes_to_read);
        }
    } while (_fs_spi_check_preempted(p_ctx,chip_select));
    _fs_spi_disable_access_and_chip_select(p_ctx, chip_select);
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
#if SECURITY_FLASH_HWREV >= SECURITY_FLASH_HWREV_6
        } else if(
                  /* Factory Lock Bit, but not Lockdown Bit */ ((sec & 0x1) == 0x1)
               && /* 1M chip */ (fsv_t1 == MXIC_1M_JEDEC_ID1)
               && /* Factory Lock supported, but not user lockdown bit. */ ((fs_spi_mxic_read_lock_capabilities(p_ctx,chip_select) & 0x3800) == 0x0800))
        {
            if (dest_len < fsv_t2) {
                fs_debug_printf( "Destination buffer length was %zu but needed %zu.\n", (dest_len), fsv_t2);
            } else {
                fs_spi_mxic_read_otp(p_ctx, chip_select, dest, fsv_t2);
                fsv_t3 = fsv_t2;
            }
#endif // #if >= SECURITY_FLASH_HWREV_6
#if SECURITY_FLASH_HWREV >= SECURITY_FLASH_HWREV_2
        } else if((sec & 0x3) == 0) {
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
        // NB: Must remove SPANSION_16M_JEDEC_ID, it is S25FL1-K part and has OTP at cmd 4B instead of ESN!
    } else if (fsv_t1 == WINBOND_W25X05CL_JEDEC_ID || fsv_t1 == WINBOND_8M_JEDEC_ID || fsv_t1 == WINBOND_16M_JEDEC_ID) { // fsv_t1 == WINBOND_32M_JEDEC_ID ||
        fsv_t2 = (64/8);
        if (dest_len < fsv_t2) {
            fs_debug_printf( "Destination buffer length was %zu but needed %zu.\n", (dest_len), fsv_t2);
        } else {
            fs_spi_winbond_read_uid(p_ctx, chip_select, dest, fsv_t2);
            fsv_t3 = fsv_t2;
        }
    } else if (fsv_t1 == NUMONYX_JEDEC_ID) {
        fsv_t2 = 14;
        if (dest_len < fsv_t2) {
            fs_debug_printf( "Destination buffer length was %zu but needed %zu.\n", (dest_len), fsv_t2);
        } else {
            fs_spi_numonyx_read_uid(p_ctx, chip_select, dest, fsv_t2);
            fsv_t3 = fsv_t2;
        }
    } else if (
       fsv_t1 == EON_2M_JEDEC_ID
    || fsv_t1 == EON_8M_JEDEC_ID
    || fsv_t1 == EON_16M_JEDEC_ID
    || fsv_t1 == EON_EN25S16_JEDEC_ID
    ) {
        fsv_t2 = (96/8);
        if (dest_len < fsv_t2) {
            fs_debug_printf( "Destination buffer length was %zu but needed %zu.\n", (dest_len), fsv_t2);
        } else {
            fs_spi_eon_read_uid(p_ctx, chip_select, dest, fsv_t2);
            fsv_t3 = fsv_t2;
        }
    }
    return fsv_t3;
}

/*
 * fs_read_flash_uid_hw is the main entry point of this file
 * fs_read_flash_uid_hw -> fs_read_uid -> fs_spi_rdid
 *                                     |-> fs_spi_winbond_read_uid
 *  Flash should have an UID, unique ID,
 */
__FS_FUNCTION_PREFER_INLINE size_t fs_read_flash_uid_hw(u_int8_t* dest, size_t dest_len) {
    __FS_LOCAL_STATIC_OPTION size_t fsv_t1;
    __FS_LOCAL_STATIC_OPTION fsctx_t fsv_t2;
    fsv_t1 = 0;

    FS_LOCK
    fs_init_fsctx(&fsv_t2);
    if (dest_len < MAX_FLASH_UID_SIZE) {
        fs_low_level_failure(FS_FAILURE_fs_read_flash_uid_hw_1);
    }
    fsv_t1 = fs_read_uid(&fsv_t2, _fs_spi_get_secure_flash_chip_select(), dest, dest_len);
    fs_close_fsctx(&fsv_t2);
    FS_UNLOCK

    return fsv_t1;
}

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_flash_type_id_hw(void) {
    __FS_LOCAL_STATIC_OPTION u_int32_t fsv_t1;
    __FS_LOCAL_STATIC_OPTION fsctx_t   fsv_t2;
    fsv_t1 = 0xffffffff;

    FS_LOCK
    fs_init_fsctx(&fsv_t2);
    fsv_t1 = fs_spi_rdid(&fsv_t2, _fs_spi_get_secure_flash_chip_select());
    fs_close_fsctx(&fsv_t2);
    FS_UNLOCK

    return fsv_t1;
}

__FS_FUNCTION_PREFER_INLINE void fs_read_flash_data(uintptr_t address, u_int8_t* dest, size_t bytes_to_read) {
    __FS_LOCAL_STATIC_OPTION fsctx_t  fsv_t1;
    __FS_LOCAL_STATIC_OPTION u_int8_t fsv_t2[5];
    int chip_select = 0;

    fsv_t2[0] = _FS_CMD_FAST_READ;
    fsv_t2[1] = (address >> 16) & 0xff;
    fsv_t2[2] = (address >> 8) & 0xff;
    fsv_t2[3] = address & 0xff;
    fsv_t2[4] = 0;

    FS_LOCK
        fs_init_fsctx(&fsv_t1);
        do {
            _fs_spi_enable_access_and_chip_select(&fsv_t1, chip_select);
            memset(dest, 0, bytes_to_read);
            _fs_spi_write_then_read(&fsv_t1, chip_select, fsv_t2, sizeof fsv_t2, dest, bytes_to_read);
        } while (_fs_spi_check_preempted(&fsv_t1, chip_select));
        _fs_spi_disable_access_and_chip_select(&fsv_t1, chip_select);
        fs_close_fsctx(&fsv_t1);
    FS_UNLOCK
}
#endif // #ifdef SECURITY_HAVE_SPI_FLASH_HARDWARE && !SECURITY_HAVE_PROPRIETARY_SPI_CONTROLLER

#if SECURITY_ENABLE_SIMULATION || SECURITY_HAVE_SPI_FLASH_HARDWARE
__FS_FUNCTION_PREFER_INLINE size_t fs_read_flash_uid_length_hw(void) {
    __FS_LOCAL_STATIC_OPTION u_int8_t fsv_t1[MAX_FLASH_UID_SIZE];
    return fs_read_flash_uid_hw(fsv_t1, sizeof fsv_t1);
}
__FS_FUNCTION_PREFER_INLINE int fs_is_flash_uid_available(void) {
    return !!fs_read_flash_uid_length_hw();
}
#endif // #if SECURITY_ENABLE_SIMULATION || SECURITY_HAVE_SPI_FLASH_HARDWARE
