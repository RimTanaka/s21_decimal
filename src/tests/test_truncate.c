#include "test.h"

// 123.999 -> 123
START_TEST(truncate_test_1) {
  s21_decimal test = {{123999, 0, 0, 0}},
              result_decimal = s21_get_null_decimal();
  float expected_float = 123.0, res_float = 0.0;
  int expected_int = 123, res_int = 0;

  s21_set_scale(&test, 3);
  s21_truncate(test, &result_decimal);

  s21_from_decimal_to_float(result_decimal, &res_float);
  ck_assert_float_eq(expected_float, res_float);

  s21_from_decimal_to_int(result_decimal, &res_int);
  ck_assert_int_eq(expected_int, res_int);
}
END_TEST

START_TEST(truncate_test_2) {
  // 2640938750475477919784798344.5
  s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x10000}};
  s21_decimal result = s21_get_null_decimal();
  // 2640938750475477919784798344
  s21_decimal decimal_check = {{0x88888888, 0x88888888, 0x8888888, 0x0}};

  s21_truncate(decimal, &result);

  ck_assert_int_eq(s21_is_decimal_identical(result, decimal_check), 1);
}

Suite *s21_truncate_suite(void) {
  Suite *s;
  s = suite_create("\033[33ms21_truncate\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("s21_truncate_core");
  tcase_add_test(tc_core, truncate_test_1);
  tcase_add_test(tc_core, truncate_test_2);

  suite_add_tcase(s, tc_core);
  return s;
}
