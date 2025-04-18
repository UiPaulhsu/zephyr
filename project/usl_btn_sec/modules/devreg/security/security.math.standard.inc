#define FS_MP_PREC       32
typedef u_int32_t fs_mp_digit;
typedef u_int64_t fs_mp_word;
#define DIGIT_BIT 28

typedef struct {
	int          used;
	int          alloc;
	int          sign;
	fs_mp_digit* dp;
} fs_mp_int;

typedef struct fs_mp_data {
	int             fs_mp_error;
	fs_mp_int*      fs_mp_zero_a1;
	int             fs_mp_zero_t1;
	fs_mp_digit*    fs_mp_zero_t2;
	fs_mp_int*      fs_mp_clear_a1;
	int             fs_mp_clear_t1;
	fs_mp_int**     fs_mp_safe_shred_and_free_mp_int_a1;
	int             fs_mp_safe_shred_and_free_mp_int_t1;
	fs_mp_int*      fs_mp_count_bits_a1;
	fs_mp_digit     fs_mp_count_bits_t1;
	int             fs_mp_count_bits_r;
	fs_mp_int*      fs_mp_init_a1;
	int             fs_mp_init_t1;
	fs_mp_int**     fs_mp_alloc_and_init_a1;
	fs_mp_int*      fs_mp_unsigned_bin_size_a1;
	size_t          fs_mp_unsigned_bin_size_r;
	fs_mp_int*      fs_mp_cnt_lsb_a1;
	fs_mp_digit     fs_mp_cnt_lsb_t1;
	fs_mp_digit     fs_mp_cnt_lsb_t2;
	int             fs_mp_cnt_lsb_r;
	fs_mp_int*      fs_mp_grow_a1;
	int             fs_mp_grow_a2;
	fs_mp_digit*    fs_mp_grow_t1;
	int             fs_mp_grow_t2;
	fs_mp_int*      fs_mp_copy_a1;
	fs_mp_int*      fs_mp_copy_a2;
	fs_mp_digit*    fs_mp_copy_t1;
	fs_mp_digit*    fs_mp_copy_t2;
	int             fs_mp_copy_t3;
	fs_mp_int*      fs_mp_2expt_a1;
	int             fs_mp_2expt_a2;
	fs_mp_int*      fs_mp_clamp_a1;
	fs_mp_int*      fs_mp_abs_a1;
	fs_mp_int*      fs_mp_abs_a2;
	fs_mp_int*      fs_mp_rshd_a1;
	int             fs_mp_rshd_a2;
	int             fs_mp_rshd_t1;
	fs_mp_digit*    fs_mp_rshd_t2;
	fs_mp_digit*    fs_mp_rshd_t3;
	fs_mp_int*      fs_mp_lshd_a1;
	int             fs_mp_lshd_a2;
	int             fs_mp_lshd_t1;
	fs_mp_digit*    fs_mp_lshd_t2;
	fs_mp_digit*    fs_mp_lshd_t3;
	fs_mp_int*      fs_mp_mul_2d_a1;
	int             fs_mp_mul_2d_a2;
	fs_mp_int*      fs_mp_mul_2d_a3;
	fs_mp_digit     fs_mp_mul_2d_t1;
	int             fs_mp_mul_2d_t2;
	fs_mp_digit*    fs_mp_mul_2d_t3;
	fs_mp_digit     fs_mp_mul_2d_t4;
	fs_mp_digit     fs_mp_mul_2d_t5;
	fs_mp_digit     fs_mp_mul_2d_t6;
	fs_mp_digit     fs_mp_mul_2d_t7;
	fs_mp_int*      fs_mp_read_unsigned_bin_a1;
	const u_int8_t* fs_mp_read_unsigned_bin_a2;
	int             fs_mp_read_unsigned_bin_a3;
	fs_mp_int*      fs_mp_s_sub_a1;
	fs_mp_int*      fs_mp_s_sub_a2;
	fs_mp_int*      fs_mp_s_sub_a3;
	int             fs_mp_s_sub_t1;
	int             fs_mp_s_sub_t2;
	int             fs_mp_s_sub_t3;
	fs_mp_digit     fs_mp_s_sub_t4;
	fs_mp_digit*    fs_mp_s_sub_t5;
	fs_mp_digit*    fs_mp_s_sub_t6;
	fs_mp_digit*    fs_mp_s_sub_t7;
	int             fs_mp_s_sub_t8;
	fs_mp_int*      fs_mp_s_add_a1;
	fs_mp_int*      fs_mp_s_add_a2;
	fs_mp_int*      fs_mp_s_add_a3;
	fs_mp_int*      fs_mp_s_add_t1;
	int             fs_mp_s_add_t2;
	int             fs_mp_s_add_t3;
	int             fs_mp_s_add_t4;
	fs_mp_digit     fs_mp_s_add_t5;
	fs_mp_digit*    fs_mp_s_add_t6;
	fs_mp_digit*    fs_mp_s_add_t7;
	fs_mp_digit*    fs_mp_s_add_t8;
	int             fs_mp_s_add_t9;
	fs_mp_int*      fs_mp_set_a1;
	fs_mp_digit     fs_mp_set_a2;
	fs_mp_int*      fs_mp_cmp_mag_a1;
	fs_mp_int*      fs_mp_cmp_mag_a2;
	int             fs_mp_cmp_mag_t1;
	int             fs_mp_cmp_mag_r;
	fs_mp_digit*    fs_mp_cmp_mag_t2;
	fs_mp_digit*    fs_mp_cmp_mag_t3;
	fs_mp_int*      fs_mp_sub_a1;
	fs_mp_int*      fs_mp_sub_a2;
	fs_mp_int*      fs_mp_sub_a3;
	int             fs_mp_sub_t1;
	int             fs_mp_sub_t2;
	fs_mp_int*      fs_mp_add_a1;
	fs_mp_int*      fs_mp_add_a2;
	fs_mp_int*      fs_mp_add_a3;
	int             fs_mp_add_t1;
	int             fs_mp_add_t2;
	fs_mp_int*      fs_mp_mod_2d_a1;
	int             fs_mp_mod_2d_a2;
	fs_mp_int*      fs_mp_mod_2d_a3;
	int             fs_mp_mod_2d_t1;
	fs_mp_int*      fs_mp_exch_a1;
	fs_mp_int*      fs_mp_exch_a2;
	fs_mp_int       fs_mp_exch_t1;
	fs_mp_int*      fs_mp_init_copy_a1;
	fs_mp_int*      fs_mp_init_copy_a2;
	fs_mp_int*      fs_mp_div_2d_a1;
	int             fs_mp_div_2d_a2;
	fs_mp_int*      fs_mp_div_2d_a3;
	fs_mp_int*      fs_mp_div_2d_a4;
	fs_mp_digit     fs_mp_div_2d_t1;
	fs_mp_digit     fs_mp_div_2d_t2;
	fs_mp_digit     fs_mp_div_2d_t3;
	fs_mp_digit*    fs_mp_div_2d_t4;
	fs_mp_int       fs_mp_div_2d_t5;
	int             fs_mp_div_2d_t6;
	fs_mp_digit     fs_mp_div_2d_t7;
	fs_mp_digit     fs_mp_div_2d_t8;
	fs_mp_int*      fs_mp_to_unsigned_bin_a1;
	unsigned char*  fs_mp_to_unsigned_bin_a2;
	int             fs_mp_to_unsigned_bin_t1;
	int             fs_mp_to_unsigned_bin_t2;
	unsigned char   fs_mp_to_unsigned_bin_t3;
	int             fs_mp_to_unsigned_bin_t4;
	fs_mp_int       fs_mp_to_unsigned_bin_t5;
	fs_mp_int*      fs_mp_cmp_a1;
	fs_mp_int*      fs_mp_cmp_a2;
	int             fs_mp_cmp_r;
	fs_mp_int*      fs_mp_div_a1;
	fs_mp_int*      fs_mp_div_a2;
	fs_mp_int*      fs_mp_div_a3;
	fs_mp_int*      fs_mp_div_a4;
	fs_mp_int       fs_mp_div_t1;
	fs_mp_int       fs_mp_div_t2;
	fs_mp_int       fs_mp_div_t3;
	fs_mp_int       fs_mp_div_t4;
	int             fs_mp_div_t5;
	int             fs_mp_div_t6;
	fs_mp_int*      fs_mp_reduce_setup_a1;
	fs_mp_int*      fs_mp_reduce_setup_a2;
	fs_mp_int*      fs_mp_cmp_d_a1;
	fs_mp_digit     fs_mp_cmp_d_a2;
	int             fs_mp_cmp_d_r;
	fs_mp_int*      fs_mp_mod_a1;
	fs_mp_int*      fs_mp_mod_a2;
	fs_mp_int*      fs_mp_mod_a3;
	fs_mp_int       fs_mp_mod_t1;
	fs_mp_int*      fs_mp_div_2_a1;
	fs_mp_int*      fs_mp_div_2_a2;
	int             fs_mp_div_2_t1;
	int             fs_mp_div_2_t2;
	fs_mp_digit     fs_mp_div_2_t3;
	fs_mp_digit     fs_mp_div_2_t4;
	fs_mp_digit*    fs_mp_div_2_t5;
	fs_mp_digit*    fs_mp_div_2_t6;
	fs_mp_int*      fs_mp_invmod_a1;
	fs_mp_int*      fs_mp_invmod_a2;
	fs_mp_int*      fs_mp_invmod_a3;
	fs_mp_int       fs_mp_invmod_t1;
	fs_mp_int       fs_mp_invmod_t2;
	fs_mp_int       fs_mp_invmod_t3;
	fs_mp_int       fs_mp_invmod_t4;
	fs_mp_int       fs_mp_invmod_t5;
	fs_mp_int       fs_mp_invmod_t6;
	fs_mp_int       fs_mp_invmod_t7;
	fs_mp_int       fs_mp_invmod_t8;
	fs_mp_int*      fs_mp_fast_s_mul_digs_a1;
	fs_mp_int*      fs_mp_fast_s_mul_digs_a2;
	fs_mp_int*      fs_mp_fast_s_mul_digs_a3;
	int             fs_mp_fast_s_mul_digs_a4;
	int             fs_mp_fast_s_mul_digs_t1;
	int             fs_mp_fast_s_mul_digs_t2;
	int             fs_mp_fast_s_mul_digs_t3;
	int             fs_mp_fast_s_mul_digs_t4;
	fs_mp_digit     fs_mp_fast_s_mul_digs_t5[(1 << (sizeof(fs_mp_word) * 8 - 2 * DIGIT_BIT + 1))];
	fs_mp_word      fs_mp_fast_s_mul_digs_t6;
	int             fs_mp_fast_s_mul_digs_t7;
	int             fs_mp_fast_s_mul_digs_t8;
	int             fs_mp_fast_s_mul_digs_t9;
	fs_mp_digit*    fs_mp_fast_s_mul_digs_t10;
	fs_mp_digit*    fs_mp_fast_s_mul_digs_t11;
	fs_mp_digit*    fs_mp_fast_s_mul_digs_t12;
	fs_mp_int*      fs_mp_init_size_a1;
	int             fs_mp_init_size_a2;
	int             fs_mp_init_size_t1;
	fs_mp_int*      fs_mp_s_mul_digs_a1;
	fs_mp_int*      fs_mp_s_mul_digs_a2;
	fs_mp_int*      fs_mp_s_mul_digs_a3;
	int             fs_mp_s_mul_digs_a4;
	fs_mp_int       fs_mp_s_mul_digs_t1;
	int             fs_mp_s_mul_digs_t2;
	int             fs_mp_s_mul_digs_t3;
	int             fs_mp_s_mul_digs_t4;
	int             fs_mp_s_mul_digs_t5;
	fs_mp_digit     fs_mp_s_mul_digs_t6;
	fs_mp_word      fs_mp_s_mul_digs_t7;
	fs_mp_digit     fs_mp_s_mul_digs_t8;
	fs_mp_digit*    fs_mp_s_mul_digs_t9;
	fs_mp_digit*    fs_mp_s_mul_digs_t10;
	fs_mp_int*      fs_mp_mul_a1;
	fs_mp_int*      fs_mp_mul_a2;
	fs_mp_int*      fs_mp_mul_a3;
	int             fs_mp_mul_t1;
	fs_mp_int*      fs_mp_s_mul_high_digs_a1;
	fs_mp_int*      fs_mp_s_mul_high_digs_a2;
	fs_mp_int*      fs_mp_s_mul_high_digs_a3;
	int             fs_mp_s_mul_high_digs_a4;
	fs_mp_int       fs_mp_s_mul_high_digs_t1;
	int             fs_mp_s_mul_high_digs_t2;
	int             fs_mp_s_mul_high_digs_t3;
	int             fs_mp_s_mul_high_digs_t4;
	int             fs_mp_s_mul_high_digs_t5;
	fs_mp_digit     fs_mp_s_mul_high_digs_t6;
	fs_mp_word      fs_mp_s_mul_high_digs_t7;
	fs_mp_digit     fs_mp_s_mul_high_digs_t10;
	fs_mp_digit*    fs_mp_s_mul_high_digs_t8;
	fs_mp_digit*    fs_mp_s_mul_high_digs_t9;
	fs_mp_int*      fs_mp_reduce_a1;
	fs_mp_int*      fs_mp_reduce_a2;
	fs_mp_int*      fs_mp_reduce_a3;
	fs_mp_int       fs_mp_reduce_t1;
	int             fs_mp_reduce_t2;
	fs_mp_int*      fs_mp_sqr_a1;
	fs_mp_int*      fs_mp_sqr_a2;
	fs_mp_int       fs_mp_sqr_t1;
	int             fs_mp_sqr_t2;
	int             fs_mp_sqr_t3;
	int             fs_mp_sqr_t4;
	fs_mp_word      fs_mp_sqr_t5;
	fs_mp_digit     fs_mp_sqr_t6;
	fs_mp_digit     fs_mp_sqr_t7;
	fs_mp_digit*    fs_mp_sqr_t8;
	fs_mp_int*      fs_mp_reduce_2k_l_a1;
	fs_mp_int*      fs_mp_reduce_2k_l_a2;
	fs_mp_int*      fs_mp_reduce_2k_l_a3;
	fs_mp_int       fs_mp_reduce_2k_l_t1;
	fs_mp_int*      fs_mp_reduce_2k_setup_a1;
	fs_mp_digit*    fs_mp_reduce_2k_setup_a2;
	fs_mp_int       fs_mp_reduce_2k_setup_t1;
	fs_mp_int*      fs_mp_reduce_2k_setup_l_a1;
	fs_mp_int*      fs_mp_reduce_2k_setup_l_a2;
	fs_mp_int       fs_mp_reduce_2k_setup_l_t1;
	fs_mp_int*      fs_mp_s_exptmod_a1;
	fs_mp_int*      fs_mp_s_exptmod_a2;
	fs_mp_int*      fs_mp_s_exptmod_a3;
	fs_mp_int*      fs_mp_s_exptmod_a4;
	int             fs_mp_s_exptmod_a5;
	fs_mp_int       fs_mp_s_exptmod_t1[16];
	fs_mp_int       fs_mp_s_exptmod_t2;
	fs_mp_int       fs_mp_s_exptmod_t3;
	fs_mp_digit     fs_mp_s_exptmod_t4;
	int             fs_mp_s_exptmod_t5;
	int             fs_mp_s_exptmod_t6;
	int             fs_mp_s_exptmod_t7;
	int             fs_mp_s_exptmod_t8;
	int             fs_mp_s_exptmod_t9;
	int             fs_mp_s_exptmod_t10;
	int             fs_mp_s_exptmod_t11;
	int             fs_mp_s_exptmod_t12;
	int             fs_mp_s_exptmod_t13;
	fs_mp_int*      fs_mp_dr_is_modulus_a1;
	int             fs_mp_dr_is_modulus_t1;
	int             fs_mp_dr_is_modulus_r;
	fs_mp_int*      fs_mp_reduce_is_2k_a1;
	int             fs_mp_reduce_is_2k_t1;
	int             fs_mp_reduce_is_2k_t2;
	fs_mp_digit     fs_mp_reduce_is_2k_t3;
	int             fs_mp_reduce_is_2k_r;
	fs_mp_int*      fs_mp_montgomery_setup_a1;
	fs_mp_digit*    fs_mp_montgomery_setup_a2;
	fs_mp_digit     fs_mp_montgomery_setup_t1;
	fs_mp_digit     fs_mp_montgomery_setup_t2;
	fs_mp_int*      fs_mp_xxx_reduce_a1;
	fs_mp_int*      fs_mp_xxx_reduce_a2;
	fs_mp_digit     fs_mp_xxx_reduce_a3;
	int             fs_mp_fast_montgomery_reduce_t1;
	int             fs_mp_fast_montgomery_reduce_t2;
	fs_mp_word      fs_mp_fast_montgomery_reduce_t3[(1 << (sizeof(fs_mp_word) * 8 - 2 * DIGIT_BIT + 1))];
	fs_mp_digit     fs_mp_fast_montgomery_reduce_t4;
	fs_mp_word*     fs_mp_fast_montgomery_reduce_t5;
	fs_mp_digit*    fs_mp_fast_montgomery_reduce_t6;
	int             fs_mp_fast_montgomery_reduce_t7;
	fs_mp_digit*    fs_mp_fast_montgomery_reduce_t8;
	fs_mp_word*     fs_mp_fast_montgomery_reduce_t9;
	int             fs_mp_montgomery_reduce_t1;
	int             fs_mp_montgomery_reduce_t2;
	fs_mp_digit     fs_mp_montgomery_reduce_t3;
	int             fs_mp_montgomery_reduce_t4;
	fs_mp_digit*    fs_mp_montgomery_reduce_t5;
	fs_mp_digit*    fs_mp_montgomery_reduce_t6;
	fs_mp_digit     fs_mp_montgomery_reduce_t7;
	fs_mp_word      fs_mp_montgomery_reduce_t8;
	int             fs_mp_dr_reduce_t1;
	int             fs_mp_dr_reduce_t2;
	fs_mp_word      fs_mp_dr_reduce_t3;
	fs_mp_digit*    fs_mp_dr_reduce_t4;
	fs_mp_digit*    fs_mp_dr_reduce_t5;
	fs_mp_digit     fs_mp_dr_reduce_t6;
	fs_mp_int*      fs_mp_mul_d_a1;
	fs_mp_digit     fs_mp_mul_d_a2;
	fs_mp_int*      fs_mp_mul_d_a3;
	fs_mp_digit     fs_mp_mul_d_t1;
	fs_mp_digit*    fs_mp_mul_d_t2;
	fs_mp_digit*    fs_mp_mul_d_t3;
	fs_mp_word      fs_mp_mul_d_t4;
	int             fs_mp_mul_d_t5;
	int             fs_mp_mul_d_t6;
	fs_mp_int       fs_mp_reduce_2k_t1;
	fs_mp_int*      fs_mp_mul_2_a1;
	fs_mp_int*      fs_mp_mul_2_a2;
	int             fs_mp_mul_2_t1;
	int             fs_mp_mul_2_t2;
	fs_mp_digit     fs_mp_mul_2_t3;
	fs_mp_digit     fs_mp_mul_2_t4;
	fs_mp_digit*    fs_mp_mul_2_t5;
	fs_mp_digit*    fs_mp_mul_2_t6;
	fs_mp_int*      fs_mp_montgomery_calc_normalization_a1;
	fs_mp_int*      fs_mp_montgomery_calc_normalization_a2;
	int             fs_mp_montgomery_calc_normalization_t1;
	int             fs_mp_montgomery_calc_normalization_t2;
	fs_mp_int*      fs_mp_exptmod_fast_a1;
	fs_mp_int*      fs_mp_exptmod_fast_a2;
	fs_mp_int*      fs_mp_exptmod_fast_a3;
	fs_mp_int*      fs_mp_exptmod_fast_a4;
	int             fs_mp_exptmod_fast_a5;
	fs_mp_int       fs_mp_exptmod_fast_t1;
	fs_mp_int       fs_mp_exptmod_fast_t2[256];
	fs_mp_digit     fs_mp_exptmod_fast_t3;
	fs_mp_digit     fs_mp_exptmod_fast_t4;
	int             fs_mp_exptmod_fast_t5;
	int             fs_mp_exptmod_fast_t6;
	int             fs_mp_exptmod_fast_t7;
	int             fs_mp_exptmod_fast_t8;
	int             fs_mp_exptmod_fast_t9;
	int             fs_mp_exptmod_fast_t10;
	int             fs_mp_exptmod_fast_t11;
	int             fs_mp_exptmod_fast_t12;
	int             fs_mp_exptmod_fast_t13;
	fs_mp_int       fs_mp_exptmod_fast_t14;
	fs_mp_int*      fs_mp_exptmod_a1;
	fs_mp_int*      fs_mp_exptmod_a2;
	fs_mp_int*      fs_mp_exptmod_a3;
	fs_mp_int*      fs_mp_exptmod_a4;
	int             fs_mp_exptmod_t1;
	fs_mp_int       fs_mp_exptmod_t2;
	fs_mp_int       fs_mp_exptmod_t3;
	int             fs_mp_exptmod_t4;
	int             fs_mp_exptmod_t5;
	int             fs_mp_exptmod_t6;
} fs_mp_data_t;

static fs_mp_data_t fsv_mp_globals;
__FS_FUNCTION_MAYBE_INLINE void fs_mp_zero(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_zero_a1->sign = fsv_mp_globals.fs_mp_zero_a1->used = 0;
	fsv_mp_globals.fs_mp_zero_t2 = fsv_mp_globals.fs_mp_zero_a1->dp;
	for(fsv_mp_globals.fs_mp_zero_t1 = 0; fsv_mp_globals.fs_mp_zero_t1 < fsv_mp_globals.fs_mp_zero_a1->alloc; fsv_mp_globals.fs_mp_zero_t1++) {
		*fsv_mp_globals.fs_mp_zero_t2++ = 0;
	}
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_clear(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_clear_t1 = 0;
	if(fsv_mp_globals.fs_mp_clear_a1->dp != NULL) {
		for(fsv_mp_globals.fs_mp_clear_t1 = 0; fsv_mp_globals.fs_mp_clear_t1 < fsv_mp_globals.fs_mp_clear_a1->used; fsv_mp_globals.fs_mp_clear_t1++) {
			fsv_mp_globals.fs_mp_clear_a1->dp[fsv_mp_globals.fs_mp_clear_t1] = 0;
		}
		fs_safe_shred_and_free(&fsv_mp_globals.fs_mp_clear_a1->dp, fsv_mp_globals.fs_mp_clear_a1->alloc * sizeof(*fsv_mp_globals.fs_mp_clear_a1->dp));
		fsv_mp_globals.fs_mp_clear_a1->dp = NULL;
		fsv_mp_globals.fs_mp_clear_a1->alloc = fsv_mp_globals.fs_mp_clear_a1->used = fsv_mp_globals.fs_mp_clear_a1->sign = 0;
	}
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_safe_shred_and_free_mp_int(void) {
	fsv_mp_globals.fs_mp_error = 0;
	if(fsv_mp_globals.fs_mp_safe_shred_and_free_mp_int_a1 != NULL) {
		if((*fsv_mp_globals.fs_mp_safe_shred_and_free_mp_int_a1) != NULL) {
			fsv_mp_globals.fs_mp_safe_shred_and_free_mp_int_t1 = 0;
			if((*fsv_mp_globals.fs_mp_safe_shred_and_free_mp_int_a1)->dp != NULL) {
				for(fsv_mp_globals.fs_mp_safe_shred_and_free_mp_int_t1 = 0; fsv_mp_globals.fs_mp_safe_shred_and_free_mp_int_t1 < (*fsv_mp_globals.fs_mp_safe_shred_and_free_mp_int_a1)->used; fsv_mp_globals.fs_mp_safe_shred_and_free_mp_int_t1++) {
					(*fsv_mp_globals.fs_mp_safe_shred_and_free_mp_int_a1)->dp[fsv_mp_globals.fs_mp_safe_shred_and_free_mp_int_t1] = 0;
				}
				fs_safe_shred_and_free(&(*fsv_mp_globals.fs_mp_safe_shred_and_free_mp_int_a1)->dp, (*fsv_mp_globals.fs_mp_safe_shred_and_free_mp_int_a1)->alloc * sizeof(*(*fsv_mp_globals.fs_mp_safe_shred_and_free_mp_int_a1)->dp));
				(*fsv_mp_globals.fs_mp_safe_shred_and_free_mp_int_a1)->dp    = NULL;
				(*fsv_mp_globals.fs_mp_safe_shred_and_free_mp_int_a1)->alloc = (*fsv_mp_globals.fs_mp_safe_shred_and_free_mp_int_a1)->used = 0;
				(*fsv_mp_globals.fs_mp_safe_shred_and_free_mp_int_a1)->sign  = 0;
			}
			fs_safe_shred_and_free(fsv_mp_globals.fs_mp_safe_shred_and_free_mp_int_a1, sizeof(*(*fsv_mp_globals.fs_mp_safe_shred_and_free_mp_int_a1)));
			(*fsv_mp_globals.fs_mp_safe_shred_and_free_mp_int_a1) = NULL;
		}
	}
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_count_bits(void) {
	fsv_mp_globals.fs_mp_error = 0;
	if(fsv_mp_globals.fs_mp_count_bits_a1 == NULL) {
		fsv_mp_globals.fs_mp_count_bits_r = 1;
		goto done;
	}
	if(fsv_mp_globals.fs_mp_count_bits_a1->used == 0) {
		fsv_mp_globals.fs_mp_count_bits_r = 0;
		goto done;
	}
	fsv_mp_globals.fs_mp_count_bits_r = (fsv_mp_globals.fs_mp_count_bits_a1->used - 1) * DIGIT_BIT;
	fsv_mp_globals.fs_mp_count_bits_t1 = fsv_mp_globals.fs_mp_count_bits_a1->dp[fsv_mp_globals.fs_mp_count_bits_a1->used - 1];
	while(fsv_mp_globals.fs_mp_count_bits_t1 > ((fs_mp_digit) 0)) {
		++fsv_mp_globals.fs_mp_count_bits_r;
		fsv_mp_globals.fs_mp_count_bits_t1 >>= ((fs_mp_digit) 1);
	}
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_init(void) {
	fsv_mp_globals.fs_mp_error = 0;
	memset((char*)fsv_mp_globals.fs_mp_init_a1, 0, sizeof(*fsv_mp_globals.fs_mp_init_a1));
	fsv_mp_globals.fs_mp_init_a1->dp = (fs_mp_digit*)fs_zalloc(sizeof (fs_mp_digit) * FS_MP_PREC);
	if(fsv_mp_globals.fs_mp_init_a1->dp != NULL) {
		fsv_mp_globals.fs_mp_init_a1->alloc = FS_MP_PREC;
	} else {
		fsv_mp_globals.fs_mp_error = 1;
	}
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_alloc_and_init(void) {
	fsv_mp_globals.fs_mp_error = 0;
	*(fsv_mp_globals.fs_mp_alloc_and_init_a1) = (fs_mp_int*)fs_zalloc(sizeof(fs_mp_int));
	if(*(fsv_mp_globals.fs_mp_alloc_and_init_a1)) {
		memset((char*)*(fsv_mp_globals.fs_mp_alloc_and_init_a1), 0, sizeof(fs_mp_int));
		(*(fsv_mp_globals.fs_mp_alloc_and_init_a1))->dp = (fs_mp_digit*)fs_zalloc(sizeof (fs_mp_digit) * FS_MP_PREC);
		if((*(fsv_mp_globals.fs_mp_alloc_and_init_a1))->dp != NULL) {
			(*(fsv_mp_globals.fs_mp_alloc_and_init_a1))->alloc = FS_MP_PREC;
		} else {
			fs_free(*(fsv_mp_globals.fs_mp_alloc_and_init_a1));
			*(fsv_mp_globals.fs_mp_alloc_and_init_a1) = NULL;
		}
	}
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_unsigned_bin_size(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_count_bits_a1 = fsv_mp_globals.fs_mp_unsigned_bin_size_a1;
	fs_mp_count_bits();
	fsv_mp_globals.fs_mp_unsigned_bin_size_r = (fsv_mp_globals.fs_mp_count_bits_r / 8 + ((fsv_mp_globals.fs_mp_count_bits_r & 7) != 0 ? 1 : 0));
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_cnt_lsb(void) {
	__FS_LOCAL_STATIC_OPTION const int fsv_t1[16] = { 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0 };
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_cnt_lsb_r = 0;
	if((((fsv_mp_globals.fs_mp_cnt_lsb_a1)->used == 0) ? 1 : 0) == 1) {
		goto done;
	}
	for(fsv_mp_globals.fs_mp_cnt_lsb_r = 0; fsv_mp_globals.fs_mp_cnt_lsb_r < fsv_mp_globals.fs_mp_cnt_lsb_a1->used && fsv_mp_globals.fs_mp_cnt_lsb_a1->dp[fsv_mp_globals.fs_mp_cnt_lsb_r] == 0; fsv_mp_globals.fs_mp_cnt_lsb_r++) {
		/* nothing*/
	}
	fsv_mp_globals.fs_mp_cnt_lsb_t1 = fsv_mp_globals.fs_mp_cnt_lsb_a1->dp[fsv_mp_globals.fs_mp_cnt_lsb_r];
	fsv_mp_globals.fs_mp_cnt_lsb_r *= DIGIT_BIT;
	if((fsv_mp_globals.fs_mp_cnt_lsb_t1 & 1) == 0) {
		do {
			fsv_mp_globals.fs_mp_cnt_lsb_t2  = fsv_mp_globals.fs_mp_cnt_lsb_t1 & 15;
			fsv_mp_globals.fs_mp_cnt_lsb_r  += fsv_t1[fsv_mp_globals.fs_mp_cnt_lsb_t2];
			fsv_mp_globals.fs_mp_cnt_lsb_t1 >>= 4;
		} while(fsv_mp_globals.fs_mp_cnt_lsb_t2 == 0);
	}
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_grow(void) {
	fsv_mp_globals.fs_mp_error = 0;
	if(fsv_mp_globals.fs_mp_grow_a1->alloc < fsv_mp_globals.fs_mp_grow_a2) {
		fsv_mp_globals.fs_mp_grow_a2 += (FS_MP_PREC * 2) - (fsv_mp_globals.fs_mp_grow_a2 % FS_MP_PREC);
		fsv_mp_globals.fs_mp_grow_t1 = (fs_mp_digit*)fs_realloc(fsv_mp_globals.fs_mp_grow_a1->dp, sizeof (fs_mp_digit) * fsv_mp_globals.fs_mp_grow_a2);
		if(!fsv_mp_globals.fs_mp_grow_t1) {
			fsv_mp_globals.fs_mp_error = 1;
			goto done;
		}
		fsv_mp_globals.fs_mp_grow_a1->dp = fsv_mp_globals.fs_mp_grow_t1;
		fsv_mp_globals.fs_mp_grow_t2 = fsv_mp_globals.fs_mp_grow_a1->alloc;
		fsv_mp_globals.fs_mp_grow_a1->alloc = fsv_mp_globals.fs_mp_grow_a2;
		for(; fsv_mp_globals.fs_mp_grow_t2 < fsv_mp_globals.fs_mp_grow_a1->alloc; fsv_mp_globals.fs_mp_grow_t2++) {
			fsv_mp_globals.fs_mp_grow_a1->dp[fsv_mp_globals.fs_mp_grow_t2] = 0;
		}
	}
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_copy(void) {
	fsv_mp_globals.fs_mp_error   = 0;
	fsv_mp_globals.fs_mp_copy_t3 = 0;
	if(fsv_mp_globals.fs_mp_copy_a1 == fsv_mp_globals.fs_mp_copy_a2) {
		fsv_mp_globals.fs_mp_error = 0;
		goto done;
	}
	if(fsv_mp_globals.fs_mp_copy_a2->alloc < fsv_mp_globals.fs_mp_copy_a1->used) {
		fsv_mp_globals.fs_mp_grow_a1 = fsv_mp_globals.fs_mp_copy_a2;
		fsv_mp_globals.fs_mp_grow_a2 = fsv_mp_globals.fs_mp_copy_a1->used;
		fs_mp_grow();
		if((fsv_mp_globals.fs_mp_error = fsv_mp_globals.fs_mp_error)) {
			goto done;
		}
	}
	fsv_mp_globals.fs_mp_copy_t1 = fsv_mp_globals.fs_mp_copy_a1->dp;
	fsv_mp_globals.fs_mp_copy_t2 = fsv_mp_globals.fs_mp_copy_a2->dp;
	for(fsv_mp_globals.fs_mp_copy_t3 = 0; fsv_mp_globals.fs_mp_copy_t3 < fsv_mp_globals.fs_mp_copy_a1->used; fsv_mp_globals.fs_mp_copy_t3++) {
		*fsv_mp_globals.fs_mp_copy_t2++ = *fsv_mp_globals.fs_mp_copy_t1++;
	}
	for(; fsv_mp_globals.fs_mp_copy_t3 < fsv_mp_globals.fs_mp_copy_a2->used; fsv_mp_globals.fs_mp_copy_t3++) {
		*fsv_mp_globals.fs_mp_copy_t2++ = 0;
	}
	fsv_mp_globals.fs_mp_copy_a2->used = fsv_mp_globals.fs_mp_copy_a1->used;
	fsv_mp_globals.fs_mp_copy_a2->sign = fsv_mp_globals.fs_mp_copy_a1->sign;
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_2expt(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_zero_a1 = fsv_mp_globals.fs_mp_2expt_a1;
	fs_mp_zero();
	fsv_mp_globals.fs_mp_grow_a1 = fsv_mp_globals.fs_mp_2expt_a1;
	fsv_mp_globals.fs_mp_grow_a2 = fsv_mp_globals.fs_mp_2expt_a2 / DIGIT_BIT + 1;
	fs_mp_grow();
	if(fsv_mp_globals.fs_mp_error) {
		goto done;
	}
	fsv_mp_globals.fs_mp_2expt_a1->used = fsv_mp_globals.fs_mp_2expt_a2 / DIGIT_BIT + 1;
	fsv_mp_globals.fs_mp_2expt_a1->dp[fsv_mp_globals.fs_mp_2expt_a2 / DIGIT_BIT] = ((fs_mp_digit)1) << (fsv_mp_globals.fs_mp_2expt_a2 % DIGIT_BIT);
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_clamp(void) {
	fsv_mp_globals.fs_mp_error = 0;
	while(fsv_mp_globals.fs_mp_clamp_a1->used > 0 && fsv_mp_globals.fs_mp_clamp_a1->dp[fsv_mp_globals.fs_mp_clamp_a1->used - 1] == 0) {
		--(fsv_mp_globals.fs_mp_clamp_a1->used);
	}
	if(fsv_mp_globals.fs_mp_clamp_a1->used == 0) {
		fsv_mp_globals.fs_mp_clamp_a1->sign = 0;
	}
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_abs(void) {
	fsv_mp_globals.fs_mp_error = 0;
	if(fsv_mp_globals.fs_mp_abs_a1 != fsv_mp_globals.fs_mp_abs_a2) {
		fsv_mp_globals.fs_mp_copy_a1 = fsv_mp_globals.fs_mp_abs_a1;
		fsv_mp_globals.fs_mp_copy_a2 = fsv_mp_globals.fs_mp_abs_a2;
		fs_mp_copy();
		if(fsv_mp_globals.fs_mp_error) {
			goto done;
		}
	}
	fsv_mp_globals.fs_mp_abs_a2->sign = 0;
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_rshd(void) {
	fsv_mp_globals.fs_mp_error = 0;
	if(fsv_mp_globals.fs_mp_rshd_a2 <= 0) {
		goto done;
	}
	if(fsv_mp_globals.fs_mp_rshd_a1->used <= fsv_mp_globals.fs_mp_rshd_a2) {
		fsv_mp_globals.fs_mp_zero_a1 = fsv_mp_globals.fs_mp_rshd_a1;
		fs_mp_zero();
		goto done;
	}
	fsv_mp_globals.fs_mp_rshd_t2 = fsv_mp_globals.fs_mp_rshd_a1->dp;
	fsv_mp_globals.fs_mp_rshd_t3 = fsv_mp_globals.fs_mp_rshd_a1->dp + fsv_mp_globals.fs_mp_rshd_a2;
	for(fsv_mp_globals.fs_mp_rshd_t1 = 0; fsv_mp_globals.fs_mp_rshd_t1 < (fsv_mp_globals.fs_mp_rshd_a1->used - fsv_mp_globals.fs_mp_rshd_a2); fsv_mp_globals.fs_mp_rshd_t1++) {
		*fsv_mp_globals.fs_mp_rshd_t2++ = *fsv_mp_globals.fs_mp_rshd_t3++;
	}
	for(; fsv_mp_globals.fs_mp_rshd_t1 < fsv_mp_globals.fs_mp_rshd_a1->used; fsv_mp_globals.fs_mp_rshd_t1++) {
		*fsv_mp_globals.fs_mp_rshd_t2++ = 0;
	}
	fsv_mp_globals.fs_mp_rshd_a1->used -= fsv_mp_globals.fs_mp_rshd_a2;
	done:
	return;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_lshd(void) {
	fsv_mp_globals.fs_mp_error = 0;
	if(fsv_mp_globals.fs_mp_lshd_a2 <= 0) {
		goto done;
	}
	if(fsv_mp_globals.fs_mp_lshd_a1->alloc < fsv_mp_globals.fs_mp_lshd_a1->used + fsv_mp_globals.fs_mp_lshd_a2) {
		fsv_mp_globals.fs_mp_grow_a1 = fsv_mp_globals.fs_mp_lshd_a1;
		fsv_mp_globals.fs_mp_grow_a2 = fsv_mp_globals.fs_mp_lshd_a1->used + fsv_mp_globals.fs_mp_lshd_a2;
		fs_mp_grow();
		if(fsv_mp_globals.fs_mp_error) {
			goto done;
		}
	}
	fsv_mp_globals.fs_mp_lshd_a1->used += fsv_mp_globals.fs_mp_lshd_a2;
	fsv_mp_globals.fs_mp_lshd_t2 = fsv_mp_globals.fs_mp_lshd_a1->dp + fsv_mp_globals.fs_mp_lshd_a1->used - 1;
	fsv_mp_globals.fs_mp_lshd_t3 = fsv_mp_globals.fs_mp_lshd_a1->dp + fsv_mp_globals.fs_mp_lshd_a1->used - 1 - fsv_mp_globals.fs_mp_lshd_a2;
	for(fsv_mp_globals.fs_mp_lshd_t1 = fsv_mp_globals.fs_mp_lshd_a1->used - 1; fsv_mp_globals.fs_mp_lshd_t1 >= fsv_mp_globals.fs_mp_lshd_a2; fsv_mp_globals.fs_mp_lshd_t1--) {
		*fsv_mp_globals.fs_mp_lshd_t2-- = *fsv_mp_globals.fs_mp_lshd_t3--;
	}
	fsv_mp_globals.fs_mp_lshd_t2 = fsv_mp_globals.fs_mp_lshd_a1->dp;
	for(fsv_mp_globals.fs_mp_lshd_t1 = 0; fsv_mp_globals.fs_mp_lshd_t1 < fsv_mp_globals.fs_mp_lshd_a2; fsv_mp_globals.fs_mp_lshd_t1++) {
		*fsv_mp_globals.fs_mp_lshd_t2++ = 0;
	}
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_mul_2d(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_mul_2d_t1 = 0;
	if(fsv_mp_globals.fs_mp_mul_2d_a1 != fsv_mp_globals.fs_mp_mul_2d_a3) {
		fsv_mp_globals.fs_mp_copy_a1 = fsv_mp_globals.fs_mp_mul_2d_a1;
		fsv_mp_globals.fs_mp_copy_a2 = fsv_mp_globals.fs_mp_mul_2d_a3;
		fs_mp_copy();
		if(fsv_mp_globals.fs_mp_error) {
			goto done;
		}
	}
	if(fsv_mp_globals.fs_mp_mul_2d_a3->alloc < (int)(fsv_mp_globals.fs_mp_mul_2d_a3->used + fsv_mp_globals.fs_mp_mul_2d_a2/DIGIT_BIT + 1)) {
		fsv_mp_globals.fs_mp_grow_a1 = fsv_mp_globals.fs_mp_mul_2d_a3;
		fsv_mp_globals.fs_mp_grow_a2 = fsv_mp_globals.fs_mp_mul_2d_a3->used + fsv_mp_globals.fs_mp_mul_2d_a2 / DIGIT_BIT + 1;
		fs_mp_grow();
		if(fsv_mp_globals.fs_mp_error) {
			goto done;
		}
	}
	if(fsv_mp_globals.fs_mp_mul_2d_a2 >= (int)DIGIT_BIT) {
		fsv_mp_globals.fs_mp_lshd_a1 = fsv_mp_globals.fs_mp_mul_2d_a3;
		fsv_mp_globals.fs_mp_lshd_a2 = fsv_mp_globals.fs_mp_mul_2d_a2 / DIGIT_BIT;
		fs_mp_lshd();
		if(fsv_mp_globals.fs_mp_error) {
			goto done;
		}
	}
	fsv_mp_globals.fs_mp_mul_2d_t1 = (fs_mp_digit) (fsv_mp_globals.fs_mp_mul_2d_a2 % DIGIT_BIT);
	if(fsv_mp_globals.fs_mp_mul_2d_t1 != 0) {
		fsv_mp_globals.fs_mp_mul_2d_t2 = 0;
		fsv_mp_globals.fs_mp_mul_2d_t4 = fsv_mp_globals.fs_mp_mul_2d_t5 = fsv_mp_globals.fs_mp_mul_2d_t6 = fsv_mp_globals.fs_mp_mul_2d_t7 = 0;
		fsv_mp_globals.fs_mp_mul_2d_t5 = (((fs_mp_digit)1) << fsv_mp_globals.fs_mp_mul_2d_t1) - 1;
		fsv_mp_globals.fs_mp_mul_2d_t4 = DIGIT_BIT - fsv_mp_globals.fs_mp_mul_2d_t1;
		fsv_mp_globals.fs_mp_mul_2d_t3 = fsv_mp_globals.fs_mp_mul_2d_a3->dp;
		fsv_mp_globals.fs_mp_mul_2d_t6 = 0;
		for(fsv_mp_globals.fs_mp_mul_2d_t2 = 0; fsv_mp_globals.fs_mp_mul_2d_t2 < fsv_mp_globals.fs_mp_mul_2d_a3->used; fsv_mp_globals.fs_mp_mul_2d_t2++) {
			fsv_mp_globals.fs_mp_mul_2d_t7 = (*fsv_mp_globals.fs_mp_mul_2d_t3 >> fsv_mp_globals.fs_mp_mul_2d_t4) & fsv_mp_globals.fs_mp_mul_2d_t5;
			*fsv_mp_globals.fs_mp_mul_2d_t3 = ((*fsv_mp_globals.fs_mp_mul_2d_t3 << fsv_mp_globals.fs_mp_mul_2d_t1) | fsv_mp_globals.fs_mp_mul_2d_t6) & ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1));
			++fsv_mp_globals.fs_mp_mul_2d_t3;
			fsv_mp_globals.fs_mp_mul_2d_t6 = fsv_mp_globals.fs_mp_mul_2d_t7;
		}
		if(fsv_mp_globals.fs_mp_mul_2d_t6 != 0) {
			fsv_mp_globals.fs_mp_mul_2d_a3->dp[(fsv_mp_globals.fs_mp_mul_2d_a3->used)++] = fsv_mp_globals.fs_mp_mul_2d_t6;
		}
	}
	fsv_mp_globals.fs_mp_clamp_a1 = fsv_mp_globals.fs_mp_mul_2d_a3;
	fs_mp_clamp();
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_read_unsigned_bin(void) {
	fsv_mp_globals.fs_mp_error = 0;
	if(fsv_mp_globals.fs_mp_read_unsigned_bin_a1->alloc < 2) {
		fsv_mp_globals.fs_mp_grow_a1 = fsv_mp_globals.fs_mp_read_unsigned_bin_a1;
		fsv_mp_globals.fs_mp_grow_a2 = 2;
		fs_mp_grow();
		if(fsv_mp_globals.fs_mp_error) {
			goto done;
		}
	}
	fsv_mp_globals.fs_mp_zero_a1 = fsv_mp_globals.fs_mp_read_unsigned_bin_a1;
	fs_mp_zero();
	while(fsv_mp_globals.fs_mp_read_unsigned_bin_a3-- > 0) {
		fsv_mp_globals.fs_mp_mul_2d_a1 = fsv_mp_globals.fs_mp_read_unsigned_bin_a1;
		fsv_mp_globals.fs_mp_mul_2d_a2 = 8;
		fsv_mp_globals.fs_mp_mul_2d_a3 = fsv_mp_globals.fs_mp_read_unsigned_bin_a1;
		fs_mp_mul_2d();
		if(fsv_mp_globals.fs_mp_error) {
			goto done;
		}
		fsv_mp_globals.fs_mp_read_unsigned_bin_a1->dp[0] |= *fsv_mp_globals.fs_mp_read_unsigned_bin_a2++;
		fsv_mp_globals.fs_mp_read_unsigned_bin_a1->used += 1;
	}
	fsv_mp_globals.fs_mp_clamp_a1 = fsv_mp_globals.fs_mp_read_unsigned_bin_a1;
	fs_mp_clamp();
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_s_sub(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_s_sub_t3 = fsv_mp_globals.fs_mp_s_sub_a2->used;
	fsv_mp_globals.fs_mp_s_sub_t2 = fsv_mp_globals.fs_mp_s_sub_a1->used;
	if(fsv_mp_globals.fs_mp_s_sub_a3->alloc < fsv_mp_globals.fs_mp_s_sub_t2) {
		fsv_mp_globals.fs_mp_grow_a1 = fsv_mp_globals.fs_mp_s_sub_a3;
		fsv_mp_globals.fs_mp_grow_a2 = fsv_mp_globals.fs_mp_s_sub_t2;
		fs_mp_grow();
		if(fsv_mp_globals.fs_mp_error) {
			goto done;
		}
	}
	fsv_mp_globals.fs_mp_s_sub_t1 = fsv_mp_globals.fs_mp_s_sub_a3->used;
	fsv_mp_globals.fs_mp_s_sub_a3->used = fsv_mp_globals.fs_mp_s_sub_t2;
	fsv_mp_globals.fs_mp_s_sub_t5 = fsv_mp_globals.fs_mp_s_sub_a1->dp;
	fsv_mp_globals.fs_mp_s_sub_t6 = fsv_mp_globals.fs_mp_s_sub_a2->dp;
	fsv_mp_globals.fs_mp_s_sub_t7 = fsv_mp_globals.fs_mp_s_sub_a3->dp;
	fsv_mp_globals.fs_mp_s_sub_t4 = 0;
	for(fsv_mp_globals.fs_mp_s_sub_t8 = 0; fsv_mp_globals.fs_mp_s_sub_t8 < fsv_mp_globals.fs_mp_s_sub_t3; fsv_mp_globals.fs_mp_s_sub_t8++) {
		*fsv_mp_globals.fs_mp_s_sub_t7 = *fsv_mp_globals.fs_mp_s_sub_t5++ - *fsv_mp_globals.fs_mp_s_sub_t6++ - fsv_mp_globals.fs_mp_s_sub_t4;
		fsv_mp_globals.fs_mp_s_sub_t4 = *fsv_mp_globals.fs_mp_s_sub_t7 >> ((fs_mp_digit)(8 * sizeof (fs_mp_digit) - 1));
		*fsv_mp_globals.fs_mp_s_sub_t7++ &= ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1));
	}
	for(; fsv_mp_globals.fs_mp_s_sub_t8 < fsv_mp_globals.fs_mp_s_sub_t2; fsv_mp_globals.fs_mp_s_sub_t8++) {
		*fsv_mp_globals.fs_mp_s_sub_t7 = *fsv_mp_globals.fs_mp_s_sub_t5++ - fsv_mp_globals.fs_mp_s_sub_t4;
		fsv_mp_globals.fs_mp_s_sub_t4 = *fsv_mp_globals.fs_mp_s_sub_t7 >> ((fs_mp_digit)(8 * sizeof (fs_mp_digit) - 1));
		*fsv_mp_globals.fs_mp_s_sub_t7++ &= ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1));
	}
	for(fsv_mp_globals.fs_mp_s_sub_t8 = fsv_mp_globals.fs_mp_s_sub_a3->used; fsv_mp_globals.fs_mp_s_sub_t8 < fsv_mp_globals.fs_mp_s_sub_t1; fsv_mp_globals.fs_mp_s_sub_t8++) {
		*fsv_mp_globals.fs_mp_s_sub_t7++ = 0;
	}
	fsv_mp_globals.fs_mp_clamp_a1 = fsv_mp_globals.fs_mp_s_sub_a3;
	fs_mp_clamp();
	done:
	;
}


__FS_FUNCTION_MAYBE_INLINE void fs_mp_s_add(void) {
	fsv_mp_globals.fs_mp_error = 0;
	if(fsv_mp_globals.fs_mp_s_add_a1->used > fsv_mp_globals.fs_mp_s_add_a2->used) {
		fsv_mp_globals.fs_mp_s_add_t3 = fsv_mp_globals.fs_mp_s_add_a2->used;
		fsv_mp_globals.fs_mp_s_add_t4 = fsv_mp_globals.fs_mp_s_add_a1->used;
		fsv_mp_globals.fs_mp_s_add_t1 = fsv_mp_globals.fs_mp_s_add_a1;
	} else {
		fsv_mp_globals.fs_mp_s_add_t3 = fsv_mp_globals.fs_mp_s_add_a1->used;
		fsv_mp_globals.fs_mp_s_add_t4 = fsv_mp_globals.fs_mp_s_add_a2->used;
		fsv_mp_globals.fs_mp_s_add_t1 = fsv_mp_globals.fs_mp_s_add_a2;
	}
	if(fsv_mp_globals.fs_mp_s_add_a3->alloc < fsv_mp_globals.fs_mp_s_add_t4 + 1) {
		fsv_mp_globals.fs_mp_grow_a1 = fsv_mp_globals.fs_mp_s_add_a3;
		fsv_mp_globals.fs_mp_grow_a2 = fsv_mp_globals.fs_mp_s_add_t4 + 1;
		fs_mp_grow();
		if(fsv_mp_globals.fs_mp_error) {
			goto done;
		}
	}
	fsv_mp_globals.fs_mp_s_add_t2 = fsv_mp_globals.fs_mp_s_add_a3->used;
	fsv_mp_globals.fs_mp_s_add_a3->used = fsv_mp_globals.fs_mp_s_add_t4 + 1;
	fsv_mp_globals.fs_mp_s_add_t6 = fsv_mp_globals.fs_mp_s_add_a1->dp;
	fsv_mp_globals.fs_mp_s_add_t7 = fsv_mp_globals.fs_mp_s_add_a2->dp;
	fsv_mp_globals.fs_mp_s_add_t8 = fsv_mp_globals.fs_mp_s_add_a3->dp;
	fsv_mp_globals.fs_mp_s_add_t5 = 0;
	for(fsv_mp_globals.fs_mp_s_add_t9 = 0; fsv_mp_globals.fs_mp_s_add_t9 < fsv_mp_globals.fs_mp_s_add_t3; fsv_mp_globals.fs_mp_s_add_t9++) {
		*fsv_mp_globals.fs_mp_s_add_t8 = *fsv_mp_globals.fs_mp_s_add_t6++ + *fsv_mp_globals.fs_mp_s_add_t7++ + fsv_mp_globals.fs_mp_s_add_t5;
		fsv_mp_globals.fs_mp_s_add_t5 = *fsv_mp_globals.fs_mp_s_add_t8 >> ((fs_mp_digit)DIGIT_BIT);
		*fsv_mp_globals.fs_mp_s_add_t8++ &= ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1));
	}
	if(fsv_mp_globals.fs_mp_s_add_t3 != fsv_mp_globals.fs_mp_s_add_t4) {
		for(; fsv_mp_globals.fs_mp_s_add_t9 < fsv_mp_globals.fs_mp_s_add_t4; fsv_mp_globals.fs_mp_s_add_t9++) {
			*fsv_mp_globals.fs_mp_s_add_t8 = fsv_mp_globals.fs_mp_s_add_t1->dp[fsv_mp_globals.fs_mp_s_add_t9] + fsv_mp_globals.fs_mp_s_add_t5;
			fsv_mp_globals.fs_mp_s_add_t5 = *fsv_mp_globals.fs_mp_s_add_t8 >> ((fs_mp_digit)DIGIT_BIT);
			*fsv_mp_globals.fs_mp_s_add_t8++ &= ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1));
		}
	}
	*fsv_mp_globals.fs_mp_s_add_t8++ = fsv_mp_globals.fs_mp_s_add_t5;
	for(fsv_mp_globals.fs_mp_s_add_t9 = fsv_mp_globals.fs_mp_s_add_a3->used; fsv_mp_globals.fs_mp_s_add_t9 < fsv_mp_globals.fs_mp_s_add_t2; fsv_mp_globals.fs_mp_s_add_t9++) {
		*fsv_mp_globals.fs_mp_s_add_t8++ = 0;
	}
	fsv_mp_globals.fs_mp_clamp_a1 = fsv_mp_globals.fs_mp_s_add_a3;
	fs_mp_clamp();
	done:
	;
}


__FS_FUNCTION_MAYBE_INLINE void fs_mp_set(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_zero_a1 = fsv_mp_globals.fs_mp_set_a1;
	fs_mp_zero();
	fsv_mp_globals.fs_mp_set_a1->dp[0] = fsv_mp_globals.fs_mp_set_a2 & ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1));
	fsv_mp_globals.fs_mp_set_a1->used  = (fsv_mp_globals.fs_mp_set_a1->dp[0] != 0) ? 1 : 0;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_cmp_mag(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_cmp_mag_r = 0;
	if(fsv_mp_globals.fs_mp_cmp_mag_a1->used > fsv_mp_globals.fs_mp_cmp_mag_a2->used) {
		fsv_mp_globals.fs_mp_cmp_mag_r = 1;
		goto done;
	}
	if(fsv_mp_globals.fs_mp_cmp_mag_a1->used < fsv_mp_globals.fs_mp_cmp_mag_a2->used) {
		fsv_mp_globals.fs_mp_cmp_mag_r = -1;
		goto done;
	}
	fsv_mp_globals.fs_mp_cmp_mag_t2 = fsv_mp_globals.fs_mp_cmp_mag_a1->dp + (fsv_mp_globals.fs_mp_cmp_mag_a1->used - 1);
	fsv_mp_globals.fs_mp_cmp_mag_t3 = fsv_mp_globals.fs_mp_cmp_mag_a2->dp + (fsv_mp_globals.fs_mp_cmp_mag_a1->used - 1);
	for(fsv_mp_globals.fs_mp_cmp_mag_t1 = 0; fsv_mp_globals.fs_mp_cmp_mag_t1 < fsv_mp_globals.fs_mp_cmp_mag_a1->used; ++fsv_mp_globals.fs_mp_cmp_mag_t1, --fsv_mp_globals.fs_mp_cmp_mag_t2, --fsv_mp_globals.fs_mp_cmp_mag_t3) {
		if(*fsv_mp_globals.fs_mp_cmp_mag_t2 > *fsv_mp_globals.fs_mp_cmp_mag_t3) {
			fsv_mp_globals.fs_mp_cmp_mag_r = 1;
			goto done;
		}
		if(*fsv_mp_globals.fs_mp_cmp_mag_t2 < *fsv_mp_globals.fs_mp_cmp_mag_t3) {
			fsv_mp_globals.fs_mp_cmp_mag_r = -1;
			goto done;
		}
	}
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_sub(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_sub_t1 = fsv_mp_globals.fs_mp_sub_t2 = 0;
	fsv_mp_globals.fs_mp_sub_t1 = fsv_mp_globals.fs_mp_sub_a1->sign;
	fsv_mp_globals.fs_mp_sub_t2 = fsv_mp_globals.fs_mp_sub_a2->sign;
	if(fsv_mp_globals.fs_mp_sub_t1 != fsv_mp_globals.fs_mp_sub_t2) {
		fsv_mp_globals.fs_mp_sub_a3->sign = fsv_mp_globals.fs_mp_sub_t1;
		fsv_mp_globals.fs_mp_s_add_a1 = fsv_mp_globals.fs_mp_sub_a1;
		fsv_mp_globals.fs_mp_s_add_a2 = fsv_mp_globals.fs_mp_sub_a2;
		fsv_mp_globals.fs_mp_s_add_a3 = fsv_mp_globals.fs_mp_sub_a3;
		fs_mp_s_add();
	} else {
		fsv_mp_globals.fs_mp_cmp_mag_a1 = fsv_mp_globals.fs_mp_sub_a1;
		fsv_mp_globals.fs_mp_cmp_mag_a2 = fsv_mp_globals.fs_mp_sub_a2;
		fs_mp_cmp_mag();
		if(fsv_mp_globals.fs_mp_cmp_mag_r != -1) {
			fsv_mp_globals.fs_mp_sub_a3->sign = fsv_mp_globals.fs_mp_sub_t1;
			fsv_mp_globals.fs_mp_s_sub_a1 = fsv_mp_globals.fs_mp_sub_a1;
			fsv_mp_globals.fs_mp_s_sub_a2 = fsv_mp_globals.fs_mp_sub_a2;
			fsv_mp_globals.fs_mp_s_sub_a3 = fsv_mp_globals.fs_mp_sub_a3;
			fs_mp_s_sub();
		} else {
			fsv_mp_globals.fs_mp_sub_a3->sign = (fsv_mp_globals.fs_mp_sub_t1 == 0) ? 1 : 0;
			fsv_mp_globals.fs_mp_s_sub_a1 = fsv_mp_globals.fs_mp_sub_a2;
			fsv_mp_globals.fs_mp_s_sub_a2 = fsv_mp_globals.fs_mp_sub_a1;
			fsv_mp_globals.fs_mp_s_sub_a3 = fsv_mp_globals.fs_mp_sub_a3;
			fs_mp_s_sub();
		}
	}
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_add(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_add_t1 = fsv_mp_globals.fs_mp_add_a1->sign;
	fsv_mp_globals.fs_mp_add_t2 = fsv_mp_globals.fs_mp_add_a2->sign;
	if(fsv_mp_globals.fs_mp_add_t1 == fsv_mp_globals.fs_mp_add_t2) {
		fsv_mp_globals.fs_mp_add_a3->sign = fsv_mp_globals.fs_mp_add_t1;
		fsv_mp_globals.fs_mp_s_add_a1 = fsv_mp_globals.fs_mp_add_a1;
		fsv_mp_globals.fs_mp_s_add_a2 = fsv_mp_globals.fs_mp_add_a2;
		fsv_mp_globals.fs_mp_s_add_a3 = fsv_mp_globals.fs_mp_add_a3;
		fs_mp_s_add();
	} else {
		fsv_mp_globals.fs_mp_cmp_mag_a1 = fsv_mp_globals.fs_mp_add_a1;
		fsv_mp_globals.fs_mp_cmp_mag_a2 = fsv_mp_globals.fs_mp_add_a2;
		fs_mp_cmp_mag();
		if(fsv_mp_globals.fs_mp_cmp_mag_r == -1) {
			fsv_mp_globals.fs_mp_add_a3->sign = fsv_mp_globals.fs_mp_add_t2;
			fsv_mp_globals.fs_mp_s_sub_a1 = fsv_mp_globals.fs_mp_add_a2;
			fsv_mp_globals.fs_mp_s_sub_a2 = fsv_mp_globals.fs_mp_add_a1;
			fsv_mp_globals.fs_mp_s_sub_a3 = fsv_mp_globals.fs_mp_add_a3;
			fs_mp_s_sub();
		} else {
			fsv_mp_globals.fs_mp_add_a3->sign = fsv_mp_globals.fs_mp_add_t1;
			fsv_mp_globals.fs_mp_s_sub_a1 = fsv_mp_globals.fs_mp_add_a1;
			fsv_mp_globals.fs_mp_s_sub_a2 = fsv_mp_globals.fs_mp_add_a2;
			fsv_mp_globals.fs_mp_s_sub_a3 = fsv_mp_globals.fs_mp_add_a3;
			fs_mp_s_sub();
		}
	}
}
__FS_FUNCTION_MAYBE_INLINE void fs_mp_mod_2d(void) {
	fsv_mp_globals.fs_mp_error = 0;
	if(fsv_mp_globals.fs_mp_mod_2d_a2 <= 0) {
		fsv_mp_globals.fs_mp_zero_a1 = fsv_mp_globals.fs_mp_mod_2d_a3;
		fs_mp_zero();
		goto done;
	}
	if(fsv_mp_globals.fs_mp_mod_2d_a2 >= (int) (fsv_mp_globals.fs_mp_mod_2d_a1->used * DIGIT_BIT)) {
		fsv_mp_globals.fs_mp_copy_a1 = fsv_mp_globals.fs_mp_mod_2d_a1;
		fsv_mp_globals.fs_mp_copy_a2 = fsv_mp_globals.fs_mp_mod_2d_a3;
		fs_mp_copy();
		goto done;
	}
	fsv_mp_globals.fs_mp_copy_a1 = fsv_mp_globals.fs_mp_mod_2d_a1;
	fsv_mp_globals.fs_mp_copy_a2 = fsv_mp_globals.fs_mp_mod_2d_a3;
	fs_mp_copy();
	if(fsv_mp_globals.fs_mp_error) {
		goto done;
	}
	for(fsv_mp_globals.fs_mp_mod_2d_t1 = (fsv_mp_globals.fs_mp_mod_2d_a2 / DIGIT_BIT) + ((fsv_mp_globals.fs_mp_mod_2d_a2 % DIGIT_BIT) == 0 ? 0 : 1); fsv_mp_globals.fs_mp_mod_2d_t1 < fsv_mp_globals.fs_mp_mod_2d_a3->used; fsv_mp_globals.fs_mp_mod_2d_t1++) {
		fsv_mp_globals.fs_mp_mod_2d_a3->dp[fsv_mp_globals.fs_mp_mod_2d_t1] = 0;
	}
	fsv_mp_globals.fs_mp_mod_2d_a3->dp[fsv_mp_globals.fs_mp_mod_2d_a2 / DIGIT_BIT] &= (fs_mp_digit) ((((fs_mp_digit) 1) << (((fs_mp_digit) fsv_mp_globals.fs_mp_mod_2d_a2) % DIGIT_BIT)) - ((fs_mp_digit) 1));
	fsv_mp_globals.fs_mp_clamp_a1 = fsv_mp_globals.fs_mp_mod_2d_a3;
	fs_mp_clamp();
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_exch(void) {
	fsv_mp_globals.fs_mp_exch_t1  = *fsv_mp_globals.fs_mp_exch_a1;
	*fsv_mp_globals.fs_mp_exch_a1 = *fsv_mp_globals.fs_mp_exch_a2;
	*fsv_mp_globals.fs_mp_exch_a2 = fsv_mp_globals.fs_mp_exch_t1;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_init_copy(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_init_a1 = fsv_mp_globals.fs_mp_init_copy_a1;
	fs_mp_init();
	if(!fsv_mp_globals.fs_mp_init_copy_a1->dp) {
		fsv_mp_globals.fs_mp_error = 1;
		goto done;
	}
	fsv_mp_globals.fs_mp_copy_a1 = fsv_mp_globals.fs_mp_init_copy_a2;
	fsv_mp_globals.fs_mp_copy_a2 = fsv_mp_globals.fs_mp_init_copy_a1;
	fs_mp_copy();
	done:
	;
}


__FS_FUNCTION_MAYBE_INLINE void fs_mp_div_2d(void) {
	fsv_mp_globals.fs_mp_error = 0;
	if(fsv_mp_globals.fs_mp_div_2d_a2 <= 0) {
		fsv_mp_globals.fs_mp_copy_a1 = fsv_mp_globals.fs_mp_div_2d_a1;
		fsv_mp_globals.fs_mp_copy_a2 = fsv_mp_globals.fs_mp_div_2d_a3;
		fs_mp_copy();
		if(fsv_mp_globals.fs_mp_div_2d_a4 != NULL) {
			fsv_mp_globals.fs_mp_zero_a1 = fsv_mp_globals.fs_mp_div_2d_a4;
			fs_mp_zero();
		}
		goto done;
	}
	fsv_mp_globals.fs_mp_init_a1 = &fsv_mp_globals.fs_mp_div_2d_t5;
	fs_mp_init();
	if(!fsv_mp_globals.fs_mp_div_2d_t5.dp) {
		fsv_mp_globals.fs_mp_error = 1;
		goto done;
	}
	if(fsv_mp_globals.fs_mp_div_2d_a4 != NULL) {
		fsv_mp_globals.fs_mp_mod_2d_a1 = fsv_mp_globals.fs_mp_div_2d_a1;
		fsv_mp_globals.fs_mp_mod_2d_a2 = fsv_mp_globals.fs_mp_div_2d_a2;
		fsv_mp_globals.fs_mp_mod_2d_a3 = &fsv_mp_globals.fs_mp_div_2d_t5;
		fs_mp_mod_2d();
		if(fsv_mp_globals.fs_mp_error) {
			fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_div_2d_t5;
			fs_mp_clear();
			fsv_mp_globals.fs_mp_error = 1;
			goto done;
		}
	}
	fsv_mp_globals.fs_mp_copy_a1 = fsv_mp_globals.fs_mp_div_2d_a1;
	fsv_mp_globals.fs_mp_copy_a2 = fsv_mp_globals.fs_mp_div_2d_a3;
	fs_mp_copy();
	if(fsv_mp_globals.fs_mp_error) {
		fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_div_2d_t5;
		fs_mp_clear();
		fsv_mp_globals.fs_mp_error = 1;
		goto done;
	}
	if(fsv_mp_globals.fs_mp_div_2d_a2 >= (int)DIGIT_BIT) {
		fsv_mp_globals.fs_mp_rshd_a1 = fsv_mp_globals.fs_mp_div_2d_a3;
		fsv_mp_globals.fs_mp_rshd_a2 = fsv_mp_globals.fs_mp_div_2d_a2 / DIGIT_BIT;
		fs_mp_rshd();
	}
	fsv_mp_globals.fs_mp_div_2d_t1 = (fs_mp_digit) (fsv_mp_globals.fs_mp_div_2d_a2 % DIGIT_BIT);
	if(fsv_mp_globals.fs_mp_div_2d_t1 != 0) {
		fsv_mp_globals.fs_mp_div_2d_t7 = (((fs_mp_digit)1) << fsv_mp_globals.fs_mp_div_2d_t1) - 1;
		fsv_mp_globals.fs_mp_div_2d_t8 = DIGIT_BIT - fsv_mp_globals.fs_mp_div_2d_t1;
		fsv_mp_globals.fs_mp_div_2d_t4 = fsv_mp_globals.fs_mp_div_2d_a3->dp + (fsv_mp_globals.fs_mp_div_2d_a3->used - 1);
		fsv_mp_globals.fs_mp_div_2d_t2 = 0;
		for(fsv_mp_globals.fs_mp_div_2d_t6 = fsv_mp_globals.fs_mp_div_2d_a3->used - 1; fsv_mp_globals.fs_mp_div_2d_t6 >= 0; fsv_mp_globals.fs_mp_div_2d_t6--) {
			fsv_mp_globals.fs_mp_div_2d_t3 = *fsv_mp_globals.fs_mp_div_2d_t4 & fsv_mp_globals.fs_mp_div_2d_t7;
			*fsv_mp_globals.fs_mp_div_2d_t4 = (*fsv_mp_globals.fs_mp_div_2d_t4 >> fsv_mp_globals.fs_mp_div_2d_t1) | (fsv_mp_globals.fs_mp_div_2d_t2 << fsv_mp_globals.fs_mp_div_2d_t8);
			--fsv_mp_globals.fs_mp_div_2d_t4;
			fsv_mp_globals.fs_mp_div_2d_t2 = fsv_mp_globals.fs_mp_div_2d_t3;
		}
	}
	fsv_mp_globals.fs_mp_clamp_a1 = fsv_mp_globals.fs_mp_div_2d_a3;
	fs_mp_clamp();
	if(fsv_mp_globals.fs_mp_div_2d_a4 != NULL) {
		fsv_mp_globals.fs_mp_exch_a1 = &fsv_mp_globals.fs_mp_div_2d_t5;
		fsv_mp_globals.fs_mp_exch_a2 = fsv_mp_globals.fs_mp_div_2d_a4;
		fs_mp_exch();
	}
	fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_div_2d_t5;
	fs_mp_clear();
	done:
	;
}
__FS_FUNCTION_MAYBE_INLINE void fs_mp_to_unsigned_bin(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_init_copy_a1 = &fsv_mp_globals.fs_mp_to_unsigned_bin_t5;
	fsv_mp_globals.fs_mp_init_copy_a2 = fsv_mp_globals.fs_mp_to_unsigned_bin_a1;
	fs_mp_init_copy();
	if(fsv_mp_globals.fs_mp_error) {
		goto done;
	}
	fsv_mp_globals.fs_mp_to_unsigned_bin_t4 = 0;
	while((((&fsv_mp_globals.fs_mp_to_unsigned_bin_t5)->used == 0) ? 1 : 0) == 0) {
		fsv_mp_globals.fs_mp_to_unsigned_bin_a2[fsv_mp_globals.fs_mp_to_unsigned_bin_t4++] = (unsigned char) (fsv_mp_globals.fs_mp_to_unsigned_bin_t5.dp[0] & 255);
		fsv_mp_globals.fs_mp_div_2d_a1 = &fsv_mp_globals.fs_mp_to_unsigned_bin_t5;
		fsv_mp_globals.fs_mp_div_2d_a2 = 8;
		fsv_mp_globals.fs_mp_div_2d_a3 = &fsv_mp_globals.fs_mp_to_unsigned_bin_t5;
		fsv_mp_globals.fs_mp_div_2d_a4 = NULL;
		fs_mp_div_2d();
		if(fsv_mp_globals.fs_mp_error) {
			fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_to_unsigned_bin_t5;
			fs_mp_clear();
			goto done;
		}
	}
	fsv_mp_globals.fs_mp_to_unsigned_bin_t1 = 0;
	fsv_mp_globals.fs_mp_to_unsigned_bin_t2 = fsv_mp_globals.fs_mp_to_unsigned_bin_t4 - 1;
	while(fsv_mp_globals.fs_mp_to_unsigned_bin_t1 < fsv_mp_globals.fs_mp_to_unsigned_bin_t2) {
		fsv_mp_globals.fs_mp_to_unsigned_bin_t3 = fsv_mp_globals.fs_mp_to_unsigned_bin_a2[fsv_mp_globals.fs_mp_to_unsigned_bin_t1];
		fsv_mp_globals.fs_mp_to_unsigned_bin_a2[fsv_mp_globals.fs_mp_to_unsigned_bin_t1] = fsv_mp_globals.fs_mp_to_unsigned_bin_a2[fsv_mp_globals.fs_mp_to_unsigned_bin_t2];
		fsv_mp_globals.fs_mp_to_unsigned_bin_a2[fsv_mp_globals.fs_mp_to_unsigned_bin_t2] = fsv_mp_globals.fs_mp_to_unsigned_bin_t3;
		++fsv_mp_globals.fs_mp_to_unsigned_bin_t1;
		--fsv_mp_globals.fs_mp_to_unsigned_bin_t2;
	}

	fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_to_unsigned_bin_t5;
	fs_mp_clear();
	done:
	;
}
__FS_FUNCTION_MAYBE_INLINE void fs_mp_cmp(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_cmp_r = 0;
	if(fsv_mp_globals.fs_mp_cmp_a1->sign != fsv_mp_globals.fs_mp_cmp_a2->sign) {
		if(fsv_mp_globals.fs_mp_cmp_a1->sign == 1) {
			fsv_mp_globals.fs_mp_cmp_r = -1;
			goto done;
		} else {
			fsv_mp_globals.fs_mp_cmp_r = 1;
			goto done;
		}
	}
	if(fsv_mp_globals.fs_mp_cmp_a1->sign == 1) {
		fsv_mp_globals.fs_mp_cmp_mag_a1 = fsv_mp_globals.fs_mp_cmp_a2;
		fsv_mp_globals.fs_mp_cmp_mag_a2 = fsv_mp_globals.fs_mp_cmp_a1;
		fs_mp_cmp_mag();
		fsv_mp_globals.fs_mp_cmp_r = fsv_mp_globals.fs_mp_cmp_mag_r;
		goto done;
	} else {
		fsv_mp_globals.fs_mp_cmp_mag_a1 = fsv_mp_globals.fs_mp_cmp_a1;
		fsv_mp_globals.fs_mp_cmp_mag_a2 = fsv_mp_globals.fs_mp_cmp_a2;
		fs_mp_cmp_mag();
		fsv_mp_globals.fs_mp_cmp_r = fsv_mp_globals.fs_mp_cmp_mag_r;
		goto done;
	}
	done:
	;
}


__FS_FUNCTION_MAYBE_INLINE void fs_mp_div(void) {
	fsv_mp_globals.fs_mp_error = 0;
	if((((fsv_mp_globals.fs_mp_div_a2)->used == 0) ? 1 : 0) == 1) {
		fsv_mp_globals.fs_mp_error = 1;
		goto done;
	}
	fsv_mp_globals.fs_mp_cmp_mag_a1 = fsv_mp_globals.fs_mp_div_a1;
	fsv_mp_globals.fs_mp_cmp_mag_a2 = fsv_mp_globals.fs_mp_div_a2;
	fs_mp_cmp_mag();
	if(fsv_mp_globals.fs_mp_cmp_mag_r == -1) {
		if(fsv_mp_globals.fs_mp_div_a4 != NULL) {
			fsv_mp_globals.fs_mp_copy_a1 = fsv_mp_globals.fs_mp_div_a1;
			fsv_mp_globals.fs_mp_copy_a2 = fsv_mp_globals.fs_mp_div_a4;
			fs_mp_copy();
		}
		if(fsv_mp_globals.fs_mp_div_a3 != NULL) {
			fsv_mp_globals.fs_mp_zero_a1 = fsv_mp_globals.fs_mp_div_a3;
			fs_mp_zero();
		}
		goto done;
	}
	fsv_mp_globals.fs_mp_init_a1 = &fsv_mp_globals.fs_mp_div_t1;
	fs_mp_init();
	fsv_mp_globals.fs_mp_init_a1 = &fsv_mp_globals.fs_mp_div_t2;
	fs_mp_init();
	fsv_mp_globals.fs_mp_init_a1 = &fsv_mp_globals.fs_mp_div_t3;
	fs_mp_init();
	fsv_mp_globals.fs_mp_init_a1 = &fsv_mp_globals.fs_mp_div_t4;
	fs_mp_init();
	if(!fsv_mp_globals.fs_mp_div_t1.dp || !fsv_mp_globals.fs_mp_div_t2.dp || !fsv_mp_globals.fs_mp_div_t3.dp || !fsv_mp_globals.fs_mp_div_t4.dp) {
		fsv_mp_globals.fs_mp_error = 1;
		goto done;
	}
	fsv_mp_globals.fs_mp_set_a1 = &fsv_mp_globals.fs_mp_div_t3;
	fsv_mp_globals.fs_mp_set_a2 =  1;
	fs_mp_set();
	fsv_mp_globals.fs_mp_count_bits_a1 = fsv_mp_globals.fs_mp_div_a1;
	fs_mp_count_bits();
	fsv_mp_globals.fs_mp_div_t5 = fsv_mp_globals.fs_mp_count_bits_r;
	fsv_mp_globals.fs_mp_count_bits_a1 = fsv_mp_globals.fs_mp_div_a2;
	fs_mp_count_bits();
	fsv_mp_globals.fs_mp_div_t5 -= fsv_mp_globals.fs_mp_count_bits_r;
	fsv_mp_globals.fs_mp_abs_a1 = fsv_mp_globals.fs_mp_div_a1;
	fsv_mp_globals.fs_mp_abs_a2 = &fsv_mp_globals.fs_mp_div_t1;
	fs_mp_abs();
	if(fsv_mp_globals.fs_mp_error) {
		goto LBL_ERR;
	}
	fsv_mp_globals.fs_mp_abs_a1 = fsv_mp_globals.fs_mp_div_a2;
	fsv_mp_globals.fs_mp_abs_a2 = &fsv_mp_globals.fs_mp_div_t2;
	fs_mp_abs();
	if(fsv_mp_globals.fs_mp_error) {
		goto LBL_ERR;
	}
	fsv_mp_globals.fs_mp_mul_2d_a1 = &fsv_mp_globals.fs_mp_div_t2;
	fsv_mp_globals.fs_mp_mul_2d_a2 = fsv_mp_globals.fs_mp_div_t5;
	fsv_mp_globals.fs_mp_mul_2d_a3 = &fsv_mp_globals.fs_mp_div_t2;
	fs_mp_mul_2d();
	if(fsv_mp_globals.fs_mp_error) {
		goto LBL_ERR;
	}
	fsv_mp_globals.fs_mp_mul_2d_a1 = &fsv_mp_globals.fs_mp_div_t3;
	fsv_mp_globals.fs_mp_mul_2d_a2 = fsv_mp_globals.fs_mp_div_t5;
	fsv_mp_globals.fs_mp_mul_2d_a3 = &fsv_mp_globals.fs_mp_div_t3;
	fs_mp_mul_2d();
	if(fsv_mp_globals.fs_mp_error) {
		goto LBL_ERR;
	}
	while(fsv_mp_globals.fs_mp_div_t5-- >= 0) {
		fsv_mp_globals.fs_mp_cmp_a1 = &fsv_mp_globals.fs_mp_div_t2;
		fsv_mp_globals.fs_mp_cmp_a2 = &fsv_mp_globals.fs_mp_div_t1;
		fs_mp_cmp();
		if(fsv_mp_globals.fs_mp_cmp_r != 1) {
			fsv_mp_globals.fs_mp_sub_a1 = &fsv_mp_globals.fs_mp_div_t1;
			fsv_mp_globals.fs_mp_sub_a2 = &fsv_mp_globals.fs_mp_div_t2;
			fsv_mp_globals.fs_mp_sub_a3 = &fsv_mp_globals.fs_mp_div_t1;
			fs_mp_sub();
			if(fsv_mp_globals.fs_mp_error) {
				goto LBL_ERR;
			}
			fsv_mp_globals.fs_mp_add_a1 = &fsv_mp_globals.fs_mp_div_t4;
			fsv_mp_globals.fs_mp_add_a2 = &fsv_mp_globals.fs_mp_div_t3;
			fsv_mp_globals.fs_mp_add_a3 = &fsv_mp_globals.fs_mp_div_t4;
			fs_mp_add();
			if(fsv_mp_globals.fs_mp_error) {
				goto LBL_ERR;
			}
		}
		fsv_mp_globals.fs_mp_div_2d_a1 = &fsv_mp_globals.fs_mp_div_t2;
		fsv_mp_globals.fs_mp_div_2d_a2 = 1;
		fsv_mp_globals.fs_mp_div_2d_a3 = &fsv_mp_globals.fs_mp_div_t2;
		fsv_mp_globals.fs_mp_div_2d_a4 = NULL;
		fs_mp_div_2d();
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_ERR;
		}
		fsv_mp_globals.fs_mp_div_2d_a1 = &fsv_mp_globals.fs_mp_div_t3;
		fsv_mp_globals.fs_mp_div_2d_a2 = 1;
		fsv_mp_globals.fs_mp_div_2d_a3 = &fsv_mp_globals.fs_mp_div_t3;
		fsv_mp_globals.fs_mp_div_2d_a4 = NULL;
		fs_mp_div_2d();
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_ERR;
		}
	}
	fsv_mp_globals.fs_mp_div_t5  = fsv_mp_globals.fs_mp_div_a1->sign;
	fsv_mp_globals.fs_mp_div_t6 = (fsv_mp_globals.fs_mp_div_a1->sign == fsv_mp_globals.fs_mp_div_a2->sign ? 0 : 1);
	if(fsv_mp_globals.fs_mp_div_a3 != NULL) {
		fsv_mp_globals.fs_mp_exch_a1 = fsv_mp_globals.fs_mp_div_a3;
		fsv_mp_globals.fs_mp_exch_a2 = &fsv_mp_globals.fs_mp_div_t4;
		fs_mp_exch();
		fsv_mp_globals.fs_mp_div_a3->sign  = ((((fsv_mp_globals.fs_mp_div_a3)->used == 0) ? 1 : 0) == 1) ? 0 : fsv_mp_globals.fs_mp_div_t6;
	}
	if(fsv_mp_globals.fs_mp_div_a4 != NULL) {
		fsv_mp_globals.fs_mp_exch_a1 = fsv_mp_globals.fs_mp_div_a4;
		fsv_mp_globals.fs_mp_exch_a2 = &fsv_mp_globals.fs_mp_div_t1;
		fs_mp_exch();
		fsv_mp_globals.fs_mp_div_a4->sign = ((((fsv_mp_globals.fs_mp_div_a4)->used == 0) ? 1 : 0) == 1) ? 0 : fsv_mp_globals.fs_mp_div_t5;
	}
	LBL_ERR:
	fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_div_t1;
	fs_mp_clear();
	fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_div_t2;
	fs_mp_clear();
	fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_div_t3;
	fs_mp_clear();
	fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_div_t4;
	fs_mp_clear();
	done:
	;
}
__FS_FUNCTION_MAYBE_INLINE int fs_mp_cmp_d(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_cmp_d_r = 0;
	if(fsv_mp_globals.fs_mp_cmp_d_a1->sign == 1) {
		fsv_mp_globals.fs_mp_cmp_d_r = -1;
		goto done;
	}
	if(fsv_mp_globals.fs_mp_cmp_d_a1->used > 1) {
		fsv_mp_globals.fs_mp_cmp_d_r = 1;
		goto done;
	}
	if(fsv_mp_globals.fs_mp_cmp_d_a1->dp[0] > fsv_mp_globals.fs_mp_cmp_d_a2) {
		fsv_mp_globals.fs_mp_cmp_d_r = 1;
		goto done;
	} else if(fsv_mp_globals.fs_mp_cmp_d_a1->dp[0] < fsv_mp_globals.fs_mp_cmp_d_a2) {
		fsv_mp_globals.fs_mp_cmp_d_r = -1;
		goto done;
	} else {
		fsv_mp_globals.fs_mp_cmp_d_r = 0;
		goto done;
	}
	done:
	return fsv_mp_globals.fs_mp_cmp_d_r;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_mod(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_init_a1 = &fsv_mp_globals.fs_mp_mod_t1;
	fs_mp_init();
	if(!fsv_mp_globals.fs_mp_mod_t1.dp) {
		fsv_mp_globals.fs_mp_error = 1;
		goto done;
	}
	fsv_mp_globals.fs_mp_div_a1 = fsv_mp_globals.fs_mp_mod_a1;
	fsv_mp_globals.fs_mp_div_a2 = fsv_mp_globals.fs_mp_mod_a2;
	fsv_mp_globals.fs_mp_div_a3 = NULL;
	fsv_mp_globals.fs_mp_div_a4 = &fsv_mp_globals.fs_mp_mod_t1;
	fs_mp_div();
	if(fsv_mp_globals.fs_mp_error) {
		fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_mod_t1;
		fs_mp_clear();
		goto done;
	}
	if(fsv_mp_globals.fs_mp_mod_t1.sign != fsv_mp_globals.fs_mp_mod_a2->sign) {
		fsv_mp_globals.fs_mp_add_a1 = fsv_mp_globals.fs_mp_mod_a2;
		fsv_mp_globals.fs_mp_add_a2 = &fsv_mp_globals.fs_mp_mod_t1;
		fsv_mp_globals.fs_mp_add_a3 = fsv_mp_globals.fs_mp_mod_a3;
		fs_mp_add();
	} else {
		fsv_mp_globals.fs_mp_exch_a1 = &fsv_mp_globals.fs_mp_mod_t1;
		fsv_mp_globals.fs_mp_exch_a2 = fsv_mp_globals.fs_mp_mod_a3;
		fs_mp_exch();
	}
	fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_mod_t1;
	fs_mp_clear();
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_div_2(void) {
	fsv_mp_globals.fs_mp_error = 0;
	if(fsv_mp_globals.fs_mp_div_2_a2->alloc < fsv_mp_globals.fs_mp_div_2_a1->used) {
		fsv_mp_globals.fs_mp_grow_a1 = fsv_mp_globals.fs_mp_div_2_a2;
		fsv_mp_globals.fs_mp_grow_a2 = fsv_mp_globals.fs_mp_div_2_a1->used;
		fs_mp_grow();
		if(fsv_mp_globals.fs_mp_error) {
			goto done;
		}
	}
	fsv_mp_globals.fs_mp_div_2_t2 = fsv_mp_globals.fs_mp_div_2_a2->used;
	fsv_mp_globals.fs_mp_div_2_a2->used = fsv_mp_globals.fs_mp_div_2_a1->used;
	fsv_mp_globals.fs_mp_div_2_t5 = fsv_mp_globals.fs_mp_div_2_a1->dp + fsv_mp_globals.fs_mp_div_2_a2->used - 1;
	fsv_mp_globals.fs_mp_div_2_t6 = fsv_mp_globals.fs_mp_div_2_a2->dp + fsv_mp_globals.fs_mp_div_2_a2->used - 1;
	fsv_mp_globals.fs_mp_div_2_t3 = 0;
	for(fsv_mp_globals.fs_mp_div_2_t1 = fsv_mp_globals.fs_mp_div_2_a2->used - 1; fsv_mp_globals.fs_mp_div_2_t1 >= 0; fsv_mp_globals.fs_mp_div_2_t1--) {
		fsv_mp_globals.fs_mp_div_2_t4 = *fsv_mp_globals.fs_mp_div_2_t5 & 1;
		*fsv_mp_globals.fs_mp_div_2_t6-- = (*fsv_mp_globals.fs_mp_div_2_t5-- >> 1) | (fsv_mp_globals.fs_mp_div_2_t3 << (DIGIT_BIT - 1));
		fsv_mp_globals.fs_mp_div_2_t3 = fsv_mp_globals.fs_mp_div_2_t4;
	}
	fsv_mp_globals.fs_mp_div_2_t6 = fsv_mp_globals.fs_mp_div_2_a2->dp + fsv_mp_globals.fs_mp_div_2_a2->used;
	for(fsv_mp_globals.fs_mp_div_2_t1 = fsv_mp_globals.fs_mp_div_2_a2->used; fsv_mp_globals.fs_mp_div_2_t1 < fsv_mp_globals.fs_mp_div_2_t2; fsv_mp_globals.fs_mp_div_2_t1++) {
		*fsv_mp_globals.fs_mp_div_2_t6++ = 0;
	}
	fsv_mp_globals.fs_mp_div_2_a2->sign = fsv_mp_globals.fs_mp_div_2_a1->sign;
	fsv_mp_globals.fs_mp_clamp_a1 = fsv_mp_globals.fs_mp_div_2_a2;
	fs_mp_clamp();
	done:
	;
}
__FS_FUNCTION_MAYBE_INLINE void fs_mp_invmod(void) {
	fsv_mp_globals.fs_mp_error = 0;
	if(fsv_mp_globals.fs_mp_invmod_a2->sign == 1 || (((fsv_mp_globals.fs_mp_invmod_a2)->used == 0) ? 1 : 0) == 1) {
		fsv_mp_globals.fs_mp_error = -3;
		goto LBL_ERR;
	}
	fsv_mp_globals.fs_mp_init_a1 = &fsv_mp_globals.fs_mp_invmod_t1;
	fs_mp_init();
	fsv_mp_globals.fs_mp_init_a1 = &fsv_mp_globals.fs_mp_invmod_t2;
	fs_mp_init();
	fsv_mp_globals.fs_mp_init_a1 = &fsv_mp_globals.fs_mp_invmod_t3;
	fs_mp_init();
	fsv_mp_globals.fs_mp_init_a1 = &fsv_mp_globals.fs_mp_invmod_t4;
	fs_mp_init();
	fsv_mp_globals.fs_mp_init_a1 = &fsv_mp_globals.fs_mp_invmod_t5;
	fs_mp_init();
	fsv_mp_globals.fs_mp_init_a1 = &fsv_mp_globals.fs_mp_invmod_t6;
	fs_mp_init();
	fsv_mp_globals.fs_mp_init_a1 = &fsv_mp_globals.fs_mp_invmod_t7;
	fs_mp_init();
	fsv_mp_globals.fs_mp_init_a1 = &fsv_mp_globals.fs_mp_invmod_t8;
	fs_mp_init();
	if(!fsv_mp_globals.fs_mp_invmod_t1.dp
	   || !fsv_mp_globals.fs_mp_invmod_t2.dp
	   || !fsv_mp_globals.fs_mp_invmod_t3.dp
	   || !fsv_mp_globals.fs_mp_invmod_t4.dp
	   || !fsv_mp_globals.fs_mp_invmod_t5.dp
	   || !fsv_mp_globals.fs_mp_invmod_t6.dp
	   || !fsv_mp_globals.fs_mp_invmod_t7.dp
	   || !fsv_mp_globals.fs_mp_invmod_t8.dp) {
		fsv_mp_globals.fs_mp_error = 1;
		goto LBL_ERR;
	}
	fsv_mp_globals.fs_mp_mod_a1 = fsv_mp_globals.fs_mp_invmod_a1;
	fsv_mp_globals.fs_mp_mod_a2 = fsv_mp_globals.fs_mp_invmod_a2;
	fsv_mp_globals.fs_mp_mod_a3 = &fsv_mp_globals.fs_mp_invmod_t1;
	fs_mp_mod();
	if(fsv_mp_globals.fs_mp_error) {
		goto LBL_ERR;
	}
	fsv_mp_globals.fs_mp_copy_a1 = fsv_mp_globals.fs_mp_invmod_a2;
	fsv_mp_globals.fs_mp_copy_a2 = &fsv_mp_globals.fs_mp_invmod_t2;
	fs_mp_copy();
	if(fsv_mp_globals.fs_mp_error) {
		goto LBL_ERR;
	}
	if((((&fsv_mp_globals.fs_mp_invmod_t1)->used > 0 && (((&fsv_mp_globals.fs_mp_invmod_t1)->dp[0] & 1) == 0)) ? 1 : 0) == 1 && (((&fsv_mp_globals.fs_mp_invmod_t2)->used > 0 && (((&fsv_mp_globals.fs_mp_invmod_t2)->dp[0] & 1) == 0)) ? 1 : 0) == 1) {
		fsv_mp_globals.fs_mp_error = -3;
		goto LBL_ERR;
	}
	fsv_mp_globals.fs_mp_copy_a1 = &fsv_mp_globals.fs_mp_invmod_t1;
	fsv_mp_globals.fs_mp_copy_a2 = &fsv_mp_globals.fs_mp_invmod_t3;
	fs_mp_copy();
	if(fsv_mp_globals.fs_mp_error) {
		goto LBL_ERR;
	}
	fsv_mp_globals.fs_mp_copy_a1 = &fsv_mp_globals.fs_mp_invmod_t2;
	fsv_mp_globals.fs_mp_copy_a2 = &fsv_mp_globals.fs_mp_invmod_t4;
	fs_mp_copy();
	if(fsv_mp_globals.fs_mp_error) {
		goto LBL_ERR;
	}
	fsv_mp_globals.fs_mp_set_a1 = &fsv_mp_globals.fs_mp_invmod_t5;
	fsv_mp_globals.fs_mp_set_a2 =  1;
	fs_mp_set();
	fsv_mp_globals.fs_mp_set_a1 = &fsv_mp_globals.fs_mp_invmod_t8;
	fsv_mp_globals.fs_mp_set_a2 =  1;
	fs_mp_set();
	top:
	while((((&fsv_mp_globals.fs_mp_invmod_t3)->used > 0 && (((&fsv_mp_globals.fs_mp_invmod_t3)->dp[0] & 1) == 0)) ? 1 : 0) == 1) {
		fsv_mp_globals.fs_mp_div_2_a1 = &fsv_mp_globals.fs_mp_invmod_t3;
		fsv_mp_globals.fs_mp_div_2_a2 = &fsv_mp_globals.fs_mp_invmod_t3;
		fs_mp_div_2();
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_ERR;
		}
		if((((&fsv_mp_globals.fs_mp_invmod_t5)->used > 0 && (((&fsv_mp_globals.fs_mp_invmod_t5)->dp[0] & 1) == 1)) ? 1 : 0) == 1 || (((&fsv_mp_globals.fs_mp_invmod_t6)->used > 0 && (((&fsv_mp_globals.fs_mp_invmod_t6)->dp[0] & 1) == 1)) ? 1 : 0) == 1) {
			fsv_mp_globals.fs_mp_add_a1 = &fsv_mp_globals.fs_mp_invmod_t5;
			fsv_mp_globals.fs_mp_add_a2 = &fsv_mp_globals.fs_mp_invmod_t2;
			fsv_mp_globals.fs_mp_add_a3 = &fsv_mp_globals.fs_mp_invmod_t5;
			fs_mp_add();
			if(fsv_mp_globals.fs_mp_error) {
				goto LBL_ERR;
			}
			fsv_mp_globals.fs_mp_sub_a1 = &fsv_mp_globals.fs_mp_invmod_t6;
			fsv_mp_globals.fs_mp_sub_a2 = &fsv_mp_globals.fs_mp_invmod_t1;
			fsv_mp_globals.fs_mp_sub_a3 = &fsv_mp_globals.fs_mp_invmod_t6;
			fs_mp_sub();
			if(fsv_mp_globals.fs_mp_error) {
				goto LBL_ERR;
			}
		}
		fsv_mp_globals.fs_mp_div_2_a1 = &fsv_mp_globals.fs_mp_invmod_t5;
		fsv_mp_globals.fs_mp_div_2_a2 = &fsv_mp_globals.fs_mp_invmod_t5;
		fs_mp_div_2();
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_ERR;
		}
		fsv_mp_globals.fs_mp_div_2_a1 = &fsv_mp_globals.fs_mp_invmod_t6;
		fsv_mp_globals.fs_mp_div_2_a2 = &fsv_mp_globals.fs_mp_invmod_t6;
		fs_mp_div_2();
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_ERR;
		}
	}
	while((((&fsv_mp_globals.fs_mp_invmod_t4)->used > 0 && (((&fsv_mp_globals.fs_mp_invmod_t4)->dp[0] & 1) == 0)) ? 1 : 0) == 1) {
		fsv_mp_globals.fs_mp_div_2_a1 = &fsv_mp_globals.fs_mp_invmod_t4;
		fsv_mp_globals.fs_mp_div_2_a2 = &fsv_mp_globals.fs_mp_invmod_t4;
		fs_mp_div_2();
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_ERR;
		}
		if((((&fsv_mp_globals.fs_mp_invmod_t7)->used > 0 && (((&fsv_mp_globals.fs_mp_invmod_t7)->dp[0] & 1) == 1)) ? 1 : 0) == 1 || (((&fsv_mp_globals.fs_mp_invmod_t8)->used > 0 && (((&fsv_mp_globals.fs_mp_invmod_t8)->dp[0] & 1) == 1)) ? 1 : 0) == 1) {
			fsv_mp_globals.fs_mp_add_a1 = &fsv_mp_globals.fs_mp_invmod_t7;
			fsv_mp_globals.fs_mp_add_a2 = &fsv_mp_globals.fs_mp_invmod_t2;
			fsv_mp_globals.fs_mp_add_a3 = &fsv_mp_globals.fs_mp_invmod_t7;
			fs_mp_add();
			if(fsv_mp_globals.fs_mp_error) {
				goto LBL_ERR;
			}
			fsv_mp_globals.fs_mp_sub_a1 = &fsv_mp_globals.fs_mp_invmod_t8;
			fsv_mp_globals.fs_mp_sub_a2 = &fsv_mp_globals.fs_mp_invmod_t1;
			fsv_mp_globals.fs_mp_sub_a3 = &fsv_mp_globals.fs_mp_invmod_t8;
			fs_mp_sub();
			if(fsv_mp_globals.fs_mp_error) {
				goto LBL_ERR;
			}
		}
		fsv_mp_globals.fs_mp_div_2_a1 = &fsv_mp_globals.fs_mp_invmod_t7;
		fsv_mp_globals.fs_mp_div_2_a2 = &fsv_mp_globals.fs_mp_invmod_t7;
		fs_mp_div_2();
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_ERR;
		}
		fsv_mp_globals.fs_mp_div_2_a1 = &fsv_mp_globals.fs_mp_invmod_t8;
		fsv_mp_globals.fs_mp_div_2_a2 = &fsv_mp_globals.fs_mp_invmod_t8;
		fs_mp_div_2();
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_ERR;
		}
	}
	fsv_mp_globals.fs_mp_cmp_a1 = &fsv_mp_globals.fs_mp_invmod_t3;
	fsv_mp_globals.fs_mp_cmp_a2 = &fsv_mp_globals.fs_mp_invmod_t4;
	fs_mp_cmp();
	if(fsv_mp_globals.fs_mp_cmp_r != -1) {
		fsv_mp_globals.fs_mp_sub_a1 = &fsv_mp_globals.fs_mp_invmod_t3;
		fsv_mp_globals.fs_mp_sub_a2 = &fsv_mp_globals.fs_mp_invmod_t4;
		fsv_mp_globals.fs_mp_sub_a3 = &fsv_mp_globals.fs_mp_invmod_t3;
		fs_mp_sub();
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_ERR;
		}
		fsv_mp_globals.fs_mp_sub_a1 = &fsv_mp_globals.fs_mp_invmod_t5;
		fsv_mp_globals.fs_mp_sub_a2 = &fsv_mp_globals.fs_mp_invmod_t7;
		fsv_mp_globals.fs_mp_sub_a3 = &fsv_mp_globals.fs_mp_invmod_t5;
		fs_mp_sub();
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_ERR;
		}
		fsv_mp_globals.fs_mp_sub_a1 = &fsv_mp_globals.fs_mp_invmod_t6;
		fsv_mp_globals.fs_mp_sub_a2 = &fsv_mp_globals.fs_mp_invmod_t8;
		fsv_mp_globals.fs_mp_sub_a3 = &fsv_mp_globals.fs_mp_invmod_t6;
		fs_mp_sub();
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_ERR;
		}
	} else {
		fsv_mp_globals.fs_mp_sub_a1 = &fsv_mp_globals.fs_mp_invmod_t4;
		fsv_mp_globals.fs_mp_sub_a2 = &fsv_mp_globals.fs_mp_invmod_t3;
		fsv_mp_globals.fs_mp_sub_a3 = &fsv_mp_globals.fs_mp_invmod_t4;
		fs_mp_sub();
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_ERR;
		}
		fsv_mp_globals.fs_mp_sub_a1 = &fsv_mp_globals.fs_mp_invmod_t7;
		fsv_mp_globals.fs_mp_sub_a2 = &fsv_mp_globals.fs_mp_invmod_t5;
		fsv_mp_globals.fs_mp_sub_a3 = &fsv_mp_globals.fs_mp_invmod_t7;
		fs_mp_sub();
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_ERR;
		}
		fsv_mp_globals.fs_mp_sub_a1 = &fsv_mp_globals.fs_mp_invmod_t8;
		fsv_mp_globals.fs_mp_sub_a2 = &fsv_mp_globals.fs_mp_invmod_t6;
		fsv_mp_globals.fs_mp_sub_a3 = &fsv_mp_globals.fs_mp_invmod_t8;
		fs_mp_sub();
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_ERR;
		}
	}
	if((((&fsv_mp_globals.fs_mp_invmod_t3)->used == 0) ? 1 : 0) == 0)
		goto top;
	fsv_mp_globals.fs_mp_cmp_d_a1 = &fsv_mp_globals.fs_mp_invmod_t4;
	fsv_mp_globals.fs_mp_cmp_d_a2 = 1;
	fs_mp_cmp_d();
	if(fsv_mp_globals.fs_mp_cmp_d_r != 0) {
		fsv_mp_globals.fs_mp_error = -3;
		goto LBL_ERR;
	}

	fsv_mp_globals.fs_mp_cmp_d_a1 = &fsv_mp_globals.fs_mp_invmod_t7;
	fsv_mp_globals.fs_mp_cmp_d_a2 = 0;
	fs_mp_cmp_d();
	while(fsv_mp_globals.fs_mp_cmp_d_r == -1) {
		fsv_mp_globals.fs_mp_add_a1 = &fsv_mp_globals.fs_mp_invmod_t7;
		fsv_mp_globals.fs_mp_add_a2 = fsv_mp_globals.fs_mp_invmod_a2;
		fsv_mp_globals.fs_mp_add_a3 = &fsv_mp_globals.fs_mp_invmod_t7;
		fs_mp_add();
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_ERR;
		}
		fs_mp_cmp_d();
	}
	fsv_mp_globals.fs_mp_cmp_mag_a1 = &fsv_mp_globals.fs_mp_invmod_t7;
	fsv_mp_globals.fs_mp_cmp_mag_a2 = fsv_mp_globals.fs_mp_invmod_a2;
	fs_mp_cmp_mag();
	while(fsv_mp_globals.fs_mp_cmp_mag_r != -1) {
		fsv_mp_globals.fs_mp_sub_a1 = &fsv_mp_globals.fs_mp_invmod_t7;
		fsv_mp_globals.fs_mp_sub_a2 = fsv_mp_globals.fs_mp_invmod_a2;
		fsv_mp_globals.fs_mp_sub_a3 = &fsv_mp_globals.fs_mp_invmod_t7;
		fs_mp_sub();
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_ERR;
		}
		fs_mp_cmp_mag();
	}
	fsv_mp_globals.fs_mp_exch_a1 = &fsv_mp_globals.fs_mp_invmod_t7;
	fsv_mp_globals.fs_mp_exch_a2 = fsv_mp_globals.fs_mp_invmod_a3;
	fs_mp_exch();
	fsv_mp_globals.fs_mp_error = 0;
	LBL_ERR:
	fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_invmod_t1;
	fs_mp_clear();
	fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_invmod_t2;
	fs_mp_clear();
	fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_invmod_t3;
	fs_mp_clear();
	fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_invmod_t4;
	fs_mp_clear();
	fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_invmod_t5;
	fs_mp_clear();
	fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_invmod_t6;
	fs_mp_clear();
	fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_invmod_t7;
	fs_mp_clear();
	fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_invmod_t8;
	fs_mp_clear();
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_reduce_setup(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_2expt_a1 = fsv_mp_globals.fs_mp_reduce_setup_a1;
	fsv_mp_globals.fs_mp_2expt_a2 = fsv_mp_globals.fs_mp_reduce_setup_a2->used * 2 * DIGIT_BIT;
	fs_mp_2expt();
	if(fsv_mp_globals.fs_mp_error) {
		goto done;
	}
	fsv_mp_globals.fs_mp_div_a1 = fsv_mp_globals.fs_mp_reduce_setup_a1;
	fsv_mp_globals.fs_mp_div_a2 = fsv_mp_globals.fs_mp_reduce_setup_a2;
	fsv_mp_globals.fs_mp_div_a3 = fsv_mp_globals.fs_mp_reduce_setup_a1;
	fsv_mp_globals.fs_mp_div_a4 = NULL;
	fs_mp_div();
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_fast_s_mul_digs(void) {
	fsv_mp_globals.fs_mp_error = 0;
	if(fsv_mp_globals.fs_mp_fast_s_mul_digs_a3->alloc < fsv_mp_globals.fs_mp_fast_s_mul_digs_a4) {
		fsv_mp_globals.fs_mp_grow_a1 = fsv_mp_globals.fs_mp_fast_s_mul_digs_a3;
		fsv_mp_globals.fs_mp_grow_a2 = fsv_mp_globals.fs_mp_fast_s_mul_digs_a4;
		fs_mp_grow();
		if(fsv_mp_globals.fs_mp_error) {
			goto done;
		}
	}
	fsv_mp_globals.fs_mp_fast_s_mul_digs_t2 = fsv_mp_globals.fs_mp_fast_s_mul_digs_a4 < (fsv_mp_globals.fs_mp_fast_s_mul_digs_a1->used + fsv_mp_globals.fs_mp_fast_s_mul_digs_a2->used) ? fsv_mp_globals.fs_mp_fast_s_mul_digs_a4 : (fsv_mp_globals.fs_mp_fast_s_mul_digs_a1->used + fsv_mp_globals.fs_mp_fast_s_mul_digs_a2->used);
	fsv_mp_globals.fs_mp_fast_s_mul_digs_t6 = 0;
	for(fsv_mp_globals.fs_mp_fast_s_mul_digs_t3 = 0; fsv_mp_globals.fs_mp_fast_s_mul_digs_t3 < fsv_mp_globals.fs_mp_fast_s_mul_digs_t2; fsv_mp_globals.fs_mp_fast_s_mul_digs_t3++) {
		fsv_mp_globals.fs_mp_fast_s_mul_digs_t8 = (fsv_mp_globals.fs_mp_fast_s_mul_digs_a2->used-1) < fsv_mp_globals.fs_mp_fast_s_mul_digs_t3 ? (fsv_mp_globals.fs_mp_fast_s_mul_digs_a2->used-1) : fsv_mp_globals.fs_mp_fast_s_mul_digs_t3;
		fsv_mp_globals.fs_mp_fast_s_mul_digs_t7 = fsv_mp_globals.fs_mp_fast_s_mul_digs_t3 - fsv_mp_globals.fs_mp_fast_s_mul_digs_t8;
		fsv_mp_globals.fs_mp_fast_s_mul_digs_t10 = fsv_mp_globals.fs_mp_fast_s_mul_digs_a1->dp + fsv_mp_globals.fs_mp_fast_s_mul_digs_t7;
		fsv_mp_globals.fs_mp_fast_s_mul_digs_t11 = fsv_mp_globals.fs_mp_fast_s_mul_digs_a2->dp + fsv_mp_globals.fs_mp_fast_s_mul_digs_t8;
		fsv_mp_globals.fs_mp_fast_s_mul_digs_t9 = (fsv_mp_globals.fs_mp_fast_s_mul_digs_a1->used - fsv_mp_globals.fs_mp_fast_s_mul_digs_t7) < (fsv_mp_globals.fs_mp_fast_s_mul_digs_t8+1) ? (fsv_mp_globals.fs_mp_fast_s_mul_digs_a1->used - fsv_mp_globals.fs_mp_fast_s_mul_digs_t7) : (fsv_mp_globals.fs_mp_fast_s_mul_digs_t8+1);
		for(fsv_mp_globals.fs_mp_fast_s_mul_digs_t4 = 0; fsv_mp_globals.fs_mp_fast_s_mul_digs_t4 < fsv_mp_globals.fs_mp_fast_s_mul_digs_t9; ++fsv_mp_globals.fs_mp_fast_s_mul_digs_t4) {
			fsv_mp_globals.fs_mp_fast_s_mul_digs_t6 += ((fs_mp_word)*fsv_mp_globals.fs_mp_fast_s_mul_digs_t10++)*((fs_mp_word)*fsv_mp_globals.fs_mp_fast_s_mul_digs_t11--);
		}
		fsv_mp_globals.fs_mp_fast_s_mul_digs_t5[fsv_mp_globals.fs_mp_fast_s_mul_digs_t3] = ((fs_mp_digit)fsv_mp_globals.fs_mp_fast_s_mul_digs_t6) & ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1));
		fsv_mp_globals.fs_mp_fast_s_mul_digs_t6 = fsv_mp_globals.fs_mp_fast_s_mul_digs_t6 >> ((fs_mp_word)DIGIT_BIT);
	}
	fsv_mp_globals.fs_mp_fast_s_mul_digs_t1  = fsv_mp_globals.fs_mp_fast_s_mul_digs_a3->used;
	fsv_mp_globals.fs_mp_fast_s_mul_digs_a3->used = fsv_mp_globals.fs_mp_fast_s_mul_digs_t2;
	fsv_mp_globals.fs_mp_fast_s_mul_digs_t12 = fsv_mp_globals.fs_mp_fast_s_mul_digs_a3->dp;
	for(fsv_mp_globals.fs_mp_fast_s_mul_digs_t3 = 0; fsv_mp_globals.fs_mp_fast_s_mul_digs_t3 < fsv_mp_globals.fs_mp_fast_s_mul_digs_t2+1; fsv_mp_globals.fs_mp_fast_s_mul_digs_t3++) {
		*fsv_mp_globals.fs_mp_fast_s_mul_digs_t12++ = fsv_mp_globals.fs_mp_fast_s_mul_digs_t5[fsv_mp_globals.fs_mp_fast_s_mul_digs_t3];
	}
	for(; fsv_mp_globals.fs_mp_fast_s_mul_digs_t3 < fsv_mp_globals.fs_mp_fast_s_mul_digs_t1; fsv_mp_globals.fs_mp_fast_s_mul_digs_t3++) {
		*fsv_mp_globals.fs_mp_fast_s_mul_digs_t12++ = 0;
	}
	fsv_mp_globals.fs_mp_clamp_a1 = fsv_mp_globals.fs_mp_fast_s_mul_digs_a3;
	fs_mp_clamp();
	done:
	;
}
__FS_FUNCTION_MAYBE_INLINE void fs_mp_init_size(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_init_size_a2 += (FS_MP_PREC * 2) - (fsv_mp_globals.fs_mp_init_size_a2 % FS_MP_PREC);
	fsv_mp_globals.fs_mp_init_size_a1->dp = (fs_mp_digit*)fs_malloc(sizeof (fs_mp_digit) * fsv_mp_globals.fs_mp_init_size_a2);
	if(fsv_mp_globals.fs_mp_init_size_a1->dp == NULL) {
		fsv_mp_globals.fs_mp_error = 1;
		goto done;
	}
	fsv_mp_globals.fs_mp_init_size_a1->used  = 0;
	fsv_mp_globals.fs_mp_init_size_a1->alloc = fsv_mp_globals.fs_mp_init_size_a2;
	fsv_mp_globals.fs_mp_init_size_a1->sign  = 0;
	for(fsv_mp_globals.fs_mp_init_size_t1 = 0; fsv_mp_globals.fs_mp_init_size_t1 < fsv_mp_globals.fs_mp_init_size_a2; fsv_mp_globals.fs_mp_init_size_t1++) {
		fsv_mp_globals.fs_mp_init_size_a1->dp[fsv_mp_globals.fs_mp_init_size_t1] = 0;
	}
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_s_mul_digs(void) {
	fsv_mp_globals.fs_mp_error = 0;
	if(((fsv_mp_globals.fs_mp_s_mul_digs_a4) < (1 << (sizeof(fs_mp_word) * 8 - 2 * DIGIT_BIT + 1))) &&
	   (fsv_mp_globals.fs_mp_s_mul_digs_a1->used < fsv_mp_globals.fs_mp_s_mul_digs_a2->used ? fsv_mp_globals.fs_mp_s_mul_digs_a1->used : fsv_mp_globals.fs_mp_s_mul_digs_a2->used) <
	   (1 << ((8 * sizeof (fs_mp_word)) - (2 * DIGIT_BIT)))) {
		fsv_mp_globals.fs_mp_fast_s_mul_digs_a1 = fsv_mp_globals.fs_mp_s_mul_digs_a1;
		fsv_mp_globals.fs_mp_fast_s_mul_digs_a2 = fsv_mp_globals.fs_mp_s_mul_digs_a2;
		fsv_mp_globals.fs_mp_fast_s_mul_digs_a3 = fsv_mp_globals.fs_mp_s_mul_digs_a3;
		fsv_mp_globals.fs_mp_fast_s_mul_digs_a4 = fsv_mp_globals.fs_mp_s_mul_digs_a4;
		fs_mp_fast_s_mul_digs();
		goto done;
	}
	fsv_mp_globals.fs_mp_init_size_a1 = &fsv_mp_globals.fs_mp_s_mul_digs_t1;
	fsv_mp_globals.fs_mp_init_size_a2 = fsv_mp_globals.fs_mp_s_mul_digs_a4;
	fs_mp_init_size();
	if(fsv_mp_globals.fs_mp_error) {
		goto done;
	}
	fsv_mp_globals.fs_mp_s_mul_digs_t1.used = fsv_mp_globals.fs_mp_s_mul_digs_a4;
	fsv_mp_globals.fs_mp_s_mul_digs_t2 = fsv_mp_globals.fs_mp_s_mul_digs_a1->used;
	for(fsv_mp_globals.fs_mp_s_mul_digs_t4 = 0; fsv_mp_globals.fs_mp_s_mul_digs_t4 < fsv_mp_globals.fs_mp_s_mul_digs_t2; fsv_mp_globals.fs_mp_s_mul_digs_t4++) {
		fsv_mp_globals.fs_mp_s_mul_digs_t6 = 0;
		fsv_mp_globals.fs_mp_s_mul_digs_t3 = fsv_mp_globals.fs_mp_s_mul_digs_a2->used < (fsv_mp_globals.fs_mp_s_mul_digs_a4 - fsv_mp_globals.fs_mp_s_mul_digs_t4) ? fsv_mp_globals.fs_mp_s_mul_digs_a2->used : (fsv_mp_globals.fs_mp_s_mul_digs_a4 - fsv_mp_globals.fs_mp_s_mul_digs_t4);
		fsv_mp_globals.fs_mp_s_mul_digs_t8 = fsv_mp_globals.fs_mp_s_mul_digs_a1->dp[fsv_mp_globals.fs_mp_s_mul_digs_t4];
		fsv_mp_globals.fs_mp_s_mul_digs_t9 = fsv_mp_globals.fs_mp_s_mul_digs_t1.dp + fsv_mp_globals.fs_mp_s_mul_digs_t4;
		fsv_mp_globals.fs_mp_s_mul_digs_t10 = fsv_mp_globals.fs_mp_s_mul_digs_a2->dp;
		for(fsv_mp_globals.fs_mp_s_mul_digs_t5 = 0; fsv_mp_globals.fs_mp_s_mul_digs_t5 < fsv_mp_globals.fs_mp_s_mul_digs_t3; fsv_mp_globals.fs_mp_s_mul_digs_t5++) {
			fsv_mp_globals.fs_mp_s_mul_digs_t7       = ((fs_mp_word)*fsv_mp_globals.fs_mp_s_mul_digs_t9) +
						      ((fs_mp_word)fsv_mp_globals.fs_mp_s_mul_digs_t8) * ((fs_mp_word)*fsv_mp_globals.fs_mp_s_mul_digs_t10++) +
						      ((fs_mp_word) fsv_mp_globals.fs_mp_s_mul_digs_t6);
			*fsv_mp_globals.fs_mp_s_mul_digs_t9++ = (fs_mp_digit) (fsv_mp_globals.fs_mp_s_mul_digs_t7 & ((fs_mp_word) ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1))));
			fsv_mp_globals.fs_mp_s_mul_digs_t6       = (fs_mp_digit) (fsv_mp_globals.fs_mp_s_mul_digs_t7 >> ((fs_mp_word) DIGIT_BIT));
		}
		if(fsv_mp_globals.fs_mp_s_mul_digs_t4 + fsv_mp_globals.fs_mp_s_mul_digs_t5 < fsv_mp_globals.fs_mp_s_mul_digs_a4) {
			*fsv_mp_globals.fs_mp_s_mul_digs_t9 = fsv_mp_globals.fs_mp_s_mul_digs_t6;
		}
	}
	fsv_mp_globals.fs_mp_clamp_a1 = &fsv_mp_globals.fs_mp_s_mul_digs_t1;
	fs_mp_clamp();
	fsv_mp_globals.fs_mp_exch_a1 = &fsv_mp_globals.fs_mp_s_mul_digs_t1;
	fsv_mp_globals.fs_mp_exch_a2 = fsv_mp_globals.fs_mp_s_mul_digs_a3;
	fs_mp_exch();
	fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_s_mul_digs_t1;
	fs_mp_clear();
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_mul(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_mul_t1 = (fsv_mp_globals.fs_mp_mul_a1->sign == fsv_mp_globals.fs_mp_mul_a2->sign) ? 0 : 1;
	fsv_mp_globals.fs_mp_s_mul_digs_a1 = fsv_mp_globals.fs_mp_mul_a1;
	fsv_mp_globals.fs_mp_s_mul_digs_a2 = fsv_mp_globals.fs_mp_mul_a2;
	fsv_mp_globals.fs_mp_s_mul_digs_a3 = fsv_mp_globals.fs_mp_mul_a3;
	fsv_mp_globals.fs_mp_s_mul_digs_a4 = fsv_mp_globals.fs_mp_mul_a1->used + fsv_mp_globals.fs_mp_mul_a2->used + 1;
	fs_mp_s_mul_digs();
	fsv_mp_globals.fs_mp_mul_a3->sign = (fsv_mp_globals.fs_mp_mul_a3->used > 0) ? fsv_mp_globals.fs_mp_mul_t1 : 0;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_s_mul_high_digs(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_init_size_a1 = &fsv_mp_globals.fs_mp_s_mul_high_digs_t1;
	fsv_mp_globals.fs_mp_init_size_a2 = fsv_mp_globals.fs_mp_s_mul_high_digs_a1->used + fsv_mp_globals.fs_mp_s_mul_high_digs_a2->used + 1;
	fs_mp_init_size();
	if(fsv_mp_globals.fs_mp_error) {
		goto done;
	}
	fsv_mp_globals.fs_mp_s_mul_high_digs_t1.used = fsv_mp_globals.fs_mp_s_mul_high_digs_a1->used + fsv_mp_globals.fs_mp_s_mul_high_digs_a2->used + 1;
	fsv_mp_globals.fs_mp_s_mul_high_digs_t2 = fsv_mp_globals.fs_mp_s_mul_high_digs_a1->used;
	fsv_mp_globals.fs_mp_s_mul_high_digs_t3 = fsv_mp_globals.fs_mp_s_mul_high_digs_a2->used;
	for(fsv_mp_globals.fs_mp_s_mul_high_digs_t4 = 0; fsv_mp_globals.fs_mp_s_mul_high_digs_t4 < fsv_mp_globals.fs_mp_s_mul_high_digs_t2; fsv_mp_globals.fs_mp_s_mul_high_digs_t4++) {
		fsv_mp_globals.fs_mp_s_mul_high_digs_t6 = 0;
		fsv_mp_globals.fs_mp_s_mul_high_digs_t10 = fsv_mp_globals.fs_mp_s_mul_high_digs_a1->dp[fsv_mp_globals.fs_mp_s_mul_high_digs_t4];
		fsv_mp_globals.fs_mp_s_mul_high_digs_t8 = &(fsv_mp_globals.fs_mp_s_mul_high_digs_t1.dp[fsv_mp_globals.fs_mp_s_mul_high_digs_a4]);
		fsv_mp_globals.fs_mp_s_mul_high_digs_t9 = fsv_mp_globals.fs_mp_s_mul_high_digs_a2->dp + (fsv_mp_globals.fs_mp_s_mul_high_digs_a4 - fsv_mp_globals.fs_mp_s_mul_high_digs_t4);
		for(fsv_mp_globals.fs_mp_s_mul_high_digs_t5 = fsv_mp_globals.fs_mp_s_mul_high_digs_a4 - fsv_mp_globals.fs_mp_s_mul_high_digs_t4; fsv_mp_globals.fs_mp_s_mul_high_digs_t5 < fsv_mp_globals.fs_mp_s_mul_high_digs_t3; fsv_mp_globals.fs_mp_s_mul_high_digs_t5++) {
			fsv_mp_globals.fs_mp_s_mul_high_digs_t7       = ((fs_mp_word)*fsv_mp_globals.fs_mp_s_mul_high_digs_t8) +
							   ((fs_mp_word)fsv_mp_globals.fs_mp_s_mul_high_digs_t10) * ((fs_mp_word)*fsv_mp_globals.fs_mp_s_mul_high_digs_t9++) +
							   ((fs_mp_word) fsv_mp_globals.fs_mp_s_mul_high_digs_t6);
			*fsv_mp_globals.fs_mp_s_mul_high_digs_t8++ = (fs_mp_digit) (fsv_mp_globals.fs_mp_s_mul_high_digs_t7 & ((fs_mp_word) ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1))));
			fsv_mp_globals.fs_mp_s_mul_high_digs_t6       = (fs_mp_digit) (fsv_mp_globals.fs_mp_s_mul_high_digs_t7 >> ((fs_mp_word) DIGIT_BIT));
		}
		*fsv_mp_globals.fs_mp_s_mul_high_digs_t8 = fsv_mp_globals.fs_mp_s_mul_high_digs_t6;
	}
	fsv_mp_globals.fs_mp_clamp_a1 = &fsv_mp_globals.fs_mp_s_mul_high_digs_t1;
	fs_mp_clamp();
	fsv_mp_globals.fs_mp_exch_a1 = &fsv_mp_globals.fs_mp_s_mul_high_digs_t1;
	fsv_mp_globals.fs_mp_exch_a2 = fsv_mp_globals.fs_mp_s_mul_high_digs_a3;
	fs_mp_exch();
	fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_s_mul_high_digs_t1;
	fs_mp_clear();
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_reduce(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_reduce_t2 = fsv_mp_globals.fs_mp_reduce_a2->used;
	fsv_mp_globals.fs_mp_init_copy_a1 = &fsv_mp_globals.fs_mp_reduce_t1;
	fsv_mp_globals.fs_mp_init_copy_a2 = fsv_mp_globals.fs_mp_reduce_a1;
	fs_mp_init_copy();
	if(fsv_mp_globals.fs_mp_error) {
		goto done;
	}
	fsv_mp_globals.fs_mp_rshd_a1 = &fsv_mp_globals.fs_mp_reduce_t1;
	fsv_mp_globals.fs_mp_rshd_a2 = fsv_mp_globals.fs_mp_reduce_t2 - 1;
	fs_mp_rshd();
	if(((unsigned long) fsv_mp_globals.fs_mp_reduce_t2) > (((fs_mp_digit)1) << (DIGIT_BIT - 1))) {
		fsv_mp_globals.fs_mp_mul_a1 = &fsv_mp_globals.fs_mp_reduce_t1;
		fsv_mp_globals.fs_mp_mul_a2 = fsv_mp_globals.fs_mp_reduce_a3;
		fsv_mp_globals.fs_mp_mul_a3 = &fsv_mp_globals.fs_mp_reduce_t1;
		fs_mp_mul();
		if(fsv_mp_globals.fs_mp_error) {
			goto CLEANUP;
		}
	} else {
		fsv_mp_globals.fs_mp_s_mul_high_digs_a1 = &fsv_mp_globals.fs_mp_reduce_t1;
		fsv_mp_globals.fs_mp_s_mul_high_digs_a2 = fsv_mp_globals.fs_mp_reduce_a3;
		fsv_mp_globals.fs_mp_s_mul_high_digs_a3 = &fsv_mp_globals.fs_mp_reduce_t1;
		fsv_mp_globals.fs_mp_s_mul_high_digs_a4 = fsv_mp_globals.fs_mp_reduce_t2;
		fs_mp_s_mul_high_digs();
		if(fsv_mp_globals.fs_mp_error) {
			goto CLEANUP;
		}
	}
	fsv_mp_globals.fs_mp_rshd_a1 = &fsv_mp_globals.fs_mp_reduce_t1;
	fsv_mp_globals.fs_mp_rshd_a2 = fsv_mp_globals.fs_mp_reduce_t2 + 1;
	fs_mp_rshd();
	fsv_mp_globals.fs_mp_mod_2d_a1 = fsv_mp_globals.fs_mp_reduce_a1;
	fsv_mp_globals.fs_mp_mod_2d_a2 = DIGIT_BIT * (fsv_mp_globals.fs_mp_reduce_t2 + 1);
	fsv_mp_globals.fs_mp_mod_2d_a3 = fsv_mp_globals.fs_mp_reduce_a1;
	fs_mp_mod_2d();
	if(fsv_mp_globals.fs_mp_error) {
		goto CLEANUP;
	}
	fsv_mp_globals.fs_mp_s_mul_digs_a1 = &fsv_mp_globals.fs_mp_reduce_t1;
	fsv_mp_globals.fs_mp_s_mul_digs_a2 = fsv_mp_globals.fs_mp_reduce_a2;
	fsv_mp_globals.fs_mp_s_mul_digs_a3 = &fsv_mp_globals.fs_mp_reduce_t1;
	fsv_mp_globals.fs_mp_s_mul_digs_a4 = fsv_mp_globals.fs_mp_reduce_t2 + 1;
	fs_mp_s_mul_digs();
	if(fsv_mp_globals.fs_mp_error) {
		goto CLEANUP;
	}
	fsv_mp_globals.fs_mp_sub_a1 = fsv_mp_globals.fs_mp_reduce_a1;
	fsv_mp_globals.fs_mp_sub_a2 = &fsv_mp_globals.fs_mp_reduce_t1;
	fsv_mp_globals.fs_mp_sub_a3 = fsv_mp_globals.fs_mp_reduce_a1;
	fs_mp_sub();
	if(fsv_mp_globals.fs_mp_error) {
		goto CLEANUP;
	}
	fsv_mp_globals.fs_mp_cmp_d_a1 = fsv_mp_globals.fs_mp_reduce_a1;
	fsv_mp_globals.fs_mp_cmp_d_a2 = 0;
	fs_mp_cmp_d();
	if(fsv_mp_globals.fs_mp_cmp_d_r == -1) {
		fsv_mp_globals.fs_mp_set_a1 = &fsv_mp_globals.fs_mp_reduce_t1;
		fsv_mp_globals.fs_mp_set_a2 =  1;
		fs_mp_set();
		fsv_mp_globals.fs_mp_lshd_a1 = &fsv_mp_globals.fs_mp_reduce_t1;
		fsv_mp_globals.fs_mp_lshd_a2 = fsv_mp_globals.fs_mp_reduce_t2 + 1;
		fs_mp_lshd();
		if(fsv_mp_globals.fs_mp_error) {
			goto CLEANUP;
		}
		fsv_mp_globals.fs_mp_add_a1 = fsv_mp_globals.fs_mp_reduce_a1;
		fsv_mp_globals.fs_mp_add_a2 = &fsv_mp_globals.fs_mp_reduce_t1;
		fsv_mp_globals.fs_mp_add_a3 = fsv_mp_globals.fs_mp_reduce_a1;
		fs_mp_add();
		if(fsv_mp_globals.fs_mp_error) {
			goto CLEANUP;
		}
	}
	fsv_mp_globals.fs_mp_cmp_a1 = fsv_mp_globals.fs_mp_reduce_a1;
	fsv_mp_globals.fs_mp_cmp_a2 = fsv_mp_globals.fs_mp_reduce_a2;
	fs_mp_cmp();
	while(fsv_mp_globals.fs_mp_cmp_r != -1) {
		fsv_mp_globals.fs_mp_s_sub_a1 = fsv_mp_globals.fs_mp_reduce_a1;
		fsv_mp_globals.fs_mp_s_sub_a2 = fsv_mp_globals.fs_mp_reduce_a2;
		fsv_mp_globals.fs_mp_s_sub_a3 = fsv_mp_globals.fs_mp_reduce_a1;
		fs_mp_s_sub();
		if(fsv_mp_globals.fs_mp_error) {
			goto CLEANUP;
		}
		fs_mp_cmp();
	}
	CLEANUP:
	fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_reduce_t1;
	fs_mp_clear();
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_reduce_2k_setup(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_init_a1 = &fsv_mp_globals.fs_mp_reduce_2k_setup_t1;
	fs_mp_init();
	if(!fsv_mp_globals.fs_mp_reduce_2k_setup_t1.dp) {
		fsv_mp_globals.fs_mp_error = 1;
		goto done;
	}
	fsv_mp_globals.fs_mp_count_bits_a1 = fsv_mp_globals.fs_mp_reduce_2k_setup_a1;
	fs_mp_count_bits();
	fsv_mp_globals.fs_mp_2expt_a1 = &fsv_mp_globals.fs_mp_reduce_2k_setup_t1;
	fsv_mp_globals.fs_mp_2expt_a2 = fsv_mp_globals.fs_mp_count_bits_r;
	fs_mp_2expt();
	if(fsv_mp_globals.fs_mp_error) {
		goto done;
	}
	fsv_mp_globals.fs_mp_s_sub_a1 = &fsv_mp_globals.fs_mp_reduce_2k_setup_t1;
	fsv_mp_globals.fs_mp_s_sub_a2 = fsv_mp_globals.fs_mp_reduce_2k_setup_a1;
	fsv_mp_globals.fs_mp_s_sub_a3 = &fsv_mp_globals.fs_mp_reduce_2k_setup_t1;
	fs_mp_s_sub();
	if(fsv_mp_globals.fs_mp_error) {
		goto done;
	}
	*fsv_mp_globals.fs_mp_reduce_2k_setup_a2 = fsv_mp_globals.fs_mp_reduce_2k_setup_t1.dp[0];
	done:
	fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_reduce_2k_setup_t1;
	fs_mp_clear();
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_reduce_2k_setup_l(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_init_a1 = &fsv_mp_globals.fs_mp_reduce_2k_setup_l_t1;
	fs_mp_init();
	if(!fsv_mp_globals.fs_mp_reduce_2k_setup_l_t1.dp) {
		fsv_mp_globals.fs_mp_error = 1;
		goto done;
	}
	fsv_mp_globals.fs_mp_count_bits_a1 = fsv_mp_globals.fs_mp_reduce_2k_setup_l_a1;
	fs_mp_count_bits();
	fsv_mp_globals.fs_mp_2expt_a1 = &fsv_mp_globals.fs_mp_reduce_2k_setup_l_t1;
	fsv_mp_globals.fs_mp_2expt_a2 = fsv_mp_globals.fs_mp_count_bits_r;
	fs_mp_2expt();
	if(fsv_mp_globals.fs_mp_error) {
		goto LBL_ERR;
	}
	fsv_mp_globals.fs_mp_s_sub_a1 = &fsv_mp_globals.fs_mp_reduce_2k_setup_l_t1;
	fsv_mp_globals.fs_mp_s_sub_a2 = fsv_mp_globals.fs_mp_reduce_2k_setup_l_a1;
	fsv_mp_globals.fs_mp_s_sub_a3 = fsv_mp_globals.fs_mp_reduce_2k_setup_l_a2;
	fs_mp_s_sub();
	if(fsv_mp_globals.fs_mp_error) {
		goto LBL_ERR;
	}
	LBL_ERR:
	fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_reduce_2k_setup_l_t1;
	fs_mp_clear();
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_sqr(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_sqr_t4 = fsv_mp_globals.fs_mp_sqr_a1->used;
	fsv_mp_globals.fs_mp_init_size_a1 = &fsv_mp_globals.fs_mp_sqr_t1;
	fsv_mp_globals.fs_mp_init_size_a2 = 2*fsv_mp_globals.fs_mp_sqr_t4 + 1;
	fs_mp_init_size();
	if(fsv_mp_globals.fs_mp_error) {
		fsv_mp_globals.fs_mp_sqr_a2->sign = 0;
		goto done;
	}
	fsv_mp_globals.fs_mp_sqr_t1.used = 2*fsv_mp_globals.fs_mp_sqr_t4 + 1;
	for(fsv_mp_globals.fs_mp_sqr_t2 = 0; fsv_mp_globals.fs_mp_sqr_t2 < fsv_mp_globals.fs_mp_sqr_t4; fsv_mp_globals.fs_mp_sqr_t2++) {
		fsv_mp_globals.fs_mp_sqr_t5 = ((fs_mp_word) fsv_mp_globals.fs_mp_sqr_t1.dp[2*fsv_mp_globals.fs_mp_sqr_t2]) +
				 ((fs_mp_word)fsv_mp_globals.fs_mp_sqr_a1->dp[fsv_mp_globals.fs_mp_sqr_t2])*((fs_mp_word)fsv_mp_globals.fs_mp_sqr_a1->dp[fsv_mp_globals.fs_mp_sqr_t2]);
		fsv_mp_globals.fs_mp_sqr_t1.dp[fsv_mp_globals.fs_mp_sqr_t2+fsv_mp_globals.fs_mp_sqr_t2] = (fs_mp_digit) (fsv_mp_globals.fs_mp_sqr_t5 & ((fs_mp_word) ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1))));
		fsv_mp_globals.fs_mp_sqr_t6           = (fs_mp_digit)(fsv_mp_globals.fs_mp_sqr_t5 >> ((fs_mp_word) DIGIT_BIT));
		fsv_mp_globals.fs_mp_sqr_t7        = fsv_mp_globals.fs_mp_sqr_a1->dp[fsv_mp_globals.fs_mp_sqr_t2];
		fsv_mp_globals.fs_mp_sqr_t8        = fsv_mp_globals.fs_mp_sqr_t1.dp + (2*fsv_mp_globals.fs_mp_sqr_t2 + 1);
		for(fsv_mp_globals.fs_mp_sqr_t3 = fsv_mp_globals.fs_mp_sqr_t2 + 1; fsv_mp_globals.fs_mp_sqr_t3 < fsv_mp_globals.fs_mp_sqr_t4; fsv_mp_globals.fs_mp_sqr_t3++) {
			fsv_mp_globals.fs_mp_sqr_t5       = ((fs_mp_word)fsv_mp_globals.fs_mp_sqr_t7) * ((fs_mp_word)fsv_mp_globals.fs_mp_sqr_a1->dp[fsv_mp_globals.fs_mp_sqr_t3]);
			fsv_mp_globals.fs_mp_sqr_t5       = ((fs_mp_word) *fsv_mp_globals.fs_mp_sqr_t8) + fsv_mp_globals.fs_mp_sqr_t5 + fsv_mp_globals.fs_mp_sqr_t5 + ((fs_mp_word) fsv_mp_globals.fs_mp_sqr_t6);
			*fsv_mp_globals.fs_mp_sqr_t8++ = (fs_mp_digit) (fsv_mp_globals.fs_mp_sqr_t5 & ((fs_mp_word) ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1))));
			fsv_mp_globals.fs_mp_sqr_t6       = (fs_mp_digit)(fsv_mp_globals.fs_mp_sqr_t5 >> ((fs_mp_word) DIGIT_BIT));
		}
		while(fsv_mp_globals.fs_mp_sqr_t6 != ((fs_mp_digit) 0)) {
			fsv_mp_globals.fs_mp_sqr_t5       = ((fs_mp_word) *fsv_mp_globals.fs_mp_sqr_t8) + ((fs_mp_word) fsv_mp_globals.fs_mp_sqr_t6);
			*fsv_mp_globals.fs_mp_sqr_t8++ = (fs_mp_digit) (fsv_mp_globals.fs_mp_sqr_t5 & ((fs_mp_word) ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1))));
			fsv_mp_globals.fs_mp_sqr_t6       = (fs_mp_digit)(fsv_mp_globals.fs_mp_sqr_t5 >> ((fs_mp_word) DIGIT_BIT));
		}
	}
	fsv_mp_globals.fs_mp_clamp_a1 = &fsv_mp_globals.fs_mp_sqr_t1;
	fs_mp_clamp();
	fsv_mp_globals.fs_mp_exch_a1 = &fsv_mp_globals.fs_mp_sqr_t1;
	fsv_mp_globals.fs_mp_exch_a2 = fsv_mp_globals.fs_mp_sqr_a2;
	fs_mp_exch();
	fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_sqr_t1;
	fs_mp_clear();
	fsv_mp_globals.fs_mp_sqr_a2->sign = 0;
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_reduce_2k_l(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_init_a1 = &fsv_mp_globals.fs_mp_reduce_2k_l_t1;
	fs_mp_init();
	if(!fsv_mp_globals.fs_mp_reduce_2k_l_t1.dp) {
		fsv_mp_globals.fs_mp_error = 1;
		goto done;
	}
	fsv_mp_globals.fs_mp_count_bits_a1 = fsv_mp_globals.fs_mp_reduce_2k_l_a2;
	fs_mp_count_bits();
	top:
	fsv_mp_globals.fs_mp_div_2d_a1 = fsv_mp_globals.fs_mp_reduce_2k_l_a1;
	fsv_mp_globals.fs_mp_div_2d_a2 = fsv_mp_globals.fs_mp_count_bits_r;
	fsv_mp_globals.fs_mp_div_2d_a3 = &fsv_mp_globals.fs_mp_reduce_2k_l_t1;
	fsv_mp_globals.fs_mp_div_2d_a4 = fsv_mp_globals.fs_mp_reduce_2k_l_a1;
	fs_mp_div_2d();
	if(fsv_mp_globals.fs_mp_error) {
		goto LBL_ERR;
	}
	fsv_mp_globals.fs_mp_mul_a1 = &fsv_mp_globals.fs_mp_reduce_2k_l_t1;
	fsv_mp_globals.fs_mp_mul_a2 = fsv_mp_globals.fs_mp_reduce_2k_l_a3;
	fsv_mp_globals.fs_mp_mul_a3 = &fsv_mp_globals.fs_mp_reduce_2k_l_t1;
	fs_mp_mul();
	if(fsv_mp_globals.fs_mp_error) {
		goto LBL_ERR;
	}
	fsv_mp_globals.fs_mp_s_add_a1 = fsv_mp_globals.fs_mp_reduce_2k_l_a1;
	fsv_mp_globals.fs_mp_s_add_a2 = &fsv_mp_globals.fs_mp_reduce_2k_l_t1;
	fsv_mp_globals.fs_mp_s_add_a3 = fsv_mp_globals.fs_mp_reduce_2k_l_a1;
	fs_mp_s_add();
	if(fsv_mp_globals.fs_mp_error) {
		goto LBL_ERR;
	}
	fsv_mp_globals.fs_mp_cmp_mag_a1 = fsv_mp_globals.fs_mp_reduce_2k_l_a1;
	fsv_mp_globals.fs_mp_cmp_mag_a2 = fsv_mp_globals.fs_mp_reduce_2k_l_a2;
	fs_mp_cmp_mag();
	if(fsv_mp_globals.fs_mp_cmp_mag_r != -1) {
		fsv_mp_globals.fs_mp_s_sub_a1 = fsv_mp_globals.fs_mp_reduce_2k_l_a1;
		fsv_mp_globals.fs_mp_s_sub_a2 = fsv_mp_globals.fs_mp_reduce_2k_l_a2;
		fsv_mp_globals.fs_mp_s_sub_a3 = fsv_mp_globals.fs_mp_reduce_2k_l_a1;
		fs_mp_s_sub();
		goto top;
	}
	LBL_ERR:
	fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_reduce_2k_l_t1;
	fs_mp_clear();
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_s_exptmod(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_count_bits_a1 = fsv_mp_globals.fs_mp_s_exptmod_a2;
	fs_mp_count_bits();
	if(fsv_mp_globals.fs_mp_count_bits_r <= 7) {
		fsv_mp_globals.fs_mp_s_exptmod_t12 = 2;
	} else if(fsv_mp_globals.fs_mp_count_bits_r <= 36) {
		fsv_mp_globals.fs_mp_s_exptmod_t12 = 3;
	} else if(fsv_mp_globals.fs_mp_count_bits_r <= 140) {
		fsv_mp_globals.fs_mp_s_exptmod_t12 = 4;
	} else if(fsv_mp_globals.fs_mp_count_bits_r <= 450) {
		fsv_mp_globals.fs_mp_s_exptmod_t12 = 5;
	} else if(fsv_mp_globals.fs_mp_count_bits_r <= 1303) {
		fsv_mp_globals.fs_mp_s_exptmod_t12 = 6;
	} else if(fsv_mp_globals.fs_mp_count_bits_r <= 3529) {
		fsv_mp_globals.fs_mp_s_exptmod_t12 = 7;
	} else {
		fsv_mp_globals.fs_mp_s_exptmod_t12 = 8;
	}
	if(fsv_mp_globals.fs_mp_s_exptmod_t12 > 4) {
		fsv_mp_globals.fs_mp_s_exptmod_t12 = 4;
	}
	fsv_mp_globals.fs_mp_init_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t1[1];
	fs_mp_init();
	if(!fsv_mp_globals.fs_mp_s_exptmod_t1[1].dp) {
		fsv_mp_globals.fs_mp_error = 1;
		goto done;
	}
	for(fsv_mp_globals.fs_mp_s_exptmod_t10 = 1<<(fsv_mp_globals.fs_mp_s_exptmod_t12-1); fsv_mp_globals.fs_mp_s_exptmod_t10 < (1 << fsv_mp_globals.fs_mp_s_exptmod_t12); fsv_mp_globals.fs_mp_s_exptmod_t10++) {
		fsv_mp_globals.fs_mp_init_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t1[fsv_mp_globals.fs_mp_s_exptmod_t10];
		fs_mp_init();
		if(!fsv_mp_globals.fs_mp_s_exptmod_t1[fsv_mp_globals.fs_mp_s_exptmod_t10].dp) {
			fsv_mp_globals.fs_mp_error = 1;
			for(fsv_mp_globals.fs_mp_s_exptmod_t11 = 1<<(fsv_mp_globals.fs_mp_s_exptmod_t12-1); fsv_mp_globals.fs_mp_s_exptmod_t11 < fsv_mp_globals.fs_mp_s_exptmod_t10; fsv_mp_globals.fs_mp_s_exptmod_t11++) {
				fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t1[fsv_mp_globals.fs_mp_s_exptmod_t11];
				fs_mp_clear();
			}
			fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t1[1];
			fs_mp_clear();
			goto done;
		}
	}
	fsv_mp_globals.fs_mp_init_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t3;
	fs_mp_init();
	if(!fsv_mp_globals.fs_mp_s_exptmod_t3.dp) {
		fsv_mp_globals.fs_mp_error = 1;
		goto LBL_M;
	}
	if(fsv_mp_globals.fs_mp_s_exptmod_a5 == 0) {
		fsv_mp_globals.fs_mp_reduce_setup_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t3;
		fsv_mp_globals.fs_mp_reduce_setup_a2 = fsv_mp_globals.fs_mp_s_exptmod_a3;
		fs_mp_reduce_setup();
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_MU;
		}
		fsv_mp_globals.fs_mp_s_exptmod_t13 = 1;
	} else {
		fsv_mp_globals.fs_mp_reduce_2k_setup_l_a1 = fsv_mp_globals.fs_mp_s_exptmod_a3;
		fsv_mp_globals.fs_mp_reduce_2k_setup_l_a2 = &fsv_mp_globals.fs_mp_s_exptmod_t3;
		fs_mp_reduce_2k_setup_l();
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_MU;
		}
		fsv_mp_globals.fs_mp_s_exptmod_t13 = 2;
	}
	fsv_mp_globals.fs_mp_mod_a1 = fsv_mp_globals.fs_mp_s_exptmod_a1;
	fsv_mp_globals.fs_mp_mod_a2 = fsv_mp_globals.fs_mp_s_exptmod_a3;
	fsv_mp_globals.fs_mp_mod_a3 = &fsv_mp_globals.fs_mp_s_exptmod_t1[1];
	fs_mp_mod();
	if(fsv_mp_globals.fs_mp_error) {
		goto LBL_MU;
	}
	fsv_mp_globals.fs_mp_copy_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t1[1];
	fsv_mp_globals.fs_mp_copy_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t1[1 << (fsv_mp_globals.fs_mp_s_exptmod_t12 - 1)];
	fs_mp_copy();
	if(fsv_mp_globals.fs_mp_error) {
		goto LBL_MU;
	}
	for(fsv_mp_globals.fs_mp_s_exptmod_t10 = 0; fsv_mp_globals.fs_mp_s_exptmod_t10 < (fsv_mp_globals.fs_mp_s_exptmod_t12 - 1); fsv_mp_globals.fs_mp_s_exptmod_t10++) {
		fsv_mp_globals.fs_mp_sqr_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t1[1 << (fsv_mp_globals.fs_mp_s_exptmod_t12 - 1)];
		fsv_mp_globals.fs_mp_sqr_a2 = &fsv_mp_globals.fs_mp_s_exptmod_t1[1 << (fsv_mp_globals.fs_mp_s_exptmod_t12 - 1)];
		fs_mp_sqr();
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_MU;
		}
		if(fsv_mp_globals.fs_mp_s_exptmod_t13 == 1) {
			fsv_mp_globals.fs_mp_reduce_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t1[1 << (fsv_mp_globals.fs_mp_s_exptmod_t12 - 1)];
			fsv_mp_globals.fs_mp_reduce_a2 = fsv_mp_globals.fs_mp_s_exptmod_a3;
			fsv_mp_globals.fs_mp_reduce_a3 = &fsv_mp_globals.fs_mp_s_exptmod_t3;
			fs_mp_reduce();
			if(fsv_mp_globals.fs_mp_error) {
				goto LBL_MU;
			}
		} else if(fsv_mp_globals.fs_mp_s_exptmod_t13 == 2) {
			fsv_mp_globals.fs_mp_reduce_2k_l_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t1[1 << (fsv_mp_globals.fs_mp_s_exptmod_t12 - 1)];
			fsv_mp_globals.fs_mp_reduce_2k_l_a2 = fsv_mp_globals.fs_mp_s_exptmod_a3;
			fsv_mp_globals.fs_mp_reduce_2k_l_a3 = &fsv_mp_globals.fs_mp_s_exptmod_t3;
			fs_mp_reduce_2k_l();
			if(fsv_mp_globals.fs_mp_error) {
				goto LBL_MU;
			}
		}
	}
	for(fsv_mp_globals.fs_mp_s_exptmod_t10 = (1 << (fsv_mp_globals.fs_mp_s_exptmod_t12 - 1)) + 1; fsv_mp_globals.fs_mp_s_exptmod_t10 < (1 << fsv_mp_globals.fs_mp_s_exptmod_t12); fsv_mp_globals.fs_mp_s_exptmod_t10++) {
		fsv_mp_globals.fs_mp_mul_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t1[fsv_mp_globals.fs_mp_s_exptmod_t10 - 1];
		fsv_mp_globals.fs_mp_mul_a2 = &fsv_mp_globals.fs_mp_s_exptmod_t1[1];
		fsv_mp_globals.fs_mp_mul_a3 = &fsv_mp_globals.fs_mp_s_exptmod_t1[fsv_mp_globals.fs_mp_s_exptmod_t10];
		fs_mp_mul();
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_MU;
		}
		if(fsv_mp_globals.fs_mp_s_exptmod_t13 == 1) {
			fsv_mp_globals.fs_mp_reduce_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t1[fsv_mp_globals.fs_mp_s_exptmod_t10];
			fsv_mp_globals.fs_mp_reduce_a2 = fsv_mp_globals.fs_mp_s_exptmod_a3;
			fsv_mp_globals.fs_mp_reduce_a3 = &fsv_mp_globals.fs_mp_s_exptmod_t3;
			fs_mp_reduce();
			if(fsv_mp_globals.fs_mp_error) {
				goto LBL_MU;
			}
		} else if(fsv_mp_globals.fs_mp_s_exptmod_t13 == 2) {
			fsv_mp_globals.fs_mp_reduce_2k_l_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t1[fsv_mp_globals.fs_mp_s_exptmod_t10];
			fsv_mp_globals.fs_mp_reduce_2k_l_a2 = fsv_mp_globals.fs_mp_s_exptmod_a3;
			fsv_mp_globals.fs_mp_reduce_2k_l_a3 = &fsv_mp_globals.fs_mp_s_exptmod_t3;
			fs_mp_reduce_2k_l();
			if(fsv_mp_globals.fs_mp_error) {
				goto LBL_MU;
			}
		}
	}
	fsv_mp_globals.fs_mp_init_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t2;
	fs_mp_init();
	if(!fsv_mp_globals.fs_mp_s_exptmod_t2.dp) {
		fsv_mp_globals.fs_mp_error = 1;
		goto LBL_MU;
	}
	fsv_mp_globals.fs_mp_set_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t2;
	fsv_mp_globals.fs_mp_set_a2 =  1;
	fs_mp_set();
	fsv_mp_globals.fs_mp_s_exptmod_t8   = 0;
	fsv_mp_globals.fs_mp_s_exptmod_t7 = 1;
	fsv_mp_globals.fs_mp_s_exptmod_t4    = 0;
	fsv_mp_globals.fs_mp_s_exptmod_t9 = fsv_mp_globals.fs_mp_s_exptmod_a2->used - 1;
	fsv_mp_globals.fs_mp_s_exptmod_t6 = 0;
	fsv_mp_globals.fs_mp_s_exptmod_t5 = 0;
	for(;;) {
		if(--fsv_mp_globals.fs_mp_s_exptmod_t7 == 0) {
			if(fsv_mp_globals.fs_mp_s_exptmod_t9 == -1) {
				break;
			}
			fsv_mp_globals.fs_mp_s_exptmod_t4    = fsv_mp_globals.fs_mp_s_exptmod_a2->dp[fsv_mp_globals.fs_mp_s_exptmod_t9--];
			fsv_mp_globals.fs_mp_s_exptmod_t7 = (int) DIGIT_BIT;
		}
		fsv_mp_globals.fs_mp_s_exptmod_t11     = (fsv_mp_globals.fs_mp_s_exptmod_t4 >> (fs_mp_digit)(DIGIT_BIT - 1)) & 1;
		fsv_mp_globals.fs_mp_s_exptmod_t4 <<= (fs_mp_digit)1;
		if(fsv_mp_globals.fs_mp_s_exptmod_t8 == 0 && fsv_mp_globals.fs_mp_s_exptmod_t11 == 0) {
			continue;
		}
		if(fsv_mp_globals.fs_mp_s_exptmod_t8 == 1 && fsv_mp_globals.fs_mp_s_exptmod_t11 == 0) {
			fsv_mp_globals.fs_mp_sqr_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t2;
			fsv_mp_globals.fs_mp_sqr_a2 = &fsv_mp_globals.fs_mp_s_exptmod_t2;
			fs_mp_sqr();
			if(fsv_mp_globals.fs_mp_error) {
				goto LBL_RES;
			}
			if(fsv_mp_globals.fs_mp_s_exptmod_t13 == 1) {
				fsv_mp_globals.fs_mp_reduce_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t2;
				fsv_mp_globals.fs_mp_reduce_a2 = fsv_mp_globals.fs_mp_s_exptmod_a3;
				fsv_mp_globals.fs_mp_reduce_a3 = &fsv_mp_globals.fs_mp_s_exptmod_t3;
				fs_mp_reduce();
				if(fsv_mp_globals.fs_mp_error) {
					goto LBL_RES;
				}
			} else if(fsv_mp_globals.fs_mp_s_exptmod_t13 == 2) {
				fsv_mp_globals.fs_mp_reduce_2k_l_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t2;
				fsv_mp_globals.fs_mp_reduce_2k_l_a2 = fsv_mp_globals.fs_mp_s_exptmod_a3;
				fsv_mp_globals.fs_mp_reduce_2k_l_a3 = &fsv_mp_globals.fs_mp_s_exptmod_t3;
				fs_mp_reduce_2k_l();
				if(fsv_mp_globals.fs_mp_error) {
					goto LBL_RES;
				}
			}
			continue;
		}
		fsv_mp_globals.fs_mp_s_exptmod_t5 |= (fsv_mp_globals.fs_mp_s_exptmod_t11 << (fsv_mp_globals.fs_mp_s_exptmod_t12 - ++fsv_mp_globals.fs_mp_s_exptmod_t6));
		fsv_mp_globals.fs_mp_s_exptmod_t8    = 2;
		if(fsv_mp_globals.fs_mp_s_exptmod_t6 == fsv_mp_globals.fs_mp_s_exptmod_t12) {
			for(fsv_mp_globals.fs_mp_s_exptmod_t10 = 0; fsv_mp_globals.fs_mp_s_exptmod_t10 < fsv_mp_globals.fs_mp_s_exptmod_t12; fsv_mp_globals.fs_mp_s_exptmod_t10++) {
				fsv_mp_globals.fs_mp_sqr_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t2;
				fsv_mp_globals.fs_mp_sqr_a2 = &fsv_mp_globals.fs_mp_s_exptmod_t2;
				fs_mp_sqr();
				if(fsv_mp_globals.fs_mp_error) {
					goto LBL_RES;
				}
				if(fsv_mp_globals.fs_mp_s_exptmod_t13 == 1) {
					fsv_mp_globals.fs_mp_reduce_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t2;
					fsv_mp_globals.fs_mp_reduce_a2 = fsv_mp_globals.fs_mp_s_exptmod_a3;
					fsv_mp_globals.fs_mp_reduce_a3 = &fsv_mp_globals.fs_mp_s_exptmod_t3;
					fs_mp_reduce();
					if(fsv_mp_globals.fs_mp_error) {
						goto LBL_RES;
					}
				} else if(fsv_mp_globals.fs_mp_s_exptmod_t13 == 2) {
					fsv_mp_globals.fs_mp_reduce_2k_l_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t2;
					fsv_mp_globals.fs_mp_reduce_2k_l_a2 = fsv_mp_globals.fs_mp_s_exptmod_a3;
					fsv_mp_globals.fs_mp_reduce_2k_l_a3 = &fsv_mp_globals.fs_mp_s_exptmod_t3;
					fs_mp_reduce_2k_l();
					if(fsv_mp_globals.fs_mp_error) {
						goto LBL_RES;
					}
				}
			}
			fsv_mp_globals.fs_mp_mul_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t2;
			fsv_mp_globals.fs_mp_mul_a2 = &fsv_mp_globals.fs_mp_s_exptmod_t1[fsv_mp_globals.fs_mp_s_exptmod_t5];
			fsv_mp_globals.fs_mp_mul_a3 = &fsv_mp_globals.fs_mp_s_exptmod_t2;
			fs_mp_mul();
			if(fsv_mp_globals.fs_mp_error) {
				goto LBL_RES;
			}
			if(fsv_mp_globals.fs_mp_s_exptmod_t13 == 1) {
				fsv_mp_globals.fs_mp_reduce_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t2;
				fsv_mp_globals.fs_mp_reduce_a2 = fsv_mp_globals.fs_mp_s_exptmod_a3;
				fsv_mp_globals.fs_mp_reduce_a3 = &fsv_mp_globals.fs_mp_s_exptmod_t3;
				fs_mp_reduce();
				if(fsv_mp_globals.fs_mp_error) {
					goto LBL_RES;
				}
			} else if(fsv_mp_globals.fs_mp_s_exptmod_t13 == 2) {
				fsv_mp_globals.fs_mp_reduce_2k_l_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t2;
				fsv_mp_globals.fs_mp_reduce_2k_l_a2 = fsv_mp_globals.fs_mp_s_exptmod_a3;
				fsv_mp_globals.fs_mp_reduce_2k_l_a3 = &fsv_mp_globals.fs_mp_s_exptmod_t3;
				fs_mp_reduce_2k_l();
				if(fsv_mp_globals.fs_mp_error) {
					goto LBL_RES;
				}
			}
			fsv_mp_globals.fs_mp_s_exptmod_t6 = 0;
			fsv_mp_globals.fs_mp_s_exptmod_t5 = 0;
			fsv_mp_globals.fs_mp_s_exptmod_t8   = 1;
		}
	}
	if(fsv_mp_globals.fs_mp_s_exptmod_t8 == 2 && fsv_mp_globals.fs_mp_s_exptmod_t6 > 0) {
		for(fsv_mp_globals.fs_mp_s_exptmod_t10 = 0; fsv_mp_globals.fs_mp_s_exptmod_t10 < fsv_mp_globals.fs_mp_s_exptmod_t6; fsv_mp_globals.fs_mp_s_exptmod_t10++) {
			fsv_mp_globals.fs_mp_sqr_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t2;
			fsv_mp_globals.fs_mp_sqr_a2 = &fsv_mp_globals.fs_mp_s_exptmod_t2;
			fs_mp_sqr();
			if(fsv_mp_globals.fs_mp_error) {
				goto LBL_RES;
			}
			if(fsv_mp_globals.fs_mp_s_exptmod_t13 == 1) {
				fsv_mp_globals.fs_mp_reduce_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t2;
				fsv_mp_globals.fs_mp_reduce_a2 = fsv_mp_globals.fs_mp_s_exptmod_a3;
				fsv_mp_globals.fs_mp_reduce_a3 = &fsv_mp_globals.fs_mp_s_exptmod_t3;
				fs_mp_reduce();
				if(fsv_mp_globals.fs_mp_error) {
					goto LBL_RES;
				}
			} else if(fsv_mp_globals.fs_mp_s_exptmod_t13 == 2) {
				fsv_mp_globals.fs_mp_reduce_2k_l_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t2;
				fsv_mp_globals.fs_mp_reduce_2k_l_a2 = fsv_mp_globals.fs_mp_s_exptmod_a3;
				fsv_mp_globals.fs_mp_reduce_2k_l_a3 = &fsv_mp_globals.fs_mp_s_exptmod_t3;
				fs_mp_reduce_2k_l();
				if(fsv_mp_globals.fs_mp_error) {
					goto LBL_RES;
				}
			}
			fsv_mp_globals.fs_mp_s_exptmod_t5 <<= 1;
			if((fsv_mp_globals.fs_mp_s_exptmod_t5 & (1 << fsv_mp_globals.fs_mp_s_exptmod_t12)) != 0) {
				fsv_mp_globals.fs_mp_mul_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t2;
				fsv_mp_globals.fs_mp_mul_a2 = &fsv_mp_globals.fs_mp_s_exptmod_t1[1];
				fsv_mp_globals.fs_mp_mul_a3 = &fsv_mp_globals.fs_mp_s_exptmod_t2;
				fs_mp_mul();
				if(fsv_mp_globals.fs_mp_error) {
					goto LBL_RES;
				}
				fsv_mp_globals.fs_mp_reduce_2k_l_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t2;
				fsv_mp_globals.fs_mp_reduce_2k_l_a2 = fsv_mp_globals.fs_mp_s_exptmod_a3;
				fsv_mp_globals.fs_mp_reduce_2k_l_a3 = &fsv_mp_globals.fs_mp_s_exptmod_t3;
				fs_mp_reduce_2k_l();
				if(fsv_mp_globals.fs_mp_error) {
					goto LBL_RES;
				}
			}
		}
	}
	fsv_mp_globals.fs_mp_exch_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t2;
	fsv_mp_globals.fs_mp_exch_a2 = fsv_mp_globals.fs_mp_s_exptmod_a4;
	fs_mp_exch();
	fsv_mp_globals.fs_mp_error = 0;
	LBL_RES:
	fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t2;
	fs_mp_clear();
	LBL_MU:
	fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t3;
	fs_mp_clear();
	LBL_M:
	fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t1[1];
	fs_mp_clear();
	for(fsv_mp_globals.fs_mp_s_exptmod_t10 = 1<<(fsv_mp_globals.fs_mp_s_exptmod_t12-1); fsv_mp_globals.fs_mp_s_exptmod_t10 < (1 << fsv_mp_globals.fs_mp_s_exptmod_t12); fsv_mp_globals.fs_mp_s_exptmod_t10++) {
		fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_s_exptmod_t1[fsv_mp_globals.fs_mp_s_exptmod_t10];
		fs_mp_clear();
	}
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_dr_is_modulus(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_dr_is_modulus_r = 0;
	if(fsv_mp_globals.fs_mp_dr_is_modulus_a1->used < 2) {
		fsv_mp_globals.fs_mp_dr_is_modulus_r = 0;
		goto done;
	}
	for(fsv_mp_globals.fs_mp_dr_is_modulus_t1 = 1; fsv_mp_globals.fs_mp_dr_is_modulus_t1 < fsv_mp_globals.fs_mp_dr_is_modulus_a1->used; fsv_mp_globals.fs_mp_dr_is_modulus_t1++) {
		if(fsv_mp_globals.fs_mp_dr_is_modulus_a1->dp[fsv_mp_globals.fs_mp_dr_is_modulus_t1] != ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1))) {
			fsv_mp_globals.fs_mp_dr_is_modulus_r = 0;
			goto done;
		}
	}
	fsv_mp_globals.fs_mp_dr_is_modulus_r = 1;
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_reduce_is_2k(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_reduce_is_2k_r = 0;
	if(fsv_mp_globals.fs_mp_reduce_is_2k_a1->used == 0) {
		fsv_mp_globals.fs_mp_reduce_is_2k_r = 0;
		goto done;
	} else if(fsv_mp_globals.fs_mp_reduce_is_2k_a1->used == 1) {
		fsv_mp_globals.fs_mp_reduce_is_2k_r = 1;
		goto done;
	} else if(fsv_mp_globals.fs_mp_reduce_is_2k_a1->used > 1) {
		fsv_mp_globals.fs_mp_count_bits_a1 = fsv_mp_globals.fs_mp_reduce_is_2k_a1;
		fs_mp_count_bits();
		fsv_mp_globals.fs_mp_reduce_is_2k_t3 = 1;
		fsv_mp_globals.fs_mp_reduce_is_2k_t2 = 1;
		for(fsv_mp_globals.fs_mp_reduce_is_2k_t1 = DIGIT_BIT; fsv_mp_globals.fs_mp_reduce_is_2k_t1 < fsv_mp_globals.fs_mp_count_bits_r; fsv_mp_globals.fs_mp_reduce_is_2k_t1++) {
			if((fsv_mp_globals.fs_mp_reduce_is_2k_a1->dp[fsv_mp_globals.fs_mp_reduce_is_2k_t2] & fsv_mp_globals.fs_mp_reduce_is_2k_t3) == 0) {
				fsv_mp_globals.fs_mp_reduce_is_2k_r = 0;
				goto done;
			}
			fsv_mp_globals.fs_mp_reduce_is_2k_t3 <<= 1;
			if(fsv_mp_globals.fs_mp_reduce_is_2k_t3 > (fs_mp_digit)((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1))) {
				++fsv_mp_globals.fs_mp_reduce_is_2k_t2;
				fsv_mp_globals.fs_mp_reduce_is_2k_t3 = 1;
			}
		}
	}
	fsv_mp_globals.fs_mp_reduce_is_2k_r = 1;
	done:
	;
}


__FS_FUNCTION_MAYBE_INLINE void fs_mp_montgomery_setup(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_montgomery_setup_t2 = fsv_mp_globals.fs_mp_montgomery_setup_a1->dp[0];
	if((fsv_mp_globals.fs_mp_montgomery_setup_t2 & 1) == 0) {
		fsv_mp_globals.fs_mp_error = 1;
		goto done;
	}
	fsv_mp_globals.fs_mp_montgomery_setup_t1 = (((fsv_mp_globals.fs_mp_montgomery_setup_t2 + 2) & 4) << 1) + fsv_mp_globals.fs_mp_montgomery_setup_t2;
	fsv_mp_globals.fs_mp_montgomery_setup_t1 *= 2 - fsv_mp_globals.fs_mp_montgomery_setup_t2 * fsv_mp_globals.fs_mp_montgomery_setup_t1;
	fsv_mp_globals.fs_mp_montgomery_setup_t1 *= 2 - fsv_mp_globals.fs_mp_montgomery_setup_t2 * fsv_mp_globals.fs_mp_montgomery_setup_t1;
	fsv_mp_globals.fs_mp_montgomery_setup_t1 *= 2 - fsv_mp_globals.fs_mp_montgomery_setup_t2 * fsv_mp_globals.fs_mp_montgomery_setup_t1;
	*fsv_mp_globals.fs_mp_montgomery_setup_a2 = (unsigned long)(((fs_mp_word)1 << ((fs_mp_word) DIGIT_BIT)) - fsv_mp_globals.fs_mp_montgomery_setup_t1) & ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1));
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_fast_montgomery_reduce(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_fast_montgomery_reduce_t2 = fsv_mp_globals.fs_mp_xxx_reduce_a1->used;
	if(fsv_mp_globals.fs_mp_xxx_reduce_a1->alloc < fsv_mp_globals.fs_mp_xxx_reduce_a2->used + 1) {
		fsv_mp_globals.fs_mp_grow_a1 = fsv_mp_globals.fs_mp_xxx_reduce_a1;
		fsv_mp_globals.fs_mp_grow_a2 = fsv_mp_globals.fs_mp_xxx_reduce_a2->used + 1;
		fs_mp_grow();
		if(fsv_mp_globals.fs_mp_error) {
			goto done;
		}
	}
	fsv_mp_globals.fs_mp_fast_montgomery_reduce_t5   = fsv_mp_globals.fs_mp_fast_montgomery_reduce_t3;
	fsv_mp_globals.fs_mp_fast_montgomery_reduce_t6 = fsv_mp_globals.fs_mp_xxx_reduce_a1->dp;
	for(fsv_mp_globals.fs_mp_fast_montgomery_reduce_t1 = 0; fsv_mp_globals.fs_mp_fast_montgomery_reduce_t1 < fsv_mp_globals.fs_mp_xxx_reduce_a1->used; fsv_mp_globals.fs_mp_fast_montgomery_reduce_t1++) {
		*fsv_mp_globals.fs_mp_fast_montgomery_reduce_t5++ = *fsv_mp_globals.fs_mp_fast_montgomery_reduce_t6++;
	}
	for(; fsv_mp_globals.fs_mp_fast_montgomery_reduce_t1 < fsv_mp_globals.fs_mp_xxx_reduce_a2->used * 2 + 1; fsv_mp_globals.fs_mp_fast_montgomery_reduce_t1++) {
		*fsv_mp_globals.fs_mp_fast_montgomery_reduce_t5++ = 0;
	}
	for(fsv_mp_globals.fs_mp_fast_montgomery_reduce_t1 = 0; fsv_mp_globals.fs_mp_fast_montgomery_reduce_t1 < fsv_mp_globals.fs_mp_xxx_reduce_a2->used; fsv_mp_globals.fs_mp_fast_montgomery_reduce_t1++) {
		fsv_mp_globals.fs_mp_fast_montgomery_reduce_t4 = (fs_mp_digit) (((fsv_mp_globals.fs_mp_fast_montgomery_reduce_t3[fsv_mp_globals.fs_mp_fast_montgomery_reduce_t1] & ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1))) * fsv_mp_globals.fs_mp_xxx_reduce_a3) & ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1)));
		fsv_mp_globals.fs_mp_fast_montgomery_reduce_t8 = fsv_mp_globals.fs_mp_xxx_reduce_a2->dp;
		fsv_mp_globals.fs_mp_fast_montgomery_reduce_t5 = fsv_mp_globals.fs_mp_fast_montgomery_reduce_t3 + fsv_mp_globals.fs_mp_fast_montgomery_reduce_t1;
		for(fsv_mp_globals.fs_mp_fast_montgomery_reduce_t7 = 0; fsv_mp_globals.fs_mp_fast_montgomery_reduce_t7 < fsv_mp_globals.fs_mp_xxx_reduce_a2->used; fsv_mp_globals.fs_mp_fast_montgomery_reduce_t7++) {
			*fsv_mp_globals.fs_mp_fast_montgomery_reduce_t5++ += ((fs_mp_word)fsv_mp_globals.fs_mp_fast_montgomery_reduce_t4) * ((fs_mp_word)*fsv_mp_globals.fs_mp_fast_montgomery_reduce_t8++);
		}
		fsv_mp_globals.fs_mp_fast_montgomery_reduce_t3[fsv_mp_globals.fs_mp_fast_montgomery_reduce_t1 + 1] += fsv_mp_globals.fs_mp_fast_montgomery_reduce_t3[fsv_mp_globals.fs_mp_fast_montgomery_reduce_t1] >> ((fs_mp_word) DIGIT_BIT);
	}
	fsv_mp_globals.fs_mp_fast_montgomery_reduce_t9 = fsv_mp_globals.fs_mp_fast_montgomery_reduce_t3 + fsv_mp_globals.fs_mp_fast_montgomery_reduce_t1;
	fsv_mp_globals.fs_mp_fast_montgomery_reduce_t5 = fsv_mp_globals.fs_mp_fast_montgomery_reduce_t3 + ++fsv_mp_globals.fs_mp_fast_montgomery_reduce_t1;
	for(; fsv_mp_globals.fs_mp_fast_montgomery_reduce_t1 <= fsv_mp_globals.fs_mp_xxx_reduce_a2->used * 2 + 1; fsv_mp_globals.fs_mp_fast_montgomery_reduce_t1++) {
		*fsv_mp_globals.fs_mp_fast_montgomery_reduce_t5++ += *fsv_mp_globals.fs_mp_fast_montgomery_reduce_t9++ >> ((fs_mp_word) DIGIT_BIT);
	}
	fsv_mp_globals.fs_mp_fast_montgomery_reduce_t6 = fsv_mp_globals.fs_mp_xxx_reduce_a1->dp;
	fsv_mp_globals.fs_mp_fast_montgomery_reduce_t5 = fsv_mp_globals.fs_mp_fast_montgomery_reduce_t3 + fsv_mp_globals.fs_mp_xxx_reduce_a2->used;
	for(fsv_mp_globals.fs_mp_fast_montgomery_reduce_t1 = 0; fsv_mp_globals.fs_mp_fast_montgomery_reduce_t1 < fsv_mp_globals.fs_mp_xxx_reduce_a2->used + 1; fsv_mp_globals.fs_mp_fast_montgomery_reduce_t1++) {
		*fsv_mp_globals.fs_mp_fast_montgomery_reduce_t6++ = (fs_mp_digit)(*fsv_mp_globals.fs_mp_fast_montgomery_reduce_t5++ & ((fs_mp_word) ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1))));
	}
	for(; fsv_mp_globals.fs_mp_fast_montgomery_reduce_t1 < fsv_mp_globals.fs_mp_fast_montgomery_reduce_t2; fsv_mp_globals.fs_mp_fast_montgomery_reduce_t1++) {
		*fsv_mp_globals.fs_mp_fast_montgomery_reduce_t6++ = 0;
	}
	fsv_mp_globals.fs_mp_xxx_reduce_a1->used = fsv_mp_globals.fs_mp_xxx_reduce_a2->used + 1;
	fsv_mp_globals.fs_mp_clamp_a1 = fsv_mp_globals.fs_mp_xxx_reduce_a1;
	fs_mp_clamp();
	fsv_mp_globals.fs_mp_cmp_mag_a1 = fsv_mp_globals.fs_mp_xxx_reduce_a1;
	fsv_mp_globals.fs_mp_cmp_mag_a2 = fsv_mp_globals.fs_mp_xxx_reduce_a2;
	fs_mp_cmp_mag();
	if(fsv_mp_globals.fs_mp_cmp_mag_r != -1) {
		fsv_mp_globals.fs_mp_s_sub_a1 = fsv_mp_globals.fs_mp_xxx_reduce_a1;
		fsv_mp_globals.fs_mp_s_sub_a2 = fsv_mp_globals.fs_mp_xxx_reduce_a2;
		fsv_mp_globals.fs_mp_s_sub_a3 = fsv_mp_globals.fs_mp_xxx_reduce_a1;
		fs_mp_s_sub();
		goto done;
	}
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_montgomery_reduce(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_montgomery_reduce_t2 = fsv_mp_globals.fs_mp_xxx_reduce_a2->used * 2 + 1;
	if((fsv_mp_globals.fs_mp_montgomery_reduce_t2 < (1 << (sizeof(fs_mp_word) * 8 - 2 * DIGIT_BIT + 1))) &&
	   fsv_mp_globals.fs_mp_xxx_reduce_a2->used <
	   (1 << ((8 * sizeof (fs_mp_word)) - (2 * DIGIT_BIT)))) {
		fsv_mp_globals.fs_mp_xxx_reduce_a1 = fsv_mp_globals.fs_mp_xxx_reduce_a1;
		fsv_mp_globals.fs_mp_xxx_reduce_a2 = fsv_mp_globals.fs_mp_xxx_reduce_a2;
		fsv_mp_globals.fs_mp_xxx_reduce_a3 = fsv_mp_globals.fs_mp_xxx_reduce_a3;
		fs_mp_fast_montgomery_reduce();
		goto done;
	}
	if(fsv_mp_globals.fs_mp_xxx_reduce_a1->alloc < fsv_mp_globals.fs_mp_montgomery_reduce_t2) {
		fsv_mp_globals.fs_mp_grow_a1= fsv_mp_globals.fs_mp_xxx_reduce_a1;
		fsv_mp_globals.fs_mp_grow_a2 = fsv_mp_globals.fs_mp_montgomery_reduce_t2;
		fs_mp_grow();
		if(fsv_mp_globals.fs_mp_error) {
			goto done;
		}
	}
	fsv_mp_globals.fs_mp_xxx_reduce_a1->used = fsv_mp_globals.fs_mp_montgomery_reduce_t2;
	for(fsv_mp_globals.fs_mp_montgomery_reduce_t1 = 0; fsv_mp_globals.fs_mp_montgomery_reduce_t1 < fsv_mp_globals.fs_mp_xxx_reduce_a2->used; fsv_mp_globals.fs_mp_montgomery_reduce_t1++) {
		fsv_mp_globals.fs_mp_montgomery_reduce_t3 = (fs_mp_digit) (((fs_mp_word)fsv_mp_globals.fs_mp_xxx_reduce_a1->dp[fsv_mp_globals.fs_mp_montgomery_reduce_t1]) * ((fs_mp_word)fsv_mp_globals.fs_mp_xxx_reduce_a3) & ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1)));
		{
			fsv_mp_globals.fs_mp_montgomery_reduce_t5 = fsv_mp_globals.fs_mp_xxx_reduce_a2->dp;
			fsv_mp_globals.fs_mp_montgomery_reduce_t6 = fsv_mp_globals.fs_mp_xxx_reduce_a1->dp + fsv_mp_globals.fs_mp_montgomery_reduce_t1;
			fsv_mp_globals.fs_mp_montgomery_reduce_t7 = 0;
			for(fsv_mp_globals.fs_mp_montgomery_reduce_t4 = 0; fsv_mp_globals.fs_mp_montgomery_reduce_t4 < fsv_mp_globals.fs_mp_xxx_reduce_a2->used; fsv_mp_globals.fs_mp_montgomery_reduce_t4++) {
				fsv_mp_globals.fs_mp_montgomery_reduce_t8       = ((fs_mp_word)fsv_mp_globals.fs_mp_montgomery_reduce_t3) * ((fs_mp_word)*fsv_mp_globals.fs_mp_montgomery_reduce_t5++) +
								     ((fs_mp_word) fsv_mp_globals.fs_mp_montgomery_reduce_t7) + ((fs_mp_word) * fsv_mp_globals.fs_mp_montgomery_reduce_t6);
				fsv_mp_globals.fs_mp_montgomery_reduce_t7       = (fs_mp_digit)(fsv_mp_globals.fs_mp_montgomery_reduce_t8 >> ((fs_mp_word) DIGIT_BIT));
				*fsv_mp_globals.fs_mp_montgomery_reduce_t6++ = (fs_mp_digit)(fsv_mp_globals.fs_mp_montgomery_reduce_t8 & ((fs_mp_word) ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1))));
			}
			while(fsv_mp_globals.fs_mp_montgomery_reduce_t7) {
				*fsv_mp_globals.fs_mp_montgomery_reduce_t6   += fsv_mp_globals.fs_mp_montgomery_reduce_t7;
				fsv_mp_globals.fs_mp_montgomery_reduce_t7        = *fsv_mp_globals.fs_mp_montgomery_reduce_t6 >> DIGIT_BIT;
				*fsv_mp_globals.fs_mp_montgomery_reduce_t6++ &= ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1));
			}
		}
	}
	fsv_mp_globals.fs_mp_clamp_a1 = fsv_mp_globals.fs_mp_xxx_reduce_a1;
	fs_mp_clamp();
	fsv_mp_globals.fs_mp_rshd_a1 = fsv_mp_globals.fs_mp_xxx_reduce_a1;
	fsv_mp_globals.fs_mp_rshd_a2 = fsv_mp_globals.fs_mp_xxx_reduce_a2->used;
	fs_mp_rshd();
	fsv_mp_globals.fs_mp_cmp_mag_a1 = fsv_mp_globals.fs_mp_xxx_reduce_a1;
	fsv_mp_globals.fs_mp_cmp_mag_a2 = fsv_mp_globals.fs_mp_xxx_reduce_a2;
	fs_mp_cmp_mag();
	if(fsv_mp_globals.fs_mp_cmp_mag_r != -1) {
		fsv_mp_globals.fs_mp_s_sub_a1 = fsv_mp_globals.fs_mp_xxx_reduce_a1;
		fsv_mp_globals.fs_mp_s_sub_a2 = fsv_mp_globals.fs_mp_xxx_reduce_a2;
		fsv_mp_globals.fs_mp_s_sub_a3 = fsv_mp_globals.fs_mp_xxx_reduce_a1;
		fs_mp_s_sub();
		goto done;
	}
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_dr_reduce(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_dr_reduce_t2 = fsv_mp_globals.fs_mp_xxx_reduce_a2->used;
	if(fsv_mp_globals.fs_mp_xxx_reduce_a1->alloc < fsv_mp_globals.fs_mp_dr_reduce_t2 + fsv_mp_globals.fs_mp_dr_reduce_t2) {
		fsv_mp_globals.fs_mp_grow_a1 = fsv_mp_globals.fs_mp_xxx_reduce_a1;
		fsv_mp_globals.fs_mp_grow_a2 = fsv_mp_globals.fs_mp_dr_reduce_t2 + fsv_mp_globals.fs_mp_dr_reduce_t2;
		fs_mp_grow();
		if(fsv_mp_globals.fs_mp_error) {
			goto done;
		}
	}
	top:
	fsv_mp_globals.fs_mp_dr_reduce_t4 = fsv_mp_globals.fs_mp_xxx_reduce_a1->dp;
	fsv_mp_globals.fs_mp_dr_reduce_t5 = fsv_mp_globals.fs_mp_xxx_reduce_a1->dp + fsv_mp_globals.fs_mp_dr_reduce_t2;
	fsv_mp_globals.fs_mp_dr_reduce_t6 = 0;
	for(fsv_mp_globals.fs_mp_dr_reduce_t1 = 0; fsv_mp_globals.fs_mp_dr_reduce_t1 < fsv_mp_globals.fs_mp_dr_reduce_t2; fsv_mp_globals.fs_mp_dr_reduce_t1++) {
		fsv_mp_globals.fs_mp_dr_reduce_t3         = ((fs_mp_word)*fsv_mp_globals.fs_mp_dr_reduce_t5++) * ((fs_mp_word)fsv_mp_globals.fs_mp_xxx_reduce_a3) + *fsv_mp_globals.fs_mp_dr_reduce_t4 + fsv_mp_globals.fs_mp_dr_reduce_t6;
		*fsv_mp_globals.fs_mp_dr_reduce_t4++  = (fs_mp_digit)(fsv_mp_globals.fs_mp_dr_reduce_t3 & ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1)));
		fsv_mp_globals.fs_mp_dr_reduce_t6        = (fs_mp_digit)(fsv_mp_globals.fs_mp_dr_reduce_t3 >> ((fs_mp_word)DIGIT_BIT));
	}
	*fsv_mp_globals.fs_mp_dr_reduce_t4++ = fsv_mp_globals.fs_mp_dr_reduce_t6;
	for(fsv_mp_globals.fs_mp_dr_reduce_t1 = fsv_mp_globals.fs_mp_dr_reduce_t2 + 1; fsv_mp_globals.fs_mp_dr_reduce_t1 < fsv_mp_globals.fs_mp_xxx_reduce_a1->used; fsv_mp_globals.fs_mp_dr_reduce_t1++) {
		*fsv_mp_globals.fs_mp_dr_reduce_t4++ = 0;
	}
	fsv_mp_globals.fs_mp_clamp_a1 = fsv_mp_globals.fs_mp_xxx_reduce_a1;
	fs_mp_clamp();
	fsv_mp_globals.fs_mp_cmp_mag_a1 = fsv_mp_globals.fs_mp_xxx_reduce_a1;
	fsv_mp_globals.fs_mp_cmp_mag_a2 = fsv_mp_globals.fs_mp_xxx_reduce_a2;
	fs_mp_cmp_mag();
	if(fsv_mp_globals.fs_mp_cmp_mag_r != -1) {
		fsv_mp_globals.fs_mp_s_sub_a1 = fsv_mp_globals.fs_mp_xxx_reduce_a1;
		fsv_mp_globals.fs_mp_s_sub_a2 = fsv_mp_globals.fs_mp_xxx_reduce_a2;
		fsv_mp_globals.fs_mp_s_sub_a3 = fsv_mp_globals.fs_mp_xxx_reduce_a1;
		fs_mp_s_sub();
		goto top;
	}
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_mul_d(void) {
	fsv_mp_globals.fs_mp_error = 0;
	if(fsv_mp_globals.fs_mp_mul_d_a3->alloc < fsv_mp_globals.fs_mp_mul_d_a1->used + 1) {
		fsv_mp_globals.fs_mp_grow_a1 = fsv_mp_globals.fs_mp_mul_d_a3;
		fsv_mp_globals.fs_mp_grow_a2 = fsv_mp_globals.fs_mp_mul_d_a1->used + 1;
		fs_mp_grow();
		if(fsv_mp_globals.fs_mp_error) {
			goto done;
		}
	}
	fsv_mp_globals.fs_mp_mul_d_t6 = fsv_mp_globals.fs_mp_mul_d_a3->used;
	fsv_mp_globals.fs_mp_mul_d_a3->sign = fsv_mp_globals.fs_mp_mul_d_a1->sign;
	fsv_mp_globals.fs_mp_mul_d_t2 = fsv_mp_globals.fs_mp_mul_d_a1->dp;
	fsv_mp_globals.fs_mp_mul_d_t3 = fsv_mp_globals.fs_mp_mul_d_a3->dp;
	fsv_mp_globals.fs_mp_mul_d_t1 = 0;
	for(fsv_mp_globals.fs_mp_mul_d_t5 = 0; fsv_mp_globals.fs_mp_mul_d_t5 < fsv_mp_globals.fs_mp_mul_d_a1->used; fsv_mp_globals.fs_mp_mul_d_t5++) {
		fsv_mp_globals.fs_mp_mul_d_t4       = ((fs_mp_word) fsv_mp_globals.fs_mp_mul_d_t1) + ((fs_mp_word)*fsv_mp_globals.fs_mp_mul_d_t2++) * ((fs_mp_word)fsv_mp_globals.fs_mp_mul_d_a2);
		*fsv_mp_globals.fs_mp_mul_d_t3++ = (fs_mp_digit) (fsv_mp_globals.fs_mp_mul_d_t4 & ((fs_mp_word) ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1))));
		fsv_mp_globals.fs_mp_mul_d_t1       = (fs_mp_digit) (fsv_mp_globals.fs_mp_mul_d_t4 >> ((fs_mp_word) DIGIT_BIT));
	}
	*fsv_mp_globals.fs_mp_mul_d_t3++ = fsv_mp_globals.fs_mp_mul_d_t1;
	++fsv_mp_globals.fs_mp_mul_d_t5;
	while(fsv_mp_globals.fs_mp_mul_d_t5++ < fsv_mp_globals.fs_mp_mul_d_t6) {
		*fsv_mp_globals.fs_mp_mul_d_t3++ = 0;
	}
	fsv_mp_globals.fs_mp_mul_d_a3->used = fsv_mp_globals.fs_mp_mul_d_a1->used + 1;
	fsv_mp_globals.fs_mp_clamp_a1 = fsv_mp_globals.fs_mp_mul_d_a3;
	fs_mp_clamp();
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_reduce_2k(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_init_a1 = &fsv_mp_globals.fs_mp_reduce_2k_t1;
	fs_mp_init();
	if(!fsv_mp_globals.fs_mp_reduce_2k_t1.dp) {
		fsv_mp_globals.fs_mp_error = 1;
		goto done;
	}
	fsv_mp_globals.fs_mp_count_bits_a1 = fsv_mp_globals.fs_mp_xxx_reduce_a2;
	fs_mp_count_bits();
	top:
	fsv_mp_globals.fs_mp_div_2d_a1 = fsv_mp_globals.fs_mp_xxx_reduce_a1;
	fsv_mp_globals.fs_mp_div_2d_a2 = fsv_mp_globals.fs_mp_count_bits_r;
	fsv_mp_globals.fs_mp_div_2d_a3 = &fsv_mp_globals.fs_mp_reduce_2k_t1;
	fsv_mp_globals.fs_mp_div_2d_a4 = fsv_mp_globals.fs_mp_xxx_reduce_a1;
	fs_mp_div_2d();
	if(fsv_mp_globals.fs_mp_error) {
		goto LBL_ERR;
	}
	if(fsv_mp_globals.fs_mp_xxx_reduce_a3 != 1) {
		fsv_mp_globals.fs_mp_mul_d_a1 = &fsv_mp_globals.fs_mp_reduce_2k_t1;
		fsv_mp_globals.fs_mp_mul_d_a2 = fsv_mp_globals.fs_mp_xxx_reduce_a3;
		fsv_mp_globals.fs_mp_mul_d_a3 = &fsv_mp_globals.fs_mp_reduce_2k_t1;
		fs_mp_mul_d();
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_ERR;
		}
	}
	fsv_mp_globals.fs_mp_s_add_a1 = fsv_mp_globals.fs_mp_xxx_reduce_a1;
	fsv_mp_globals.fs_mp_s_add_a2 = &fsv_mp_globals.fs_mp_reduce_2k_t1;
	fsv_mp_globals.fs_mp_s_add_a3 = fsv_mp_globals.fs_mp_xxx_reduce_a1;
	fs_mp_s_add();
	if(fsv_mp_globals.fs_mp_error) {
		goto LBL_ERR;
	}
	fsv_mp_globals.fs_mp_cmp_mag_a1 = fsv_mp_globals.fs_mp_xxx_reduce_a1;
	fsv_mp_globals.fs_mp_cmp_mag_a2 = fsv_mp_globals.fs_mp_xxx_reduce_a2;
	fs_mp_cmp_mag();
	if(fsv_mp_globals.fs_mp_cmp_mag_r != -1) {
		fsv_mp_globals.fs_mp_s_sub_a1 = fsv_mp_globals.fs_mp_xxx_reduce_a1;
		fsv_mp_globals.fs_mp_s_sub_a2 = fsv_mp_globals.fs_mp_xxx_reduce_a2;
		fsv_mp_globals.fs_mp_s_sub_a3 = fsv_mp_globals.fs_mp_xxx_reduce_a1;
		fs_mp_s_sub();
		goto top;
	}
	LBL_ERR:
	fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_reduce_2k_t1;
	fs_mp_clear();
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_mul_2(void) {
	fsv_mp_globals.fs_mp_error = 0;
	if(fsv_mp_globals.fs_mp_mul_2_a2->alloc < fsv_mp_globals.fs_mp_mul_2_a1->used + 1) {
		fsv_mp_globals.fs_mp_grow_a1 = fsv_mp_globals.fs_mp_mul_2_a2;
		fsv_mp_globals.fs_mp_grow_a2 = fsv_mp_globals.fs_mp_mul_2_a1->used + 1;
		if(fsv_mp_globals.fs_mp_error) {
			goto done;
		}
	}
	fsv_mp_globals.fs_mp_mul_2_t2 = fsv_mp_globals.fs_mp_mul_2_a2->used;
	fsv_mp_globals.fs_mp_mul_2_a2->used = fsv_mp_globals.fs_mp_mul_2_a1->used;
	{
		fsv_mp_globals.fs_mp_mul_2_t5 = fsv_mp_globals.fs_mp_mul_2_a1->dp;
		fsv_mp_globals.fs_mp_mul_2_t6 = fsv_mp_globals.fs_mp_mul_2_a2->dp;
		fsv_mp_globals.fs_mp_mul_2_t3 = 0;
		for(fsv_mp_globals.fs_mp_mul_2_t1 = 0; fsv_mp_globals.fs_mp_mul_2_t1 < fsv_mp_globals.fs_mp_mul_2_a1->used; fsv_mp_globals.fs_mp_mul_2_t1++) {
			fsv_mp_globals.fs_mp_mul_2_t4 = *fsv_mp_globals.fs_mp_mul_2_t5 >> ((fs_mp_digit)(DIGIT_BIT - 1));
			*fsv_mp_globals.fs_mp_mul_2_t6++ = ((*fsv_mp_globals.fs_mp_mul_2_t5++ << ((fs_mp_digit)1)) | fsv_mp_globals.fs_mp_mul_2_t3) & ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1));
			fsv_mp_globals.fs_mp_mul_2_t3 = fsv_mp_globals.fs_mp_mul_2_t4;
		}
		if(fsv_mp_globals.fs_mp_mul_2_t3 != 0) {
			*fsv_mp_globals.fs_mp_mul_2_t6 = 1;
			++(fsv_mp_globals.fs_mp_mul_2_a2->used);
		}
		fsv_mp_globals.fs_mp_mul_2_t6 = fsv_mp_globals.fs_mp_mul_2_a2->dp + fsv_mp_globals.fs_mp_mul_2_a2->used;
		for(fsv_mp_globals.fs_mp_mul_2_t1 = fsv_mp_globals.fs_mp_mul_2_a2->used; fsv_mp_globals.fs_mp_mul_2_t1 < fsv_mp_globals.fs_mp_mul_2_t2; fsv_mp_globals.fs_mp_mul_2_t1++) {
			*fsv_mp_globals.fs_mp_mul_2_t6++ = 0;
		}
	}
	fsv_mp_globals.fs_mp_mul_2_a2->sign = fsv_mp_globals.fs_mp_mul_2_a1->sign;
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_montgomery_calc_normalization(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_count_bits_a1 = fsv_mp_globals.fs_mp_montgomery_calc_normalization_a2;
	fs_mp_count_bits();
	fsv_mp_globals.fs_mp_montgomery_calc_normalization_t2 = fsv_mp_globals.fs_mp_count_bits_r % DIGIT_BIT;
	if(fsv_mp_globals.fs_mp_montgomery_calc_normalization_a2->used > 1) {
		fsv_mp_globals.fs_mp_2expt_a1 = fsv_mp_globals.fs_mp_montgomery_calc_normalization_a1;
		fsv_mp_globals.fs_mp_2expt_a2 = (fsv_mp_globals.fs_mp_montgomery_calc_normalization_a2->used - 1) * DIGIT_BIT + fsv_mp_globals.fs_mp_montgomery_calc_normalization_t2 - 1;
		fs_mp_2expt();
		if(fsv_mp_globals.fs_mp_error) {
			goto done;
		}
	} else {
		fsv_mp_globals.fs_mp_set_a1 = fsv_mp_globals.fs_mp_montgomery_calc_normalization_a1;
		fsv_mp_globals.fs_mp_set_a2 =  1;
		fs_mp_set();
		fsv_mp_globals.fs_mp_montgomery_calc_normalization_t2 = 1;
	}
	for(fsv_mp_globals.fs_mp_montgomery_calc_normalization_t1 = fsv_mp_globals.fs_mp_montgomery_calc_normalization_t2 - 1; fsv_mp_globals.fs_mp_montgomery_calc_normalization_t1 < (int)DIGIT_BIT; fsv_mp_globals.fs_mp_montgomery_calc_normalization_t1++) {
		fsv_mp_globals.fs_mp_mul_2_a1 = fsv_mp_globals.fs_mp_montgomery_calc_normalization_a1;
		fsv_mp_globals.fs_mp_mul_2_a2 = fsv_mp_globals.fs_mp_montgomery_calc_normalization_a1;
		fs_mp_mul_2();
		if(fsv_mp_globals.fs_mp_error) {
			goto done;
		}
		fsv_mp_globals.fs_mp_cmp_mag_a1 = fsv_mp_globals.fs_mp_montgomery_calc_normalization_a1;
		fsv_mp_globals.fs_mp_cmp_mag_a2 = fsv_mp_globals.fs_mp_montgomery_calc_normalization_a2;
		fs_mp_cmp_mag();
		if(fsv_mp_globals.fs_mp_cmp_mag_r != -1) {
			fsv_mp_globals.fs_mp_s_sub_a1 = fsv_mp_globals.fs_mp_montgomery_calc_normalization_a1;
			fsv_mp_globals.fs_mp_s_sub_a2 = fsv_mp_globals.fs_mp_montgomery_calc_normalization_a2;
			fsv_mp_globals.fs_mp_s_sub_a3 = fsv_mp_globals.fs_mp_montgomery_calc_normalization_a1;
			fs_mp_s_sub();
			if(fsv_mp_globals.fs_mp_error) {
				goto done;
			}
		}
	}
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_exptmod_fast(void) {
	fsv_mp_globals.fs_mp_error = 0;
	fsv_mp_globals.fs_mp_count_bits_a1 = fsv_mp_globals.fs_mp_exptmod_fast_a2;
	fs_mp_count_bits();
	fs_mp_count_bits();
	if(fsv_mp_globals.fs_mp_count_bits_r <= 7) {
		fsv_mp_globals.fs_mp_exptmod_fast_t12 = 2;
	} else if(fsv_mp_globals.fs_mp_count_bits_r <= 36) {
		fsv_mp_globals.fs_mp_exptmod_fast_t12 = 3;
	} else if(fsv_mp_globals.fs_mp_count_bits_r <= 140) {
		fsv_mp_globals.fs_mp_exptmod_fast_t12 = 4;
	} else if(fsv_mp_globals.fs_mp_count_bits_r <= 450) {
		fsv_mp_globals.fs_mp_exptmod_fast_t12 = 5;
	} else if(fsv_mp_globals.fs_mp_count_bits_r <= 1303) {
		fsv_mp_globals.fs_mp_exptmod_fast_t12 = 6;
	} else if(fsv_mp_globals.fs_mp_count_bits_r <= 3529) {
		fsv_mp_globals.fs_mp_exptmod_fast_t12 = 7;
	} else {
		fsv_mp_globals.fs_mp_exptmod_fast_t12 = 8;
	}
	fsv_mp_globals.fs_mp_init_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t2[1];
	fs_mp_init();
	if(!fsv_mp_globals.fs_mp_exptmod_fast_t2[1].dp) {
		fsv_mp_globals.fs_mp_error = 1;
		goto done;
	}
	for(fsv_mp_globals.fs_mp_exptmod_fast_t10 = 1<<(fsv_mp_globals.fs_mp_exptmod_fast_t12-1); fsv_mp_globals.fs_mp_exptmod_fast_t10 < (1 << fsv_mp_globals.fs_mp_exptmod_fast_t12); fsv_mp_globals.fs_mp_exptmod_fast_t10++) {
		fsv_mp_globals.fs_mp_init_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t2[fsv_mp_globals.fs_mp_exptmod_fast_t10];
		fs_mp_init();
		if(!fsv_mp_globals.fs_mp_exptmod_fast_t2[fsv_mp_globals.fs_mp_exptmod_fast_t10].dp) {
			for(fsv_mp_globals.fs_mp_exptmod_fast_t11 = 1<<(fsv_mp_globals.fs_mp_exptmod_fast_t12-1); fsv_mp_globals.fs_mp_exptmod_fast_t11 < fsv_mp_globals.fs_mp_exptmod_fast_t10; fsv_mp_globals.fs_mp_exptmod_fast_t11++) {
				fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t2[fsv_mp_globals.fs_mp_exptmod_fast_t11];
				fs_mp_clear();
			}
			fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t2[1];
			fs_mp_clear();
			goto done;
		}
	}
	if(fsv_mp_globals.fs_mp_exptmod_fast_a5 == 0) {
		fsv_mp_globals.fs_mp_montgomery_setup_a1 = fsv_mp_globals.fs_mp_exptmod_fast_a3;
		fsv_mp_globals.fs_mp_montgomery_setup_a2 = &fsv_mp_globals.fs_mp_exptmod_fast_t4;
		fs_mp_montgomery_setup();
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_M;
		}
		if(((fsv_mp_globals.fs_mp_exptmod_fast_a3->used * 2 + 1) < (1 << (sizeof(fs_mp_word) * 8 - 2 * DIGIT_BIT + 1))) &&
		   fsv_mp_globals.fs_mp_exptmod_fast_a3->used < (1 << ((8 * sizeof (fs_mp_word)) - (2 * DIGIT_BIT)))) {
			fsv_mp_globals.fs_mp_exptmod_fast_t13 = 1;//fs_mp_fast_montgomery_reduce;
		} else {
			fsv_mp_globals.fs_mp_exptmod_fast_t13 = 2;//fs_mp_montgomery_reduce;
			fsv_mp_globals.fs_mp_error = 1;
			goto LBL_M;
		}
	} else if(fsv_mp_globals.fs_mp_exptmod_fast_a5 == 1) {
		fsv_mp_globals.fs_mp_exptmod_fast_t4 = (fs_mp_digit)((((fs_mp_word)1) << ((fs_mp_word)DIGIT_BIT)) - ((fs_mp_word)fsv_mp_globals.fs_mp_exptmod_fast_a3->dp[0]));
		fsv_mp_globals.fs_mp_exptmod_fast_t13 = 3; //fs_mp_dr_reduce;
	} else {
		fsv_mp_globals.fs_mp_reduce_2k_setup_a1 = fsv_mp_globals.fs_mp_exptmod_fast_a3;
		fsv_mp_globals.fs_mp_reduce_2k_setup_a2 = &fsv_mp_globals.fs_mp_exptmod_fast_t4;
		fs_mp_reduce_2k_setup();
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_M;
		}
		fsv_mp_globals.fs_mp_exptmod_fast_t13 = 4; //fs_mp_reduce_2k;
	}
	fsv_mp_globals.fs_mp_init_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t14;
	fs_mp_init();
	if(!fsv_mp_globals.fs_mp_exptmod_fast_t14.dp) {
		fsv_mp_globals.fs_mp_error = 1;
		goto LBL_M;
	}
	if(fsv_mp_globals.fs_mp_exptmod_fast_a5 == 0) {
		fsv_mp_globals.fs_mp_montgomery_calc_normalization_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t14;
		fsv_mp_globals.fs_mp_montgomery_calc_normalization_a2 = fsv_mp_globals.fs_mp_exptmod_fast_a3;
		fs_mp_montgomery_calc_normalization();
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_RES;
		}
		fsv_mp_globals.fs_mp_init_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t1;
		fs_mp_init();
		if(!fsv_mp_globals.fs_mp_exptmod_fast_t1.dp) {
			fsv_mp_globals.fs_mp_error = 1;
			goto done;
		}
		fsv_mp_globals.fs_mp_mul_a1 = fsv_mp_globals.fs_mp_exptmod_fast_a1;
		fsv_mp_globals.fs_mp_mul_a2 = &fsv_mp_globals.fs_mp_exptmod_fast_t14;
		fsv_mp_globals.fs_mp_mul_a3 = &fsv_mp_globals.fs_mp_exptmod_fast_t1;
		fs_mp_mul();
		if(fsv_mp_globals.fs_mp_error) {
			fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t1;
			fs_mp_clear();
			goto done;
		}
		fsv_mp_globals.fs_mp_mod_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t1;
		fsv_mp_globals.fs_mp_mod_a2 = fsv_mp_globals.fs_mp_exptmod_fast_a3;
		fsv_mp_globals.fs_mp_mod_a3 = &fsv_mp_globals.fs_mp_exptmod_fast_t2[1];
		fs_mp_mod();
		fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t1;
		fs_mp_clear();
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_RES;
		}
	} else {
		fsv_mp_globals.fs_mp_set_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t14;
		fsv_mp_globals.fs_mp_set_a2 =  1;
		fs_mp_set();
		fsv_mp_globals.fs_mp_mod_a1 = fsv_mp_globals.fs_mp_exptmod_fast_a1;
		fsv_mp_globals.fs_mp_mod_a2 = fsv_mp_globals.fs_mp_exptmod_fast_a3;
		fsv_mp_globals.fs_mp_mod_a3 = &fsv_mp_globals.fs_mp_exptmod_fast_t2[1];
		fs_mp_mod();
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_RES;
		}
	}
	fsv_mp_globals.fs_mp_copy_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t2[1];
	fsv_mp_globals.fs_mp_copy_a2 = &fsv_mp_globals.fs_mp_exptmod_fast_t2[1 << (fsv_mp_globals.fs_mp_exptmod_fast_t12 - 1)];
	fs_mp_copy();
	if(fsv_mp_globals.fs_mp_error) {
		goto LBL_RES;
	}
	for(fsv_mp_globals.fs_mp_exptmod_fast_t10 = 0; fsv_mp_globals.fs_mp_exptmod_fast_t10 < (fsv_mp_globals.fs_mp_exptmod_fast_t12 - 1); fsv_mp_globals.fs_mp_exptmod_fast_t10++) {
		fsv_mp_globals.fs_mp_sqr_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t2[1 << (fsv_mp_globals.fs_mp_exptmod_fast_t12 - 1)];
		fsv_mp_globals.fs_mp_sqr_a2 = &fsv_mp_globals.fs_mp_exptmod_fast_t2[1 << (fsv_mp_globals.fs_mp_exptmod_fast_t12 - 1)];
		fs_mp_sqr();
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_RES;
		}
		fsv_mp_globals.fs_mp_xxx_reduce_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t2[1 << (fsv_mp_globals.fs_mp_exptmod_fast_t12 - 1)];
		fsv_mp_globals.fs_mp_xxx_reduce_a2 = fsv_mp_globals.fs_mp_exptmod_fast_a3;
		fsv_mp_globals.fs_mp_xxx_reduce_a3 = fsv_mp_globals.fs_mp_exptmod_fast_t4;
		switch(fsv_mp_globals.fs_mp_exptmod_fast_t13) {
		case 1:
			fs_mp_fast_montgomery_reduce();
			break;
		case 2:
			fs_mp_montgomery_reduce();
			break;
		case 3:
			fs_mp_dr_reduce();
			break;
		case 4:
			fs_mp_reduce_2k();
			break;
		default:
			break;
		}
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_RES;
		}
	}
	for(fsv_mp_globals.fs_mp_exptmod_fast_t10 = (1 << (fsv_mp_globals.fs_mp_exptmod_fast_t12 - 1)) + 1; fsv_mp_globals.fs_mp_exptmod_fast_t10 < (1 << fsv_mp_globals.fs_mp_exptmod_fast_t12); fsv_mp_globals.fs_mp_exptmod_fast_t10++) {
		fsv_mp_globals.fs_mp_mul_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t2[fsv_mp_globals.fs_mp_exptmod_fast_t10 - 1];
		fsv_mp_globals.fs_mp_mul_a2 = &fsv_mp_globals.fs_mp_exptmod_fast_t2[1];
		fsv_mp_globals.fs_mp_mul_a3 = &fsv_mp_globals.fs_mp_exptmod_fast_t2[fsv_mp_globals.fs_mp_exptmod_fast_t10];
		fs_mp_mul();
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_RES;
		}
		fsv_mp_globals.fs_mp_xxx_reduce_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t2[fsv_mp_globals.fs_mp_exptmod_fast_t10];
		fsv_mp_globals.fs_mp_xxx_reduce_a2 = fsv_mp_globals.fs_mp_exptmod_fast_a3;
		fsv_mp_globals.fs_mp_xxx_reduce_a3 = fsv_mp_globals.fs_mp_exptmod_fast_t4;
		switch(fsv_mp_globals.fs_mp_exptmod_fast_t13) {
		case 1:
			fs_mp_fast_montgomery_reduce();
			break;
		case 2:
			fs_mp_montgomery_reduce();
			break;
		case 3:
			fs_mp_dr_reduce();
			break;
		case 4:
			fs_mp_reduce_2k();
			break;
		default:
			break;
		}
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_RES;
		}
	}
	fsv_mp_globals.fs_mp_exptmod_fast_t8   = 0;
	fsv_mp_globals.fs_mp_exptmod_fast_t7 = 1;
	fsv_mp_globals.fs_mp_exptmod_fast_t3    = 0;
	fsv_mp_globals.fs_mp_exptmod_fast_t9 = fsv_mp_globals.fs_mp_exptmod_fast_a2->used - 1;
	fsv_mp_globals.fs_mp_exptmod_fast_t6 = 0;
	fsv_mp_globals.fs_mp_exptmod_fast_t5 = 0;
	for(;;) {
		if(--fsv_mp_globals.fs_mp_exptmod_fast_t7 == 0) {
			if(fsv_mp_globals.fs_mp_exptmod_fast_t9 == -1) {
				break;
			}
			fsv_mp_globals.fs_mp_exptmod_fast_t3    = fsv_mp_globals.fs_mp_exptmod_fast_a2->dp[fsv_mp_globals.fs_mp_exptmod_fast_t9--];
			fsv_mp_globals.fs_mp_exptmod_fast_t7 = (int)DIGIT_BIT;
		}
		fsv_mp_globals.fs_mp_exptmod_fast_t11     = (fs_mp_digit)(fsv_mp_globals.fs_mp_exptmod_fast_t3 >> (DIGIT_BIT - 1)) & 1;
		fsv_mp_globals.fs_mp_exptmod_fast_t3 <<= (fs_mp_digit)1;
		if(fsv_mp_globals.fs_mp_exptmod_fast_t8 == 0 && fsv_mp_globals.fs_mp_exptmod_fast_t11 == 0) {
			continue;
		}
		if(fsv_mp_globals.fs_mp_exptmod_fast_t8 == 1 && fsv_mp_globals.fs_mp_exptmod_fast_t11 == 0) {
			fsv_mp_globals.fs_mp_sqr_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t14;
			fsv_mp_globals.fs_mp_sqr_a2 = &fsv_mp_globals.fs_mp_exptmod_fast_t14;
			fs_mp_sqr();
			if(fsv_mp_globals.fs_mp_error) {
				goto LBL_RES;
			}
			fsv_mp_globals.fs_mp_xxx_reduce_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t14;
			fsv_mp_globals.fs_mp_xxx_reduce_a2 = fsv_mp_globals.fs_mp_exptmod_fast_a3;
			fsv_mp_globals.fs_mp_xxx_reduce_a3 = fsv_mp_globals.fs_mp_exptmod_fast_t4;
			switch(fsv_mp_globals.fs_mp_exptmod_fast_t13) {
			case 1:
				fs_mp_fast_montgomery_reduce();
				break;
			case 2:
				fs_mp_montgomery_reduce();
				break;
			case 3:
				fs_mp_dr_reduce();
				break;
			case 4:
				fs_mp_reduce_2k();
				break;
			default:
				break;
			}
			if(fsv_mp_globals.fs_mp_error) {
				goto LBL_RES;
			}
			continue;
		}
		fsv_mp_globals.fs_mp_exptmod_fast_t5 |= (fsv_mp_globals.fs_mp_exptmod_fast_t11 << (fsv_mp_globals.fs_mp_exptmod_fast_t12 - ++fsv_mp_globals.fs_mp_exptmod_fast_t6));
		fsv_mp_globals.fs_mp_exptmod_fast_t8    = 2;
		if(fsv_mp_globals.fs_mp_exptmod_fast_t6 == fsv_mp_globals.fs_mp_exptmod_fast_t12) {
			for(fsv_mp_globals.fs_mp_exptmod_fast_t10 = 0; fsv_mp_globals.fs_mp_exptmod_fast_t10 < fsv_mp_globals.fs_mp_exptmod_fast_t12; fsv_mp_globals.fs_mp_exptmod_fast_t10++) {
				fsv_mp_globals.fs_mp_sqr_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t14;
				fsv_mp_globals.fs_mp_sqr_a2 = &fsv_mp_globals.fs_mp_exptmod_fast_t14;
				fs_mp_sqr();
				if(fsv_mp_globals.fs_mp_error) {
					goto LBL_RES;
				}
				fsv_mp_globals.fs_mp_xxx_reduce_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t14;
				fsv_mp_globals.fs_mp_xxx_reduce_a2 = fsv_mp_globals.fs_mp_exptmod_fast_a3;
				fsv_mp_globals.fs_mp_xxx_reduce_a3 = fsv_mp_globals.fs_mp_exptmod_fast_t4;
				switch(fsv_mp_globals.fs_mp_exptmod_fast_t13) {
				case 1:
					fs_mp_fast_montgomery_reduce();
					break;
				case 2:
					fs_mp_montgomery_reduce();
					break;
				case 3:
					fs_mp_dr_reduce();
					break;
				case 4:
					fs_mp_reduce_2k();
					break;
				default:
					break;
				}
				if(fsv_mp_globals.fs_mp_error) {
					goto LBL_RES;
				}
			}
			fsv_mp_globals.fs_mp_mul_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t14;
			fsv_mp_globals.fs_mp_mul_a2 = &fsv_mp_globals.fs_mp_exptmod_fast_t2[fsv_mp_globals.fs_mp_exptmod_fast_t5];
			fsv_mp_globals.fs_mp_mul_a3 = &fsv_mp_globals.fs_mp_exptmod_fast_t14;
			fs_mp_mul();
			if(fsv_mp_globals.fs_mp_error) {
				goto LBL_RES;
			}
			fsv_mp_globals.fs_mp_xxx_reduce_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t14;
			fsv_mp_globals.fs_mp_xxx_reduce_a2 = fsv_mp_globals.fs_mp_exptmod_fast_a3;
			fsv_mp_globals.fs_mp_xxx_reduce_a3 = fsv_mp_globals.fs_mp_exptmod_fast_t4;
			switch(fsv_mp_globals.fs_mp_exptmod_fast_t13) {
			case 1:
				fs_mp_fast_montgomery_reduce();
				break;
			case 2:
				fs_mp_montgomery_reduce();
				break;
			case 3:
				fs_mp_dr_reduce();
				break;
			case 4:
				fs_mp_reduce_2k();
				break;
			default:
				break;
			}
			if(fsv_mp_globals.fs_mp_error) {
				goto LBL_RES;
			}
			fsv_mp_globals.fs_mp_exptmod_fast_t6 = 0;
			fsv_mp_globals.fs_mp_exptmod_fast_t5 = 0;
			fsv_mp_globals.fs_mp_exptmod_fast_t8   = 1;
		}
	}
	if(fsv_mp_globals.fs_mp_exptmod_fast_t8 == 2 && fsv_mp_globals.fs_mp_exptmod_fast_t6 > 0) {
		for(fsv_mp_globals.fs_mp_exptmod_fast_t10 = 0; fsv_mp_globals.fs_mp_exptmod_fast_t10 < fsv_mp_globals.fs_mp_exptmod_fast_t6; fsv_mp_globals.fs_mp_exptmod_fast_t10++) {
			fsv_mp_globals.fs_mp_sqr_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t14;
			fsv_mp_globals.fs_mp_sqr_a2 = &fsv_mp_globals.fs_mp_exptmod_fast_t14;
			fs_mp_sqr();
			if(fsv_mp_globals.fs_mp_error) {
				goto LBL_RES;
			}
			fsv_mp_globals.fs_mp_xxx_reduce_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t14;
			fsv_mp_globals.fs_mp_xxx_reduce_a2 = fsv_mp_globals.fs_mp_exptmod_fast_a3;
			fsv_mp_globals.fs_mp_xxx_reduce_a3 = fsv_mp_globals.fs_mp_exptmod_fast_t4;
			switch(fsv_mp_globals.fs_mp_exptmod_fast_t13) {
			case 1:
				fs_mp_fast_montgomery_reduce();
				break;
			case 2:
				fs_mp_montgomery_reduce();
				break;
			case 3:
				fs_mp_dr_reduce();
				break;
			case 4:
				fs_mp_reduce_2k();
				break;
			default:
				break;
			}
			if(fsv_mp_globals.fs_mp_error) {
				goto LBL_RES;
			}
			fsv_mp_globals.fs_mp_exptmod_fast_t5 <<= 1;
			if((fsv_mp_globals.fs_mp_exptmod_fast_t5 & (1 << fsv_mp_globals.fs_mp_exptmod_fast_t12)) != 0) {
				fsv_mp_globals.fs_mp_mul_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t14;
				fsv_mp_globals.fs_mp_mul_a2 = &fsv_mp_globals.fs_mp_exptmod_fast_t2[1];
				fsv_mp_globals.fs_mp_mul_a3 = &fsv_mp_globals.fs_mp_exptmod_fast_t14;
				fs_mp_mul();
				if(fsv_mp_globals.fs_mp_error) {
					goto LBL_RES;
				}
				fsv_mp_globals.fs_mp_xxx_reduce_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t14;
				fsv_mp_globals.fs_mp_xxx_reduce_a2 = fsv_mp_globals.fs_mp_exptmod_fast_a3;
				fsv_mp_globals.fs_mp_xxx_reduce_a3 = fsv_mp_globals.fs_mp_exptmod_fast_t4;
				switch(fsv_mp_globals.fs_mp_exptmod_fast_t13) {
				case 1:
					fs_mp_fast_montgomery_reduce();
					break;
				case 2:
					fs_mp_montgomery_reduce();
					break;
				case 3:
					fs_mp_dr_reduce();
					break;
				case 4:
					fs_mp_reduce_2k();
					break;
				default:
					break;
				}
				if(fsv_mp_globals.fs_mp_error) {
					goto LBL_RES;
				}
			}
		}
	}
	if(fsv_mp_globals.fs_mp_exptmod_fast_a5 == 0) {
		fsv_mp_globals.fs_mp_xxx_reduce_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t14;
		fsv_mp_globals.fs_mp_xxx_reduce_a2 = fsv_mp_globals.fs_mp_exptmod_fast_a3;
		fsv_mp_globals.fs_mp_xxx_reduce_a3 = fsv_mp_globals.fs_mp_exptmod_fast_t4;
		switch(fsv_mp_globals.fs_mp_exptmod_fast_t13) {
		case 1:
			fs_mp_fast_montgomery_reduce();
			break;
		case 2:
			fs_mp_montgomery_reduce();
			break;
		case 3:
			fs_mp_dr_reduce();
			break;
		case 4:
			fs_mp_reduce_2k();
			break;
		default:
			break;
		}
		if(fsv_mp_globals.fs_mp_error) {
			goto LBL_RES;
		}
	}
	fsv_mp_globals.fs_mp_exch_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t14;
	fsv_mp_globals.fs_mp_exch_a2 = fsv_mp_globals.fs_mp_exptmod_fast_a4;
	fs_mp_exch();
	fsv_mp_globals.fs_mp_error = 0;
	LBL_RES:
	fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t14;
	fs_mp_clear();
	LBL_M:
	fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t2[1];
	fs_mp_clear();
	for(fsv_mp_globals.fs_mp_exptmod_fast_t10 = 1<<(fsv_mp_globals.fs_mp_exptmod_fast_t12-1); fsv_mp_globals.fs_mp_exptmod_fast_t10 < (1 << fsv_mp_globals.fs_mp_exptmod_fast_t12); fsv_mp_globals.fs_mp_exptmod_fast_t10++) {
		fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_exptmod_fast_t2[fsv_mp_globals.fs_mp_exptmod_fast_t10];
		fs_mp_clear();
	}
	done:
	;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_exptmod(void) {
	fsv_mp_globals.fs_mp_error = 0;
	if(fsv_mp_globals.fs_mp_exptmod_a3->sign == -1) {
		fsv_mp_globals.fs_mp_error = 1;
		goto done;
	}
	if(fsv_mp_globals.fs_mp_exptmod_a2->sign == -1) {
		fsv_mp_globals.fs_mp_init_a1 = &fsv_mp_globals.fs_mp_exptmod_t2;
		fs_mp_init();
		if(!fsv_mp_globals.fs_mp_exptmod_t2.dp) {
			fsv_mp_globals.fs_mp_error = 1;
			goto done;
		}
		fsv_mp_globals.fs_mp_invmod_a1 = fsv_mp_globals.fs_mp_exptmod_a1;
		fsv_mp_globals.fs_mp_invmod_a2 = fsv_mp_globals.fs_mp_exptmod_a3;
		fsv_mp_globals.fs_mp_invmod_a3 = &fsv_mp_globals.fs_mp_exptmod_t2;
		fs_mp_invmod();
		if(fsv_mp_globals.fs_mp_error) {
			fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_exptmod_t2;
			fs_mp_clear();
			goto done;
		}
		fsv_mp_globals.fs_mp_init_a1 = &fsv_mp_globals.fs_mp_exptmod_t3;
		fs_mp_init();
		if(!fsv_mp_globals.fs_mp_exptmod_t3.dp) {
			fsv_mp_globals.fs_mp_error = 1;
			fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_exptmod_t2;
			fs_mp_clear();
			goto done;
		}
		fsv_mp_globals.fs_mp_abs_a1 = fsv_mp_globals.fs_mp_exptmod_a2;
		fsv_mp_globals.fs_mp_abs_a2 = &fsv_mp_globals.fs_mp_exptmod_t3;
		fs_mp_abs();
		if(fsv_mp_globals.fs_mp_error) {
			fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_exptmod_t2;
			fs_mp_clear();
			fsv_mp_globals.fs_mp_clear_a1 = &fsv_mp_globals.fs_mp_exptmod_t3;
			goto done;
		}
		fsv_mp_globals.fs_mp_error = 1;
		goto done;
	}
	if(fsv_mp_globals.fs_mp_exptmod_a3->used == 0) {
		fsv_mp_globals.fs_mp_exptmod_t6 = 0;
	} else if(fsv_mp_globals.fs_mp_exptmod_a3->used == 1) {
		fsv_mp_globals.fs_mp_exptmod_t6 = 1;
	} else if(fsv_mp_globals.fs_mp_exptmod_a3->used > 1) {
		for(fsv_mp_globals.fs_mp_exptmod_t5 = fsv_mp_globals.fs_mp_exptmod_t4 = 0; fsv_mp_globals.fs_mp_exptmod_t4 < fsv_mp_globals.fs_mp_exptmod_a3->used; fsv_mp_globals.fs_mp_exptmod_t4++) {
			if(fsv_mp_globals.fs_mp_exptmod_a3->dp[fsv_mp_globals.fs_mp_exptmod_t4] == ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1))) {
				++fsv_mp_globals.fs_mp_exptmod_t5;
			}
		}
		fsv_mp_globals.fs_mp_exptmod_t6 = (fsv_mp_globals.fs_mp_exptmod_t5 >= (fsv_mp_globals.fs_mp_exptmod_a3->used/2)) ? 1 : 0;
	}
	if(fsv_mp_globals.fs_mp_exptmod_t6 == 1) {
		fsv_mp_globals.fs_mp_s_exptmod_a1 = fsv_mp_globals.fs_mp_exptmod_a1;
		fsv_mp_globals.fs_mp_s_exptmod_a2 = fsv_mp_globals.fs_mp_exptmod_a2;
		fsv_mp_globals.fs_mp_s_exptmod_a3 = fsv_mp_globals.fs_mp_exptmod_a3;
		fsv_mp_globals.fs_mp_s_exptmod_a4 = fsv_mp_globals.fs_mp_exptmod_a4;
		fsv_mp_globals.fs_mp_s_exptmod_a5 = 1;
		fs_mp_s_exptmod();
		goto done;
	}
	fsv_mp_globals.fs_mp_dr_is_modulus_a1 = fsv_mp_globals.fs_mp_exptmod_a3;
	fs_mp_dr_is_modulus();
	fsv_mp_globals.fs_mp_exptmod_t1 = fsv_mp_globals.fs_mp_dr_is_modulus_r;
	if(fsv_mp_globals.fs_mp_exptmod_t1 == 0) {
		fsv_mp_globals.fs_mp_reduce_is_2k_a1 = fsv_mp_globals.fs_mp_exptmod_a3;
		fs_mp_reduce_is_2k();
		fsv_mp_globals.fs_mp_exptmod_t1 = fsv_mp_globals.fs_mp_reduce_is_2k_r << 1;
	}
	if((((fsv_mp_globals.fs_mp_exptmod_a3)->used > 0 && (((fsv_mp_globals.fs_mp_exptmod_a3)->dp[0] & 1) == 1)) ? 1 : 0) == 1 || fsv_mp_globals.fs_mp_exptmod_t1 !=  0) {
		fsv_mp_globals.fs_mp_exptmod_fast_a1 = fsv_mp_globals.fs_mp_exptmod_a1;
		fsv_mp_globals.fs_mp_exptmod_fast_a2 = fsv_mp_globals.fs_mp_exptmod_a2;
		fsv_mp_globals.fs_mp_exptmod_fast_a3 = fsv_mp_globals.fs_mp_exptmod_a3;
		fsv_mp_globals.fs_mp_exptmod_fast_a4 = fsv_mp_globals.fs_mp_exptmod_a4;
		fsv_mp_globals.fs_mp_exptmod_fast_a5 = fsv_mp_globals.fs_mp_exptmod_t1;
		fs_mp_exptmod_fast();
		goto done;
	} else {
		fsv_mp_globals.fs_mp_s_exptmod_a1 = fsv_mp_globals.fs_mp_exptmod_a1;
		fsv_mp_globals.fs_mp_s_exptmod_a2 = fsv_mp_globals.fs_mp_exptmod_a2;
		fsv_mp_globals.fs_mp_s_exptmod_a3 = fsv_mp_globals.fs_mp_exptmod_a3;
		fsv_mp_globals.fs_mp_s_exptmod_a4 = fsv_mp_globals.fs_mp_exptmod_a4;
		fsv_mp_globals.fs_mp_s_exptmod_a5 = 0;
		fs_mp_s_exptmod();
		goto done;
	}
	done:
	;
}

