#ifdef UBNT_MIPS_RTL838x

#define FLASH_UID_LEN                             13
#define FLASH_ID_LEN                               4

#ifdef UNIFI_LAYOUT
#define FLASH_CMD_DEVNAME		"sflash"
#define FLASH_CMD_DEVNUM		200

/* SPI flash command */
#define SPI_FLASH_IOCTL_READ_ID		(0x01)
#define SPI_FLASH_IOCTL_READ_UID	(0x02)
#define SPI_FLASH_IOCTL_READ_SA		(0x03)

enum op_status {
	FLASH_OP_SUCCESS = 0,
	FLASH_OP_FAILED = 1,
};

struct spi_flash_cmd_opt {
	size_t len;
	void *data;
	enum op_status  result;
};

#ifdef __KERNEL__
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
extern int hal_get_spi_info(u_int32_t unit, u_int8_t * sf_uid, u_int8_t * sf_id);
#else
#endif // #if __KERNEL__

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_flash_uid_hw(u_int8_t *flash_uid, size_t dest_len) {
    uint8_t uid[64] = {0};
#ifdef __KERNEL__
    uint8_t id[64] = {0};
    if (dest_len < FLASH_UID_LEN)
        return 0;
    hal_get_spi_info(0, uid, id);
    memcpy(flash_uid, uid, FLASH_UID_LEN);
    return FLASH_UID_LEN;
#else
    struct spi_flash_cmd_opt spi_flash;
    int fd;

    spi_flash.data = uid;

    fd = open("/dev/" FLASH_CMD_DEVNAME, O_RDONLY);
    if (fd < 0)
         return 0;

    if (ioctl(fd, SPI_FLASH_IOCTL_READ_UID, &spi_flash) < 0) {
        close(fd);
        return 0;
    }

    close(fd);

    if (spi_flash.result)
        return 0;

    if (spi_flash.len > dest_len) {
        return 0;
    }
    memcpy(flash_uid, uid, spi_flash.len);
    return spi_flash.len;
#endif
}

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_flash_type_id_hw(void) {
    uint8_t id[64] = {0};
#ifdef __KERNEL__
    uint8_t uid[64] = {0};
    hal_get_spi_info(0, uid, id);
	return ((id[0] << 16) | (id[1] << 8) | id[2]);
#else
	struct spi_flash_cmd_opt spi_flash;
	int fd;

	spi_flash.data = id;

	fd = open("/dev/" FLASH_CMD_DEVNAME, O_RDONLY);
	if (fd < 0)
		return 0;

	if (ioctl(fd, SPI_FLASH_IOCTL_READ_ID, &spi_flash) < 0) {
		close(fd);
		return 0;
	}

	close(fd);

	if (spi_flash.result)
		return 0;

	return ((id[1] << 16) | (id[2] << 8) | id[3]);
#endif
}

#else

#include <netinet/in.h>
#include <sys/socket.h>

typedef struct rtdrv_spiCfg_s
{
    u_int32_t                      unit;
    u_int32_t                      addr;
    u_int32_t                      data;
    u_int8_t  *spi_uid;
    u_int8_t  *spi_id;
} rtdrv_spiCfg_t;

typedef struct rtdrv_msgHdr_s
{
    u_int32_t          ret_code;
} rtdrv_msgHdr_t;

/*
 * Symbol Definition
 */
#define RTDRV_BASE_CTL                          (64+1024+64+64+9000) /* 0x27E8 */
#define RTDRV_MODULE_SHIFT                      16
#define RTDRV_DEBUG_OFFSET                      ( 29 << RTDRV_MODULE_SHIFT )

enum rtdrv_debug_get_e
{
    RTDRV_DEBUG_EN_LOG_GET = (RTDRV_BASE_CTL + RTDRV_DEBUG_OFFSET),
    RTDRV_DEBUG_LOGLV_GET,
    RTDRV_DEBUG_LOGLVMASK_GET,
    RTDRV_DEBUG_LOGTYPE_GET,
    RTDRV_DEBUG_LOGFORMAT_GET,
    RTDRV_DEBUG_MODMASK_GET,
    RTDRV_DEBUG_LOGCFG_GET,
    RTDRV_DEBUG_MEM_READ,
    RTDRV_DEBUG_MIB_DBG_CNTR_GET,
    RTDRV_DEBUG_FLOWCTRL_PORT_USED_PAGE_CNT_INGRESS_GET,
    RTDRV_DEBUG_FLOWCTRL_PORT_USED_PAGE_CNT_EGRESS_GET,
    RTDRV_DEBUG_FLOWCTRL_PORT_QUEUE_USED_PAGE_CNT_GET,
    RTDRV_DEBUG_FLOWCTRL_SYSTEM_USED_PAGE_CNT_GET,
    RTDRV_DEBUG_FLOWCTRL_RPECT_QUEUE_CNTR_GET,
    RTDRV_DEBUG_WATCHDOG_CNT_GET,
    RTDRV_DEBUG_REPCTQ_EMPTY_GET,
    RTDRV_DEBUG_REPCTQ_STICK_ENABLE_GET,
    RTDRV_DEBUG_REPCTQ_FETCH_ENABLE_GET,
    RTDRV_DEBUG_SPI_RDSFDP_FLASH_UID_GET,
    RTDRV_DEBUG_SPI_FLASH_TYPE_GET,
};

#define GETSOCKOPT(optid, varptr, vartype, qty) rtusr_msg_getsockopt(optid, varptr, (sizeof(vartype) * qty))
#define RTUSR_MSG_VARPTR(_p)        (char *)_p + sizeof(rtdrv_msgHdr_t)

int
rtusr_msg_getsockopt(unsigned int optid, void *varptr, unsigned int size)
{
    unsigned int    ret;
    int             sockfd;
    int             len;
    char            *p;
    rtdrv_msgHdr_t  *pHdr;

    if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) == -1)
    {
        //RT_LOG(LOG_MAJOR_ERR, MOD_RTUSR, "socket error(%d) %s", errno, strerror(errno));
        return -1;
    }

    len = sizeof(rtdrv_msgHdr_t) + size;
    if ((p = malloc(len)) == NULL)
    {
        close(sockfd);
        return -1;
    }
    pHdr = (rtdrv_msgHdr_t *)p;
    memset(pHdr, 0, sizeof(rtdrv_msgHdr_t));
    memcpy(RTUSR_MSG_VARPTR(p), varptr, size);
    if ((ret = getsockopt(sockfd, IPPROTO_IP, optid, (void *)p, (socklen_t *)&len)) != 0)
    {
        //RT_LOG(LOG_MAJOR_ERR, MOD_RTUSR, "getsockopt error(%d) %s", errno, strerror(errno));
        free(p);
        close(sockfd);
        return -1;
    }
    close(sockfd);

    memcpy(varptr, RTUSR_MSG_VARPTR(p), size);
    ret = pHdr->ret_code;
    free(p);

    return ret;
} 

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_RTL838x_flash_uid_hw(u_int8_t *flash_uid) {
    rtdrv_spiCfg_t spi_cfg;
    u_int8_t sf_uid[FLASH_UID_LEN];
    u_int32_t k;

    memset(&spi_cfg, 0, sizeof(rtdrv_spiCfg_t));

    spi_cfg.unit = 0;
    spi_cfg.spi_uid= sf_uid;

#ifdef __KERNEL__
    hal_get_spi_info(0, sf_uid, flash_uid);
#else
    GETSOCKOPT(RTDRV_DEBUG_SPI_RDSFDP_FLASH_UID_GET, &spi_cfg, rtdrv_spiCfg_t, 1);
#endif

    fs_debug_printf_off("Flash UID : ");	
    for(k =0; k< FLASH_UID_LEN; k++)
        fs_debug_printf_off("0x%02x ", sf_uid[k]);	

    fs_debug_printf_off("\n");

    memcpy(flash_uid, sf_uid, FLASH_UID_LEN);

    return 0;
}


__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_flash_uid_hw(u_int8_t *flash_uid, size_t dest_len) {
    rtdrv_spiCfg_t spi_cfg;
    u_int8_t sf_uid[FLASH_UID_LEN];
    u_int32_t k;

    memset(&spi_cfg, 0, sizeof(rtdrv_spiCfg_t));

    spi_cfg.unit = 0;
    spi_cfg.spi_uid= sf_uid;

#ifdef __KERNEL__
    hal_get_spi_info(spi_cfg.unit, spi_cfg.spi_uid, spi_cfg.spi_id);
#else
    GETSOCKOPT(RTDRV_DEBUG_SPI_RDSFDP_FLASH_UID_GET, &spi_cfg, rtdrv_spiCfg_t, 1);
#endif
    fs_debug_printf_off("Flash UID : ");	
    for(k =0; k< FLASH_UID_LEN; k++)
        fs_debug_printf_off("0x%02x ", sf_uid[k]);	

    fs_debug_printf_off("\n");

    memcpy(flash_uid, sf_uid, FLASH_UID_LEN);

    dest_len = FLASH_UID_LEN;

    return dest_len;
}

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_flash_type_id_hw(void) {
    rtdrv_spiCfg_t spi_cfg;
    u_int8_t sf_id[4];
    u_int32_t k, flash_type_id;

    memset(&spi_cfg, 0, sizeof(rtdrv_spiCfg_t));

    spi_cfg.unit = 0;
    spi_cfg.spi_id= sf_id;

#ifdef __KERNEL__
    hal_get_spi_info(spi_cfg.unit, spi_cfg.spi_uid, spi_cfg.spi_id);
#else
    GETSOCKOPT(RTDRV_DEBUG_SPI_RDSFDP_FLASH_UID_GET, &spi_cfg, rtdrv_spiCfg_t, 1);
#endif

    fs_debug_printf_off("Flash Type ID : ");	
    for(k =0; k< FLASH_ID_LEN; k++)
        fs_debug_printf_off("0x%02x ", sf_id[k]);	

    fs_debug_printf_off("\n");

    memcpy(&flash_type_id, sf_id, FLASH_ID_LEN);

    flash_type_id =  (flash_type_id >> 8) & 0xffffff;

    fs_debug_printf_off("0x%x ", flash_type_id);

    return flash_type_id;
}

#endif // #ifdef UNIFI_LAYOUT
#endif // #ifdef UBNT_MIPS_RTL838x
