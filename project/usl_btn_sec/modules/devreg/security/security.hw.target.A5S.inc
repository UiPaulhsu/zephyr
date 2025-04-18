#if SECURITY_IS_TARGET_BUILD && defined(UBNT_ARM_A5S)

#define A5S_SSI_IDENT_ADDR      ((uintptr_t)0x7001e058)
#define A5S_SSI_VERSION_ADDR    ((uintptr_t)0x7000205c)

#define A5S_SSI_IDENT_MASK      0xffffffff
#define A5S_SSI_VERSION_MASK    0xffffffff

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_AMBA_ssi_ident_id_hw(void)                { return fs_read_mem32(A5S_SSI_IDENT_ADDR   ) & A5S_SSI_IDENT_MASK ;   }
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_AMBA_ssi_version_id_hw(void)              { return fs_read_mem32(A5S_SSI_VERSION_ADDR ) & A5S_SSI_VERSION_MASK ; }

#endif // #if SECURITY_IS_TARGET_BUILD && defined(UBNT_ARM_A5S)

// NB: This is shared 
#if SECURITY_IS_TARGET_BUILD && SECURITY_ENABLE_SIMULATION
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_AMBA_ssi_ident_id_hw(void) { 
    u_int32_t x = 0;
    fs_read_ini_hex_raw((u_int8_t*)&x, sizeof(x), g_simulation_ini_filename, "AMBA_SSI_IDENT_ID", 0, sizeof(x), 1);
    // fprintf(stderr,"AMBA_SSI_IDENT_ID: 0x%08x\n", x);
    return x;
}
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_AMBA_ssi_version_id_hw(void) { 
    u_int32_t x = 0;
    fs_read_ini_hex_raw((u_int8_t*)&x, sizeof(x), g_simulation_ini_filename, "AMBA_SSI_VERSION_ID", 0, sizeof(x), 1);
    // fprintf(stderr,"AMBA_SSI_VERSION_ID: 0x%08x\n", x);
    return x;
}
#endif // #if SECURITY_IS_TARGET_BUILD && SECURITY_ENABLE_SIMULATION

