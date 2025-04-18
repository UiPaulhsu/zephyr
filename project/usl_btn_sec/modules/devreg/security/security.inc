#ifndef __FS_INCLUDED__
#define __FS_INCLUDED__
/*
Configuration Settings:

    SECURITY_ENABLE_DEBUG_OUTPUT (default 0)
    SECURITY_ENABLE_FD_LEAK_DEBUG (default 0)
    SECURITY_ENABLE_DIAGNOSTIC_DUMPS (default 0)
    SECURITY_USE_STATICS_FOR_LOCALS (default 1)
    SECURITY_ENABLE_INLINE_HINTS (default 0)
    SECURITY_ENABLE_FORCED_INLINE (default 0)
    SECURITY_USE_STATICS_FOR_LOCALS (default 1)
    SECURITY_ENABLE_CRASHING (default 0)
    SECURITY_ENABLE_UNUSED_FUNCTION_WARNINGS (default 0)
    SECURITY_ENABLE_SIMULATION (default 0)
    SECURITY_ENABLE_SIGNAL_HANDLER (default 0)
    SECURITY_ENABLE_RSA_KEY_LOAD_SHORTCUT (default 1)
    SECURITY_ENABLE_GRANDFATHER_AR7240_AR7241 (default 1)
    SECURITY_ENABLE_TMPTAG (default 1)
    SECURITY_ENABLE_LOCKOUT (default 0)
    SECURITY_ENABLE_TAG_ETC_VERSION (default 1)
    SECURITY_ENABLE_TAG_ETC_COUNTERFEIT (default 1)
    SECURITY_ENABLE_SET_HOSTNAME_TO_COUNTERFEIT (default 1)
    SECURITY_ENABLE_SET_DOMAINNAME_TO_COUNTERFEIT (default 1)
    SECURITY_ENABLE_SET_PRINTK_RATELIMIT_TO_666 (default 1)
    SECURITY_ENABLE_DISABLE_IPv4_FORWARDING (default 1)
    SECURITY_ENABLE_MANGLE (default 1)

DANGER DANGER DANGER DANGER DANGER
DANGER DANGER DANGER DANGER DANGER

         SECURITY_DISABLED is for debugging security ONLY.  Do not use it.
         If you make a mistake and leave this disabled and a customer gets
         the image, this will be very Bad.

    SECURITY_DISABLED (default 0)

DANGER DANGER DANGER DANGER DANGER
DANGER DANGER DANGER DANGER DANGER 
 
    SECURITY_ENABLE_TEST_RSA_KEY replaces the key with non-production keys. 

Other Build Flags :
        BUILD_MIPS
        BUILD_ARM

Code Modifiers:
    - Prefix all locals with __FS_LOCAL_STATIC_OPTION
    - Prefix all functions with one of:

      __FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE
      __FS_FUNCTION_FORCED_INLINE
      __FS_FUNCTION_PREFER_INLINE
      __FS_FUNCTION_MAYBE_INLINE
*/
#ifndef SECURITY_DISABLED
	#define SECURITY_DISABLED 0
#endif

//////////////////////////////
/// No-op implementation
//////////////////////////////

#if SECURITY_DISABLED
#ifndef __INC_FLASH_SECURITY_INC__
#define SECURITY_SIMULATION_GLOBALS
#ifndef __ATTRIB_UNUSED
#define __ATTRIB_UNUSED __attribute__( ( unused ) )
#endif // #ifndef __ATTRIB_UNUSED
#undef fs_check_sec
#define fs_check_sec(...) do {} while(0)
#undef fs_check_sec_no_pci
#define fs_check_sec_no_pci(...) do {} while(0)
#undef fs_check_ubnt_signature
#define fs_check_ubnt_signature(...) do {} while(0)
#define FS_CHECKS_PASSED          1
#define FS_CHECKS_PASSED_SIGNED   1
#define FS_CHECKS_PASSED_UNSIGNED 0
#define FS_CHECKS_FAILED          0
#define FS_CHECKS_FAILED_SIGNED   0
#define FS_CHECKS_FAILED_UNSIGNED 0
#undef fs_debug_printf
#define fs_debug_printf(...) do {} while(0)
#undef fs_debug_printf_nosyslog
#define fs_debug_printf_nosyslog(...) do {} while(0)
#undef fs_dump
#define fs_dump(...) do {} while(0)
#undef fs_init_simulation
#define fs_init_simulation(...) do {} while(0)
#define __INC_FLASH_SECURITY_INC__
#endif // #ifndef __INC_FLASH_SECURITY_INC__
#endif // #if SECURITY_DISABLED

//////////////////////////////
/// Normal implementation
//////////////////////////////

#ifndef __INC_FLASH_SECURITY_INC__
#define __INC_FLASH_SECURITY_INC__

#ifdef __cplusplus
using namespace std;
#define __STDC_FORMAT_MACROS
#endif

#include "security.mangle.inc"
#include "security.version.inc"
#include "security.target.inc"
#include "security.dependencies.inc"
#include "security.settings.inc"
#include "security.classes.inc"
#include "security.misc.inc"
#include "security.config.inc"
#include "security.checks.switchmacros.inc"

#ifndef SECURITY_CONFIG_DEFS_ONLY
#include "security.util.inc"
#include "security.sim.inc"

#ifndef SECURITY_SIM_ONLY
#include "security.descramblers.inc"
#include "security.failhandlers.inc"
#include "security.output.inc"
#include "security.low.level.fileaccess.inc"
#include "security.errors.inc"
#include "security.low.level.failure.inc"
#include "security.fileaccess.inc"
#include "security.locking.inc"
#include "security.memaccess.inc"
#include "security.flash.inc"

#if SECURITY_LOW_MEMORY
#include "security.math.lowmemory.inc"
#else // SECURITY_LOW_MEMORY
#include "security.math.standard.inc"
#endif // #if SECURITY_LOW_MEMORY
#include "security.crypt.inc"
#if SECURITY_LOW_MEMORY
#include "security.rsa.lowmemory.inc"
#else
#include "security.rsa.standard.inc"
#endif
#include "security.blowfish.inc"
#include "security.hash.inc"
#include "security.hw.inc"

#ifndef SECURITY_HW_ONLY
#include "security.high.level.failure.inc"
#include "security.sec.inc"

#ifndef SECURITY_SEC_ONLY
#include "security.fbd.inc"
#include "security.os.boardinfo.inc"
#include "security.checks.inc"
#include "security.diagnostic.inc"
#endif // #ifndef SECURITY_SEC_ONLY
#endif // #ifndef SECURITY_HW_ONLY
#endif // #ifndef SECURITY_SIM_ONLY
#endif // #ifndef SECURITY_CONFIG_DEFS_ONLY

#endif // #ifndef __INC_FLASH_SECURITY_INC__
#endif // #ifndef __FS_INCLUDED__

