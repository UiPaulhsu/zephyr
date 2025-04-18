#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_MIPS_BCM4706) || SECURITY_ENABLE_SIMULATION)

#define __BCM5300X_REV_ID               ((uintptr_t)(0x18000000))
#define __BCM5300X_CHIPTYPE_MASK        0xf0000000      /* should be 0x1 */
#define __BCM5300X_CORECNT_MASK         0x0f000000           
#define __BCM5300X_PKGOPT_MASK          0x00f00000
#define __BCM5300X_CHIPREV_MASK         0x000f0000
#define __BCM5300X_CHIPID_MASK          0x0000ffff      /* should be 0x5300 */

#define __BCM4706_REV_ID_MASK           (__BCM5300X_CHIPTYPE_MASK | __BCM5300X_CORECNT_MASK | __BCM5300X_PKGOPT_MASK | __BCM5300X_CHIPID_MASK)
#define __BCM4706_PROCESSOR_ID          0x19015300

#define __BCM4706_RADIO1_PCI_LOC        0x0108
#define __BCM4706_RADIO2_PCI_LOC        0x0208

#define __BCM_PCI_VENDOR_ID             0x14e4

// kernel implementation

#ifdef __KERNEL__
#if (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,20))
	#define pci_find_device pci_get_device
#endif
	__FS_FUNCTION_PREFER_INLINE uint32_t fs_read_wifi_wifi_radio_id(uint16_t radio_pci_location) {
		__FS_LOCAL_STATIC_OPTION struct pci_dev* fsv_t2;
		fsv_t2 = NULL;
		while((fsv_t2 = pci_find_device(__BCM_PCI_VENDOR_ID, PCI_ANY_ID, fsv_t2)) != NULL) {
			if (radio_pci_location == (((fsv_t2->bus->number & 0xFF) << 8) | (fsv_t2->devfn & 0xFF))) {
				return ((fsv_t2->vendor & 0xFFFF) << 16) | (fsv_t2->device & 0xFFFF);
			}
		}
		fs_debug_printf_off("No radio found at location 0x%04x.\n", radio_pci_location);
		return 0;
	}
#else
	typedef struct fs_read_wifi_radio_id_ex_data {
		char      line[512];
		u_int32_t bdf;
		u_int32_t vendor_device;
		u_int32_t irq;
		uintptr_t bar0;
		FILE*     p_devices_file;
		int       c;
	} fs_read_wifi_radio_id_ex_data_t;

	__FS_FUNCTION_PREFER_INLINE uint32_t fs_read_wifi_radio_id_ex(uint16_t radio_pci_location, const char* pathname) {
		__FS_LOCAL_STATIC_OPTION uint32_t fsv_t1;
		__FS_LOCAL_STATIC_OPTION fs_read_wifi_radio_id_ex_data_t* fsv_t2;
		fsv_t1 = 0;
		fsv_t2 = (fs_read_wifi_radio_id_ex_data_t*)fs_zalloc(sizeof(fs_read_wifi_radio_id_ex_data_t));
		if(NULL == fsv_t2) {
			fsv_t1 = 0; // still zero
			goto done;
		}
		fsv_t2->p_devices_file = fs_fopen(pathname, "r");
		if (fsv_t2->p_devices_file != NULL) {
			while (!feof(fsv_t2->p_devices_file) && fgets(fsv_t2->line, sizeof(fsv_t2->line), fsv_t2->p_devices_file)) {
                                // Read the first four values (only)
				fsv_t2->c = sscanf(fsv_t2->line, "%x %x %x %" PRIxPTR, &fsv_t2->bdf, &fsv_t2->vendor_device, &fsv_t2->irq, &fsv_t2->bar0);
				if (fsv_t2->c != 4) {
					continue;
				}
				if (fsv_t2->bdf == radio_pci_location) {
                                        fsv_t1 = fsv_t2->vendor_device;
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
	__FS_FUNCTION_PREFER_INLINE uint32_t fs_read_wifi_radio_id(uint16_t radio_pci_location) {
		return fs_read_wifi_radio_id_ex(radio_pci_location, g_simulation_pcidevices_filename);
	}
    #else // #if SECURITY_ENABLE_SIMULATION
	__FS_FUNCTION_PREFER_INLINE uint32_t fs_read_wifi_radio_id(uint16_t radio_pci_location) {
		return fs_read_wifi_radio_id_ex(radio_pci_location, fs_get_proc_bus_pci_devices());
	}
    #endif // #if SECURITY_ENABLE_SIMULATION
#endif

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_BCM4706_cpu_rev_id_hw(void) {
	return fs_read_mem32( __BCM5300X_REV_ID );
}

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_BCM4706_wifi_radio1_id_hw(void) {
	return fs_read_wifi_radio_id( __BCM4706_RADIO1_PCI_LOC );
}

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_BCM4706_wifi_radio2_id_hw(void) {
	return fs_read_wifi_radio_id( __BCM4706_RADIO2_PCI_LOC );
}

#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_MIPS_BCM4706) || SECURITY_ENABLE_SIMULATION)

