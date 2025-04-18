#if SECURITY_IS_TARGET_BUILD && (defined(UBNT_MIPS_QCA851x) || SECURITY_ENABLE_SIMULATION)

/* Packet processor GLOBAL_CTRL_0
		7:0 Revision ID, 1 - 0xA0, 2 - 0xB0
		15:8 Device family ID, 0x20 - MUSIC-I */
#define __QCA851x_PP_REV_ID 0x18800000
#define __QCA851x_PP_REV_ID_SHIFT 0
#define __QCA851x_PP_REV_ID_MASK 0x0000ffff


/* GMAC master control register DMA_MAS_CTRL
		23:16 Device revision ID, 0x01
		30:24 Device ID number, 0x40 */
#define __QCA851x_GMAC_REV_ID 0x18111400
#define __QCA851x_GMAC_REV_ID_SHIFT 16
#define __QCA851x_GMAC_REV_ID_MASK 0x00007fff

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_QCA851x_rev_id_hw(void)
{
	/* Combine PP and GMAC IDs to single 31bit value */
	return (((fs_read_mem32( __QCA851x_PP_REV_ID ) >> __QCA851x_PP_REV_ID_SHIFT) & __QCA851x_PP_REV_ID_MASK) | 
		(((fs_read_mem32( __QCA851x_GMAC_REV_ID ) >> __QCA851x_GMAC_REV_ID_SHIFT) & __QCA851x_GMAC_REV_ID_MASK) << 16));
}

#endif // #if SECURITY_IS_TARGET_BUILD && (defined(UBNT_MIPS_QCA851x) || SECURITY_ENABLE_SIMULATION)
