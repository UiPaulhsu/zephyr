#ifdef UBNT_MIPS_CN50xx
#ifdef __KERNEL__
#include <linux/sched.h>
#endif /* __KERNEL__ */

typedef struct fsctx {
} fsctx_t;

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void _fs_spi_disable_access_and_chip_select(__ATTRIB_UNUSED fsctx_t* p_ctx, __ATTRIB_UNUSED u_int8_t chip_select) {}
__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void _fs_spi_enable_access_and_chip_select(__ATTRIB_UNUSED fsctx_t* p_ctx, __ATTRIB_UNUSED u_int8_t chip_select) {}
__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE int  _fs_spi_check_preempted(__ATTRIB_UNUSED fsctx_t* p_ctx, __ATTRIB_UNUSED u_int8_t chip_select) { return 0;}

typedef union spi_dat {
	uint64_t u64;
	struct spi_dat_s {
		uint64_t reserved : 56;
		uint64_t data     : 8;
	} s;
} spi_dat_t;

typedef union spi_tx {
	uint64_t u64;
	struct spi_tx_s {
		uint64_t reserved_17_63 : 47;
		uint64_t leavecs        : 1;
		uint64_t reserved_13_15 : 3;
		uint64_t txnum          : 5;
		uint64_t reserved_5_7   : 3;
		uint64_t totnum         : 5;
	} s;
} spi_tx_t;

typedef union spi_sts {
	uint64_t u64;
	struct spi_sts_s {
		uint64_t reserved_13_63 : 51;
		uint64_t rxnum          : 5;
		uint64_t reserved_1_7   : 7;
		uint64_t busy           : 1;
	} s;
} spi_sts_t;

#define SPI_DAT_BASE 0x8001070000001080ull
#define SPI_TX       0x8001070000001010ull
#define SPI_STS      0x8001070000001008ull

static inline void _spi_rw(int l_cs, uint8_t *dtx, int n_tx,
			   uint8_t *drx, int n_rx)
{
	int j;
	int n_tot = n_tx + n_rx;
	spi_dat_t dat;
	spi_tx_t tx;
	spi_sts_t sts;

	if (n_tot > 9) {
		fs_debug_printf("Invalid length for SPI transaction\n");
		return;
	}

	for (j = 0; j < n_tx; j++) {
		dat.u64 = 0;
		dat.s.data = dtx[j];
		CN50xx_write_csr((SPI_DAT_BASE + (j * 8)), dat.u64);
	}

	tx.u64 = 0;
	tx.s.txnum = n_tx;
	tx.s.totnum = n_tot;
	tx.s.leavecs = l_cs;
	CN50xx_write_csr(SPI_TX, tx.u64);

	for (j = 0; j < 20; j++) {
#ifdef __KERNEL__
		yield();
#else /* !__KERNEL__ */
		sched_yield();
#endif /* __KERNEL__ */

		sts.u64 = CN50xx_read_csr(SPI_STS);
		if (!sts.s.busy) {
			break;
		}
	}
	if (j == 20) {
		fs_debug_printf("SPI transaction timed out\n");
	} else {
		int i;
		for (j = 0, i = n_tx; j < n_rx; j++, i++) {
			dat.u64 = CN50xx_read_csr((SPI_DAT_BASE + (i * 8)));
			drx[j] = dat.s.data;
		}
	}
}

__FS_FUNCTION_PREFER_INLINE void _fs_spi_write_then_read(__ATTRIB_UNUSED fsctx_t* p_ctx, __ATTRIB_UNUSED u_int8_t chip_select, u_int8_t* tx, size_t tx_len, u_int8_t* rx, size_t rx_len) {
	int rem = tx_len;
	int idx = 0, w, r, cs;

	if ((tx_len + rx_len) <= 9) {
		_spi_rw(0, tx, tx_len, rx, rx_len);
		return;
	}

	while (rem > 0) {
		w = (rem > 9) ? 9 : rem;
		cs = (rem > 9 || rx_len > 0) ? 1 : 0;
		_spi_rw(cs, &(tx[idx]), w, NULL, 0);
		rem -= 9;
		idx += 9;
	}

	rem = rx_len;
	idx = 0;
	while (rem > 0) {
		r = (rem > 9) ? 9 : rem;
		cs = (rem > 9) ? 1 : 0;
		_spi_rw(cs, NULL, 0, &(rx[idx]), r);
		rem -= 9;
		idx += 9;
	}
}

__FS_FUNCTION_PREFER_INLINE void fs_init_fsctx(__ATTRIB_UNUSED fsctx_t* p_ctx) {}

__FS_FUNCTION_PREFER_INLINE void fs_close_fsctx(__ATTRIB_UNUSED fsctx_t* p_ctx) {}

#endif // #ifdef UBNT_MIPS_CN50xx
