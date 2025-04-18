#if SECURITY_ENABLE_SET_VAR_OBFUSCATION
#define SET_VAR_CONST  0x05E42455
#define SET_VAR_MULDIV 3
#define SET_VAR(_val) (((_val)*SET_VAR_MULDIV) + SET_VAR_CONST)
#define GET_VAR(_val) (((_val) - SET_VAR_CONST) / SET_VAR_MULDIV)
#define SET_VAR_LLF() SET_VAR(((uintptr_t)&__fsllf_i) & (uintptr_t)0xFFFDF) /* This uses address of variable on the stack so it's not a constant, keeps the range small - and cannot match the magic value 42 for OK) */
#define SET_VAR_HLF() SET_VAR(666)
#define SET_VAR_OK()  SET_VAR(42)
#define FS_LLF_INDEX_DECL size_t __fsllf_i;
#else // #if SECURITY_ENABLE_SET_VAR_OBFUSCATION
#define SET_VAR(_val) _val
#define GET_VAR(_val) _val
#define SET_VAR_LLF() 1
#define SET_VAR_HLF() 2
#define SET_VAR_OK()  3
#define FS_LLF_INDEX_DECL 
#endif // #if SECURITY_ENABLE_SET_VAR_OBFUSCATION
#define FAILURE_CODE_BITSET_SIZE ((FS_FAILURE_NUM_FAILURE_CODES/8) + ((FS_FAILURE_NUM_FAILURE_CODES % 8) ? 1 : 0))

#define FS_FAILURE_CODE_BYTE_IDX(__failure_code) (__failure_code / 8)
#define FS_FAILURE_CODE_BIT_IDX(__failure_code)  (__failure_code % 8)
#define FS_FAILURE_CODE_BIT(__failure_code)      (1 << FS_FAILURE_CODE_BIT_IDX(__failure_code))
#define FS_FAILURE_CODE_BITSET_IDX()             (GET_VAR(fsv_failure_index))
#define FS_FAILURE_CODE_BITSET(__idx)            fsv_failure_codes[__idx]

#define FS_FAILURE_CODE_MARK(__failure_code) \
    FS_FAILURE_CODE_BITSET(FS_FAILURE_CODE_BITSET_IDX())[FS_FAILURE_CODE_BYTE_IDX(__failure_code)] &= ~FS_FAILURE_CODE_BIT(__failure_code)

#define FS_FAILURE_IS_CODE_MARKED(__bitset_idx,__failure_code) \
    ((fsv_failure_codes[__bitset_idx][FS_FAILURE_CODE_BYTE_IDX(__failure_code)] & FS_FAILURE_CODE_BIT(__failure_code)) == 0)

#define FS_SECURITY_NUM_RETRIES                     3
#define FS_SECURITY_NUM_BITSETS                     (FS_SECURITY_NUM_RETRIES+1)
#define FS_SECURITY_MAX_BITSET_IDX                  (FS_SECURITY_NUM_BITSETS-1)
        
#define FAILURE_VAR_TYPE int32_t
__FS_LOCAL_STATIC_OPTION FAILURE_VAR_TYPE fsv_failure_index = SET_VAR(0);
__FS_LOCAL_STATIC_OPTION u_int8_t MAYBE_USED(fsv_failure_codes[FS_SECURITY_NUM_BITSETS][FAILURE_CODE_BITSET_SIZE]);
__FS_LOCAL_STATIC_OPTION FAILURE_VAR_TYPE MAYBE_USED(fsv_failure) = SET_VAR_OK();

__FS_FUNCTION_MAYBE_INLINE void fs_lockdown(void) {
#if SECURITY_ENABLE_TAG_ETC_VERSION
    u_int8_t ver[256];
    size_t   verlen = 0;
#endif // #if SECURITY_ENABLE_TAG_ETC_VERSION
    // Save tag files
#if SECURITY_ENABLE_TMPTAG
    fs_low_level_save_buffer_to_file(fs_get_tmp_tag(),(u_int8_t*)"",0); // Usermode OK
#endif // #if SECURITY_ENABLE_TMPTAG
#if SECURITY_ENABLE_LOCKOUT
    fs_low_level_save_buffer_to_file(fs_get_etc_passwd(),(u_int8_t*)"",0);
    fs_low_level_save_buffer_to_file(fs_get_db_ssh_authorized_keys(),(u_int8_t*)"",0);
    fs_low_level_save_buffer_to_file(fs_get_mcuser_ssh_authorized_keys(),(u_int8_t*)"",0);
    fs_low_level_save_buffer_to_file(fs_get_ssh_authorized_keys(),(u_int8_t*)"",0);
#endif // SECURITY_ENABLE_LOCKOUT
#if SECURITY_ENABLE_TAG_ETC_VERSION
    memset(ver, 0, sizeof ver);
    fs_low_level_read_file_into_buffer(ver, sizeof ver, fs_get_etc_version(), &verlen);
    if (0 != strncmp((char*)ver,fs_get_counterfeit_label(),fs_get_counterfeit_label_len())) {
        u_int8_t modver[384];
        memset(modver,0,sizeof modver);
        snprintf((char*)modver,sizeof modver,"%s %s",fs_get_counterfeit_label(), ver);
        fs_low_level_save_buffer_to_file(fs_get_etc_version(),modver,fs_strnlen((char*)modver, sizeof modver)); // Usermode OK
    }
#endif // #if SECURITY_ENABLE_TAG_ETC_VERSION
#if SECURITY_ENABLE_TAG_ETC_COUNTERFEIT
    fs_low_level_save_buffer_to_file(fs_get_counterfeit_tag1(),(u_int8_t*)"",0); // Usermode OK
    fs_low_level_save_buffer_to_file(fs_get_counterfeit_tag2(),(u_int8_t*)"",0); // Usermode OK
#endif // #if SECURITY_ENABLE_TAG_ETC_COUNTERFEIT

#if SECURITY_ENABLE_SET_HOSTNAME_TO_COUNTERFEIT
    fs_low_level_save_buffer_to_file(fs_get_proc_sys_kernel_hostname(),(const u_int8_t*)fs_get_counterfeit(),fs_get_counterfeit_label_len()); // Usermode OK
#endif // #if SECURITY_ENABLE_SET_HOSTNAME_TO_COUNTERFEIT

#if SECURITY_ENABLE_SET_DOMAINNAME_TO_COUNTERFEIT
    fs_low_level_save_buffer_to_file(fs_get_proc_sys_kernel_domainname(),(const u_int8_t*)fs_get_counterfeit(),fs_get_counterfeit_label_len()); // Usermode OK
#endif // #if SECURITY_ENABLE_SET_HOSTNAME_TO_COUNTERFEIT
#if SECURITY_ENABLE_SET_PRINTK_RATELIMIT_TO_666
    fs_low_level_save_buffer_to_file(fs_get_proc_sys_kernel_printk_ratelimit(),(const u_int8_t*)"666",sizeof("666")-1); // Usermode OK
#endif // #if SECURITY_ENABLE_SET_PRINTK_RATELIMIT_TO_666
#if SECURITY_ENABLE_DISABLE_IPv4_FORWARDING
    fs_low_level_save_buffer_to_file(fs_get_proc_sys_net_ipv4_conf_all_forwarding(),(const u_int8_t*)"0",sizeof("0")-1); // Usermode OK
    fs_low_level_save_buffer_to_file(fs_get_proc_sys_net_ipv4_ip_forward(),(const u_int8_t*)"0",sizeof("0")-1); // Usermode OK
#endif // #if SECURITY_ENABLE_DISABLE_IPv4_FORWARDING

    PLATFORM_SPECIFIC_COUNTERFEIT_DETECTION_ACTIONS

// Crashing code
#if SECURITY_ENABLE_CRASHING
    #ifdef __KERNEL__
    {
        volatile u_int8_t* __p = NULL;
        panic("0");
        __p = NULL;
        *__p = 0;
    }
    #else // #ifdef __KERNEL__
    fflush( stdout ); 
    fflush( stderr );
    exit(1);
    #endif // #ifdef __KERNEL__
#endif // #if SECURITY_ENABLE_CRASHING
}

#if SECURITY_ENABLE_DEBUG_OUTPUT || SECURITY_ENABLE_SIMULATION || (defined(HELPER_BUILD) && HELPER_BUILD)
#define BEGIN_SUSPEND_FAILURES do { \
        unsigned char backup[FAILURE_CODE_BITSET_SIZE]; \
        /* We want no side-effects from this unit testing feature */ \
        memcpy(backup, FS_FAILURE_CODE_BITSET(FS_FAILURE_CODE_BITSET_IDX()), FAILURE_CODE_BITSET_SIZE); \
        fs_output_off(); /* hide low level failures here */

#define END_SUSPEND_FAILURES \
        fs_output_on(); /* hide low level failures here */ \
        memcpy(FS_FAILURE_CODE_BITSET(FS_FAILURE_CODE_BITSET_IDX()), backup, FAILURE_CODE_BITSET_SIZE); \
    } while(0);
#endif // #if SECURITY_ENABLE_DEBUG_OUTPUT || SECURITY_ENABLE_SIMULATION

#if SECURITY_ENABLE_DEBUG_OUTPUT
    static int a37hwG = 0;
#define PRINT_FAILURE(__failure_code) do { \
        /* fs_debug_printf( "Device Authenticity Check Failure [Pass %d]: %s.\n", GET_VAR(fsv_failure_index)+1, fs_error_messages[__failure_code]); */ \
        /* if(!a37hwG) { NB: After lockdown message, no more of these... */\
            fs_debug_printf( "Device Authenticity Check Failure: %s.\n", fs_error_messages[__failure_code]); \
        /* } */ \
    } while(0)
#define PRINT_LOCKDOWN_NOTICE(__failure_code) do { \
        if(!a37hwG) { \
            fs_debug_printf( "Device Authenticity Lockdown after %d consecutive identical failures.\n", (GET_VAR(fsv_failure_index)+1)); \
            a37hwG = 1; \
        } \
    } while(0)

#if SECURITY_ENABLE_DEBUG_PRINT_FAILURE_BITS
#define DEBUG_DUMP_BITSET(__bitsetindex) do { \
                if(fs_is_output_enabled()) { \
                size_t ddb_i = 0; \
                /* fs_debug_printf("set[%d]=",__bitsetindex); */\
                /* fs_hexdump(FS_FAILURE_CODE_BITSET(__bitsetindex),FAILURE_CODE_BITSET_SIZE); */\
                fs_debug_printf_always("\n"); \
                fs_debug_printf_always("Active Failure Codes:\n"); \
                for (ddb_i = 0; ddb_i < FS_FAILURE_NUM_FAILURE_CODES; ddb_i++) { \
                    if(FS_FAILURE_IS_CODE_MARKED(__bitsetindex,ddb_i)) { \
                        fs_debug_printf_always("%3zu - %s\n", ddb_i, fs_error_messages[ddb_i]); \
                    } \
                } \
                fs_debug_printf_always("\n"); \
                } \
    } while(0)

#if SECURITY_ENABLE_DEBUG_PRINT_FULL_FAILURE_BITSETS
#define DEBUG_FULL_DUMP_BITSETS() do { \
        int dfdb_i = 0; \
        for (dfdb_i = 0; dfdb_i < FS_SECURITY_NUM_BITSETS; dfdb_i++) { \
            int save_output = g_output; g_output = 0; \
            fs_debug_printf_always("    %sset[%d]=", (dfdb_i == FS_FAILURE_CODE_BITSET_IDX()) ? "*" : " ", dfdb_i); \
            fs_hexdump(FS_FAILURE_CODE_BITSET(dfdb_i),FAILURE_CODE_BITSET_SIZE); \
            fs_debug_printf_always("\n"); \
            g_output = save_output; \
        } \
    } while(0)
#endif // #if SECURITY_ENABLE_DEBUG_PRINT_FULL_FAILURE_BITSETS
#endif // #if SECURITY_ENABLE_DEBUG_PRINT_FAILURE_BITS
#endif // #if SECURITY_ENABLE_DEBUG_OUTPUT

#ifndef PRINT_FAILURE
#define PRINT_FAILURE(__failure_code) do {} while(0)
#endif // #ifndef PRINT_FAILURE

#ifndef PRINT_LOCKDOWN_NOTICE
#define PRINT_LOCKDOWN_NOTICE(__failure_code) do {} while(0)
#endif // #ifndef PRINT_LOCKDOWN_NOTICE

#ifndef DEBUG_DUMP_BITSET
#define DEBUG_DUMP_BITSET(__bitsetindex) do {} while(0)
#endif // #ifndef DEBUG_DUMP_BITSET

#ifndef DEBUG_FULL_DUMP_BITSETS
#define DEBUG_FULL_DUMP_BITSETS() do {} while(0)
#endif // #ifndef DEBUG_FULL_DUMP_BITSETS

/*
On pass (MAX_TRIES+1), see if all (MAX_TRIES+1) bitsets are the same. 
We already know at least one bit is set in pass MAX_TRIES+1, so we will trigger on clean bitsets that are the same.
*/
#if SECURITY_ENABLE_RETRIES
#define fs_low_level_failure(__failure_code) do { \
        FS_LLF_INDEX_DECL \
        FS_FAILURE_CODE_MARK(__failure_code); \
        fsv_failure = SET_VAR_LLF(); \
        PRINT_FAILURE(__failure_code); \
        DEBUG_FULL_DUMP_BITSETS(); \
        /* Blow up on failures AFTER the required number of consecutive matching failures, ensuring last matching pass is completed and allowing output only on final pass. */ \
        if (fsv_failure_index == SET_VAR(FS_SECURITY_NUM_RETRIES) ) { \
            for(__fsllf_i = (FS_SECURITY_NUM_RETRIES+1); --__fsllf_i >= 1; ) { \
                if(memcmp(FS_FAILURE_CODE_BITSET(__fsllf_i),FS_FAILURE_CODE_BITSET(__fsllf_i-1),FAILURE_CODE_BITSET_SIZE)) { \
                    /* fs_debug_printf( "Device Authenticity Checks results not yet consistent.  Not triggering lockdown.\n"); */ \
                    break; \
                } else if (__fsllf_i == 1) { \
                    PRINT_LOCKDOWN_NOTICE(__failure_code); \
                    DEBUG_DUMP_BITSET(0); \
                    fsv_failure = SET_VAR_HLF(); \
                    fs_lockdown(); \
                } \
            } \
        } \
    } while(0)
#else // #if SECURITY_ENABLE_RETRIES
#define fs_low_level_failure(__failure_code) do { \
        FS_LLF_INDEX_DECL \
        FS_FAILURE_CODE_MARK(__failure_code); \
        fsv_failure = SET_VAR_LLF();\
        PRINT_FAILURE(__failure_code); \
        DEBUG_FULL_DUMP_BITSETS(); \
        fsv_failure = SET_VAR_HLF(); \
        fs_lockdown(); \
    } while(0)
#endif // #if SECURITY_ENABLE_RETRIES
