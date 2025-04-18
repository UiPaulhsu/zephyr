#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_AM3xxx) || SECURITY_ENABLE_SIMULATION)

#define __AM3xxx_CPU_REV_ID 0x4830A204
// #define __AM3xxx_CPU_REV_ID 0x4001BFFC

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_AM3xxx_cpu_rev_id_hw(void) {
        return fs_read_mem32( __AM3xxx_CPU_REV_ID );
}
#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_AM3xxx) || SECURITY_ENABLE_SIMULATION)
