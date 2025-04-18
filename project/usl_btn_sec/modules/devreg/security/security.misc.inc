#ifndef __INC_SECURITY_MISC_INC__
#define __INC_SECURITY_MISC_INC__

//*****************************************************************************
// MACRO DEFINITIONS
//*****************************************************************************

#if SECURITY_USE_STATICS_FOR_LOCALS
#define __FS_LOCAL_STATIC_OPTION static
#else
#define __FS_LOCAL_STATIC_OPTION
#endif // #ifdef

#ifndef __ATTRIB_UNUSED
#if defined(__GNUC__)
#define __ATTRIB_UNUSED __attribute__( ( unused ) )
#else // #if defined(__GNUC__)
#define __ATTRIB_UNUSED
#endif // #if defined(__GNUC__)
#endif // #ifndef __ATTRIB_UNUSED

#if defined(UBNT_ARM_STM32F30x)
#pragma anon_unions
#endif // #if defined(UBNT_ARM_STM32F30x)

#ifndef __ATTRIB_PACKED_PRE
#if defined(UBNT_ARM_STM32F30x)
#define __ATTRIB_PACKED_PRE __packed
#else // #if defined(UBNT_ARM_STM32F30x)
#define __ATTRIB_PACKED_PRE
#endif // #if defined(UBNT_ARM_STM32F30x)
#endif // #ifndef __ATTRIB_PACKED_PRE

#ifndef __ATTRIB_PACKED_POST
#if defined(__GNUC__) && !defined(UBNT_ARM_STM32F30x)
#define __ATTRIB_PACKED_POST __attribute__(( packed ))
#else // #if defined(__GNUC__) && !defined(UBNT_ARM_STM32F30x)
#define __ATTRIB_PACKED_POST
#endif // #if defined(__GNUC__) && !defined(UBNT_ARM_STM32F30x)
#endif // #ifndef __ATTRIB_PACKED_POST

#if SECURITY_ENABLE_UNUSED_FUNCTION_WARNINGS
#define __FS_FUNCTION_UNUSED_OPTION
#else
#define __FS_FUNCTION_UNUSED_OPTION __ATTRIB_UNUSED
#endif // #if SECURITY_ENABLE_UNUSED_FUNCTION_WARNINGS

#ifndef __FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE
#if defined(__GNUC__)
#define __FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE static inline __attribute__( ( always_inline ) ) __FS_FUNCTION_UNUSED_OPTION
#else // #if defined(__GNUC__)
#define __FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE static inline
#endif // #if defined(__GNUC__)
#endif // #ifndef __FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE

#define __FS_FUNCTION_MAYBE_INLINE static __FS_FUNCTION_UNUSED_OPTION

#if SECURITY_ENABLE_INLINE_HINTS
#define __FS_FUNCTION_PREFER_INLINE static inline __FS_FUNCTION_UNUSED_OPTION
#else // #if SECURITY_ENABLE_INLINE_HINTS
#define __FS_FUNCTION_PREFER_INLINE __FS_FUNCTION_MAYBE_INLINE
#endif // #if SECURITY_ENABLE_INLINE_HINTS

#if SECURITY_ENABLE_FORCED_INLINE
#define __FS_FUNCTION_FORCED_INLINE __FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE
#elif SECURITY_ENABLE_INLINE_HINTS
#define __FS_FUNCTION_FORCED_INLINE __FS_FUNCTION_PREFER_INLINE
#else
#define __FS_FUNCTION_FORCED_INLINE __FS_FUNCTION_MAYBE_INLINE
#endif // #if !SECURITY_NO_INLINE_HINTS

#undef UNUSED
#ifdef UNUSED
#elif defined( __GNUC__ )
#define UNUSED(x) UNUSED_ ## x __ATTRIB_UNUSED
#elif defined( __LCLINT__ )
#define UNUSED(x) /*@unused@*/ x
#else
#define UNUSED(x) x
#endif

#ifdef MAYBE_USED
#elif defined( __GNUC__ )
#define MAYBE_USED(x) x __ATTRIB_UNUSED
#elif defined( __LCLINT__ )
#define MAYBE_USED(x) /*@unused@*/ x
#else
#define MAYBE_USED(x) x
#endif

#ifndef BLOCK_SIZES
#define BLOCK_SIZES
#define BLOCK_512  ((size_t)0x00200)
#define BLOCK_1K   ((size_t)0x00400)
#define BLOCK_2K   ((size_t)0x00800)
#define BLOCK_3K   ((size_t)0x00c00)
#define BLOCK_4K   ((size_t)0x01000)
#define BLOCK_6K   ((size_t)0x01800)
#define BLOCK_8K   ((size_t)0x02000)
#define BLOCK_10K  ((size_t)0x02800)
#define BLOCK_12K  ((size_t)0x03000)
#define BLOCK_14K  ((size_t)0x03800)
#define BLOCK_16K  ((size_t)0x04000)
#define BLOCK_18K  ((size_t)0x04800)
#define BLOCK_20K  ((size_t)0x05000)
#define BLOCK_22K  ((size_t)0x05800)
#define BLOCK_24K  ((size_t)0x06000)
#define BLOCK_26K  ((size_t)0x06800)
#define BLOCK_28K  ((size_t)0x07000)
#define BLOCK_30K  ((size_t)0x07800)
#define BLOCK_32K  ((size_t)0x08000)
#define BLOCK_34K  ((size_t)0x08800)
#define BLOCK_36K  ((size_t)0x09000)
#define BLOCK_38K  ((size_t)0x09800)
#define BLOCK_40K  ((size_t)0x0A000)
#define BLOCK_42K  ((size_t)0x0A800)
#define BLOCK_44K  ((size_t)0x0B000)
#define BLOCK_46K  ((size_t)0x0B800)
#define BLOCK_48K  ((size_t)0x0C000)
#define BLOCK_50K  ((size_t)0x0C800)
#define BLOCK_52K  ((size_t)0x0D000)
#define BLOCK_54K  ((size_t)0x0D800)
#define BLOCK_56K  ((size_t)0x0E000)
#define BLOCK_58K  ((size_t)0x0E800)
#define BLOCK_60K  ((size_t)0x0F000)
#define BLOCK_62K  ((size_t)0x0F800)
#define BLOCK_64K  ((size_t)0x10000)
#endif // #ifndef BLOCK_SIZES

#ifndef __KERNEL__
#define fs_strtoul strtoul
#else // #ifndef __KERNEL__
#define fs_strtoul simple_strtoul
#endif // #ifndef __KERNEL__

#ifndef __KERNEL__
#ifndef __force
#define __force
#endif
#endif // #ifndef __KERNEL__

#ifdef __KERNEL__
#define fs_malloc(__size)          kmalloc(__size,GFP_ATOMIC)
#define fs_zalloc(__size)          kzalloc(__size,GFP_ATOMIC)
#define fs_calloc( __num, __size)  kzalloc((__num*__size),GFP_ATOMIC)
#define fs_free(__obj )            kfree(__obj)

__FS_FUNCTION_PREFER_INLINE void *fs_realloc(void *__obj, size_t __size) {
    void *p_new = NULL;
    if(NULL == __obj) {
        return kmalloc(__size, GFP_ATOMIC);
    }
    //if(ksize(__obj) >= __size) {
    //    return __obj;
    //}
    p_new = kmalloc(__size, GFP_ATOMIC);
    if(p_new != NULL) {
        memcpy(p_new, __obj, __size);
    }
    kfree(__obj);
    return p_new;
}
#else

#define pvPortMalloc(size)      k_malloc(size)
#define pvPortCalloc(num, size) calloc(num, size)  // 需有 libc
#define vPortFree(p)            k_free(p)
#define pvPortRealloc(p, size)  realloc(p, size)   // 需有 libc

#define fs_malloc(__size)          pvPortMalloc( __size )
#define fs_zalloc(__size)          pvPortCalloc( __size, 1 )
#define fs_calloc(__size,__num)    pvPortCalloc(__size, __num )
#define fs_free(__p )              vPortFree( __p )
#define fs_realloc(__p, __size)    pvPortRealloc(__p, __size)

#endif // #ifdef __KERNEL__

#define fs_safe_shred_and_free(__pp,__size) do { \
        if(*__pp != NULL) { \
            memset( *__pp, 0xbd, __size); \
            fs_free( *__pp ); \
            *__pp = NULL; \
        } \
    } while(0)

#define fs_safe_shred(__p,__size) do { \
        if(__p != NULL) { \
            memset( __p, 0xbd, __size); \
            __pp = NULL; \
        } \
    } while(0)

#ifndef HAVE_ENDIAN_FUNCS
#define HAVE_ENDIAN_FUNCS
#ifdef __KERNEL__
#ifndef htobe16
#define htobe16 __cpu_to_be16
#endif
#ifndef htole16
#define htole16 __cpu_to_le16
#endif
#ifndef be16toh
#define be16toh __be16_to_cpu
#endif
#ifndef le16toh
#define le16toh __le16_to_cpu
#endif
#ifndef htobe32
#define htobe32 __cpu_to_be32
#endif
#ifndef htole32
#define htole32 __cpu_to_le32
#endif
#ifndef be32toh
#define be32toh __be32_to_cpu
#endif
#ifndef le32toh
#define le32toh __le32_to_cpu
#endif
#ifndef htobe64
#define htobe64 __cpu_to_be64
#endif
#ifndef htole64
#define htole64 __cpu_to_le64
#endif
#ifndef be64toh
#define be64toh __be64_to_cpu
#endif
#ifndef le64toh
#define le64toh __le64_to_cpu
#endif
#else // #ifdef __KERNEL__

#if !defined(__bswap_16) && defined(__swap16)
#define __bswap_16 __swap16
#endif // #if !defined(__bswap_16) && defined(__swap16)
#if !defined(__bswap_32) && defined(__swap32)
#define __bswap_32 __swap32
#endif // #if !defined(__bswap_32) && defined(__swap32)
#if !defined(__bswap_64) && defined(__swap64)
#define __bswap_64 __swap64
#endif // #if !defined(__bswap_64) && defined(__swap64)

#if (defined(UBNT_ARM_STM32F30x) && UBNT_ARM_STM32F30x) || (defined(UBNT_EFR32xG13) && UBNT_EFR32xG13) || (defined(UBNT_ST50H) && UBNT_ST50H)
#define __bswap_16(x) ( (((x) & 0x00FF) << 8) | \
                        (((x) & 0xFF00) >> 8) )
#define __bswap_32(x) ( (((x) & 0xFF000000) >> 24) | \
                        (((x) & 0x00FF0000) >>  8) | \
                        (((x) & 0x0000FF00) <<  8) | \
                        (((x) & 0x000000FF) << 24) )
#define __bswap_64(x) ( (((x) & 0xFF00000000000000) >> 56) | \
                        (((x) & 0x00FF000000000000) >> 40) | \
                        (((x) & 0x0000FF0000000000) >> 24) | \
                        (((x) & 0x000000FF00000000) >>  8) | \
                        (((x) & 0x00000000FF000000) <<  8) | \
                        (((x) & 0x0000000000FF0000) << 24) | \
                        (((x) & 0x000000000000FF00) << 40) | \
                        (((x) & 0x00000000000000FF) << 56) )

#endif // #if (defined(UBNT_ARM_STM32F30x) && UBNT_ARM_STM32F30x) || (defined(UBNT_EFR32xG13) && UBNT_EFR32xG13) || (defined(UBNT_ST50H) && UBNT_ST50H)

#if __BYTE_ORDER == __LITTLE_ENDIAN
#ifndef htobe16
#define htobe16(x) __bswap_16 (x)
#endif
#ifndef htole16
#define htole16(x) (x)
#endif
#ifndef be16toh
#define be16toh(x) __bswap_16 (x)
#endif
#ifndef le16toh
#define le16toh(x) (x)
#endif
#ifndef htobe32
#define htobe32(x) __bswap_32 (x)
#endif
#ifndef htole32
#define htole32(x) (x)
#endif
#ifndef be32toh
#define be32toh(x) __bswap_32 (x)
#endif
#ifndef le32toh
#define le32toh(x) (x)
#endif
#ifndef htobe64
#define htobe64(x) __bswap_64 (x)
#endif
#ifndef htole64
#define htole64(x) (x)
#endif
#ifndef be64toh
#define be64toh(x) __bswap_64 (x)
#endif
#ifndef le64toh
#define le64toh(x) (x)
#endif
#else // #if __BYTE_ORDER == __LITTLE_ENDIAN
#ifndef htobe16
#define htobe16(x) (x)
#endif
#ifndef htole16
#define htole16(x) __bswap_16 (x)
#endif
#ifndef be16toh
#define be16toh(x) (x)
#endif
#ifndef le16toh
#define le16toh(x) __bswap_16 (x)
#endif
#ifndef htobe32
#define htobe32(x) (x)
#endif
#ifndef htole32
#define htole32(x) __bswap_32 (x)
#endif
#ifndef be32toh
#define be32toh(x) (x)
#endif
#ifndef le32toh
#define le32toh(x) __bswap_32 (x)
#endif
#ifndef htobe64
#define htobe64(x) (x)
#endif
#ifndef htole64
#define htole64(x) __bswap_64 (x)
#endif
#ifndef be64toh
#define be64toh(x) (x)
#endif
#ifndef le64toh
#define le64toh(x) __bswap_64 (x)
#endif
#endif // #if __BYTE_ORDER == __LITTLE_ENDIAN
#endif // #ifdef __KERNEL__
#endif // #ifndef HAVE_ENDIAN_FUNCS

#define _FS_STRINGIFY(__x__) #__x__
#define FS_STRINGIFY(__x__) _FS_STRINGIFY(__x__)

#endif // #ifndef __INC_SECURITY_MISC_INC__
