#include "test.h"

START_TEST(s21_normalize_test_1) {
  // write test like s21_decimal = {{0xFF, 0, 0, 0xACDC}}
  // d_1 = 1.2, d_2 = 0.12
  s21_decimal d_1 = {{12, 0, 0, 0}}, d_2 = {{12, 0, 0, 0}};
  s21_set_scale(&d_1, 1);
  s21_set_scale(&d_2, 2);

  s21_big_decimal bd_1, bd_2;
  s21_to_big_decimal(d_1, &bd_1);
  s21_to_big_decimal(d_2, &bd_2);

  int code = s21_normalize(&bd_1, &bd_2);
  ck_assert_int_eq(OK, code);

  code = s21_to_decimal(bd_1, &d_1);
  ck_assert_int_eq(OK, code);

  code = s21_to_decimal(bd_2, &d_2);
  ck_assert_int_eq(OK, code);

  int scale = s21_get_scale(d_1);
  ck_assert_int_eq(scale, 2);

  ck_assert_int_eq(s21_get_scale(d_2), 2);

  float f_1 = 0.0, f_2 = 0.0;

  code = s21_from_decimal_to_float(d_1, &f_1);
  ck_assert_int_eq(OK, code);

  code = s21_from_decimal_to_float(d_2, &f_2);
  ck_assert_int_eq(OK, code);

  ck_assert_float_eq(f_1, 1.2);
  ck_assert_float_eq(f_2, 0.12);
}
END_TEST

START_TEST(s21_normalize_test_2) {
  // write test like s21_decimal = {{0xFF, 0, 0, 0xACDC}}
  // d_1 = 1.2, d_2 = 0.12

  s21_big_decimal bd_1 = {{12, 0, 0, 0, 0, 0, 0, 0}},
                  bd_2 = {{12, 0, 0, 0, 0, 0, 0, 0}};
  s21_set_scale_big(&bd_1, -1);
  int code = s21_normalize(&bd_1, &bd_2);
  ck_assert_int_eq(1, code);
}
END_TEST

Suite *s21_normalize_suite(void) {
  Suite *s;
  s = suite_create("\033[33ms21_s21_normalize\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("s21_s21_normalize_core");
  tcase_add_test(tc_core, s21_normalize_test_1);
  tcase_add_test(tc_core, s21_normalize_test_2);

  suite_add_tcase(s, tc_core);
  return s;
}
