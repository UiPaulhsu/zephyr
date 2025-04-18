#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_MT7623) || SECURITY_ENABLE_SIMULATION)

#if SECURITY_ENABLE_SIMULATION

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_MT7623_cpu_rev_id_hw(void) {
	__FS_LOCAL_STATIC_OPTION u_int32_t fsv_t1;

	fsv_t1 = 0;
	fs_read_ini_hex_raw(
					   ((u_int8_t*)&fsv_t1), 
					   sizeof fsv_t1, 
					   g_simulation_ini_filename,
					   "CPU_ID", 
					   sizeof fsv_t1, 
					   sizeof fsv_t1,
					   1);
	fsv_t1 = be32toh(fsv_t1);
	return fsv_t1;
}

#else // #if SECURITY_ENABLE_SIMULATION

#ifdef __KERNEL__

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_MT7623_cpu_rev_id_hw(void) {
    /* FIXME: KMLUOH */
    return 0xdeadbabe;
}

#else /* ifdef __KERNEL__ */

#include <setjmp.h>

__FS_FUNCTION_PREFER_INLINE sigjmp_buf ill_jumper;
__FS_FUNCTION_PREFER_INLINE void (*old_sigill_handler)(int);

__FS_FUNCTION_PREFER_INLINE void sigill_handler(__ATTRIB_UNUSED int signum) {
	siglongjmp(ill_jumper, 1);
}

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_MT7623_cpu_rev_id_hw(void) {
    uint32_t id = 0xffffffff;
    int rc;
    /* typically, mrc p15 c0,c0 access would cause SIGILL
     * as the instruction is allowed ONLY in privileged mode.
     * however, properly patched kernel would pass this through..
     * as we might be called on unpatched kernel, handle SIGILL
     * gracefully.
     */
    old_sigill_handler = signal(SIGILL, sigill_handler);
    rc = sigsetjmp(ill_jumper, 1);
    if (!rc) {
            asm("mrc p15, 0, %0, c0, c0, 0" : "=r" (id));
    }
    signal(SIGILL, old_sigill_handler);
    return id;
}

#endif /* ifdef __KERNEL__ */

#endif // #if SECURITY_ENABLE_SIMULATION

#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_MT7623) || SECURITY_ENABLE_SIMULATION)
