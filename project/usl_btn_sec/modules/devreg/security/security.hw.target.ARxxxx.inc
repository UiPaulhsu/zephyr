#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_MIPS_ARxxxx) || SECURITY_ENABLE_SIMULATION)

// CPU revision ID register
#define __ARxxxx_REV_ID                     ((uintptr_t)(0x18060090))
#define __ARxxxx_REV_ID_MASK_MAJOR          0xfff0u
#define __ARxxxx_REV_ID_MASK_MINOR          0x000fu
#define __ARxxxx_REV_ID_MASK                (__ARxxxx_REV_ID_MASK_MAJOR | __ARxxxx_REV_ID_MASK_MINOR)

#define __H_SREV_ID                         ((uintptr_t)(0x4020))

#define __AR933X_RADIO1___H_SREV_ID         ((uintptr_t)(0xb8100000+__H_SREV_ID )) // verified - hornet

// AR7240 - Python --- MAJOR 0x00c
#define __AR7240_REV_1_x                    0x00c0
#define __AR7240_REV_1_0                    (__AR7240_REV_1_x|0x0)
#define __AR7240_REV_1_1                    (__AR7240_REV_1_x|0x1)
#define __AR7240_REV_1_2                    (__AR7240_REV_1_x|0x2)
#define __AR7240_REV_1_3                    (__AR7240_REV_1_x|0x3)
#define __AR7240_REV_1_4                    (__AR7240_REV_1_x|0x4)
#define __AR7240_REV_1_5                    (__AR7240_REV_1_x|0x5)
#define __AR7240_REV_1_6                    (__AR7240_REV_1_x|0x6)
#define __AR7240_REV_1_7                    (__AR7240_REV_1_x|0x7)
#define __AR7240_REV_1_8                    (__AR7240_REV_1_x|0x8)
#define __AR7240_REV_1_9                    (__AR7240_REV_1_x|0x9)
#define __AR7240_REV_1_10                   (__AR7240_REV_1_x|0xa)
#define __AR7240_REV_1_11                   (__AR7240_REV_1_x|0xb)
#define __AR7240_REV_1_12                   (__AR7240_REV_1_x|0xc)
#define __AR7240_REV_1_13                   (__AR7240_REV_1_x|0xd)
#define __AR7240_REV_1_14                   (__AR7240_REV_1_x|0xe)
#define __AR7240_REV_1_15                   (__AR7240_REV_1_x|0xf)

// AR7241 - Virian (old) --- MAJOR 0x010
#define __AR7241_REV_1_x                    0x0100
#define __AR7241_REV_1_0                    (__AR7241_REV_1_x|0x0)
#define __AR7241_REV_1_1                    (__AR7241_REV_1_x|0x1)
#define __AR7241_REV_1_2                    (__AR7241_REV_1_x|0x2)
#define __AR7241_REV_1_3                    (__AR7241_REV_1_x|0x3)
#define __AR7241_REV_1_4                    (__AR7241_REV_1_x|0x4)
#define __AR7241_REV_1_5                    (__AR7241_REV_1_x|0x5)
#define __AR7241_REV_1_6                    (__AR7241_REV_1_x|0x6)
#define __AR7241_REV_1_7                    (__AR7241_REV_1_x|0x7)
#define __AR7241_REV_1_8                    (__AR7241_REV_1_x|0x8)
#define __AR7241_REV_1_9                    (__AR7241_REV_1_x|0x9)
#define __AR7241_REV_1_10                   (__AR7241_REV_1_x|0xa)
#define __AR7241_REV_1_11                   (__AR7241_REV_1_x|0xb)
#define __AR7241_REV_1_12                   (__AR7241_REV_1_x|0xc)
#define __AR7241_REV_1_13                   (__AR7241_REV_1_x|0xd)
#define __AR7241_REV_1_14                   (__AR7241_REV_1_x|0xe)
#define __AR7241_REV_1_15                   (__AR7241_REV_1_x|0xf)

// AR7242 - Virian --- MAJOR 0x110
#define __AR7242_REV_1_x                    0x1100
#define __AR7242_REV_1_0                    (__AR7242_REV_1_x|0x0)
#define __AR7242_REV_1_1                    (__AR7242_REV_1_x|0x1)
#define __AR7242_REV_1_2                    (__AR7242_REV_1_x|0x2)
#define __AR7242_REV_1_3                    (__AR7242_REV_1_x|0x3)
#define __AR7242_REV_1_4                    (__AR7242_REV_1_x|0x4)
#define __AR7242_REV_1_5                    (__AR7242_REV_1_x|0x5)
#define __AR7242_REV_1_6                    (__AR7242_REV_1_x|0x6)
#define __AR7242_REV_1_7                    (__AR7242_REV_1_x|0x7)
#define __AR7242_REV_1_8                    (__AR7242_REV_1_x|0x8)
#define __AR7242_REV_1_9                    (__AR7242_REV_1_x|0x9)
#define __AR7242_REV_1_10                   (__AR7242_REV_1_x|0xa)
#define __AR7242_REV_1_11                   (__AR7242_REV_1_x|0xb)
#define __AR7242_REV_1_12                   (__AR7242_REV_1_x|0xc)
#define __AR7242_REV_1_13                   (__AR7242_REV_1_x|0xd)
#define __AR7242_REV_1_14                   (__AR7242_REV_1_x|0xe)
#define __AR7242_REV_1_15                   (__AR7242_REV_1_x|0xf)

// AR9330 - Hornet -- MAJOR 0x011
#define __AR9330_REV_1_x                    0x0110
#define __AR9330_REV_1_0                    (__AR9330_REV_1_x|0x0)
#define __AR9330_REV_1_1                    (__AR9330_REV_1_x|0x1)
#define __AR9330_REV_1_2                    (__AR9330_REV_1_x|0x2)
#define __AR9330_REV_1_3                    (__AR9330_REV_1_x|0x3)
#define __AR9330_REV_1_4                    (__AR9330_REV_1_x|0x4)
#define __AR9330_REV_1_5                    (__AR9330_REV_1_x|0x5)
#define __AR9330_REV_1_6                    (__AR9330_REV_1_x|0x6)
#define __AR9330_REV_1_7                    (__AR9330_REV_1_x|0x7)
#define __AR9330_REV_1_8                    (__AR9330_REV_1_x|0x8)
#define __AR9330_REV_1_9                    (__AR9330_REV_1_x|0x9)
#define __AR9330_REV_1_10                   (__AR9330_REV_1_x|0xA)
#define __AR9330_REV_1_11                   (__AR9330_REV_1_x|0xB)
#define __AR9330_REV_1_12                   (__AR9330_REV_1_x|0xC)
#define __AR9330_REV_1_13                   (__AR9330_REV_1_x|0xD)
#define __AR9330_REV_1_14                   (__AR9330_REV_1_x|0xE)
#define __AR9330_REV_1_15                   (__AR9330_REV_1_x|0xF)

// AR9331 - Hornet -- MAJOR 0x111
#define __AR9331_REV_1_x                    0x1110
#define __AR9331_REV_1_0                    (__AR9331_REV_1_x|0x0)
#define __AR9331_REV_1_1                    (__AR9331_REV_1_x|0x1)
#define __AR9331_REV_1_2                    (__AR9331_REV_1_x|0x2)
#define __AR9331_REV_1_3                    (__AR9331_REV_1_x|0x3)
#define __AR9331_REV_1_4                    (__AR9331_REV_1_x|0x4)
#define __AR9331_REV_1_5                    (__AR9331_REV_1_x|0x5)
#define __AR9331_REV_1_6                    (__AR9331_REV_1_x|0x6)
#define __AR9331_REV_1_7                    (__AR9331_REV_1_x|0x7)
#define __AR9331_REV_1_8                    (__AR9331_REV_1_x|0x8)
#define __AR9331_REV_1_9                    (__AR9331_REV_1_x|0x9)
#define __AR9331_REV_1_10                   (__AR9331_REV_1_x|0xA)
#define __AR9331_REV_1_11                   (__AR9331_REV_1_x|0xB)
#define __AR9331_REV_1_12                   (__AR9331_REV_1_x|0xC)
#define __AR9331_REV_1_13                   (__AR9331_REV_1_x|0xD)
#define __AR9331_REV_1_14                   (__AR9331_REV_1_x|0xE)
#define __AR9331_REV_1_15                   (__AR9331_REV_1_x|0xF)

// AR9341 - Wasp -- MAJOR 0x012
#define __AR9341_REV_1_x                    0x0120
#define __AR9341_REV_1_0                    (__AR9341_REV_1_x|0x0)
#define __AR9341_REV_1_1                    (__AR9341_REV_1_x|0x1)
#define __AR9341_REV_1_2                    (__AR9341_REV_1_x|0x2)
#define __AR9341_REV_1_3                    (__AR9341_REV_1_x|0x3)
#define __AR9341_REV_1_4                    (__AR9341_REV_1_x|0x4)
#define __AR9341_REV_1_5                    (__AR9341_REV_1_x|0x5)
#define __AR9341_REV_1_6                    (__AR9341_REV_1_x|0x6)
#define __AR9341_REV_1_7                    (__AR9341_REV_1_x|0x7)
#define __AR9341_REV_1_8                    (__AR9341_REV_1_x|0x8)
#define __AR9341_REV_1_9                    (__AR9341_REV_1_x|0x9)
#define __AR9341_REV_1_10                   (__AR9341_REV_1_x|0xA)
#define __AR9341_REV_1_11                   (__AR9341_REV_1_x|0xB)
#define __AR9341_REV_1_12                   (__AR9341_REV_1_x|0xC)
#define __AR9341_REV_1_13                   (__AR9341_REV_1_x|0xD)
#define __AR9341_REV_1_14                   (__AR9341_REV_1_x|0xE)
#define __AR9341_REV_1_15                   (__AR9341_REV_1_x|0xF)

// AR9342 - Wasp -- MAJOR 0x112
#define __AR9342_REV_1_x                    0x1120
#define __AR9342_REV_1_0                    (__AR9342_REV_1_x|0x0)
#define __AR9342_REV_1_1                    (__AR9342_REV_1_x|0x1)
#define __AR9342_REV_1_2                    (__AR9342_REV_1_x|0x2)
#define __AR9342_REV_1_3                    (__AR9342_REV_1_x|0x3)
#define __AR9342_REV_1_4                    (__AR9342_REV_1_x|0x4)
#define __AR9342_REV_1_5                    (__AR9342_REV_1_x|0x5)
#define __AR9342_REV_1_6                    (__AR9342_REV_1_x|0x6)
#define __AR9342_REV_1_7                    (__AR9342_REV_1_x|0x7)
#define __AR9342_REV_1_8                    (__AR9342_REV_1_x|0x8)
#define __AR9342_REV_1_9                    (__AR9342_REV_1_x|0x9)
#define __AR9342_REV_1_10                   (__AR9342_REV_1_x|0xA)
#define __AR9342_REV_1_11                   (__AR9342_REV_1_x|0xB)
#define __AR9342_REV_1_12                   (__AR9342_REV_1_x|0xC)
#define __AR9342_REV_1_13                   (__AR9342_REV_1_x|0xD)
#define __AR9342_REV_1_14                   (__AR9342_REV_1_x|0xE)
#define __AR9342_REV_1_15                   (__AR9342_REV_1_x|0xF)

// AR9344 - Wasp -- MAJOR 0x212
#define __AR9344_REV_1_x                    0x2120
#define __AR9344_REV_1_0                    (__AR9344_REV_1_x|0x0)
#define __AR9344_REV_1_1                    (__AR9344_REV_1_x|0x1)
#define __AR9344_REV_1_2                    (__AR9344_REV_1_x|0x2)
#define __AR9344_REV_1_3                    (__AR9344_REV_1_x|0x3)
#define __AR9344_REV_1_4                    (__AR9344_REV_1_x|0x4)
#define __AR9344_REV_1_5                    (__AR9344_REV_1_x|0x5)
#define __AR9344_REV_1_6                    (__AR9344_REV_1_x|0x6)
#define __AR9344_REV_1_7                    (__AR9344_REV_1_x|0x7)
#define __AR9344_REV_1_8                    (__AR9344_REV_1_x|0x8)
#define __AR9344_REV_1_9                    (__AR9344_REV_1_x|0x9)
#define __AR9344_REV_1_10                   (__AR9344_REV_1_x|0xA)
#define __AR9344_REV_1_11                   (__AR9344_REV_1_x|0xB)
#define __AR9344_REV_1_12                   (__AR9344_REV_1_x|0xC)
#define __AR9344_REV_1_13                   (__AR9344_REV_1_x|0xD)
#define __AR9344_REV_1_14                   (__AR9344_REV_1_x|0xE)
#define __AR9344_REV_1_15                   (__AR9344_REV_1_x|0xF)

// QCA9550 - Scorpion -- MAJOR 0x1130
#define __QCA955x_REV_1_x                    0x1130
#define __QCA955x_REV_1_0                    (__QCA955x_REV_1_x|0x0)
#define __QCA955x_REV_1_1                    (__QCA955x_REV_1_x|0x1)
#define __QCA955x_REV_1_2                    (__QCA955x_REV_1_x|0x2)
#define __QCA955x_REV_1_3                    (__QCA955x_REV_1_x|0x3)
#define __QCA955x_REV_1_4                    (__QCA955x_REV_1_x|0x4)
#define __QCA955x_REV_1_5                    (__QCA955x_REV_1_x|0x5)
#define __QCA955x_REV_1_6                    (__QCA955x_REV_1_x|0x6)
#define __QCA955x_REV_1_7                    (__QCA955x_REV_1_x|0x7)
#define __QCA955x_REV_1_8                    (__QCA955x_REV_1_x|0x8)
#define __QCA955x_REV_1_9                    (__QCA955x_REV_1_x|0x9)
#define __QCA955x_REV_1_10                   (__QCA955x_REV_1_x|0xA)
#define __QCA955x_REV_1_11                   (__QCA955x_REV_1_x|0xB)
#define __QCA955x_REV_1_12                   (__QCA955x_REV_1_x|0xC)
#define __QCA955x_REV_1_13                   (__QCA955x_REV_1_x|0xD)
#define __QCA955x_REV_1_14                   (__QCA955x_REV_1_x|0xE)
#define __QCA955x_REV_1_15                   (__QCA955x_REV_1_x|0xF)

// QCA9556 - Scorpion -- 0x01360
#define __QCA9556_REV                        __QCA955x_REV_1_6

// QCA9557 - Scorpion -- 0x0137
#define __QCA9557_REV                        __QCA955x_REV_1_7

// QCA956X - Dragonfly -- MAJOR 0x1150
#define __QCA956x_REV_1_x                    0x1150
#define __QCA956x_REV_1_0                    (__QCA956x_REV_1_x|0x0)
#define __QCA956x_REV_1_1                    (__QCA956x_REV_1_x|0x1)
#define __QCA956x_REV_1_2                    (__QCA956x_REV_1_x|0x2)
#define __QCA956x_REV_1_3                    (__QCA956x_REV_1_x|0x3)
#define __QCA956x_REV_1_4                    (__QCA956x_REV_1_x|0x4)
#define __QCA956x_REV_1_5                    (__QCA956x_REV_1_x|0x5)
#define __QCA956x_REV_1_6                    (__QCA956x_REV_1_x|0x6)
#define __QCA956x_REV_1_7                    (__QCA956x_REV_1_x|0x7)
#define __QCA956x_REV_1_8                    (__QCA956x_REV_1_x|0x8)
#define __QCA956x_REV_1_9                    (__QCA956x_REV_1_x|0x9)
#define __QCA956x_REV_1_10                   (__QCA956x_REV_1_x|0xA)
#define __QCA956x_REV_1_11                   (__QCA956x_REV_1_x|0xB)
#define __QCA956x_REV_1_12                   (__QCA956x_REV_1_x|0xC)
#define __QCA956x_REV_1_13                   (__QCA956x_REV_1_x|0xD)
#define __QCA956x_REV_1_14                   (__QCA956x_REV_1_x|0xE)
#define __QCA956x_REV_1_15                   (__QCA956x_REV_1_x|0xF)

__FS_FUNCTION_PREFER_INLINE int fs_is_ar7240(u_int32_t fsa_cpu_silicon_revision)    { return ((fsa_cpu_silicon_revision & __ARxxxx_REV_ID_MASK_MAJOR) == __AR7240_REV_1_x); }
__FS_FUNCTION_PREFER_INLINE int fs_is_ar7241(u_int32_t fsa_cpu_silicon_revision)    { return ((fsa_cpu_silicon_revision & __ARxxxx_REV_ID_MASK_MAJOR) == __AR7241_REV_1_x); }
__FS_FUNCTION_PREFER_INLINE int fs_is_ar7242(u_int32_t fsa_cpu_silicon_revision)    { return ((fsa_cpu_silicon_revision & __ARxxxx_REV_ID_MASK_MAJOR) == __AR7242_REV_1_x); }
__FS_FUNCTION_PREFER_INLINE int fs_is_ar9330(u_int32_t fsa_cpu_silicon_revision)    { return ((fsa_cpu_silicon_revision & __ARxxxx_REV_ID_MASK_MAJOR) == __AR9330_REV_1_x); }
__FS_FUNCTION_PREFER_INLINE int fs_is_ar9331(u_int32_t fsa_cpu_silicon_revision)    { return ((fsa_cpu_silicon_revision & __ARxxxx_REV_ID_MASK_MAJOR) == __AR9331_REV_1_x); }
__FS_FUNCTION_PREFER_INLINE int fs_is_ar9341(u_int32_t fsa_cpu_silicon_revision)    { return ((fsa_cpu_silicon_revision & __ARxxxx_REV_ID_MASK_MAJOR) == __AR9341_REV_1_x); }
__FS_FUNCTION_PREFER_INLINE int fs_is_ar9342(u_int32_t fsa_cpu_silicon_revision)    { return ((fsa_cpu_silicon_revision & __ARxxxx_REV_ID_MASK_MAJOR) == __AR9342_REV_1_x); }
__FS_FUNCTION_PREFER_INLINE int fs_is_ar9344(u_int32_t fsa_cpu_silicon_revision)    { return ((fsa_cpu_silicon_revision & __ARxxxx_REV_ID_MASK_MAJOR) == __AR9344_REV_1_x); }
__FS_FUNCTION_PREFER_INLINE int fs_is_qca9550(u_int32_t fsa_cpu_silicon_revision)   { return ((fsa_cpu_silicon_revision & __ARxxxx_REV_ID_MASK) == __QCA955x_REV_1_0); }
__FS_FUNCTION_PREFER_INLINE int fs_is_qca9556(u_int32_t fsa_cpu_silicon_revision)   { return ((fsa_cpu_silicon_revision & __ARxxxx_REV_ID_MASK) == __QCA9556_REV); }
__FS_FUNCTION_PREFER_INLINE int fs_is_qca9557(u_int32_t fsa_cpu_silicon_revision)   { return ((fsa_cpu_silicon_revision & __ARxxxx_REV_ID_MASK) == __QCA9557_REV); }
__FS_FUNCTION_PREFER_INLINE int fs_is_ar724x(u_int32_t fsa_cpu_silicon_revision)    { return (fs_is_ar7240(fsa_cpu_silicon_revision) || fs_is_ar7241(fsa_cpu_silicon_revision) || fs_is_ar7242(fsa_cpu_silicon_revision)); }
__FS_FUNCTION_PREFER_INLINE int fs_is_ar933x(u_int32_t fsa_cpu_silicon_revision)    { return (fs_is_ar9330(fsa_cpu_silicon_revision) || fs_is_ar9331(fsa_cpu_silicon_revision)); }
__FS_FUNCTION_PREFER_INLINE int fs_is_ar934x(u_int32_t fsa_cpu_silicon_revision)    { return (fs_is_ar9341(fsa_cpu_silicon_revision) || fs_is_ar9342(fsa_cpu_silicon_revision) || fs_is_ar9344(fsa_cpu_silicon_revision)); }
__FS_FUNCTION_PREFER_INLINE int fs_is_qca955x(u_int32_t fsa_cpu_silicon_revision)   { return ((fsa_cpu_silicon_revision & __ARxxxx_REV_ID_MASK_MAJOR) == __QCA955x_REV_1_x); }
__FS_FUNCTION_PREFER_INLINE int fs_is_qca956x(u_int32_t fsa_cpu_silicon_revision)   { return ((fsa_cpu_silicon_revision & __ARxxxx_REV_ID_MASK_MAJOR) == __QCA956x_REV_1_x); }

#if !SECURITY_ENABLE_SIMULATION
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_cpu_rev_id_hw(void) {
	return fs_read_mem32( __ARxxxx_REV_ID );
}
#endif // #if !SECURITY_ENABLE_SIMULATION

// kernel implementation
#ifdef __KERNEL__
#if (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,20))
	#define pci_find_device pci_get_device
#endif
	__FS_FUNCTION_PREFER_INLINE struct pci_dev* fs_read_find_pci(unsigned int radio /* zero based index */) {
		__FS_LOCAL_STATIC_OPTION u_int32_t fsv_t1;
		__FS_LOCAL_STATIC_OPTION struct pci_dev* fsv_t2;
        __FS_LOCAL_STATIC_OPTION u_int16_t fsv_t3;
		fsv_t1 = 0;
		fsv_t2 = NULL;
        fsv_t3 = 0;
		while ((fsv_t2 = pci_find_device(PCI_ANY_ID, PCI_ANY_ID, fsv_t2)) != NULL) {
            fsv_t3 = ((fsv_t2->vendor) & 0xffff);
            if ((fsv_t3 != 0x168c) && (fsv_t3 != 0x0777)) {
                continue;
            }
            if (fsv_t1 == radio) 
                return fsv_t2;
            fsv_t1++;
		}
		fs_debug_printf_off("No radio %d found\n", (radio+1));
		return NULL;
	}
	__FS_FUNCTION_PREFER_INLINE uintptr_t fs_read_find_pci_bar0(unsigned int radio /* zero based index */) {
		__FS_LOCAL_STATIC_OPTION struct pci_dev* fsv_t1;
		fsv_t1 = NULL;
		if ((fsv_t1 = fs_read_find_pci(radio)) != NULL) {
			fs_debug_printf_off("Found radio %d BAR0 at %" PRIxPTR "\n", (radio+1), fsv_t1->resource[0].start);
			return fsv_t1->resource[0].start;
		}
		return 0;
	}
	__FS_FUNCTION_PREFER_INLINE uint32_t fs_read_find_pci_id(unsigned int radio /* zero based index */) {
		__FS_LOCAL_STATIC_OPTION struct pci_dev* fsv_t1;
		fsv_t1 = NULL;
		if ((fsv_t1 = fs_read_find_pci(radio)) != NULL)
			return ((fsv_t1->vendor & 0xFFFF) << 16) | (fsv_t1->device & 0xFFFF);
		return 0;
	}

#else
	typedef struct fs_read_find_pci_ex_data {
		char      line[512];
		int32_t   match;
		u_int32_t bdf;
		u_int32_t vendor_device;
		u_int32_t irq;
		uintptr_t bar0;
		FILE*     p_devices_file;
		int       c;
	} fs_read_find_pci_ex_data_t;

	__FS_FUNCTION_PREFER_INLINE uint32_t fs_read_find_pci_ex(int radio /* zero based index */, const char* pathname, int ret_param /* 0 - return bar0, 1 - return vendor */ ) {
		__FS_LOCAL_STATIC_OPTION uint32_t fsv_t1;
		__FS_LOCAL_STATIC_OPTION fs_read_find_pci_ex_data_t* fsv_t2;
        __FS_LOCAL_STATIC_OPTION uint16_t fsv_t3;
		fsv_t1 = 0;
		fsv_t2 = (fs_read_find_pci_ex_data_t*)fs_zalloc(sizeof(fs_read_find_pci_ex_data_t));
        fsv_t3 = 0;
		if(NULL == fsv_t2) {
			fsv_t1 = 0; // still zero
			goto done;
		}
		fsv_t2->p_devices_file = fs_fopen(pathname, "r");
		if (fsv_t2->p_devices_file != NULL) {
			while (!feof(fsv_t2->p_devices_file) && fgets(fsv_t2->line, sizeof(fsv_t2->line), fsv_t2->p_devices_file)) {
				fsv_t2->c = sscanf(fsv_t2->line, "%x %x %x %" PRIxPTR, &fsv_t2->bdf, &fsv_t2->vendor_device, &fsv_t2->irq, &fsv_t2->bar0);
				if (fsv_t2->c != 4) {
					continue;
				}
                fsv_t3 = ((fsv_t2->vendor_device >> 16) & 0xffff);
                if ((fsv_t3 != 0x168c) && (fsv_t3 != 0x0777)) {
					continue;
				}
				if(fsv_t2->match++ == (radio)) {
					/* Filter out flags */
					switch (ret_param) {
					case 0:
						fsv_t1 = fsv_t2->bar0 - (fsv_t2->bar0 % (u_int32_t)sysconf(_SC_PAGE_SIZE));
						break;
					case 1:
						fsv_t1 = fsv_t2->vendor_device;
						break;
					default:
						fs_debug_printf_off("Found radio %d, but return param (%d) is invalid\n", (radio+1), ret_param);
						fsv_t1 = 0;
					}
					break;
				}
			}
		}
	done:
		if(fsv_t2->p_devices_file != NULL) {
			fs_fclose( fsv_t2->p_devices_file );
			fsv_t2->p_devices_file = NULL;
		}
		fs_safe_shred_and_free(&fsv_t2, sizeof(*fsv_t2));
		return fsv_t1;
	}

    #if SECURITY_ENABLE_SIMULATION
	extern const char* g_simulation_pcidevices_filename;
	__FS_FUNCTION_PREFER_INLINE uintptr_t fs_read_find_pci_bar0(int radio /* zero based index */) {
		return fs_read_find_pci_ex(radio, g_simulation_pcidevices_filename, 0);
	}
	__FS_FUNCTION_PREFER_INLINE uint32_t fs_read_find_pci_id(int radio /* zero based index */) {
		return fs_read_find_pci_ex(radio, g_simulation_pcidevices_filename, 1);
	}
    #else // #if SECURITY_ENABLE_SIMULATION
	__FS_FUNCTION_PREFER_INLINE uintptr_t fs_read_find_pci_bar0(int radio /* zero based index */) {
		return fs_read_find_pci_ex(radio, fs_get_proc_bus_pci_devices(), 0);
	}
	__FS_FUNCTION_PREFER_INLINE uint32_t fs_read_find_pci_id(int radio /* zero based index */) {
		return fs_read_find_pci_ex(radio, fs_get_proc_bus_pci_devices(), 1);
	}
    #endif // #if SECURITY_ENABLE_SIMULATION
#endif

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_wifi_radio1_mac_rev_id_hw(void) {
	u_int32_t fsv_t1 = fs_read_cpu_rev_id_hw();
	if(fs_is_ar933x(fsv_t1)) {
		/* On AR933x (Hornet) there is a non-PCI built in radio 1 */
		fsv_t1 = fs_read_mem32(__AR933X_RADIO1___H_SREV_ID);
	} else if(fs_is_ar9342(fsv_t1)) {
		/* 
		Wasp AR9342/AR9344 has only internal radio.  We will use the CPU rev for the built in radio as radio1.
		*/
		fsv_t1 = fs_read_cpu_rev_id_hw();
	} else if(fs_is_ar934x(fsv_t1)) {
		/*
		Wasp may have internal radio, and for this we use the CPU revision ID for Wasp built-in radio.
		If PCI radio revision is 0x001c04ff, then this is a UAP Pro and we use CPU rev 
		for built-in radio as radio1, and 0x001c04ff for radio2. 
		*/
		uintptr_t base = fs_read_find_pci_bar0(0);
		if(base) {
			fsv_t1 = fs_read_mem32(base + __H_SREV_ID);
			if(fsv_t1 == 0x001c04ff) {
				fsv_t1 = fs_read_cpu_rev_id_hw();
                        }
                } else {
                        fsv_t1 = fs_read_cpu_rev_id_hw();
		}
	} else if(fs_is_qca955x(fsv_t1)) {
		/*
		 * With QCA955x (Scorpion) we use QCA988x (Peregrine) attached through PCI.
		 */
		fsv_t1 = fs_read_find_pci_id(0);
	} else if(fs_is_qca956x(fsv_t1)) {
		/*
		QCA956x (Dragonfly) has internal radio, and for this we use the CPU revision ID for QCA956x built-in radio.
		*/
                fsv_t1 = fs_read_cpu_rev_id_hw(); // NB: this has no effect.  fsv_t1 is already CPU ID
	} else if(fs_is_ar724x(fsv_t1)) {
		/* On AR724x (Hydra/Python/Virian) we use PCI address space for first PCI radio */
		uintptr_t base = fs_read_find_pci_bar0(0);
		if(base) {
			fsv_t1 = fs_read_mem32(base + __H_SREV_ID);
		} else {
			fs_low_level_failure(FS_FAILURE_fs_read_wifi_radio1_mac_rev_id_hw_1);
			fsv_t1 = 0; /* in case of debug 'nocrash' mode */
		}
#if SECURITY_ENABLE_SIMULATION
	} else if(fs_is_ipq40xx(fsv_t1)) { /* NB: This implementation is only used in simulation mode, as this function is replaced on IPQ40xx platform. */
		fsv_t1 = fs_read_cpu_rev_id_hw();
#endif // #if SECURITY_ENABLE_SIMULATION
	} else {
		fs_debug_printf("Unrecognized CPU ID: 0x%08x\n", fsv_t1);
		fs_low_level_failure(FS_FAILURE_fs_read_wifi_radio1_mac_rev_id_hw_2);
		fsv_t1 = 0; /* in case of debug 'nocrash' mode */
	}
	return fsv_t1;
}

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_wifi_radio2_mac_rev_id_hw(void) {
	uintptr_t fsv_t1 = 0;
	u_int32_t fsv_t2 = fs_read_cpu_rev_id_hw();
	if(fs_is_ar933x(fsv_t2)) {
		/* Wasp has built-in radio and second radio we add may be on PCI address space of first PCI radio */
		if((fsv_t1 = fs_read_find_pci_bar0(0 /* first on PCI bus */))) {
			fsv_t2 = fs_read_mem32(fsv_t1 + __H_SREV_ID);
		} else {
			fsv_t2 = 0;
		}
	} else if(fs_is_ar9342(fsv_t2)) {
		/* Wasp AR9342/AR93444 has only internal radio. */
		fsv_t2 = 0;
	} else if(fs_is_ar934x(fsv_t2)) {
		/*
		Wasp may have internal radio, and for this we use the CPU revision ID for Wasp built-in radio.
		If PCI radio revision is 0x001c04ff, then this is a UAP Pro and we use CPU rev 
		for built-in radio as radio1, and 0x001c04ff for radio2. 
		*/
		fsv_t1 = fs_read_find_pci_bar0(0);
		if(fsv_t1) {
			u_int32_t fsv_t3 = fs_read_mem32(fsv_t1 + __H_SREV_ID);
			if(fsv_t3 == 0x001c04ff) {
				fsv_t2 = fsv_t3;
			} else {
				uintptr_t fsv_t4 = fs_read_find_pci_bar0(1);
				if (fsv_t4) {
					fsv_t2 = fs_read_mem32(fsv_t4 + __H_SREV_ID);
				} else {
					fs_low_level_failure(FS_FAILURE_fs_read_wifi_radio2_mac_rev_id_hw_1);
					fsv_t2 = 0; /* in case of debug 'nocrash' mode */
				}
			}
		} else {
			fs_low_level_failure(FS_FAILURE_fs_read_wifi_radio2_mac_rev_id_hw_2);
			fsv_t2 = 0; /* in case of debug 'nocrash' mode */
		}
	} else if(fs_is_qca955x(fsv_t2)) {
		/*
		Scorpion QCA955x has internal radio so for this we use the CPU revision ID
		Do not use right now.
		*/
		fsv_t2 = 0;
	} else if(fs_is_qca956x(fsv_t2)) {
		/*
		Scorpion QCA956x has internal radio so for this we use the CPU revision ID
		Do not use right now.
		*/
		fsv_t2 = fs_read_find_pci_id(0);
	} else if(fs_is_ar724x(fsv_t2)) {
		/* On AR724x (Hydra/Python/Virian) we use PCI address space for radio 2 */
		if((fsv_t1 = fs_read_find_pci_bar0(1 /* second on PCI bus */))) {
			fsv_t2 = fs_read_mem32(fsv_t1 + __H_SREV_ID);
		} else {
			fsv_t2 = 0;
		}
#if SECURITY_ENABLE_SIMULATION
	} else if(fs_is_ipq40xx(fsv_t2)) { /* NB: This implementation is only used in simulation mode, as this function is replaced on IPQ40xx platform. */
		fsv_t2 = fs_read_cpu_rev_id_hw(); // Radio revision is CPU revision
#endif // #if SECURITY_ENABLE_SIMULATION
	} else {
		fs_low_level_failure(FS_FAILURE_fs_read_wifi_radio2_mac_rev_id_hw_3);
		fsv_t2 = 0; // just in case of 'nocrash' debug mode
	}
	return fsv_t2;
}
#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_MIPS_ARxxxx) || SECURITY_ENABLE_SIMULATION)

