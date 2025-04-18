#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_BCM5616x) || SECURITY_ENABLE_SIMULATION)

#if SECURITY_ENABLE_SIMULATION
#define BCM5616x_CPU_REV      0x00008415

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_BCM5616x_cpu_rev_id_hw(void) {
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

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_BCM5616x_cpu_rev_id_hw(void) {
	unsigned int tmp;
#ifdef __KERNEL__
	volatile unsigned int *sku_id = NULL;

	sku_id = (volatile void *)ioremap(0x03210224,
		sizeof(unsigned int));

	tmp = ((*sku_id) & 0x0000ffff);
	iounmap(sku_id);
#else /* ifdef __KERNEL__ */
	{
		__bde_ioctl_t d;
		__ioctl(LUBDE_IPROC_CPU_REV_ID, &d);
		tmp = d.d1;
	}
#endif /* ifdef __KERNEL__ */
    return tmp;
}
#endif // #if SECURITY_ENABLE_SIMULATION

#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_BCM5616x) || SECURITY_ENABLE_SIMULATION)
