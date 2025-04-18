#if SECURITY_IS_TARGET_BUILD && defined(UBNT_ARM64_S5L)

#define S5L_SSI_IDENT_ADDR      ((uintptr_t)0xE0022058)
#define S5L_SSI_VERSION_ADDR    ((uintptr_t)0xE002205c)

#define S5L_SSI_IDENT_MASK      0xffffffff
#define S5L_SSI_VERSION_MASK    0xffffffff

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_AMBA_ssi_ident_id_hw(void)                { return fs_read_mem32(S5L_SSI_IDENT_ADDR   ) & S5L_SSI_IDENT_MASK ;   }
__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_AMBA_ssi_version_id_hw(void)              { return fs_read_mem32(S5L_SSI_VERSION_ADDR ) & S5L_SSI_VERSION_MASK ; }

#endif // #if SECURITY_IS_TARGET_BUILD && defined(UBNT_ARM64_S5L)
