#ifdef UBNT_ARM64_AL324

#ifdef __KERNEL__

__FS_FUNCTION_PREFER_INLINE size_t fs_read_flash_uid_hw(u_int8_t* dest, size_t dest_len) {
	__FS_LOCAL_STATIC_OPTION size_t fsv_t1;
	return 0;
}

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_flash_type_id_hw(void) {
	__FS_LOCAL_STATIC_OPTION u_int32_t fsv_t1;
	return 0xffffffff;
}

#else /* #ifdef __KERNEL__ */

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_al324_flash_rdid(void) {

	int fd;
	u_int32_t id;
	char buf[16];

	id = 0xffffffff;
	memset(buf, 0, sizeof(buf));

	fd = open("/sys/class/mtd/mtd0/jedec_id", O_RDONLY);
	if (fd < 0)
		return id;

	if (read(fd, buf, sizeof(buf)) < 0) {
		close(fd);
		return id;
	}
	close(fd);
	id = strtol(buf, NULL, 16);

	return id;
}

/* OTP mode selection */
#define MTD_OTP_OFF		0
#define MTD_OTP_FACTORY		1
#define MTD_OTP_USER		2
#define MTD_MXIC_UID_SFDP_ADDR  0x8c
#define MTD_MXIC_UID_SIZE	13

/* Set OTP (One-Time Programmable) mode (factory vs. user) */
#define OTPSELECT		_IOR('M', 13, int)

__FS_FUNCTION_PREFER_INLINE size_t fs_al324_flash_read_uid(u_int8_t* dest, size_t dest_len) {
	uint8_t uid[MAX_FLASH_UID_SIZE];
	uint8_t temp[256];
	int fd, len, val;

	if (dest_len < MAX_FLASH_UID_SIZE)
		return 0;

	fd = open("/dev/mtd0", O_RDONLY);

	if (fd < 0)
		return 0;

	val = MTD_OTP_FACTORY;
	if (ioctl(fd, OTPSELECT, &val) < 0) {
		close(fd);
		return 0;
	}

	len = read(fd, temp, sizeof(temp));
	if (len < 0) {
		close(fd);
		return 0;
	}
	close(fd);

	memcpy(uid, &temp[MTD_MXIC_UID_SFDP_ADDR], MTD_MXIC_UID_SIZE);
	memcpy(dest, uid, MTD_MXIC_UID_SIZE);

	return MTD_MXIC_UID_SIZE;
}

__FS_FUNCTION_PREFER_INLINE size_t fs_read_flash_uid_hw(u_int8_t* dest, size_t dest_len) {
	__FS_LOCAL_STATIC_OPTION size_t fsv_t1;
	fsv_t1 = 0;

	if (dest_len < MAX_FLASH_UID_SIZE) {
		fs_low_level_failure(FS_FAILURE_fs_read_flash_uid_hw_1);
	}
	fsv_t1 = fs_al324_flash_read_uid(dest, dest_len);

	return fsv_t1;
}

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_flash_type_id_hw(void) {
	__FS_LOCAL_STATIC_OPTION u_int32_t fsv_t1;
	fsv_t1 = 0xffffffff;

	fsv_t1 = fs_al324_flash_rdid();

	return fsv_t1;
}

#endif /* #ifdef __KERNEL__ */

#endif /* #ifdef UBNT_ARM64_AL324 */
