#include "test.h"

START_TEST(test_s21_is_zero_non_zero) {
  s21_decimal decimal = {.bits = {1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_zero(decimal), 0);
}

START_TEST(test_s21_is_zero_zero) {
  s21_decimal decimal = {.bits = {0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_zero(decimal), 1);
}

START_TEST(test_s21_is_less) {
  // 1 < 2
  s21_decimal decimal_1 = {.bits = {-133248880, 240, 0, -2147483648}};
  s21_decimal decimal_2 = {.bits = {333425, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(decimal_1, decimal_2), 1);

  // 1 == 2
  decimal_1.bits[3] = -133248880, decimal_1.bits[2] = 240,
  decimal_1.bits[1] = 0, decimal_1.bits[0] = -2147483648;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 240,
  decimal_2.bits[1] = 0, decimal_2.bits[0] = -2147483648;
  ck_assert_int_eq(s21_is_less(decimal_1, decimal_2), 0);

  // 1 > 2
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 240, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = -2147483648;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 240,
  decimal_2.bits[1] = 0, decimal_2.bits[0] = -2147483648;
  ck_assert_int_eq(s21_is_less(decimal_1, decimal_2), 0);

  // 0 = 0
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = 0, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_less(decimal_1, decimal_2), 0);

  // -0 = 0
  decimal_1.bits[3] = -133248880, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = 0, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_less(decimal_1, decimal_2), 0);

  // 0 = -0
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_less(decimal_1, decimal_2), 0);

  // 2.4 < 24
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 24;
  decimal_2.bits[3] = 0, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 24;
  s21_set_scale(&decimal_1, 1);
  ck_assert_int_eq(s21_is_less(decimal_1, decimal_2), 1);

  // Max_Dec^28 > Max_Dec
  decimal_1.bits[3] = 0, decimal_1.bits[2] = -1, decimal_1.bits[1] = -1,
  decimal_1.bits[0] = -1;
  decimal_2.bits[3] = 0, decimal_2.bits[2] = -1, decimal_2.bits[1] = -1,
  decimal_2.bits[0] = -1;
  s21_set_scale(&decimal_1, 28);
  ck_assert_int_eq(s21_is_less(decimal_1, decimal_2), 1);
}

START_TEST(test_s21_is_less_or_equal) {
  // 1 < 2
  s21_decimal decimal_1 = {.bits = {-133248880, 240, 0, -2147483648}};
  s21_decimal decimal_2 = {.bits = {333425, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(decimal_1, decimal_2), 1);

  // 1 == 2
  decimal_1.bits[3] = -133248880, decimal_1.bits[2] = 240,
  decimal_1.bits[1] = 0, decimal_1.bits[0] = -2147483648;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 240,
  decimal_2.bits[1] = 0, decimal_2.bits[0] = -2147483648;
  ck_assert_int_eq(s21_is_less_or_equal(decimal_1, decimal_2), 1);

  // 1 > 2
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 240, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = -2147483648;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 240,
  decimal_2.bits[1] = 0, decimal_2.bits[0] = -2147483648;
  ck_assert_int_eq(s21_is_less_or_equal(decimal_1, decimal_2), 0);

  // 0 = 0
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = 0, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_less_or_equal(decimal_1, decimal_2), 1);

  // -0 = 0
  decimal_1.bits[3] = -133248880, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = 0, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_less_or_equal(decimal_1, decimal_2), 1);

  // 0 = -0
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_less_or_equal(decimal_1, decimal_2), 1);
}

START_TEST(test_s21_is_greater) {
  // 1 < 2
  s21_decimal decimal_1 = {.bits = {-133248880, 240, 0, -2147483648}};
  s21_decimal decimal_2 = {.bits = {333425, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(decimal_1, decimal_2), 0);

  // 1 == 2
  decimal_1.bits[3] = -133248880, decimal_1.bits[2] = 240,
  decimal_1.bits[1] = 0, decimal_1.bits[0] = -2147483648;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 240,
  decimal_2.bits[1] = 0, decimal_2.bits[0] = -2147483648;
  ck_assert_int_eq(s21_is_greater(decimal_1, decimal_2), 0);

  // 1 > 2
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 240, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = -2147483648;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 240,
  decimal_2.bits[1] = 0, decimal_2.bits[0] = -2147483648;
  ck_assert_int_eq(s21_is_greater(decimal_1, decimal_2), 1);

  // 0 = 0
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = 0, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_greater(decimal_1, decimal_2), 0);

  // -0 = 0
  decimal_1.bits[3] = -133248880, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = 0, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_greater(decimal_1, decimal_2), 0);

  // 0 = -0
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_greater(decimal_1, decimal_2), 0);
}

START_TEST(test_s21_is_greater_or_equal) {
  // 1 < 2
  s21_decimal decimal_1 = {.bits = {-133248880, 240, 0, -2147483648}};
  s21_decimal decimal_2 = {.bits = {333425, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal_1, decimal_2), 0);

  // 1 == 2
  decimal_1.bits[3] = -133248880, decimal_1.bits[2] = 240,
  decimal_1.bits[1] = 0, decimal_1.bits[0] = -2147483648;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 240,
  decimal_2.bits[1] = 0, decimal_2.bits[0] = -2147483648;
  ck_assert_int_eq(s21_is_greater_or_equal(decimal_1, decimal_2), 1);

  // 1 > 2
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 240, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = -2147483648;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 240,
  decimal_2.bits[1] = 0, decimal_2.bits[0] = -2147483648;
  ck_assert_int_eq(s21_is_greater_or_equal(decimal_1, decimal_2), 1);

  // 0 = 0
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = 0, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_greater_or_equal(decimal_1, decimal_2), 1);

  // -0 = 0
  decimal_1.bits[3] = -133248880, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = 0, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_greater_or_equal(decimal_1, decimal_2), 1);

  // 0 = -0
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_greater_or_equal(decimal_1, decimal_2), 1);
}

START_TEST(test_s21_is_equal) {
  // 1 < 2
  s21_decimal decimal_1 = {.bits = {-133248880, 240, 0, -2147483648}};
  s21_decimal decimal_2 = {.bits = {333425, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(decimal_1, decimal_2), 0);

  // 1 == 2
  decimal_1.bits[3] = -133248880, decimal_1.bits[2] = 240,
  decimal_1.bits[1] = 0, decimal_1.bits[0] = -2147483648;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 240,
  decimal_2.bits[1] = 0, decimal_2.bits[0] = -2147483648;
  ck_assert_int_eq(s21_is_equal(decimal_1, decimal_2), 1);

  // 1 > 2
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 240, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = -2147483648;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 240,
  decimal_2.bits[1] = 0, decimal_2.bits[0] = -2147483648;
  ck_assert_int_eq(s21_is_equal(decimal_1, decimal_2), 0);

  // 0 = 0
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = 0, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_equal(decimal_1, decimal_2), 1);

  // -0 = 0
  decimal_1.bits[3] = -133248880, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = 0, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_equal(decimal_1, decimal_2), 1);

  // 0 = -0
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_equal(decimal_1, decimal_2), 1);
}

START_TEST(test_s21_is_not_equal) {
  // 1 < 2
  s21_decimal decimal_1 = {.bits = {-133248880, 240, 0, -2147483648}};
  s21_decimal decimal_2 = {.bits = {333425, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(decimal_1, decimal_2), 1);

  // 1 == 2
  decimal_1.bits[3] = -133248880, decimal_1.bits[2] = 240,
  decimal_1.bits[1] = 0, decimal_1.bits[0] = -2147483648;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 240,
  decimal_2.bits[1] = 0, decimal_2.bits[0] = -2147483648;
  ck_assert_int_eq(s21_is_not_equal(decimal_1, decimal_2), 0);

  // 1 > 2
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 240, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = -2147483648;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 240,
  decimal_2.bits[1] = 0, decimal_2.bits[0] = -2147483648;
  ck_assert_int_eq(s21_is_not_equal(decimal_1, decimal_2), 1);

  // 0 = 0
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = 0, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_not_equal(decimal_1, decimal_2), 0);

  // -0 = 0
  decimal_1.bits[3] = -133248880, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = 0, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_not_equal(decimal_1, decimal_2), 0);

  // 0 = -0
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_not_equal(decimal_1, decimal_2), 0);
}

Suite *s21_compare_suite(void) {
  Suite *s;
  s = suite_create("\033[33ms21_compare\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("21_compare_core");
  tcase_add_test(tc_core, test_s21_is_zero_non_zero);
  tcase_add_test(tc_core, test_s21_is_zero_zero);

  tcase_add_test(tc_core, test_s21_is_less);
  tcase_add_test(tc_core, test_s21_is_less_or_equal);

  tcase_add_test(tc_core, test_s21_is_greater);
  tcase_add_test(tc_core, test_s21_is_greater_or_equal);

  tcase_add_test(tc_core, test_s21_is_equal);
  tcase_add_test(tc_core, test_s21_is_not_equal);

  suite_add_tcase(s, tc_core);
  return s;
}
