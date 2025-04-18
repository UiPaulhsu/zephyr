#define MT8117_CPU_REV      0x00008127

#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_MT8117) || SECURITY_ENABLE_SIMULATION)

#define __MT8117_CPU_REV_ID 0x08000000

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_MT8117_cpu_rev_id_hw(void) {
        return fs_read_mem32( __MT8117_CPU_REV_ID );
}

#if !SECURITY_ENABLE_SIMULATION
#undef fs_read_cpu_rev_id_hw
#define fs_read_cpu_rev_id_hw fs_read_MT8117_cpu_rev_id_hw
#endif // #if !SECURITY_ENABLE_SIMULATION


#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_ARM_MT8117) || SECURITY_ENABLE_SIMULATION)
