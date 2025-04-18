enum {
	PK_PUBLIC=0,
	PK_PRIVATE=1
};

enum {
	FS_ASN1_EOL,
	FS_ASN1_BOOLEAN,
	FS_ASN1_INTEGER,
	FS_ASN1_SHORT_INTEGER,
	FS_ASN1_BIT_STRING,
	FS_ASN1_OCTET_STRING,
	FS_ASN1_NULL,
	FS_ASN1_OBJECT_IDENTIFIER,
	FS_ASN1_IA5_STRING,
	FS_ASN1_PRINTABLE_STRING,
	FS_ASN1_UTF8_STRING,
	FS_ASN1_UTCTIME,
	FS_ASN1_CHOICE,
	FS_ASN1_SEQUENCE,
	FS_ASN1_SET,
	FS_ASN1_SETOF
};

enum fs_pkcs_1_v1_5_blocks {
	FS_PKCS_1_EMSA = 1,
	FS_PKCS_1_EME = 2
}
;


typedef struct fs_asn1_list_ {
	int type;
	void *data;
	unsigned long size;
	int used;
	struct fs_asn1_list_ *prev, *next, *child, *parent;
}  fs_asn1_list;

typedef struct {
	int type;
	fs_mp_int *e; 
	fs_mp_int *d; 
	fs_mp_int *N; 
	fs_mp_int *p; 
	fs_mp_int *q; 
	fs_mp_int *qP; 
	fs_mp_int *dP; 
	fs_mp_int *dQ;
} fs_rsa_key;

#define FS_SET_ASN1(__list, __index, __type, __data, __size)  \
   do {                                              \
      /* NOT__FS_LOCAL_STATIC_OPTION */ int oov2joa1moh1nohda2xei5is0Eigh1oo; \
      /* NOT__FS_LOCAL_STATIC_OPTION */ fs_asn1_list *Ohxeivefob0eevee9eiphai2Phee5Ofo = NULL; \
      oov2joa1moh1nohda2xei5is0Eigh1oo = (__index);       \
      Ohxeivefob0eevee9eiphai2Phee5Ofo = (__list);        \
      Ohxeivefob0eevee9eiphai2Phee5Ofo[oov2joa1moh1nohda2xei5is0Eigh1oo].type = (__type);  \
      Ohxeivefob0eevee9eiphai2Phee5Ofo[oov2joa1moh1nohda2xei5is0Eigh1oo].data = (void*)(__data);  \
      Ohxeivefob0eevee9eiphai2Phee5Ofo[oov2joa1moh1nohda2xei5is0Eigh1oo].size = (__size);  \
      Ohxeivefob0eevee9eiphai2Phee5Ofo[oov2joa1moh1nohda2xei5is0Eigh1oo].used = 0;       \
   } while (0);

/* Min and Max RSA key sizes (in bits) */
#define MIN_RSA_SIZE 1024
#define MAX_RSA_SIZE 4096

__FS_FUNCTION_PREFER_INLINE int fs_pkcs_1_v1_5_decode(const unsigned char *msg, unsigned long  msglen, int block_type, unsigned long modulus_bitlen, unsigned char *out, unsigned long *outlen, int *is_valid) {
	__FS_LOCAL_STATIC_OPTION unsigned long t1;
	__FS_LOCAL_STATIC_OPTION unsigned long t2;
	__FS_LOCAL_STATIC_OPTION unsigned long t3;
	__FS_LOCAL_STATIC_OPTION int fsv_t4;

	t1 = 0;
	t2 = 0;
	t3 = 0;
	fsv_t4 = 0;

	/* default to invalid packet */
	*is_valid = 0;

	t1 = (modulus_bitlen >> 3) + (modulus_bitlen & 7 ? 1 : 0);

	/* test message size */

	if((msglen > t1) || (t1 < 11)) {
		fsv_t4 = 1;
		goto bail;
	}

	/* separate encoded message */

	if((msg[0] != 0x00) || (msg[1] != (unsigned char)block_type)) {
		fsv_t4 = 1;
		goto bail;
	}

	if(block_type == FS_PKCS_1_EME) {
		for(t3 = 2; t3 < t1; t3++) {
			/* separator */
			if(msg[t3] == 0x00) {
				break;
			}
		}
		t2 = t3++ - 2;

		if((t3 >= t1) || (t2 < 8)) {
			/* There was no octet with hexadecimal value 0x00 to separate ps from m,
			 * or the length of ps is less than 8 octets.
			 */
			fsv_t4 = 1;
			goto bail;
		}
	} else {
		for(t3 = 2; t3 < t1 - 1; t3++) {
			if(msg[t3] != 0xFF) {
				break;
			}
		}

		/* separator check */
		if(msg[t3] != 0) {
			/* There was no octet with hexadecimal value 0x00 to separate ps from m. */
			fsv_t4 = 1;
			goto bail;
		}

		t2 = t3 - 2;
	}

	if(*outlen < (msglen - (2 + t2 + 1))) {
		*outlen = msglen - (2 + t2 + 1);
		fsv_t4 = 1;
		goto bail;
	}

	*outlen = (msglen - (2 + t2 + 1));
	memcpy(out, &msg[2 + t2 + 1], *outlen);

	/* valid packet */
	*is_valid = 1;
	fsv_t4    = 0;
	bail:
	return fsv_t4;
} /* fs_pkcs_1_v1_5_decode */

__FS_FUNCTION_PREFER_INLINE int fs_der_length_bit_string(unsigned long nbits, unsigned long *outlen) {
	__FS_LOCAL_STATIC_OPTION unsigned long t1;
	__FS_LOCAL_STATIC_OPTION int t2;
	t2 = 0;
	/* get the number of the bytes */
	t1 = (nbits >> 3) + ((nbits & 7) ? 1 : 0) + 1;

	if(t1 < 128) {
		/* 03 LL PP DD DD DD ... */
		*outlen = 2 + t1;
	} else if(t1 < 256) {
		/* 03 81 LL PP DD DD DD ... */
		*outlen = 3 + t1;
	} else if(t1 < 65536) {
		/* 03 82 LL LL PP DD DD DD ... */
		*outlen = 4 + t1;
	} else {
		t2 = 1;
		goto done;
	}
	done:
	return t2;
}
__FS_FUNCTION_PREFER_INLINE int fs_der_decode_octet_string(const unsigned char *in, unsigned long inlen, unsigned char *out, unsigned long *outlen) {
	__FS_LOCAL_STATIC_OPTION unsigned long t1;
	__FS_LOCAL_STATIC_OPTION unsigned long t2;
	__FS_LOCAL_STATIC_OPTION unsigned long t3;
	__FS_LOCAL_STATIC_OPTION int fsv_t4;

	fsv_t4 = 0;

	/* must have header at least */
	if(inlen < 2) {
		fsv_t4 = 1;
		goto done;
	}

	/* check for 0x04 */
	if((in[0] & 0x1F) != 0x04) {
		fsv_t4 = 1;
		goto done;
	}
	t1 = 1;

	/* decode the length */
	if(in[t1] & 0x80) {
		/* valid # of bytes in length are 1,2,3 */
		t2 = in[t1] & 0x7F;
		if((t2 == 0) || (t2 > 3) || ((t1 + t2) > inlen)) {
			fsv_t4 = 1;
			goto done;
		}

		/* read the length in */
		t3 = 0;
		++t1;
		while(t2--) {
			t3 = (t3 << 8) | in[t1++];
		}
	} else {
		t3 = in[t1++] & 0x7F;
	}

	/* is it too long? */
	if(t3 > *outlen) {
		*outlen = t3;
		fsv_t4 = 1;
		goto done;
	}

	if(t3 + t1 > inlen) {
		fsv_t4 = 1;
		goto done;
	}

	/* read the data */
	for(t2 = 0; t2 < t3; t2++) {
		out[t2] = in[t1++];
	}

	*outlen = t2;
	done:
	return fsv_t4;
}


__FS_FUNCTION_PREFER_INLINE int fs_der_decode_bit_string(const unsigned char *in,  unsigned long inlen, unsigned char *out, unsigned long *outlen) {
	__FS_LOCAL_STATIC_OPTION unsigned long t1;
	__FS_LOCAL_STATIC_OPTION unsigned long t2;
	__FS_LOCAL_STATIC_OPTION unsigned long t3;
	__FS_LOCAL_STATIC_OPTION unsigned long fsv_t4;
	__FS_LOCAL_STATIC_OPTION int fsv_t5;

	t1 = 0;
	t2 = 0;
	t3 = 0;
	fsv_t4 = 0;
	fsv_t5 = 0;
	
	/* packet must be at least 4 bytes */
	if(inlen < 4) {
		fsv_t5 = 1;
		goto done;
	}

	/* check for 0x03 */
	if((in[0]&0x1F) != 0x03) {
		fsv_t5 = 1;
		goto done;
	}

	/* offset in the data */
	t3 = 1;

	/* get the length of the data */
	if(in[t3] & 0x80) {
		/* long format get number of length bytes */
		fsv_t4 = in[t3++] & 0x7F;

		/* invalid if 0 or > 2 */
		if(fsv_t4 == 0 || fsv_t4 > 2) {
			fsv_t5 = 1;
			goto done;
		}

		/* read the data len */
		t1 = 0;
		while(fsv_t4--) {
			t1 = (t1 << 8) | (unsigned long)in[t3++];
		}
	} else {
		/* short format */
		t1 = in[t3++] & 0x7F;
	}

	/* is the data len too long or too short? */
	if((t1 == 0) || (t1 + t3 > inlen)) {
		fsv_t5 = 1;
		goto done;
	}

	/* get padding count */
	t2 = ((t1 - 1) << 3) - (in[t3++] & 7);

	/* too many bits? */
	if(t2 > *outlen) {
		*outlen = t2;
		fsv_t5 = 1;
		goto done;
	}

	/* decode/store the bits */
	for(fsv_t4 = 0; fsv_t4 < t2; fsv_t4++) {
		out[fsv_t4] = (in[t3] & (1 << (7 - (fsv_t4 & 7)))) ? 1 : 0;
		if((fsv_t4 & 7) == 7) {
			++t3;
		}
	}

	/* we done */
	*outlen = t2;
	done:
	return fsv_t5;
}

__FS_FUNCTION_PREFER_INLINE int fs_der_decode_object_identifier(const unsigned char *in, unsigned long inlen, unsigned long *words, unsigned long *outlen) {
	__FS_LOCAL_STATIC_OPTION unsigned long t1;
	__FS_LOCAL_STATIC_OPTION unsigned long t2;
	__FS_LOCAL_STATIC_OPTION unsigned long t3;
	__FS_LOCAL_STATIC_OPTION unsigned long fsv_t4;
	__FS_LOCAL_STATIC_OPTION int fsv_t5;
	t1    = 0;  
	t2    = 0;  
	t3    = 0;  
	fsv_t4  = 0;
	fsv_t5 = 0;
	/* header is at least 3 bytes */
	if(inlen < 3) {
		fsv_t5 = 1;
		goto done;
	}

	/* must be room for at least two words */
	if(*outlen < 2) {
		fsv_t5 = 1;
		goto done;
	}

	/* decode the packet header */
	t1 = 0;
	if((in[t1++] & 0x1F) != 0x06) {
		fsv_t5 = 1;
		goto done;
	}

	/* get the length */
	if(in[t1] < 128) {
		fsv_t4 = in[t1++]; 
	} else {
		if(in[t1] < 0x81 || in[t1] > 0x82) {
			fsv_t5 = 1;
			goto done;
		}
		t2   = in[t1++] & 0x7F;
		fsv_t4 = 0;
		while(t2--) {
			fsv_t4 = (fsv_t4 << 8) | (unsigned long)in[t1++];
		}
	}

	if(fsv_t4 < 1 || (fsv_t4 + t1) > inlen) {
		fsv_t5 = 1;
		goto done;
	}

	/* decode words */
	t2 = 0;
	t3 = 0;
	while(fsv_t4--) {
		t3 = (t3 << 7) | (in[t1] & 0x7F);
		if(!(in[t1++] & 0x80)) {
			/* store t */
			if(t2 >= *outlen) {
				fsv_t5 = 1;
				goto done;
			}
			if(t2 == 0) {
				words[0] = t3 / 40;
				words[1] = t3 % 40;
				t2 = 2;
			} else {
				words[t2++] = t3;
			}
			t3          = 0;
		}
	}

	*outlen = t2;
	done:
	return fsv_t5;
}

__FS_FUNCTION_PREFER_INLINE int fs_der_length_octet_string(unsigned long noctets, unsigned long *outlen) {
	__FS_LOCAL_STATIC_OPTION int t1 = 0;
	t1 = 0;
	if(noctets < 128) {
		/* 04 LL DD DD DD ... */
		*outlen = 2 + noctets;
	} else if(noctets < 256) {
		/* 04 81 LL DD DD DD ... */
		*outlen = 3 + noctets;
	} else if(noctets < 65536UL) {
		/* 04 82 LL LL DD DD DD ... */
		*outlen = 4 + noctets;
	} else if(noctets < 16777216UL) {
		/* 04 83 LL LL LL DD DD DD ... */
		*outlen = 5 + noctets;
	} else {
		t1 = 1;
		goto done;
	}
	done:
	return t1;
}

__FS_FUNCTION_PREFER_INLINE int fs_der_length_integer(void *num, unsigned long *outlen) {
	__FS_LOCAL_STATIC_OPTION unsigned long t1;
	__FS_LOCAL_STATIC_OPTION unsigned long t2;
	__FS_LOCAL_STATIC_OPTION int t3;
	__FS_LOCAL_STATIC_OPTION int fsv_t4;
    __FS_LOCAL_STATIC_OPTION int t4;
    __FS_LOCAL_STATIC_OPTION int fsv_t5;
    __FS_LOCAL_STATIC_OPTION int t6;

	t1 = 0;
	t2 = 0;
	fsv_t4 = 0;
	t3 = 0;

	t6 = fs_mp_cmp_d((fs_mp_int*)num, 0);
	if(t6 != -1) {
		/* positive */
		fs_mp_cmp_d((fs_mp_int*)num, 0);
		if((fs_mp_count_bits((fs_mp_int*)num) & 7) == 0 || (t6 == 0 ? 1 : 0) == 1) {
			t3 = 1;
		} else {
			t3 = 0;
		}

		/* size for bignum */
		t1 = t2 = t3 + fs_mp_unsigned_bin_size((fs_mp_int*)num);
	} else {
		/* it's negative */
		/* find power of 2 that is a multiple of eight and greater than count bits */
		t3 = 0;
		t4 = fs_mp_count_bits((fs_mp_int*)num);
		t1 = t4 + (8 - (t4 & 7));
		fsv_t5 = fs_mp_cnt_lsb((fs_mp_int*)num);
		if(((fsv_t5+1) == t4) && ((t4 & 7)==0)) {
			--t1;
		}
		t2 = t1 = t1 >> 3;
	}

	/* now we need a length */
	if(t1 < 128) {
		/* short form */
		++t2;
	} else {
		/* long form (relies on z != 0), assumes length bytes < 128 */
		++t2;

		while(t1) {
			++t2;
			t1 >>= 8;
		}
	}

	/* we need a 0x02 to indicate it's INTEGER */
	++t2;

	/* return length */
	*outlen = t2; 
	return fsv_t4;
}

__FS_FUNCTION_PREFER_INLINE unsigned long fs_der_object_identifier_bits(unsigned long fsa_x) {
	__FS_LOCAL_STATIC_OPTION unsigned long t1;
	t1  = 0;
	
	fsa_x &= 0xFFFFFFFF;
	while(fsa_x) {
		++t1;
		fsa_x >>= 1;
	}
	return t1;
}

__FS_FUNCTION_PREFER_INLINE int fs_der_length_object_identifier(unsigned long *words, unsigned long nwords, unsigned long *outlen) {
	__FS_LOCAL_STATIC_OPTION unsigned long t1;
	__FS_LOCAL_STATIC_OPTION unsigned long t2;
	__FS_LOCAL_STATIC_OPTION unsigned long t3;
	__FS_LOCAL_STATIC_OPTION unsigned long fsv_t4;
	__FS_LOCAL_STATIC_OPTION int fsv_t5;

	t1 = 0; 
	t2 = 0; 
	t3 = 0; 
	fsv_t4 = 0; 
	fsv_t5 = 0;

	/* must be >= 2 words */
	if(nwords < 2) {
		fsv_t5 = 1;
		goto done;
	}

	/* word1 = 0,1,2,3 and word2 0..39 */
	if(words[0] > 3 || (words[0] < 2 && words[1] > 39)) {
		fsv_t5 = 1;
		goto done;
	}

	/* leading word is the first two */
	t2 = 0;
	fsv_t4 = words[0] * 40 + words[1];
	for(t1 = 1; t1 < nwords; t1++) {
		t3 = fs_der_object_identifier_bits(fsv_t4);
		t2 += t3/7 + ((t3%7) ? 1 : 0) + (fsv_t4 == 0 ? 1 : 0);
		if(t1 < nwords - 1) {
			/* grab next word */
			fsv_t4 = words[t1+1];
		}
	}

	/* now depending on the length our length encoding changes */
	if(t2 < 128) {
		t2 += 2;
	} else if(t2 < 256) {
		t2 += 3;
	} else if(t2 < 65536UL) {
		t2 += 4;
	} else {
		fsv_t5 = 1;
		goto done;
	}

	*outlen = t2;
	done:
	return fsv_t5;
}

/* A copy of fs_der_length_sequence so we can it.  Limits us to only 1 level of recursion but it will be inlined. */
__FS_FUNCTION_PREFER_INLINE int fs_der_length_sequence2(fs_asn1_list *list, unsigned long inlen, unsigned long *outlen) {
	__FS_LOCAL_STATIC_OPTION int t1;
	__FS_LOCAL_STATIC_OPTION int t2;
	__FS_LOCAL_STATIC_OPTION unsigned long t3;
	__FS_LOCAL_STATIC_OPTION unsigned long fsv_t4;
	__FS_LOCAL_STATIC_OPTION unsigned long fsv_t5;
	__FS_LOCAL_STATIC_OPTION unsigned long fsv_t6;
	__FS_LOCAL_STATIC_OPTION void* fsv_t8;

	t1 = 0;
	/* get size of output that will be required */
	fsv_t6 = 0;
	for(t3 = 0; t3 < inlen; t3++) {
		t2 = list[t3].type;
		fsv_t4 = list[t3].size;
		fsv_t8 = list[t3].data;

		if(t2 == FS_ASN1_EOL) {
			break;
		}

		switch(t2) {
		
		case FS_ASN1_NULL:
			fsv_t6 += 2;
			break;

		case FS_ASN1_OBJECT_IDENTIFIER:
			if((t1 = fs_der_length_object_identifier((long unsigned int*)fsv_t8, fsv_t4, &fsv_t5)) != 0) {
				goto done;
			}
			fsv_t6 += fsv_t5;
			break;

			//           case FS_ASN1_SET:
			//           case FS_ASN1_SETOF:
			//           case FS_ASN1_SEQUENCE:
			//               if ((err = fs_der_length_sequence2(data, size, &x)) != 0) {
			//                  goto done;
			//               }
			//               y += x;
			//               break;


		default:
			t1 = 1;
			goto done;
		}
	}

	/* calc header size */
	if(fsv_t6 < 128) {
		fsv_t6 += 2;
	} else if(fsv_t6 < 256) {
		/* 0x30 0x81 LL */
		fsv_t6 += 3;
	} else if(fsv_t6 < 65536UL) {
		/* 0x30 0x82 LL LL */
		fsv_t6 += 4;
	} else if(fsv_t6 < 16777216UL) {
		/* 0x30 0x83 LL LL LL */
		fsv_t6 += 5;
	} else {
		t1 = 1;
		goto done;
	}

	/* store size */
	*outlen = fsv_t6;
	t1     = 0;

	done:
	return t1;
}

__FS_FUNCTION_PREFER_INLINE int fs_der_length_sequence(fs_asn1_list *list, unsigned long inlen, unsigned long *outlen) {
	__FS_LOCAL_STATIC_OPTION int t1;
	__FS_LOCAL_STATIC_OPTION int t2;
	__FS_LOCAL_STATIC_OPTION unsigned long t3;
	__FS_LOCAL_STATIC_OPTION unsigned long fsv_t4;
	__FS_LOCAL_STATIC_OPTION unsigned long fsv_t5;
	__FS_LOCAL_STATIC_OPTION unsigned long fsv_t6;
	__FS_LOCAL_STATIC_OPTION void* fsv_t8;

	t1 = 0;
	/* get size of output that will be required */
	fsv_t6 = 0;
	for(t3 = 0; t3 < inlen; t3++) {
		t2 = list[t3].type;
		fsv_t4 = list[t3].size;
		fsv_t8 = list[t3].data;

		if(t2 == FS_ASN1_EOL) {
			break;
		}

		switch(t2) {
		
		case FS_ASN1_NULL:
			fsv_t6 += 2;
			break;

		case FS_ASN1_OBJECT_IDENTIFIER:
			if((t1 = fs_der_length_object_identifier((long unsigned int*)fsv_t8, fsv_t4, &fsv_t5)) != 0) {
				goto done;
			}
			fsv_t6 += fsv_t5;
			break;

		case FS_ASN1_SET:
		case FS_ASN1_SETOF:
		case FS_ASN1_SEQUENCE:
			if((t1 = fs_der_length_sequence2((fs_asn1_list*)fsv_t8, fsv_t4, &fsv_t5)) != 0) {
				goto done;
			}
			fsv_t6 += fsv_t5;
			break;


		default:
			t1 = 1;
			goto done;
		}
	}

	/* calc header size */
	if(fsv_t6 < 128) {
		fsv_t6 += 2;
	} else if(fsv_t6 < 256) {
		/* 0x30 0x81 LL */
		fsv_t6 += 3;
	} else if(fsv_t6 < 65536UL) {
		/* 0x30 0x82 LL LL */
		fsv_t6 += 4;
	} else if(fsv_t6 < 16777216UL) {
		/* 0x30 0x83 LL LL LL */
		fsv_t6 += 5;
	} else {
		t1 = 1;
		goto done;
	}

	/* store size */
	*outlen = fsv_t6;
	t1     = 0;

	done:
	return t1;
}

typedef struct fs_der_decode_integer_data {
	unsigned long x, y, z;
} fs_der_decode_integer_data_t;

__FS_FUNCTION_PREFER_INLINE int fs_der_decode_integer(const unsigned char *in, unsigned long inlen, void *num) {
	__FS_LOCAL_STATIC_OPTION int t1;
	__FS_LOCAL_STATIC_OPTION fs_der_decode_integer_data_t* t2;
	__FS_LOCAL_STATIC_OPTION fs_mp_int *t3;
	t2 = (fs_der_decode_integer_data_t*)fs_zalloc(sizeof(fs_der_decode_integer_data_t));
	t1 = 0;
	t3 = NULL;
	if(t2 == NULL) {
		t1 = 1;
		goto done;
	}

	/* min DER INTEGER is 0x02 01 00 == 0 */
	if(inlen < (1 + 1 + 1)) {
		t1 = 1;
		goto done;
	}

	/* ok expect 0x02 when we AND with 0001 1111 [1F] */
	t2->x = 0;
	if((in[t2->x++] & 0x1F) != 0x02) {
		t1 = 1;
		goto done;
	}

	/* now decode the len stuff */
	t2->z = in[t2->x++];

	if((t2->z & 0x80) == 0x00) {
		/* short form */

		/* will it overflow? */
		if(t2->x + t2->z > inlen) {
			t1 = 1;
			goto done;
		}

		/* no so read it */
		fs_mp_read_unsigned_bin((fs_mp_int*)num, (unsigned char *)in + t2->x, t2->z);
		if (fs_mp_error) {
			t1 = 1;
			goto done;
		}
	} else {
		/* long form */
		t2->z &= 0x7F;

		/* will number of length bytes overflow? (or > 4) */
		if(((t2->x + t2->z) > inlen) || (t2->z > 4) || (t2->z == 0)) {
			t1 = 1;
			goto done;
		}

		/* now read it in */
		t2->y = 0;
		while(t2->z--) {
			t2->y = ((unsigned long)(in[t2->x++])) | (t2->y << 8);
		}

		/* now will reading p_data->y bytes overrun? */
		if((t2->x + t2->y) > inlen) {
			t1 = 1;
			goto done;
		}

		/* no so read it */
		fs_mp_read_unsigned_bin((fs_mp_int*)num, (unsigned char *)in + t2->x, t2->y);
		if (fs_mp_error) {
			t1 = 1;
			goto done;
		}
	}

	/* see if it's negative */
	if(in[t2->x] & 0x80) {
		fs_mp_alloc_and_init(&t3);
		if(t3 == NULL) {
			t1 = 1;
			goto done;
		}

		fs_mp_2expt(t3, fs_mp_count_bits((fs_mp_int*)num));
		if(fs_mp_error) {
			fs_mp_safe_shred_and_free_mp_int(&t3);
			goto done;
		}
		fs_mp_sub((fs_mp_int*)num, t3, (fs_mp_int*)num);
		if(fs_mp_error) {
			fs_mp_safe_shred_and_free_mp_int(&t3);
			t1 = 1;
			goto done;
		}
		fs_mp_safe_shred_and_free_mp_int(&t3);
	}
	t1 = 0;
	done:
	fs_safe_shred_and_free(&t2, sizeof(*t2));

	return t1;
}

typedef struct fs_der_decode_sequence_ex_data {
	int type;
	unsigned long size;
	unsigned long x;
	unsigned long y;
	unsigned long z;
	unsigned long t3;
	unsigned long blksize;
	void*         data;
} fs_der_decode_sequence_ex_data_t;


/* Copy of fs_der_decode_sequence_ex so we can do one level of recursion and still everything */
__FS_FUNCTION_PREFER_INLINE int fs_der_decode_sequence_ex2(const unsigned char *in, unsigned long  inlen, fs_asn1_list *list, unsigned long  outlen, int ordered) {
	__FS_LOCAL_STATIC_OPTION int           t1 = 0;
	__FS_LOCAL_STATIC_OPTION fs_der_decode_sequence_ex_data_t* t2;
	t1 = 0;
	t2 = (fs_der_decode_sequence_ex_data_t*)fs_zalloc(sizeof(fs_der_decode_sequence_ex_data_t));
	if(NULL == t2) {
		t1 = 1; 
		goto done;
	}

	/* get blk size */
	if(inlen < 2) {
		t1 = 1;
		goto done;
	}

	/* sequence p_data->type? We allow 0x30 SEQUENCE and 0x31 SET since fundamentally they're the same structure */
	t2->x = 0;
	if(in[t2->x] != 0x30 && in[t2->x] != 0x31) {
		t1 = 1;
		goto done;
	}
	++t2->x;

	if(in[t2->x] < 128) {
		t2->blksize = in[t2->x++];
	} else if(in[t2->x] & 0x80) {
		if(in[t2->x] < 0x81 || in[t2->x] > 0x83) {
			t1 = 1;
			goto done;
		}
		t2->y = in[t2->x++] & 0x7F;

		/* would reading the len bytes overrun? */
		if(t2->x + t2->y > inlen) {
			t1 = 1;
			goto done;
		}

		/* read len */
		t2->blksize = 0;
		while(t2->y--) {
			t2->blksize = (t2->blksize << 8) | (unsigned long)in[t2->x++];
		}
	}

	/* would this p_data->blksize overflow? */
	if(t2->x + t2->blksize > inlen) {
		t1 = 1;
		goto done;
	}

	/* mark all as unused */
	for(t2->t3 = 0; t2->t3 < outlen; t2->t3++) {
		list[t2->t3].used = 0;
	}     

	/* ok read p_data->data */
	inlen = t2->blksize;
	for(t2->t3 = 0; t2->t3 < outlen; t2->t3++) {
		t2->z    = 0;
		t2->type = list[t2->t3].type;
		t2->size = list[t2->t3].size;
		t2->data = list[t2->t3].data;
		if(!ordered && list[t2->t3].used == 1) {
			continue;
		}

		if(t2->type == FS_ASN1_EOL) {
			break;
		}

		switch(t2->type) {
		
		case FS_ASN1_INTEGER:
			t2->z = inlen;
			if((t1 = fs_der_decode_integer(in + t2->x, t2->z, t2->data)) != 0) {
				if(!ordered) {
					continue;
				}
				goto done;
			}
			if((t1 = fs_der_length_integer(t2->data, &t2->z)) != 0) {
				goto done;
			}
			break;

		case FS_ASN1_BIT_STRING:
			t2->z = inlen;
			if((t1 = fs_der_decode_bit_string(in + t2->x, t2->z, (u_int8_t*)t2->data, &t2->size)) != 0) {
				if(!ordered) {
					continue;
				}
				goto done;
			}
			list[t2->t3].size = t2->size;
			if((t1 = fs_der_length_bit_string(t2->size, &t2->z)) != 0) {
				goto done;
			}
			break;

		case FS_ASN1_OCTET_STRING:
			t2->z = inlen;
			if((t1 = fs_der_decode_octet_string(in + t2->x, t2->z, (u_int8_t*)t2->data, &t2->size)) != 0) {
				if(!ordered) {
					continue;
				}
				goto done;
			}
			list[t2->t3].size = t2->size;
			if((t1 = fs_der_length_octet_string(t2->size, &t2->z)) != 0) {
				goto done;
			}
			break;

		case FS_ASN1_NULL:
			if(inlen < 2 || in[t2->x] != 0x05 || in[t2->x+1] != 0x00) {
				if(!ordered) {
					continue;
				}
				t1 = 1;
				goto done;
			}
			t2->z = 2;
			break;

		case FS_ASN1_OBJECT_IDENTIFIER:
			t2->z = inlen;
			if((t1 = fs_der_decode_object_identifier(in + t2->x, t2->z, (long unsigned int*)t2->data, &t2->size)) != 0) {
				if(!ordered) {
					continue;
				}
				goto done;
			}
			list[t2->t3].size = t2->size;
			if((t1 = fs_der_length_object_identifier((long unsigned int*)t2->data, t2->size, &t2->z)) != 0) {
				goto done;
			}
			break;

			//           case FS_ASN1_SET:
			//               p_data->z = inlen;
			//               if ((err = fs_der_decode_sequence_ex(in + p_data->x, p_data->z, p_data->data, p_data->size, 0)) != 0) {
			//                  if (!ordered) { continue; }
			//                  goto done;
			//               }
			//               if ((err = fs_der_length_sequence(p_data->data, p_data->size, &p_data->z)) != 0) {
			//                  goto done;
			//               }
			//               break;

			//           case FS_ASN1_SETOF:
			//           case FS_ASN1_SEQUENCE:
			//               /* detect if we have the right p_data->type */
			//               if ((p_data->type == FS_ASN1_SETOF && (in[p_data->x] & 0x3F) != 0x31) || (p_data->type == FS_ASN1_SEQUENCE && (in[p_data->x] & 0x3F) != 0x30)) {
			//                  err = 1;
			//                  goto done;
			//               }
			//
			//               p_data->z = inlen;
			//               if ((err = fs_der_decode_sequence_ex(in + p_data->x, p_data->z, p_data->data, p_data->size, 1)) != 0) {
			//                  if (!ordered) { continue; }
			//                  goto done;
			//               }
			//               if ((err = fs_der_length_sequence(p_data->data, p_data->size, &p_data->z)) != 0) {
			//                  goto done;
			//               }
			//               break;

		default:
			t1 = 1;
			goto done;
		}
		t2->x           += t2->z;
		inlen       -= t2->z;
		list[t2->t3].used = 1;
		if(!ordered) {
			/* restart the decoder */
			t2->t3 = -1;
		}
	}

	for(t2->t3 = 0; t2->t3 < outlen; t2->t3++) {
		if(list[t2->t3].used == 0) {
			t1 = 1;
			goto done;
		}
	}                
	t1 = 0;   

	done:
	fs_safe_shred_and_free(&t2,sizeof(*t2));
	return t1;
}
__FS_FUNCTION_PREFER_INLINE int fs_der_decode_sequence_ex(const unsigned char *in, unsigned long  inlen, fs_asn1_list *list, unsigned long  outlen, int ordered) {
	__FS_LOCAL_STATIC_OPTION int           t1 = 0;
	__FS_LOCAL_STATIC_OPTION fs_der_decode_sequence_ex_data_t* t2;

	t1 = 0;
	t2 = (fs_der_decode_sequence_ex_data_t*)fs_zalloc(sizeof(fs_der_decode_sequence_ex_data_t));
	if(NULL == t2) {
		t1 = 1; 
		goto done;
	}
	/* get blk p_data->size */
	if(inlen < 2) {
		t1 = 1;
		goto done;
	}

	/* sequence p_data->type? We allow 0x30 SEQUENCE and 0x31 SET since fundamentally they're the same structure */
	t2->x = 0;
	if(in[t2->x] != 0x30 && in[t2->x] != 0x31) {
		t1 = 1;
		goto done;
	}
	++t2->x;

	if(in[t2->x] < 128) {
		t2->blksize = in[t2->x++];
	} else if(in[t2->x] & 0x80) {
		if(in[t2->x] < 0x81 || in[t2->x] > 0x83) {
			t1 = 1;
			goto done;
		}
		t2->y = in[t2->x++] & 0x7F;

		/* would reading the len bytes overrun? */
		if(t2->x + t2->y > inlen) {
			t1 = 1;
			goto done;
		}

		/* read len */
		t2->blksize = 0;
		while(t2->y--) {
			t2->blksize = (t2->blksize << 8) | (unsigned long)in[t2->x++];
		}
	}

	/* would this p_data->blksize overflow? */
	if(t2->x + t2->blksize > inlen) {
		t1 = 1;
		goto done;
	}

	/* mark all as unused */
	for(t2->t3 = 0; t2->t3 < outlen; t2->t3++) {
		list[t2->t3].used = 0;
	}     

	/* ok read p_data->data */
	inlen = t2->blksize;
	for(t2->t3 = 0; t2->t3 < outlen; t2->t3++) {
		t2->z    = 0;
		t2->type = list[t2->t3].type;
		t2->size = list[t2->t3].size;
		t2->data = list[t2->t3].data;
		if(!ordered && list[t2->t3].used == 1) {
			continue;
		}

		if(t2->type == FS_ASN1_EOL) {
			break;
		}

		switch(t2->type) {
		
		case FS_ASN1_INTEGER:
			t2->z = inlen;
			if((t1 = fs_der_decode_integer(in + t2->x, t2->z, t2->data)) != 0) {
				if(!ordered) {
					continue;
				}
				goto done;
			}
			if((t1 = fs_der_length_integer(t2->data, &t2->z)) != 0) {
				goto done;
			}
			break;

		case FS_ASN1_BIT_STRING:
			t2->z = inlen;
			if((t1 = fs_der_decode_bit_string(in + t2->x, t2->z, (u_int8_t*)t2->data, &t2->size)) != 0) {
				if(!ordered) {
					continue;
				}
				goto done;
			}
			list[t2->t3].size = t2->size;
			if((t1 = fs_der_length_bit_string(t2->size, &t2->z)) != 0) {
				goto done;
			}
			break;

		case FS_ASN1_OCTET_STRING:
			t2->z = inlen;
			if((t1 = fs_der_decode_octet_string(in + t2->x, t2->z, (u_int8_t*)t2->data, &t2->size)) != 0) {
				if(!ordered) {
					continue;
				}
				goto done;
			}
			list[t2->t3].size = t2->size;
			if((t1 = fs_der_length_octet_string(t2->size, &t2->z)) != 0) {
				goto done;
			}
			break;

		case FS_ASN1_NULL:
			if(inlen < 2 || in[t2->x] != 0x05 || in[t2->x+1] != 0x00) {
				if(!ordered) {
					continue;
				}
				t1 = 1;
				goto done;
			}
			t2->z = 2;
			break;

		case FS_ASN1_OBJECT_IDENTIFIER:
			t2->z = inlen;
			if((t1 = fs_der_decode_object_identifier(in + t2->x, t2->z, (long unsigned int*)t2->data, &t2->size)) != 0) {
				if(!ordered) {
					continue;
				}
				goto done;
			}
			list[t2->t3].size = t2->size;
			if((t1 = fs_der_length_object_identifier((long unsigned int*)t2->data, t2->size, &t2->z)) != 0) {
				goto done;
			}
			break;

		case FS_ASN1_SET:
			t2->z = inlen;
			if((t1 = fs_der_decode_sequence_ex2(in + t2->x, t2->z, (fs_asn1_list*)t2->data, t2->size, 0)) != 0) {
				if(!ordered) {
					continue;
				}
				goto done;
			}
			if((t1 = fs_der_length_sequence((fs_asn1_list*)t2->data, t2->size, &t2->z)) != 0) {
				goto done;
			}
			break;

		case FS_ASN1_SETOF:
		case FS_ASN1_SEQUENCE:
			/* detect if we have the right p_data->type */
			if((t2->type == FS_ASN1_SETOF && (in[t2->x] & 0x3F) != 0x31) || (t2->type == FS_ASN1_SEQUENCE && (in[t2->x] & 0x3F) != 0x30)) {
				t1 = 1;
				goto done;
			}

			t2->z = inlen;
			if((t1 = fs_der_decode_sequence_ex2(in + t2->x, t2->z, (fs_asn1_list*)t2->data, t2->size, 1)) != 0) {
				if(!ordered) {
					continue;
				}
				goto done;
			}
			if((t1 = fs_der_length_sequence((fs_asn1_list*)t2->data, t2->size, &t2->z)) != 0) {
				goto done;
			}
			break;
		default:
			t1 = 1;
			goto done;
		}
		t2->x           += t2->z;
		inlen       -= t2->z;
		list[t2->t3].used = 1;
		if(!ordered) {
			/* restart the decoder */
			t2->t3 = -1;
		}
	}

	for(t2->t3 = 0; t2->t3 < outlen; t2->t3++) {
		if(list[t2->t3].used == 0) {
			t1 = 1;
			goto done;
		}
	}                
	t1 = 0;   
	done:
	fs_safe_shred_and_free(&t2,sizeof(*t2));
	return t1;
}

__FS_FUNCTION_PREFER_INLINE int fs_release_public_key(fs_rsa_key *key) {
	fs_mp_safe_shred_and_free_mp_int(&key->d);
	fs_mp_safe_shred_and_free_mp_int(&key->e);
	fs_mp_safe_shred_and_free_mp_int(&key->N);
	fs_mp_safe_shred_and_free_mp_int(&key->dQ);
	fs_mp_safe_shred_and_free_mp_int(&key->dP);
	fs_mp_safe_shred_and_free_mp_int(&key->qP);
	fs_mp_safe_shred_and_free_mp_int(&key->p);
	fs_mp_safe_shred_and_free_mp_int(&key->q);
	return 0;
}

typedef struct fs_rsa_load_public_key_data {
	fs_mp_int*     zero;
	unsigned char  tmpbuf[MAX_RSA_SIZE*8];
	unsigned long  t;
	unsigned long  x;
	unsigned long  y;
	unsigned long  z;
	unsigned long  tmpoid[16];
	fs_asn1_list   ssl_pubkey_hashoid[2];
	fs_asn1_list   ssl_pubkey[2];
	fs_asn1_list   list[9];
} fs_rsa_load_public_key_data_t;

#if SECURITY_ENABLE_RSA_KEY_LOAD_SHORTCUT
__FS_FUNCTION_PREFER_INLINE int fs_rsa_load_public_key(fs_rsa_key *key) {
	__FS_LOCAL_STATIC_OPTION int t1;
	__FS_LOCAL_STATIC_OPTION fs_mp_digit t2[] = { 0x06324005, 0x0675d159, 0x0dd5177e, 0x074e9258, 0x072b87b8, 0x081f7d30, 0x056073a2, 0x08852faf, 0x0cf7ec6e, 0x0e0badda, 0x0d6ebefa, 0x085f7d6e, 0x0c5b42d7, 0x0e1cd3a6, 0x0bff2da1, 0x04aff45b, 
		0x03df79f4, 0x02ece0e3, 0x03c42fad, 0x02f4d3c5, 0x041afaf6, 0x02f8120f, 0x0660f51a, 0x0a42594f, 0x08804d60, 0x043c1780, 0x053e7f90, 0x0aef2aa9, 0x0983ff38, 0x00af5e21, 0x0b75bb62, 0x0f6e2c11, 
		0x09772856, 0x0e960bf6, 0x0223751e, 0x0a1add2f, 0x05c0d019, 0x098ddfdd, 0x0dc8baa1, 0x09a045a0, 0x028c3207, 0x082bea9c, 0x0340758a, 0x06d50783, 0x03fb5d78, 0x09baa299, 0x089b1317, 0x096341af, 
		0x05cd38ad, 0x0053bc8e, 0x062d91ca, 0x0dc07296, 0x003ac226, 0x0a4369a1, 0x00f1fe26, 0x064f02ab, 0x098064bc, 0x07833867, 0x08668c4d, 0x0b05e66a, 0x0f1bf159, 0x02adc689, 0x037c8f95, 0x0a376c1f, 
		0x088082c1, 0x0d82a174, 0x07d3a352, 0x0b4c4bc9, 0x0473cec9, 0x068d6470, 0x0b00a040, 0x003597d8, 0x09825eef, 0x03db3ccf, 0x03f6c54d, 0x0a5ba160, 0x014c8e33, 0x096fadfc, 0x0634fe5c, 0x00d05b16, 
		0x077283de, 0x006e404d, 0x06ef6d2e, 0x0a2b80e4, 0x03a3c105, 0x07a23e32, 0x010c32c6, 0x07913a17, 0x0a3b6465, 0x096fc51c, 0x0342554f, 0x04a8d706, 0x0271d617, 0x0262bb27, 0x0cd7ef26, 0x097c8de5, 
		0x02e9333c, 0x06f3ebaf, 0x0a751a74, 0x0d5c738b, 0x08a8c58d, 0x0815a7fc, 0x0d4d270f, 0x0dbe0245, 0x039efcf9, 0x0400f225, 0x091e898c, 0x02207d77, 0x0fbf9913, 0x06df7362, 0x036c8d74, 0x05e61bda, 
		0x0770ad1c, 0x0f2587c8, 0x0b4a3655, 0x05b36cda, 0x08a57c08, 0x0750dfae, 0x06670591, 0x05eb60a1, 0x0241c042, 0x0109a693, 0x07e819c1, 0x0e6fd4e5, 0x0183c44e, 0x016dbe33, 0x0d8915d5, 0x0f3710da, 
		0x0c77b3a7, 0x0c1c493a, 0x087195aa, 0x025c3cd3, 0x095245f1, 0x09ee956b, 0x05c345db, 0x0793136f, 0x028b8f83, 0x0f6f737b, 0x0a9f791c, 0x006cd594, 0x09a3971f, 0x0afce8a6, 0x098b6e12, 0x08950d5d, 
		0x0b63bc1c, 0x086979bf, 0x000000d0 };

	t1 = 0;
	memset( key, 0, sizeof *key);
	key->type = 0;
	fs_mp_alloc_and_init(&key->e);
	fs_mp_alloc_and_init(&key->d);
	fs_mp_alloc_and_init(&key->N);
	fs_mp_alloc_and_init(&key->dQ);
	fs_mp_alloc_and_init(&key->dP);
	fs_mp_alloc_and_init(&key->qP);
	fs_mp_alloc_and_init(&key->p);
	fs_mp_alloc_and_init(&key->q);
	if(!key->e || !key->d || !key->N || !key->dQ || !key->dP || !key->qP || !key->p || !key->q) {
		t1 = 1;
		goto fail;
	}
	fs_mp_grow(key->e, 1);
	key->e->dp[0] = 0x00010001;
	key->e->used = 1;
	fs_mp_grow(key->N, 147);
	memcpy( &key->N->dp[0], &t2[0], sizeof(t2) );
	key->N->used = 147;

	return t1;
fail:
    fs_mp_safe_shred_and_free_mp_int(&key->d);
    fs_mp_safe_shred_and_free_mp_int(&key->e);
    fs_mp_safe_shred_and_free_mp_int(&key->N);
    fs_mp_safe_shred_and_free_mp_int(&key->dQ);
    fs_mp_safe_shred_and_free_mp_int(&key->dP);
    fs_mp_safe_shred_and_free_mp_int(&key->qP);
    fs_mp_safe_shred_and_free_mp_int(&key->p);
    fs_mp_safe_shred_and_free_mp_int(&key->q);
    return t1;
}
#else // #if SECURITY_ENABLE_RSA_KEY_LOAD_SHORTCUT
__FS_FUNCTION_MAYBE_INLINE int fs_rsa_load_public_key(fs_rsa_key *key) {
	__FS_LOCAL_STATIC_OPTION int t1;
	__FS_LOCAL_STATIC_OPTION fs_rsa_load_public_key_data_t* t2;

	t1 = 0;
	t2 = (fs_rsa_load_public_key_data_t*)fs_zalloc(sizeof(fs_rsa_load_public_key_data_t));
	if(NULL == t2) {
		t1 = 1;
		goto done;
	}

	__FS_LOCAL_STATIC_OPTION u_int8_t t3[] = { 0x30,0x82,0x02,0x22,0x30,0x0d,0x06,0x09,0x2a,0x86,0x48,0x86,0xf7,0x0d,0x01,0x01,0x01,0x05,0x00,0x03,0x82,0x02,0x0f,0x00,0x30,0x82,0x02,0x0a,0x02,0x82,0x02,0x01,0x00,0xd0,0x86,0x97,0x9b,0xfb,0x63,0xbc,0x1c,0x89,0x50,0xd5,0xd9,0x8b,0x6e,0x12,0xaf,0xce,0x8a,0x69,0xa3,0x97,0x1f,0x06,0xcd,0x59,0x4a,0x9f,0x79,0x1c,0xf6,0xf7,0x37,0xb2,0x8b,0x8f,0x83,0x79,0x31,0x36,0xf5,0xc3,0x45,0xdb,0x9e,0xe9,0x56,0xb9,0x52,0x45,0xf1,0x25,0xc3,0xcd,0x38,0x71,0x95,0xaa,0xc1,0xc4,0x93,0xac,0x77,0xb3,0xa7,0xf3,0x71,0x0d,0xad,0x89,0x15,0xd5,0x16,0xdb,0xe3,0x31,0x83,0xc4,0x4e,0xe6,0xfd,0x4e,0x57,0xe8,0x19,0xc1,0x10,0x9a,0x69,0x32,0x41,0xc0,0x42,0x5e,0xb6,0x0a,0x16,0x67,0x05,0x91,0x75,0x0d,0xfa,0xe8,0xa5,0x7c,0x08,0x5b,0x36,0xcd,0xab,0x4a,0x36,0x55,0xf2,0x58,0x7c,0x87,0x70,0xad,0x1c,0x5e,0x61,0xbd,0xa3,0x6c,0x8d,0x74,0x6d,0xf7,0x36,0x2f,0xbf,0x99,0x13,0x22,0x07,0xd7,0x79,0x1e,0x89,0x8c,0x40,0x0f,0x22,0x53,0x9e,0xfc,0xf9,0xdb,0xe0,0x24,0x5d,0x4d,0x27,0x0f,0x81,0x5a,0x7f,0xc8,0xa8,0xc5,0x8d,0xd5,0xc7,0x38,0xba,0x75,0x1a,0x74,0x6f,0x3e,0xba,0xf2,0xe9,0x33,0x3c,0x97,0xc8,0xde,0x5c,0xd7,0xef,0x26,0x26,0x2b,0xb2,0x72,0x71,0xd6,0x17,0x4a,0x8d,0x70,0x63,0x42,0x55,0x4f,0x96,0xfc,0x51,0xca,0x3b,0x64,0x65,0x79,0x13,0xa1,0x71,0x0c,0x32,0xc6,0x7a,0x23,0xe3,0x23,0xa3,0xc1,0x05,0xa2,0xb8,0x0e,0x46,0xef,0x6d,0x2e,0x06,0xe4,0x04,0xd7,0x72,0x83,0xde,0x0d,0x05,0xb1,0x66,0x34,0xfe,0x5c,0x96,0xfa,0xdf,0xc1,0x4c,0x8e,0x33,0xa5,0xba,0x16,0x03,0xf6,0xc5,0x4d,0x3d,0xb3,0xcc,0xf9,0x82,0x5e,0xef,0x03,0x59,0x7d,0x8b,0x00,0xa0,0x40,0x68,0xd6,0x47,0x04,0x73,0xce,0xc9,0xb4,0xc4,0xbc,0x97,0xd3,0xa3,0x52,0xd8,0x2a,0x17,0x48,0x80,0x82,0xc1,0xa3,0x76,0xc1,0xf3,0x7c,0x8f,0x95,0x2a,0xdc,0x68,0x9f,0x1b,0xf1,0x59,0xb0,0x5e,0x66,0xa8,0x66,0x8c,0x4d,0x78,0x33,0x86,0x79,0x80,0x64,0xbc,0x64,0xf0,0x2a,0xb0,0xf1,0xfe,0x26,0xa4,0x36,0x9a,0x10,0x3a,0xc2,0x26,0xdc,0x07,0x29,0x66,0x2d,0x91,0xca,0x05,0x3b,0xc8,0xe5,0xcd,0x38,0xad,0x96,0x34,0x1a,0xf8,0x9b,0x13,0x17,0x9b,0xaa,0x29,0x93,0xfb,0x5d,0x78,0x6d,0x50,0x78,0x33,0x40,0x75,0x8a,0x82,0xbe,0xa9,0xc2,0x8c,0x32,0x07,0x9a,0x04,0x5a,0x0d,0xc8,0xba,0xa1,0x98,0xdd,0xfd,0xd5,0xc0,0xd0,0x19,0xa1,0xad,0xd2,0xf2,0x23,0x75,0x1e,0xe9,0x60,0xbf,0x69,0x77,0x28,0x56,0xf6,0xe2,0xc1,0x1b,0x75,0xbb,0x62,0x0a,0xf5,0xe2,0x19,0x83,0xff,0x38,0xae,0xf2,0xaa,0x95,0x3e,0x7f,0x90,0x43,0xc1,0x78,0x08,0x80,0x4d,0x60,0xa4,0x25,0x94,0xf6,0x60,0xf5,0x1a,0x2f,0x81,0x20,0xf4,0x1a,0xfa,0xf6,0x2f,0x4d,0x3c,0x53,0xc4,0x2f,0xad,0x2e,0xce,0x0e,0x33,0xdf,0x79,0xf4,0x4a,0xff,0x45,0xbb,0xff,0x2d,0xa1,0xe1,0xcd,0x3a,0x6c,0x5b,0x42,0xd7,0x85,0xf7,0xd6,0xed,0x6e,0xbe,0xfa,0xe0,0xba,0xdd,0xac,0xf7,0xec,0x6e,0x88,0x52,0xfa,0xf5,0x60,0x73,0xa2,0x81,0xf7,0xd3,0x07,0x2b,0x87,0xb8,0x74,0xe9,0x25,0x8d,0xd5,0x17,0x7e,0x67,0x5d,0x15,0x96,0x32,0x40,0x05,0x02,0x03,0x01,0x00,0x01 };

	fs_mp_alloc_and_init(&key->e);
	fs_mp_alloc_and_init(&key->d);
	fs_mp_alloc_and_init(&key->N);
	fs_mp_alloc_and_init(&key->dQ);
	fs_mp_alloc_and_init(&key->dP);
	fs_mp_alloc_and_init(&key->qP);
	fs_mp_alloc_and_init(&key->p);
	fs_mp_alloc_and_init(&key->q);
	if(!key->e || !key->d || !key->N || !key->dQ || !key->dP || !key->qP || !key->p || !key->q) {
		t1 = 1;
		goto fail;
	}

	/* this includes the internal hash ID and optional params (NULL in this case) */
	FS_SET_ASN1(t2->ssl_pubkey_hashoid, 0, FS_ASN1_OBJECT_IDENTIFIER, t2->tmpoid,                sizeof(t2->tmpoid)/sizeof(t2->tmpoid[0]));   
	FS_SET_ASN1(t2->ssl_pubkey_hashoid, 1, FS_ASN1_NULL,              NULL,                  0);

	/* the actual format of the SSL DER key is odd, it stores a RSAPublicKey in a **BIT** string ... so we have to extract it
	   then proceed to convert bit to octet 
	 */
	FS_SET_ASN1(t2->ssl_pubkey, 0,         FS_ASN1_SEQUENCE,          &t2->ssl_pubkey_hashoid,   2);
	FS_SET_ASN1(t2->ssl_pubkey, 1,         FS_ASN1_BIT_STRING,        t2->tmpbuf,                sizeof(t2->tmpbuf));

	if(fs_der_decode_sequence_ex(t3, sizeof(t3), t2->ssl_pubkey, 2UL, 1) == 0) {

		/* ok now we have to reassemble the BIT STRING to an OCTET STRING.  Thanks OpenSSL... */
		for(t2->t = t2->y = t2->z = t2->x = 0; t2->x < t2->ssl_pubkey[1].size; t2->x++) {
			t2->y = (t2->y << 1) | t2->tmpbuf[t2->x];
			if(++t2->z == 8) {
				t2->tmpbuf[t2->t++] = (unsigned char)t2->y;
				t2->y           = 0;
				t2->z           = 0;
			}
		}
		t2->list[0].type = FS_ASN1_INTEGER;
		t2->list[0].size = 1UL;
		t2->list[0].data = key->N;
		t2->list[1].type = FS_ASN1_INTEGER;
		t2->list[1].size = 1UL;
		t2->list[1].data = key->e;

		/* now it should be SEQUENCE { INTEGER, INTEGER } */
		if((t1 = fs_der_decode_sequence_ex(t2->tmpbuf, t2->t, t2->list, 2, 1)) != 0) {
			goto fail;
		}
		key->type = PK_PUBLIC;
		t1 = 0;
		goto done;
	}

	t2->list[0].type = FS_ASN1_INTEGER;
	t2->list[0].size = 1UL;
	t2->list[0].data = key->N;
	/* not SSL public key, try to match against LTC_PKCS #1 standards */
	if((t1 = fs_der_decode_sequence_ex(t3, sizeof(t3), t2->list, 1, 1)) != 0) {
		goto fail;
	}

	if(fs_mp_cmp_d(key->N, 0) == 0) {
		fs_mp_alloc_and_init(&t2->zero);
		if(!t2->zero) {
			t1 = 1;
			goto fail;
		}
		/* it's a private key */
		t2->list[0].type = FS_ASN1_INTEGER; t2->list[0].size = 1UL; t2->list[0].data = t2->zero;
		t2->list[1].type = FS_ASN1_INTEGER; t2->list[1].size = 1UL; t2->list[1].data = key->N;
		t2->list[2].type = FS_ASN1_INTEGER; t2->list[2].size = 1UL; t2->list[2].data = key->e;
		t2->list[3].type = FS_ASN1_INTEGER; t2->list[3].size = 1UL; t2->list[3].data = key->d;
		t2->list[4].type = FS_ASN1_INTEGER; t2->list[4].size = 1UL; t2->list[4].data = key->p;
		t2->list[5].type = FS_ASN1_INTEGER; t2->list[5].size = 1UL; t2->list[5].data = key->q;
		t2->list[6].type = FS_ASN1_INTEGER; t2->list[6].size = 1UL; t2->list[6].data = key->dP;
		t2->list[7].type = FS_ASN1_INTEGER; t2->list[7].size = 1UL; t2->list[7].data = key->dQ;
		t2->list[8].type = FS_ASN1_INTEGER; t2->list[8].size = 1UL; t2->list[8].data = key->qP;
		if((t1 = fs_der_decode_sequence_ex(t3, sizeof(t3), t2->list, 8, 1)) != 0) {
			fs_mp_safe_shred_and_free_mp_int(&t2->zero);
			goto fail;
		}
		fs_mp_safe_shred_and_free_mp_int(&t2->zero);
		key->type = PK_PRIVATE;
	} else {
		if (fs_mp_cmp_d(key->N, 1) == 0) {
			/* we don't support multi-prime RSA */
			t1 = 1;
			goto fail;
		} else {
			t2->list[0].type = FS_ASN1_INTEGER; t2->list[0].size = 1UL; t2->list[0].data = key->N;
			t2->list[1].type = FS_ASN1_INTEGER; t2->list[1].size = 1UL; t2->list[1].data = key->e;
			/* it's a public key and we lack e */
			if((t1 = fs_der_decode_sequence_ex(t3, sizeof(t3), t2->list, 2, 1)) != 0) {
				goto fail;
			}
			key->type = PK_PUBLIC;
		}
	}
done:
	fs_safe_shred_and_free(&t2, sizeof(*t2));
	return 0;
fail:
	fs_safe_shred_and_free(&t2, sizeof(*t2));
	fs_mp_safe_shred_and_free_mp_int(&key->d);
	fs_mp_safe_shred_and_free_mp_int(&key->e);
	fs_mp_safe_shred_and_free_mp_int(&key->N);
	fs_mp_safe_shred_and_free_mp_int(&key->dQ);
	fs_mp_safe_shred_and_free_mp_int(&key->dP);
	fs_mp_safe_shred_and_free_mp_int(&key->qP);
	fs_mp_safe_shred_and_free_mp_int(&key->p);
	fs_mp_safe_shred_and_free_mp_int(&key->q);
	return t1;
}
#endif // #if SECURITY_ENABLE_RSA_KEY_LOAD_SHORTCUT

__FS_FUNCTION_PREFER_INLINE int fs_rsa_exptmod(const unsigned char *in,   unsigned long inlen, unsigned char *out,  unsigned long *outlen, fs_rsa_key *key) {
	__FS_LOCAL_STATIC_OPTION int fsv_t4;
	__FS_LOCAL_STATIC_OPTION fs_mp_int*    t1;
	__FS_LOCAL_STATIC_OPTION fs_mp_int*    t2;
	__FS_LOCAL_STATIC_OPTION fs_mp_int*    t3;
	/* init and copy into t1 */
	fsv_t4 = 0;
	fs_mp_alloc_and_init(&t1);
	fs_mp_alloc_and_init(&t2);
	fs_mp_alloc_and_init(&t3);
	if(!t1 || !t2 || !t3) {
		fsv_t4 = 1;
		goto error;
	}
	fs_mp_read_unsigned_bin(t1, (unsigned char *)in, (int)inlen);
	if (fs_mp_error) {
		fsv_t4 = 1;
		goto error;
	}

	/* sanity check on the input */
	if(fs_mp_cmp(key->N, t1) == -1) {
		fsv_t4 = 1;
		goto error;
	}
	/* exptmod it */
	fs_mp_exptmod(t1, key->e, key->N, t1);
	if(fs_mp_error) {
		fsv_t4 = 1;
		goto error;
	}

	/* read it back */
	if(fs_mp_unsigned_bin_size(key->N) > *outlen) {
		*outlen = fs_mp_unsigned_bin_size(key->N);
		fsv_t4 = 1;
		goto error;
	}
	*outlen = fs_mp_unsigned_bin_size(key->N);

	/* convert it */
	memset(out, 0, *outlen);
	fs_mp_to_unsigned_bin(t1, out+(*outlen - fs_mp_unsigned_bin_size(t1)));
	if(fs_mp_error) {
		goto error;
	}

	/* clean up and return */
	fsv_t4 = 0;
error:
	fs_mp_safe_shred_and_free_mp_int(&t1);
	fs_mp_safe_shred_and_free_mp_int(&t2);
	fs_mp_safe_shred_and_free_mp_int(&t3);
	return fsv_t4;
}


typedef struct rsa_verify_signature_data {
	unsigned long  modulus_bitlen;
	unsigned long  x;
	unsigned char* tmpbuf;
	/* LTC_PKCS #1 v1.5 decode it */
	unsigned char* out;
	unsigned long  outlen;
	unsigned long  loid[16];
	int            decoded;
	fs_asn1_list   digestinfo[2];
	fs_asn1_list   siginfo[2];
} rsa_verify_signature_data_t;

__FS_FUNCTION_PREFER_INLINE int fs_rsa_verify_signature(const unsigned char *sig, unsigned long siglen, const unsigned char *hash, unsigned long hashlen, fs_rsa_key *key) {
	__FS_LOCAL_STATIC_OPTION int t1;
	__FS_LOCAL_STATIC_OPTION rsa_verify_signature_data_t* t2;
	__FS_LOCAL_STATIC_OPTION unsigned long t3[9] = { 2, 16, 840, 1, 101, 3, 4, 2, 3 };

	t1 = 0;
	t2 = (rsa_verify_signature_data_t*)fs_zalloc(sizeof(rsa_verify_signature_data_t));
	if(NULL == t2) {
		t1 = 1;
		goto done;
	}
	/* get modulus len in bits */
	t2->modulus_bitlen = fs_mp_count_bits(key->N);

	/* outlen must be at least the size of the modulus */
	if(fs_mp_unsigned_bin_size(key->N) != siglen) {
		t1 = 1;
		goto done;
	}

	/* allocate temp buffer for decoded sig */
	t2->tmpbuf = (u_int8_t*)fs_zalloc(siglen);
	if(t2->tmpbuf == NULL) {
		t1 = 1;
		goto done;
	}

	/* RSA decode it  */
	t2->x = siglen;
	if((t1 = fs_rsa_exptmod(sig, siglen, t2->tmpbuf, &t2->x, key)) != 0) {
		goto done;
	}

	/* make sure the output is the right size */
	if(t2->x != siglen) {
		t1 = 1;
		goto done;
	}

	/* allocate temp buffer for decoded hash */
	t2->outlen = ((t2->modulus_bitlen >> 3) + (t2->modulus_bitlen & 7 ? 1 : 0)) - 3;
	t2->out    = (u_int8_t*)fs_zalloc(t2->outlen);
	if(t2->out == NULL) {
		t1 = 1;
		goto done;
	}

	if((t1 = fs_pkcs_1_v1_5_decode(t2->tmpbuf, t2->x, FS_PKCS_1_EMSA, t2->modulus_bitlen, t2->out, &t2->outlen, &t2->decoded)) != 0) {
		goto done;
	}

	/* now we must decode out[0...outlen-1] using ASN.1, test the OID and then test the hash */
	/* construct the SEQUENCE 
	  SEQUENCE {
	     SEQUENCE {hashoid OID
		       blah    NULL
	     }
	     hash    OCTET STRING 
	  }
       */
	FS_SET_ASN1(t2->digestinfo, 0, FS_ASN1_OBJECT_IDENTIFIER, t2->loid, sizeof(t2->loid)/sizeof(t2->loid[0]));
	FS_SET_ASN1(t2->digestinfo, 1, FS_ASN1_NULL,              NULL,                          0);
	FS_SET_ASN1(t2->siginfo,    0, FS_ASN1_SEQUENCE,          t2->digestinfo,                    2);
	FS_SET_ASN1(t2->siginfo,    1, FS_ASN1_OCTET_STRING,      t2->tmpbuf,                        siglen);

	if((t1 = fs_der_decode_sequence_ex(t2->out, t2->outlen, t2->siginfo, 2, 1)) != 0) {
		goto done;
	}

	/* test OID */
	if((t2->digestinfo[0].size != 9) ||
	   (memcmp(t2->digestinfo[0].data, t3, sizeof(unsigned long) * 9) != 0) ||
	   (t2->siginfo[1].size != hashlen) ||
	   (memcmp(t2->siginfo[1].data, hash, hashlen) != 0)) {
		t1 = 1;
		goto done;
	}

	done:
	fs_safe_shred_and_free(&t2->out, t2->outlen);
	fs_safe_shred_and_free(&t2->tmpbuf, siglen);
	fs_safe_shred_and_free(&t2, sizeof(*t2));
	return t1;
}
