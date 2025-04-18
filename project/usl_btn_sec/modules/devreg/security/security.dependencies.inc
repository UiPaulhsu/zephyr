#ifndef __INC_SECURITY_DEPENDENCIES_INC__
#define __INC_SECURITY_DEPENDENCIES_INC__

#if UBNT_LINUX

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif

#ifdef __KERNEL__
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
    #include <linux/kconfig.h>
#endif
    #include <linux/kernel.h>
    #include <linux/types.h>
    #include <linux/string.h>
    #include <linux/slab.h>
    #include <linux/netdevice.h>
    #include <linux/byteorder/generic.h>
    #include <linux/fs.h>
    #include <linux/spinlock.h>
    #include <linux/delay.h>
    #include <linux/pci.h>
    #include <linux/reboot.h>
    #include <linux/proc_fs.h> /* Necessary because we use the proc fs */
    #include <asm/uaccess.h>   /* for copy_from_user */
    #include <linux/buffer_head.h>
#if LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 15)
    #include <linux/spi/spi.h>
#endif
#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 33)
#include <linux/autoconf.h>
#else
#include <generated/autoconf.h>
#endif

#ifndef __WORDSIZE
#define __WORDSIZE 32
#endif // #ifndef __WORDSIZE

#if __WORDSIZE == 64
    #define __PRI64_PREFIX     "l"
    #define __PRIPTR_PREFIX    "l"
    #if !defined(_ATH_AH_OSDEP_H_) && !defined(_STDINT_H) && (!defined(UINTPTR_T_IN_TYPES) || !defined(INTPTR_T_IN_TYPES) || !defined(_LINUX_TYPES_H))
        #if !defined(HAVE_UINTPTR_T)
	#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24))
            typedef unsigned long int  uintptr_t;
	#endif
        #endif
        #if !defined(HAVE_INTPTR_T)
	#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24))
            typedef long int           intptr_t;
	#endif
        #endif
    #endif
#else
    #define __PRI64_PREFIX  "ll"
    #define __PRIPTR_PREFIX
    #if !defined(_ATH_AH_OSDEP_H_) && !defined(_STDINT_H) && (!defined(UINTPTR_T_IN_TYPES) || !defined(INTPTR_T_IN_TYPES) || !defined(_LINUX_TYPES_H))
        #if !defined(HAVE_UINTPTR_T)
	    #if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24))
            typedef unsigned int      uintptr_t;
            #endif
        #endif
        #if !defined(HAVE_INTPTR_T)
	    #if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24))
            typedef int               intptr_t;
		#endif
        #endif
    #endif
#endif // #if __WORDSIZE == 64
    #define PRIu8   "u"
    #define PRIu16  "u"
    #define PRIu32  "u"
    #define PRIu64  __PRI64_PREFIX "u"
    #define PRIx8  "x"
    #define PRIx16  "x"
    #define PRIx32  "x"
    #define PRIx64  __PRI64_PREFIX  "x"
    #define PRIxPTR __PRIPTR_PREFIX "x"
    #define PRId8     "hhd"
    #define PRId16    "hd"
    #define PRId32    "d"
    #define PRId64    "lld"
#else  // #ifdef __KERNEL__
    #include <stddef.h>
    #include <stdint.h>
    #include <sched.h>
#if defined(UBNT_X86) || defined(UBNT_X64)
    #include <execinfo.h>
#endif // #if defined(UBNT_X86) || defined(UBNT_X64)
    #include <setjmp.h>
    #include <stdio.h>
    #include <strings.h>
    #include <string.h>
    #include <sys/mman.h>
    #include <fcntl.h>
    #include <signal.h>
    #include <errno.h>
    #include <time.h>
    #define __USE_MISC 1
    #include <stdlib.h>
    #define __USE_GNU 1
    #include <unistd.h> // for sysconf
    #include <net/if.h>
    #include <sys/socket.h>
    #include <stdarg.h>
    #include <strings.h>
    #include <sys/ioctl.h>
    #include <sys/types.h>
    #include <inttypes.h>
    #include <endian.h>
    #include <byteswap.h>
    #include <syslog.h>
    #include <semaphore.h>
    #include <sys/time.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <sys/ioctl.h>
    #include <linux/types.h>
#if LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 15)
    #include <linux/spi/spidev.h>
#endif

#endif // #ifdef __KERNEL__
#endif // #if UBNT_LINUX

#if (defined(UBNT_ARM_STM32F30x) && UBNT_ARM_STM32F30x) || (defined(UBNT_EFR32xG13) && UBNT_EFR32xG13) || (defined(UBNT_ST50H) && UBNT_ST50H)
    #include <stdio.h>
    #include <stdint.h>
    #include <inttypes.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stddef.h>

    #define u_int8_t uint8_t
    #define u_int16_t uint16_t
    #define u_int32_t uint32_t
    #define u_int64_t uint64_t
    #define int8_t int8_t
    #define int16_t int16_t
    #define int32_t int32_t
    #define int64_t int64_t
    #define ssize_t ptrdiff_t

#endif // #if (defined(UBNT_ARM_STM32F30x) && UBNT_ARM_STM32F30x) || (defined(UBNT_EFR32xG13) && UBNT_EFR32xG13) || (defined(UBNT_ST50H) && UBNT_ST50H)

#endif // #ifndef __INC_SECURITY_DEPENDENCIES_INC__
