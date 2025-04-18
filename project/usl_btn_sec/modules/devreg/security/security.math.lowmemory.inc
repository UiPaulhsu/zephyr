#define FS_MP_PREC 1
typedef u_int32_t fs_mp_digit;
typedef u_int64_t fs_mp_word;
#define DIGIT_BIT 28

typedef struct {
    int used;
    int alloc;
    int sign;
    fs_mp_digit* dp;
} fs_mp_int;

static int fs_mp_error;

__FS_FUNCTION_MAYBE_INLINE void fs_mp_zero(fs_mp_int* a1) {
    int t1 = 0;
    fs_mp_digit* t2 = NULL;

    fs_mp_error = 0;

    a1->sign = a1->used = 0;
    t2 = a1->dp;
    for(t1 = 0; t1 < a1->alloc; t1++) {
        *t2++ = 0;
    }
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_shrink(fs_mp_int* a1) {
  fs_mp_digit *t1;
  fs_mp_error = 0;

  if (a1->alloc != a1->used && a1->used > 0) {
    if ((t1 = fs_realloc(a1->dp, sizeof (fs_mp_digit) * a1->used)) == NULL) {
        if(!t1) {
            fs_mp_error = 1;
            goto done;
        }
    }
    a1->dp    = t1;
    a1->alloc = a1->used;
  }
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_clear(fs_mp_int* a1) {
    int t1 = 0;

    fs_mp_error = 0;

    if(a1->dp != NULL) {
        for(t1 = 0; t1 < a1->used; t1++) {
            a1->dp[t1] = 0;
        }
        fs_safe_shred_and_free(&a1->dp, a1->alloc * sizeof(*a1->dp));
        a1->dp = NULL;
        a1->alloc = a1->used = a1->sign = 0;
    }
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_safe_shred_and_free_mp_int(fs_mp_int** a1) {
    int t1 = 0;

    fs_mp_error = 0;

    if(a1 != NULL) {
        if((*a1) != NULL) {
            t1 = 0;
            if((*a1)->dp != NULL) {
                for(t1 = 0; t1 < (*a1)->used; t1++) {
                    (*a1)->dp[t1] = 0;
                }
                fs_safe_shred_and_free(&(*a1)->dp, (*a1)->alloc * sizeof(*(*a1)->dp));
                (*a1)->dp    = NULL;
                (*a1)->alloc = (*a1)->used = 0;
                (*a1)->sign  = 0;
            }
            fs_safe_shred_and_free(a1, sizeof(*(*a1)));
            (*a1) = NULL;
        }
    }
}

__FS_FUNCTION_MAYBE_INLINE int fs_mp_count_bits(fs_mp_int* a1) {
    int r = 0;
    fs_mp_digit t1 = 0;

    fs_mp_error = 0;

    if(a1 == NULL) {
        r = 1;
        goto done;
    }
    if(a1->used == 0) {
        r = 0;
        goto done;
    }
    r = (a1->used - 1) * DIGIT_BIT;
    t1 = a1->dp[a1->used - 1];
    while(t1 > ((fs_mp_digit) 0)) {
        ++r;
        t1 >>= ((fs_mp_digit) 1);
    }
done:
    return r;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_init(fs_mp_int* a1) {
    fs_mp_error = 0;

    memset((char*)a1, 0, sizeof(*a1));
    a1->dp = (fs_mp_digit*)fs_zalloc(sizeof (fs_mp_digit) * FS_MP_PREC);
    if(a1->dp != NULL) {
        a1->alloc = FS_MP_PREC;
    } else {
        fs_mp_error = 1;
    }
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_alloc_and_init(fs_mp_int** a1) {
    fs_mp_error = 0;

    *a1 = (fs_mp_int*)fs_zalloc(sizeof(fs_mp_int));
    if(*a1) {
        memset((char*)*a1, 0, sizeof(fs_mp_int));
        (*a1)->dp = (fs_mp_digit*)fs_zalloc(sizeof (fs_mp_digit) * FS_MP_PREC);
        if((*a1)->dp != NULL) {
            (*a1)->alloc = FS_MP_PREC;
        } else {
            fs_free(*a1);
            *a1 = NULL;
        }
    }
}

__FS_FUNCTION_MAYBE_INLINE size_t fs_mp_unsigned_bin_size(fs_mp_int* a1) {
    int t1 = 0;

    fs_mp_error = 0;

    t1 = fs_mp_count_bits(a1);
    return (t1 / 8 + ((t1 & 7) != 0 ? 1 : 0));
}

__FS_FUNCTION_MAYBE_INLINE int fs_mp_cnt_lsb(fs_mp_int* a1) {
    int r = 0;
    fs_mp_digit t1 = 0;
    fs_mp_digit t2 = 0;
    const int t3[16] = { 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0 };

    fs_mp_error = 0;

    if((((a1)->used == 0) ? 1 : 0) == 1) {
        goto done;
    }
    for(r = 0; r < a1->used && a1->dp[r] == 0; r++) {
        /* nothing*/
    }
    t1 = a1->dp[r];
    r *= DIGIT_BIT;
    if((t1 & 1) == 0) {
        do {
            t2  = t1 & 15;
            r  += t3[t2];
            t1 >>= 4;
        } while(t2 == 0);
    }
done:
    return r;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_grow(fs_mp_int* a1, int a2) {
    fs_mp_digit* t1 = NULL;
    int t2 = 0;

    fs_mp_error = 0;

    if(a1->alloc < a2) {
        a2 += (FS_MP_PREC * 2) - (a2 % FS_MP_PREC);
        t1 = (fs_mp_digit*)fs_realloc(a1->dp, sizeof (fs_mp_digit) * a2);
        if(!t1) {
            fs_mp_error = 1;
            goto done;
        }
        a1->dp = t1;
        t2 = a1->alloc;
        a1->alloc = a2;
        for(; t2 < a1->alloc; t2++) {
            a1->dp[t2] = 0;
        }
    }
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_copy(fs_mp_int* a1, fs_mp_int* a2) {
    fs_mp_digit* t1 = NULL;
    fs_mp_digit* t2 = NULL;
    int t3 = 0;

    fs_mp_error   = 0;

    if(a1 == a2) {
        fs_mp_error = 0;
        goto done;
    }
    if(a2->alloc < a1->used) {
        fs_mp_grow(a2, a1->used);
        if(fs_mp_error) {
            goto done;
        }
    }
    t1 = a1->dp;
    t2 = a2->dp;
    for(t3 = 0; t3 < a1->used; t3++) {
        *t2++ = *t1++;
    }
    for(; t3 < a2->used; t3++) {
        *t2++ = 0;
    }
    a2->used = a1->used;
    a2->sign = a1->sign;
done:
    ;
}


__FS_FUNCTION_MAYBE_INLINE void fs_mp_2expt(fs_mp_int* a1, int a2) {
    fs_mp_error = 0;

    fs_mp_zero(a1);
    fs_mp_grow(a1, a2 / DIGIT_BIT + 1);
    if(fs_mp_error) {
        goto done;
    }
    a1->used = a2 / DIGIT_BIT + 1;
    a1->dp[a2 / DIGIT_BIT] = ((fs_mp_digit)1) << (a2 % DIGIT_BIT);
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_clamp(fs_mp_int* a1) {
    fs_mp_error = 0;

    while(a1->used > 0 && a1->dp[a1->used - 1] == 0) {
        --(a1->used);
    }
    if(a1->used == 0) {
        a1->sign = 0;
    }
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_abs(fs_mp_int* a1, fs_mp_int* a2) {
    fs_mp_error = 0;
    if(a1 != a2) {
        fs_mp_copy(a1, a2);
        if(fs_mp_error) {
            goto done;
        }
    }
    a2->sign = 0;
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_rshd(fs_mp_int* a1, int a2) {
    int t1 = 0;
    fs_mp_digit* t2 = NULL;
    fs_mp_digit* t3 = NULL;

    fs_mp_error = 0;

    if(a2 <= 0) {
        goto done;
    }
    if(a1->used <= a2) {
        fs_mp_zero(a1);
        goto done;
    }
    t2 = a1->dp;
    t3 = a1->dp + a2;
    for(t1 = 0; t1 < (a1->used - a2); t1++) {
        *t2++ = *t3++;
    }
    for(; t1 < a1->used; t1++) {
        *t2++ = 0;
    }
    a1->used -= a2;
done:
    return;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_lshd(fs_mp_int* a1, int a2) {
    int t1 = 0;
    fs_mp_digit* t2 = NULL;
    fs_mp_digit* t3 = NULL;

    fs_mp_error = 0;

    if(a2 <= 0) {
        goto done;
    }
    if(a1->alloc < a1->used + a2) {
        fs_mp_grow(a1, a1->used + a2);
        if(fs_mp_error) {
            goto done;
        }
    }
    a1->used += a2;
    t2 = a1->dp + a1->used - 1;
    t3 = a1->dp + a1->used - 1 - a2;
    for(t1 = a1->used - 1; t1 >= a2; t1--) {
        *t2-- = *t3--;
    }
    t2 = a1->dp;
    for(t1 = 0; t1 < a2; t1++) {
        *t2++ = 0;
    }
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_mul_2d(fs_mp_int* a1, int a2, fs_mp_int* a3) {
    fs_mp_digit t1 = 0;
    int t2 = 0;
    fs_mp_digit* t3 = NULL;
    fs_mp_digit t4 = 0;
    fs_mp_digit t5 = 0;
    fs_mp_digit t6 = 0;
    fs_mp_digit t7 = 0;

    fs_mp_error = 0;

    if(a1 != a3) {
        fs_mp_copy(a1, a3);
        if(fs_mp_error) {
            goto done;
        }
    }
    if(a3->alloc < (int)(a3->used + a2/DIGIT_BIT + 1)) {
        fs_mp_grow(a3, a3->used + a2 / DIGIT_BIT + 1);
        if(fs_mp_error) {
            goto done;
        }
    }
    if(a2 >= (int)DIGIT_BIT) {
        fs_mp_lshd(a3, a2 / DIGIT_BIT);
        if(fs_mp_error) {
            goto done;
        }
    }
    t1 = (fs_mp_digit) (a2 % DIGIT_BIT);
    if(t1 != 0) {
        t2 = 0;
        t4 = t5 = t6 = t7 = 0;
        t5 = (((fs_mp_digit)1) << t1) - 1;
        t4 = DIGIT_BIT - t1;
        t3 = a3->dp;
        t6 = 0;
        for(t2 = 0; t2 < a3->used; t2++) {
            t7 = (*t3 >> t4) & t5;
            *t3 = ((*t3 << t1) | t6) & ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1));
            ++t3;
            t6 = t7;
        }
        if(t6 != 0) {
            a3->dp[(a3->used)++] = t6;
        }
    }
    fs_mp_clamp(a3);
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_read_unsigned_bin(fs_mp_int* a1, const u_int8_t* a2, int a3) {
    fs_mp_error = 0;

    if(a1->alloc < 2) {
        fs_mp_grow(a1, 2);
        if(fs_mp_error) {
            goto done;
        }
    }
    fs_mp_zero(a1);
    while(a3-- > 0) {
        fs_mp_mul_2d(a1, 8, a1);
        if(fs_mp_error) {
            goto done;
        }
        a1->dp[0] |= *a2++;
        a1->used += 1;
    }
    fs_mp_clamp(a1);
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_s_sub(fs_mp_int* a1, fs_mp_int* a2, fs_mp_int* a3) {
    int t1 = 0;
    int t2 = 0;
    int t3 = 0;
    fs_mp_digit t4 = 0;
    fs_mp_digit* t5 = NULL;
    fs_mp_digit* t6 = NULL;
    fs_mp_digit* t7 = NULL;
    int t8 = 0;

    fs_mp_error = 0;

    t3 = a2->used;
    t2 = a1->used;
    if(a3->alloc < t2) {
        fs_mp_grow(a3, t2);
        if(fs_mp_error) {
            goto done;
        }
    }
    t1 = a3->used;
    a3->used = t2;
    t5 = a1->dp;
    t6 = a2->dp;
    t7 = a3->dp;
    t4 = 0;
    for(t8 = 0; t8 < t3; t8++) {
        *t7 = *t5++ - *t6++ - t4;
        t4 = *t7 >> ((fs_mp_digit)(8 * sizeof (fs_mp_digit) - 1));
        *t7++ &= ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1));
    }
    for(; t8 < t2; t8++) {
        *t7 = *t5++ - t4;
        t4 = *t7 >> ((fs_mp_digit)(8 * sizeof (fs_mp_digit) - 1));
        *t7++ &= ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1));
    }
    for(t8 = a3->used; t8 < t1; t8++) {
        *t7++ = 0;
    }
    fs_mp_clamp(a3);
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_s_add(fs_mp_int* a1, fs_mp_int* a2, fs_mp_int* a3) {
    fs_mp_int* t1 = NULL;
    int t2 = 0;
    int t3 = 0;
    int t4 = 0;
    fs_mp_digit t5 = 0;
    fs_mp_digit* t6 = NULL;
    fs_mp_digit* t7 = NULL;
    fs_mp_digit* t8 = NULL;
    int t9 = 0;

    fs_mp_error = 0;

    if(a1->used > a2->used) {
        t3 = a2->used;
        t4 = a1->used;
        t1 = a1;
    } else {
        t3 = a1->used;
        t4 = a2->used;
        t1 = a2;
    }
    if(a3->alloc < t4 + 1) {
        fs_mp_grow(a3, t4 + 1);
        if(fs_mp_error) {
            goto done;
        }
    }
    t2 = a3->used;
    a3->used = t4 + 1;
    t6 = a1->dp;
    t7 = a2->dp;
    t8 = a3->dp;
    t5 = 0;
    for(t9 = 0; t9 < t3; t9++) {
        *t8 = *t6++ + *t7++ + t5;
        t5 = *t8 >> ((fs_mp_digit)DIGIT_BIT);
        *t8++ &= ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1));
    }
    if(t3 != t4) {
        for(; t9 < t4; t9++) {
            *t8 = t1->dp[t9] + t5;
            t5 = *t8 >> ((fs_mp_digit)DIGIT_BIT);
            *t8++ &= ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1));
        }
    }
    *t8++ = t5;
    for(t9 = a3->used; t9 < t2; t9++) {
        *t8++ = 0;
    }
    fs_mp_clamp(a3);
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_set(fs_mp_int* a1, fs_mp_digit a2) {
    fs_mp_error = 0;

    fs_mp_zero(a1);
    a1->dp[0] = a2 & ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1));
    a1->used  = (a1->dp[0] != 0) ? 1 : 0;
}

__FS_FUNCTION_MAYBE_INLINE int fs_mp_cmp_mag(fs_mp_int* a1, fs_mp_int* a2) {
	int r = 0;
    int t1 = 0;
    fs_mp_digit* t2 = NULL;
    fs_mp_digit* t3 = NULL;

    fs_mp_error = 0;

    if(a1->used > a2->used) {
        r = 1;
		goto done;
    }
    if(a1->used < a2->used) {
        r = -1;
		goto done;
    }
    t2 = a1->dp + (a1->used - 1);
    t3 = a2->dp + (a1->used - 1);
    for(t1 = 0; t1 < a1->used; ++t1, --t2, --t3) {
        if(*t2 > *t3) {
            r = 1;
			goto done;
        }
        if(*t2 < *t3) {
            r = -1;
			goto done;
        }
    }
done:
	return r;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_sub(fs_mp_int* a1, fs_mp_int* a2, fs_mp_int* a3) {
    int t1 = 0;
    int t2 = 0;

    fs_mp_error = 0;

    t1 = a1->sign;
    t2 = a2->sign;
    if(t1 != t2) {
        a3->sign = t1;
        fs_mp_s_add(a1, a2, a3);
    } else {
        if(fs_mp_cmp_mag(a1, a2) != -1) {
            a3->sign = t1;
            fs_mp_s_sub(a1, a2, a3);
        } else {
            a3->sign = (t1 == 0) ? 1 : 0;
            fs_mp_s_sub(a2, a1, a3);
        }
    }
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_add(fs_mp_int* a1, fs_mp_int* a2, fs_mp_int* a3) {
    int t1 = 0;
    int t2 = 0;

    fs_mp_error = 0;

    t1 = a1->sign;
    t2 = a2->sign;
    if(t1 == t2) {
        a3->sign = t1;
        fs_mp_s_add(a1, a2, a3);
    } else {
        if(fs_mp_cmp_mag(a1, a2) == -1) {
            a3->sign = t2;
            fs_mp_s_sub(a2, a1, a3);
        } else {
            a3->sign = t1;
            fs_mp_s_sub(a1, a2, a3);
        }
    }
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_mod_2d(fs_mp_int* a1, int a2, fs_mp_int* a3) {
    int t1 = 0;

    fs_mp_error = 0;

    if(a2 <= 0) {
        fs_mp_zero(a3);
        goto done;
    }
    if(a2 >= (int) (a1->used * DIGIT_BIT)) {
        fs_mp_copy(a1, a3);
        goto done;
    }
    fs_mp_copy(a1, a3);
    if(fs_mp_error) {
        goto done;
    }
    for(t1 = (a2 / DIGIT_BIT) + ((a2 % DIGIT_BIT) == 0 ? 0 : 1); t1 < a3->used; t1++) {
        a3->dp[t1] = 0;
    }
    a3->dp[a2 / DIGIT_BIT] &= (fs_mp_digit) ((((fs_mp_digit) 1) << (((fs_mp_digit) a2) % DIGIT_BIT)) - ((fs_mp_digit) 1));
    fs_mp_clamp(a3);
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_exch(fs_mp_int* a1, fs_mp_int* a2) {
    fs_mp_int t1 = *a1;

    *a1 = *a2;
    *a2 = t1;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_init_copy(fs_mp_int* a1, fs_mp_int* a2) {
    fs_mp_error = 0;

    fs_mp_init(a1);
    if(!a1->dp) {
        fs_mp_error = 1;
        goto done;
    }
    fs_mp_copy(a2, a1);
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_div_2d(fs_mp_int* a1, int a2, fs_mp_int* a3, fs_mp_int* a4) {
    fs_mp_digit t1 = 0;
    fs_mp_digit t2 = 0;
    fs_mp_digit t3 = 0;
    fs_mp_digit* t4 = NULL;
    fs_mp_int t5;
    int t6 = 0;
    fs_mp_digit t7 = 0;
    fs_mp_digit t8 = 0;

    fs_mp_error = 0;

    if(a2 <= 0) {
        fs_mp_copy(a1, a3);
        if(a4 != NULL) {
            fs_mp_zero(a4);
        }
        goto done;
    }
    fs_mp_init(&t5);
    if(!t5.dp) {
        fs_mp_error = 1;
        goto done;
    }
    if(a4 != NULL) {
        fs_mp_mod_2d(a1, a2, &t5);
        if(fs_mp_error) {
            fs_mp_clear(&t5);
            fs_mp_error = 1;
            goto done;
        }
    }
    fs_mp_copy(a1, a3);
    if(fs_mp_error) {
        fs_mp_clear(&t5);
        fs_mp_error = 1;
        goto done;
    }
    if(a2 >= (int)DIGIT_BIT) {
        fs_mp_rshd(a3, a2 / DIGIT_BIT);
    }
    t1 = (fs_mp_digit) (a2 % DIGIT_BIT);
    if(t1 != 0) {
        t7 = (((fs_mp_digit)1) << t1) - 1;
        t8 = DIGIT_BIT - t1;
        t4 = a3->dp + (a3->used - 1);
        t2 = 0;
        for(t6 = a3->used - 1; t6 >= 0; t6--) {
            t3 = *t4 & t7;
            *t4 = (*t4 >> t1) | (t2 << t8);
            --t4;
            t2 = t3;
        }
    }
    fs_mp_clamp(a3);
    if(a4 != NULL) {
        fs_mp_exch(&t5, a4);
    }
    fs_mp_clear(&t5);
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_to_unsigned_bin(fs_mp_int* a1, unsigned char* a2) {
    int t1 = 0;
    int t2 = 0;
    unsigned char t3 = 0;
    int t4 = 0;
    fs_mp_int t5;

    fs_mp_error = 0;

    fs_mp_init_copy(&t5, a1);
    if(fs_mp_error) {
        goto done;
    }
    t4 = 0;
    while((((&t5)->used == 0) ? 1 : 0) == 0) {
        a2[t4++] = (unsigned char) (t5.dp[0] & 255);
        fs_mp_div_2d(&t5, 8, &t5, NULL);
        if(fs_mp_error) {
            fs_mp_clear(&t5);
            goto done;
        }
    }
    t1 = 0;
    t2 = t4 - 1;
    while(t1 < t2) {
        t3 = a2[t1];
        a2[t1] = a2[t2];
        a2[t2] = t3;
        ++t1;
        --t2;
    }

    fs_mp_clear(&t5);
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE int fs_mp_cmp(fs_mp_int* a1, fs_mp_int* a2) {
    int r = 0;

    fs_mp_error = 0;

    if(a1->sign != a2->sign) {
        if(a1->sign == 1) {
            r = -1;
            goto done;
        } else {
            r = 1;
            goto done;
        }
    }
    if(a1->sign == 1) {
        r = fs_mp_cmp_mag(a2, a1);
        goto done;
    } else {
        r = fs_mp_cmp_mag(a1, a2);
        goto done;
    }
done:
    return r;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_div(fs_mp_int* a1, fs_mp_int* a2, fs_mp_int* a3, fs_mp_int* a4) {
    fs_mp_int t1;
    fs_mp_int t2;
    fs_mp_int t3;
    fs_mp_int t4;
    int t5 = 0;
    int t6 = 0;

    fs_mp_error = 0;
    if((((a2)->used == 0) ? 1 : 0) == 1) {
        fs_mp_error = 1;
        goto done;
    }

    if(fs_mp_cmp_mag(a1, a2) == -1) {
        if(a4 != NULL) {
            fs_mp_copy(a1, a4);
        }
        if(a3 != NULL) {
            fs_mp_zero(a3);
        }
        goto done;
    }
    fs_mp_init(&t1);
    fs_mp_init(&t2);
    fs_mp_init(&t3);
    fs_mp_init(&t4);
    if(!t1.dp || !t2.dp || !t3.dp || !t4.dp) {
        fs_mp_error = 1;
        goto done;
    }
    fs_mp_set(&t3, 1);
    t5 = fs_mp_count_bits(a1);
    t5 -= fs_mp_count_bits(a2);
    fs_mp_abs(a1, &t1);
    if(fs_mp_error) {
        goto LBL_ERR;
    }
    fs_mp_abs(a2, &t2);
    if(fs_mp_error) {
        goto LBL_ERR;
    }
    fs_mp_mul_2d(&t2, t5, &t2);
    if(fs_mp_error) {
        goto LBL_ERR;
    }
    fs_mp_mul_2d(&t3, t5, &t3);
    if(fs_mp_error) {
        goto LBL_ERR;
    }
    while(t5-- >= 0) {
        if(fs_mp_cmp(&t2, &t1) != 1) {
            fs_mp_sub(&t1, &t2, &t1);
            if(fs_mp_error) {
                goto LBL_ERR;
            }
            fs_mp_add(&t4, &t3, &t4);
            if(fs_mp_error) {
                goto LBL_ERR;
            }
        }
        fs_mp_div_2d(&t2, 1, &t2, NULL);
        if(fs_mp_error) {
            goto LBL_ERR;
        }
        fs_mp_div_2d(&t3, 1, &t3, NULL);
        if(fs_mp_error) {
            goto LBL_ERR;
        }
    }
    t5  = a1->sign;
    t6 = (a1->sign == a2->sign ? 0 : 1);
    if(a3 != NULL) {
        fs_mp_exch(a3, &t4);
        a3->sign  = ((((a3)->used == 0) ? 1 : 0) == 1) ? 0 : t6;
    }
    if(a4 != NULL) {
        fs_mp_exch(a4, &t1);
        a4->sign = ((((a4)->used == 0) ? 1 : 0) == 1) ? 0 : t5;
    }
    LBL_ERR:
        fs_mp_clear(&t1);
        fs_mp_clear(&t2);
        fs_mp_clear(&t3);
        fs_mp_clear(&t4);
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE int fs_mp_cmp_d(fs_mp_int* a1, fs_mp_digit a2) {
    int r = 0;

    fs_mp_error = 0;

    if(a1->sign == 1) {
        r = -1;
        goto done;
    }
    if(a1->used > 1) {
        r = 1;
        goto done;
    }
    if(a1->dp[0] > a2) {
        r = 1;
        goto done;
    } else if(a1->dp[0] < a2) {
        r = -1;
        goto done;
    } else {
        r = 0;
        goto done;
    }
done:
    return r;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_mod(fs_mp_int* a1, fs_mp_int* a2, fs_mp_int* a3) {
    fs_mp_int t1;

    fs_mp_error = 0;

    fs_mp_init(&t1);
    if(!t1.dp) {
        fs_mp_error = 1;
        goto done;
    }
    fs_mp_div(a1, a2, NULL, &t1);
    if(fs_mp_error) {
        fs_mp_clear(&t1);
        goto done;
    }
    if(t1.sign != a2->sign) {
        fs_mp_add(a2, &t1, a3);
    } else {
        fs_mp_exch(&t1, a3);
    }
    fs_mp_clear(&t1);
done:
    ;
}


__FS_FUNCTION_MAYBE_INLINE void fs_mp_div_2(fs_mp_int* a1, fs_mp_int* a2) {
    int t1 = 0;
    int t2 = 0;
    fs_mp_digit t3 = 0;
    fs_mp_digit t4 = 0;
    fs_mp_digit* t5 = NULL;
    fs_mp_digit* t6 = NULL;

    fs_mp_error = 0;

    if(a2->alloc < a1->used) {
        fs_mp_grow(a2, a1->used);
        if(fs_mp_error) {
            goto done;
        }
    }
    t2 = a2->used;
    a2->used = a1->used;
    t5 = a1->dp + a2->used - 1;
    t6 = a2->dp + a2->used - 1;
    t3 = 0;
    for(t1 = a2->used - 1; t1 >= 0; t1--) {
        t4 = *t5 & 1;
        *t6-- = (*t5-- >> 1) | (t3 << (DIGIT_BIT - 1));
        t3 = t4;
    }
    t6 = a2->dp + a2->used;
    for(t1 = a2->used; t1 < t2; t1++) {
        *t6++ = 0;
    }
    a2->sign = a1->sign;
    fs_mp_clamp(a2);
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_invmod(fs_mp_int* a1, fs_mp_int* a2, fs_mp_int* a3) {
    fs_mp_int t1;
    fs_mp_int t2;
    fs_mp_int t3;
    fs_mp_int t4;
    fs_mp_int t5;
    fs_mp_int t6;
    fs_mp_int t7;
    fs_mp_int t8;
    int t9 = 0;

    fs_mp_error = 0;

    if(a2->sign == 1 || (((a2)->used == 0) ? 1 : 0) == 1) {
        fs_mp_error = -3;
        goto LBL_ERR;
    }
    fs_mp_init(&t1);
    fs_mp_init(&t2);
    fs_mp_init(&t3);
    fs_mp_init(&t4);
    fs_mp_init(&t5);
    fs_mp_init(&t6);
    fs_mp_init(&t7);
    fs_mp_init(&t8);
    if(!t1.dp
       || !t2.dp
       || !t3.dp
       || !t4.dp
       || !t5.dp
       || !t6.dp
       || !t7.dp
       || !t8.dp) {
        fs_mp_error = 1;
        goto LBL_ERR;
    }
    fs_mp_mod(a1, a2, &t1);
    if(fs_mp_error) {
        goto LBL_ERR;
    }
    fs_mp_copy(a2, &t2);
    if(fs_mp_error) {
        goto LBL_ERR;
    }
    if((((&t1)->used > 0 && (((&t1)->dp[0] & 1) == 0)) ? 1 : 0) == 1 && (((&t2)->used > 0 && (((&t2)->dp[0] & 1) == 0)) ? 1 : 0) == 1) {
        fs_mp_error = -3;
        goto LBL_ERR;
    }
    fs_mp_copy(&t1, &t3);
    if(fs_mp_error) {
        goto LBL_ERR;
    }
    fs_mp_copy(&t2, &t4);
    if(fs_mp_error) {
        goto LBL_ERR;
    }
    fs_mp_set(&t5, 1);
    fs_mp_set(&t8, 1);
    top:
    while((((&t3)->used > 0 && (((&t3)->dp[0] & 1) == 0)) ? 1 : 0) == 1) {
        fs_mp_div_2(&t3, &t3);
        if(fs_mp_error) {
            goto LBL_ERR;
        }
        if((((&t5)->used > 0 && (((&t5)->dp[0] & 1) == 1)) ? 1 : 0) == 1 || (((&t6)->used > 0 && (((&t6)->dp[0] & 1) == 1)) ? 1 : 0) == 1) {
            fs_mp_add(&t5, &t2, &t5);
            if(fs_mp_error) {
                goto LBL_ERR;
            }
            fs_mp_sub(&t6, &t1, &t6);
            if(fs_mp_error) {
                goto LBL_ERR;
            }
        }
        fs_mp_div_2(&t5, &t5);
        if(fs_mp_error) {
            goto LBL_ERR;
        }
        fs_mp_div_2(&t6, &t6);
        if(fs_mp_error) {
            goto LBL_ERR;
        }
    }
    while((((&t4)->used > 0 && (((&t4)->dp[0] & 1) == 0)) ? 1 : 0) == 1) {
        fs_mp_div_2(&t4, &t4);
        if(fs_mp_error) {
            goto LBL_ERR;
        }
        if((((&t7)->used > 0 && (((&t7)->dp[0] & 1) == 1)) ? 1 : 0) == 1 || (((&t8)->used > 0 && (((&t8)->dp[0] & 1) == 1)) ? 1 : 0) == 1) {
            fs_mp_add(&t7, &t2, &t7);
            if(fs_mp_error) {
                goto LBL_ERR;
            }
            fs_mp_sub(&t8, &t1, &t8);
            if(fs_mp_error) {
                goto LBL_ERR;
            }
        }
        fs_mp_div_2(&t7, &t7);
        if(fs_mp_error) {
            goto LBL_ERR;
        }
        fs_mp_div_2(&t8, &t8);
        if(fs_mp_error) {
            goto LBL_ERR;
        }
    }
    if(fs_mp_cmp(&t3, &t4) != -1) {
        fs_mp_sub(&t3, &t4, &t3);
        if(fs_mp_error) {
            goto LBL_ERR;
        }
        fs_mp_sub(&t5, &t7, &t5);
        if(fs_mp_error) {
            goto LBL_ERR;
        }
        fs_mp_sub(&t6, &t8, &t6);
        if(fs_mp_error) {
            goto LBL_ERR;
        }
    } else {
        fs_mp_sub(&t4, &t3, &t4);
        if(fs_mp_error) {
            goto LBL_ERR;
        }
        fs_mp_sub(&t7, &t5, &t7);
        if(fs_mp_error) {
            goto LBL_ERR;
        }
        fs_mp_sub(&t8, &t6, &t8);
        if(fs_mp_error) {
            goto LBL_ERR;
        }
    }
    if((((&t3)->used == 0) ? 1 : 0) == 0)
        goto top;
    t9 = fs_mp_cmp_d(&t4, 1);
    if(t9 != 0) {
        fs_mp_error = -3;
        goto LBL_ERR;
    }

    t9 = fs_mp_cmp_d(&t7, 0);
    while(t9 == -1) {
        fs_mp_add(&t7, a2, &t7);
        if(fs_mp_error) {
            goto LBL_ERR;
        }
        fs_mp_cmp_d(&t7, 0);
    }
    while(fs_mp_cmp_mag(&t7, a2) != -1) {
        fs_mp_sub(&t7, a2, &t7);
        if(fs_mp_error) {
            goto LBL_ERR;
        }
        fs_mp_cmp_mag(&t7, a2); // NB: ERROR - dead code?
    }
    fs_mp_exch(&t7, a3);
    fs_mp_error = 0;
    LBL_ERR:
    fs_mp_clear(&t1);
    fs_mp_clear(&t2);
    fs_mp_clear(&t3);
    fs_mp_clear(&t4);
    fs_mp_clear(&t5);
    fs_mp_clear(&t6);
    fs_mp_clear(&t7);
    fs_mp_clear(&t8);
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_reduce_setup(fs_mp_int* a1, fs_mp_int* a2) {
    fs_mp_error = 0;

    fs_mp_2expt(a1, a2->used * 2 * DIGIT_BIT);
    if(fs_mp_error) {
        goto done;
    }
    fs_mp_div(a1, a2, a1, NULL);
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_fast_s_mul_digs(fs_mp_int* a1, fs_mp_int* a2, fs_mp_int* a3, int a4) {
    int t1 = 0;
    int t2 = 0;
    int t3 = 0;
    int t4 = 0;
    fs_mp_digit t5[(1 << (sizeof(fs_mp_word) * 8 - 2 * DIGIT_BIT + 1))];
    fs_mp_word t6 = 0;
    int t7 = 0;
    int t8 = 0;
    int t9 = 0;
    fs_mp_digit* t10 = NULL;
    fs_mp_digit* t11 = NULL;
    fs_mp_digit* t12 = NULL;

    fs_mp_error = 0;

    if(a3->alloc < a4) {
        fs_mp_grow(a3, a4);
        if(fs_mp_error) {
            goto done;
        }
    }
    t2 = a4 < (a1->used + a2->used) ? a4 : (a1->used + a2->used);
    t6 = 0;
    for(t3 = 0; t3 < t2; t3++) {
        t8 = (a2->used-1) < t3 ? (a2->used-1) : t3;
        t7 = t3 - t8;
        t10 = a1->dp + t7;
        t11 = a2->dp + t8;
        t9 = (a1->used - t7) < (t8+1) ? (a1->used - t7) : (t8+1);
        for(t4 = 0; t4 < t9; ++t4) {
            t6 += ((fs_mp_word)*t10++)*((fs_mp_word)*t11--);
        }
        t5[t3] = ((fs_mp_digit)t6) & ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1));
        t6 = t6 >> ((fs_mp_word)DIGIT_BIT);
    }
    t1  = a3->used;
    a3->used = t2;
    t12 = a3->dp;
    for(t3 = 0; t3 < t2+1; t3++) {
        *t12++ = t5[t3];
    }
    for(; t3 < t1; t3++) {
        *t12++ = 0;
    }
    fs_mp_clamp(a3);
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_init_size(fs_mp_int* a1, int a2) {
    int t1 = 0;

    fs_mp_error = 0;

    a2 += (FS_MP_PREC * 2) - (a2 % FS_MP_PREC);
    a1->dp = (fs_mp_digit*)fs_malloc(sizeof (fs_mp_digit) * a2);
    if(a1->dp == NULL) {
        fs_mp_error = 1;
        goto done;
    }
    a1->used  = 0;
    a1->alloc = a2;
    a1->sign  = 0;
    for(t1 = 0; t1 < a2; t1++) {
        a1->dp[t1] = 0;
    }
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_s_mul_digs(fs_mp_int* a1, fs_mp_int* a2, fs_mp_int* a3, int a4) {
    fs_mp_int t1;
    int t2 = 0;
    int t3 = 0;
    int t4 = 0;
    int t5 = 0;
    fs_mp_digit t6 = 0;
    fs_mp_word t7 = 0;
    fs_mp_digit t8 = 0;
    fs_mp_digit* t9 = NULL;
    fs_mp_digit* t10 = NULL;

    fs_mp_error = 0;

    if(((a4) < (1 << (sizeof(fs_mp_word) * 8 - 2 * DIGIT_BIT + 1))) &&
       (a1->used < a2->used ? a1->used : a2->used) <
       (1 << ((8 * sizeof (fs_mp_word)) - (2 * DIGIT_BIT)))) {
        fs_mp_fast_s_mul_digs(a1, a2, a3, a4);
        goto done;
    }
    fs_mp_init_size(&t1, a4);
    if(fs_mp_error) {
        goto done;
    }
    t1.used = a4;
    t2 = a1->used;
    for(t4 = 0; t4 < t2; t4++) {
        t6 = 0;
        t3 = a2->used < (a4 - t4) ? a2->used : (a4 - t4);
        t8 = a1->dp[t4];
        t9 = t1.dp + t4;
        t10 = a2->dp;
        for(t5 = 0; t5 < t3; t5++) {
            t7       = ((fs_mp_word)*t9) +
                              ((fs_mp_word)t8) * ((fs_mp_word)*t10++) +
                              ((fs_mp_word) t6);
            *t9++ = (fs_mp_digit) (t7 & ((fs_mp_word) ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1))));
            t6       = (fs_mp_digit) (t7 >> ((fs_mp_word) DIGIT_BIT));
        }
        if(t4 + t5 < a4) {
            *t9 = t6;
        }
    }
    fs_mp_clamp(&t1);
    fs_mp_exch(&t1, a3);
    fs_mp_clear(&t1);
done:
    ;
}



__FS_FUNCTION_MAYBE_INLINE void fs_mp_mul(fs_mp_int* a1, fs_mp_int* a2, fs_mp_int* a3) {
    int t1 = 0;

    fs_mp_error = 0;

    t1 = (a1->sign == a2->sign) ? 0 : 1;
    fs_mp_s_mul_digs(a1, a2, a3, a1->used + a2->used + 1);
    a3->sign = (a3->used > 0) ? t1 : 0;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_s_mul_high_digs(fs_mp_int* a1, fs_mp_int* a2, fs_mp_int* a3, int a4) {
    fs_mp_int t1;
    int t2 = 0;
    int t3 = 0;
    int t4 = 0;
    int t5 = 0;
    fs_mp_digit t6 = 0;
    fs_mp_word t7 = 0;
    fs_mp_digit t10 = 0;
    fs_mp_digit* t8 = NULL;
    fs_mp_digit* t9 = NULL;

    fs_mp_error = 0;

    fs_mp_init_size(&t1, a1->used + a2->used + 1);
    if(fs_mp_error) {
        goto done;
    }
    t1.used = a1->used + a2->used + 1;
    t2 = a1->used;
    t3 = a2->used;
    for(t4 = 0; t4 < t2; t4++) {
        t6 = 0;
        t10 = a1->dp[t4];
        t8 = &(t1.dp[a4]);
        t9 = a2->dp + (a4 - t4);
        for(t5 = a4 - t4; t5 < t3; t5++) {
            t7 = ((fs_mp_word)*t8) +
                           ((fs_mp_word)t10) * ((fs_mp_word)*t9++) +
                           ((fs_mp_word) t6);
            *t8++ = (fs_mp_digit) (t7 & ((fs_mp_word) ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1))));
            t6 = (fs_mp_digit) (t7 >> ((fs_mp_word) DIGIT_BIT));
        }
        *t8 = t6;
    }
    fs_mp_clamp(&t1);
    fs_mp_exch(&t1, a3);
    fs_mp_clear(&t1);
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_reduce(fs_mp_int* a1, fs_mp_int* a2, fs_mp_int* a3) {
    fs_mp_int t1;
    int t2 = a2->used;

    fs_mp_error = 0;

    fs_mp_init_copy(&t1, a1);
    if(fs_mp_error) {
        goto done;
    }
    fs_mp_rshd(&t1, t2 -1);
    if(((unsigned long) t2) > (((fs_mp_digit)1) << (DIGIT_BIT - 1))) {
        fs_mp_mul(&t1, a3, &t1);
        if(fs_mp_error) {
            goto CLEANUP;
        }
    } else {
        fs_mp_s_mul_high_digs(&t1, a3, &t1, t2);
        if(fs_mp_error) {
            goto CLEANUP;
        }
    }
    fs_mp_rshd(&t1, t2 + 1);
    fs_mp_mod_2d(a1, DIGIT_BIT * (t2 + 1), a1);
    if(fs_mp_error) {
        goto CLEANUP;
    }
    fs_mp_s_mul_digs(&t1, a2, &t1, t2 + 1);
    if(fs_mp_error) {
        goto CLEANUP;
    }
    fs_mp_sub(a1, &t1, a1);
    if(fs_mp_error) {
        goto CLEANUP;
    }
    if(fs_mp_cmp_d(a1, 0) == -1) {
        fs_mp_set(&t1, 1);
        fs_mp_lshd(&t1, t2 + 1);
        if(fs_mp_error) {
            goto CLEANUP;
        }
        fs_mp_add(a1, &t1, a1);
        if(fs_mp_error) {
            goto CLEANUP;
        }
    }
    while(fs_mp_cmp(a1, a2) != -1) {
        fs_mp_s_sub(a1, a2, a1);
        if(fs_mp_error) {
            goto CLEANUP;
        }
        fs_mp_cmp(a1, a2);
    }
CLEANUP:
    fs_mp_clear(&t1);
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_reduce_2k_setup(fs_mp_int* a1, fs_mp_digit* a2) {
    fs_mp_int t1;

    fs_mp_error = 0;

    fs_mp_init(&t1);
    if(!t1.dp) {
        fs_mp_error = 1;
        goto done;
    }
    fs_mp_2expt(&t1, fs_mp_count_bits(a1));
    if(fs_mp_error) {
        goto done;
    }
    fs_mp_s_sub(&t1, a1, &t1);
    if(fs_mp_error) {
        goto done;
    }
    *a2 = t1.dp[0];
done:
    fs_mp_clear(&t1);
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_reduce_2k_setup_l(fs_mp_int* a1, fs_mp_int* a2) {
    fs_mp_int t1;

    fs_mp_error = 0;

    fs_mp_init(&t1);
    if(!t1.dp) {
        fs_mp_error = 1;
        goto done;
    }
    fs_mp_2expt(&t1, fs_mp_count_bits(a1));
    if(fs_mp_error) {
        goto LBL_ERR;
    }

    fs_mp_s_sub(&t1, a1, a2);
    if(fs_mp_error) {
        goto LBL_ERR;
    }
    LBL_ERR:
    fs_mp_clear(&t1);
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_sqr(fs_mp_int* a1, fs_mp_int* a2) {
    fs_mp_int t1;
    int t2 = 0;
    int t3 = 0;
    int t4 = a1->used;
    fs_mp_word t5 = 0;
    fs_mp_digit t6 = 0;
    fs_mp_digit t7 = 0;
    fs_mp_digit* t8 = NULL;

    fs_mp_error = 0;

    fs_mp_init_size(&t1, 2*t4 + 1);
    if(fs_mp_error) {
        a2->sign = 0;
        goto done;
    }
    t1.used = 2*t4 + 1;
    for(t2 = 0; t2 < t4; t2++) {
        t5 = ((fs_mp_word) t1.dp[2*t2]) +
                 ((fs_mp_word)a1->dp[t2])*((fs_mp_word)a1->dp[t2]);
        t1.dp[t2+t2] = (fs_mp_digit) (t5 & ((fs_mp_word) ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1))));
        t6           = (fs_mp_digit)(t5 >> ((fs_mp_word) DIGIT_BIT));
        t7        = a1->dp[t2];
        t8        = t1.dp + (2*t2 + 1);
        for(t3 = t2 + 1; t3 < t4; t3++) {
            t5       = ((fs_mp_word)t7) * ((fs_mp_word)a1->dp[t3]);
            t5       = ((fs_mp_word) *t8) + t5 + t5 + ((fs_mp_word) t6);
            *t8++ = (fs_mp_digit) (t5 & ((fs_mp_word) ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1))));
            t6       = (fs_mp_digit)(t5 >> ((fs_mp_word) DIGIT_BIT));
        }
        while(t6 != ((fs_mp_digit) 0)) {
            t5       = ((fs_mp_word) *t8) + ((fs_mp_word) t6);
            *t8++ = (fs_mp_digit) (t5 & ((fs_mp_word) ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1))));
            t6       = (fs_mp_digit)(t5 >> ((fs_mp_word) DIGIT_BIT));
        }
    }
    fs_mp_clamp(&t1);
    fs_mp_exch(&t1, a2);
    fs_mp_clear(&t1);
    a2->sign = 0;
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_reduce_2k_l(fs_mp_int* a1, fs_mp_int* a2, fs_mp_int* a3) {
    fs_mp_int t1;
    int t2 = 0;

    fs_mp_error = 0;

    fs_mp_init(&t1);
    if(!t1.dp) {
        fs_mp_error = 1;
        goto done;
    }
    t2 = fs_mp_count_bits(a2);
top:
    fs_mp_div_2d(a1, t2, &t1, a1);
    if(fs_mp_error) {
        goto LBL_ERR;
    }
    fs_mp_mul(&t1, a3, &t1);
    if(fs_mp_error) {
        goto LBL_ERR;
    }
    fs_mp_s_add(a1, &t1, a1);
    if(fs_mp_error) {
        goto LBL_ERR;
    }
    if(fs_mp_cmp_mag(a1, a2) != -1) {
        fs_mp_s_sub(a1, a2, a1);
        goto top;
    }
    LBL_ERR:
    fs_mp_clear(&t1);
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_s_exptmod(fs_mp_int* a1, fs_mp_int* a2, fs_mp_int* a3, fs_mp_int* a4, int a5) {

    fs_mp_int t1[16]; // 1<< t12
    fs_mp_int t2;
    fs_mp_int t3;
    fs_mp_digit t4 = 0;
    int t5 = 0;
    int t6 = 0;
    int t7 = 0;
    int t8 = 0;
    int t9 = 0;
    int t10 = 0;
    int t11 = 0;
    int t12 = 0;
    int t13 = 0;
    int t14 = fs_mp_count_bits(a2);

    memset(&t1, 0, sizeof t1);
    fs_mp_error = 0;

    if(t14 <= 7) {
        t12 = 2;
    } else if(t14 <= 36) {
        t12 = 3;
    } else if(t14 <= 140) {
        t12 = 4;
    } else if(t14 <= 450) {
        t12 = 5;
    } else if(t14 <= 1303) {
        t12 = 6;
    } else if(t14 <= 3529) {
        t12 = 7;
    } else {
        t12 = 8;
    }
    // Low mem hack.  If you increase this, increase t2 also.
    if(t12 > 4) {
        t12 = 4;
    }
    fs_mp_init(&t1[1]);
    if(!t1[1].dp) {
        fs_mp_error = 1;
        goto done;
    }
    for(t10 = 1<<(t12-1); t10 < (1 << t12); t10++) {
        fs_mp_init(&t1[t10]);
        if(!t1[t10].dp) {
            fs_mp_error = 1;
            for(t11 = 1<<(t12-1); t11 < t10; t11++) {
                fs_mp_clear(&t1[t11]);
            }
            fs_mp_clear(&t1[1]);
            goto done;
        }
    }
    fs_mp_init(&t3);
    if(!t3.dp) {
        fs_mp_error = 1;
        goto LBL_M;
    }
    if(a5 == 0) {
        fs_mp_reduce_setup(&t3, a3);
        if(fs_mp_error) {
            goto LBL_MU;
        }
        t13 = 1;
    } else {
        fs_mp_reduce_2k_setup_l(a3, &t3);
        if(fs_mp_error) {
            goto LBL_MU;
        }
        t13 = 2;
    }
    fs_mp_mod(a1, a3, &t1[1]);
    if(fs_mp_error) {
        goto LBL_MU;
    }
    fs_mp_copy(&t1[1], &t1[1 << (t12 - 1)]);
    if(fs_mp_error) {
        goto LBL_MU;
    }
    for(t10 = 0; t10 < (t12 - 1); t10++) {
        fs_mp_sqr(&t1[1 << (t12 - 1)], &t1[1 << (t12 - 1)]);
        if(fs_mp_error) {
            goto LBL_MU;
        }
        if(t13 == 1) {
            fs_mp_reduce(&t1[1 << (t12 - 1)], a3, &t3);
            if(fs_mp_error) {
                goto LBL_MU;
            }
        } else if(t13 == 2) {
            fs_mp_reduce_2k_l(&t1[1 << (t12 - 1)], a3, &t3);
            if(fs_mp_error) {
                goto LBL_MU;
            }
        }
    }
    for(t10 = (1 << (t12 - 1)) + 1; t10 < (1 << t12); t10++) {
        fs_mp_mul(&t1[t10 - 1], &t1[1], &t1[t10]);
        if(fs_mp_error) {
            goto LBL_MU;
        }
        if(t13 == 1) {
            fs_mp_reduce(&t1[t10], a3, &t3);
            if(fs_mp_error) {
                goto LBL_MU;
            }
        } else if(t13 == 2) {
            fs_mp_reduce_2k_l(&t1[t10], a3, &t3);
            if(fs_mp_error) {
                goto LBL_MU;
            }
        }
    }
    fs_mp_init(&t2);
    if(!t2.dp) {
        fs_mp_error = 1;
        goto LBL_MU;
    }
    fs_mp_set(&t2, 1);
    t8 = 0;
    t7 = 1;
    t4 = 0;
    t9 = a2->used - 1;
    t6 = 0;
    t5 = 0;
    for(;;) {
        if(--t7 == 0) {
            if(t9 == -1) {
                break;
            }
            t4    = a2->dp[t9--];
            t7 = (int) DIGIT_BIT;
        }
        t11     = (t4 >> (fs_mp_digit)(DIGIT_BIT - 1)) & 1;
        t4 <<= (fs_mp_digit)1;
        if(t8 == 0 && t11 == 0) {
            continue;
        }
        if(t8 == 1 && t11 == 0) {
            fs_mp_sqr(&t2, &t2);
            if(fs_mp_error) {
                goto LBL_RES;
            }
            if(t13 == 1) {
                fs_mp_reduce(&t2, a3, &t3);
                if(fs_mp_error) {
                    goto LBL_RES;
                }
            } else if(t13 == 2) {
                fs_mp_reduce_2k_l(&t2, a3, &t3);
                if(fs_mp_error) {
                    goto LBL_RES;
                }
            }
            continue;
        }
        t5 |= (t11 << (t12 - ++t6));
        t8    = 2;
        if(t6 == t12) {
            for(t10 = 0; t10 < t12; t10++) {
                fs_mp_sqr(&t2, &t2);
                if(fs_mp_error) {
                    goto LBL_RES;
                }
                if(t13 == 1) {
                    fs_mp_reduce(&t2, a3, &t3);
                    if(fs_mp_error) {
                        goto LBL_RES;
                    }
                } else if(t13 == 2) {
                    fs_mp_reduce_2k_l(&t3, a3, &t3);
                    if(fs_mp_error) {
                        goto LBL_RES;
                    }
                }
            }
            fs_mp_mul(&t2, &t1[t5], &t2);
            if(fs_mp_error) {
                goto LBL_RES;
            }
            if(t13 == 1) {
                fs_mp_reduce(&t2, a3, &t3);
                if(fs_mp_error) {
                    goto LBL_RES;
                }
            } else if(t13 == 2) {
                fs_mp_reduce_2k_l(&t2, a3, &t3);
                if(fs_mp_error) {
                    goto LBL_RES;
                }
            }
            t6 = 0;
            t5 = 0;
            t8 = 1;
        }
    }
    if(t8 == 2 && t6 > 0) {
        for(t10 = 0; t10 < t6; t10++) {
            fs_mp_sqr(&t2, &t2);
            if(fs_mp_error) {
                goto LBL_RES;
            }
            if(t13 == 1) {
                fs_mp_reduce(&t2, a3, &t3);
                if(fs_mp_error) {
                    goto LBL_RES;
                }
            } else if(t13 == 2) {
                fs_mp_reduce_2k_l(&t2, a3, &t3);
                if(fs_mp_error) {
                    goto LBL_RES;
                }
            }
            t5 <<= 1;
            if((t5 & (1 << t12)) != 0) {
                fs_mp_mul(&t2, &t1[1], &t2);
                if(fs_mp_error) {
                    goto LBL_RES;
                }
                fs_mp_reduce_2k_l(&t2, a3, &t3);
                if(fs_mp_error) {
                    goto LBL_RES;
                }
            }
        }
    }
    fs_mp_exch(&t2, a4);
    fs_mp_error = 0;
    LBL_RES:
    fs_mp_clear(&t2);
    LBL_MU:
    fs_mp_clear(&t3);
    LBL_M:
    fs_mp_clear(&t1[1]);
    for(t10 = 1<<(t12-1); t10 < (1 << t12); t10++) {
        fs_mp_clear(&t1[t10]);
    }
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE int fs_mp_dr_is_modulus(fs_mp_int* a1) {
    int t1 = 0;
    int r = 1;

    fs_mp_error = 0;

    if(a1->used < 2) {
        r = 0;
        goto done;
    }
    for(t1 = 1; t1 < a1->used; t1++) {
        if(a1->dp[t1] != ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1))) {
            r = 0;
            goto done;
        }
    }
done:
    return r;
}

__FS_FUNCTION_MAYBE_INLINE int fs_mp_reduce_is_2k(fs_mp_int* a1) {
    int t1 = 0;
    int t2 = 0;
    fs_mp_digit t3 = 0;
    int t4 = 0;
    int r = 0;

    fs_mp_error = 0;

    if(a1->used == 0) {
        r = 0;
        goto done;
    } else if(a1->used == 1) {
        r = 1;
        goto done;
    } else if(a1->used > 1) {
        t4 = fs_mp_count_bits(a1);
        t3 = 1;
        t2 = 1;
        for(t1 = DIGIT_BIT; t1 < t4; t1++) {
            if((a1->dp[t2] & t3) == 0) {
                r = 0;
                goto done;
            }
            t3 <<= 1;
            if(t3 > (fs_mp_digit)((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1))) {
                ++t2;
                t3 = 1;
            }
        }
    }
    r = 1;
done:
    return r;
}


__FS_FUNCTION_MAYBE_INLINE void fs_mp_montgomery_setup(fs_mp_int* a1, fs_mp_digit* a2) {
    fs_mp_digit t1 = 0;
    fs_mp_digit t2 = a1->dp[0];

    fs_mp_error = 0;

    if((t2 & 1) == 0) {
        fs_mp_error = 1;
        goto done;
    }
    t1 = (((t2 + 2) & 4) << 1) + t2;
    t1 *= 2 - t2 * t1;
    t1 *= 2 - t2 * t1;
    t1 *= 2 - t2 * t1;
    *a2 = (unsigned long)(((fs_mp_word)1 << ((fs_mp_word) DIGIT_BIT)) - t1) & ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1));
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_fast_montgomery_reduce(fs_mp_int* a1, fs_mp_int* a2, fs_mp_digit a3) {
    int t1 = 0;
    int t2 = a1->used;
    fs_mp_word t3[(1 << (sizeof(fs_mp_word) * 8 - 2 * DIGIT_BIT + 1))];
    fs_mp_digit t4 = 0;
    fs_mp_word* t5 = NULL;
    fs_mp_digit* t6 = NULL;
    int t7 = 0;
    fs_mp_digit* t8 = NULL;
    fs_mp_word* t9 = NULL;

    fs_mp_error = 0;

    if(a1->alloc < a2->used + 1) {
        fs_mp_grow(a1, a2->used + 1);
        if(fs_mp_error) {
            goto done;
        }
    }
    t5 = t3;
    t6 = a1->dp;
    for(t1 = 0; t1 < a1->used; t1++) {
        *t5++ = *t6++;
    }
    for(; t1 < a2->used * 2 + 1; t1++) {
        *t5++ = 0;
    }
    for(t1 = 0; t1 < a2->used; t1++) {
        t4 = (fs_mp_digit) (((t3[t1] & ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1))) * a3) & ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1)));
        t8 = a2->dp;
        t5 = t3 + t1;
        for(t7 = 0; t7 < a2->used; t7++) {
            *t5++ += ((fs_mp_word)t4) * ((fs_mp_word)*t8++);
        }
        t3[t1 + 1] += t3[t1] >> ((fs_mp_word) DIGIT_BIT);
    }
    t9 = t3 + t1;
    t5 = t3 + ++t1;
    for(; t1 <= a2->used * 2 + 1; t1++) {
        *t5++ += *t9++ >> ((fs_mp_word) DIGIT_BIT);
    }
    t6 = a1->dp;
    t5 = t3 + a2->used;
    for(t1 = 0; t1 < a2->used + 1; t1++) {
        *t6++ = (fs_mp_digit)(*t5++ & ((fs_mp_word) ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1))));
    }
    for(; t1 < t2; t1++) {
        *t6++ = 0;
    }
    a1->used = a2->used + 1;
    fs_mp_clamp(a1);
    if(fs_mp_cmp_mag(a1, a2) != -1) {
        fs_mp_s_sub(a1, a2, a1);
        goto done;
    }
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_montgomery_reduce(fs_mp_int* a1, fs_mp_int* a2, fs_mp_digit a3) {
    int t1 = 0;
    int t2 = a2->used * 2 + 1;
    fs_mp_digit t3 = 0;
    int t4 = 0;
    fs_mp_digit* t5 = NULL;
    fs_mp_digit* t6 = NULL;
    fs_mp_digit t7 = 0;
    fs_mp_word t8 = 0;

    fs_mp_error = 0;

    if((t2 < (1 << (sizeof(fs_mp_word) * 8 - 2 * DIGIT_BIT + 1))) &&
       a2->used <
       (1 << ((8 * sizeof (fs_mp_word)) - (2 * DIGIT_BIT)))) {
        fs_mp_fast_montgomery_reduce(a1, a2, a3);
        goto done;
    }
    if(a1->alloc < t2) {
        fs_mp_grow(a1, t2);
        if(fs_mp_error) {
            goto done;
        }
    }
    a1->used = t2;
    for(t1 = 0; t1 < a2->used; t1++) {
        t3 = (fs_mp_digit) (((fs_mp_word)a1->dp[t1]) * ((fs_mp_word)a3) & ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1)));
        {
            t5 = a2->dp;
            t6 = a1->dp + t1;
            t7 = 0;
            for(t4 = 0; t4 < a2->used; t4++) {
                t8       = ((fs_mp_word)t3) * ((fs_mp_word)*t5++) +
                                     ((fs_mp_word) t7) + ((fs_mp_word) * t6);
                t7       = (fs_mp_digit)(t8 >> ((fs_mp_word) DIGIT_BIT));
                *t6++ = (fs_mp_digit)(t8 & ((fs_mp_word) ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1))));
            }
            while(t7) {
                *t6   += t7;
                t7        = *t6 >> DIGIT_BIT;
                *t6++ &= ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1));
            }
        }
    }
    fs_mp_clamp(a1);
    fs_mp_rshd(a1, a2->used);
    if(fs_mp_cmp_mag(a1, a2) != -1) {
        fs_mp_s_sub(a1, a2, a1);
        goto done;
    }
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_dr_reduce(fs_mp_int* a1, fs_mp_int* a2, fs_mp_digit a3) {
    int t1 = 0;
    int t2 = 0;
    fs_mp_word t3 = 0;
    fs_mp_digit* t4 = NULL;
    fs_mp_digit* t5 = NULL;
    fs_mp_digit t6 = 0;

    fs_mp_error = 0;
    t2 = a2->used;
    if(a1->alloc < t2 + t2) {
        fs_mp_grow(a1, t2 + t2);
        if(fs_mp_error) {
            goto done;
        }
    }
    top:
    t4 = a1->dp;
    t5 = a1->dp + t2;
    t6 = 0;
    for(t1 = 0; t1 < t2; t1++) {
        t3         = ((fs_mp_word)*t5++) * ((fs_mp_word)a3) + *t4 + t6;
        *t4++  = (fs_mp_digit)(t3 & ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1)));
        t6        = (fs_mp_digit)(t3 >> ((fs_mp_word)DIGIT_BIT));
    }
    *t4++ = t6;
    for(t1 = t2 + 1; t1 < a1->used; t1++) {
        *t4++ = 0;
    }
    fs_mp_clamp(a1);
    if(fs_mp_cmp_mag(a1, a2) != -1) {
        fs_mp_s_sub(a1, a2, a1);
        goto top;
    }
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_mul_d(fs_mp_int* a1, fs_mp_digit a2, fs_mp_int* a3) {
    fs_mp_digit t1 = 0;
    fs_mp_digit* t2 = NULL;
    fs_mp_digit* t3 = NULL;
    fs_mp_word t4 = 0;
    int t5 = 0;
    int t6 = 0;

    fs_mp_error = 0;

    if(a3->alloc < a1->used + 1) {
        fs_mp_grow(a3, a1->used + 1);
        if(fs_mp_error) {
            goto done;
        }
    }
    t6 = a3->used;
    a3->sign = a1->sign;
    t2 = a1->dp;
    t3 = a3->dp;
    t1 = 0;
    for(t5 = 0; t5 < a1->used; t5++) {
        t4       = ((fs_mp_word) t1) + ((fs_mp_word)*t2++) * ((fs_mp_word)a2);
        *t3++ = (fs_mp_digit) (t4 & ((fs_mp_word) ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1))));
        t1       = (fs_mp_digit) (t4 >> ((fs_mp_word) DIGIT_BIT));
    }
    *t3++ = t1;
    ++t5;
    while(t5++ < t6) {
        *t3++ = 0;
    }
    a3->used = a1->used + 1;
    fs_mp_clamp(a3);
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_reduce_2k(fs_mp_int* a1, fs_mp_int* a2, fs_mp_digit a3) {
    fs_mp_int t1;
    int t2 = 0;

    fs_mp_error = 0;
    fs_mp_init(&t1);
    if(!t1.dp) {
        fs_mp_error = 1;
        goto done;
    }
    t2 = fs_mp_count_bits(a2);
    top:
    fs_mp_div_2d(a1, t2, &t1, a1);
    if(fs_mp_error) {
        goto LBL_ERR;
    }
    if(a3 != 1) {
        fs_mp_mul_d(&t1, a3, &t1);
        if(fs_mp_error) {
            goto LBL_ERR;
        }
    }
    fs_mp_s_add(a1, &t1, a1);
    if(fs_mp_error) {
        goto LBL_ERR;
    }
    if(fs_mp_cmp_mag(a1, a2) != -1) {
        fs_mp_s_sub(a1, a2, a1);
        goto top;
    }
    LBL_ERR:
    fs_mp_clear(&t1);
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_mul_2(fs_mp_int* a1, fs_mp_int* a2) {
    int t1 = 0;
    int t2 = 0;
    fs_mp_digit t3 = 0;
    fs_mp_digit t4 = 0;
    fs_mp_digit* t5 = NULL;
    fs_mp_digit* t6 = NULL;

    fs_mp_error = 0;

    if(a2->alloc < a1->used + 1) {
        fs_mp_grow(a2, a1->used + 1);
        if(fs_mp_error) {
            goto done;
        }
    }
    t2 = a2->used;
    a2->used = a1->used;
    {
        t5 = a1->dp;
        t6 = a2->dp;
        t3 = 0;
        for(t1 = 0; t1 < a1->used; t1++) {
            t4 = *t5 >> ((fs_mp_digit)(DIGIT_BIT - 1));
            *t6++ = ((*t5++ << ((fs_mp_digit)1)) | t3) & ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1));
            t3 = t4;
        }
        if(t3 != 0) {
            *t6 = 1;
            ++(a2->used);
        }
        t6 = a2->dp + a2->used;
        for(t1 = a2->used; t1 < t2; t1++) {
            *t6++ = 0;
        }
    }
    a2->sign = a1->sign;
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_montgomery_calc_normalization(fs_mp_int* a1, fs_mp_int* a2) {
    int t1 = 0;
    int t2 = fs_mp_count_bits(a2) % DIGIT_BIT;

    fs_mp_error = 0;

    if(a2->used > 1) {
        fs_mp_2expt(a1, (a2->used - 1) * DIGIT_BIT + t2 - 1);
        if(fs_mp_error) {
            goto done;
        }
    } else {
        fs_mp_set(a1, 1);
        t2 = 1;
    }
    for(t1 = t2 - 1; t1 < (int)DIGIT_BIT; t1++) {
        fs_mp_mul_2(a1, a1);
        if(fs_mp_error) {
            goto done;
        }
        if(fs_mp_cmp_mag(a1, a2) != -1) {
            fs_mp_s_sub(a1, a2, a1);
            if(fs_mp_error) {
                goto done;
            }
        }
    }
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_exptmod_fast(fs_mp_int* a1, fs_mp_int* a2, fs_mp_int* a3, fs_mp_int* a4, int a5) {
    fs_mp_int t1;
    fs_mp_int t2[16]; // 1 << t12
    fs_mp_digit t3 = 0;
    fs_mp_digit t4 = 0;
    int t5 = 0;
    int t6 = 0;
    int t7 = 0;
    int t8 = 0;
    int t9 = 0;
    int t10 = 0;
    int t11 = 0;
    int t12 = 0;
    int t13 = 0;
    fs_mp_int t14;
    int t15 = 0;

    fs_mp_error = 0;
    t15 = fs_mp_count_bits(a2);
    if(t15 <= 7) {
        t12 = 2;
    } else if(t15 <= 36) {
        t12 = 3;
    } else if(t15 <= 140) {
        t12 = 4;
    } else if(t15 <= 450) {
        t12 = 5;
    } else if(t15 <= 1303) {
        t12 = 6;
    } else if(t15 <= 3529) {
        t12 = 7;
    } else {
        t12 = 8;
    }
    // Low mem hack.  If you increase this, increase t2 also.
    if(t12 > 4) {
        t12 = 4;
    }
    fs_mp_init(&t2[1]);
    if(!t2[1].dp) {
        fs_mp_error = 1;
        goto done;
    }
    for(t10 = 1<<(t12-1); t10 < (1 << t12); t10++) {
        fs_mp_init(&t2[t10]);
        if(!t2[t10].dp) {
            for(t11 = 1<<(t12-1); t11 < t10; t11++) {
                fs_mp_clear(&t2[t11]);
            }
            fs_mp_clear(&t2[1]);
            goto done;
        }
    }
    if(a5 == 0) {
        fs_mp_montgomery_setup(a3, &t4);
        if(fs_mp_error) {
            goto LBL_M;
        }
        if(((a3->used * 2 + 1) < (1 << (sizeof(fs_mp_word) * 8 - 2 * DIGIT_BIT + 1))) &&
           a3->used < (1 << ((8 * sizeof (fs_mp_word)) - (2 * DIGIT_BIT)))) {
            t13 = 1;//fs_mp_fast_montgomery_reduce;
        } else {
            t13 = 2;//fs_mp_montgomery_reduce;
            fs_mp_error = 1;
            goto LBL_M;
        }
    } else if(a5 == 1) {
        t4 = (fs_mp_digit)((((fs_mp_word)1) << ((fs_mp_word)DIGIT_BIT)) - ((fs_mp_word)a3->dp[0]));
        t13 = 3; //fs_mp_dr_reduce;
    } else {
        fs_mp_reduce_2k_setup(a3, &t4);
        if(fs_mp_error) {
            goto LBL_M;
        }
        t13 = 4; //fs_mp_reduce_2k;
    }
    fs_mp_init(&t14);
    if(!t14.dp) {
        fs_mp_error = 1;
        goto LBL_M;
    }
    if(a5 == 0) {
        fs_mp_montgomery_calc_normalization(&t14, a3);
        if(fs_mp_error) {
            goto LBL_RES;
        }
        fs_mp_init(&t1);
        if(!t1.dp) {
            fs_mp_error = 1;
            goto done;
        }
        fs_mp_mul(a1, &t14, &t1);
        if(fs_mp_error) {
            fs_mp_clear(&t1);
            goto done;
        }
        fs_mp_mod(&t1, a3, &t2[1]);
        fs_mp_clear(&t1);
        if(fs_mp_error) {
            goto LBL_RES;
        }
    } else {
        fs_mp_set(&t14, 1);
        fs_mp_mod(a1, a3, &t2[1]);
        if(fs_mp_error) {
            goto LBL_RES;
        }
    }
    fs_mp_copy(&t2[1], &t2[1 << (t12 - 1)]);
    if(fs_mp_error) {
        goto LBL_RES;
    }
    for(t10 = 0; t10 < (t12 - 1); t10++) {
        fs_mp_sqr(&t2[1 << (t12 - 1)], &t2[1 << (t12 - 1)]);
        if(fs_mp_error) {
            goto LBL_RES;
        }
        switch(t13) {
        case 1:
            fs_mp_fast_montgomery_reduce(&t2[1 << (t12 - 1)], a3, t4);
            break;
        case 2:
            fs_mp_montgomery_reduce(&t2[1 << (t12 - 1)], a3, t4);
            break;
        case 3:
            fs_mp_dr_reduce(&t2[1 << (t12 - 1)], a3, t4);
            break;
        case 4:
            fs_mp_reduce_2k(&t2[1 << (t12 - 1)], a3, t4);
            break;
        default:
            break;
        }
        if(fs_mp_error) {
            goto LBL_RES;
        }
    }
    for(t10 = (1 << (t12 - 1)) + 1; t10 < (1 << t12); t10++) {
        fs_mp_mul(&t2[t10 - 1], &t2[1], &t2[t10]);
        if(fs_mp_error) {
            goto LBL_RES;
        }

        switch(t13) {
        case 1:
            fs_mp_fast_montgomery_reduce(&t2[t10], a3, t4);
            break;
        case 2:
            fs_mp_montgomery_reduce(&t2[t10], a3, t4);
            break;
        case 3:
            fs_mp_dr_reduce(&t2[t10], a3, t4);
            break;
        case 4:
            fs_mp_reduce_2k(&t2[t10], a3, t4);
            break;
        default:
            break;
        }
        if(fs_mp_error) {
            goto LBL_RES;
        }
    }
    t8 = 0;
    t7 = 1;
    t3 = 0;
    t9 = a2->used - 1;
    t6 = 0;
    t5 = 0;
    for(;;) {
        if(--t7 == 0) {
            if(t9 == -1) {
                break;
            }
            t3    = a2->dp[t9--];
            t7 = (int)DIGIT_BIT;
        }
        t11     = (fs_mp_digit)(t3 >> (DIGIT_BIT - 1)) & 1;
        t3 <<= (fs_mp_digit)1;
        if(t8 == 0 && t11 == 0) {
            continue;
        }
        if(t8 == 1 && t11 == 0) {
            fs_mp_sqr(&t14, &t14);
            if(fs_mp_error) {
                goto LBL_RES;
            }

            switch(t13) {
            case 1:
                fs_mp_fast_montgomery_reduce(&t14, a3, t4);
                break;
            case 2:
                fs_mp_montgomery_reduce(&t14, a3, t4);
                break;
            case 3:
                fs_mp_dr_reduce(&t14, a3, t4);
                break;
            case 4:
                fs_mp_reduce_2k(&t14, a3, t4);
                break;
            default:
                break;
            }
            if(fs_mp_error) {
                goto LBL_RES;
            }
            continue;
        }
        t5 |= (t11 << (t12 - ++t6));
        t8    = 2;
        if(t6 == t12) {
            for(t10 = 0; t10 < t12; t10++) {
                fs_mp_sqr(&t14, &t14);
                if(fs_mp_error) {
                    goto LBL_RES;
                }

                switch(t13) {
                case 1:
                    fs_mp_fast_montgomery_reduce(&t14, a3, t4);
                    break;
                case 2:
                    fs_mp_montgomery_reduce(&t14, a3, t4);
                    break;
                case 3:
                    fs_mp_dr_reduce(&t14, a3, t4);
                    break;
                case 4:
                    fs_mp_reduce_2k(&t14, a3, t4);
                    break;
                default:
                    break;
                }
                if(fs_mp_error) {
                    goto LBL_RES;
                }
            }
            fs_mp_mul(&t14, &t2[t5], &t14);
            if(fs_mp_error) {
                goto LBL_RES;
            }

            switch(t13) {
            case 1:
                fs_mp_fast_montgomery_reduce(&t14, a3, t4);
                break;
            case 2:
                fs_mp_montgomery_reduce(&t14, a3, t4);
                break;
            case 3:
                fs_mp_dr_reduce(&t14, a3, t4);
                break;
            case 4:
                fs_mp_reduce_2k(&t14, a3, t4);
                break;
            default:
                break;
            }
            if(fs_mp_error) {
                goto LBL_RES;
            }
            t6 = 0;
            t5 = 0;
            t8   = 1;
        }
    }
    if(t8 == 2 && t6 > 0) {
        for(t10 = 0; t10 < t6; t10++) {
            fs_mp_sqr(&t14, &t14);
            if(fs_mp_error) {
                goto LBL_RES;
            }
            switch(t13) {
            case 1:
                fs_mp_fast_montgomery_reduce(&t14, a3, t4);
                break;
            case 2:
                fs_mp_montgomery_reduce(&t14, a3, t4);
                break;
            case 3:
                fs_mp_dr_reduce(&t14, a3, t4);
                break;
            case 4:
                fs_mp_reduce_2k(&t14, a3, t4);
                break;
            default:
                break;
            }
            if(fs_mp_error) {
                goto LBL_RES;
            }
            t5 <<= 1;
            if((t5 & (1 << t12)) != 0) {
                fs_mp_mul(&t14, &t2[1], &t14);
                if(fs_mp_error) {
                    goto LBL_RES;
                }
                switch(t13) {
                case 1:
                    fs_mp_fast_montgomery_reduce(&t14, a3, t4);
                    break;
                case 2:
                    fs_mp_montgomery_reduce(&t14, a3, t4);
                    break;
                case 3:
                    fs_mp_dr_reduce(&t14, a3, t4);
                    break;
                case 4:
                    fs_mp_reduce_2k(&t14, a3, t4);
                    break;
                default:
                    break;
                }
                if(fs_mp_error) {
                    goto LBL_RES;
                }
            }
        }
    }
    if(a5 == 0) {
        switch(t13) {
        case 1:
            fs_mp_fast_montgomery_reduce(&t14, a3, t4);
            break;
        case 2:
            fs_mp_montgomery_reduce(&t14, a3, t4);
            break;
        case 3:
            fs_mp_dr_reduce(&t14, a3, t4);
            break;
        case 4:
            fs_mp_reduce_2k(&t14, a3, t4);
            break;
        default:
            break;
        }
        if(fs_mp_error) {
            goto LBL_RES;
        }
    }
    fs_mp_exch(&t14, a4);
    fs_mp_error = 0;
    LBL_RES:
    fs_mp_clear(&t14);
    LBL_M:
    fs_mp_clear(&t2[1]);
    for(t10 = 1<<(t12-1); t10 < (1 << t12); t10++) {
        fs_mp_clear(&t2[t10]);
    }
done:
    ;
}

__FS_FUNCTION_MAYBE_INLINE void fs_mp_exptmod(fs_mp_int* a1, fs_mp_int* a2, fs_mp_int* a3, fs_mp_int* a4) {
    int t1 = 0;
    fs_mp_int t2;
    fs_mp_int t3;
    int t4 = 0;
    int t5 = 0;
    int t6 = 0;

    fs_mp_error = 0;

    if(a3->sign == -1) {
        fs_mp_error = 1;
        goto done;
    }
    if(a2->sign == -1) {
        fs_mp_init(&t2);
        if(!t2.dp) {
            fs_mp_error = 1;
            goto done;
        }
        fs_mp_invmod(a1, a3, &t2);
        if(fs_mp_error) {
            fs_mp_clear(&t2);
            goto done;
        }
        fs_mp_init(&t3);
        if(!t3.dp) {
            fs_mp_error = 1;
            fs_mp_clear(&t2);
            goto done;
        }
        fs_mp_abs(a2, &t3);
        if(fs_mp_error) {
            fs_mp_clear(&t2);
            fs_mp_clear(&t3);
            goto done;
        }
        fs_mp_error = 1;
        goto done;
    }
    if(a3->used == 0) {
        t6 = 0;
    } else if(a3->used == 1) {
        t6 = 1;
    } else if(a3->used > 1) {
        for(t5 = t4 = 0; t4 < a3->used; t4++) {
            if(a3->dp[t4] == ((((fs_mp_digit)1)<<((fs_mp_digit)DIGIT_BIT))-((fs_mp_digit)1))) {
                ++t5;
            }
        }
        t6 = (t5 >= (a3->used/2)) ? 1 : 0;
    }
    if(t6 == 1) {
        fs_mp_s_exptmod(a1, a2, a3, a4, 1);
        goto done;
    }
    t1 = fs_mp_dr_is_modulus(a3);
    if(t1 == 0) {
        t1 = fs_mp_reduce_is_2k(a3) << 1;
    }
    if((((a3)->used > 0 && (((a3)->dp[0] & 1) == 1)) ? 1 : 0) == 1 || t1 !=  0) {
        fs_mp_exptmod_fast(a1, a2, a3, a4, t1);
        goto done;
    } else {
        fs_mp_s_exptmod(a1, a2, a3, a4, 0);
        goto done;
    }
done:
    ;
}
