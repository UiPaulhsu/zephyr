#ifdef UBNT_MIPS_VSC7514

#define UUID_SIZE 		12
#define MX_IDCODE		0xc2
#define RDID_SIZE 		3

#ifdef __KERNEL__
#define UUID_CMD_SIZE 	5
#define MX_UUID_OFFSET 	0x8c

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <asm/vcoreiii.h>
#else
#include <stdlib.h>             
#include <stdio.h>             
#include <string.h>           
#include <sys/ioctl.h>
#include <fcntl.h>
#include <getopt.h>
#endif

#ifndef __INC_SPI_FLASH_API__

#define FLASH_CMD_DEVNAME		"sflash"
#define FLASH_CMD_DEVNUM		200

/* SPI flash command */
#define SPI_FLASH_IOCTL_READ_ID		(0x01)
#define SPI_FLASH_IOCTL_READ_UID	(0x02)
#define SPI_FLASH_IOCTL_READ_SA		(0x03)

enum op_status {
	FLASH_OP_SUCCESS = 0,
	FLASH_OP_FAILED = 1,
};

struct spi_flash_cmd_opt {
	size_t len;
	void *data;
	enum op_status  result;
};

struct nand_spi_flash_cmd_opt {
	unsigned char   *id;
	enum op_status  result;
};

#ifdef __KERNEL__
extern void vsc7514_spi_lock(void);
extern void vsc7514_spi_unlock(void);

#define DELAY() while(0) {};

static u8 cs_active = 0;
static u8 cs_active_high = 1;
static u8 init_clk_high = 0;

static int orig_sw_mode = -1;
static int orig_genl_ctrl = -1;

static inline void spi_registers_reset(void)
{
    int set_owner = 0;

    // backup original values
    orig_sw_mode = readl(VTSS_ICPU_CFG_SPI_MST_SW_MODE); 
    orig_genl_ctrl = readl(VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL); 
    // reset SW_MODE
    writel(0, VTSS_ICPU_CFG_SPI_MST_SW_MODE);

    // clear onwer bits
    set_owner = (orig_genl_ctrl &~ VTSS_M_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_IF_SI_OWNER);
    // set onwer bit 1
    set_owner |= VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_IF_SI_OWNER(1);

    writel(set_owner, VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL);
    mmiowb();
    return;
}

static inline void spi_registers_restore(void)
{
    // restore original values
    if (orig_sw_mode != -1)
        writel(orig_sw_mode, VTSS_ICPU_CFG_SPI_MST_SW_MODE);
    if (orig_genl_ctrl != -1)
        writel(orig_genl_ctrl, VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL);
    mmiowb();
    return;
}

static inline void spi_cs_assert(void)
{
    u32 value;

    if (cs_active) {
        return;
    }

    /* Enable bitbang, SCK_OE, SDO_OE */
    value = (VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_PIN_CTRL_MODE| /* SW Bitbang */
             VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SDO|       /* DO */
             VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SCK_OE|    /* SCK_OE */
             VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SDO_OE);   /* SDO OE */

    /* Add CS */ 
    value |= VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_CS_OE(VTSS_BIT(0)); /* CS_OE = 1, but don't chip-select */
    if (cs_active_high) {
        // Don't chip-select
        value |= VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_CS(VTSS_BIT(0));
    }

    /* Clock polarity */
    if (init_clk_high) {
        value |= VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SCK;
    }

    /* Enable the CS in HW */
    writel(value, VTSS_ICPU_CFG_SPI_MST_SW_MODE);
    mmiowb();

    /* CS now active */
    cs_active = 1;
}

static inline void spi_transfer(u32 data_size, const u8 *tx_data, u8 *rx_data)
{
    u32 i, svalue, sw_mode;

    svalue =
        VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SCK_OE    | /* SCK_OE */
        VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SDO_OE    | /* SDO OE */
        VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_PIN_CTRL_MODE;  /* SW Bitbang */

    // Preserve current CS_OE/CS    
    sw_mode = readl(VTSS_ICPU_CFG_SPI_MST_SW_MODE);
    
    svalue |= (sw_mode &
               (VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_CS_OE| VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_CS)) |
              VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SDO;    // Tick with DO high

    for (i = 0; i < data_size; i++) {
        u32 rx = 0, mask = 0x80, value;
        while (mask) {
            // Initial condition: CLK is low.
            value = svalue;
            if (tx_data[i] & mask) {
                value |= VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SDO;
            } else {
                value &= ~VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SDO;
	    }

            // Drive data while taking CLK low. The device we're accessing will
            // sample on the following rising edge and will output data on this edge for us
            // to be sampled at the end of this loop.
            writel(value & ~VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SCK, VTSS_ICPU_CFG_SPI_MST_SW_MODE);
            mmiowb();

            // Wait for t_setup. All devices do have a setup-time, so we always insert some
            // delay here. Some devices have a very long setup-time, which can be adjusted by
            // the user through vcoreiii_device->delay.
            DELAY();

            // Drive the clock high.
            writel(value | VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SCK , VTSS_ICPU_CFG_SPI_MST_SW_MODE);
            mmiowb();

            // Wait for t_hold. See comment about t_setup above.
            DELAY();

            // We sample as close to the next falling edge as possible
            value = readl(VTSS_ICPU_CFG_SPI_MST_SW_MODE);
            if (value & VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SDI) {
                rx |= mask;
            }
            mask >>= 1;
        }
        if (rx_data) {
            rx_data[i] = (u8)rx;
        }
    }
}

static inline void spi_cs_drop(void)
{
        u32 clk_value = VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SCK;
        u32 cs_value, value;

        cs_value = VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_CS_OE(VTSS_BIT(0)); /* CS_OE */
        if (!cs_active_high) {
            cs_value |= VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_CS(VTSS_BIT(0));
        }

        // We ended up (in spi_transaction_transfer()) with CLK driven high.
        if (!init_clk_high && cs_active) {
            // Drive it low as dictated by higher layer.
            clk_value = VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SCK_OE    | /* SCK_OE */
                        VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SDO_OE    | /* SDO OE */
                        VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_PIN_CTRL_MODE;  /* SW Bitbang */
            writel(cs_value, VTSS_ICPU_CFG_SPI_MST_SW_MODE);
            mmiowb();
            DELAY();
        }

        // Keep driving the CLK to its current value while actively deselecting CS.
        value = clk_value                                         | /* SCK = 0 or 1 */
                VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SCK_OE     | /* SCK_OE = 1 */
                VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_PIN_CTRL_MODE;   /* SW Bitbang */

        cs_value = VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_CS_OE(VTSS_BIT(0)); /* CS_OE = 1 */
        if (cs_active_high) {
            cs_value |= VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_CS(VTSS_BIT(0)); /* CS = 1 => nCS = 0 */
        } else {
            /* CS = 0 => nCS = 1 */
        }
        value |= cs_value;

        //VTSS_ICPU_CFG_SPI_MST_SW_MODE = value;
        writel(value, VTSS_ICPU_CFG_SPI_MST_SW_MODE);
        mmiowb();
        DELAY();

        // Stop driving the clock, but keep on driving CS with nCS == 1 (or - in case of active high - CS = 1)
        writel(cs_value| VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_PIN_CTRL_MODE, VTSS_ICPU_CFG_SPI_MST_SW_MODE);
        mmiowb();

        // Drop everything
        writel(readl(VTSS_ICPU_CFG_SPI_MST_SW_MODE) & ~VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_PIN_CTRL_MODE, VTSS_ICPU_CFG_SPI_MST_SW_MODE);
        mmiowb();
	cs_active = 0;
}

static inline u32 do_spi_cmd(u8 tlen, const u8 *tx, u8 rlen, u8 *rx)
{
    u8 tx_buf[64] = {0}, rx_buf[64] = {0};

    if (!(tx && rx))
        return 0;

    memcpy(tx_buf, tx, tlen);

    vsc7514_spi_lock();
    spi_registers_reset();
    spi_cs_assert();
    spi_transfer(tlen + rlen, tx_buf, rx_buf);
    spi_cs_drop();
    spi_registers_restore();
    vsc7514_spi_unlock();

    memcpy(rx, rx_buf + tlen, rlen);

    return rlen;
}
#endif /* ifdef __KERNEL__ */

#endif // #ifndef __INC_SPI_FLASH_API__

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_flash_type_id_hw(void) {
#ifdef __KERNEL__
	unsigned char rdid_rcv[RDID_SIZE] = {0};
	u8 	rdid_cmd[1] = {0x9f};

	if (!do_spi_cmd(1, rdid_cmd, RDID_SIZE, rdid_rcv))
		return 0;

	/* endian is different user space */
	return ((rdid_rcv[0] << 16 | (rdid_rcv[1] << 8 ) | rdid_rcv[2]));
#else /* ifdef __KERNEL__ */
	uint8_t id[3];
	struct spi_flash_cmd_opt spi_flash;
	int fd;

	spi_flash.data = id;

	fd = open("/dev/" FLASH_CMD_DEVNAME, O_RDONLY);
	if (fd < 0)
		return 0;

	if (ioctl(fd, SPI_FLASH_IOCTL_READ_ID, &spi_flash) < 0) {
		close(fd);
		return 0;
	}

	close(fd);

	if (spi_flash.result)
		return 0;

	return ((id[2] << 16) | (id[1] << 8) | id[0]);
#endif /* ifdef __KERNEL__ */
}

__FS_FUNCTION_PREFER_INLINE size_t fs_read_flash_uid_hw(u_int8_t* dest, size_t dest_len) {
#ifdef __KERNEL__
	unsigned char rcv_byte;
	u8 uuid_cmd[UUID_CMD_SIZE] = { 0x5a, 0x0, 0x0, 0x0, 0x0};
	u_int32_t fid = fs_read_flash_type_id_hw();
	u_int32_t mid = (fid >> 16) & 0xff;

	/* endian is different user space */
	if (mid == MX_IDCODE) {
		uuid_cmd[3] = MX_UUID_OFFSET;
		rcv_byte = UUID_SIZE + 1;
	} else
		return 0;

        if(dest_len < rcv_byte)
	    return 0;

	if (!do_spi_cmd(UUID_CMD_SIZE, uuid_cmd, rcv_byte, dest)) {
		return 0;
        }
	return rcv_byte;
#else /* ifdef __KERNEL__ */
	{
		struct spi_flash_cmd_opt spi_flash;
		int fd;
		u_int8_t uid[64];

		spi_flash.data = uid;

		fd = open("/dev/" FLASH_CMD_DEVNAME, O_RDONLY);
		if (fd < 0)
			return 0;

		if (ioctl(fd, SPI_FLASH_IOCTL_READ_UID, &spi_flash) < 0) {
			close(fd);
			return 0;
		}

		close(fd);

		if (spi_flash.result)
			return 0;

		if (spi_flash.len > dest_len) {
			return 0;
		}
		memcpy(dest, uid, spi_flash.len);
		return spi_flash.len;
	}
#endif /* ifdef __KERNEL__ */
}

#endif // #ifdef UBNT_MIPS_VSC7514
