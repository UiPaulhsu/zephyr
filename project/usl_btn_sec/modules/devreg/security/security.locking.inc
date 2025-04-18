#if SECURITY_ENABLE_FS_LOCK

#define _FS_LOCK_TIMEOUT_SECONDS          0
#define _FS_LOCK_TIMEOUT_ERROR_VALUE      EAGAIN
#define _FS_LOCK_TIMEOUT_BREAK_LOCK       0

#ifdef __KERNEL__
#if defined(UBNT_MIPS_ARxxxx) || defined(UBNT_MIPS_BCM4706)
#if defined(CONFIG_MTD_ATH_FLASH) && CONFIG_MTD_ATH_FLASH
	extern void ath_flash_spi_down(void);
	extern void ath_flash_spi_up(void);
	#define FS_LOCK_MTD_SEMAPHORE     do { ath_flash_spi_down();
	#define FS_UNLOCK_MTD_SEMAPHORE   ath_flash_spi_up(); } while(0);
#endif // #if CONFIG_MTD_ATH_FLASH

#if defined(CONFIG_MTD_AR7240_SPI_FLASH) && CONFIG_MTD_AR7240_SPI_FLASH
	extern void ar7240_flash_spi_down(void);
	extern void ar7240_flash_spi_up(void);
	#define FS_LOCK_MTD_SEMAPHORE     do { ar7240_flash_spi_down();
	#define FS_UNLOCK_MTD_SEMAPHORE   ar7240_flash_spi_up(); } while(0);
#endif // #if CONFIG_MTD_AR7240_SPI_FLASH

#ifdef CONFIG_SPI_ATH79
	#include "asm/mach-ath79/ath79.h"
	#define FS_LOCK_MTD_SEMAPHORE     do { ath79_spi_lock();
	#define FS_UNLOCK_MTD_SEMAPHORE   ath79_spi_unlock(); } while(0);
#endif // CONFIG_SPI_ATH79

#if defined(CONFIG_BCM947XX) && CONFIG_BCM947XX
	extern void ccsflash_spi_lock(void);
	extern void ccsflash_spi_unlock(void);
	#define FS_LOCK_MTD_SEMAPHORE     do { ccsflash_spi_lock();
	#define FS_UNLOCK_MTD_SEMAPHORE   ccsflash_spi_unlock(); } while(0);
#endif // #if defined(CONFIG_BCM947XX) && CONFIG_BCM947XX

#ifdef CONFIG_SPI_MT7621
	extern void mt7621_spi_lock(void);
	extern void mt7621_spi_unlock(void);
	#define FS_LOCK_MTD_SEMAPHORE	do { mt7621_spi_lock();
	#define FS_UNLOCK_MTD_SEMAPHORE	mt7621_spi_unlock(); } while(0);
#endif // #ifdef CONFIG_SPI_MT7621

#ifndef FS_LOCK_MTD_SEMAPHORE
	#error "No flash locking functions supported in kernel for platform $(UBNT_TARGET)"
#endif // #ifndef FS_LOCK_MTD_SEMAPHORE

#else // #if defined(UBNT_MIPS_ARxxxx) || defined(UBNT_MIPS_BCM4706) || defined(UBNT_MIPS_RTL838x)
	// NB: having the empty do/while encapsulation still helps enforce matching of lock/unlock
	#define FS_LOCK_MTD_SEMAPHORE   do {
	#define FS_UNLOCK_MTD_SEMAPHORE } while(0);
#endif // #if defined(UBNT_MIPS_ARxxxx) || defined(UBNT_MIPS_BCM4706) || defined(UBNT_MIPS_RTL838x)
#if defined(UBNT_MIPS_CN50xx) || defined(UBNT_ARM_BCM5334x) || defined(UBNT_ARM_BCM5341x) || defined(UBNT_ARM_BCM5616x) || defined(UBNT_MIPS_MT7621)
#define FS_LOCK   do {
#define FS_UNLOCK } while(0);
#elif defined(UBNT_MIPS_VSC7514) // #if defined(UBNT_MIPS_CN50xx) || defined(UBNT_ARM_BCM5334x) || defined(UBNT_ARM_BCM5341x)
	extern void vsc7514_spi_lock(void);
	extern void vsc7514_spi_unlock(void);
	#define FS_LOCK do { vsc7514_spi_lock();
	#define FS_UNLOCK vsc7514_spi_unlock(); } while(0);

#elif defined(UBNT_MIPS_RTL838x)
	#define FS_LOCK do { barrier();
	#define FS_UNLOCK barrier(); } while(0);

#else // #if defined(UBNT_MIPS_CN50xx) || defined(UBNT_ARM_BCM5334x) || defined(UBNT_ARM_BCM5341x) || defined(UBNT_ARM_BCM5616x) || defined(UBNT_MIPS_MT7621) || defined(UBNT_MIPS_RTL838x)
	/*
	If we are in kernel, we can prevent other modules from using SPI at the
	same time as us and garbling our answers.  We can also prevent other
	modules from reading flash while it is disabled in the case of MIPS.
	*/
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,0,0))
	#define FS_LOCK \
		do { \
			static DEFINE_SPINLOCK(lock); \
			unsigned long flags; \
			FS_LOCK_MTD_SEMAPHORE \
			spin_lock_irqsave(&lock, flags); \
			preempt_disable(); \
                        do {
	#define FS_UNLOCK \
                        } while(0); \
			preempt_enable_no_resched(); \
			spin_unlock_irqrestore(&lock, flags); \
			FS_UNLOCK_MTD_SEMAPHORE \
		} while(0);
#else
	#define FS_LOCK \
		do { \
			static spinlock_t lock = SPIN_LOCK_UNLOCKED; \
			unsigned long flags; \
			FS_LOCK_MTD_SEMAPHORE \
			spin_lock_irqsave(&lock, flags); \
			preempt_disable(); \
                        do {
	#define FS_UNLOCK \
                        } while(0); \
			preempt_enable_no_resched(); \
			spin_unlock_irqrestore(&lock, flags); \
			FS_UNLOCK_MTD_SEMAPHORE \
		} while(0);
#endif // #if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,0,0))
#endif // #if defined(UBNT_MIPS_CN50xx) || defined(UBNT_ARM_BCM5334x) || defined(UBNT_ARM_BCM5341x) || defined(UBNT_ARM_BCM5616x) || defined(UBNT_MIPS_MT7621) || defined(UBNT_MIPS_VSC7514) || defined(UBNT_MIPS_RTL838x)
#else // #ifdef __KERNEL__
#if defined(UBNT_MIPS_CN50xx) || defined(UBNT_MIPS_MT7621)
	#include <sys/file.h>
	#define FS_LOCK \
		do { \
			int lfd = open(fs_get_security_lockfile_name(), O_RDONLY); \
			if (lfd < 0) { \
				fs_low_level_failure(FS_FAILURE_fs_acquire_file_based_lock_1); \
			} \
			while (flock(lfd, LOCK_EX | LOCK_NB) != 0) { \
				sched_yield(); \
			} \
			do {
	#define FS_UNLOCK \
			} while(0); \
			flock(lfd, LOCK_UN); \
			close(lfd); \
		} while(0);
#else // #if defined(UBNT_MIPS_CN50xx) || defined(UBNT_MIPS_MT7621)
#if defined(UBNT_MIPS_BCM4706)
    #define FS_LOCK   do {
    #define FS_UNLOCK } while(0);
#else // #if defined(UBNT_MIPS_BCM4706)
	#define FS_LOCK \
		do { \
			int __spi_lock_rval = fs_acquire_file_based_lock(fs_get_security_lockfile_name(), _FS_LOCK_TIMEOUT_SECONDS, _FS_LOCK_TIMEOUT_BREAK_LOCK, _FS_LOCK_TIMEOUT_ERROR_VALUE); \
			if(0 != __spi_lock_rval) { \
				/* If we are not breaking locks or it isn't a "still locked", fail */ \
				if ((__spi_lock_rval != _FS_LOCK_TIMEOUT_ERROR_VALUE) || (!_FS_LOCK_TIMEOUT_BREAK_LOCK)) { \
					fs_low_level_failure(FS_FAILURE_fs_acquire_file_based_lock_2); \
				} \
				sched_yield(); /* Avoid priority inversion on deadlock? */ \
			} else { \
				struct sched_param old_sp; \
				struct sched_param new_sp; \
				int old_policy   = 0; \
				old_policy = sched_getscheduler(0); \
				sched_getparam( 0, &old_sp ); \
				new_sp.sched_priority = sched_get_priority_max(SCHED_FIFO); \
				sched_setscheduler(0,SCHED_FIFO,&new_sp); \
                                do {
	#define FS_UNLOCK  \
                                } while(0); \
				sched_setscheduler(0,old_policy,&old_sp); \
				if(0 != fs_release_file_based_lock(fs_get_security_lockfile_name())) { \
					fs_low_level_failure(FS_FAILURE_fs_release_file_based_lock_1); \
				} \
			} \
		} while(0);
#endif // #if defined(CONFIG_BCM947XX) && CONFIG_BCM947XX
#endif // #if defined(UBNT_MIPS_CN50xx) || defined(UBNT_MIPS_MT7621)
#endif // #ifdef __KERNEL__

#else /* !SECURITY_ENABLE_FS_LOCK */
#define FS_LOCK   do {
#define FS_UNLOCK } while(0);
#endif /* SECURITY_ENABLE_FS_LOCK */
