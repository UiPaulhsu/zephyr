#ifndef __INC_SECURITY_SIM_INC__
#define __INC_SECURITY_SIM_INC__

#if SECURITY_ENABLE_SIMULATION
	extern const char* g_config_filename;
	extern const char* g_boardinfo_filename;
	extern const char* g_simulation_ini_filename;
	extern const char* g_simulation_pcidevices_filename;
	
	#define SECURITY_SIMULATION_GLOBALS \
		const char* g_config_filename                 = "eeprom.bin"; \
		const char* g_boardinfo_filename              = "board.info"; \
		const char* g_simulation_ini_filename         = "simulation.ini"; \
		const char* g_simulation_pcidevices_filename  = "devices"; 

	__FS_FUNCTION_PREFER_INLINE void fs_init_simulation(const char* MAYBE_USED( config_filename ), const char* MAYBE_USED( boardinfo__filename ), const char* MAYBE_USED( register_filename ),  const char* MAYBE_USED( pcidevices )) {
		g_config_filename                = config_filename;
		g_boardinfo_filename             = boardinfo__filename;
		g_simulation_ini_filename        = register_filename;
		g_simulation_pcidevices_filename = pcidevices;
	}

	__FS_FUNCTION_PREFER_INLINE const char* fs_get_boardinfo_pathname(void) {
		return g_boardinfo_filename;
	}

#else // #if SECURITY_ENABLE_SIMULATION
	#define SECURITY_SIMULATION_GLOBALS
	__FS_FUNCTION_PREFER_INLINE void fs_init_simulation(const char* UNUSED( config_filename ), const char* UNUSED( boardinfo__filename ), const char* UNUSED( register_filename ),  const char* UNUSED( pcidevices )) {}
#endif // #if SECURITY_ENABLE_SIMULATION

#endif // #ifndef __INC_SECURITY_SIM_INC__
