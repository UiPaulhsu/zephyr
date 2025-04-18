__FS_FUNCTION_PREFER_INLINE int _fs_is_flash_security_format_recognized(void) {
        switch(fs_read_security_data_format_sec()) {
        CASE_SUPPORTED_FORMATS
                return 1;
        default: 
                return 0;
        }
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_flash_security_format(void) {
        switch(fs_read_security_data_format_sec()) {
        CASE_SUPPORTED_FORMATS
            break;
        default: 
            fs_failure(FS_FAILURE_fs_check_flash_security_format_1);
            break;
        }
}

__FS_FUNCTION_PREFER_INLINE int _fs_is_security_data_present(void) {
        switch(fs_read_security_data_format_sec()) {
        CASE_SUPPORTED_FORMATS
                return fs_read_subvendor_id_sec() == 0x0777;
        default:
                return 0;
        }
}

#define __fs_check_generic_sec_vs_hw(__type,__name_sec,__name_hw) do { \
        if(fs_read_ ## __name_sec ## _sec() != fs_read_ ## __name_hw ## _hw()) { \
                fs_failure(FS_FAILURE_fs_check_ ## __name_sec ## _sec_vs_ ## __name_hw ## _hw_1); \
        } \
    } while(0)

#define __fs_check_generic_sec_vs_bi(__type,__name_sec,__name_bi) do { \
        if(fs_read_ ## __name_sec ## _sec() != fs_read_ ## __name_bi ## _bi()) { \
                fs_failure(FS_FAILURE_fs_check_ ## __name_sec ## _sec_vs_ ## __name_bi ## _bi_1); \
        } \
    } while(0)

#define __fs_check_generic_sec_vs_fbd(__type,__name_sec,__name_fbd) do { \
        if(fs_read_ ## __name_sec ## _sec() != fs_read_ ## __name_fbd ## _fbd()) { \
                fs_failure(FS_FAILURE_fs_check_ ## __name_sec ## _sec_vs_ ## __name_fbd ## _fbd_1); \
        } \
    } while(0)


#define __fs_check_sec_array_vs_hw_array(__name_sec,__name_hw,__len) do { \
                u_int8_t __fs_check_generic_sec[__len]; \
                u_int8_t __fs_check_generic_hw[__len]; \
                fs_read_ ## __name_sec ## _sec( __fs_check_generic_sec, sizeof __fs_check_generic_sec ); \
                fs_read_ ## __name_hw ## _hw( __fs_check_generic_hw, sizeof __fs_check_generic_hw ); \
                if(memcmp( &__fs_check_generic_sec, &__fs_check_generic_hw, __len) != 0 \
                && memcmp( &__fs_check_generic_hw, fsv_mac_all_ones, __len) != 0) { \
                        fs_failure(FS_FAILURE_fs_check_ ## __name_sec ## _sec_vs_ ## __name_hw ## _hw_1); \
                } \
        } while(0)

#define __fs_check_sec_array_vs_fbd_array(__name_sec,__name_fbd,__len) do { \
                u_int8_t __fs_check_generic_sec[__len]; \
                u_int8_t __fs_check_generic_fbd[__len]; \
                fs_read_ ## __name_sec ## _sec( __fs_check_generic_sec, sizeof __fs_check_generic_sec ); \
                fs_read_ ## __name_fbd ## _fbd( __fs_check_generic_fbd, sizeof __fs_check_generic_fbd ); \
                if(memcmp( &__fs_check_generic_sec, &__fs_check_generic_fbd, __len) != 0) { \
                        fs_failure(FS_FAILURE_fs_check_ ## __name_sec ## _sec_vs_ ## __name_fbd ## _fbd_1); \
                } \
        } while(0)

#define __fs_check_sec_array_vs_bi_array(__name_sec,__name_bi,__len) do { \
        u_int8_t __fs_check_generic_sec[__len]; \
        u_int8_t __fs_check_generic_bi[__len]; \
        fs_read_ ## __name_sec ## _sec( __fs_check_generic_sec, sizeof __fs_check_generic_sec ); \
        fs_read_ ## __name_bi ## _bi( __fs_check_generic_bi, sizeof __fs_check_generic_bi ); \
        if(memcmp( &__fs_check_generic_sec,  &__fs_check_generic_bi, __len) != 0) { \
                fs_failure(FS_FAILURE_fs_check_ ## __name_sec ## _sec_vs_ ## __name_bi ## _bi_1); \
        } \
    } while(0)

__FS_FUNCTION_PREFER_INLINE void _fs_check_flash_type_id_sec_vs_hw(void)             { __fs_check_generic_sec_vs_hw(u_int32_t,flash_type_id,flash_type_id); }
#if SECURITY_ENABLE_INI_SUPPORT
__FS_FUNCTION_PREFER_INLINE void _fs_check_subsystem_id_sec_vs_system_id_bi(void)    { __fs_check_generic_sec_vs_bi(u_int16_t,subsystem_id,system_id); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_subvendor_id_sec_vs_vendor_id_bi(void)    { __fs_check_generic_sec_vs_bi(u_int16_t,subvendor_id,vendor_id); }
#endif // #if SECURITY_ENABLE_INI_SUPPORT
__FS_FUNCTION_PREFER_INLINE void _fs_check_subsystem_id_sec_vs_fbd(void)             { __fs_check_generic_sec_vs_fbd(u_int16_t,subsystem_id,subsystem_id); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_subvendor_id_sec_vs_fbd(void)             { __fs_check_generic_sec_vs_fbd(u_int16_t,subvendor_id,subvendor_id); }

#if SECURITY_ENABLE_MAC_ADDRESS_SUPPORT
__FS_FUNCTION_PREFER_INLINE void _fs_check_eth0_mac_address_sec_vs_fbd(void)         { __fs_check_sec_array_vs_fbd_array(eth0_mac_address,eth0_mac_address,MAC_ADDRESS_SIZE); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_eth1_mac_address_sec_vs_fbd(void)         { __fs_check_sec_array_vs_fbd_array(eth1_mac_address,eth1_mac_address,MAC_ADDRESS_SIZE); }
__FS_FUNCTION_PREFER_INLINE void _fs_check_eth0_mac_address_sec_vs_hw(void)          { __fs_check_sec_array_vs_hw_array(eth0_mac_address,eth0_mac_address,MAC_ADDRESS_SIZE); }
#endif // #if SECURITY_ENABLE_MAC_ADDRESS_SUPPORT

#if SECURITY_LOW_MEMORY

static /* do not inline */ void fs_eeprom_reader(void* fsa_dest, size_t fsa_dest_len, uintptr_t fsa_address, size_t fsa_length) {
    fs_read_config(fsa_dest, fsa_dest_len,fsa_address, fsa_length);
}

__FS_FUNCTION_PREFER_INLINE void fs_sha512_sha512_sec(u_int8_t* dest, size_t dest_length, u_int32_t eeprom_offset, u_int32_t num_bytes_to_be_hashed) { 
    memset(dest , 0, dest_length);
    if(0 == num_bytes_to_be_hashed) {
        fs_failure( FS_FAILURE_fs_sha512_sha512_sec_1 );
    } else {
        fs_sha512_incremental(fs_eeprom_reader, eeprom_offset, num_bytes_to_be_hashed, dest);
        fs_sha512(dest, dest_length, dest);
    }
}

#else // #if SECURITY_LOW_MEMORY

__FS_FUNCTION_PREFER_INLINE void fs_sha512_sha512(u_int8_t* dest, size_t dest_length, u_int8_t* bytes_to_hash, u_int32_t num_bytes_to_be_hashed) {
        memset(dest , 0, dest_length);
        if(0 == num_bytes_to_be_hashed) {
            fs_failure( FS_FAILURE_fs_sha512_sha512_1 );
        } else {
            fs_sha512(bytes_to_hash, num_bytes_to_be_hashed, dest);
            fs_sha512(dest, dest_length, dest);
        }
}

__FS_FUNCTION_PREFER_INLINE void fs_sha512_sha512_sec(u_int8_t* dest, size_t dest_length, u_int32_t eeprom_offset, u_int32_t num_bytes_to_be_hashed) { 
        __FS_LOCAL_STATIC_OPTION u_int8_t* fsv_t1;
        memset(dest, 0, dest_length);
        fsv_t1 = (u_int8_t*)fs_zalloc(num_bytes_to_be_hashed);
        if(!fsv_t1) {
            fs_failure( FS_FAILURE_fs_sha512_sha512_sec_1 );
        } else if(0 == num_bytes_to_be_hashed) {
            fs_failure( FS_FAILURE_fs_sha512_sha512_sec_2 );
        } else {
            fs_read_config(fsv_t1, num_bytes_to_be_hashed, (uintptr_t)eeprom_offset, num_bytes_to_be_hashed);
            fs_sha512_sha512(dest, dest_length, fsv_t1, num_bytes_to_be_hashed);
            fs_safe_shred_and_free(&fsv_t1, num_bytes_to_be_hashed);
        }
}

#endif // #if SECURITY_LOW_MEMORY

__FS_FUNCTION_PREFER_INLINE void fs_compute_ubnt_hash(u_int8_t* dest, size_t dest_len) {
        __FS_LOCAL_STATIC_OPTION uintptr_t fsv_t1;
        __FS_LOCAL_STATIC_OPTION uintptr_t fsv_t2;
        memset(dest, 0, dest_len);
        switch(fs_read_security_data_format_sec()) {
        CASE_SUPPORTED_FORMATS
            fsv_t1 = fs_get_config_offset_ubnt_signed_start();
            fsv_t2 = fs_get_config_offset_ubnt_signed_end();
            fs_sha512_sha512_sec(dest, dest_len, fsv_t1, fsv_t2 - fsv_t1 );
            break;
        default:
            fs_failure(FS_FAILURE_fs_compute_ubnt_hash_1);
            break;
        }
}

#if SECURITY_ENABLE_ESN_SIGNATURE_CHECKS
__FS_FUNCTION_PREFER_INLINE void fs_compute_esn_hash(u_int8_t* dest, size_t dest_len) {
        __FS_LOCAL_STATIC_OPTION uintptr_t fsv_t1;
        __FS_LOCAL_STATIC_OPTION uintptr_t fsv_t2;
        memset(dest, 0, dest_len);
        switch(fs_read_security_data_format_sec()) {
        CASE_SUPPORTED_FORMATS
            fsv_t1 = fs_get_config_offset_esn_signed_start();
            fsv_t2 = fs_get_config_offset_esn_signed_end();
            fs_sha512_sha512_sec(dest, dest_len, fsv_t1, fsv_t2 - fsv_t1 );
            break;
        default:
            fs_failure(FS_FAILURE_fs_compute_esn_hash_1);
            break;
        }
}
#endif // #if SECURITY_ENABLE_ESN_SIGNATURE_CHECKS

typedef struct _fs_check_ubnt_signature_data {
        u_int8_t    signature[RSA_SIGNATURE_SIZE];
        u_int8_t    digest[SHA512_HASH_SIZE];
        fs_rsa_key  public_key;
#if defined(SECURITY_ENABLE_TEST_RSA_KEY) && SECURITY_ENABLE_TEST_RSA_KEY
        fs_rsa_key  test_public_key;
#endif // #if defined(SECURITY_ENABLE_TEST_RSA_KEY) && SECURITY_ENABLE_TEST_RSA_KEY
} _fs_check_ubnt_signature_data_t;

__FS_FUNCTION_PREFER_INLINE void _fs_check_ubnt_signature(void) {
        __FS_LOCAL_STATIC_OPTION _fs_check_ubnt_signature_data_t* fsv_t1;
        fsv_t1 = (_fs_check_ubnt_signature_data_t*)fs_zalloc(sizeof(_fs_check_ubnt_signature_data_t));
        if (NULL == fsv_t1) {
                goto done;
        }
        fs_read_ubnt_signature_sec(fsv_t1->signature, sizeof fsv_t1->signature);
        fs_compute_ubnt_hash(fsv_t1->digest, sizeof fsv_t1->digest);
        if(0 != fs_rsa_load_public_key(&fsv_t1->public_key)) {
                fs_failure( FS_FAILURE_fs_check_ubnt_signature_2 );
        }
#if defined(SECURITY_ENABLE_TEST_RSA_KEY) && SECURITY_ENABLE_TEST_RSA_KEY
        if(0 != fs_rsa_load_test_public_key(&fsv_t1->test_public_key)) {
                fs_failure( FS_FAILURE_fs_check_ubnt_signature_3 );
        }
#endif // #if defined(SECURITY_ENABLE_TEST_RSA_KEY) && SECURITY_ENABLE_TEST_RSA_KEY
#if 0
        fs_debug_printf("\n==================================\n");
        fs_debug_printf("PK:\n");
        fs_debug_printf("type=%d\n",p_data->public_key.type);
        fs_debug_printf("e" , p_data->public_key.e);
        fs_debug_printf("d" , p_data->public_key.d);
        fs_debug_printf("N" , p_data->public_key.N);
        fs_debug_printf("p" , p_data->public_key.p);
        fs_debug_printf("q" , p_data->public_key.q);
        fs_debug_printf("qP", p_data->public_key.qP);
        fs_debug_printf("dP", p_data->public_key.dP);
        fs_debug_printf("dQ", p_data->public_key.dQ);
        fs_debug_printf("\n==================================\n");
#endif
        if(0 != fs_rsa_verify_signature(fsv_t1->signature, sizeof fsv_t1->signature, fsv_t1->digest, sizeof fsv_t1->digest, &fsv_t1->public_key)) {
#if defined(SECURITY_ENABLE_TEST_RSA_KEY) && SECURITY_ENABLE_TEST_RSA_KEY
            if(0 == fs_rsa_verify_signature(fsv_t1->signature, sizeof fsv_t1->signature, fsv_t1->digest, sizeof fsv_t1->digest, &fsv_t1->test_public_key)) {
                fs_debug_printf("WARNING: This device was signed with a test key!\n");
            } else 
#endif // #if defined(SECURITY_ENABLE_TEST_RSA_KEY) && SECURITY_ENABLE_TEST_RSA_KEY
            fs_failure( FS_FAILURE_fs_check_ubnt_signature_1 );
        }
done:
        fs_release_public_key(&fsv_t1->public_key);
#if defined(SECURITY_ENABLE_TEST_RSA_KEY) && SECURITY_ENABLE_TEST_RSA_KEY
        fs_release_public_key(&fsv_t1->test_public_key);
#endif // #if defined(SECURITY_ENABLE_TEST_RSA_KEY) && SECURITY_ENABLE_TEST_RSA_KEY
        fs_safe_shred_and_free(&fsv_t1, sizeof(*fsv_t1));
}

#if SECURITY_ENABLE_ESN_SIGNATURE_CHECKS
typedef struct _fs_check_esn_signature_data {
        u_int8_t buf[MAX_EEPROM_SIZE];
        u_int8_t digest[SHA512_HASH_SIZE];
        u_int8_t decrypted_digest[SHA512_HASH_SIZE];
        u_int8_t uid_length;
        size_t   pwlen;
} _fs_check_esn_signature_data_t;

__FS_FUNCTION_PREFER_INLINE void _fs_check_esn_signature(void) {
        __FS_LOCAL_STATIC_OPTION _fs_check_esn_signature_data_t* fsv_t1;
        fsv_t1 = (_fs_check_esn_signature_data_t*)fs_zalloc(sizeof(_fs_check_esn_signature_data_t));
        if (NULL == fsv_t1) {
                goto done;
        }
        fs_read_config(fsv_t1->buf, sizeof fsv_t1->buf, (uintptr_t)0, fs_get_config_size());
        fs_compute_esn_hash(fsv_t1->digest, sizeof fsv_t1->digest);
        fsv_t1->uid_length = fs_read_flash_uid_length_sec();
        fsv_t1->pwlen = (fsv_t1->uid_length < 56 ) ? fsv_t1->uid_length : 56;
        if(0 != fs_blowfish_decrypt(&fsv_t1->buf[fs_get_config_offset_esn_sig_iv_area_sec()], &fsv_t1->buf[fs_get_config_offset_flash_uid_sec() + fsv_t1->uid_length - fsv_t1->pwlen], fsv_t1->pwlen, &fsv_t1->buf[fs_get_config_offset_esn_signature_sec()], fsv_t1->decrypted_digest,  sizeof	fsv_t1->decrypted_digest))	{
                fs_failure(FS_FAILURE_fs_check_esn_signature_1);
        }
        if(0 != memcmp(fsv_t1->decrypted_digest, fsv_t1->digest, sizeof fsv_t1->digest)) {
                fs_failure(FS_FAILURE_fs_check_esn_signature_2);
        }
done:
        fs_safe_shred_and_free(&fsv_t1, sizeof(*fsv_t1));
}
#else // #if SECURITY_ENABLE_ESN_SIGNATURE_CHECKS
#undef _fs_check_esn_signature
#define _fs_check_esn_signature(...)
#endif // #if SECURITY_ENABLE_ESN_SIGNATURE_CHECKS

__FS_FUNCTION_PREFER_INLINE int fs_is_security_data_present(void) {
        // NB: ignore failure here
        int ret = 0;
        fs_output_off();
        ret = _fs_is_security_data_present();
        fs_output_on();
        return ret;
}

__FS_FUNCTION_UNCONDITIONALLY_FORCED_INLINE int fs_is_flash_security_format_recognized(void) { 
        // NB: ignore failure here
        int ret = 0;
        fs_output_off();
        ret = _fs_is_flash_security_format_recognized();
        fs_output_on();
        return ret;
}

__FS_FUNCTION_PREFER_INLINE void _fs_check_pcba_sec_vs_fbd(void) {
    /* 
    NB: On boards with security data format without a 4-byte PCBA field, both fs_read_pcba_sec and fs_read_pcba_fbd will return 0. 
    NB: WARNING: We will not do a comparison if we do not believe flash board data has a 4-byte PCBA field, even though this is 
        made redundant by the fact that both fs_read_pcba_sec and fs_read_pcba_fbd will return 0 and comparison would always succeed.
        It is made explicit partly as a way to document the point.
    */
    if(fs_get_config_offset_pcba_sec()) {
        __fs_check_generic_sec_vs_fbd(u_int32_t,pcba,pcba);
    }
}

