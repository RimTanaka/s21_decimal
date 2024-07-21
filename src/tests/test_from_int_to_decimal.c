#include "test.h"

// simple conversion
START_TEST(itod_test_1) {
  int x = rand();
  s21_decimal expected = {{x, 0, 0, 0}};
  s21_decimal result = s21_get_null_decimal();

  s21_from_int_to_decimal(x, &result);

  ck_assert_int_eq(expected.bits[0], result.bits[0]);
}
END_TEST

// conversion with negative integer
START_TEST(itod_test_2) {
  int x = rand();
  s21_decimal expected = {{x, 0, 0, 0}};
  expected.bits[3] |= (1u << 31);

  s21_decimal result = s21_get_null_decimal();

  s21_from_int_to_decimal(x * -1, &result);

  ck_assert_int_eq(expected.bits[0], result.bits[0]);
  ck_assert_int_eq(expected.bits[3], result.bits[3]);
}
END_TEST

Suite *s21_itod_suite(void) {
  Suite *s;
  s = suite_create("\033[33ms21_itod\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("s21_itod_core");
  tcase_add_test(tc_core, itod_test_1);
  tcase_add_test(tc_core, itod_test_2);

  suite_add_tcase(s, tc_core);
  return s;
}
