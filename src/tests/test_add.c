#include "test.h"

START_TEST(add_test_1) {
  float value_1 = 122e-2, value_2 = 12e-2, result = 0, expected = 134e-2;
  s21_decimal value_1_decimal = s21_get_null_decimal(),
              value_2_decimal = s21_get_null_decimal(),
              value_3_decimal = s21_get_null_decimal();

  s21_from_float_to_decimal(value_1, &value_1_decimal);
  s21_from_float_to_decimal(value_2, &value_2_decimal);

  s21_add(value_1_decimal, value_2_decimal, &value_3_decimal);

  s21_from_decimal_to_float(value_3_decimal, &result);

  ck_assert_float_eq(result, expected);
}
END_TEST

START_TEST(add_test_2) {
  float result = 0, expected = 1.32;

  // d_1 = 1.2, d_2 = 0.12
  s21_decimal d_1 = {{12, 0, 0, 0}}, d_2 = {{12, 0, 0, 0}};
  s21_set_scale(&d_1, 1);
  s21_set_scale(&d_2, 2);

  s21_decimal d_3 = s21_get_null_decimal();

  s21_add(d_1, d_2, &d_3);

  s21_from_decimal_to_float(d_3, &result);

  ck_assert_float_eq(result, expected);
}
END_TEST

START_TEST(add_test_3) {
  float result = 0, expected = 1.0;

  // d_1 = 1.2, d_2 = 0.12
  s21_decimal d_1 = {{12, 0, 0, 0}}, d_2 = {{2, 0, 0, 0}};
  s21_set_scale(&d_1, 1);
  s21_set_scale(&d_2, 1);
  s21_set_sign(&d_2, 1);

  s21_decimal d_3 = s21_get_null_decimal();

  s21_add(d_1, d_2, &d_3);

  s21_from_decimal_to_float(d_3, &result);

  ck_assert_float_eq(result, expected);
}
END_TEST

// START_TEST(add_test_4) {
//   float result = 0, expected = -0.08;
//
//   // d_1 = 1.2, d_2 = 0.12
//   s21_decimal d_1 = {{12, 0, 0, 0}}, d_2 = {{2, 0, 0, 0}};
//   s21_set_scale(&d_1, 2);
//   s21_set_scale(&d_2, 1);
//   s21_set_sign(&d_2, 1);
//
//   s21_decimal d_3 = s21_get_null_decimal();
//
//   s21_add(d_1, d_2, &d_3);
//
//   s21_from_decimal_to_float(d_3, &result);
//
//   ck_assert_float_eq(result, expected);
// }
// END_TEST

START_TEST(add_test_5) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -79228162514264337593543950327
  s21_decimal check = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {{0}};
  s21_add(decimal1, decimal2, &result);

  int code = s21_is_equal(result, check);

  ck_assert_int_eq(1, code);
}

Suite *s21_add_suite(void) {
  Suite *s;
  s = suite_create("\033[33ms21_add\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("s21_add_core");
  tcase_add_test(tc_core, add_test_1);
  tcase_add_test(tc_core, add_test_2);
  tcase_add_test(tc_core, add_test_3);
  //  tcase_add_test(tc_core, add_test_4);
  tcase_add_test(tc_core, add_test_5);

  suite_add_tcase(s, tc_core);
  return s;
}
