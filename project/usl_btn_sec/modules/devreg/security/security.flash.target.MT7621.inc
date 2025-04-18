#ifdef UBNT_MIPS_MT7621

#ifdef UNIFI_MT7621

#ifdef __KERNEL__

#define ra_inl(addr)  (*(volatile u32 *)(addr))
#define ra_outl(addr, value)  (*(volatile u32 *)(addr) = (value))
#define ra_and(addr, value) ra_outl(addr, (ra_inl(addr) & (value)))
#define ra_or(addr, value) ra_outl(addr, (ra_inl(addr) | (value)))
#define RALINK_SPI_DELAY udelay(10);
#define RALINK_SPI_CS_SCK_DELAY udelay(1000);
#define RALINK_SPI_MOSI_HIGH	do { ra_outl(RALINK_REG_PIOSET+4, 1 << 6); RALINK_SPI_DELAY } while(0)
#define RALINK_SPI_MOSI_LOW	do { ra_outl(RALINK_REG_PIORESET+4, 1 << 6); RALINK_SPI_DELAY } while(0)
#define RALINK_SPI_CLK_HIGH	do { ra_outl(RALINK_REG_PIOSET+4, 1 << 4); RALINK_SPI_DELAY } while(0)
#define RALINK_SPI_CLK_LOW	do { ra_outl(RALINK_REG_PIORESET+4, 1 << 4); RALINK_SPI_DELAY } while(0)
#define RALINK_SPI_CS_HIGH	do { ra_outl(RALINK_REG_PIOSET+4, 1 << 2); RALINK_SPI_DELAY } while(0)
#define RALINK_SPI_CS_LOW	do { ra_outl(RALINK_REG_PIORESET+4, 1 << 2); RALINK_SPI_DELAY } while(0)

#define SPIC_READ_BYTES (1<<0)
#define SPIC_WRITE_BYTES (1<<1)

#define OPCODE_RD_DATA		0x03    /* Read Data */
#define OPCODE_FAST_READ	0x0B    /* Read Data */
#define OPCODE_RDSR             5       /* Read status register */
#define OPCODE_RDID             0x9F    /* Read ID */
#define OPCODE_RDSFDP		0x5A	/* Read SFDP mode and Unique ID number */
#define OPCODE_ENSA		0xB1	/* Enter Secured Area */
#define OPCODE_EXSA		0xC1	/* Exit Secured Area */

/* Status Register bits. */
#define SR_WIP                  1       /* Write in progress */

#define MTK_SPI_BASE            KSEG1ADDR(0x1E000B00) //0xBE000B00
#define SPI_REG_CTL             (MTK_SPI_BASE + 0x00)
#define SPI_REG_OPCODE          (MTK_SPI_BASE + 0x04)
#define SPI_REG_DATA0           (MTK_SPI_BASE + 0x08)
#define SPI_REG_DATA(x)         (SPI_REG_DATA0 + (x * 4))
#define SPI_REG_MASTER          (MTK_SPI_BASE + 0x28)
#define SPI_REG_MOREBUF         (MTK_SPI_BASE + 0x2c)
#define SPI_REG_Q_CTL           (MTK_SPI_BASE + 0x30)
#define SPI_REG_SPACE_CR        (MTK_SPI_BASE + 0x3c)

#define SPI_CTL_START           0x00000100
#define SPI_CTL_BUSY            0x00010000
#define SPI_CTL_TXCNT_MASK      0x0000000f
#define SPI_CTL_RXCNT_MASK      0x000000f0
#define SPI_CTL_TX_RX_CNT_MASK  0x000000ff
#define SPI_CTL_SIZE_MASK       0x00180000
#define SPI_CTL_ADDREXT_MASK    0xff000000

#define SPI_MBCTL_TXCNT_MASK            0x000001ff
#define SPI_MBCTL_RXCNT_MASK            0x001ff000
#define SPI_MBCTL_TX_RX_CNT_MASK        (SPI_MBCTL_TXCNT_MASK | SPI_MBCTL_RXCNT_MASK)
#define SPI_MBCTL_CMD_MASK              0x3f000000

#define RALINK_SYSCTL_ADDR	0xBE000000
#define RALINK_REG_GPIOMODE	(RALINK_SYSCTL_ADDR + 0x60)
#define RALINK_PIO_BASE		0xBE000600
#define RALINK_REG_PIODIR	(RALINK_PIO_BASE + 0x00)
#define RALINK_REG_PIORESET	(RALINK_PIO_BASE + 0x40)
#define RALINK_REG_PIOSET	(RALINK_PIO_BASE + 0x30)

#endif /* __KERNEL__ */

#ifdef __KERNEL__
#include <asm/delay.h>
#else /* __KERNEL__ */
#include <stdlib.h>             
#include <stdio.h>             
#include <string.h>           
#include <sys/ioctl.h>
#include <fcntl.h>
#include <getopt.h>
#endif /* __KERNEL__ */

#ifndef __INC_SPI_FLASH_API__

#define FLASH_CMD_DEVNAME		"sflash"
#define FLASH_CMD_DEVNUM		200

/* SPI flash command */
#define SPI_FLASH_IOCTL_READ_ID		(0x01)
#define SPI_FLASH_IOCTL_READ_SFDP	(0x02)
#define SPI_FLASH_IOCTL_READ_SA		(0x03)

/* NAND flash command */
#define NAND_FLASH_IOCTL_READ_ID	(0x50)

enum op_status {
	FLASH_OP_SUCCESS = 0,
	FLASH_OP_FAILED = 1,
};

struct spi_flash_cmd_opt {
	unsigned char   *id;
	unsigned char   *uid;
	unsigned char   *sa;
	enum op_status  result;
};

struct nand_spi_flash_cmd_opt {
	unsigned char   *id;
	enum op_status  result;
};

#ifdef __KERNEL__

static int mt7621_bitbang_spi_3b_fast_read_from_zero(unsigned char *buf, const size_t n_rx)
{
	uint32_t i, b, c;
	// set CS0 (GPIO #34) as output
	ra_or(RALINK_REG_PIODIR+4, 1 << 2);

	// set MISO (GPIO #37) as input
	ra_and(RALINK_REG_PIODIR+4, ~(1 << 5));

	// set MOSI (GPIO #38) as output
	ra_or(RALINK_REG_PIODIR+4, 1 << 6);

	// set SCK (GPIO #36) as output
	ra_or(RALINK_REG_PIODIR+4, 1 << 4);

	// set CS0 (GPIO #34) low
	RALINK_SPI_CS_LOW;
	ra_or(RALINK_REG_PIORESET+4, 1 << 2);

	// set MOSI (GPIO #38) low by default
	RALINK_SPI_MOSI_LOW;

	// set SCK (GPIO #36) low by default
	RALINK_SPI_CLK_LOW;

	// change SPI pinmux to GPIO mode
	ra_and(RALINK_REG_GPIOMODE, ~(3 << 16));
	ra_or(RALINK_REG_GPIOMODE, 1 << 16);

	RALINK_SPI_CS_SCK_DELAY

	// SPI transaction begin

	// shift out command
	for (i=0; i < 8; i++) {
		if ( (OPCODE_RDSFDP & (1 << (7-i))) > 0) {
			//fs_debug_printf("out 1\n");
			// MOSI set high
			RALINK_SPI_MOSI_HIGH;
			// CLK set high
			RALINK_SPI_CLK_HIGH;
			// CLK set low
			RALINK_SPI_CLK_LOW;
		} else {
			//fs_debug_printf("out 0\n");
			// MOSI set low
			RALINK_SPI_MOSI_LOW;
			// CLK set high
			RALINK_SPI_CLK_HIGH;
			// CLK set low
			RALINK_SPI_CLK_LOW;
		}
	}

	// shift out address of 0
	// MOSI set low
	RALINK_SPI_MOSI_LOW;

	for (i=0; i<16; i++) {
		//fs_debug_printf("out 0\n");
		// CLK set high
		RALINK_SPI_CLK_HIGH;
		// CLK set low
		RALINK_SPI_CLK_LOW;
	}

	// address 0x8c is an undocumented (?) UID for this chip.  We already use this for other devices.
	for (i=0; i < 8; i++) {
		if ( (0x8c & (1 << (7-i))) > 0) {
			//fs_debug_printf("out 1\n");
			// MOSI set high
			RALINK_SPI_MOSI_HIGH;
			// CLK set high
			RALINK_SPI_CLK_HIGH;
			// CLK set low
			RALINK_SPI_CLK_LOW;
		} else {
			//fs_debug_printf("out 0\n");
			// MOSI set low
			RALINK_SPI_MOSI_LOW;
			// CLK set high
			RALINK_SPI_CLK_HIGH;
			// CLK set low
			RALINK_SPI_CLK_LOW;
		}
	}

	// clock out one more 0 byte
	for (i=0; i<8; i++) {
		RALINK_SPI_CLK_HIGH;
		RALINK_SPI_CLK_LOW;
	}

	// MOSI set high
	RALINK_SPI_MOSI_HIGH;

	//while ( true ) {
	// shift in response
	for (b=0; b < n_rx; b++) {
		c = 0;
		for (i=0; i < 8; i++) {
			// CLK set low
			RALINK_SPI_CLK_LOW;

			// read MISO
			c |= (((ra_inl(KSEG1ADDR(0x1E000624)) & (1 << 5)) >> 5) << (7-i)); RALINK_SPI_DELAY
			//fs_debug_printf("in: %x\n", ra_inl(KSEG1ADDR(0x1E000624)) & (1 << 5));

			// CLK set high
			RALINK_SPI_CLK_HIGH;
		}
		//fs_debug_printf("val: %02x\n", c);
		buf[b] = c;
	}
	//} // while ( true )


	// SPI transaction end

	RALINK_SPI_CS_SCK_DELAY

	// set CS0 (GPIO #34) high
	RALINK_SPI_CS_HIGH;

	// change SPI pinmux to SPI mode
	ra_and(RALINK_REG_GPIOMODE, ~(3 << 16));

	RALINK_SPI_CS_SCK_DELAY

	return 0;
}

static int bbu_spic_trans(const unsigned char code, const unsigned int addr, unsigned char *buf, const size_t n_tx, const size_t n_rx, int flag)
{
	uint32_t i, b, c, j;
	unsigned int reg = 0;

	if (flag == SPIC_WRITE_BYTES)
		return 0;  //unsupported for now

	// set CS0 (GPIO #34) as output
	ra_or(RALINK_REG_PIODIR+4, 1 << 2);

	// set MISO (GPIO #37) as input
	ra_and(RALINK_REG_PIODIR+4, ~(1 << 5));

	// set MOSI (GPIO #38) as output
	ra_or(RALINK_REG_PIODIR+4, 1 << 6);

	// set SCK (GPIO #36) as output
	ra_or(RALINK_REG_PIODIR+4, 1 << 4);

	// set CS0 (GPIO #34) low
	RALINK_SPI_CS_LOW;

	// set MOSI (GPIO #38) low by default
	ra_or(RALINK_REG_PIORESET+4, 1 << 6);

	// set SCK (GPIO #36) low by default
	ra_or(RALINK_REG_PIORESET+4, 1 << 4);


	// change SPI pinmux to GPIO mode
	ra_and(RALINK_REG_GPIOMODE, ~(3 << 16));
	ra_or(RALINK_REG_GPIOMODE, 1 << 16);

	// wait for things to stabilize after CS to start clock
	RALINK_SPI_CS_SCK_DELAY

	// SPI transaction begin

	// shift out command
	for (i=0; i < 8; i++) {
		if ( (code & (1 << (7-i))) > 0) {
			RALINK_SPI_MOSI_HIGH;
			RALINK_SPI_CLK_HIGH;
			RALINK_SPI_CLK_LOW;
		} else {
			RALINK_SPI_MOSI_LOW;
			RALINK_SPI_CLK_HIGH;
			RALINK_SPI_CLK_LOW;
		}
	}

	// shift in response
	for (b=0; b < n_rx; b++) {
		c = 0;
		for (i=0; i < 8; i++) {
			RALINK_SPI_CLK_HIGH;

			// read MISO
			c |= (((ra_inl(KSEG1ADDR(0x1E000624)) & (1 << 5)) >> 5) << (7-i)); RALINK_SPI_DELAY

			RALINK_SPI_CLK_LOW;
		}
		buf[n_rx - b - 1] = c;
	}

	// SPI transaction end

	RALINK_SPI_CS_SCK_DELAY

	// set CS0 (GPIO #34) high
	RALINK_SPI_CS_HIGH;

	// change SPI pinmux to SPI mode
	ra_and(RALINK_REG_GPIOMODE, ~(3 << 16));

	return 0;
}

extern void mt7621_spi_lock(void);
extern void mt7621_spi_unlock(void);
#endif /* __KERNEL__ */

#endif // #ifndef __INC_SPI_FLASH_API__

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_flash_type_id_hw(void) {
#ifdef __KERNEL__
	u8 id[3];
	unsigned char code = OPCODE_RDID;
	int retval;

	mt7621_spi_lock();
	retval = bbu_spic_trans(code, 0, id, 1, 3, SPIC_READ_BYTES);
	mt7621_spi_unlock();

	if (retval)
		return 0;

	return ((id[2] << 16) | (id[1] << 8) | id[0]);
#else /* __KERNEL__ */
	uint8_t id[3];
	struct spi_flash_cmd_opt spi_flash;
	int fd;

	spi_flash.id = id;

	fd = open("/dev/"FLASH_CMD_DEVNAME, O_RDONLY);
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
#endif /* __KERNEL__ */
}

__FS_FUNCTION_PREFER_INLINE size_t fs_read_flash_uid_hw(u_int8_t* dest, size_t dest_len) {
	u_int32_t fid = fs_read_flash_type_id_hw();
	u_int8_t uid[64];
	size_t uid_len;

	// ONLY mx25l12835fmi and mx25l25635fmi supported on UAP-NANO-HD right now!
	if (fid == MXIC_16M_JEDEC_ID || fid == MXIC_32M_JEDEC_ID1)
		uid_len = 13;
	else
		return 0;

	if (dest_len < uid_len)
		return 0;

#ifdef __KERNEL__
	if (fid == MXIC_16M_JEDEC_ID || fid == MXIC_32M_JEDEC_ID1) {
		int retval;
		mt7621_spi_lock();
		retval = mt7621_bitbang_spi_3b_fast_read_from_zero(uid, 13);
		mt7621_spi_unlock();
		if (retval)
			return retval;

		memcpy(dest, uid, 13);
		return 13;

	}
		return 0;
#else /* __KERNEL__ */
	{
		struct spi_flash_cmd_opt spi_flash;
		int fd;

		spi_flash.uid = uid;

		fd = open("/dev/"FLASH_CMD_DEVNAME, O_RDONLY);
		if (fd < 0)
			return 0;

		if (ioctl(fd, SPI_FLASH_IOCTL_READ_SFDP, &spi_flash) < 0) {
			close(fd);
			return 0;
		}

		close(fd);

		if (spi_flash.result)
			return 0;

		memcpy(dest, uid, uid_len);
		return uid_len;
	}
#endif /* __KERNEL__ */
}

#else /* #ifdef UNIFI_MT7621 */

#ifdef __KERNEL__

#define ra_inl(addr)  (*(volatile u32 *)(addr))
#define ra_outl(addr, value)  (*(volatile u32 *)(addr) = (value))
#define ra_and(addr, value) ra_outl(addr, (ra_inl(addr) & (value)))
#define ra_or(addr, value) ra_outl(addr, (ra_inl(addr) | (value)))

#define SPIC_READ_BYTES (1<<0)
#define SPIC_WRITE_BYTES (1<<1)

#define OPCODE_RD_DATA		0x03    /* Read Data */
#define OPCODE_FAST_READ	0x0B    /* Read Data */
#define OPCODE_RDSR             5       /* Read status register */
#define OPCODE_RDID             0x9F    /* Read ID */
#define OPCODE_RDSFDP		0x5A	/* Read SFDP mode and Unique ID number */
#define OPCODE_ENSA		0xB1	/* Enter Secured Area */
#define OPCODE_EXSA		0xC1	/* Exit Secured Area */

/* Status Register bits. */
#define SR_WIP                  1       /* Write in progress */

#define MTK_SPI_BASE            0xBE000B00
#define SPI_REG_CTL             (MTK_SPI_BASE + 0x00)
#define SPI_REG_OPCODE          (MTK_SPI_BASE + 0x04)
#define SPI_REG_DATA0           (MTK_SPI_BASE + 0x08)
#define SPI_REG_DATA(x)         (SPI_REG_DATA0 + (x * 4))
#define SPI_REG_MASTER          (MTK_SPI_BASE + 0x28)
#define SPI_REG_MOREBUF         (MTK_SPI_BASE + 0x2c)
#define SPI_REG_Q_CTL           (MTK_SPI_BASE + 0x30)
#define SPI_REG_SPACE_CR        (MTK_SPI_BASE + 0x3c)

#define SPI_CTL_START           0x00000100
#define SPI_CTL_BUSY            0x00010000
#define SPI_CTL_TXCNT_MASK      0x0000000f
#define SPI_CTL_RXCNT_MASK      0x000000f0
#define SPI_CTL_TX_RX_CNT_MASK  0x000000ff
#define SPI_CTL_SIZE_MASK       0x00180000
#define SPI_CTL_ADDREXT_MASK    0xff000000

#define SPI_MBCTL_TXCNT_MASK            0x000001ff
#define SPI_MBCTL_RXCNT_MASK            0x001ff000
#define SPI_MBCTL_TX_RX_CNT_MASK        (SPI_MBCTL_TXCNT_MASK | SPI_MBCTL_RXCNT_MASK)
#define SPI_MBCTL_CMD_MASK              0x3f000000

#endif /* __KERNEL__ */

#ifdef __KERNEL__
#include <asm/delay.h>
#include "ralink_gpio.h"
#else /* __KERNEL__ */
#include <stdlib.h>             
#include <stdio.h>             
#include <string.h>           
#include <sys/ioctl.h>
#include <fcntl.h>
#include <getopt.h>
#endif /* __KERNEL__ */

#ifndef __INC_SPI_FLASH_API__

#define USE_SPI_CS1
//#define GPIO6_TO_SPI_CS

#define FLASH_CMD_DEVNAME		"flash0"
#define FLASH_CMD_DEVNUM		200

/* SPI flash command */
#define SPI_FLASH_IOCTL_READ_ID		(0x01)
#define SPI_FLASH_IOCTL_READ_SFDP	(0x02)
#define SPI_FLASH_IOCTL_READ_SA		(0x03)

/* NAND flash command */
#define NAND_FLASH_IOCTL_READ_ID	(0x50)

enum op_status {
	SUCCESS = 0,
	FAILED = 1,
};

struct spi_flash_cmd_opt {
	unsigned char   *id;
	unsigned char   *uid;
	unsigned char   *sa;
	enum op_status  result;
};

struct nand_spi_flash_cmd_opt {
	unsigned char   *id;
	enum op_status  result;
};

#ifdef __KERNEL__
static int bbu_spic_busy_wait(void)
{
	int n = 100000;
	do {
		if ((ra_inl(SPI_REG_CTL) & SPI_CTL_BUSY) == 0)
			return 0;
		udelay(1);
	} while (--n > 0);

	fs_debug_printf("bbu_spic_busy_wait: fail \n");
	return -1;
}

static int bbu_mb_spic_trans(const u8 code, const u32 addr, u8 *buf, const size_t n_tx, const size_t n_rx, int flag)
{
	u32 reg;
	int i, q, r;

	/* step 0. enable more byte mode */
	ra_or(SPI_REG_MASTER, (1 << 2));

#ifdef USE_SPI_CS1
	ra_or(SPI_REG_MASTER, (1 << 29)); //cs1 enabled
#endif
	ra_and(RALINK_REG_GPIOMODE, ~(3 << 16)); //spi mode
#ifdef GPIO6_TO_SPI_CS
	ra_or(RALINK_REG_GPIOMODE, (1 << 3)); //uart3 as GPIO mode
	ra_or(RALINK_REG_PIODIR, 1<<6); //output mode
	ra_or(RALINK_REG_PIORESET, 1<<6); //pull low
#endif

	/* step 0. enable more byte mode */
	ra_or(SPI_REG_MASTER, (1 << 2));

	bbu_spic_busy_wait();

	/* step 1. set opcode & address, and fix cmd bit count to 32 (or 40) */
	ra_outl(SPI_REG_OPCODE, (code << 24) & 0xff000000);
	ra_or(SPI_REG_OPCODE, (addr & 0xffffff));

	ra_and(SPI_REG_MOREBUF, ~SPI_MBCTL_CMD_MASK);
	ra_or(SPI_REG_MOREBUF, (32 << 24)); //opcode(1)+addr(3)=32bits

	/* step 2. write DI/DO data #0 ~ #7 */
	ra_outl(SPI_REG_DATA(0), 0); //dummp byte

	/* step 3. set rx (miso_bit_cnt) and tx (mosi_bit_cnt) bit count */
	ra_and(SPI_REG_MOREBUF, ~SPI_MBCTL_TX_RX_CNT_MASK);
	ra_or(SPI_REG_MOREBUF, (n_rx << 3 << 12));
	ra_or(SPI_REG_MOREBUF, (n_tx) << 3);

	/* step 4. kick */
	ra_or(SPI_REG_CTL, SPI_CTL_START);

	/* step 5. wait spi_master_busy */
	bbu_spic_busy_wait();

	/* step 6. read DI/DO data #0 */
	if (flag & SPIC_READ_BYTES) {
		if (buf == NULL) {
			fs_debug_printf("bbu_mb_spic_trans: read null buf\n");
			return -1;
		}
		for (i = 0; i < n_rx; i++) {
			q = i / 4;
			r = i % 4;
			reg = ra_inl(SPI_REG_DATA(q));
			*(buf + i) = (u8)(reg >> (r * 8));
		}
	}

	/* step #. disable more byte mode */
	ra_and(SPI_REG_MASTER, ~(1 << 2));
	ra_or(RALINK_REG_GPIOMODE, (2 << 16)); //nand mode
#ifdef GPIO6_TO_SPI_CS
	ra_or(RALINK_REG_PIOSET, (1<<6)); //pull high
#endif

	return 0;
}

int bbu_spic_trans(const unsigned char code, const unsigned int addr, unsigned char *buf, const size_t n_tx, const size_t n_rx, int flag)
{
	unsigned int reg;

#ifdef USE_SPI_CS1
	ra_or(SPI_REG_MASTER, (1 << 29)); //change to spi_cs1
#endif
	ra_and(RALINK_REG_GPIOMODE, ~(3 << 16)); //change to spi mode
#ifdef GPIO6_TO_SPI_CS
	ra_or(RALINK_REG_GPIOMODE, (1 << 3)); //uart3 as GPIO mode
	ra_or(RALINK_REG_PIODIR, 1<<6); //output mode
	ra_or(RALINK_REG_PIORESET, 1<<6); //pull low
#endif

	bbu_spic_busy_wait();

	/* step 1. set opcode & address */
	if(n_tx > 4) {
		ra_and(SPI_REG_CTL, ~SPI_CTL_ADDREXT_MASK);
		ra_or(SPI_REG_CTL, addr & SPI_CTL_ADDREXT_MASK);
	} 

	ra_outl(SPI_REG_OPCODE, ((addr & 0xffffff) << 8));
	ra_or(SPI_REG_OPCODE, code);

	/* step 2. write DI/DO data #0 */
	if (flag & SPIC_WRITE_BYTES) {
		if (buf == NULL) {
			fs_debug_printf("bbu_spic_trans: write null buf\n");
			ra_or(RALINK_REG_GPIOMODE, (2 << 16)); //change to nand mode
#ifdef GPIO6_TO_SPI_CS
			ra_or(RALINK_REG_PIOSET, (1<<6)); //pull high
#endif

			return -1;
		}
		ra_outl(SPI_REG_DATA0, 0);
		switch (n_tx) {
			case 8:
				ra_or(SPI_REG_DATA0, (*(buf+3) << 24));
			case 7:
				ra_or(SPI_REG_DATA0, (*(buf+2) << 16));
			case 6:
				ra_or(SPI_REG_DATA0, (*(buf+1) << 8));
			case 5:
			case 2:
				ra_or(SPI_REG_DATA0, *buf);
				break;
			default:
				fs_debug_printf("bbu_spic_trans: fixme, write of length %d\n", n_tx);
				ra_or(RALINK_REG_GPIOMODE, (2 << 16)); //change to nand mode
#ifdef GPIO6_TO_SPI_CS
				ra_or(RALINK_REG_PIOSET, (1<<6)); //pull high
#endif
				return -1;
		}
	}

	/* step 3. set mosi_byte_cnt */
	ra_and(SPI_REG_CTL, ~SPI_CTL_TX_RX_CNT_MASK);
	ra_or(SPI_REG_CTL, (n_rx << 4));
	ra_or(SPI_REG_CTL, n_tx);

	/* step 4. kick */
	ra_or(SPI_REG_CTL, SPI_CTL_START);

	/* step 5. wait spi_master_busy */
	bbu_spic_busy_wait();
	if (flag & SPIC_WRITE_BYTES) {
		ra_or(RALINK_REG_GPIOMODE, (2 << 16)); //change to nand mode
#ifdef GPIO6_TO_SPI_CS
		ra_or(RALINK_REG_PIOSET, (1<<6)); //pull high
#endif
		return 0;
	}

	/* step 6. read DI/DO data #0 */
	if (flag & SPIC_READ_BYTES) {
		if (buf == NULL) {
			fs_debug_printf("bbu_spic_trans: read null buf\n");
			ra_or(RALINK_REG_GPIOMODE, (2 << 16)); //change to nand mode
#ifdef GPIO6_TO_SPI_CS
			ra_or(RALINK_REG_PIOSET, (1<<6)); //pull high
#endif
			return -1;
		}
		reg = ra_inl(SPI_REG_DATA0);
		switch (n_rx) {
			case 4:
				*(buf+3) = (unsigned char)(reg >> 24);
			case 3:
				*(buf+2) = (unsigned char)(reg >> 16);
			case 2:
				*(buf+1) = (unsigned char)(reg >> 8);
			case 1:
				*buf = (unsigned char)reg;
				break;
			default:
				fs_debug_printf("bbu_spic_trans: fixme, read of length %d\n", n_rx);
				return -1;
		}
	}
	ra_or(RALINK_REG_GPIOMODE, (2 << 16)); //change to nand mode
#ifdef GPIO6_TO_SPI_CS
	ra_or(RALINK_REG_PIOSET, (1<<6)); //pull high
#endif
	return 0;
}

extern spinlock_t nand_spi_lock;
#endif /* __KERNEL__ */

#endif // #ifndef __INC_SPI_FLASH_API__

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_flash_type_id_hw(void) {
#ifdef __KERNEL__
	u8 id[3];
	unsigned char code = OPCODE_RDID;
	int retval;

	spin_lock_irq(&nand_spi_lock);
	retval = bbu_spic_trans(code, 0, id, 1, 3, SPIC_READ_BYTES);
	spin_unlock_irq(&nand_spi_lock);

	if (retval)
		return 0;

	return ((id[0] << 16) | (id[1] << 8) | id[2]);
#else /* __KERNEL__ */
	uint8_t id[3];
	struct spi_flash_cmd_opt spi_flash;
	int fd;

	spi_flash.id = id;

	fd = open("/dev/"FLASH_CMD_DEVNAME, O_RDONLY);
	if (fd < 0)
		return 0;

	if (ioctl(fd, SPI_FLASH_IOCTL_READ_ID, &spi_flash) < 0) {
		close(fd);
		return 0;
	}

	close(fd);

	if (spi_flash.result)
		return 0;

	return ((id[0] << 16) | (id[1] << 8) | id[2]);
#endif /* __KERNEL__ */
}

__FS_FUNCTION_PREFER_INLINE size_t fs_read_flash_uid_hw(u_int8_t* dest, size_t dest_len) {
	u_int32_t fid = fs_read_flash_type_id_hw();
	u_int8_t uid[64];
	size_t uid_len;

	if (fid == EON_2M_JEDEC_ID)
		uid_len = 12;
	else if (fid == MXIC_2M_JEDEC_ID1)
		uid_len = 64;
	else
		return 0;

	if (dest_len < uid_len)
		return 0;

#ifdef __KERNEL__
	if (fid == EON_2M_JEDEC_ID) {
		unsigned char code =  OPCODE_RDSFDP;
		unsigned int addr = 0x000080; /* 3 bytes address */
		int retval;

		spin_lock_irq(&nand_spi_lock);
		retval = bbu_mb_spic_trans(code, addr, uid, 1, 12,
				SPIC_READ_BYTES);
		spin_unlock_irq(&nand_spi_lock);

		if (retval)
			return 0;

		memcpy(dest, uid, 12);
		return 12;
	} else if (fid == MXIC_2M_JEDEC_ID1) {
		int retval;

		spin_lock_irq(&nand_spi_lock);
		//enter secured area
		bbu_spic_trans(OPCODE_ENSA, 0, NULL, 1, 0, 0);
		//read secured area
		retval = bbu_mb_spic_trans(OPCODE_FAST_READ, 0, uid, 1, 32,
					   SPIC_READ_BYTES);
		retval = bbu_mb_spic_trans(OPCODE_FAST_READ, 32, &uid[32], 1,
					   32, SPIC_READ_BYTES);
		//exit secured area
		bbu_spic_trans(OPCODE_EXSA, 0, NULL, 1, 0, 0);
		spin_unlock_irq(&nand_spi_lock);

		if (retval)
			return retval;

		memcpy(dest, uid, 64);
		return 64;
	} else
		return 0;
#else /* __KERNEL__ */
	{
		struct spi_flash_cmd_opt spi_flash;
		int fd;

		spi_flash.uid = uid;

		fd = open("/dev/"FLASH_CMD_DEVNAME, O_RDONLY);
		if (fd < 0)
			return 0;

		if (ioctl(fd, SPI_FLASH_IOCTL_READ_SFDP, &spi_flash) < 0) {
			close(fd);
			return 0;
		}

		close(fd);

		if (spi_flash.result)
			return 0;

		memcpy(dest, uid, uid_len);
		return uid_len;
	}
#endif /* __KERNEL__ */
}

#endif /* #ifdef UNIFI_MT7621 */

#endif // #ifdef UBNT_MIPS_MT7621
