#define TEST_HED
#define BUFFER 512

#ifndef CHECK_HED
#define CHECK_HED
#include <check.h>
#endif

#include "../s21_decimal.h"

#ifndef TIME_HED
#define TIME_HED
#include <time.h>
#endif

int s21_is_decimal_identical(s21_decimal v1, s21_decimal v2);

Suite *s21_floor_suite(void);
Suite *s21_negate_suite(void);
Suite *s21_round_suite(void);
Suite *s21_truncate_suite(void);
Suite *s21_dtoi_suite(void);
Suite *s21_dtof_suite(void);
Suite *s21_add_suite(void);
Suite *s21_sub_suite(void);
Suite *s21_shift_left_suite(void);
Suite *s21_normalize_suite(void);
Suite *s21_converts_suite(void);
Suite *s21_itod_suite(void);
Suite *s21_ftod_suite(void);
Suite *s21_compare_suite(void);
Suite *s21_divide_by_10_suite(void);
Suite *s21_bank_round_suite(void);
Suite *s21_mul_suite(void);
Suite *s21_div_suite(void);
