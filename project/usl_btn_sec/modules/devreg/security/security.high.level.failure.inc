#if SECURITY_IS_TARGET_BUILD

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE int _fs_failure_is_security_data_present(void) {
    switch (fs_read_config8(FLASH_SECURITY_OFFSET_FORMAT)) {
    CASE_SUPPORTED_FORMATS
        return (fs_read_config_be16toh(FLASH_SECURITY_OFFSET_SUBVENDOR_ID) == 0x0777);
    default:
        return 0;
    }
}
#endif // #if SECURITY_IS_TARGET_BUILD

/*
The old boards that were shipped before security system was added:
  1. Must be AR7240, AR7241, or AR7242
  2. Must have at least one radio (this excludes switches 
  3. Must not have security data, by definition.
  4. Must not be an enforced AR724x SSID: 
      0xe532 (UniFiAP-Outdoor)
      0xe515 (UniFiAP-Outdoor5G)
      0xe1d2 (Rocket M2 Titanium, R2T)
      0xe1d5 (Rocket M5 Titanium, R5T)
      0xe2d2 (Bullet M2 Titanium B2T)
      0xe2d5 (Bullet M5 Titanium B5T)
      0xe006 (NanoStation M6, N6N)
      0xe2e5 (NanoBridge M5 HP, NB5-HP)
      0xe2b2 (NanoBridge M2 HP, NB2-HP)
      0xe1b6 (Rocket M6, R6N)
      0xe255 (AirGrid M2 new layout, AG5-HP)
      0xe252 (AirGrid M2 new layout, AG2-HP)
*/
#define IS_AR7240_OR_AR7241_OR_AR7242             (fs_is_ar7240(fs_read_cpu_rev_id_hw()) || fs_is_ar7241(fs_read_cpu_rev_id_hw()) || fs_is_ar7242(fs_read_cpu_rev_id_hw()))
#define HAS_AT_LEAST_ONE_RADIO                    (fs_read_wifi_radio1_mac_rev_id_hw() != 0)
#define DOES_NOT_HAVE_SECURITY_DATA               (!_fs_failure_is_security_data_present())

/* ~0xe532 = 0x1ACD */
#define IS_NOT_SSID_e532                          ((!fs_file_exists(fs_get_boardinfo_pathname()) || \
        (((0xfffff1fc) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0xf0f0) >> 4)) \
        +((0xffffafdf) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0x0f0f) << 4)))))

/* ~0xe515 = 0x1AEA */
#define IS_NOT_SSID_e515                          ((!fs_file_exists(fs_get_boardinfo_pathname()) || \
        (((0xfffff1fe) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0xf0f0) >> 4)) \
        +((0xffffafaf) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0x0f0f) << 4)))))

/* ~0xe1d2 = 0x1e2d */
#define IS_NOT_SSID_e1d2                          ((!fs_file_exists(fs_get_boardinfo_pathname()) || \
        (((0xfffff1f2) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0xf0f0) >> 4)) \
        +((0xffffefdf) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0x0f0f) << 4)))))

/* ~0xe1d5 = 0x1e2a */
#define IS_NOT_SSID_e1d5                          ((!fs_file_exists(fs_get_boardinfo_pathname()) || \
        (((0xfffff1f2) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0xf0f0) >> 4)) \
        +((0xffffefaf) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0x0f0f) << 4)))))

/* 0xe2d2 = 0x1d2d */
#define IS_NOT_SSID_e2d2                          ((!fs_file_exists(fs_get_boardinfo_pathname()) || \
        (((0xfffff1f2) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0xf0f0) >> 4)) \
        +((0xffffdfdf) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0x0f0f) << 4)))))

/* 0xe2d5 = 0x1d2a */
#define IS_NOT_SSID_e2d5                          ((!fs_file_exists(fs_get_boardinfo_pathname()) || \
        (((0xfffff1f2) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0xf0f0) >> 4)) \
        +((0xffffdfaf) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0x0f0f) << 4)))))

/* 0xe006 */
#define IS_NOT_SSID_e006                          ((!fs_file_exists(fs_get_boardinfo_pathname()) || \
	(((0xfffff1ff) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0xf0f0) >> 4)) \
	+((0xffffff9f) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0x0f0f) << 4)))))

/* 0xe2e5 */
#define IS_NOT_SSID_e2e5                          ((!fs_file_exists(fs_get_boardinfo_pathname()) || \
	(((0xfffff1f1) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0xf0f0) >> 4)) \
	+((0xffffdfaf) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0x0f0f) << 4)))))

/* 0xe2b2 */
#define IS_NOT_SSID_e2b2                          ((!fs_file_exists(fs_get_boardinfo_pathname()) || \
	(((0xfffff1f4) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0xf0f0) >> 4)) \
	+((0xffffdfdf) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0x0f0f) << 4)))))

/* 0xe1b6 */
#define IS_NOT_SSID_e1b6                          ((!fs_file_exists(fs_get_boardinfo_pathname()) || \
	(((0xfffff1f4) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0xf0f0) >> 4)) \
	+((0xffffef9f) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0x0f0f) << 4)))))

/* 0xe255 */
#define IS_NOT_SSID_e255                          ((!fs_file_exists(fs_get_boardinfo_pathname()) || \
	(((0xfffff1fa) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0xf0f0) >> 4)) \
	+((0xffffdfaf) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0x0f0f) << 4)))))

/* 0xe252 */
#define IS_NOT_SSID_e252                          ((!fs_file_exists(fs_get_boardinfo_pathname()) || \
	(((0xfffff1fa) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0xf0f0) >> 4)) \
	+((0xffffdfdf) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0x0f0f) << 4)))))

/* ~0xe502 = 0x1AFD */
#define IS_SSID_e502                          ((fs_file_exists(fs_get_boardinfo_pathname()) && \
        (!(((0xfffff1ff) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0xf0f0) >> 4)) \
        +((0xffffafdf) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0x0f0f) << 4))))))

/* ~0xe512 = 0x1AED */
#define IS_SSID_e512                          ((fs_file_exists(fs_get_boardinfo_pathname()) && \
        (!(((0xfffff1fe) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0xf0f0) >> 4)) \
        +((0xffffafdf) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0x0f0f) << 4))))))

/* ~0xe302 = 0x1CFD */
#define IS_SSID_e302                          ((fs_file_exists(fs_get_boardinfo_pathname()) && \
        (!(((0xfffff1ff) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0xf0f0) >> 4)) \
        +((0xffffcfdf) ^ ~((fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0) & 0x0f0f) << 4))))))

#ifndef UNIFI_NOT_ENFORCE_OLDUAP
#define IS_NOT_AN_ENFORCED_SSID (IS_NOT_SSID_e532 && \
IS_NOT_SSID_e515 && \
IS_NOT_SSID_e1d2 && \
IS_NOT_SSID_e1d5 && \
IS_NOT_SSID_e2d2 && \
IS_NOT_SSID_e2d5 && \
IS_NOT_SSID_e006 && \
IS_NOT_SSID_e2e5 && \
IS_NOT_SSID_e2b2 && \
IS_NOT_SSID_e1b6 && \
IS_NOT_SSID_e255 && \
IS_NOT_SSID_e252)
#else
/* for UniFi AP only */
#define IS_NOT_AN_ENFORCED_SSID (IS_SSID_e502 || IS_SSID_e512 || IS_SSID_e302)
#endif

////////////////////////////////////////////////////////////////////////////////
// Grandfather in the old stuff...
////////////////////////////////////////////////////////////////////////////////

#if ( ( (defined(UBNT_MIPS_ARxxxx) && UBNT_MIPS_ARxxxx) || SECURITY_ENABLE_SIMULATION) && SECURITY_ENABLE_GRANDFATHER_AR7240_AR7241)

#if SECURITY_ENABLE_SIMULATION
static inline int _fs_check_for_exemption(void) {
        int is_mips_target = 0;
        char product_class[128];
        memset(product_class,0,sizeof(product_class));
        fs_read_ini_key( (unsigned char*)product_class, sizeof product_class, g_simulation_ini_filename, "product_class", 1 );
        if(0 == strcasecmp(product_class,"radio")) {
                is_mips_target = 1;
        } else if(0 == strcasecmp(product_class,"rf_board")) {
                is_mips_target = 1;
        } else if(0 == strcasecmp(product_class,"rf_board_dual")) {
                is_mips_target = 1;
        } else if(0 == strcasecmp(product_class,"digital_board")) {
                is_mips_target = 1;
        } else if(0 == strcasecmp(product_class,"switch")) {
                is_mips_target = 1;
        } else {
                is_mips_target = 0;
        }
        // fs_debug_printf("is_mips_target=%d\n",is_mips_target);
        return is_mips_target;
}
        #define FS_CHECK_FOR_EXEMPTION _fs_check_for_exemption()
#else
        #define FS_CHECK_FOR_EXEMPTION 1
#endif // #if SECURITY_ENABLE_SIMULATION

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE int fs_eeprom_probe_crc(const unsigned char* buf, size_t size)
{
	u_int16_t sum = 0;
	u_int16_t len, i;
	u_int16_t* ptr = (u_int16_t*)buf;

	len = be16toh(*ptr);
	if ((len > size) || (len == 0))
		return 0;

	/* calculate */
	for (i = 0; i < len / 2; ++i)
	{
		sum ^= *ptr;
		ptr++;
	}

	if (sum == 0xFFFF)
	{
		return 1;
	}

	return 0;
}

#define AR7K_EEPROM_SIZE 0x1000
#define AR7K_EEPROM_OFFSET 0x1000

/* KITE */
#define ATH7K_BASE_EEOFFSET_4K	0x80
/* KIWI */
#define ATH7K_BASE_EEOFFSET_8K	0x100
/* MERLIN */
#define ATH7K_BASE_EEOFFSET_DEF	0x200

#define ATH7K_BASE_OFFSET_MAC 0xC

#define OUI_00 0x00
#define OUI_15 0x15
#define OUI_6D 0x6D

#define OUI_27 0x27
#define OUI_22 0x22

#define OUI_DC 0xDC
#define OUI_9F 0x9F
#define OUI_DB 0xDB

#define SCRAMBLED_BYTE_TEST(_a, _x, _r1, _r2) ((((_a) ^ (_r1)) + (_r2)) == (((_x) ^ (_r1)) + (_r2)))
#define TEST_OUI_BYTE_00(_x) SCRAMBLED_BYTE_TEST(OUI_00, (_x), 0xf6, 0x95)
#define TEST_OUI_BYTE_15(_x) SCRAMBLED_BYTE_TEST(OUI_15, (_x), 0x4b, 0xf9)
#define TEST_OUI_BYTE_6D(_x) SCRAMBLED_BYTE_TEST(OUI_6D, (_x), 0x1b, 0x57)
#define TEST_OUI_BYTE_27(_x) SCRAMBLED_BYTE_TEST(OUI_27, (_x), 0xd1, 0x89)
#define TEST_OUI_BYTE_22(_x) SCRAMBLED_BYTE_TEST(OUI_22, (_x), 0x82, 0x21)
#define TEST_OUI_BYTE_DC(_x) SCRAMBLED_BYTE_TEST(OUI_DC, (_x), 0xf0, 0x6a)
#define TEST_OUI_BYTE_9F(_x) SCRAMBLED_BYTE_TEST(OUI_9F, (_x), 0x29, 0xf8)
#define TEST_OUI_BYTE_DB(_x) SCRAMBLED_BYTE_TEST(OUI_DB, (_x), 0x1b, 0x81)

#define TEST_OUI_00156D_OR_002722_OR_DC9FDB(_x) \
	( TEST_OUI_BYTE_00(_x[0]) && ( \
		(TEST_OUI_BYTE_27(_x[1]) && TEST_OUI_BYTE_22(_x[2])) || \
		(TEST_OUI_BYTE_15(_x[1]) && TEST_OUI_BYTE_6D(_x[2])) ) ) || \
	(TEST_OUI_BYTE_9F(_x[1]) && TEST_OUI_BYTE_DB(_x[2]) && TEST_OUI_BYTE_DC(_x[0]))

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_fill_eth_oui(u_int8_t *eth_oui)
{
	fs_read_config(eth_oui, 3, 0x00, 3);
}
/*                      
NB: This only works on ATH7K boards.  For others, we don't use it.
*/
__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE int fs_fill_ath_oui(u_int8_t *ath_oui)
{
	u_int8_t *ee;
	u_int8_t *eep = NULL;
	u_int8_t eth_oui[MAC_OUI_SIZE];
    int result = 0;
	
	// Allocate size for EEPROM and two MACs - one is FFs and one is reserved for ETH oui
	// but they are interleaved to obfuscate the code
	ee = (u_int8_t*)fs_malloc(AR7K_EEPROM_SIZE);
	fs_read_config(ee, AR7K_EEPROM_SIZE, AR7K_EEPROM_OFFSET, AR7K_EEPROM_SIZE);
	fs_fill_eth_oui(eth_oui);

	if(fs_eeprom_probe_crc(ee + ATH7K_BASE_EEOFFSET_DEF, AR7K_EEPROM_SIZE - ATH7K_BASE_EEOFFSET_DEF)) {
		eep = ee + ATH7K_BASE_EEOFFSET_DEF;
	}
	else if (fs_eeprom_probe_crc(ee + ATH7K_BASE_EEOFFSET_8K, AR7K_EEPROM_SIZE - ATH7K_BASE_EEOFFSET_8K)) {
		eep = ee + ATH7K_BASE_EEOFFSET_8K;
	}
	else if(fs_eeprom_probe_crc(ee + ATH7K_BASE_EEOFFSET_4K, AR7K_EEPROM_SIZE - ATH7K_BASE_EEOFFSET_4K)) {
		eep = ee + ATH7K_BASE_EEOFFSET_4K;
	}
#if SECURITY_ENABLE_ATH_OUI_MATCHES_EEPROM_WITH_CORRUPTED_CRCS

#define ATH7K_MAGIC_HIGH 0xa5
#define ATH7K_MAGIC_LOW  0x5a

#define MAGIC_TEST1(__ee__) ( ((0xFF - __ee__[1]) == __ee__[0]) && ((~(ATH7K_MAGIC_LOW & 0xf)) == ~(__ee__[1] & 0xf)) && (~(ATH7K_MAGIC_LOW & 0xf0) == ~(__ee__[1] & 0xf0)) )
#define MAGIC_TEST2(__ee__) ( (((~__ee__[0]) & 0xFF) == __ee__[1]) && ((~ATH7K_MAGIC_LOW & 0xFF) == (~__ee__[1] & 0xFF)) )
#define MAGIC_TEST3(__ee__) ( (__ee__[1] == (0xFF - __ee__[0])) && (~__ee__[0] == ~ATH7K_MAGIC_HIGH) )

#define EEPROM_MATCH_BY_MAGIC_AND_OUI1(__ee__,__eth_oui__,__base__) \
    (  MAGIC_TEST1(__ee__) \
    && __eth_oui__[2] == __ee__[ATH7K_BASE_OFFSET_MAC + 2 + __base__] \
    && __eth_oui__[0] == __ee__[__base__ + ATH7K_BASE_OFFSET_MAC + 0] \
    && __ee__[ATH7K_BASE_OFFSET_MAC + __base__ + 1] == __eth_oui__[1])

#define EEPROM_MATCH_BY_MAGIC_AND_OUI2(__ee__,__eth_oui__,__base__) \
    (  __ee__[__base__ + ATH7K_BASE_OFFSET_MAC + 1] == __eth_oui__[1] \
    && MAGIC_TEST2(__ee__) \
    && __eth_oui__[0] == __ee__[0 + __base__ + ATH7K_BASE_OFFSET_MAC] \
    && __eth_oui__[2] == __ee__[__base__ + 2 + ((2*ATH7K_BASE_OFFSET_MAC) >> 1)])

#define EEPROM_MATCH_BY_MAGIC_AND_OUI3(__ee__,__eth_oui__,__base__) \
    (__ee__[__base__ + ATH7K_BASE_OFFSET_MAC + 1] == __eth_oui__[1] \
    && __eth_oui__[0] == __ee__[__base__ + ATH7K_BASE_OFFSET_MAC + 0] \
    && MAGIC_TEST3(__ee__) \
    && __ee__[ATH7K_BASE_OFFSET_MAC + __base__ + 2] == __eth_oui__[2])

	/* Allow for corrupted EEPROM CRCs..., the WLAN0 and ETH0 OUI should match */
	else if (EEPROM_MATCH_BY_MAGIC_AND_OUI1(ee, eth_oui, ATH7K_BASE_EEOFFSET_8K))
	{
		eep = ee + ATH7K_BASE_EEOFFSET_8K;
	} 
	else if (EEPROM_MATCH_BY_MAGIC_AND_OUI2(ee, eth_oui, ATH7K_BASE_EEOFFSET_4K))
	{
		eep = ee + ATH7K_BASE_EEOFFSET_4K;
	} 
    else if (EEPROM_MATCH_BY_MAGIC_AND_OUI3(ee, eth_oui, ATH7K_BASE_EEOFFSET_DEF))
	{
		eep = ee + ATH7K_BASE_EEOFFSET_DEF;
	}
#endif // #if SECURITY_ENABLE_ATH_OUI_MATCHES_EEPROM_WITH_CORRUPTED_CRCS
	else 
	{
		eep = ee + ATH7K_BASE_EEOFFSET_DEF;
		/* 
		The old behavior was to ALWAYS copy whatever was at the MERLIN OUI location.
		 
		Because we didn't match EEPROM (with or without valid CRC), we can safely return 0xFFs for ath OUI. 
		 
		The caller, fs_check_ouis(), is going to fail the test for grandfathering anyway.
		 
		We'll just reset those bytes in memory to effect the change
		*/
		*((u_int32_t*)&eep[ATH7K_BASE_OFFSET_MAC]) = 0xFFFFFFFF;
        result = -1;
	}

	eep += ATH7K_BASE_OFFSET_MAC;

	ath_oui[0] = *(eep++);
	ath_oui[1] = *(eep++);
	ath_oui[2] = *eep;

	fs_free(ee);
	return result;
}

/*
NB: If the board is not ATH7K with caldata, fs_fill_ath_oui will not be the wifi OUI.  This is good because it also forces fs_check_ouis to return TRUE for non ATH7K boards. 
*/
__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE int fs_check_ouis(void)
{
	u_int8_t eth_oui[3] = {0,};
	u_int8_t ath_oui[3] = {0,};
	int ee_result;

	fs_fill_eth_oui(eth_oui);
	ee_result = fs_fill_ath_oui(ath_oui);

	return ( (!ee_result) && ((eth_oui[0] == ath_oui[0]) && (eth_oui[1] == ath_oui[1]) && (eth_oui[2] == ath_oui[2])) &&
		 (TEST_OUI_00156D_OR_002722_OR_DC9FDB(eth_oui)) );

}

#define HAS_OUI_00156D_OR_002722_OR_DC9FDB fs_check_ouis()

#if SECURITY_ENABLE_DEBUG_OUTPUT && SECURITY_ENABLE_DEBUG_PRINT_FAILURE_BITS && SECURITY_IS_TARGET_BUILD && ( (defined(UBNT_MIPS_ARxxxx) && UBNT_MIPS_ARxxxx) || SECURITY_ENABLE_SIMULATION)

static int fs_failure_nonexempt_wrote_reason = 0;

// NB: Use fs_debug_printf_always because this code is ONLY hit when we are running with "dumpfailure" build and we need to see why it did what it dis.
#define EXPLAIN_NON_EXEMPT_STATUS(...) do { \
			if(!fs_failure_nonexempt_wrote_reason) { \
				BEGIN_SUSPEND_FAILURES \
				fs_failure_nonexempt_wrote_reason = 1; \
				do { \
					if(!IS_AR7240_OR_AR7241_OR_AR7242) { \
						fs_debug_printf_always("Authenticity Check Enforced: Board is not AR724x.\n"); \
					} \
					if(!HAS_AT_LEAST_ONE_RADIO) { \
						fs_debug_printf_always("Authenticity Check Enforced: Board does not have at least one radio.\n"); \
					} \
					if(!DOES_NOT_HAVE_SECURITY_DATA) { \
						fs_debug_printf_always("Authenticity Check Enforced: Security data is present.\n"); \
					} \
					if(!IS_NOT_AN_ENFORCED_SSID) { \
						fs_debug_printf_always("Authenticity Check Enforced: Subsystem ID is 0x%04x.\n", fs_read_ini_hex16( fs_get_boardinfo_pathname(), fs_get_boardinfo_key__board_sysid(), 1, 0x0)); \
					} \
					if(!HAS_OUI_00156D_OR_002722_OR_DC9FDB) { \
						u_int8_t eth_oui[3] = {0,}; \
						u_int8_t ath_oui[3] = {0,}; \
						int ee_result; \
						fs_fill_eth_oui(eth_oui); \
						ee_result = fs_fill_ath_oui(ath_oui); \
						fs_debug_printf_always("Authenticity Check Enforced: OUIs ETH %02x%02x%02x ATH %02x%02x%02x (Calibration data %s).\n", \
							eth_oui[0], eth_oui[1], eth_oui[2], ath_oui[0], ath_oui[1], ath_oui[2], (ee_result == 0 ? "found" : "not found") \
						); \
					} \
				} while(0); \
				END_SUSPEND_FAILURES \
			} \
		} while(0)
#else // #if SECURITY_ENABLE_DEBUG_OUTPUT
#define EXPLAIN_NON_EXEMPT_STATUS(...) do {} while(0)
#endif // #if SECURITY_ENABLE_DEBUG_OUTPUT

#define HANDLE_EXEMPTION(__failure_code) /* do not add do/while here! break must leave OUTER loop */ \
		if (FS_CHECK_FOR_EXEMPTION) {   						\
			if (1   											\
			   && IS_AR7240_OR_AR7241_OR_AR7242 				\
			   && HAS_AT_LEAST_ONE_RADIO						\
			   && DOES_NOT_HAVE_SECURITY_DATA   				\
			   && IS_NOT_AN_ENFORCED_SSID   					\
			   && HAS_OUI_00156D_OR_002722_OR_DC9FDB			\
			   )									            \
			{ \
				if (SECURITY_ENABLE_DEBUG_PRINT_FAILURE_BITS) { \
					fs_debug_printf_always( "Device Authenticity Check Failure: %s [EXEMPTED].\n", fs_error_messages[__failure_code]); \
				} \
				break; /* NB: Do not remove or enclose in another loop! */ \
			} else { \
				EXPLAIN_NON_EXEMPT_STATUS(); \
			} \
		}

#else // #if ( ( (defined(UBNT_MIPS_ARxxxx) && UBNT_MIPS_ARxxxx) || SECURITY_ENABLE_SIMULATION) && SECURITY_ENABLE_GRANDFATHER_AR7240_AR7241)


#define HANDLE_EXEMPTION(...) do {} while(0)

#endif // #if ( ( (defined(UBNT_MIPS_ARxxxx) && UBNT_MIPS_ARxxxx) || SECURITY_ENABLE_SIMULATION) && SECURITY_ENABLE_GRANDFATHER_AR7240_AR7241)

#define fs_failure(__failure_code) do { \
                HANDLE_EXEMPTION(__failure_code); \
                fs_low_level_failure( __failure_code ); \
        } while(0)

