#ifdef UBNT_NVRx64

#ifndef __KERNEL__

#define NVR_DEBUG(...)
#define NVR_ERROR(...)

typedef struct pci_device {
	uint8_t bus;
	uint8_t dev;
	uint8_t function;

	uint16_t vendor_id;
	uint16_t device_id;

	int cfg_fd;

	int (*cfg_read)(struct pci_device* dev, uint32_t offset, uint8_t* buf, size_t buflen);
} pci_device_t;
#define PROC_PCI "/proc/bus/pci/"
#define PROC_DEVICES PROC_PCI "devices"

static int
proc_cfg_read(pci_device_t* d, uint32_t offset, uint8_t* buf, size_t buflen) {
	int rc;
	if (d->cfg_fd < 0) {
		char buf[512];
		snprintf(buf, sizeof(buf), PROC_PCI "%02x/%02x.%d",
				d->bus, d->dev, d->function);
		d->cfg_fd = open(buf, O_RDONLY);
		if (d->cfg_fd < 0) {
			return -1;
		}
	}

	rc = pread(d->cfg_fd, buf, buflen, offset);
	if (rc < 0) {
		close(d->cfg_fd);
		d->cfg_fd = -1;
		return -2;
	}

	return 0;
}

static pci_device_t*
pci_device_create(uint32_t bdf, uint32_t vendor) {
	pci_device_t* dev = calloc(1, sizeof(pci_device_t));
	if (!dev)
		return NULL;
	dev->cfg_fd = -1;

	dev->bus = (bdf >> 8) & 0xff;
	dev->dev = (bdf >> 3) & 0x1f;
	dev->function = bdf & 0x07;

	dev->device_id = vendor & 0xffff;
	dev->vendor_id = vendor >> 16;

	dev->cfg_read = proc_cfg_read;

	return dev;
}

static void
pci_device_destroy(pci_device_t* d) {
	if (!d)
		return;
	if (d->cfg_fd >= 0) {
		close(d->cfg_fd);
	}
	free(d);
}

static pci_device_t*
pci_proc_find_device(uint16_t vendor_id, uint16_t device_id) {
	FILE* f;
	char buf[512];
	pci_device_t* dev = NULL;
	uint32_t vendor_match = (vendor_id << 16) | device_id;

	f = fopen(PROC_DEVICES, "r");
	if (!f) {
		return NULL;
	}
	while (fgets(buf, sizeof(buf) - 1, f)) {
		uint32_t bdf; /* bus, dev, function */
		uint32_t vendor;
		int count = sscanf(buf, "%x %x", &bdf, &vendor);
		if (count == 2 && vendor == vendor_match) {
			dev = pci_device_create(bdf, vendor);
			break;
		}
	}

	fclose(f);
	return dev;
}

static pci_device_t*
pci_find_device(uint16_t vendor_id, uint16_t device_id) {
	return pci_proc_find_device(vendor_id, device_id);
}

typedef struct nvrhw {
	void* ctx;
	int (*get_jedec_id)(struct nvrhw* x, uint8_t* vendor, uint16_t* flashinfo);
	int (*get_unique_id)(struct nvrhw* x, uint8_t* buffer, size_t buflen);
	int (*get_cpu_id)(struct nvrhw* x, uint8_t* buffer, size_t buflen);
	int (*test)(struct nvrhw* x, int count, int (*printfunc)(const char *,...));
	void (*printinfo)(struct nvrhw* x, int (*printfunc)(const char *,...));
	void (*destroy)(struct nvrhw* x);
} nvrhw_t;

#define PCI_READB(_base, _reg) \
        (*((volatile uint8_t*)((uint8_t*)(_base) + (_reg))))
#define PCI_READW(_base, _reg) \
        (*((volatile uint16_t*)((uint8_t*)(_base) + (_reg))))
#define PCI_READL(_base, _reg) \
        (*((volatile uint32_t*)((uint8_t*)(_base) + (_reg))))

#define PCI_WRITEB(_base, _reg, _val) \
        (*((volatile uint8_t*)((uint8_t*)(_base) + (_reg))) = (_val))
#define PCI_WRITEW(_base, _reg, _val) \
        (*((volatile uint16_t*)((uint8_t*)(_base) + (_reg))) = (_val))
#define PCI_WRITEL(_base, _reg, _val) \
        (*((volatile uint32_t*)((uint8_t*)(_base) + (_reg))) = (_val))

#define reg_print(reg, bit, value, x) \
        do { \
                uint32_t bval = (value & reg##_##bit) >> reg##_##bit##_OFFSET; \
                printf("%s: 0x%x (%d)" x, #bit, bval, bval); \
        } while (0)

#define reg_value(reg, bit, value) \
        ((value & reg##_##bit) >> reg##_##bit##_OFFSET)


static inline void
x86_cpuid(uint32_t* eax, uint32_t* ebx, uint32_t* ecx, uint32_t* edx) {
	asm volatile("cpuid"
		     : "=a" (*eax),
		     "=b" (*ebx),
		     "=c" (*ecx),
		     "=d" (*edx)
		     : "0" (*eax), "2" (*ecx));
}

#define ICH7_SPIBAR_OFFSET 0x3020

#define RCBA 0xF0
#define RCBA_EN 0x1
#define RCBA_EN_OFFSET 0
#define RCBA_BA 0xFFFFC000
/* commented out intentionally, BA is not offsettable!
#define RCBA_BA_OFFSET 14
*/

#define BIOS_CNTL 0xDC
#define BIOS_CNTL_BIOSWE 0x1
#define BIOS_CNTL_BIOSWE_OFFSET 0
#define BIOS_CNTL_BLE 0x2
#define BIOS_CNTL_BLE_OFFSET 1
#define BIOS_CNTL_SRC 0xC
#define BIOS_CNTL_SRC_OFFSET 2
#define BIOS_CNTL_TSS 0x10
#define BIOS_CNTL_TSS_OFFSET 4

#define GCS 0x3410
#define GCS_BILD 0x1
#define GCS_BILD_OFFSET 0
#define GCS_NR 0x20
#define GCS_NR_OFFSET 5
#define GCS_BBS 0xC00
#define GCS_BBS_OFFSET 10

#define BUC 0x3414
#define BUC_TS 0x1
#define BUC_TS_OFFSET 0

#define SPI_SPIS 0x00
#define SPI_SPIS_RESERVED_MASK 0x7FF0
#define SPI_SPIS_SCIP 0x01
#define SPI_SPIS_SCIP_OFFSET 0
#define SPI_SPIS_ACC_GRANT 0x02
#define SPI_SPIS_ACC_GRANT_OFFSET 1
#define SPI_SPIS_CDS 0x04
#define SPI_SPIS_CDS_OFFSET 2
#define SPI_SPIS_BAS 0x08
#define SPI_SPIS_BAS_OFFSET 3
#define SPI_SPIS_LOCKDOWN 0x0F
#define SPI_SPIS_LOCKDOWN_OFFSET 15

#define SPI_SPIC 0x02
#define SPI_SPIC_ACC_REQ 0x01
#define SPI_SPIC_ACC_REQ_OFFSET 0
#define SPI_SPIC_SCGO 0x02
#define SPI_SPIC_SCGO_OFFSET 1
#define SPI_SPIC_ACS 0x04
#define SPI_SPIC_ACS_OFFSET 2
#define SPI_SPIC_SPOP 0x08
#define SPI_SPIC_SPOP_OFFSET 3
#define SPI_SPIC_COP 0x38
#define SPI_SPIC_COP_OFFSET 4
#define SPI_SPIC_DC 0x4000
#define SPI_SPIC_DC_OFFSET 14

#define SPI_SPIA 0x04

#define SPI_SPID0 0x08
#define SPI_SPID1 0x10
#define SPI_SPID2 0x18
#define SPI_SPID3 0x20
#define SPI_SPID4 0x28
#define SPI_SPID5 0x30
#define SPI_SPID6 0x38
#define SPI_SPID7 0x40

#define SPI_BBAR 0x50
#define SPI_BBAR_BOTTOM 0xFFFF00

#define SPI_PREOP 0x54
#define SPI_PREOP_PREFIX0 0xff
#define SPI_PREOP_PREFIX0_OFFSET 0
#define SPI_PREOP_PREFIX1 0xff00
#define SPI_PREOP_PREFIX1_OFFSET 8

#define SPI_OPTYPE 0x56

#define SPI_OPMENU0 0x58
#define SPI_OPMENU1 0x5c

#define SPI_PBR0 0x60
#define SPI_PBR1 0x64
#define SPI_PBR2 0x68

#ifdef USE_BBSNAMES

static const char* ich7_bbs_names[] = {
	"reserved",
	"SPI",
	"PCI",
	"LPC"
};

#endif

typedef struct jedec_id {
	uint8_t vendor;
	uint16_t flashmodel;
} jedec_id_t;

typedef struct ich7_ctx {
	pci_device_t* dev;
	int memfd;
	uint32_t memsize;
	void* rcrb;
	void* spibar;
	jedec_id_t flash_id;
	int spilockdown;
} ich7_ctx_t;

static inline uint8_t
ich7_pci_readb(const ich7_ctx_t* ctx, uint32_t reg) {
	return PCI_READB(ctx->rcrb, reg);
}

static inline uint16_t
ich7_pci_readw(const ich7_ctx_t* ctx, uint32_t reg) {
	return PCI_READW(ctx->rcrb, reg);
}

static inline uint32_t
ich7_pci_readl(const ich7_ctx_t* ctx, uint32_t reg) {
	return PCI_READL(ctx->rcrb, reg);
}

static inline uint8_t
ich7_spi_readb(const ich7_ctx_t* ctx, uint32_t reg) {
	return PCI_READB(ctx->spibar, reg);
}

static inline uint16_t
ich7_spi_readw(const ich7_ctx_t* ctx, uint32_t reg) {
	return PCI_READW(ctx->spibar, reg);
}

static inline uint32_t
ich7_spi_readl(const ich7_ctx_t* ctx, uint32_t reg) {
	return PCI_READL(ctx->spibar, reg);
}

static inline void
ich7_spi_writeb(const ich7_ctx_t* ctx, uint32_t reg, uint8_t value) {
	PCI_WRITEB(ctx->spibar, reg, value);
}

static inline void
ich7_spi_writew(const ich7_ctx_t* ctx, uint32_t reg, uint16_t value) {
	PCI_WRITEW(ctx->spibar, reg, value);
}

static inline void
ich7_spi_writel(const ich7_ctx_t* ctx, uint32_t reg, uint32_t value) {
	PCI_WRITEL(ctx->spibar, reg, value);
}

static ich7_ctx_t*
ich7_ctx_create(pci_device_t* dev, uint32_t rcba_ba, uint32_t memsize) {
	ich7_ctx_t* ctx;
	uint32_t gcs, bbs; /* General Control & Status, BIOS Boot Strap */
	uint8_t* mem;
	int fd = open("/dev/mem", O_RDWR);
	if (fd < 0) {
		NVR_ERROR("Failed opening /dev/mem: %s\n", strerror(errno));
		return NULL;
	}
	NVR_DEBUG("Mapping 0x%x area at offset 0x%08x..\n", memsize, rcba_ba);
	mem = mmap(0, memsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, rcba_ba);
	if (mem == MAP_FAILED) {
		NVR_ERROR("Failed mapping 0x%x area at offset 0x%08x: %s\n",
				memsize, rcba_ba, strerror(errno));
		close(fd);
		return NULL;
	}

	gcs = PCI_READL(mem, GCS);
	bbs = reg_value(GCS, BBS, gcs);

	if (bbs != 0x01) {
		NVR_ERROR("Expected SPI BIOS Bootstrap, but got %s (%d)\n",
				ich7_bbs_names[bbs], bbs);
		munmap(mem, memsize);
		close(fd);
		return NULL;
	}

	ctx = calloc(1, sizeof(ich7_ctx_t));
	ctx->dev = dev;
	ctx->memfd = fd;
	ctx->memsize = memsize;
	ctx->rcrb = mem;
	ctx->spibar = mem + ICH7_SPIBAR_OFFSET;

	ctx->flash_id.vendor = 0xff;
	ctx->flash_id.flashmodel = 0xffff;
	ctx->spilockdown =
		reg_value(SPI_SPIS, LOCKDOWN, ich7_spi_readw(ctx, SPI_SPIS)) != 0;

	return ctx;
}

static void
ich7_ctx_destroy(ich7_ctx_t* ctx) {
	if (!ctx)
		return;

	if (ctx->rcrb) {
		munmap(ctx->rcrb, ctx->memsize);
		ctx->rcrb = NULL;
	}
	if (ctx->dev) {
		pci_device_destroy(ctx->dev);
		ctx->dev = NULL;
	}
	close(ctx->memfd);
	free(ctx);
}

static int
ich7_opcode_index(ich7_ctx_t* ctx, uint8_t opcode) {
	int i;
	uint64_t opmenu;
	opmenu = ich7_spi_readl(ctx, SPI_OPMENU1);
	opmenu <<= 32;
	opmenu |= ich7_spi_readl(ctx, SPI_OPMENU0);
	NVR_DEBUG("OPMENU: 0x%016lx\n", opmenu);
	for (i = 0; i < 8; ++i) {
		if ((opmenu & 0xff) == opcode) {
			break;
		}
		opmenu >>= 8;
	}

	if (i == 8) {
		NVR_ERROR("Opcode 0x%02x not found!\n", opcode);
		return -1;
	}
	NVR_DEBUG("OPCODE %02x found at index %d\n", opcode, i);
	return i;
}

static int
ich7_spi_read_data(ich7_ctx_t* ctx, uint8_t* data, int len) {
	int i;
	uint32_t x = 0;
	for (i = 0; i < len; ++i) {
		if ((i % 4) == 0) {
			x = ich7_spi_readl(ctx, SPI_SPID0 + i);
		}
		data[i] = (x >> ((i % 4) * 8)) & 0xff;
	}
	return 0;
}

#define SPI_CMD_TIMEOUT_COUNT (10 * 100)
#define SPI_CMD_TIMEOUT_CYCLE 100

#define RC_SPI_READ_TIMEOUT		1
#define RC_SPI_READ_OPCODE_ERROR	(-60)
#define RC_SPI_READ_BLOCKED		(-61)

static inline int
ich7_spi_wait_done(ich7_ctx_t* ctx, int count, int cycle_timeout) {
	uint16_t spis;
	do {
		usleep(cycle_timeout);
		spis = ich7_spi_readw(ctx, SPI_SPIS);
	} while (((spis & (SPI_SPIS_CDS | SPI_SPIS_BAS)) == 0) && --count);
	return count;
}

static inline int
ich7_spi_wait_scip(ich7_ctx_t* ctx, int count, int cycle_timeout) {
	uint16_t spis;
	do {
		usleep(cycle_timeout);
		spis = ich7_spi_readw(ctx, SPI_SPIS);
	} while ((spis & SPI_SPIS_SCIP) && --count);
	return count;
}

static int
ich7_spi_read_cmd(ich7_ctx_t* ctx, uint8_t cmd, uint8_t* data, uint8_t datalen) {
	int timeout;
	uint16_t spis, spic;
	int index;

	/* make sure we have opcode in our opmenu */
	index = ich7_opcode_index(ctx, cmd);
	if (index < 0) {
		return RC_SPI_READ_OPCODE_ERROR;
	}

	/* before we issue any command, we have to make sure SCIP is clear */
	timeout = ich7_spi_wait_scip(ctx, SPI_CMD_TIMEOUT_COUNT, SPI_CMD_TIMEOUT_CYCLE);
	if (timeout == 0) {
		NVR_ERROR("Timeout waiting for current Cycle in Progress..\n");
		return RC_SPI_READ_TIMEOUT;
	}

	/* prepare SPIS */
	spis = ich7_spi_readw(ctx, SPI_SPIS);
	spis &= SPI_SPIS_RESERVED_MASK;
	spis |= (SPI_SPIS_CDS | SPI_SPIS_BAS);
	ich7_spi_writew(ctx, SPI_SPIS, spis);

	/* prepare SPIC */
	spic = ((uint16_t)(index & 0x07)) << SPI_SPIC_COP_OFFSET;
	if (datalen > 0 && datalen <= 64) {
		spic |= SPI_SPIC_DC;
		spic |= (datalen - 1) << 8;
	}

	spic |= SPI_SPIC_SCGO;
	ich7_spi_writew(ctx, SPI_SPIC, spic);

	timeout = ich7_spi_wait_done(ctx, SPI_CMD_TIMEOUT_COUNT, SPI_CMD_TIMEOUT_CYCLE);
	if (timeout == 0) {
		NVR_ERROR("Timeout waiting for SPI command (%02x) completion...\n", cmd);
		return RC_SPI_READ_TIMEOUT;
	}

	/* additional SCIP wait to ensure data flush */
	timeout = ich7_spi_wait_scip(ctx, SPI_CMD_TIMEOUT_COUNT, SPI_CMD_TIMEOUT_CYCLE);
	if (timeout == 0) {
		NVR_ERROR("Timeout waiting for current Cycle in Progress (2)..\n");
		return RC_SPI_READ_TIMEOUT;
	}

	/* clear errors if any */
	spis = ich7_spi_readw(ctx, SPI_SPIS);
	if (spis & SPI_SPIS_BAS) {
		spis &= SPI_SPIS_RESERVED_MASK;
		spis |= SPI_SPIS_BAS;
		ich7_spi_writew(ctx, SPI_SPIS, spis);
		return RC_SPI_READ_BLOCKED;
	}
	ich7_spi_read_data(ctx, data, datalen);
	return 0;
}

static int
ich7_spi_opcode_validate(ich7_ctx_t* ctx, uint8_t opcode) {
	int opcode_index = ich7_opcode_index(ctx, opcode);
	if (opcode_index < 0) {
		if (ctx->spilockdown) {
			return -2;
		}
		ich7_spi_writew(ctx, SPI_OPTYPE, 0x043b);
		ich7_spi_writel(ctx, SPI_OPMENU0, 0x05200302);
		ich7_spi_writel(ctx, SPI_OPMENU1, 0x0000019f | (opcode << 16));
		opcode_index = ich7_opcode_index(ctx, opcode);
		/* reprogramming opcodes failed? can't do anything else */
		if (opcode_index < 0) {
			return -3;
		}
	}
	return 0;
}

static int
ich7_spi_get_jedec_id(ich7_ctx_t* ctx, uint8_t* vendor, uint16_t* flashinfo) {
	uint8_t jedecid[4];
	int rc;
	if (!ctx || !vendor || !flashinfo)
		return -1;

	if (ctx->flash_id.vendor != 0xff && ctx->flash_id.flashmodel != 0xffff) {
		*vendor = ctx->flash_id.vendor;
		*flashinfo = ctx->flash_id.flashmodel;
		return 0;
	}

	rc = ich7_spi_opcode_validate(ctx, 0x9f);
	if (rc != 0) {
		return -2;
	}

	rc = ich7_spi_read_cmd(ctx, 0x9f, jedecid, 4);
	if (rc == 0) {
		ctx->flash_id.vendor = jedecid[0];
		ctx->flash_id.flashmodel = jedecid[1] << 8 | jedecid[2];
		*vendor = ctx->flash_id.vendor;
		*flashinfo = ctx->flash_id.flashmodel;
	}

	return rc;
}

static int
ich7_spi_get_winbond_unique_id(ich7_ctx_t* ctx, uint8_t* buffer, size_t buflen) {
	uint8_t uniqid[12];
	int rc;
	if (!ctx)
		return -1;

	if (!buffer || buflen == 0)
		return 8; // return preferred size

	rc = ich7_spi_opcode_validate(ctx, 0x4b);
	if (rc != 0) {
		return -2;
	}

	// 4b instruction requires 4 additional cycles, hence uniqid length is 12
	// and later we skip 4 bytes
	rc = ich7_spi_read_cmd(ctx, 0x4b, uniqid, sizeof(uniqid));
	if (rc == 0) {
		uint8_t* p = uniqid + 4;
		if (buflen < 8)
			p += 8 - buflen;
		else
			buflen = 8;
		memcpy(buffer, p, buflen);
	}

	return rc;
}

static int
ich7_spi_get_unique_id(ich7_ctx_t* ctx, uint8_t* buffer, size_t buflen) {
	uint8_t flash_vendor = 0;
	uint16_t flash_model = 0;

	ich7_spi_get_jedec_id(ctx, &flash_vendor, &flash_model);
	if (flash_vendor == 0xef) {
		switch (flash_model) {
		case 0x4014:
		case 0x4015:
		case 0x4016:
			return ich7_spi_get_winbond_unique_id(ctx, buffer, buflen);
		}
	}

	/* unsupported flash manufacturer */
	return -100;
}

static int
ich7nvr_get_jedec_id(nvrhw_t* x, uint8_t* vendor, uint16_t* flashinfo) {
	return ich7_spi_get_jedec_id(x->ctx, vendor, flashinfo);
}

static int
ich7nvr_get_unique_id(nvrhw_t* x, uint8_t* buffer, size_t buflen) {
	return ich7_spi_get_unique_id(x->ctx, buffer, buflen);
}

static int
ich7nvr_get_cpu_id(__ATTRIB_UNUSED nvrhw_t* x, uint8_t* buffer, size_t buflen) {
	uint32_t eax, ebx, ecx, edx;
	int cnt, i;
	// return preferred size if buffer is NULL or len is 0
	if (!buffer || buflen == 0)
		return 8;
	if (!buffer || buflen < 8)
		return -1;
	eax = 1; ebx = ecx = edx = 0;
	x86_cpuid(&eax, &ebx, &ecx, &edx);

	cnt = 0;
	// EAX bytes:
	//	stepping+model
	//	family and type
	//	extended model
	//	extended family
	buffer[cnt++] = eax & 0xff;
	buffer[cnt++] = (eax >> 8) & 0xff;
	buffer[cnt++] = (eax >> 16) & 0xff;
	buffer[cnt++] = (eax >> 20) & 0xff;

	// EDX as extra, so we match dmidecode CPU ID
	for (i = 0; i < 4; ++i) {
		buffer[cnt++] = edx & 0xff;
		edx >>= 8;
	}

	return cnt;
}

#ifndef USE_PRINTINFO

#define ich7nvr_dumpinfo 0

#else

static void
ich7nvr_dumpinfo(nvrhw_t* x, int (*printfunc)(const char *,...)) {
	uint32_t gcs, bbs, buc, i;
	if (!x || !x->ctx)
		return;

	ich7_ctx_t* ctx = x->ctx;

	if (ctx->dev) {
		pci_device_t* dev = ctx->dev;
		uint32_t rcba, cntl;
		uint8_t spi_rc, bios_we, bios_le;

		dev->cfg_read(dev, BIOS_CNTL, (uint8_t*)&cntl, sizeof(cntl));
		bios_we = reg_value(BIOS_CNTL, BIOSWE, cntl);
		bios_le = reg_value(BIOS_CNTL, BLE, cntl);
		printfunc("BIOS_CNTL: 0x%02x\n", cntl);
		printfunc("BIOS Writeable: %s (%x)\n", bios_we == 0 ? "no" : "yes", bios_we);
		printfunc("BIOS Locked: %s (%x)\n", bios_le == 0 ? "no" : "yes", bios_le);
		spi_rc = reg_value(BIOS_CNTL, SRC, cntl);
		printfunc("SPI Read Configuration: %x (prefetching: %s; caching: %s)\n",
				spi_rc,
				(spi_rc & 0x2) ? "yes" : "no",
				(spi_rc & 0x1) ? "no" : "yes");
		printfunc("Top Swap Status: %x\n", reg_value(BIOS_CNTL, TSS, cntl));

		dev->cfg_read(dev, RCBA, (uint8_t*)&rcba, sizeof(rcba));
		printfunc("RCBA (Root Complex Base Address): 0x%08x\n", rcba);
		printfunc("RCBA BA: 0x%08x\n", rcba & RCBA_BA);
	}

	gcs = ich7_pci_readl(ctx, GCS);
	printfunc("GCS: 0x%08x\n", gcs);
	printfunc("BIOS Interface Lock-Down: %s\n", reg_value(GCS, BILD, gcs) ? "yes" : "no");
	printfunc("No Reboot: %d\n", reg_value(GCS, NR, gcs));
	bbs = reg_value(GCS, BBS, gcs);
	printfunc("BIOS Boot Straps: %x (%s)\n", bbs, ich7_bbs_names[bbs]);

	buc = ich7_pci_readb(ctx, BUC);
	printfunc("BUC: 0x%08x\n", buc);
	printfunc("Top Swap: %d\n", reg_value(BUC, TS, buc));
	printfunc("SPI Info:\n");
	uint16_t spis = ich7_spi_readw(ctx, SPI_SPIS);
	printfunc("  SPIS: 0x%04x\n", spis);
	printfunc("    Configuration Lockdown: %s\n",
			reg_value(SPI_SPIS, LOCKDOWN, spis) ? "on" : "off");
	printfunc("  SPIC: 0x%04x\n", ich7_spi_readw(ctx, SPI_SPIC));
	printfunc("  SPIA: 0x%08x\n", ich7_spi_readl(ctx, SPI_SPIA));
	uint32_t bbar = ich7_spi_readl(ctx, SPI_BBAR);
	printfunc("  BBAR: 0x%08x\n", bbar);
	printfunc("    Bottom of System Flash: 0x%04x\n", bbar & SPI_BBAR_BOTTOM);
	printfunc("  PBR0: 0x%08x\n", ich7_spi_readl(ctx, SPI_PBR0));
	printfunc("  PBR1: 0x%08x\n", ich7_spi_readl(ctx, SPI_PBR1));
	printfunc("  PBR2: 0x%08x\n", ich7_spi_readl(ctx, SPI_PBR2));

	printfunc("SPI OP Info:\n");
	printfunc("  PREOP: 0x%04x\n", ich7_spi_readw(ctx, SPI_PREOP));
	uint32_t opmenu0 = ich7_spi_readl(ctx, SPI_OPMENU0);
	uint32_t opmenu1 = ich7_spi_readl(ctx, SPI_OPMENU1);
	uint16_t optypes = ich7_spi_readw(ctx, SPI_OPTYPE);
	printfunc("  OPMENU0: 0x%08x\n", opmenu0);
	printfunc("  OPMENU1: 0x%08x\n", opmenu1);
	printfunc("  OPTYPE: 0x%04x\n", optypes);
	uint64_t opmenu = opmenu1;
	opmenu <<= 32;
	opmenu |= opmenu0;
	for (i = 0; i < 8; ++i) {
		uint8_t opcode = opmenu & 0xff;
		uint8_t optype = optypes & 0x03;
		printfunc("  [%u] 0x%02x %s w/%c address\n", i, opcode,
				optype & 0x01 ? "write" : " read",
				optype & 0x02 ? ' ' : 'o');

		opmenu >>= 8;
		optypes >>= 2;
	}

}

#endif /* USE_PRINTINFO */

typedef struct test_uid_item {
	uint8_t uid[8];
	size_t count;
} test_uid_item_t;

#define MAX_TEST_UIDS 16

typedef struct test_uids {
	test_uid_item_t uids[MAX_TEST_UIDS];
	size_t size;
} test_uids_t;

#define UID_STR "%02x%02x%02x%02x-%02x%02x%02x%02x"
#define UID2STR(a) (a)[0], (a)[1], (a)[2], (a)[3], (a)[4], (a)[5], (a)[6], (a)[7]

#ifndef USE_TESTS

#define ich7nvr_test 0

#else

static void
ich7_spi_clear_data(ich7_ctx_t* ctx) {
	int i;
	for (i = 0; i < 8; ++i) {
		ich7_spi_writel(ctx, SPI_SPID0 + i * 4, 0);
	}
}

/* test cycle for triggering SPI errors */
static int
ich7nvr_test(nvrhw_t* x, int count, int (*printfunc)(const char *,...)) {
	int i, j, rc;
	uint8_t uid[8];
	int failures = 0;
	test_uids_t* uids;

	if (!x || !x->ctx) {
		return -1;
	}

	uids = calloc(1, sizeof(test_uids_t));

	printfunc(" 000%% completed");
	for (i = 0; i < count; ++i) {
		if (i % 100) {
			printfunc("\r %03d", (i * 100) / count);
		}
		ich7_spi_clear_data(x->ctx);
		memset(uid, 0, sizeof(uid));
		rc = ich7_spi_get_unique_id(x->ctx, uid, sizeof(uid));
		if (rc != 0) {
			printfunc("\nERROR (%d) on iteration: %d\n", rc, i);
			++failures;
			continue;
		}
		test_uid_item_t* found = NULL;
		for (j = 0; j < uids->size; ++j) {
			test_uid_item_t* item = &(uids->uids[j]);
			if (memcmp(item->uid, uid, sizeof(uid)) == 0) {
				found = item;
				break;
			}
		}

		if (!found) {
			if ((uids->size + 1) < MAX_TEST_UIDS) {
				test_uid_item_t* item = &(uids->uids[uids->size]);
				memcpy(item->uid, uid, sizeof(uid));
				item->count = 1;
				++uids->size;
			} else {
				printfunc("\nERROR: too many different (%d) entries already\n", MAX_TEST_UIDS);
			}
		} else {
			++found->count;
		}

	}

	printfunc("\nSUMMARY: %d tests, %d failures, %d UIDs\n", count, failures, uids->size);
	for (i = 0; i < uids->size; ++i) {
		test_uid_item_t* item = &(uids->uids[i]);
		printfunc(" [%d] " UID_STR " : %u\n", i, UID2STR(item->uid), item->count);
	}

	free(uids);

	return failures;
}
#endif /* USE_TESTS */

static void
ich7nvr_destroy(nvrhw_t* x) {
	if (!x)
		return;
	if (x->ctx) {
		ich7_ctx_destroy((ich7_ctx_t*)x->ctx);
		x->ctx = NULL;
	}
	free(x);
}

static nvrhw_t*
ich7nvr_detect(void) {
	uint32_t rcba = 0, rcba_ba = 0;
#if 1
	pci_device_t* dev = pci_find_device(0x8086, 0x27bc);
	if (dev == NULL)
		return NULL;

	dev->cfg_read(dev, RCBA, (uint8_t*)&rcba, sizeof(rcba));
#else
	rcba = 0xfed1c001;
#endif
	rcba_ba = rcba & RCBA_BA;
	if (rcba_ba == 0) {
		return NULL;
	}

	ich7_ctx_t* ctx = ich7_ctx_create(dev, rcba_ba, 0x4000);
	if (!ctx) {
		return NULL;
	}

	nvrhw_t* box = calloc(1, sizeof(nvrhw_t));
	box->ctx = ctx;
	box->get_jedec_id = ich7nvr_get_jedec_id;
	box->get_unique_id = ich7nvr_get_unique_id;
	box->get_cpu_id = ich7nvr_get_cpu_id;
	box->printinfo = ich7nvr_dumpinfo;
	box->test = ich7nvr_test;
	box->destroy = ich7nvr_destroy;

	return box;
}
#define VV_RCBA 0xF0
#define VV_RCBA_EN 0x1
#define VV_RCBA_EN_OFFSET 0
#define VV_RCBA_BA 0xFFFFFC00
/* commented out intentionally, BA is not offsettable!
#define VV_RCBA_BA_OFFSET 10
*/

#define VV_SPIBASE 0x54
#define VV_SPIBASE_EN 0x2
#define VV_SPIBASE_EN_OFFSET 1
#define VV_SPIBASE_BA 0xFFFFFE00
/* commented out intentionally, BA is not offsettable!
#define VV_SPIBASE_BA_OFFSET 9
*/

/* Hardware sequencing Flash Status */
#define VV_SPI_HSFSTS 0x04
/* Flash Cycle Done */
#define VV_SPI_HSFSTS_FCDONE 0x01
#define VV_SPI_HSFSTS_FCDONE_OFFSET 0
/* FLash Cycle Error */
#define VV_SPI_HSFSTS_FCERR 0x02
#define VV_SPI_HSFSTS_FCERR_OFFSET 1
/* Access Error Log */
#define VV_SPI_HSFSTS_AEL 0x04
#define VV_SPI_HSFSTS_AEL_OFFSET 2
/* SCIP */
#define VV_SPI_HSFSTS_SCIP 0x20
#define VV_SPI_HSFSTS_SCIP_OFFSET 5
/* Flash Descriptor Valid */
#define VV_SPI_HSFSTS_FDV 0x4000
#define VV_SPI_HSFSTS_FDV_OFFSET 13

#define VV_SPI_FADDR 0x08
#define VV_SPI_FADDR_FLA 0x1ffffff
#define VV_SPI_FADDR_FLA_OFFSET 0

/* Software sequencing Flash Status */
#define VV_SPI_SSFSTS 0x90
/* SCIP - RO */
#define VV_SPI_SSFSTS_SCIP 0x01
#define VV_SPI_SSFSTS_SCIP_OFFSET 0
/* Cycle Done Status - RW/C1 */
#define VV_SPI_SSFSTS_CDS 0x04
#define VV_SPI_SSFSTS_CDS_OFFSET 2
/* Flash Cycle Error - RW/C1 */
#define VV_SPI_SSFSTS_FCERR 0x08
#define VV_SPI_SSFSTS_FCERR_OFFSET 3
/* SPI Cycle GO */
#define VV_SPI_SSFSTS_SCGO 0x200
#define VV_SPI_SSFSTS_SCGO_OFFSET 9
/* Atomic Sequence - preifx+cmd+polling */
#define VV_SPI_SSFSTS_ACS 0x400
#define VV_SPI_SSFSTS_ACS_OFFSET 10
/* Atomic Sequence Prefix Opcode*/
#define VV_SPI_SSFSTS_ACPOP 0x800
#define VV_SPI_SSFSTS_ACPOP_OFFSET 11
/* Cycle Opcode Pointer (cmd) */
#define VV_SPI_SSFSTS_COP 0x7000
#define VV_SPI_SSFSTS_COP_OFFSET 12
/* Data Byte Count */
#define VV_SPI_SSFSTS_DBC 0x3F0000
#define VV_SPI_SSFSTS_DBC_OFFSET 16
/* Data Cycle - 0 = no data*/
#define VV_SPI_SSFSTS_DC 0x400000
#define VV_SPI_SSFSTS_DC_OFFSET 22
/* SPI SMI# Enable */
#define VV_SPI_SSFSTS_SME 0x800000
#define VV_SPI_SSFSTS_SME_OFFSET 23
/* SPI Cycle Frequency: 000=20Mhz,001=33Mhz,010=66Mhz(NA),011=25Mhz(NA),100=50Mhz(NA) */
#define VV_SPI_SSFSTS_SCF 0x7000000
#define VV_SPI_SSFSTS_SCF_OFFSET 24

#define VV_SPI_BCR 0xFC
#define VV_SPI_BCR_LOCK_EN 0x01
#define VV_SPI_BCR_LOCK_EN_OFFSET 0
#define VV_SPI_BCR_SRC 0x06
#define VV_SPI_BCR_SRC_OFFSET 1
#define VV_SPI_BCR_EISS 0x20
#define VV_SPI_BCR_EISS_OFFSET 4

#define VV_SPI_PREOP   0x94
#define VV_SPI_PREOP_PO0 0xff
#define VV_SPI_PREOP_PO0_OFFSET 0
#define VV_SPI_PREOP_PO1 0xff00
#define VV_SPI_PREOP_PO1_OFFSET 8

#define VV_SPI_OPTYPE  0x96
#define VV_SPI_OPMENU0 0x98
#define VV_SPI_OPMENU1 0x9c

#define VV_SPI_FDATA0  0x10
#define VV_SPI_FDATA15 0x4c

#define VV_RCRB_GCS 0x00
#define VV_RCRB_GCS_BILD 0x01
#define VV_RCRB_GCS_BILD_OFFSET 0
#define VV_RCRB_GCS_TOPSWAP 0x02
#define VV_RCRB_GCS_TOPSWAP_OFFSET 1
#define VV_RCRB_GCS_BBS 0xC00
#define VV_RCRB_GCS_BBS_OFFSET 10
#define VV_RCRB_GCS_BBSIZE 0x60000000
#define VV_RCRB_GCS_BBSIZE_OFFSET 29

#ifdef USE_BBSNAMES

static const char* vv_bbs_names[] = {
	"LPC",
	"reserved",
	"reserved",
	"SPI"
};

static const char* vv_bbsize[] = {
	"64KB",
	"128KB",
	"256KB",
	"reserved"
};

#endif

typedef struct vv_ctx {
	pci_device_t* dev;
	int memfd;
	uint32_t rcbr_memsize;
	void* rcbr;
	uint32_t spi_memsize;
	void* spimem;
	jedec_id_t flash_id;
	int spilockdown;
} vv_ctx_t;

static inline uint32_t
vv_rcrb_readl(const vv_ctx_t* ctx, uint32_t reg) {
	return PCI_READL(ctx->rcbr, reg);
}

static inline uint8_t
vv_spi_readb(const vv_ctx_t* ctx, uint32_t reg) {
	return PCI_READB(ctx->spimem, reg);
}

static inline uint16_t
vv_spi_readw(const vv_ctx_t* ctx, uint32_t reg) {
	return PCI_READW(ctx->spimem, reg);
}

static inline uint32_t
vv_spi_readl(const vv_ctx_t* ctx, uint32_t reg) {
	return PCI_READL(ctx->spimem, reg);
}

static inline void
vv_spi_writeb(const vv_ctx_t* ctx, uint32_t reg, uint8_t value) {
	PCI_WRITEB(ctx->spimem, reg, value);
}

static inline void
vv_spi_writew(const vv_ctx_t* ctx, uint32_t reg, uint16_t value) {
	PCI_WRITEW(ctx->spimem, reg, value);
}

static inline void
vv_spi_writel(const vv_ctx_t* ctx, uint32_t reg, uint32_t value) {
	PCI_WRITEL(ctx->spimem, reg, value);
}

static inline int
vv_spi_sw_wait_cip(vv_ctx_t* ctx, int timeout) {
	uint16_t spis;
	do {
		usleep(100);
		spis = vv_spi_readl(ctx, VV_SPI_SSFSTS);
	} while ((spis & VV_SPI_SSFSTS_SCIP) && --timeout);
	return timeout;
}

static inline int
vv_spi_sw_wait_done(vv_ctx_t* ctx, int timeout) {
	uint16_t spis;
	do {
		usleep(100);
		spis = vv_spi_readl(ctx, VV_SPI_SSFSTS);
	} while (((spis & (VV_SPI_SSFSTS_CDS | VV_SPI_SSFSTS_FCERR)) == 0) && --timeout);
	return timeout;
}

static inline void
vv_spi_sw_clr_errors(vv_ctx_t* ctx) {
	uint32_t status = (VV_SPI_SSFSTS_FCERR | VV_SPI_SSFSTS_CDS);
	vv_spi_writel(ctx, VV_SPI_SSFSTS, status);
}

static int
vv_spi_opcode_index(vv_ctx_t* ctx, uint8_t cmd) {
	int i;
	uint64_t opmenu;
	opmenu = vv_spi_readl(ctx, VV_SPI_OPMENU1);
	opmenu <<= 32;
	opmenu |= vv_spi_readl(ctx, VV_SPI_OPMENU0);
	NVR_DEBUG("OPMENU: 0x%016lx\n", opmenu);
	for (i = 0; i < 8; ++i) {
		if ((opmenu & 0xff) == cmd) {
			break;
		}
		opmenu >>= 8;
	}

	if (i == 8) {
		NVR_ERROR("Opcode 0x%02x not found!\n", cmd);
		return -1;
	}
	NVR_DEBUG("OPCODE %02x found at index %d\n", cmd, i);
	return i;
}

static void
clear_fdata(vv_ctx_t* ctx) {
	int i;
	for (i = 0; i < 16; ++i) {
		vv_spi_writel(ctx, VV_SPI_FDATA0 + (i * 4), 0);
	}
}

#ifdef VV_DIAG
static void
dump_fdata(vv_ctx_t* ctx, int max) {
	int i;
	uint32_t val;
	for (i = 0; i < max; ++i) {
		val = vv_spi_readl(ctx, VV_SPI_FDATA0 + (i * 4));
		NVR_DEBUG("  FDATA%d: 0x%08x\n", i, val);
	}
}
#endif

static int
vv_spi_sw_read_data(vv_ctx_t* ctx, uint8_t* data, uint8_t len) {
	int i;
	uint32_t x = 0;
	for (i = 0; i < len; ++i) {
		if ((i % 4) == 0) {
			x = vv_spi_readl(ctx, VV_SPI_FDATA0 + i);
		}
		data[i] = (x >> ((i % 4) * 8)) & 0xff;
	}
	return 0;
}

static int
vv_spi_sw_read_cmd(vv_ctx_t* ctx, uint8_t cmd, uint8_t* data, uint8_t outlen) {
	int timeout = 10 * 60;
	uint32_t status;
	int index;

	/* make sure we have opcode in our opmenu */
	index = vv_spi_opcode_index(ctx, cmd);
	if (index < 0) {
		return -1;
	}

	timeout = vv_spi_sw_wait_cip(ctx, 10 * 60);
	if (timeout == 0) {
		NVR_ERROR("Timeout waiting for current Cycle in Progress..");
		return -10;
	}
	vv_spi_sw_clr_errors(ctx);

	status = ((uint32_t)(index & 0x07)) << VV_SPI_SSFSTS_COP_OFFSET;
	if (outlen > 0 && outlen <= 64) {
		status |= VV_SPI_SSFSTS_DC;
		status |= (outlen - 1) << VV_SPI_SSFSTS_DBC_OFFSET;
	}
	status |= VV_SPI_SSFSTS_SCGO;
	NVR_DEBUG("Sending cmd using status 0x%08x\n", status);
	vv_spi_writel(ctx, VV_SPI_SSFSTS, status);

	timeout = vv_spi_sw_wait_done(ctx, 10 * 60);
	if (timeout == 0) {
		NVR_ERROR("Timeout waiting for SPI command (%02x) completion...", cmd);
		return -11;
	}
	status = vv_spi_readl(ctx, VV_SPI_SSFSTS);
	vv_spi_sw_clr_errors(ctx);
	if (status & VV_SPI_SSFSTS_FCERR) {
		return -20;
	}

	vv_spi_sw_read_data(ctx, data, outlen);
	return 0;
}

static vv_ctx_t*
vv_ctx_create(pci_device_t* dev, uint32_t rcba_ba, uint32_t rcba_memsize, uint32_t spibase_ba, uint32_t spibase_memsize) {
	if (!dev) {
		return NULL;
	}

        uint8_t* rcbrmem;
	int memfd = open("/dev/mem", O_RDWR);
	if (memfd < 0) {
		NVR_ERROR("Failed opening /dev/mem: %s\n", strerror(errno));
		return NULL;
	}
	NVR_DEBUG("Mapping 0x%x area at offset 0x%08x..\n", rcba_memsize, rcba_ba);
	rcbrmem = mmap(0, rcba_memsize, PROT_READ | PROT_WRITE, MAP_SHARED, memfd, rcba_ba);
	if (rcbrmem == MAP_FAILED) {
		NVR_ERROR("Failed mapping 0x%x area at offset 0x%08x: %s\n",
				rcba_memsize, rcba_ba, strerror(errno));
		close(memfd);
		return NULL;
	}

	uint8_t* spimem;
	NVR_DEBUG("Mapping 0x%x area at offset 0x%08x..\n", spibase_memsize, spibase_ba);
	spimem = mmap(0, spibase_memsize, PROT_READ | PROT_WRITE, MAP_SHARED, memfd, spibase_ba);
	if (spimem == MAP_FAILED) {
		NVR_ERROR("Failed mapping 0x%x area at offset 0x%08x: %s\n",
				spibase_memsize, spibase_ba, strerror(errno));
		munmap(rcbrmem, rcba_memsize);
		close(memfd);
		return NULL;
	}

	vv_ctx_t* ctx = calloc(1, sizeof(vv_ctx_t));
	ctx->dev = dev;
	ctx->memfd = memfd;
	ctx->rcbr_memsize = rcba_memsize;
	ctx->rcbr = rcbrmem;
	ctx->spi_memsize = spibase_memsize;
	ctx->spimem = spimem;
	ctx->flash_id.vendor = 0xff;
	ctx->flash_id.flashmodel = 0xffff;
	ctx->spilockdown = 0;

#ifdef VV_DIAG
	uint32_t val = vv_rcrb_readl(ctx, VV_RCRB_GCS);
	uint32_t bbs = reg_value(VV_RCRB_GCS, BBS, val);
	uint32_t bb_size = reg_value(VV_RCRB_GCS, BBSIZE, val);
	NVR_DEBUG("RCRB: 0x%08x, Lock down: %s, Top Swap: %s, BBS: 0x%02x (%s), Boot block size: 0x%02x (%s)\n",
		val,
		(reg_value(VV_RCRB_GCS, BILD, val)) ? "yes" : "no",
		(reg_value(VV_RCRB_GCS, TOPSWAP, val)) ? "yes" : "no",
		bbs, vv_bbs_names[bbs],
		bb_size, vv_bbsize[bb_size]);

	val = vv_spi_readl(ctx, VV_SPI_BCR);
	NVR_DEBUG("BCR: 0x%08x, Lock Enable: 0x%02x, SRC: 0x%04x, EISS: 0x%04x\n",
		val,
		reg_value(VV_SPI_BCR, LOCK_EN, val),
		reg_value(VV_SPI_BCR, SRC, val),
		reg_value(VV_SPI_BCR, EISS, val));

	val = vv_spi_readl(ctx, VV_SPI_FADDR);
	NVR_DEBUG("FADDR: 0x%08x, FLA: 0x%08x\n", val, reg_value(VV_SPI_FADDR, FLA, val));

	uint16_t val16 = vv_spi_readw(ctx, VV_SPI_PREOP);
	NVR_DEBUG("PREOP: 0x%04x (PO0: 0x%02x, PO1: 0x%02x)\n",
		val16,
		reg_value(VV_SPI_PREOP, PO0, val16),
		reg_value(VV_SPI_PREOP, PO1, val16));

	val = vv_spi_readl(ctx, VV_SPI_OPMENU0);
	NVR_DEBUG("OPMENU0: 0x%08x\n", val);
	val = vv_spi_readl(ctx, VV_SPI_OPMENU1);
	NVR_DEBUG("OPMENU1: 0x%08x\n", val);
	val = vv_spi_readw(ctx, VV_SPI_OPTYPE);
	NVR_DEBUG("OPTYPE: 0x%04x\n", val);

	val = vv_spi_readw(ctx, VV_SPI_HSFSTS);
	uint32_t fdv = reg_value(VV_SPI_HSFSTS, FDV, val);
	NVR_DEBUG("Hardware sequencing Flash Status: 0x%08x; FDV: %s\n",
			val, fdv ? "hw" : "sw!");

	uint8_t id[16];
	memset(id, 0, 16);

	vv_spi_writew(ctx, VV_SPI_PREOP, 0x00);
	vv_spi_writel(ctx, VV_SPI_FADDR, 0x00);

	clear_fdata(ctx);
#if 0
	int i;
	val = vv_spi_sw_read_cmd(ctx, 0x9f, id, 4, 0);
	printf("ID 9f:   ");
	for (i = 0; i < 16; ++i) {
		printf("%02x ", id[i]);
	}
	dump_fdata(ctx);
	printf("\n");

	clear_fdata(ctx);
	memset(id, 0, 16);
	val = vv_spi_sw_read_cmd(ctx, 0x90, id, 2, 0);
	printf("ID 90:   ");
	for (i = 0; i < 16; ++i) {
		printf("%02x ", id[i]);
	}
	printf("\n");

	clear_fdata(ctx);
	memset(id, 0, 16);
	val = vv_spi_sw_read_cmd(ctx, 0xab, id, 1, 0);
	printf("ID ab:   ");
	for (i = 0; i < 16; ++i) {
		printf("%02x ", id[i]);
	}
	printf("\n");
#endif
#endif

	return ctx;
}

static void
vv_ctx_destroy(vv_ctx_t* ctx) {
	if (!ctx)
		return;
	if (ctx->rcbr) {
		munmap(ctx->rcbr, ctx->rcbr_memsize);
		ctx->rcbr = NULL;
	}
	if (ctx->spimem) {
		munmap(ctx->spimem, ctx->spi_memsize);
		ctx->spimem = NULL;
	}
	close(ctx->memfd);
	free(ctx);
}


static void
vv_destroy(nvrhw_t* x) {
	if (!x)
		return;
	if (x->ctx) {
		vv_ctx_destroy(x->ctx);
	}
	free(x);
}

static int
vv_spi_opcode_validate(vv_ctx_t* ctx, uint8_t opcode) {
	int opcode_index = vv_spi_opcode_index(ctx, opcode);
	if (opcode_index < 0) {
		if (ctx->spilockdown) {
			return -2;
		}
		vv_spi_writew(ctx, VV_SPI_OPTYPE, 0x043b);
		vv_spi_writel(ctx, VV_SPI_OPMENU0, 0x05200302);
		vv_spi_writel(ctx, VV_SPI_OPMENU1, 0x0000019f | (opcode << 16));
		opcode_index = vv_spi_opcode_index(ctx, opcode);
		/* reprogramming opcodes failed? can't do anything else */
		if (opcode_index < 0) {
			return -3;
		}
	}
	return 0;
}

static int
vv_spi_get_jedec_id(vv_ctx_t* ctx, uint8_t* vendor, uint16_t* flashinfo) {
	uint8_t jedecid[4];
	int rc;
	if (!ctx || !vendor || !flashinfo)
		return -1;

	if (ctx->flash_id.vendor != 0xff && ctx->flash_id.flashmodel != 0xffff) {
		*vendor = ctx->flash_id.vendor;
		*flashinfo = ctx->flash_id.flashmodel;
		return 0;
	}
	rc = vv_spi_opcode_validate(ctx, 0x9f);
	if (rc != 0) {
		return -2;
	}
	memset(jedecid, 0, 4);
	clear_fdata(ctx);

	rc = vv_spi_sw_read_cmd(ctx, 0x9f, jedecid, 4);
	if (rc == 0) {
		ctx->flash_id.vendor = jedecid[0];
		ctx->flash_id.flashmodel = jedecid[1] << 8 | jedecid[2];
		*vendor = ctx->flash_id.vendor;
		*flashinfo = ctx->flash_id.flashmodel;
	}

	return rc;
}

static int
vv_spi_get_4b_unique_id(vv_ctx_t* ctx, uint8_t* buffer, size_t buflen) {
	uint8_t uniqid[12];
	int rc;
	if (!ctx)
		return -1;

	if (!buffer || buflen == 0)
		return 8; // return preferred size

	rc = vv_spi_opcode_validate(ctx, 0x4b);
	if (rc != 0) {
		return -2;
	}

	// 4b instruction requires 4 additional cycles, hence uniqid length is 12
	// and later we skip 4 bytes
	rc = vv_spi_sw_read_cmd(ctx, 0x4b, uniqid, sizeof(uniqid));
	if (rc == 0) {
		uint8_t* p = uniqid + 4;
		if (buflen < 8)
			p += 8 - buflen;
		else
			buflen = 8;
		memcpy(buffer, p, buflen);
	}

	return rc;
}

static int
vv_spi_get_unique_id(vv_ctx_t* ctx, uint8_t* buffer, size_t buflen) {
	uint8_t flash_vendor = 0;
	uint16_t flash_model = 0;

	memset(buffer, 0, buflen);

	vv_spi_get_jedec_id(ctx, &flash_vendor, &flash_model);
	switch (flash_vendor) {
	case 0xef: /* Winbond */
	case 0xc8: /* Gigadevice */
		switch (flash_model) {
		case 0x6017:
			return vv_spi_get_4b_unique_id(ctx, buffer, buflen);
		}
		break;
	}

	/* unsupported flash manufacturer */
	return -100;
}

static int
vv_get_jedec_id(nvrhw_t* x, uint8_t* vendor, uint16_t* flashinfo) {
	return vv_spi_get_jedec_id(x->ctx, vendor, flashinfo);
}

static int
vv_get_unique_id(nvrhw_t* x, uint8_t* buffer, size_t buflen) {
	return vv_spi_get_unique_id(x->ctx, buffer, buflen);
}

/* TODO: this is copy-paste from ich7 - get rid of it */
static int
vv_get_cpu_id(__ATTRIB_UNUSED nvrhw_t* x, uint8_t* buffer, size_t buflen) {
	uint32_t eax, ebx, ecx, edx;
	int cnt, i;
	// return preferred size if buffer is NULL or len is 0
	if (!buffer || buflen == 0)
		return 8;
	if (!buffer || buflen < 8)
		return -1;
	eax = 1; ebx = ecx = edx = 0;
	x86_cpuid(&eax, &ebx, &ecx, &edx);

	cnt = 0;
	// EAX bytes:
	//      stepping+model
	//      family and type
	//      extended model
	//      extended family
	buffer[cnt++] = eax & 0xff;
	buffer[cnt++] = (eax >> 8) & 0xff;
	buffer[cnt++] = (eax >> 16) & 0xff;
	buffer[cnt++] = (eax >> 20) & 0xff;

	// EDX as extra, so we match dmidecode CPU ID
	for (i = 0; i < 4; ++i) {
		buffer[cnt++] = edx & 0xff;
		edx >>= 8;
	}

	return cnt;
}

#ifndef USE_PRINTINFO

#define vv_printinfo 0

#else

static void
vv_printinfo(nvrhw_t* x, int (*printfunc)(const char *,...)) {
	if (!x || !x->ctx || !printfunc) {
		return;
	}

	vv_ctx_t* ctx = x->ctx;
	if (ctx->dev) {
		NVR_DEBUG("ctx->dev is non-null\n");
	}

	uint32_t val = vv_rcrb_readl(ctx, VV_RCRB_GCS);
	uint32_t bbs = reg_value(VV_RCRB_GCS, BBS, val);
	uint32_t bb_size = reg_value(VV_RCRB_GCS, BBSIZE, val);
	NVR_DEBUG("RCRB: 0x%08x, Lock down: %s, Top Swap: %s, BBS: 0x%02x (%s), Boot block size: 0x%02x (%s)\n",
		val,
		(reg_value(VV_RCRB_GCS, BILD, val)) ? "yes" : "no",
		(reg_value(VV_RCRB_GCS, TOPSWAP, val)) ? "yes" : "no",
		bbs, vv_bbs_names[bbs],
		bb_size, vv_bbsize[bb_size]);

	val = vv_spi_readl(ctx, VV_SPI_BCR);
	NVR_DEBUG("BCR: 0x%08x, Lock Enable: 0x%02x, SRC: 0x%04x, EISS: 0x%04x\n",
		val,
		reg_value(VV_SPI_BCR, LOCK_EN, val),
		reg_value(VV_SPI_BCR, SRC, val),
		reg_value(VV_SPI_BCR, EISS, val));

	val = vv_spi_readl(ctx, VV_SPI_FADDR);
	NVR_DEBUG("FADDR: 0x%08x, FLA: 0x%08x\n", val, reg_value(VV_SPI_FADDR, FLA, val));

	uint16_t val16 = vv_spi_readw(ctx, VV_SPI_PREOP);
	NVR_DEBUG("PREOP: 0x%04x (PO0: 0x%02x, PO1: 0x%02x)\n",
		val16,
		reg_value(VV_SPI_PREOP, PO0, val16),
		reg_value(VV_SPI_PREOP, PO1, val16));

	val = vv_spi_readl(ctx, VV_SPI_OPMENU0);
	NVR_DEBUG("OPMENU0: 0x%08x\n", val);
	val = vv_spi_readl(ctx, VV_SPI_OPMENU1);
	NVR_DEBUG("OPMENU1: 0x%08x\n", val);
	val = vv_spi_readw(ctx, VV_SPI_OPTYPE);
	NVR_DEBUG("OPTYPE: 0x%04x\n", val);

	val = vv_spi_readw(ctx, VV_SPI_HSFSTS);
	uint32_t fdv = reg_value(VV_SPI_HSFSTS, FDV, val);
	NVR_DEBUG("Hardware sequencing Flash Status: 0x%08x; FDV: %s\n",
			val, fdv ? "hw" : "sw!");

	uint8_t id[16];
	memset(id, 0, 16);

	vv_spi_writew(ctx, VV_SPI_PREOP, 0x00);
	vv_spi_writel(ctx, VV_SPI_FADDR, 0x00);

	clear_fdata(ctx);
#if 0
	int i;
	val = vv_spi_sw_read_cmd(ctx, 0x9f, id, 4, 0);
	printf("ID 9f:   ");
	for (i = 0; i < 16; ++i) {
		printf("%02x ", id[i]);
	}
	dump_fdata(ctx);
	printf("\n");

	clear_fdata(ctx);
	memset(id, 0, 16);
	val = vv_spi_sw_read_cmd(ctx, 0x90, id, 2, 0);
	printf("ID 90:   ");
	for (i = 0; i < 16; ++i) {
		printf("%02x ", id[i]);
	}
	printf("\n");

	clear_fdata(ctx);
	memset(id, 0, 16);
	val = vv_spi_sw_read_cmd(ctx, 0xab, id, 1, 0);
	printf("ID ab:   ");
	for (i = 0; i < 16; ++i) {
		printf("%02x ", id[i]);
	}
	printf("\n");
#endif

}
#endif /* USE_PRINTINFO */

static nvrhw_t*
valleyview_detect(void) {
	uint32_t rcba = 0, rcba_ba = 0;
	uint32_t spibase = 0, spibase_ba = 0;
#if 1
	pci_device_t* dev = pci_find_device(0x8086, 0x0f1c);
	if (dev == NULL)
		return NULL;

	dev->cfg_read(dev, VV_RCBA, (uint8_t*)&rcba, sizeof(rcba));
	dev->cfg_read(dev, VV_SPIBASE, (uint8_t*)&spibase, sizeof(spibase));
#else
	rcba = 0xfed1c001;
	spibase = 0xfed01002;
#endif
	rcba_ba = rcba & VV_RCBA_BA;
	NVR_DEBUG("RCRB enabled: %s\n", (rcba & 1) ? "yes" : "no");
	NVR_DEBUG("RCBA_BA: 0x%08x\n", rcba_ba);
	if (rcba_ba == 0) {
		return NULL;
	}
	spibase_ba = spibase & VV_SPIBASE_BA;
	NVR_DEBUG("SPIBASE_BA: 0x%08x\n", spibase_ba);
	if (spibase_ba == 0) {
		return NULL;
	}

	vv_ctx_t* ctx = vv_ctx_create(dev, rcba_ba, 0x4000, spibase_ba, 0x4000);
	if (!ctx) {
		return NULL;
	}

	nvrhw_t* box = calloc(1, sizeof(nvrhw_t));
	box->ctx = ctx;
	box->get_jedec_id = vv_get_jedec_id;
	box->get_unique_id = vv_get_unique_id;
	box->get_cpu_id = vv_get_cpu_id;
	box->printinfo = vv_printinfo;
	box->test = NULL;
	box->destroy = vv_destroy;

	return box;
}

static nvrhw_t* nvrhw_ctx = NULL;

__FS_FUNCTION_PREFER_INLINE nvrhw_t*
nvrhw_get(void) {
	if (nvrhw_ctx == NULL) {
		nvrhw_ctx = ich7nvr_detect();
		if (nvrhw_ctx == NULL) {
			nvrhw_ctx = valleyview_detect();
		}
	}
	return nvrhw_ctx;
}

__FS_FUNCTION_PREFER_INLINE u_int32_t
nvrhw_get_jedec_id(void) {
	uint8_t vendor = 0;
	uint16_t flashinfo = 0;
	nvrhw_t* hw = nvrhw_get();
	if (!hw) {
		return 0;
	}
	hw->get_jedec_id(hw, &vendor, &flashinfo);
	return (vendor << 16) | flashinfo;
}

__FS_FUNCTION_PREFER_INLINE size_t
nvrhw_get_unique_id(uint8_t* buffer, size_t buflen) {
	int rc;
	nvrhw_t* hw = nvrhw_get();
	if (!hw) {
		NVR_ERROR("Unsupported NVRx64 hardware!");
		return 0;
	}
	if (buflen < 8) {
		NVR_ERROR("Buffer size too small");
		return 0;
	}
	rc = hw->get_unique_id(hw, buffer, buflen);
	if (rc != 0) {
		return 0;
	}
	return 8;
}

#else

#define nvrhw_get_jedec_id() 0
#define nvrhw_get_unique_id(a, b) 0

#endif /* __KERNEL__ */


__FS_FUNCTION_PREFER_INLINE size_t
fs_read_flash_uid_hw(__ATTRIB_UNUSED u_int8_t* dest, __ATTRIB_UNUSED size_t dest_len) {
	return nvrhw_get_unique_id(dest, dest_len);
}

__FS_FUNCTION_PREFER_INLINE u_int32_t
fs_read_flash_type_id_hw(void) {
	return nvrhw_get_jedec_id();
}

#endif // #if UBNT_NVRx64

