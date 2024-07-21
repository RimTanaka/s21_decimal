#include "test.h"

// 11,9 -> 12
START_TEST(round_test_1) {
  s21_decimal value = {{119, 0, 0, 0}}, result = s21_get_null_decimal(),
              expected = {{12, 0, 0, 0}};
  s21_set_scale(&value, 1);

  int code = s21_round(value, &result);
  ck_assert_int_eq(code, OK);

  int is_eq = s21_is_decimal_identical(result, expected);

  ck_assert_int_eq(is_eq, 1);
}
END_TEST

// −0,9 -> −1
START_TEST(round_test_2) {
  s21_decimal value = {{9, 0, 0, 0}}, result = s21_get_null_decimal(),
              expected = {{1, 0, 0, 0}};
  s21_set_sign(&expected, 1);

  s21_set_scale(&value, 1);
  s21_set_sign(&value, 1);

  int code = s21_round(value, &result);
  ck_assert_int_eq(code, OK);

  int is_eq = s21_is_decimal_identical(result, expected);

  ck_assert_int_eq(is_eq, 1);
}
END_TEST

// −1,1 -> −1;
START_TEST(round_test_3) {
  s21_decimal value = {{11, 0, 0, 0}}, result = s21_get_null_decimal(),
              expected = {{1, 0, 0, 0}};
  s21_set_sign(&expected, 1);

  s21_set_scale(&value, 1);
  s21_set_sign(&value, 1);

  int code = s21_round(value, &result);
  ck_assert_int_eq(code, OK);

  int is_eq = s21_is_decimal_identical(result, expected);

  ck_assert_int_eq(is_eq, 1);
}
END_TEST

// 2,5 -> 3
START_TEST(round_test_4) {
  s21_decimal value = {{25, 0, 0, 0}}, result = s21_get_null_decimal(),
              expected = {{3, 0, 0, 0}};

  s21_set_scale(&value, 1);

  int code = s21_round(value, &result);
  ck_assert_int_eq(code, OK);

  int is_eq = s21_is_decimal_identical(result, expected);

  ck_assert_int_eq(is_eq, 1);
}
END_TEST

// -2,49999 -> -2
START_TEST(round_test_5) {
  s21_decimal value = {{249999, 0, 0, 0}}, result = s21_get_null_decimal(),
              expected = {{2, 0, 0, 0}};

  s21_set_sign(&value, 1);
  s21_set_scale(&value, 5);

  s21_set_sign(&expected, 1);

  int code = s21_round(value, &result);
  ck_assert_int_eq(code, OK);

  int is_eq = s21_is_decimal_identical(result, expected);

  ck_assert_int_eq(is_eq, 1);
}
END_TEST

// result = -2 != expected = -2
START_TEST(round_test_6) {
  s21_decimal value = {{249999, 0, 0, 0}}, result = s21_get_null_decimal(),
              expected = {{3, 0, 0, 0}};

  s21_set_sign(&value, 1);
  s21_set_scale(&value, 5);

  s21_set_sign(&expected, 1);

  int code = s21_round(value, &result);
  ck_assert_int_eq(code, OK);

  int is_eq = s21_is_decimal_identical(result, expected);

  ck_assert_int_ne(is_eq, 1);
}
END_TEST

START_TEST(round_test_7) {
  s21_decimal value = {{-1, -1, -1, 0}}, result = s21_get_null_decimal();

  s21_set_scale(&value, 30);

  int code = s21_round(value, &result);
  ck_assert_int_eq(code, 1);
}
END_TEST

Suite *s21_round_suite(void) {
  Suite *s;
  s = suite_create("\033[33ms21_round\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("s21_round_core");
  tcase_add_test(tc_core, round_test_1);
  tcase_add_test(tc_core, round_test_2);
  tcase_add_test(tc_core, round_test_3);
  tcase_add_test(tc_core, round_test_4);
  tcase_add_test(tc_core, round_test_5);
  tcase_add_test(tc_core, round_test_6);
  tcase_add_test(tc_core, round_test_7);

  suite_add_tcase(s, tc_core);
  return s;
}
