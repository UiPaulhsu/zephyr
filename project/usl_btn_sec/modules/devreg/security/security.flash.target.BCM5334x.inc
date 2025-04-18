#ifdef UBNT_ARM_BCM5334x

#if defined(SHOW_WARNINGS)
#warning Must implement fs_bcm5334x_flash_read_uid    
#warning Must implement fs_bcm5334x_flash_rdid
#endif // #if defined(SHOW_WARNINGS)

#define UUID_SIZE 		12
#define MX_IDCODE		0xc2
#define EON_IDCODE 		0x1c

#define RDID_SIZE 		3

#ifdef __KERNEL__
#define SPI_XFER_END    0x02            /* Deassert CS after transfer */

#define NUM_TXRAM        32
#define NUM_RXRAM        32
#define NUM_CDRAM        16

#define MSPI_SPCR0_MSB_BITS_8               (0x00000020)
#define UUID_CMD_SIZE 	5

#define STATE_IDLE          0
#define STATE_RUNNING       1
#define STATE_SHUTDOWN      2

#define MX_UUID_OFFSET 	0x8c
#define EON_UUID_OFFSET 	0x80

#define QSPI_INTR_MSPI_DONE_MASK                    (0x00000020)
#define MAX_RETRY_COUNTS 	10000

extern spinlock_t   *qspi_hw_lock;
extern int 		*qspi_bus_state;
extern int 		*bspi_enabled;

/* MSPI registers */
struct bcm_mspi_hw {
    u32             spcr0_lsb;               /* 0x000 */
    u32             spcr0_msb;               /* 0x004 */
    u32             spcr1_lsb;               /* 0x008 */
    u32             spcr1_msb;               /* 0x00c */
    u32             newqp;                   /* 0x010 */
    u32             endqp;                   /* 0x014 */
    u32             spcr2;                   /* 0x018 */
    u32             reserved0;               /* 0x01c */
    u32             mspi_status;             /* 0x020 */
    u32             cptqp;                   /* 0x024 */
    u32             reserved1[6];            /* 0x028 */
    u32             txram[NUM_TXRAM];        /* 0x040 */
    u32             rxram[NUM_RXRAM];        /* 0x0c0 */
    u32             cdram[NUM_CDRAM];        /* 0x140 */
    u32             write_lock;              /* 0x180 */
    u32             disable_flush_gen;       /* 0x184 */
};

/* BSPI registers */
struct bcm_bspi_hw {
    u32             revision_id;             /* 0x000 */
    u32             scratch;                 /* 0x004 */
    u32             mast_n_boot_ctrl;        /* 0x008 */
    u32             busy_status;             /* 0x00c */
    u32             intr_status;             /* 0x010 */
    u32             b0_status;               /* 0x014 */
    u32             b0_ctrl;                 /* 0x018 */
    u32             b1_status;               /* 0x01c */
    u32             b1_ctrl;                 /* 0x020 */
    u32             strap_override_ctrl;     /* 0x024 */
    u32             flex_mode_enable;        /* 0x028 */
    u32             bits_per_cycle;          /* 0x02C */
    u32             bits_per_phase;          /* 0x030 */
    u32             cmd_and_mode_byte;       /* 0x034 */
    u32             flash_upper_addr_byte;   /* 0x038 */
    u32             xor_value;               /* 0x03C */
    u32             xor_enable;              /* 0x040 */
    u32             pio_mode_enable;         /* 0x044 */
    u32             pio_iodir;               /* 0x048 */
    u32             pio_data;                /* 0x04C */
};

static int mspi_16bit = 0;
static volatile struct bcm_mspi_hw         *mspi_hw = NULL;
static volatile struct bcm_bspi_hw         *bspi_hw = NULL;

/* XXX this may fail. does it need to be covered by the retry logic
 * in do_mspi()?
 */
static inline int bcmspi_disable_bspi(void)
{
	unsigned int delay_time = 1000;

	if (!*bspi_enabled)
		return 0;

    /* Switch to MSPI if not yet */
    if ((bspi_hw->mast_n_boot_ctrl & 1) == 0) {
        while(delay_time) {
            if ((bspi_hw->busy_status & 1) == 0) {
                bspi_hw->mast_n_boot_ctrl = 1;
				*bspi_enabled = 0;
                udelay(1);
                break;
            }
            udelay(1);
			delay_time--;
        }
        if (bspi_hw->mast_n_boot_ctrl != 1) {
            return -1;
        }
    }

    return 0;
}

static inline void bcmspi_enable_bspi(void)
{
	bspi_hw->mast_n_boot_ctrl = 0;
	*bspi_enabled = 1;
}

static inline int mspi_xfer(uint bytes, const u8 *tx, u8 *rx, int end)
{
	unsigned int delay_time = 1000;

    if (bytes & 1) {
        /* Use 8-bit queue for odd-bytes transfer */
        if (mspi_16bit) {
            mspi_hw->spcr0_msb |= MSPI_SPCR0_MSB_BITS_8;
            mspi_16bit = 0;
        }
    } else {
        /* Use 16-bit queue for even-bytes transfer */
        if (!mspi_16bit) {
            mspi_hw->spcr0_msb &= ~MSPI_SPCR0_MSB_BITS_8;
            mspi_16bit = 1;
        }
    }

    while(bytes) {

        unsigned int chunk;
        unsigned int queues;
        unsigned int i;

        /* Separate code for 16bit and 8bit transfers for performance */
        if (mspi_16bit) {

            /* Determine how many bytes to process this time */
			if (bytes > NUM_CDRAM * (mspi_16bit? 2 : 1))
				chunk = NUM_CDRAM * (mspi_16bit? 2 : 1);
			else
				chunk = bytes;

            queues = (chunk - 1) / 2 + 1;
            bytes -= chunk;

            /* Fill CDRAMs */
            for(i=0; i<queues; i++) {
                mspi_hw->cdram[i] = 0xc2;
            }

            /* Fill TXRAMs */
            for(i=0; i<chunk; i++) {
                mspi_hw->txram[i] = tx? tx[i] : 0xff;
            }
        } else {

            /* Determine how many bytes to process this time */
			if (bytes > NUM_CDRAM * (mspi_16bit? 2 : 1))
				chunk = NUM_CDRAM * (mspi_16bit? 2 : 1);
			else
				chunk = bytes;

            queues = chunk;
            bytes -= chunk;

            /* Fill CDRAMs and TXRAMS */
            for(i=0; i<chunk; i++) {
                mspi_hw->cdram[i] = 0x82;
                mspi_hw->txram[i << 1] = tx? tx[i] : 0xff;
            }
        }

        /* Setup queue pointers */
        mspi_hw->newqp = 0;
        mspi_hw->endqp = queues - 1;

        /* Deassert CS if requested and it's the last transfer */
        if (bytes == 0 && end ) {
            mspi_hw->cdram[queues - 1] &= ~0x80;
        }

        /* Kick off */
        mspi_hw->mspi_status = 0;
        mspi_hw->spcr2 = 0xc0;    /* cont | spe */

		while (delay_time) {
			if (mspi_hw->mspi_status & 1)
				break;

			udelay(1);
			delay_time--;
		}

        /* Read data out */
        if (rx) {
            if (mspi_16bit) {
                for(i=0; i<chunk; i++) {
                    rx[i] = mspi_hw->rxram[i] & 0xff;
                }
            } else {
                for(i=0; i<chunk; i++) {
                    rx[i] = mspi_hw->rxram[(i << 1) + 1] & 0xff;
                }
            }
        }

        /* Advance pointers */
        if (tx)
            tx += chunk;
        if (rx)
            rx += chunk;
    }

    return 0;
}

static u32 spcr0_msb = 0;
static u32 newqp = 0;
static u32 endqp = 0;
static u32 txram[NUM_TXRAM] = {0};
static u32 rxram[NUM_RXRAM] = {0};
static u32 cdram[NUM_CDRAM] = {0};

static inline void mspi_save_regs(int save_regs)
{
	int i;

	if (save_regs) {
		spcr0_msb = mspi_hw->spcr0_msb;
		newqp = mspi_hw->newqp;
		endqp = mspi_hw->endqp;
		for (i=0 ; i< NUM_TXRAM; i++) {
			txram[i] = mspi_hw->txram[i];
			rxram[i] = mspi_hw->rxram[i];
			if (i < NUM_CDRAM)
				cdram[i] = mspi_hw->cdram[i];
		}
	}
	else {
		mspi_hw->spcr0_msb = spcr0_msb;
        mspi_hw->newqp = newqp;
        mspi_hw->endqp = endqp;
		for (i=0 ; i< NUM_TXRAM; i++) {
			mspi_hw->txram[i] = txram[i];
			mspi_hw->rxram[i] = rxram[i];
			if (i < NUM_CDRAM)
				mspi_hw->cdram[i] = cdram[i];
		}
	}
}

static inline void bcm_qspi_hw_init(void)
{
	/* BSPI register range */
	bspi_hw = (volatile void *)
	          ioremap(0x18027000, sizeof(struct bcm_bspi_hw));

	/* MSPI register range */
	mspi_hw = (volatile void *)
	          ioremap(0x18027200, sizeof(struct bcm_mspi_hw));
}

/* XXX ideally just change to SECURITY_HAVE_SPI_FLASH_HARDWARE
 *     and implement _fs_spi_write_then_read() etc.
 */
static inline u_int32_t do_mspi(uint tlen, const u8 *tx, uint rlen, u8 *rx)
{
	unsigned long flags = 0;
	u32 spcr2;
	int success = 0;
	u32 retry = MAX_RETRY_COUNTS;
	int bspi_is_enabled = 0;

	if (!qspi_hw_lock) {
		fs_debug_printf("SPI: lock is NULL\n");
		return 0;
	}

	if (!bspi_hw || !mspi_hw) {
		bcm_qspi_hw_init();
		if (!bspi_hw || !mspi_hw) {
			fs_debug_printf("SPI: init failed\n");
			return 0;
		}
	}

	/* NOTE: This is an infinite loop for now. Stress testing (two "devreg
	 * stress" processes plus one process doing MTD read continuously) has
	 * been performed with instrumentation (count number of retries
	 * required). The result shows:
	 *     * No deadlock, corruption, or devreg failure in ~24 hours
	 *       (total number of SPI transactions is >91K).
	 *     * 83% of SPI transactions require 0 retry.
	 *     * 5% of SPI transactions require 1 retry.
	 *     * 9.5% of SPI transactions require 10 retries.
	 *     * 0.6% of SPI transactions require more than 10 retries, but
	 *       no transactions require more than 20.
	 *
	 * We might revisit this and add a limit to the number of retries, for
	 * example in case there is any bug in driver implementation that
	 * might cause the infinite loop to wait forever.
	 */
	while (retry) {
		if (spin_trylock_irqsave(qspi_hw_lock, flags)) {
			if ((*qspi_bus_state == STATE_IDLE)
					&& (bspi_hw->busy_status == 0)
					&& (mspi_hw->write_lock == 0)
					&& (mspi_hw->spcr2 != 0)) {
				spcr2 = mspi_hw->spcr2;
				mspi_hw->spcr2 = 0x0; /* disable interrupt */
				*qspi_bus_state = STATE_RUNNING;

				if (*bspi_enabled)
					bspi_is_enabled = 1;

				if (bcmspi_disable_bspi() != 0) {
					mspi_hw->spcr2 = spcr2; /* enable interrupt */
					*qspi_bus_state = STATE_IDLE;
					fs_debug_printf("devreg: disable_bspi failed !!!\n");
					spin_unlock_irqrestore(qspi_hw_lock, flags);
					break;
				}

				mspi_hw->write_lock = 1;
				mspi_save_regs(1);
				mspi_xfer(tlen, tx, NULL, 0);
				mspi_xfer(rlen, NULL, rx, SPI_XFER_END);
				mspi_save_regs(0);
				mspi_hw->write_lock = 0;

				success = 1;
				if (bspi_is_enabled)
					bcmspi_enable_bspi();

				*qspi_bus_state = STATE_IDLE;
				mspi_hw->spcr2 = spcr2; /* enable interrupt */
			}

			spin_unlock_irqrestore(qspi_hw_lock, flags);
		}

		if (success)
			break;

		retry--;

		udelay(2);
	}

	if (!success) {
		fs_debug_printf("devreg: retry failed !!!\n");
	}

	return ((success) ? rlen : 0);
}
#else /* ifdef __KERNEL__ */
/* nothing for userspace */
#endif /* ifdef __KERNEL__ */

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_flash_type_id_hw(void) {
	unsigned char rdid_rcv[RDID_SIZE] = {0};
#ifdef __KERNEL__
	u8 	rdid_cmd[1] = { 0x9f };

	memset(rdid_rcv, 0, RDID_SIZE);

	if (!do_mspi(1, rdid_cmd, RDID_SIZE, rdid_rcv))
		return 0;

	/* endian is different user space */
	return ((rdid_rcv[0] << 16 | (rdid_rcv[1] << 8 ) | rdid_rcv[2]));
#else /* ifdef __KERNEL__ */
	/* endian is different kernel space */
	{
		__bde_ioctl_t d;
		__ioctl(LUBDE_IPROC_FLASH_ID, &d);

		/* XXX assigning unsigned int into a 3-byte array? */
		*((unsigned int *) rdid_rcv) = d.d1;
	}
	return ((rdid_rcv[2] << 16 | (rdid_rcv[1] << 8) | (rdid_rcv[0])));
#endif /* ifdef __KERNEL__ */
}

__FS_FUNCTION_PREFER_INLINE size_t fs_read_flash_uid_hw(u_int8_t* dest, size_t dest_len) {
	unsigned char rcv_byte;
	u_int32_t fid = fs_read_flash_type_id_hw();
	u_int32_t mid = (fid >> 16) & 0xff;

#ifdef __KERNEL__
	u8 	uuid_cmd[UUID_CMD_SIZE] = { 0x5a, 0x0, 0x0, 0x0, 0x0};

	/* endian is different user space */
	if (mid == MX_IDCODE) {
		uuid_cmd[3] = MX_UUID_OFFSET;
		rcv_byte = UUID_SIZE + 1;
	} else
		return 0;

	if (!do_mspi(UUID_CMD_SIZE, uuid_cmd, rcv_byte, dest))
		return 0;
#else /* ifdef __KERNEL__ */
	/* endian is different kernel space */
	if (mid == MX_IDCODE)
		dest_len = UUID_SIZE + 1;
	else
		dest_len = UUID_SIZE;

	{
		__bde_ioctl_t d;
		d.d1 = dest_len;
		__ioctl(LUBDE_IPROC_FLASH_UID, &d);
		memcpy(dest, d.dx.buf, dest_len);
		if (d.rc != dest_len) {
			rcv_byte = 0;
		} else {
			rcv_byte = d.rc;
		}
	}
#endif /* ifdef __KERNEL__ */
	return rcv_byte;
}

#endif // #ifdef UBNT_ARM_BCM5334x
