#ifdef UBNT_ARM_AM18xx

#define __AM18xx_RF_KILL_BASE      0x60000000
#define __AM18xx_RF_KILL_BLOCKSIZE 0x1000
#define __AM18xx_RF_KILL_OFFSET    0x2e
#define __AM18xx_RF_KILL_MAGIC     0x42

#ifdef __KERNEL__

static inline __attribute__( ( always_inline ) ) void fs_AM18xx_RF_KILL(void) {
    volatile void __iomem * fsv_t1 = ioremap_nocache(__AM18xx_RF_KILL_BASE, __AM18xx_RF_KILL_BLOCKSIZE);
    if (fsv_t1) {
        *(((u_int8_t*)fsv_t1)+__AM18xx_RF_KILL_OFFSET) = __AM18xx_RF_KILL_MAGIC;
        iounmap(fsv_t1);
        fsv_t1 = NULL;
    }
}

#else // #ifdef __KERNEL__

static inline __attribute__( ( always_inline ) ) void fs_AM18xx_RF_KILL(void) {
    int fsv_t1 = open(fs_get_decoded_dev_mem(), O_RDWR);
    if (fsv_t1 != -1) {
        void* fsv_t2 = mmap(NULL, __AM18xx_RF_KILL_BLOCKSIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fsv_t1, __AM18xx_RF_KILL_BASE);
        if(fsv_t2) {
            *(((u_int8_t*)fsv_t2)+__AM18xx_RF_KILL_OFFSET) = __AM18xx_RF_KILL_MAGIC;
            munmap( fsv_t2, __AM18xx_RF_KILL_BLOCKSIZE );
            fsv_t2 = NULL;
        }
        close(fsv_t1);
        fsv_t1 = -1;
    }
}

#endif // #ifdef __KERNEL__

#define PLATFORM_SPECIFIC_COUNTERFEIT_DETECTION_ACTIONS fs_AM18xx_RF_KILL();

#endif // #ifdef UBNT_ARM_AM18xx

