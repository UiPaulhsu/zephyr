#if (defined(UBNT_NVRx64) && UBNT_NVRx64)

#include <netinet/in.h>

#define NVR_EEPROM_DISK "/dev/sda"
#define NVR_EEPROM_OFFSET (1024 * 1024)
#define NVR_EEPROM_OFFSET2 (512 * 1024)
#define NVR_EEPROM_SIZE 0x10000

#define NVR_EEPROM_PDATA_OFFSET 0x1000
#define NVR_EEPROM_MAGIC 0x55424e54

__FS_FUNCTION_PREFER_INLINE uint8_t*
eeprom_mmap(int fd, unsigned int offset) {
	uint8_t* mem;
	uint32_t* magic = 0;

	mem = mmap(0, NVR_EEPROM_SIZE, PROT_READ, MAP_SHARED, fd, offset);
	if (mem == MAP_FAILED) {
		return MAP_FAILED;
	}

	magic = (uint32_t*)(mem + NVR_EEPROM_PDATA_OFFSET);
	if (ntohl(*magic) != NVR_EEPROM_MAGIC) {
		munmap(mem, NVR_EEPROM_SIZE);
		return MAP_FAILED;
	}

       return mem;
}


__FS_FUNCTION_PREFER_INLINE void fs_read_config(__ATTRIB_UNUSED void* dest_buffer, __ATTRIB_UNUSED size_t dest_buffer_len, __ATTRIB_UNUSED uintptr_t offset, __ATTRIB_UNUSED size_t bytes_to_copy) {
        //    Read "EEPROM" data starting at offset
        //    Write into dest_buffer
        //    Write MIN(dest_buffer_len, bytes_to_copy) bytes into dest_buffer
	int fd;
	uint8_t* mem;

	if (offset > NVR_EEPROM_SIZE)
		return;

	if ((offset + bytes_to_copy) > NVR_EEPROM_SIZE)
		bytes_to_copy = NVR_EEPROM_SIZE - offset;

	fd = open(NVR_EEPROM_DISK, O_RDONLY);
	if (fd < 0)
		return;

	mem = eeprom_mmap(fd, NVR_EEPROM_OFFSET2);
	if (mem == MAP_FAILED) {
		mem = eeprom_mmap(fd, NVR_EEPROM_OFFSET);
	}

	if (mem == MAP_FAILED) {
		close(fd);
		return;
	}

	memcpy(dest_buffer, mem + offset, (bytes_to_copy < dest_buffer_len) ? bytes_to_copy : dest_buffer_len);
	munmap(mem, NVR_EEPROM_SIZE);
	close(fd);
}

#ifdef HELPER_BUILD
__FS_FUNCTION_PREFER_INLINE void fs_write_config(__ATTRIB_UNUSED uintptr_t offset, __ATTRIB_UNUSED void* src_buffer, __ATTRIB_UNUSED size_t bytes_to_copy) {
        //    Read data from src_buffer
        //    Write into "EEPROM" data starting at offset
        //    Write MIN(0x10000-offset, bytes_to_copy) bytes into EEPROM
	int fd;
	uint8_t* mem;
	if (offset > NVR_EEPROM_SIZE)
		return;

	if ((offset + bytes_to_copy) > NVR_EEPROM_SIZE)
		bytes_to_copy = NVR_EEPROM_SIZE - offset;

	fd = open(NVR_EEPROM_DISK, O_RDWR);
	if (fd < 0)
		return;

	mem = mmap(0, NVR_EEPROM_SIZE, PROT_WRITE, MAP_SHARED, fd, NVR_EEPROM_OFFSET2);
	if (mem == MAP_FAILED) {
		close(fd);
		return;
	}
	memcpy(mem + offset, src_buffer, bytes_to_copy);
	msync(mem, NVR_EEPROM_SIZE, MS_SYNC);
	munmap(mem, NVR_EEPROM_SIZE);
	close(fd);
}
#endif // #ifdef HELPER_BUILD

#endif // #if (defined(UBNT_NVRx64) && UBNT_NVRx64)
