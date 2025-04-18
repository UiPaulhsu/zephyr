#if SECURITY_ENABLE_FILE_IO_SUPPORT
#ifndef __KERNEL__
#if SECURITY_ENABLE_FD_LEAK_DEBUG
	static int fs_cntr = 0;
	__FS_FUNCTION_PREFER_INLINE int fs_open(__const char *__file, int __oflag) {
		int result = open(__file, __oflag);
		if(-1 != result) {
			fs_cntr++;
		}
		fs_debug_printf("fs_open(\"%s\",0x%08x) = %d [%d]\n", __file, __oflag, result, fs_cntr);
		return result;
	}
	__FS_FUNCTION_PREFER_INLINE int fs_close(int __fd) {
		int result = close(__fd);
		if(__fd != -1 && result == 0) {
			fs_cntr--;
		}
		fs_debug_printf("fs_close(%d) = %d.  [%d]\n", __fd, result, fs_cntr);
		return result;
	}
	__FS_FUNCTION_PREFER_INLINE FILE *fs_fopen(const char *path, const char *mode) {
		FILE* p_result = fopen(path,mode);
		if(p_result) {
			fs_cntr++;
		}
		fs_debug_printf("fs_fopen(\"%s\",\"%s\") = %p [%d]\n", path, mode, (void*)p_result, fs_cntr);
		return p_result;
	}
	__FS_FUNCTION_PREFER_INLINE int fs_fclose(FILE *fp) {
		int result = fclose(fp);
		if(fp) {
			fs_cntr--;
		}
		fs_debug_printf("fs_fclose(%p) = %d.  [%d]\n", (void*)fp, result, fs_cntr);
		return result;
	}
#else
	#undef fs_fopen
	#undef fs_fclose
	#undef fs_open
	#undef fs_close
	#define fs_fopen  fopen
	#define fs_fclose fclose
	#define fs_open   open
	#define fs_close  close
#endif
	__FS_FUNCTION_PREFER_INLINE int fs_file_exists(const char* fsa_pathname) {
		__FS_LOCAL_STATIC_OPTION int fsv_t1;
		__FS_LOCAL_STATIC_OPTION FILE* fsv_t2;
		
		fsv_t1 = 0;
		fsv_t2 = fs_fopen(fsa_pathname, "rb");
		if(fsv_t2 != NULL) {
			fsv_t1 = 1;
			fs_fclose(fsv_t2);
			fsv_t2 = NULL;
		}
		return fsv_t1;
	}

	__FS_FUNCTION_PREFER_INLINE void fs_low_level_read_file_into_buffer(u_int8_t* dest, size_t dest_len, const char* fsa_pathname, size_t* p_length) {
		__FS_LOCAL_STATIC_OPTION FILE*   fsv_t1;
		__FS_LOCAL_STATIC_OPTION ssize_t fsv_t2;

		fsv_t1 = NULL;
		fsv_t2 = 0;   

		if(dest == NULL) {
			return;
		}
		if(p_length == NULL) {
			return;
		}
		*p_length = 0;
		if(fsa_pathname == NULL) {
			return;
		}
		fsv_t1 = fs_fopen(fsa_pathname, "rb");
		if (fsv_t1 == NULL) {
			return;
		} else if(fseek(fsv_t1, 0, SEEK_END) != 0) {
			fs_fclose(fsv_t1);
			return;
		} else if((fsv_t2 = ftell(fsv_t1)) < 0) {
			fs_fclose(fsv_t1);
			return;
		} else if(fseek(fsv_t1, 0, SEEK_SET) != 0) {
			fs_fclose(fsv_t1);
			return;
		} else if(fsv_t2 > (ssize_t)dest_len) {
			fs_fclose(fsv_t1);
			return;
		} else if((ssize_t)fread(dest, 1, fsv_t2, fsv_t1) != fsv_t2) {
			fs_fclose(fsv_t1);
			return;
		}
		if(fsv_t1 != NULL) {
			fs_fclose(fsv_t1);
			fsv_t1 = NULL;
		}
		if(fsv_t2 > 0) {
			*p_length = (size_t)fsv_t2;
		}
	}

	__FS_FUNCTION_PREFER_INLINE int fs_low_level_save_buffer_to_file(const char* fsa_pathname, const u_int8_t* fsa_p_buffer, size_t fsa_length) {
		__FS_LOCAL_STATIC_OPTION int          fsv_t1;
		__FS_LOCAL_STATIC_OPTION FILE*        fsv_t2;

		fsv_t1        = 1;
		fsv_t2        = NULL;
	
		if (fsa_p_buffer == NULL) {
			fsv_t1 = 0;
		} else if (fsa_pathname == NULL) {
			fsv_t1 = 0;
		} else if(NULL == (fsv_t2 = fs_fopen(fsa_pathname, "w"))) {
			fsv_t1 = 0;
		} else if(fwrite(fsa_p_buffer, 1, fsa_length, fsv_t2) != fsa_length) {
			fsv_t1 = 0;
		}
		if(fsv_t2 != NULL) {
			fs_fclose(fsv_t2);
			fsv_t2 = NULL;
		}
		return fsv_t1;
	}

#else // #ifndef __KERNEL__

__FS_FUNCTION_PREFER_INLINE struct file* _fs_file_open(const char* path, int flags, int rights) {
	__FS_LOCAL_STATIC_OPTION struct file* fsv_t1 = NULL;
	__FS_LOCAL_STATIC_OPTION mm_segment_t fsv_t2;
	__FS_LOCAL_STATIC_OPTION int fsv_t3 = 0;
	
	fsv_t1 = NULL;
	fsv_t3 = 0;
	fsv_t2 = get_fs();
	set_fs(KERNEL_DS);//set_fs(get_ds());
	fsv_t1 = filp_open(path, flags, rights);
	set_fs(fsv_t2);
	if(IS_ERR(fsv_t1)) {
		fsv_t3 = PTR_ERR(fsv_t1);
		return NULL;
	}
	return fsv_t1;
}

__FS_FUNCTION_PREFER_INLINE void _fs_file_close(struct file* file) {
	filp_close(file, NULL);
}

__FS_FUNCTION_PREFER_INLINE int _fs_file_read(struct file* file, unsigned char* data, unsigned int size) {
	__FS_LOCAL_STATIC_OPTION char __user * fsv_t1;
	__FS_LOCAL_STATIC_OPTION mm_segment_t fsv_t2;
	__FS_LOCAL_STATIC_OPTION int fsv_t3;

	fsv_t1 = ( char __force __user *)data;
	fsv_t3 = 0;
	fsv_t2 = get_fs();
	set_fs(KERNEL_DS); //set_fs(get_ds());
	fsv_t3 = vfs_read(file, fsv_t1, size, &file->f_pos);
	set_fs(fsv_t2);
	return fsv_t3;
}

__FS_FUNCTION_PREFER_INLINE int _fs_file_write(struct file* file, const unsigned char* data, unsigned int size) {
	__FS_LOCAL_STATIC_OPTION char __user * fsv_t1;
	__FS_LOCAL_STATIC_OPTION mm_segment_t fsv_t2;
	__FS_LOCAL_STATIC_OPTION int fsv_t3;

	fsv_t1 = ( char __force __user *)data;
	fsv_t3 = 0;
	fsv_t2 = get_fs();
	set_fs(KERNEL_DS); //set_fs(get_ds());
	fsv_t3 = vfs_write(file, fsv_t1, size, &file->f_pos);
	set_fs(fsv_t2);
	return fsv_t3;
}

__FS_FUNCTION_PREFER_INLINE int fs_file_exists(const char* fsa_pathname) {
	__FS_LOCAL_STATIC_OPTION int fsv_t1;
	__FS_LOCAL_STATIC_OPTION struct file* fsv_t2;

	fsv_t1 = 0;
	fsv_t2 = _fs_file_open(fsa_pathname, O_RDONLY, 0);
	if(fsv_t2 > 0) {
		fsv_t1 = 1;
		_fs_file_close(fsv_t2);
		fsv_t2 = NULL;
	}
	return fsv_t1;
}

__FS_FUNCTION_PREFER_INLINE int fs_low_level_save_buffer_to_file(const char* fsa_pathname, const u_int8_t* fsa_p_buffer, size_t fsa_length) {
	__FS_LOCAL_STATIC_OPTION int          fsv_t1;
	__FS_LOCAL_STATIC_OPTION struct file* fsv_t2;
	__FS_LOCAL_STATIC_OPTION size_t       fsv_t3;
	fsv_t1 = 1;
	fsv_t2 = NULL;
	fsv_t3 = 0;

	if (fsa_p_buffer == NULL) {
		fsv_t1 = 0;
	} else if (fsa_pathname == NULL) {
		fsv_t1 = 0;
	} else if(NULL == (fsv_t2 = _fs_file_open(fsa_pathname, O_WRONLY|O_CREAT, 0777))) {
		fsv_t1 = 0;
	} else if((fsv_t3 = _fs_file_write(fsv_t2, fsa_p_buffer, fsa_length)) != fsa_length) {
		fsv_t1 = 0;
	}
	if(fsv_t2 != NULL) {
		_fs_file_close(fsv_t2);
		fsv_t2 = NULL;
	}
	return fsv_t1;
}

__FS_FUNCTION_PREFER_INLINE void fs_low_level_read_file_into_buffer(u_int8_t* dest, size_t dest_len, const char* fsa_pathname, size_t* p_length) {
        __FS_LOCAL_STATIC_OPTION struct file*   fsv_t1;
        __FS_LOCAL_STATIC_OPTION size_t         fsv_t2;
	fsv_t1      = NULL;
	fsv_t2  = 0;
        if(p_length == NULL) {
		return;
        }
        *p_length = 0;
	if(dest == NULL) {
	    return;
	}
        if(fsa_pathname == NULL) {
            return;
        }
        fsv_t1 = _fs_file_open(fsa_pathname, O_RDONLY, 0);
        if (fsv_t1 == NULL) {
		// fail
        } else if(0 == (fsv_t2 = _fs_file_read(fsv_t1, dest, dest_len))) {
		// fail
        }
        if(fsv_t1 != NULL) {
            _fs_file_close(fsv_t1);
            fsv_t1 = NULL;
        }
        *p_length = (size_t)fsv_t2;
}

#endif // #ifndef __KERNEL__
#endif // #if SECURITY_ENABLE_FILE_IO_SUPPORT
