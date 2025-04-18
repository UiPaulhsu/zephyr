#ifndef __INC_SECURITY_UTIL_INC__
#define __INC_SECURITY_UTIL_INC__

#if UBNT_LINUX
#ifdef __KERNEL__
__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_ndelay(int nanoseconds) {
    ndelay(nanoseconds);
}
__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_delay(int seconds) {
    msleep(seconds * 1000);
}
#else // #ifdef __KERNEL__
__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_ndelay(int nanoseconds) {
    struct timespec x = { 0, 0 };
    x.tv_nsec = nanoseconds;
    nanosleep(&x, NULL);
}
__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE void fs_delay(int seconds) {
    struct timespec x = { 0, 0 };
    x.tv_sec = seconds;
    nanosleep(&x, NULL);
}
#endif // #ifdef __KERNEL__
#endif // #if UBNT_LINUX

static __ATTRIB_UNUSED uint8_t fsv_mac_all_ones[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE size_t fs_strnlen(const char* buf, size_t max) {
    if (buf == NULL) {
        return 0;
    } else {
        const char* end = buf+max;
        register const char* pos = buf;
        for (; *pos && pos < end; ++pos)
            ;
        return pos-buf;
    }
}

#endif // #ifndef __INC_SECURITY_UTIL_INC__

