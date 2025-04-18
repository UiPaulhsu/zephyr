#if SECURITY_ENABLE_FILE_IO_SUPPORT

#define MAX_INI_LENGTH 256
#define MAX_INI_KEY_LENGTH 128

#ifndef __KERNEL__
	__FS_FUNCTION_PREFER_INLINE void fs_read_file_into_buffer(u_int8_t* dest, size_t dest_len, const char* pathname, size_t* p_length) {
		__FS_LOCAL_STATIC_OPTION FILE*   fsv_t1;
		__FS_LOCAL_STATIC_OPTION ssize_t fsv_t2;

		fsv_t1 = NULL;
		fsv_t2 = 0;   

		if(dest == NULL) {
			fs_low_level_failure(FS_FAILURE_fs_read_file_into_buffer_1);
		}
		if(p_length == NULL) {
			fs_low_level_failure(FS_FAILURE_fs_read_file_into_buffer_2);
		}
		*p_length = 0;
		if(pathname == NULL) {
			fs_low_level_failure(FS_FAILURE_fs_read_file_into_buffer_3);
		}
		fsv_t1 = fs_fopen(pathname, "rb");
		if (fsv_t1 == NULL) {
			fs_low_level_failure(FS_FAILURE_fs_read_file_into_buffer_4);
		} else if(fseek(fsv_t1, 0, SEEK_END) != 0) {
			fs_low_level_failure(FS_FAILURE_fs_read_file_into_buffer_5);
		} else if((fsv_t2 = ftell(fsv_t1)) < 0) {
			fs_low_level_failure(FS_FAILURE_fs_read_file_into_buffer_6);
		} else if(fseek(fsv_t1, 0, SEEK_SET) != 0) {
			fs_low_level_failure(FS_FAILURE_fs_read_file_into_buffer_7);
		} else if(fsv_t2 > (ssize_t)dest_len) {
			fs_low_level_failure(FS_FAILURE_fs_read_file_into_buffer_8);
		} else if((ssize_t)(fread(dest, 1, fsv_t2, fsv_t1)) != fsv_t2) {
			fs_low_level_failure(FS_FAILURE_fs_read_file_into_buffer_9);
		}
		if(fsv_t1 != NULL) {
			fs_fclose(fsv_t1);
			fsv_t1 = NULL;
		}
		if(fsv_t2 > 0) {
			*p_length = (size_t)fsv_t2;
		}
	}

	__FS_FUNCTION_PREFER_INLINE int fs_save_buffer_to_file(const char* pathname, const u_int8_t* p_buffer, size_t fsa_length) {
		__FS_LOCAL_STATIC_OPTION int          fsv_t1;
		__FS_LOCAL_STATIC_OPTION FILE*        fsv_t2;

		fsv_t1 = 1;
		fsv_t2 = NULL;

		if (p_buffer == NULL) {
			fs_low_level_failure(FS_FAILURE_fs_save_buffer_to_file_1);
			fsv_t1 = 0;
		} else if (pathname == NULL) {
			fs_low_level_failure(FS_FAILURE_fs_save_buffer_to_file_2);
			fsv_t1 = 0;
		} else if(NULL == (fsv_t2 = fs_fopen(pathname, "w"))) {
			fs_low_level_failure(FS_FAILURE_fs_save_buffer_to_file_3);
			fsv_t1 = 0;
		} else if((ssize_t)(fwrite(p_buffer, 1, fsa_length, fsv_t2)) != (ssize_t)fsa_length) {
			fs_low_level_failure(FS_FAILURE_fs_save_buffer_to_file_4);
			fsv_t1 = 0;
		}
		if(fsv_t2 != NULL) {
			fs_fclose(fsv_t2);
			fsv_t2 = NULL;
		}
		return fsv_t1;
	}
#if SECURITY_ENABLE_FS_LOCK

	__FS_FUNCTION_PREFER_INLINE int fs_release_file_based_lock(const char* pathname) {
		unlink(pathname);
		return 0;
	}

	__FS_FUNCTION_PREFER_INLINE int fs_acquire_file_based_lock(const char* pathname, unsigned int timeout_seconds, int break_lock, int lock_timeout_error_value) {
		int result = 0;
		int fd = -1;
		time_t start   = 0;
		time_t timeout = 0;
		struct timeval now;
	
		// Determine when to timeout acquisition
		gettimeofday( &now, NULL );
		start = now.tv_sec + 1; /* same as rounding up */
		timeout = start + timeout_seconds;
		
		while( (fd = open(pathname, O_RDWR | O_CREAT | O_EXCL, 0600)) < 0) {
			if(errno != EEXIST) {
				fs_low_level_failure(FS_FAILURE_fs_acquire_file_based_lock_1);
			}
			sched_yield(); /* hit scheduler */
			/* If we starve for lock for more than _FS_LOCK_TIMEOUT_SECONDS there is a very high chance it is lost. */
			if(timeout_seconds) {
				gettimeofday( &now, NULL );
				if(now.tv_sec >= timeout) {
					result = lock_timeout_error_value;
					if (break_lock) {
						fs_debug_printf("Breaking lock.  It has been %d seconds.\n", (u_int32_t)(now.tv_sec - start));
						fs_release_file_based_lock(pathname);
					}
					break;
				}
			}
		}
		close(fd);
		fd = -1;
		return result;
	}
#endif // #if SECURITY_ENABLE_FS_LOCK

#else // #ifndef __KERNEL__

__FS_FUNCTION_PREFER_INLINE int fs_save_buffer_to_file(const char* pathname, const u_int8_t* p_buffer, size_t fsa_length) {
	__FS_LOCAL_STATIC_OPTION int          fsv_t1;
	__FS_LOCAL_STATIC_OPTION struct file* fsv_t2;
	__FS_LOCAL_STATIC_OPTION size_t       fsv_t3;
	fsv_t1 = 1;   
	fsv_t2 = NULL;	
	fsv_t3 = 0;          	
	if (p_buffer == NULL) {
		fs_low_level_failure(FS_FAILURE_fs_save_buffer_to_file_5);
		fsv_t1 = 0;
	} else if (pathname == NULL) {
		fs_low_level_failure(FS_FAILURE_fs_save_buffer_to_file_6);
		fsv_t1 = 0;
	} else if(NULL == (fsv_t2 = _fs_file_open(pathname, O_WRONLY|O_CREAT, 0777))) {
		fs_low_level_failure(FS_FAILURE_fs_save_buffer_to_file_7);
		fsv_t1 = 0;
	} else if((fsv_t3 = _fs_file_write(fsv_t2, p_buffer, fsa_length)) != fsa_length) {
		fs_low_level_failure(FS_FAILURE_fs_save_buffer_to_file_8);
		fsv_t1 = 0;
	}
	if(fsv_t2 != NULL) {
		_fs_file_close(fsv_t2);
		fsv_t2 = NULL;
	}
	return fsv_t1;
}

__FS_FUNCTION_PREFER_INLINE void fs_read_file_into_buffer(u_int8_t* dest, size_t dest_len, const char* pathname, size_t* p_length) {
        __FS_LOCAL_STATIC_OPTION struct file*   fsv_t1;
        __FS_LOCAL_STATIC_OPTION size_t         fsv_t2;
	
	fsv_t1  = NULL;
	fsv_t2  = 0;
        if(dest == NULL) {
            fs_low_level_failure(FS_FAILURE_fs_read_file_into_buffer_10);
        }
        if(p_length == NULL) {
            fs_low_level_failure(FS_FAILURE_fs_read_file_into_buffer_11);
        }
        *p_length = 0;
        if(pathname == NULL) {
            fs_low_level_failure(FS_FAILURE_fs_read_file_into_buffer_12);
        }
        fsv_t1 = _fs_file_open(pathname, O_RDONLY, 0);
        if (fsv_t1 == NULL) {
            fs_low_level_failure(FS_FAILURE_fs_read_file_into_buffer_13);
        } else if(0 == (fsv_t2 = _fs_file_read(fsv_t1, dest, dest_len))) {
            fs_low_level_failure(FS_FAILURE_fs_read_file_into_buffer_14);
        }
        if(fsv_t1 != NULL) {
            _fs_file_close(fsv_t1);
            fsv_t1 = NULL;
        }
        *p_length = (size_t)fsv_t2;
}

#endif // #ifndef __KERNEL__

#ifdef __KERNEL__
#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 22)
#include <linux/ctype.h>
static inline int strncasecmp(const char *s1, const char *s2, size_t n)
{
	int c1, c2;

	do {
		c1 = tolower(*s1++);
		c2 = tolower(*s2++);
	} while ((--n > 0) && c1 == c2 && c1 != 0);
	return c1 - c2;
}
#endif
#endif

#if SECURITY_ENABLE_INI_SUPPORT
__FS_FUNCTION_PREFER_INLINE int fs_read_ini_key(u_int8_t* dest, size_t dest_len, const char* filename, const char* key, int fail_if_missing) {
	__FS_LOCAL_STATIC_OPTION u_int32_t fsv_t1;
	__FS_LOCAL_STATIC_OPTION const size_t fsv_t2 = 4096;
	__FS_LOCAL_STATIC_OPTION size_t fsv_t3;
    __FS_LOCAL_STATIC_OPTION int fsv_t4;
    __FS_LOCAL_STATIC_OPTION u_int8_t* fsv_t5;
	__FS_LOCAL_STATIC_OPTION u_int8_t* fsv_t6;
    __FS_LOCAL_STATIC_OPTION size_t fsv_t7;

	fsv_t1 = 0;
	fsv_t3 = 0;
	fsv_t4 = 0;
	fsv_t5 = (u_int8_t*)fs_zalloc(fsv_t2);
	fsv_t6 = 0;
	fsv_t7 = 0;
	memset(dest, 0, dest_len);
	if (fsv_t5 != NULL) {
		memset(fsv_t5, 0, fsv_t2);
		fs_read_file_into_buffer(fsv_t5, fsv_t2, filename, &fsv_t3);
		if(fsv_t3 > 0) {
			fsv_t6 = fsv_t5;
			fsv_t1 = 0;
			while(fsv_t1 < fsv_t3) {
				/* End of line reached*/
				if (fsv_t5[fsv_t1] == '\r' || fsv_t5[fsv_t1] == '\n' || fsv_t1 == (fsv_t3-1)) {
					/* Strip trailing newlines/advance to next line */
					while((fsv_t1 < fsv_t3) && (fsv_t5[fsv_t1] == '\r' || fsv_t5[fsv_t1] == '\n')) {
						fsv_t5[fsv_t1++] = '\0';
					}
					/* Check for a match */
					fsv_t7 = fs_strnlen((const char *)key, MAX_INI_KEY_LENGTH);
					if(fsv_t7 > MAX_INI_KEY_LENGTH) {
						fs_low_level_failure(FS_FAILURE_fs_read_ini_key_4);
					}
					if (strncasecmp((const char *)fsv_t6, key, fsv_t7) == 0 && (*(fsv_t6 + fsv_t7) == '=')) {
						if(fs_strnlen((char*)(fsv_t6+fsv_t7+1), dest_len) == dest_len) {
							fs_low_level_failure(FS_FAILURE_fs_read_ini_key_5);
						}
						snprintf( (char*)dest, dest_len, "%s", (fsv_t6+fsv_t7+1) /* start + skip key and '=' */);
						if(fs_strnlen((char*)dest, dest_len) < dest_len) {
							fsv_t4 = 1;
							break;
						}
					}
					/* No match, advance to next line. */
					fsv_t6 = (fsv_t5 + fsv_t1);
				}
				fsv_t1++;
			}
			if(!fsv_t4) {
				if(fail_if_missing) {
					fs_debug_printf( "key: '%s'\n", key );
					fs_low_level_failure(FS_FAILURE_fs_read_ini_key_1);
				}
			}
		} else {
			if(fail_if_missing) {
				fs_debug_printf( "key: '%s'\n", key );
				fs_low_level_failure(FS_FAILURE_fs_read_ini_key_2);
			}
		}
	} else {
		fs_debug_printf( "key: '%s'\n", key );
		fs_low_level_failure(FS_FAILURE_fs_read_ini_key_3);
	}
	fs_safe_shred_and_free(&fsv_t5, fsv_t2);
	return fsv_t4;
}

#endif // #if SECURITY_ENABLE_INI_SUPPORT

#ifndef HAVE_MEMMOVE
#define HAVE_MEMMOVE 0
#endif // #ifndef HAVE_MEMMOVE

#if SECURITY_ENABLE_INI_SUPPORT          
__FS_FUNCTION_PREFER_INLINE void fs_strip_quotes(u_int8_t* buf, size_t buf_len) {
	__FS_LOCAL_STATIC_OPTION size_t fsv_t1;
#if !HAVE_MEMMOVE
	__FS_LOCAL_STATIC_OPTION u_int8_t fsv_t2[MAX_INI_LENGTH];
#endif // #if !HAVE_MEMMOVE
	buf[buf_len-1] = '\0';
	fsv_t1 = fs_strnlen( (char*)buf, buf_len );
	if(fsv_t1 >= buf_len) {
		fs_debug_printf( "unterminated input.\n" );	
		fs_low_level_failure(FS_FAILURE_fs_strip_quotes_1);
	}
	if(buf[0] == '"' && buf[fsv_t1-1] == '"') {
		buf[fsv_t1-1] = '\0';
#if !HAVE_MEMMOVE
		memcpy(fsv_t2, buf+1, fsv_t1-1);
		memcpy(buf, fsv_t2, fsv_t1-1);
#else // #if !HAVE_MEMMOVE
		memmove( buf, buf+1, fsv_t1-1 /* keep the null */);
#endif // #if !HAVE_MEMMOVE
	} 
}
#endif // #if SECURITY_ENABLE_INI_SUPPORT

#if SECURITY_ENABLE_INI_SUPPORT
__FS_FUNCTION_PREFER_INLINE int fs_has_ini_key(const char* filename, const char* key) 
{
	__FS_LOCAL_STATIC_OPTION u_int8_t fsv_t1[MAX_INI_LENGTH];
	return fs_read_ini_key( fsv_t1, sizeof fsv_t1, filename, key, 0 );
}
#endif // #if SECURITY_ENABLE_INI_SUPPORT

#if SECURITY_ENABLE_INI_SUPPORT

__FS_FUNCTION_PREFER_INLINE size_t fs_read_ini_hex_raw(u_int8_t* dest, size_t dest_len, const char* filename, const char* key, __ATTRIB_UNUSED size_t min_bytes_to_read, size_t max_bytes_to_read, int fail_if_missing) 
{
	__FS_LOCAL_STATIC_OPTION u_int8_t fsv_t1[MAX_INI_LENGTH];
	__FS_LOCAL_STATIC_OPTION char*    fsv_t2;
	__FS_LOCAL_STATIC_OPTION int      fsv_t3;
	__FS_LOCAL_STATIC_OPTION size_t   fsv_t4;

	fsv_t4 = 0;
	fsv_t3 = 0;
	fsv_t2 = 0;
	memset(fsv_t1,0,sizeof(fsv_t1));
	memset(dest,0,dest_len);

	if(!fs_read_ini_key( fsv_t1, sizeof fsv_t1, filename, key, fail_if_missing )) {
		fsv_t4 = 0;
		goto done;
	}
	if(fs_strnlen( (const char*)fsv_t1 , sizeof fsv_t1) == (sizeof fsv_t1-1)) {
		fs_low_level_failure(FS_FAILURE_fs_read_ini_hex_raw_3);
		fsv_t4 = 0;
		goto done;
	}
	fs_strip_quotes( fsv_t1, sizeof fsv_t1);
    fsv_t4 = fs_strnlen( (const char*)fsv_t1, sizeof fsv_t1);
#if SECURITY_ENABLE_TOUGHER_INI_VALIDATION
	if(fsv_t4 % 2) {
		fs_debug_printf("fs_read_ini_hex_raw key %s\n", key);
		fs_low_level_failure(FS_FAILURE_fs_read_ini_hex_raw_4);
		fsv_t4 = 0;
		goto done;
	}
#endif // #if SECURITY_ENABLE_TOUGHER_INI_VALIDATION
	fsv_t4 /= 2;
	if((max_bytes_to_read > 0) && (fsv_t4 > max_bytes_to_read)) {
#if SECURITY_ENABLE_TOUGHER_INI_VALIDATION
		// NB: used to just truncate, but that's not really right and could be exploited somehow (used to say )
		fs_debug_printf("fs_read_ini_hex_raw key %s\n", key);
		fs_low_level_failure(FS_FAILURE_fs_read_ini_hex_raw_5);
		fsv_t4 = 0;
		goto done;
#else
		fsv_t4 = max_bytes_to_read;
#endif // #if SECURITY_ENABLE_TOUGHER_INI_VALIDATION
	}
#if SECURITY_ENABLE_TOUGHER_INI_VALIDATION
	if((min_bytes_to_read > 0) && (fsv_t4 < min_bytes_to_read)) {
		fs_debug_printf("fs_read_ini_hex_raw key %s\n", key);
		fs_low_level_failure(FS_FAILURE_fs_read_ini_hex_raw_6);
		fsv_t4 = 0;
		goto done;
	}
#endif // #if SECURITY_ENABLE_TOUGHER_INI_VALIDATION
	if (fsv_t4 > dest_len) {
		fs_debug_printf("fs_read_ini_hex_raw key %s\n", key);
		fs_low_level_failure(FS_FAILURE_fs_read_ini_hex_raw_1);
		fsv_t4 = 0;
		goto done;
	}
	fsv_t3 = (fsv_t4 - 1);
	while(fsv_t3 >= 0) {
		dest[fsv_t3] = fs_strtoul((const char*)&fsv_t1[fsv_t3*2], &fsv_t2, 16);
		fsv_t1[(fsv_t3*2)] = 0;
		if (fsv_t2 == NULL || *fsv_t2 != '\0') { 
			fs_debug_printf("fs_read_ini_hex_raw key %s\n", key); 
			fs_low_level_failure(FS_FAILURE_fs_read_ini_hex_raw_2); 
		}
		fsv_t3--;
	}
done:
	return fsv_t4;
}

#endif // #if SECURITY_ENABLE_INI_SUPPORT

#if SECURITY_ENABLE_INI_SUPPORT

__FS_FUNCTION_PREFER_INLINE u_int32_t fs_read_ini_hex32(const char* filename, const char* key, int fail_if_missing, u_int32_t fallback) {
	__FS_LOCAL_STATIC_OPTION u_int32_t fsv_t1;
	__FS_LOCAL_STATIC_OPTION u_int8_t  fsv_t2[64];
	__FS_LOCAL_STATIC_OPTION char*     fsv_t3;
#if SECURITY_ENABLE_TOUGHER_INI_VALIDATION
	__FS_LOCAL_STATIC_OPTION size_t    fsv_t4;
#endif // #if SECURITY_ENABLE_TOUGHER_INI_VALIDATION

	fsv_t1 = fallback; 
	fsv_t3 = NULL;
#if SECURITY_ENABLE_TOUGHER_INI_VALIDATION
	fsv_t4 = 0;
#endif // #if SECURITY_ENABLE_TOUGHER_INI_VALIDATION
	memset(fsv_t2,0,sizeof(fsv_t2));
	
	if(fs_read_ini_key( fsv_t2, sizeof fsv_t2, filename, key, fail_if_missing )) {
		fs_strip_quotes(fsv_t2, sizeof fsv_t2);
#if SECURITY_ENABLE_TOUGHER_INI_VALIDATION
		fsv_t4 = fs_strnlen((const char *)fsv_t2, sizeof fsv_t2);
		if ((fsv_t4 % 2) || (fsv_t4 != (sizeof(u_int32_t) * 2)+2 || strncasecmp((const char*)fsv_t2,"0x",2))) {
			fs_low_level_failure(FS_FAILURE_fs_read_ini_hex32_2);
			fsv_t1 = 0;
		}
#endif // #if SECURITY_ENABLE_TOUGHER_INI_VALIDATION
		fsv_t1 = (u_int32_t)fs_strtoul( (const char*)fsv_t2, &fsv_t3, 0);
		if(fsv_t3 == NULL || *fsv_t3 != '\0') { 
			fs_low_level_failure(FS_FAILURE_fs_read_ini_hex32_1);
			fsv_t1 = 0;
		}
	}
	return fsv_t1;
}
#endif // #if SECURITY_ENABLE_INI_SUPPORT

#if SECURITY_ENABLE_INI_SUPPORT
__FS_FUNCTION_PREFER_INLINE u_int16_t fs_read_ini_hex16(const char* filename, const char* key, int fail_if_missing, u_int16_t fallback) {
	__FS_LOCAL_STATIC_OPTION u_int16_t fsv_t1;
	__FS_LOCAL_STATIC_OPTION u_int8_t  fsv_t2[64];
	__FS_LOCAL_STATIC_OPTION char*     fsv_t3;
#if SECURITY_ENABLE_TOUGHER_INI_VALIDATION
	__FS_LOCAL_STATIC_OPTION size_t    fsv_t4;
#endif // #if SECURITY_ENABLE_TOUGHER_INI_VALIDATION

	fsv_t1 = fallback; 
	fsv_t3 = NULL;
#if SECURITY_ENABLE_TOUGHER_INI_VALIDATION
	fsv_t4 = 0;
#endif // #if SECURITY_ENABLE_TOUGHER_INI_VALIDATION
	memset(fsv_t2,0,sizeof(fsv_t2));
	
	if(fs_read_ini_key( fsv_t2, sizeof fsv_t2, filename, key, fail_if_missing )) {
		fs_strip_quotes( fsv_t2, sizeof fsv_t2);
#if SECURITY_ENABLE_TOUGHER_INI_VALIDATION
		fsv_t4 = fs_strnlen((const char *)fsv_t2, sizeof fsv_t2);
		if ((fsv_t4 % 2) || (fsv_t4 != (sizeof(u_int16_t) * 2)+2 || strncasecmp((const char*)fsv_t2,"0x",2))) {
			fs_low_level_failure(FS_FAILURE_fs_read_ini_hex16_2);
			fsv_t1 = 0;
		}
#endif // #if SECURITY_ENABLE_TOUGHER_INI_VALIDATION
		fsv_t1 = (u_int16_t)fs_strtoul( (const char*)fsv_t2, &fsv_t3, 0);
		if(fsv_t3 == NULL || *fsv_t3 != '\0') { 
			fs_low_level_failure(FS_FAILURE_fs_read_ini_hex16_1);
			fsv_t1 = 0; // in case of 'nocrash' debug mode
		}
	}
	return fsv_t1;
}
#endif // #if SECURITY_ENABLE_INI_SUPPORT

#endif // #if SECURITY_ENABLE_FILE_IO_SUPPORT
