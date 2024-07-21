#include "test.h"

// test left shift
START_TEST(s21_shift_left_big_test_1) {
  s21_decimal test = s21_get_null_decimal(),
              result_decimal = s21_get_null_decimal();
  int result = 0, expected = 20, code = OK;

  code = s21_from_int_to_decimal(10, &test);
  ck_assert_int_eq(code, OK);

  s21_big_decimal big_result_decimal, big_test;
  s21_to_big_decimal(test, &big_test);
  s21_to_big_decimal(result_decimal, &big_result_decimal);

  code = s21_shift_left_big(big_test, 1, &big_result_decimal);
  ck_assert_int_eq(code, OK);

  s21_to_decimal(big_result_decimal, &result_decimal);

  code = s21_from_decimal_to_int(result_decimal, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(result, expected);
}
END_TEST

// x*10 = x*6 + x*4
START_TEST(s21_shift_left_big_test_2) {
  s21_decimal test = s21_get_null_decimal(), v_result = s21_get_null_decimal();

  int rnd = 1 + (int)(214748365.0 * rand() / (RAND_MAX + 1.0));
  int result = 0, expected = rnd * 10, code = OK;

  s21_from_int_to_decimal(rnd, &test);
  s21_decimal v_1 = s21_get_null_decimal(), v_2 = s21_get_null_decimal();

  s21_big_decimal big_v_1, big_v_2, big_test;
  s21_to_big_decimal(v_1, &big_v_1);
  s21_to_big_decimal(v_2, &big_v_2);
  s21_to_big_decimal(test, &big_test);

  code = s21_shift_left_big(big_test, 3, &big_v_1);  // x*8
  ck_assert_int_eq(code, OK);

  code = s21_shift_left_big(big_test, 1, &big_v_2);  // x*2
  ck_assert_int_eq(code, OK);

  s21_to_decimal(big_v_1, &v_1);
  s21_to_decimal(big_v_2, &v_2);

  code = s21_add(v_1, v_2, &v_result);
  ck_assert_int_eq(code, OK);

  s21_from_decimal_to_int(v_result, &result);

  ck_assert_int_eq(result, expected);
}
END_TEST

Suite *s21_shift_left_suite(void) {
  Suite *s;
  s = suite_create("\033[33ms21_shift_left\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("s21_shift_left_core");
  tcase_add_test(tc_core, s21_shift_left_big_test_1);
  tcase_add_test(tc_core, s21_shift_left_big_test_2);

  suite_add_tcase(s, tc_core);
  return s;
}
