#ifdef __cplusplus
using namespace std;
#define __STDC_FORMAT_MACROS
#endif

#ifndef UBNT_TARGET
#if defined(__i386__) || defined(__i686__) || defined(__pentiumpro__) || defined(UBNT_X86)
#undef UBNT_X86
#define UBNT_X86 1
#define UBNT_TARGET        "x86"
#define UBNT_LINUX         1
#elif defined(__x86_64__) || defined(__amd64__) || defined(UBNT_X64)
#undef UBNT_X64
#define UBNT_X64 1
#define UBNT_TARGET        "x64"
#define UBNT_LINUX         1
#elif defined(__OCTEON__) || defined(UBNT_MIPS_CN50xx)
#undef UBNT_MIPS_CN50xx
#define UBNT_MIPS          1
#define UBNT_MIPS_CN50xx   1
#define UBNT_TARGET        "CN50xx"
#define UBNT_SUPPORT_CLASS_ROUTER 1
#define UBNT_LINUX         1
#elif defined(UBNT_MIPS_MT7621)
#undef UBNT_MIPS_MT7621
#define UBNT_MIPS_MT7621   1
#define UBNT_MIPS          1
#define UBNT_TARGET        "MT7621"
#define UBNT_SUPPORT_CLASS_ROUTER 1
#define UBNT_LINUX         1
#elif defined(UBNT_MIPS_VSC7514)
#undef UBNT_MIPS_VSC7514
#define UBNT_MIPS          1
#define UBNT_MIPS_VSC7514  1
#define UBNT_TARGET        "VSC7514"
#define UBNT_SUPPORT_CLASS_BASIC 1
#define UBNT_LINUX         1
// defines for QCA851x are declared also in ../Makefile.am
#elif (defined(__mips__) && defined(__R3000__) && defined(__MIPSEB__) && (__GNUC_MINOR__ == 6) && (__GNUC_PATCHLEVEL__ == 3) && (__GNUC__ == 4)) || defined(UBNT_MIPS_QCA851x)
#undef UBNT_MIPS_QCA851x
#define UBNT_MIPS          1
#define UBNT_MIPS_QCA851x  1
#define UBNT_TARGET        "QCA851x"
#define UBNT_LINUX         1
#elif (defined(__mips__) && defined(__R3000__) && defined(__MIPSEB__)) || defined(UBNT_MIPS_ARxxxx)
#undef UBNT_MIPS_ARxxxx
#define UBNT_MIPS          1
#define UBNT_MIPS_ARxxxx   1
#define UBNT_TARGET        "ARxxxx"
#define UBNT_LINUX         1
#elif (defined(__mips__) && defined(__R3000__) && defined(__MIPSEB__)) || defined(UBNT_MIPS_RTL838x)
#undef UBNT_MIPS_RTL838x
#define UBNT_MIPS          1
#define UBNT_MIPS_RTL838x  1
#define UBNT_TARGET        "RTL838x"
#define UBNT_LINUX         1
#elif (defined(__mips__) && defined(__R3000__) && defined(__MIPSEL__)) || defined(UBNT_MIPS_BCM4706)
#undef UBNT_MIPS_BCM4706
#define UBNT_MIPS          1
#define UBNT_MIPS_BCM4706  1
#define UBNT_TARGET        "BCM4706"
#define UBNT_LINUX         1
#elif (defined(__arm__) && defined(__ARM_ARCH_5TE__) && (__GNUC__ == 4) && (__GNUC_MINOR__ == 1) && (__GNUC_PATCHLEVEL__ == 2)) || defined(UBNT_ARM_AM18xx)
#undef UBNT_ARM_AM18xx
#define UBNT_ARM           1
#define UBNT_ARM_AM18xx    1
#define UBNT_TARGET        "AM18xx"
#define UBNT_LINUX         1
#elif (defined(__arm__) && defined(__ARM_ARCH_5TE__) && (__GNUC__ == 4) && (__GNUC_MINOR__ == 5) && (__GNUC_PATCHLEVEL__ == 2)) || defined(UBNT_ARM_GM81xx)
#undef UBNT_ARM_GM81xx
#define UBNT_ARM           1
#define UBNT_ARM_GM81xx    1
#define UBNT_TARGET        "GM81xx"
#define UBNT_LINUX         1
#elif (defined(__arm__) && defined(__ARM_ARCH_7A__) && defined(__ARM_EABI__) && __ARM_EABI__ && (__ARMEL__) && defined(__ANDROID__) && (__ANDROID__) && (__GNUC__ == 4) && (__GNUC_MINOR__ == 4) && (__GNUC_PATCHLEVEL__ == 3)) || defined(UBNT_ARM_BCM111xx)
// echo "" | ../toolchains/android-ndk-r8/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/arm-linux-androideabi-cpp -dM | sort
#undef UBNT_ARM_BCM111xx
#define UBNT_ARM           1
#define UBNT_ARM_BCM111xx  1
#define UBNT_TARGET        "BCM111xx"
#define UBNT_LINUX         1
#elif (defined(__arm__) && defined(__ARM_ARCH_7A__) && defined(__ARM_EABI__) && __ARM_EABI__ && (__ARMEL__) && defined(__ANDROID__) && (__ANDROID__) && (__GNUC__ == 4) && (__GNUC_MINOR__ == 8) && (__GNUC_PATCHLEVEL__ == 0)) || defined(UBNT_ARM_MT8117)
// echo "" | ../toolchains/android-ndk-r9d/toolchains/arm-linux-androideabi-4.8/prebuilt/linux-x86_64/bin/arm-linux-androideabi-cpp -dM | sort
#undef UBNT_ARM_MT8117
#define UBNT_ARM           1
#define UBNT_ARM_MT8117    1
#define UBNT_TARGET        "MT8117"
#define UBNT_LINUX         1
#elif defined(UBNT_ARM_BCM5616x)
// echo "" | ../toolchains/arm-broadcom-linux-uclibcgnueabi/bin/arm-broadcom-linux-uclibcgnueabi-cpp -dM | sort
#undef UBNT_ARM_BCM5616x
#define UBNT_ARM           1
#define UBNT_ARM_BCM5616x  1
#define UBNT_TARGET        "BCM5616x"
#define UBNT_LINUX         1
#elif defined(UBNT_ARM_BCM5341x)
// echo "" | ../toolchains/arm-broadcom-linux-uclibcgnueabi/bin/arm-broadcom-linux-uclibcgnueabi-cpp -dM | sort
#undef UBNT_ARM_BCM5341x
#define UBNT_ARM           1
#define UBNT_ARM_BCM5341x  1
#define UBNT_TARGET        "BCM5341x"
#define UBNT_LINUX         1
#elif (defined(__arm__) && defined(__ARM_ARCH_7A__) && defined(__ARM_EABI__) && __ARM_EABI__ && (__ARMEL__) && (__GNUC__ == 4) && (__GNUC_MINOR__ == 7) && (__GNUC_PATCHLEVEL__ == 2)) || defined(UBNT_ARM_BCM5334x)
// echo "" | ../toolchains/arm-broadcom-linux-uclibcgnueabi/bin/arm-broadcom-linux-uclibcgnueabi-cpp -dM | sort
#undef UBNT_ARM_BCM5334x
#define UBNT_ARM           1
#define UBNT_ARM_BCM5334x  1
#define UBNT_TARGET        "BCM5334x"
#define UBNT_LINUX         1
#elif (defined(__arm__) && defined(__ARM_ARCH_7A__) && defined(__ARM_EABI__) && __ARM_EABI__ && (__ARMEL__) && (__GNUC__ == 4) && (__GNUC_MINOR__ == 9) && (__GNUC_PATCHLEVEL__ == 2)) || defined(UBNT_ARM_MT7623)
// echo "" | ../toolchains/buildroot-gcc492_arm_glibc/bin/arm-buildroot-linux-gnueabi-cpp -dM | sort
#undef UBNT_ARM_MT7623
#define UBNT_ARM           1
#define UBNT_ARM_MT7623    1
#define UBNT_TARGET        "MT7623"
#define UBNT_LINUX         1
#elif (defined(__arm__) && defined(__ARM_ARCH_7A__) && defined(__ARM_EABI__) && __ARM_EABI__ && (__ARMEL__) && (__GNUC__ == 4) && (__GNUC_MINOR__ == 6) && (__GNUC_PATCHLEVEL__ == 3) && !defined(UBNT_ARM_IPQ806x)) || defined(UBNT_ARM_IPQ40xx)
// echo "" | ../toolchain-arm_v7-a_gcc-4.6-linaro_uClibc-0.9.33.2_eabi/bin/arm-openwrt-linux-cpp -dM | sort
#define UBNT_ARM           1
#define UBNT_ARM_IPQ40xx   1
#define UBNT_TARGET "IPQ40xx"
#define UBNT_LINUX         1
#elif (defined(__arm__) && defined(__ARM_ARCH_7A__) && defined(__ARM_EABI__) && __ARM_EABI__ && (__ARMEL__) && (__GNUC__ == 4) && (__GNUC_MINOR__ == 6) && (__GNUC_PATCHLEVEL__ == 3) && !defined(UBNT_ARM_IPQ40xx)) || defined(UBNT_ARM_IPQ806x)
// echo "" | ../toolchain-arm_v7-a_gcc-4.6-linaro_uClibc-0.9.33.2_eabi/bin/arm-openwrt-linux-cpp -dM | sort
#define UBNT_ARM           1
#define UBNT_ARM_IPQ806x   1
#define UBNT_TARGET "IPQ806x"
#define UBNT_LINUX         1
#elif (defined(__arm__) && defined(__ARM_ARCH_6K__) && (__GNUC__ == 4) && (__GNUC_MINOR__ == 7) && (__GNUC_PATCHLEVEL__ == 3)) || defined(UBNT_ARM_A5S)
#undef UBNT_ARM_A5S
#define UBNT_ARM           1
#define UBNT_ARM_A5S       1
#define UBNT_AMBA          1
#define UBNT_TARGET        "A5S"
#define UBNT_LINUX         1
#elif (defined(__arm__) && defined(__ARM_ARCH_7A__) && (__GNUC__ == 4) && (__GNUC_MINOR__ == 8) && (__GNUC_PATCHLEVEL__ == 2)) || defined(UBNT_ARM_S2)
#undef UBNT_ARM_S2
#define UBNT_ARM           1
#define UBNT_ARM_S2        1
#define UBNT_AMBA          1
#define UBNT_TARGET        "S2"
#define UBNT_LINUX         1
#elif (defined(__arm__) && defined(__ARM_ARCH_7A__) && (__GNUC__ == 4) && (__GNUC_MINOR__ == 8) && (__GNUC_PATCHLEVEL__ == 3)) && defined(UBNT_ARM_S2L)
#undef UBNT_ARM_S2L
#define UBNT_ARM           1
#define UBNT_ARM_S2L       1
#define UBNT_AMBA          1
#define UBNT_TARGET        "S2L"
#define UBNT_LINUX         1
#elif (defined(__arm__) && defined(__ARM_ARCH_7A__) && (__GNUC__ == 4) && (__GNUC_MINOR__ == 8) && (__GNUC_PATCHLEVEL__ == 3)) && defined(UBNT_ARM_S2LM)
#undef UBNT_ARM_S2LM
#define UBNT_ARM           1
#define UBNT_ARM_S2LM      1
#define UBNT_AMBA          1
#define UBNT_TARGET        "S2LM"
#define UBNT_LINUX         1
#elif defined(__aarch64__) && defined(__ARM_ARCH_8A) && (__GNUC__ == 6) && (__GNUC_MINOR__ == 3) && (__GNUC_PATCHLEVEL__ == 1) && defined(UBNT_ARM64_S5L)
#undef UBNT_ARM64_S5L
#define UBNT_ARM64         1
#define UBNT_ARM64_S5L     1
#define UBNT_AMBA          1
#define UBNT_TARGET        "S5L"
#define UBNT_LINUX         1
#elif defined(__aarch64__) && defined(__ARM_ARCH_8A) && (__GNUC__ == 6) && (__GNUC_MINOR__ == 3) && (__GNUC_PATCHLEVEL__ == 1) && defined(UBNT_ARM64_S5LM)
#undef UBNT_ARM64_S5LM
#define UBNT_ARM64         1
#define UBNT_ARM64_S5LM    1
#define UBNT_AMBA          1
#define UBNT_TARGET        "S5LM"
#define UBNT_LINUX         1
#elif defined(STM32F30X) || defined(UBNT_STM32F30X)
#undef UBNT_ARM_STM32F30x
#define UBNT_ARM           1
#define UBNT_ARM_STM32F30x 1
#define UBNT_TARGET        "STM32F30x"
#define UBNT_LINUX         0
#elif defined(UBNT_ARM64_APQ8053)
#undef UBNT_ARM64_APQ8053
#define UBNT_ARM64         1
#define UBNT_ARM64_APQ8053 1
#define UBNT_TARGET        "APQ8053"
#define UBNT_LINUX         1
#elif defined(UBNT_ARM64_AL324)
#undef UBNT_ARM64_AL324
#define UBNT_ARM64         1
#define UBNT_ARM64_AL324 1
#define UBNT_TARGET        "AL324"
#define UBNT_LINUX         1
#elif defined(UBNT_ARM64_IPQ807x)
#undef UBNT_ARM64_IPQ807x
#define UBNT_ARM64         1
#define UBNT_ARM64_IPQ807x 1
#define UBNT_TARGET        "IPQ807x"
#define UBNT_LINUX         1
#elif defined(UBNT_EFR32xG13)
#undef UBNT_EFR32xG13
#define UBNT_EFR32xG13     1
#define UBNT_TARGET        "EFR32xG13"
#define UBNT_LINUX         0
#elif defined(UBNT_ST50H)
#undef UBNT_ST50H
#define UBNT_ST50H         1
#define UBNT_TARGET        "ST50H"
#define UBNT_LINUX         0
#else
#error "Could not identify product line from pre-processor flags."
/*
NB: To find out what target-specific pre-processor flags are present use

echo "" | cpp -dM | sort

with target prefixes it looks more like:

echo ""|toolchains/toolchain-mips_gcc4.1.2/bin/mips-linux-cpp -dM | sort

Always use the pre-processor flags that start and end with two underscores as
the rest are deprecated.
*/
#endif
#endif // #ifndef UBNT_TARGET

#ifndef UBNT_LINUX
#error UBNT_LINUX not defined.
#endif // #ifndef UBNT_LINUX
#if UBNT_LINUX
#include <linux/version.h>
#ifndef KERNEL_VERSION
#define KERNEL_VERSION(a,b,c) (((a) << 16) | ((b) << 8) | (c))
#endif
#endif // #if UBNT_LINUX

#if !defined(SECURITY_ENABLE_SIMULATION)
	#define SECURITY_ENABLE_SIMULATION 0
#endif // #if !defined(SECURITY_ENABLE_SIMULATION)

