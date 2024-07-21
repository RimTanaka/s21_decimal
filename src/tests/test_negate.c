#include "test.h"

START_TEST(negate_test_1) {
  s21_decimal test = s21_get_null_decimal(),
              test_modify = s21_get_null_decimal();
  s21_from_int_to_decimal(12, &test);

  int code = s21_negate(test, &test_modify);
  ck_assert_int_eq(code, OK);

  int expected = -12, result = 0;

  code = s21_from_decimal_to_int(test_modify, &result);
  ck_assert_int_eq(code, OK);

  ck_assert_int_eq(expected, result);
}
END_TEST

START_TEST(negate_test_2) {
  s21_decimal test = {{12, 0, 0, 0}};
  s21_decimal test_modify = s21_get_null_decimal();

  int code = s21_negate(test, &test_modify);
  ck_assert_int_eq(code, OK);

  int expected = -12, result = 0;

  code = s21_from_decimal_to_int(test_modify, &result);
  ck_assert_int_eq(code, OK);

  ck_assert_int_eq(expected, result);
}
END_TEST

START_TEST(negate_test_3) {
  s21_decimal test = {{0, 0, 0, 0}};
  s21_decimal test_modify = s21_get_null_decimal();

  int code = s21_negate(test, &test_modify);
  ck_assert_int_eq(code, OK);

  int expected = 0, result = 0;

  code = s21_from_decimal_to_int(test_modify, &result);
  ck_assert_int_eq(code, OK);

  ck_assert_int_eq(expected, result);
}
END_TEST

START_TEST(negate_test_4) {
  s21_decimal test = s21_get_null_decimal(),
              test_modify = s21_get_null_decimal();
  s21_from_int_to_decimal(-5, &test);

  int code = s21_negate(test, &test_modify);
  ck_assert_int_eq(code, OK);

  int expected = 5, result = 0;

  code = s21_from_decimal_to_int(test_modify, &result);
  ck_assert_int_eq(code, OK);

  ck_assert_int_eq(expected, result);
}
END_TEST

Suite *s21_negate_suite(void) {
  Suite *s;
  s = suite_create("\033[33ms21_negate\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("s21_negate_core");
  tcase_add_test(tc_core, negate_test_1);
  tcase_add_test(tc_core, negate_test_2);
  tcase_add_test(tc_core, negate_test_3);
  tcase_add_test(tc_core, negate_test_4);

  suite_add_tcase(s, tc_core);
  return s;
}
