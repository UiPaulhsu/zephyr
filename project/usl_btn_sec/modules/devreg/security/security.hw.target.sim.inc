#if SECURITY_ENABLE_SIMULATION

    __FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_cpu_rev_id_hw(void) { 
        __FS_LOCAL_STATIC_OPTION u_int32_t fsv_t1;

        fsv_t1 = 0;
        fs_read_ini_hex_raw(
                           ((u_int8_t*)&fsv_t1), 
                           sizeof fsv_t1, 
                           g_simulation_ini_filename,
                           "CPU_ID", 
                           4,/* bytes, not characters */ 
                           4,
                           1); 
        return be32toh(fsv_t1);
    }
#endif // #if SECURITY_ENABLE_SIMULATION
