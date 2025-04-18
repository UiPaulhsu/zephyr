
#define fs_debug_printf_off(...) do {} while(0)
#if SECURITY_ENABLE_DEBUG_OUTPUT
static int g_output = 0;
#define fs_is_output_enabled() (0 == g_output)
#define fs_output_off(...) do { g_output++; 
#define fs_output_on(...)       g_output--; } while(0)
#else
#define fs_is_output_enabled()  0
#define fs_output_off(...)
#define fs_output_on(...)
#endif // #if SECURITY_ENABLE_DEBUG_OUTPUT
#ifdef __KERNEL__
	#if SECURITY_ENABLE_DEBUG_OUTPUT
		#define fs_debug_printf_always(...)          do { printk( __VA_ARGS__ ); } while(0)
		#define fs_debug_printf_nosyslog_always(...) do { printk( __VA_ARGS__ ); } while(0)
		#define fs_debug_printf_nosyslog(...)        do { if(fs_is_output_enabled()) { fs_debug_printf_nosyslog_always( __VA_ARGS__ ); } } while(0)
		#define fs_debug_printf(...)                 do { if(fs_is_output_enabled()) { fs_debug_printf_always( __VA_ARGS__ ); } } while(0)
	#else // #ifdef SECURITY_ENABLE_DEBUG_OUTPUT
		#define fs_debug_printf_always(...)          do {} while(0)
		#define fs_debug_printf_nosyslog_always(...) do {} while(0)
		#define fs_debug_printf(...)                 do {} while(0)
		#define fs_debug_printf_nosyslog(...)        do {} while(0)
	#endif // #ifdef SECURITY_ENABLE_DEBUG_OUTPUT
#else // #ifdef __KERNEL__
	#if SECURITY_ENABLE_DEBUG_OUTPUT
		#define fs_debug_printf_nosyslog_always(...) do { printf( __VA_ARGS__ ); fflush( stdout ); fflush( stderr ); } while(0)
		#define fs_debug_printf_always(...)          do { printf( __VA_ARGS__ ); fflush( stdout ); fflush( stderr ); syslog(LOG_ERR, __VA_ARGS__); } while(0)
		#define fs_debug_printf_nosyslog(...)        do { if(fs_is_output_enabled()) { fs_debug_printf_nosyslog_always( __VA_ARGS__ ); } } while(0)
		#define fs_debug_printf(...)                 do { if(fs_is_output_enabled()) { fs_debug_printf_always( __VA_ARGS__ ); } } while(0)
	#else // #ifdef SECURITY_ENABLE_DEBUG_OUTPUT
		#define fs_debug_printf_always(...)          do {} while(0)
		#define fs_debug_printf_nosyslog_always(...) do {} while(0)
		#define fs_debug_printf_nosyslog(...)        do {} while(0)
		#define fs_debug_printf(...)                 do {} while(0)
	#endif // #ifdef SECURITY_ENABLE_DEBUG_OUTPUT
#endif // #ifdef __KERNEL__

#if SECURITY_ENABLE_DEBUG_OUTPUT
__FS_FUNCTION_PREFER_INLINE void fs_hexdump( const void* const MAYBE_USED( fsa_p_data ), size_t MAYBE_USED( fsa_length )) {
        unsigned int fsv_t1 = 0;
        for(fsv_t1 = 0; fsa_length && fsv_t1 < fsa_length; fsv_t1++) {
                fs_debug_printf_nosyslog_always("%02x", ((u_int8_t*)fsa_p_data)[fsv_t1]);
        }
}
#else
#undef fs_hexdump
#define fs_hexdump(...)
#endif // #ifdef SECURITY_ENABLE_DEBUG_OUTPUT

