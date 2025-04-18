#if SECURITY_IS_TARGET_BUILD
#define DEFAULT_MTDBLOCK            5

#ifndef __KERNEL__

#if UBNT_LINUX
// Helper build keeps siglongjmp stuff
#if SECURITY_ENABLE_SIGNAL_HANDLER
__FS_LOCAL_STATIC_OPTION jmp_buf __ATTRIB_UNUSED __j/*fs_jmpbuf*/;
__FS_LOCAL_STATIC_OPTION void __ATTRIB_UNUSED __fs_sig(int UNUSED( sig )) {
	siglongjmp(__j/*fs_jmpbuf*/, 1);
}
#define BEFORE_COPY \
if(!sigsetjmp(__j/*fs_jmpbuf*/, 1)) {
#define AFTER_COPY \
} else { \
fs_low_level_failure(FS_FAILURE_fs_signal_handler_1); \
}
#else // #if SECURITY_ENABLE_SIGNAL_HANDLER
__FS_LOCAL_STATIC_OPTION void __ATTRIB_UNUSED __fs_sig(int UNUSED( sig )) {
	fs_debug_printf( "KABOOM!! (%s)\n", "__fs_sig #1");
	fflush( stdout );
	fflush( stderr );
#ifdef __KERNEL__
	volatile u_int8_t* __fs_failure__p = NULL;
	panic("");
	__fs_failure__p  = NULL;
	*__fs_failure__p = 0;
#else // #ifdef __KERNEL__
	exit(1);
#endif // #ifdef __KERNEL__
}
#define BEFORE_COPY /* nothing */
#define AFTER_COPY  /* nothing */
#endif // #if SECURITY_ENABLE_SIGNAL_HANDLER
#else // #if UBNT_LINUX
#define BEFORE_COPY /* nothing */
#define AFTER_COPY  /* nothing */
#endif // #if UBNT_LINUX

#if UBNT_LINUX
typedef struct fs_write_to_mmapped_file_data {
	void*     p_mmap;
	int       mem_fd;
	uintptr_t base_address;
	size_t    mmap_length;
	struct    sigaction old_action;
	struct    sigaction new_action;
} fs_write_to_mmapped_file_data_t;

__FS_FUNCTION_PREFER_INLINE void fs_write_to_mmapped_file(const char* fsa_p_filename, uintptr_t fsa_address, void* data, size_t fsa_length) {
	__FS_LOCAL_STATIC_OPTION fs_write_to_mmapped_file_data_t* fsv_t1;
	fsv_t1 = (fs_write_to_mmapped_file_data_t*)fs_zalloc(sizeof(fs_write_to_mmapped_file_data_t));
	if (fsv_t1 == NULL) {
		goto done;
	}
	fsv_t1->p_mmap       = NULL;
	fsv_t1->mem_fd       = -1;
	fsv_t1->base_address = fsa_address - (((uintptr_t)fsa_address) % ((uintptr_t)sysconf(_SC_PAGE_SIZE)));
	fsv_t1->mmap_length  = (((uintptr_t)fsa_address) % ((uintptr_t)sysconf(_SC_PAGE_SIZE))) + fsa_length;
	memset(((u_int8_t* )fsv_t1->p_mmap) + fsa_address - fsv_t1->base_address, 0, fsa_length);
	fs_debug_printf_off("fs_write_to_mmapped_file(\"%s\",0x%" PRIxPTR " ,0x%" PRIxPTR ", %zu)\n", fsa_p_filename, (uintptr_t)fsa_address, (uintptr_t)data, (uintptr_t)fsa_length);
	if ((fsa_address < fsv_t1->base_address) || ((fsa_address + fsa_length) > (fsv_t1->base_address + fsv_t1->mmap_length))) {
		fs_debug_printf("Data range 0x%08" PRIxPTR "..0x%08" PRIxPTR " does not fall entirely within the mapping range 0x%08" PRIxPTR "..0x%08" PRIxPTR ".\n",
						((uintptr_t)fsa_address), ((uintptr_t)(fsa_address + fsa_length)),
						((uintptr_t)fsv_t1->base_address), ((uintptr_t)(fsv_t1->base_address + fsv_t1->mmap_length)));
		fs_low_level_failure(FS_FAILURE_fs_write_to_mmapped_file_2);
	} else {
		fsv_t1->mem_fd = fs_open(fsa_p_filename, O_RDWR);
		if (fsv_t1->mem_fd < 0) {
			fs_debug_printf("Failed opening %s: %s\n", fsa_p_filename, strerror(errno));
			fs_low_level_failure(FS_FAILURE_fs_write_to_mmapped_file_3);
		} else {
			fsv_t1->p_mmap = mmap(NULL, fsv_t1->mmap_length, PROT_READ | PROT_WRITE, MAP_SHARED, fsv_t1->mem_fd, fsv_t1->base_address);
			if (fsv_t1->p_mmap == MAP_FAILED) {
				fs_debug_printf("Failed mmapping %s - 0x%zx bytes at offset 0x%" PRIxPTR ": %s\n", fsa_p_filename, (size_t)fsv_t1->mmap_length, (uintptr_t)fsv_t1->base_address, strerror(errno));
				fs_low_level_failure(FS_FAILURE_fs_write_to_mmapped_file_4);
			} else {
				fsv_t1->new_action.sa_handler = __fs_sig;
				fsv_t1->new_action.sa_flags   = 0;
				sigemptyset (&fsv_t1->new_action.sa_mask);
/* Swap SIGBUS handler */
				sigaction( SIGBUS, &fsv_t1->new_action, &fsv_t1->old_action);
/* Do the copy */
				BEFORE_COPY
				memcpy(((u_int8_t* )fsv_t1->p_mmap) + fsa_address - fsv_t1->base_address, (((u_int8_t*)data)), fsa_length);
				AFTER_COPY
/* Restore SIGBUS handler */
				sigaction( SIGBUS, &fsv_t1->old_action, NULL );
			}
		}
	}
	if (fsv_t1->p_mmap != NULL) {
		munmap( fsv_t1->p_mmap, fsv_t1->mmap_length );
		fsv_t1->p_mmap = NULL;
	}
	if (fsv_t1->mem_fd != -1) {
		fs_close( fsv_t1->mem_fd );
		fsv_t1->mem_fd = -1;
	}
	done:
	fs_safe_shred_and_free(&fsv_t1,sizeof(*fsv_t1));
}

typedef struct fs_read_from_mmapped_file_data {
	void*     p_mmap;
	int       mem_fd;
	uintptr_t base_address;
	size_t    mmap_length;
	struct    sigaction old_action;
	struct    sigaction new_action;
} fs_read_from_mmapped_file_data_t;

__FS_FUNCTION_PREFER_INLINE void fs_read_from_mmapped_file(const char* fsa_p_filename, u_int8_t* fsa_p_dest, size_t fsa_destlen, uintptr_t fsa_address, size_t fsa_length) {
	__FS_LOCAL_STATIC_OPTION fs_read_from_mmapped_file_data_t* fsv_t1;
	fsv_t1 = (fs_read_from_mmapped_file_data_t*)fs_zalloc(sizeof(fs_read_from_mmapped_file_data_t));
	if (fsv_t1 == NULL) {
		goto done;
	}
	fsv_t1->p_mmap       = NULL;
	fsv_t1->mem_fd       = -1;
	fsv_t1->base_address = fsa_address - (((uintptr_t)fsa_address) % ((uintptr_t)sysconf(_SC_PAGE_SIZE)));
	fsv_t1->mmap_length  = (((uintptr_t)fsa_address) % ((uintptr_t)sysconf(_SC_PAGE_SIZE))) + fsa_length;
	if (fsa_destlen < fsa_length) {
		fs_low_level_failure(FS_FAILURE_fs_read_from_mmapped_file_1);
	}
	memset(fsa_p_dest, 0, fsa_length);
	fs_debug_printf_off("fs_read_from_mmapped_file(\"%s\",%p,%zu,0x%08" PRIxPTR ",%zu)\n", fsa_p_filename, fsa_p_dest,fsa_destlen,(uintptr_t)fsa_address,fsa_length);
	if ((fsa_address < fsv_t1->base_address) || ((fsa_address + fsa_length) > (fsv_t1->base_address + fsv_t1->mmap_length))) {
		fs_debug_printf("Data range 0x%08" PRIxPTR "..0x%08" PRIxPTR " does not fall entirely within the mapping range 0x%08" PRIxPTR "..0x%08" PRIxPTR ".\n", ((uintptr_t)fsa_address), ((uintptr_t)(fsa_address + fsa_length)), ((uintptr_t)fsv_t1->base_address), ((uintptr_t)(fsv_t1->base_address + fsv_t1->mmap_length)));
		fs_low_level_failure(FS_FAILURE_fs_read_from_mmapped_file_2);
	} else {
		fsv_t1->mem_fd = fs_open(fsa_p_filename, O_RDWR);
		if (fsv_t1->mem_fd < 0) {
			fs_debug_printf("Failed opening %s: %s\n", fsa_p_filename, strerror(errno));
			fs_low_level_failure(FS_FAILURE_fs_read_from_mmapped_file_3);
		} else {
			fsv_t1->p_mmap = mmap(NULL, fsv_t1->mmap_length, PROT_READ | PROT_WRITE, MAP_SHARED, fsv_t1->mem_fd, fsv_t1->base_address);
			if (fsv_t1->p_mmap == MAP_FAILED) {
				fs_debug_printf("Failed mmapping %s - 0x%zx bytes at offset 0x%" PRIxPTR ": %s\n", fsa_p_filename, (size_t)fsv_t1->mmap_length, (uintptr_t)fsv_t1->base_address, strerror(errno));
				fs_low_level_failure(FS_FAILURE_fs_read_from_mmapped_file_4);
			} else {
				fsv_t1->new_action.sa_handler = __fs_sig;
				fsv_t1->new_action.sa_flags   = 0;
				sigemptyset (&fsv_t1->new_action.sa_mask);
/* Swap SIGBUS handler */
				sigaction( SIGBUS, &fsv_t1->new_action, &fsv_t1->old_action);
/* Do the copy */
				BEFORE_COPY
				memcpy((((u_int8_t*)fsa_p_dest)), ((u_int8_t* )fsv_t1->p_mmap) + fsa_address - fsv_t1->base_address, fsa_length);
				AFTER_COPY
/* Restore SIGBUS handler */
				sigaction( SIGBUS, &fsv_t1->old_action, NULL );
			}
		}
	}
	if (fsv_t1->p_mmap != NULL) {
		munmap( fsv_t1->p_mmap, fsv_t1->mmap_length );
		fsv_t1->p_mmap = NULL;
	}
	if (fsv_t1->mem_fd != -1) {
		fs_close( fsv_t1->mem_fd );
		fsv_t1->mem_fd = -1;
	}
	done:
	fs_safe_shred_and_free(&fsv_t1,sizeof(*fsv_t1));
}
#endif // #if UBNT_LINUX
#else
#if SECURITY_INCLUDE_FLASH_PARTITION_SUPPORT
__FS_FUNCTION_PREFER_INLINE void fs_get_eeprom_partition_info(int32_t* p_index, char* filename, size_t filename_max_length) {

	memset(filename, 0, filename_max_length);

#if defined(UBNT_ARM_AM18xx) && UBNT_ARM_AM18xx
	*p_index = 6;// NB: Not reading MTD partition tables in kernel modules yet
#elif defined(UBNT_MIPS_CN50xx)
	*p_index = 2;// NB: Not reading MTD partition tables in kernel modules yet
#elif defined(UBNT_MIPS_MT7621)
#if defined(UNIFI_LAYOUT)
	*p_index = 3;// NB: Not reading MTD partition tables in kernel modules yet
#else /* #if defined(UNIFI_LAYOUT) */
	*p_index = 4;// NB: Not reading MTD partition tables in kernel modules yet
#endif /* #if defined(UNIFI_LAYOUT) */
#elif defined(UBNT_ARM_A5S) && UBNT_ARM_A5S
	*p_index = 10;// NB: Not reading MTD partition tables in kernel modules yet
#elif defined(UBNT_ARM_S2) && UBNT_ARM_S2
	*p_index = 10;// NB: Not reading MTD partition tables in kernel modules yet
#elif defined(UBNT_ARM_S2L) && UBNT_ARM_S2L
	*p_index = 9;// NB: Not reading MTD partition tables in kernel modules yet
#elif defined(UBNT_ARM_S2LM) && UBNT_ARM_S2LM
	*p_index = 11;// NB: Not reading MTD partition tables in kernel modules yet
#elif defined(UBNT_ARM64_S5L) && UBNT_ARM64_S5L
    *p_index = 10;// NB: Not reading MTD partition tables in kernel modules yet
#elif defined(UBNT_ARM64_S5LM) && UBNT_ARM64_S5LM
    *p_index = 10;// NB: Not reading MTD partition tables in kernel modules yet
#elif defined(UBNT_ARM_BCM111xx) && UBNT_ARM_BCM111xx
	*p_index = 3;// NB: Not reading MTD partition tables in kernel modules yet
#elif defined(UBNT_ARM_MT8117) && UBNT_ARM_MT8117
	*p_index = 5;// NB: Not reading MTD partition tables in kernel modules yet
#elif defined(UBNT_ARM_BCM5334x) && UBNT_ARM_BCM5334x
	*p_index = 6;// NB: Not reading MTD partition tables in kernel modules yet
#elif defined(UBNT_ARM_BCM5341x) && UBNT_ARM_BCM5341x
#if defined(UNIFI_LAYOUT)
	*p_index = 6;// NB: Not reading MTD partition tables in kernel modules yet
#else /* #if defined(UNIFI_LAYOUT) */
	*p_index = 3;// NB: Not reading MTD partition tables in kernel modules yet
#endif /* #if defined(UNIFI_LAYOUT) */
#elif defined(UBNT_MIPS_VSC7514)
	*p_index = 6;// NB: Not reading MTD partition tables in kernel modules yet
#elif defined(UBNT_MIPS_RTL838x)
	*p_index = 6;// NB: Not reading MTD partition tables in kernel modules yet
#elif defined(UBNT_MIPS_BCM4706)
	*p_index = 6;// NB: Not reading MTD partition tables in kernel modules yet
#elif defined(UBNT_ARM_MT7623) && UBNT_ARM_MT7623
	*p_index = 0;// NB: Not reading MTD partition tables in kernel modules yet
#elif defined(UBNT_ARM_IPQ40xx) && UBNT_ARM_IPQ40xx
	*p_index = 7;// NB: Not reading MTD partition tables in kernel modules yet
#elif defined(UBNT_ARM_IPQ806x) && UBNT_ARM_IPQ806x
	*p_index = 10;// NB: Not reading MTD partition tables in kernel modules yet
#elif defined(UBNT_ARM64_APQ8053) && UBNT_ARM64_APQ8053
	*p_index = 0;// NB: Not reading MTD partition tables in kernel modules yet
#elif defined(UBNT_ARM64_AL324) && UBNT_ARM64_AL324
	*p_index = 0;// NB: Not reading MTD partition tables in kernel modules yet
#elif defined(UBNT_ARM64_IPQ807x) && UBNT_ARM64_IPQ807x
	*p_index = 18;// NB: Not reading MTD partition tables in kernel modules yet
#else // #if defined(UBNT_ARM_AM18xx) && UBNT_ARM_AM18xx
	*p_index = 4;// NB: Not reading MTD partition tables in kernel modules yet
#endif // #if defined(UBNT_ARM_AM18xx) && UBNT_ARM_AM18xx

	snprintf(filename, filename_max_length, "%s%u", fs_get_decoded_dev_mtdblock(), *p_index);
}
#endif // #if SECURITY_INCLUDE_FLASH_PARTITION_SUPPORT
#endif // #ifndef __KERNEL__

#if SECURITY_ENABLE_SIMULATION
#define KEYBUF_LEN 32
extern const char* g_simulation_ini_filename;
__FS_FUNCTION_PREFER_INLINE void fs_read_mem(void* fsa_dest, size_t fsa_dest_len, uintptr_t fsa_address, size_t fsa_length) {
	__FS_LOCAL_STATIC_OPTION char* fsv_t1;
	FS_LOCK
	fsv_t1 = (char*)fs_zalloc(KEYBUF_LEN);
	if (fsa_length > fsa_dest_len) {
		fs_low_level_failure(FS_FAILURE_fs_read_mem_1);
	}
	snprintf(fsv_t1, KEYBUF_LEN, "0x%08" PRIxPTR, fsa_address);
	fs_read_ini_hex_raw( (u_int8_t*)fsa_dest, fsa_dest_len, g_simulation_ini_filename, fsv_t1, fsa_length, fsa_length, 1);
	fs_safe_shred_and_free(&fsv_t1, KEYBUF_LEN);
	FS_UNLOCK
}
#if SECURITY_INCLUDE_WRITE_MEM
__FS_FUNCTION_PREFER_INLINE void fs_write_mem(__ATTRIB_UNUSED uintptr_t fsa_address, __ATTRIB_UNUSED void* value, __ATTRIB_UNUSED size_t value_length) {
	// TODO ...some kind of temporary persistent store so read backs work?
}
#endif // #if SECURITY_INCLUDE_WRITE_MEM
#else // #if SECURITY_ENABLE_SIMULATION
#ifdef __KERNEL__
#ifdef UBNT_ARM
__FS_FUNCTION_PREFER_INLINE void fs_read_mem(void* fsa_dest, size_t fsa_dest_len, uintptr_t fsa_address, size_t fsa_length) {
	FS_LOCK
	volatile void __iomem * p_base = NULL;
	if (fsa_length > fsa_dest_len) {
		fs_low_level_failure(FS_FAILURE_fs_read_mem_2);
	}
	p_base = ioremap_nocache(fsa_address,fsa_length);
	if (p_base == NULL) {
		fs_low_level_failure(FS_FAILURE_fs_read_mem_3);
	} else {
		memcpy((char*)fsa_dest, (char __force *)p_base, fsa_length);
		iounmap(p_base);
	}
	FS_UNLOCK
}
// In kernel mode, assuming host byte order of course, memcpy can work.
#if SECURITY_INCLUDE_WRITE_MEM
__FS_FUNCTION_PREFER_INLINE void fs_write_mem(uintptr_t fsa_address, void* value, size_t fsa_length) {
	FS_LOCK
	volatile void __iomem * p_base = ioremap_nocache(fsa_address, fsa_length);
	if (p_base == NULL) {
		fs_low_level_failure(FS_FAILURE_fs_write_mem_1);
	} else {
		memcpy((char __force *)p_base, (char*)value, fsa_length);
		iounmap(p_base);
	}
	FS_UNLOCK
}
#endif // #if SECURITY_INCLUDE_WRITE_MEM
#elif defined(UBNT_MIPS_CN50xx) || defined(UBNT_MIPS_MT7621)
/* These are not needed for the platform? */
__FS_FUNCTION_PREFER_INLINE void fs_read_mem(void* fsa_dest, size_t fsa_dest_len, uintptr_t fsa_address, size_t fsa_length) {
	fs_debug_printf("ERROR fs_read_mem called\n");
}
#if SECURITY_INCLUDE_WRITE_MEM
__FS_FUNCTION_PREFER_INLINE void fs_write_mem(uintptr_t fsa_address, void* value, size_t fsa_length) {
	fs_debug_printf("ERROR fs_write_mem called\n");
}
#endif // #if SECURITY_INCLUDE_WRITE_MEM
#else
__FS_FUNCTION_PREFER_INLINE void fs_read_mem(void* fsa_dest, size_t fsa_dest_len, uintptr_t fsa_address, size_t fsa_length) {
	FS_LOCK
	if (fsa_length > fsa_dest_len) {
		fs_low_level_failure(FS_FAILURE_fs_read_mem_4);
	}
	memcpy((char*)fsa_dest, (char*)KSEG1ADDR(fsa_address), fsa_length);
	FS_UNLOCK
}
#if SECURITY_INCLUDE_WRITE_MEM
__FS_FUNCTION_PREFER_INLINE void fs_write_mem(uintptr_t fsa_address, void* value, size_t fsa_length) {
	FS_LOCK
	memcpy((char*)fsa_address, (char*)value, fsa_length);
	FS_UNLOCK
}
#endif // #if SECURITY_INCLUDE_WRITE_MEM
#endif
#else // #ifdef __KERNEL__

#if UBNT_LINUX
/* Make mmapped access in user mode */
__FS_FUNCTION_PREFER_INLINE void fs_read_mem(void* fsa_dest, size_t fsa_dest_len, uintptr_t fsa_address, size_t fsa_length) {
	FS_LOCK
	if (fsa_length > fsa_dest_len) {
		fs_low_level_failure(FS_FAILURE_fs_read_mem_5);
	}
	fs_read_from_mmapped_file(fs_get_decoded_dev_mem(), (u_int8_t*)fsa_dest, fsa_dest_len, fsa_address, fsa_length);
	FS_UNLOCK
}

#if SECURITY_INCLUDE_WRITE_MEM
/* Make mmapped access in user mode */
__FS_FUNCTION_PREFER_INLINE void fs_write_mem(uintptr_t fsa_address, void* value, size_t fsa_length) {
	FS_LOCK
	fs_write_to_mmapped_file(fs_get_decoded_dev_mem(), fsa_address, value, fsa_length);
	FS_UNLOCK
}
#endif // #if SECURITY_INCLUDE_WRITE_MEM
#else // #if UBNT_LINUX
/* For non-Linux environment, currently we have microprocessor(s) where direct memory access is possible.
   Make mmapped access in user mode */
__FS_FUNCTION_PREFER_INLINE void fs_read_mem(void* fsa_dest, size_t fsa_dest_len, uintptr_t fsa_address, size_t fsa_length) {
	FS_LOCK
	if (fsa_length > fsa_dest_len) {
		fs_low_level_failure(FS_FAILURE_fs_read_mem_5);
	}
        memcpy(fsa_dest, (void*)fsa_address, fsa_dest_len < fsa_length ? fsa_dest_len : fsa_length);
	FS_UNLOCK
}

#if SECURITY_INCLUDE_WRITE_MEM
/* Make mmapped access in user mode */
__FS_FUNCTION_PREFER_INLINE void fs_write_mem(uintptr_t fsa_address, void* value, size_t fsa_length) {
	FS_LOCK
        memcpy((void*)fsa_address, value, fsa_length);
	FS_UNLOCK
}
#endif // #if SECURITY_INCLUDE_WRITE_MEM
#endif // #if UBNT_LINUX

#endif // #ifdef __KERNEL__
#endif // #if SECURITY_ENABLE_SIMULATION

#ifndef __KERNEL__
#if SECURITY_INCLUDE_FLASH_PARTITION_SUPPORT
/* Get mtd partition number for eeprom. Sample contents in /proc/mtd:
dev:    size   erasesize  name
mtd0: 000e0000 00001000 "boot"
mtd1: 00120000 00001000 "kernel"
mtd2: 005b0000 00001000 "rootfs"
mtd3: 00040000 00001000 "cfg"
mtd4: 00010000 00001000 "eeprom"
*/
__FS_FUNCTION_PREFER_INLINE void fs_get_eeprom_partition_info(int32_t* p_index, char* filename, size_t filename_max_length) {
	__FS_LOCAL_STATIC_OPTION char  fsv_t1[256];
	__FS_LOCAL_STATIC_OPTION char* fsv_t2;
	__FS_LOCAL_STATIC_OPTION int   fsv_t3;
	__FS_LOCAL_STATIC_OPTION FILE* fsv_t4;

	fsv_t3 = 0;
	fsv_t2 = NULL;
	fsv_t4 = NULL;
	memset( fsv_t1, 0, sizeof fsv_t1 );

	fsv_t4 = fs_fopen(fs_get_decoded_proc_mtd(), "r");
	*p_index = -1;
	if (fsv_t4 != NULL) {
// Skip first line - headers there
		if (NULL == fgets(fsv_t1, sizeof(fsv_t1), fsv_t4)) {
			return;
		}
// Read one line from /proc/mtd
		while (fgets(fsv_t1, sizeof(fsv_t1), fsv_t4)) {
// Find the 4th column
			fsv_t2 = fsv_t1;
			for (fsv_t3 = 0; (fsv_t3 < 3) && fsv_t2; fsv_t3++) {
				fsv_t2 = strchr(fsv_t2, ' ');
				if (fsv_t2)	fsv_t2++;
			}
			if (!fsv_t2) {
				break;
			}
// Now p should point to the partition name
			if (strncasecmp(fs_get_decoded_eeprom_quoted(), fsv_t2, fs_get_decoded_eeprom_quoted_len()) == 0) {
				if (strncmp(fs_get_decoded_mtd(), fsv_t1, fs_get_decoded_mtd_len()) == 0) {
					*p_index = atoi(fsv_t1 + fs_get_decoded_mtd_len());
					break;
				}
			}
		}
		fs_fclose(fsv_t4);
	}
#if defined(UBNT_ARM_BCM111xx) && UBNT_ARM_BCM111xx
	*p_index = 3;
#endif
#if defined(UBNT_ARM_MT8117) && UBNT_ARM_MT8117
	*p_index = 5;
#endif
#if defined(UBNT_ARM_MT7623) && UBNT_ARM_MT7623
    *p_index = 0;
#endif
#if defined(UBNT_MIPS_RTL838x) && UBNT_MIPS_RTL838x
    *p_index = 6;
#endif
/* On failure return mtdblock5 anyway */
	if (*p_index < 0) {
		*p_index = DEFAULT_MTDBLOCK;
	}
	snprintf(filename, filename_max_length, "%s%d", fs_get_decoded_dev_mtdblock(), *p_index);
}
#endif // #if SECURITY_INCLUDE_FLASH_PARTITION_SUPPORT
#endif // #ifndef __KERNEL__

#if SECURITY_READ_CONFIG_USES_MMAP

#if SECURITY_ENABLE_SIMULATION
extern const char* g_config_filename;
/* Make mmapped access in user mode */
__FS_FUNCTION_PREFER_INLINE void fs_read_config(void* fsa_dest, size_t fsa_dest_len, uintptr_t fsa_address, size_t fsa_length) {
	if (fsa_length > fsa_dest_len) {
		fs_low_level_failure(FS_FAILURE_fs_read_config_1);
	}
	fs_read_from_mmapped_file(g_config_filename, (u_int8_t*)fsa_dest, fsa_dest_len, fsa_address, fsa_length);
}
#else // #if SECURITY_ENABLE_SIMULATION
#ifdef __KERNEL__
typedef struct fs_read_config_data {
	int             i;
	char            buf[256];
	u_int8_t        config[MAX_EEPROM_SIZE];
	size_t          config_bytes_read;
} fs_read_config_data_t;
/* Read the whole file in kernel mode */
__FS_FUNCTION_PREFER_INLINE void fs_read_config(void* fsa_dest, size_t fsa_dest_len, uintptr_t fsa_address, size_t fsa_length) {
	__FS_LOCAL_STATIC_OPTION fs_read_config_data_t* fsv_t1;
	fsv_t1 = (fs_read_config_data_t*)fs_zalloc(sizeof(fs_read_config_data_t));
	if (NULL == fsv_t1) {
		goto done;
	}
	fs_get_eeprom_partition_info(&fsv_t1->i, fsv_t1->buf, sizeof fsv_t1->buf);
	if (fsa_length > sizeof fsv_t1->config) {
		fs_low_level_failure(FS_FAILURE_fs_read_config_2);
	}
	fs_read_file_into_buffer(fsv_t1->config, sizeof fsv_t1->config, fsv_t1->buf, &fsv_t1->config_bytes_read);
	if (fsa_length > fsv_t1->config_bytes_read) {
		fs_low_level_failure(FS_FAILURE_fs_read_config_3);
	}
	if (fsa_length > fsa_dest_len) {
		fs_low_level_failure(FS_FAILURE_fs_read_config_4);
	}
	memcpy( (char* )fsa_dest, &fsv_t1->config[fsa_address], fsa_length);
	done:
	fs_safe_shred_and_free(&fsv_t1, sizeof(*fsv_t1));
}
#else // #ifdef __KERNEL__
typedef struct fs_read_config_data {
	int32_t         i;
	char            buf[64];
} fs_read_config_data_t;

/* Make mmapped access in user mode */
__FS_FUNCTION_PREFER_INLINE void fs_read_config(void* fsa_dest, size_t fsa_dest_len, uintptr_t fsa_address, size_t fsa_length) {
	static fs_read_config_data_t fsv_t1;
	memset(&fsv_t1,0,sizeof fsv_t1);
	fs_get_eeprom_partition_info(&fsv_t1.i, fsv_t1.buf, sizeof fsv_t1.buf);
	FS_LOCK
	fs_read_from_mmapped_file(fsv_t1.buf, (u_int8_t*)fsa_dest, fsa_dest_len, fsa_address, fsa_length);
	FS_UNLOCK
}
#endif // #ifdef __KERNEL__
#endif // #if SECURITY_ENABLE_SIMULATION
#endif // #if SECURITY_READ_CONFIG_USES_MMAP

#if SECURITY_READ_CONFIG_USES_DIRECT_MEMORY_ACCESS
__FS_FUNCTION_PREFER_INLINE void fs_read_config(void* fsa_dest, size_t fsa_dest_len, uintptr_t fsa_address, size_t fsa_length) {
	if (fsa_length > fsa_dest_len) {
		fs_low_level_failure(FS_FAILURE_fs_read_config_5);
	}
	FS_LOCK
	memcpy( (char*)fsa_dest, (u_int8_t*)( CONFIG_PHYSICAL_ADDRESS + (fsa_address) ), fsa_length );
	FS_UNLOCK
}
#endif // #if SECURITY_READ_CONFIG_USES_DIRECT_MEMORY_ACCESS
#if SECURITY_READ_CONFIG_USES_READ_MEM
__FS_FUNCTION_PREFER_INLINE void fs_read_config(void* fsa_dest, size_t fsa_dest_len, uintptr_t fsa_address, size_t fsa_length) {
	if (fsa_length > fsa_dest_len) {
		fs_low_level_failure(FS_FAILURE_fs_read_config_6);
	}
	fs_read_mem( (u_int8_t*)fsa_dest, fsa_dest_len, CONFIG_PHYSICAL_ADDRESS + (fsa_address), fsa_length);
}
#endif //#if SECURITY_READ_CONFIG_USES_READ_MEM

#if SECURITY_READ_CONFIG_USES_READ_FLASH

	#if SECURITY_ENABLE_SIMULATION
		extern const char* g_config_filename;
		/* Make mmapped access in user mode */
		__FS_FUNCTION_PREFER_INLINE void fs_read_config(void* fsa_dest, size_t fsa_dest_len, uintptr_t fsa_address, size_t fsa_length) {
			if(fsa_length > fsa_dest_len) {
				fs_low_level_failure(FS_FAILURE_fs_read_config_1);
			}
			fs_read_from_mmapped_file(g_config_filename, (u_int8_t*)fsa_dest, fsa_dest_len, fsa_address, fsa_length);
		}

	#else // #if SECURITY_ENABLE_SIMULATION
		__FS_FUNCTION_PREFER_INLINE void fs_read_flash_data(uintptr_t address, u_int8_t* dest, size_t bytes_to_read);
		typedef struct fs_read_config_data {
			u_int8_t        config[MAX_FLASH_EEPROM_SIZE];
		} fs_read_config_data_t;
		__FS_FUNCTION_PREFER_INLINE void fs_read_config(void* fsa_dest, size_t fsa_dest_len, uintptr_t fsa_address, size_t fsa_length) {
			__FS_LOCAL_STATIC_OPTION fs_read_config_data_t* fsv_t1;
			fsv_t1 = (fs_read_config_data_t*)fs_zalloc(sizeof(fs_read_config_data_t));
			if (NULL == fsv_t1)
				goto done;
			if (fsa_length > fsa_dest_len)
				fs_low_level_failure(FS_FAILURE_fs_read_config_7);
			if (fsa_length > sizeof fsv_t1->config) {
				fs_low_level_failure(FS_FAILURE_fs_read_config_8);
			}
			fs_read_flash_data(fsa_address, fsv_t1->config, fsa_length);
			FS_LOCK
				memcpy((u_int8_t*)fsa_dest, (u_int8_t*)fsv_t1->config, fsa_length);
			FS_UNLOCK
		done:
			fs_safe_shred_and_free(&fsv_t1, sizeof(*fsv_t1));
		}
	#endif // #if SECURITY_ENABLE_SIMULATION

#endif // #if SECURITY_READ_CONFIG_USES_READ_FLASH

#if defined(HELPER_BUILD) && (defined(SECURITY_WRITE_CONFIG_USES_FILE) && SECURITY_WRITE_CONFIG_USES_FILE)
typedef struct fs_write_config_data {
	int             i;
	char            buf[256];
	u_int8_t        config[MAX_EEPROM_SIZE];
	size_t          config_bytes_read;
} fs_write_config_data_t;
__FS_FUNCTION_PREFER_INLINE void fs_write_config(__ATTRIB_UNUSED uintptr_t fsa_address, __ATTRIB_UNUSED void* fsa_src, __ATTRIB_UNUSED size_t fsa_length) {
	__FS_LOCAL_STATIC_OPTION fs_write_config_data_t* fsv_t1;
	fsv_t1 = (fs_write_config_data_t*)fs_zalloc(sizeof(fs_write_config_data_t));
	if (NULL == fsv_t1) {
		fs_low_level_failure(FS_FAILURE_fs_write_config_4);
		goto done;
	}
	fs_get_eeprom_partition_info(&fsv_t1->i, fsv_t1->buf, sizeof fsv_t1->buf);
	if (fsa_length > sizeof fsv_t1->config) {
		fs_low_level_failure(FS_FAILURE_fs_write_config_1);
		goto done;
	}
	fs_read_file_into_buffer(fsv_t1->config, sizeof fsv_t1->config, fsv_t1->buf, &fsv_t1->config_bytes_read);
	if ((fsa_address+fsa_length) > fsv_t1->config_bytes_read) {
		fs_low_level_failure(FS_FAILURE_fs_write_config_2);
		goto done;
	}
	memcpy( &fsv_t1->config[fsa_address], fsa_src, fsa_length);
	if (!fs_save_buffer_to_file(fsv_t1->buf, fsv_t1->config, fsv_t1->config_bytes_read)) {
		fs_low_level_failure(FS_FAILURE_fs_write_config_3);
		goto done;
	}
	done:
	fs_safe_shred_and_free(&fsv_t1, sizeof(*fsv_t1));
}
#endif // #if defined(HELPER_BUILD) && (defined(SECURITY_WRITE_CONFIG_USES_FILE) && SECURITY_WRITE_CONFIG_USES_FILE)

#include "security.memaccess.target.NVRx64.inc"
#include "security.memaccess.target.STM32F30x.inc"
#include "security.memaccess.target.RTL838x.inc"
#include "security.memaccess.target.EFR32xG13.inc"
#include "security.memaccess.target.ST50H.inc"

//__FS_FUNCTION_PREFER_INLINE u_int8_t  fs_read_mem8(uintptr_t address) { u_int8_t i = 0; fs_read_mem( &i, sizeof(i), address, sizeof(i)); return i; }
//__FS_FUNCTION_PREFER_INLINE u_int16_t fs_read_mem16(uintptr_t address) { u_int16_t i = 0; fs_read_mem( &i, sizeof(i), address, sizeof(i)); return i; }
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_mem32(uintptr_t fsa_address) { u_int32_t i = 0; fs_read_mem( &i, sizeof(i), fsa_address, sizeof(i)); return i; }
//__FS_FUNCTION_PREFER_INLINE u_int64_t fs_read_mem64(uintptr_t address) { u_int64_t i = 0; fs_read_mem( &i, sizeof(i), address, sizeof(i)); return i; }

#if SECURITY_INCLUDE_WRITE_MEM
__FS_FUNCTION_PREFER_INLINE void      fs_write_mem8(uintptr_t fsa_address, u_int8_t value) { fs_write_mem( fsa_address, &value, sizeof(value) ); }
#endif // #if SECURITY_INCLUDE_WRITE_MEM
__FS_FUNCTION_PREFER_INLINE u_int8_t  fs_read_config8(uintptr_t fsa_address) { u_int8_t i = 0; fs_read_config( &i, sizeof(i), fsa_address, sizeof(i)); return i;}
__FS_FUNCTION_PREFER_INLINE u_int16_t fs_read_config16(uintptr_t fsa_address) { u_int16_t i = 0; fs_read_config( &i, sizeof(i), fsa_address, sizeof(i)); return i;}
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_config32(uintptr_t fsa_address) { u_int32_t i = 0; fs_read_config( &i, sizeof(i), fsa_address, sizeof(i)); return i;}
__FS_FUNCTION_PREFER_INLINE u_int64_t fs_read_config64(uintptr_t fsa_address) { u_int64_t i = 0; fs_read_config( &i, sizeof(i), fsa_address, sizeof(i)); return i;}
__FS_FUNCTION_PREFER_INLINE u_int16_t fs_read_config_be16toh(uintptr_t fsa_address) { return be16toh( fs_read_config16(fsa_address) ); }
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_config_be32toh(uintptr_t fsa_address) { return be32toh( fs_read_config32(fsa_address) ); }
__FS_FUNCTION_PREFER_INLINE u_int64_t fs_read_config_be64toh(uintptr_t fsa_address) { return be64toh( fs_read_config64(fsa_address) ); }

#endif // #if SECURITY_IS_TARGET_BUILD
