__FS_LOCAL_STATIC_OPTION u_int64_t fs_ror64c(u_int64_t fsa_x, u_int64_t fsa_y) {
    return ( ((((fsa_x)&0xFFFFFFFFFFFFFFFFULL)>>((u_int64_t)(fsa_y)&63ULL)) | \
      ((fsa_x)<<((u_int64_t)(64-((fsa_y)&63ULL))))) & 0xFFFFFFFFFFFFFFFFULL);
}

__FS_FUNCTION_PREFER_INLINE int fs_sha512_compress(u_int64_t* p_state, unsigned char *buf) {
	__FS_LOCAL_STATIC_OPTION u_int64_t fsv_t0;
	__FS_LOCAL_STATIC_OPTION u_int64_t fsv_t1;
	__FS_LOCAL_STATIC_OPTION u_int64_t fsv_t2[80];
	__FS_LOCAL_STATIC_OPTION u_int64_t fsv_t3[8];
	__FS_LOCAL_STATIC_OPTION const u_int64_t fsv_t4[80] = {
	      0x428a2f98d728ae22ULL, 0x7137449123ef65cdULL, 
	      0xb5c0fbcfec4d3b2fULL, 0xe9b5dba58189dbbcULL,
	      0x3956c25bf348b538ULL, 0x59f111f1b605d019ULL, 
	      0x923f82a4af194f9bULL, 0xab1c5ed5da6d8118ULL,
	      0xd807aa98a3030242ULL, 0x12835b0145706fbeULL, 
	      0x243185be4ee4b28cULL, 0x550c7dc3d5ffb4e2ULL,
	      0x72be5d74f27b896fULL, 0x80deb1fe3b1696b1ULL, 
	      0x9bdc06a725c71235ULL, 0xc19bf174cf692694ULL,
	      0xe49b69c19ef14ad2ULL, 0xefbe4786384f25e3ULL, 
	      0x0fc19dc68b8cd5b5ULL, 0x240ca1cc77ac9c65ULL,
	      0x2de92c6f592b0275ULL, 0x4a7484aa6ea6e483ULL, 
	      0x5cb0a9dcbd41fbd4ULL, 0x76f988da831153b5ULL,
	      0x983e5152ee66dfabULL, 0xa831c66d2db43210ULL, 
	      0xb00327c898fb213fULL, 0xbf597fc7beef0ee4ULL,
	      0xc6e00bf33da88fc2ULL, 0xd5a79147930aa725ULL, 
	      0x06ca6351e003826fULL, 0x142929670a0e6e70ULL,
	      0x27b70a8546d22ffcULL, 0x2e1b21385c26c926ULL, 
	      0x4d2c6dfc5ac42aedULL, 0x53380d139d95b3dfULL,
	      0x650a73548baf63deULL, 0x766a0abb3c77b2a8ULL, 
	      0x81c2c92e47edaee6ULL, 0x92722c851482353bULL,
	      0xa2bfe8a14cf10364ULL, 0xa81a664bbc423001ULL,
	      0xc24b8b70d0f89791ULL, 0xc76c51a30654be30ULL,
	      0xd192e819d6ef5218ULL, 0xd69906245565a910ULL, 
	      0xf40e35855771202aULL, 0x106aa07032bbd1b8ULL,
	      0x19a4c116b8d2d0c8ULL, 0x1e376c085141ab53ULL, 
	      0x2748774cdf8eeb99ULL, 0x34b0bcb5e19b48a8ULL,
	      0x391c0cb3c5c95a63ULL, 0x4ed8aa4ae3418acbULL, 
	      0x5b9cca4f7763e373ULL, 0x682e6ff3d6b2b8a3ULL,
	      0x748f82ee5defb2fcULL, 0x78a5636f43172f60ULL, 
	      0x84c87814a1f0ab72ULL, 0x8cc702081a6439ecULL,
	      0x90befffa23631e28ULL, 0xa4506cebde82bde9ULL, 
	      0xbef9a3f7b2c67915ULL, 0xc67178f2e372532bULL,
	      0xca273eceea26619cULL, 0xd186b8c721c0c207ULL, 
	      0xeada7dd6cde0eb1eULL, 0xf57d4f7fee6ed178ULL,
	      0x06f067aa72176fbaULL, 0x0a637dc5a2c898a6ULL, 
	      0x113f9804bef90daeULL, 0x1b710b35131c471bULL,
	      0x28db77f523047d84ULL, 0x32caab7b40c72493ULL, 
	      0x3c9ebe0a15c9bebcULL, 0x431d67c49c100d4cULL,
	      0x4cc5d4becb3e42b6ULL, 0x597f299cfc657e2aULL, 
	      0x5fcb6fab3ad6faecULL, 0x6c44198c4a475817ULL
	};
	__FS_LOCAL_STATIC_OPTION int fsv_t5;
	__FS_LOCAL_STATIC_OPTION int fsv_t6;

	fsv_t5 = 0;
	fsv_t6 = 0;

	/* copy state into fs_ror64c */
	for(fsv_t6 = 0; fsv_t6 < 8; fsv_t6++) {
		fsv_t3[fsv_t6] = p_state[fsv_t6];
	}

	/* copy the state into 1024-bits into W[0..15] */
	for(fsv_t6 = 0; fsv_t6 < 16; fsv_t6++) {
		FS_LOAD64H(fsv_t2[fsv_t6], buf + (8*fsv_t6));
	}

	/* fill W[16..79] */
	for(fsv_t6 = 16; fsv_t6 < 80; fsv_t6++) {
		fsv_t2[fsv_t6] = (fs_ror64c(fsv_t2[fsv_t6 - 2], 19) ^ fs_ror64c(fsv_t2[fsv_t6 - 2], 61) ^ (((fsv_t2[fsv_t6 - 2])&0xFFFFFFFFFFFFFFFFULL)>>((u_int64_t) 6))) + fsv_t2[fsv_t6 - 7] + (fs_ror64c(fsv_t2[fsv_t6 - 15], 1) ^ fs_ror64c(fsv_t2[fsv_t6 - 15], 8) ^ (((fsv_t2[fsv_t6 - 15])&0xFFFFFFFFFFFFFFFFULL)>>((u_int64_t) 7))) + fsv_t2[fsv_t6 - 16];
	}        

	/* Compress */
	for(fsv_t6 = 0; fsv_t6 < 80; fsv_t6++) {
		fsv_t0 = fsv_t3[7] + (fs_ror64c(fsv_t3[4], 14) ^ fs_ror64c(fsv_t3[4], 18) ^ fs_ror64c(fsv_t3[4], 41)) + (fsv_t3[6] ^ (fsv_t3[4] & (fsv_t3[5] ^ fsv_t3[6]))) + fsv_t4[fsv_t6] + /* K */ fsv_t2[fsv_t6];
		fsv_t1 = (fs_ror64c(fsv_t3[0], 28) ^ fs_ror64c(fsv_t3[0], 34) ^ fs_ror64c(fsv_t3[0], 39)) + (((fsv_t3[0] | fsv_t3[1]) & fsv_t3[2]) | (fsv_t3[0] & fsv_t3[1]));
		fsv_t3[7] = fsv_t3[6];
		fsv_t3[6] = fsv_t3[5];
		fsv_t3[5] = fsv_t3[4];
		fsv_t3[4] = fsv_t3[3] + fsv_t0;
		fsv_t3[3] = fsv_t3[2];
		fsv_t3[2] = fsv_t3[1];
		fsv_t3[1] = fsv_t3[0];
		fsv_t3[0] = fsv_t0 + fsv_t1;
	}

	/* feedback */
	for(fsv_t6 = 0; fsv_t6 < 8; fsv_t6++) {
		p_state[fsv_t6] = p_state[fsv_t6] + fsv_t3[fsv_t6];
	}

	return fsv_t5;
}

typedef struct fs_sha512_data {
	u_int64_t     state[8];
	unsigned long n;
	int           i;
	u_int64_t     length;
	u_int32_t     curlen;
	u_int8_t      buf[256];
} fs_sha512_data_t;

__FS_FUNCTION_PREFER_INLINE int fs_sha512(const unsigned char *in, unsigned long length, unsigned char *out) {
	__FS_LOCAL_STATIC_OPTION int fsv_t1 = 0;
	__FS_LOCAL_STATIC_OPTION fs_sha512_data_t* fsv_t2;
	fsv_t1 = 0;
	fsv_t2 = (fs_sha512_data_t*)fs_zalloc(sizeof(fs_sha512_data_t));
	if(NULL == fsv_t2) {
		fsv_t1 = 1;
		goto done;
	}
	fsv_t2->state[0] = 0x6a09e667f3bcc908ULL;
	fsv_t2->state[1] = 0xbb67ae8584caa73bULL;
	fsv_t2->state[2] = 0x3c6ef372fe94f82bULL;
	fsv_t2->state[3] = 0xa54ff53a5f1d36f1ULL;
	fsv_t2->state[4] = 0x510e527fade682d1ULL;
	fsv_t2->state[5] = 0x9b05688c2b3e6c1fULL;
	fsv_t2->state[6] = 0x1f83d9abfb41bd6bULL;
	fsv_t2->state[7] = 0x5be0cd19137e2179ULL;
	while(length > 0) {
		if(fsv_t2->curlen == 0 && length >= 128) {
			fsv_t1 = fs_sha512_compress (fsv_t2->state, (unsigned char *)in);
			if(fsv_t1) {
				goto done;
			}
			fsv_t2->length += 128 * 8;
			in             += 128;
			length          -= 128;
		} else {
			fsv_t2->n = length < (128 - fsv_t2->curlen) ? length : (128 - fsv_t2->curlen);
			memcpy(fsv_t2->buf + fsv_t2->curlen, in, (size_t)fsv_t2->n);
			fsv_t2->curlen += fsv_t2->n;
			in             += fsv_t2->n;
			length          -= fsv_t2->n;
			if(fsv_t2->curlen == 128) {
				fsv_t1 = fs_sha512_compress (fsv_t2->state, fsv_t2->buf);
				if(fsv_t1) {
					goto done;
				}
				fsv_t2->length += 8*128;
				fsv_t2->curlen = 0;
			}
		}
	}
	fsv_t2->length += fsv_t2->curlen * 8ULL;
	fsv_t2->buf[fsv_t2->curlen++] = (unsigned char)0x80;
	if(fsv_t2->curlen > 112) {
		while(fsv_t2->curlen < 128) {
			fsv_t2->buf[fsv_t2->curlen++] = (unsigned char)0;
		}
		fs_sha512_compress(fsv_t2->state, fsv_t2->buf);
		fsv_t2->curlen = 0;
	}
	while(fsv_t2->curlen < 120) {
		fsv_t2->buf[fsv_t2->curlen++] = (unsigned char)0;
	}
	FS_STORE64H(fsv_t2->length, fsv_t2->buf+120);
	fs_sha512_compress(fsv_t2->state, fsv_t2->buf);
	for(fsv_t2->i = 0; fsv_t2->i < 8; fsv_t2->i++) {
		FS_STORE64H(fsv_t2->state[fsv_t2->i], out+(8*fsv_t2->i));
	}
	memset(&fsv_t2->state, 0, sizeof(fsv_t2->state));
done:
	fs_safe_shred_and_free(&fsv_t2,sizeof(*fsv_t2));
	return fsv_t1;
}

#if SECURITY_LOW_MEMORY
typedef void (*fs_read_fn_t)(void* fsa_dest, size_t fsa_dest_len, uintptr_t fsa_address, size_t fsa_length);

__FS_FUNCTION_PREFER_INLINE int fs_sha512_incremental(fs_read_fn_t reader_fn, uintptr_t offset, unsigned long length, unsigned char *out) {
	__FS_LOCAL_STATIC_OPTION int fsv_t1 = 0;
	__FS_LOCAL_STATIC_OPTION fs_sha512_data_t* fsv_t2;
    __FS_LOCAL_STATIC_OPTION u_int8_t fsv_t3[128]; // 512 bits
    __FS_LOCAL_STATIC_OPTION uintptr_t fsv_t4;
    
	fsv_t1 = 0;
    fsv_t4 = offset;
	fsv_t2 = (fs_sha512_data_t*)fs_zalloc(sizeof(fs_sha512_data_t));
	if(NULL == fsv_t2) {
		fsv_t1 = 1;
		goto done;
	}
	fsv_t2->state[0] = 0x6a09e667f3bcc908ULL;
	fsv_t2->state[1] = 0xbb67ae8584caa73bULL;
	fsv_t2->state[2] = 0x3c6ef372fe94f82bULL;
	fsv_t2->state[3] = 0xa54ff53a5f1d36f1ULL;
	fsv_t2->state[4] = 0x510e527fade682d1ULL;
	fsv_t2->state[5] = 0x9b05688c2b3e6c1fULL;
	fsv_t2->state[6] = 0x1f83d9abfb41bd6bULL;
	fsv_t2->state[7] = 0x5be0cd19137e2179ULL;
	while(length > 0) {
		if(fsv_t2->curlen == 0 && length >= 128) {
            reader_fn(fsv_t3, 128, fsv_t4, 128);
			fsv_t1 = fs_sha512_compress (fsv_t2->state, (unsigned char *)fsv_t3);
			if(fsv_t1) {
				goto done;
			}
			fsv_t2->length += 128 * 8;
			fsv_t4         += 128;
			length          -= 128;
		} else {
			fsv_t2->n = length < (128 - fsv_t2->curlen) ? length : (128 - fsv_t2->curlen);
            reader_fn(fsv_t2->buf + fsv_t2->curlen, (size_t)fsv_t2->n, fsv_t4, (size_t)fsv_t2->n);
			fsv_t2->curlen += fsv_t2->n;
			fsv_t4         += fsv_t2->n;
			length          -= fsv_t2->n;
			if(fsv_t2->curlen == 128) {
				fsv_t1 = fs_sha512_compress (fsv_t2->state, fsv_t2->buf);
				if(fsv_t1) {
					goto done;
				}
				fsv_t2->length += 8*128;
				fsv_t2->curlen = 0;
			}
		}
	}
	fsv_t2->length += fsv_t2->curlen * 8ULL;
	fsv_t2->buf[fsv_t2->curlen++] = (unsigned char)0x80;
	if(fsv_t2->curlen > 112) {
		while(fsv_t2->curlen < 128) {
			fsv_t2->buf[fsv_t2->curlen++] = (unsigned char)0;
		}
		fs_sha512_compress(fsv_t2->state, fsv_t2->buf);
		fsv_t2->curlen = 0;
	}
	while(fsv_t2->curlen < 120) {
		fsv_t2->buf[fsv_t2->curlen++] = (unsigned char)0;
	}
	FS_STORE64H(fsv_t2->length, fsv_t2->buf+120);
	fs_sha512_compress(fsv_t2->state, fsv_t2->buf);
	for(fsv_t2->i = 0; fsv_t2->i < 8; fsv_t2->i++) {
		FS_STORE64H(fsv_t2->state[fsv_t2->i], out+(8*fsv_t2->i));
	}
	memset(&fsv_t2->state, 0, sizeof(fsv_t2->state));
done:
	fs_safe_shred_and_free(&fsv_t2,sizeof(*fsv_t2));
	return fsv_t1;
}
#endif // #if SECURITY_LOW_MEMORY
