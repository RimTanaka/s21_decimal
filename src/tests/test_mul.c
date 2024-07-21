#include "test.h"

// 1.22 * 0.12 = 0.1464
START_TEST(mul_test_1) {
  float value_1 = 122e-2f, value_2 = 12e-2f, result = 0.0f, expected = 1464e-4f;
  s21_decimal value_1_decimal = s21_get_null_decimal(),
              value_2_decimal = s21_get_null_decimal(),
              value_3_decimal = s21_get_null_decimal();

  s21_from_float_to_decimal(value_1, &value_1_decimal);
  s21_from_float_to_decimal(value_2, &value_2_decimal);

  s21_mul(value_1_decimal, value_2_decimal, &value_3_decimal);

  s21_from_decimal_to_float(value_3_decimal, &result);

  ck_assert_float_eq(result, expected);
}
END_TEST

// -1.22 * 0.105 = -0.1281
START_TEST(mul_test_2) {
  float result = 0.0f, expected = -1281e-4f;

  s21_decimal d_1 = {{122, 0, 0, 0}}, d_2 = {{105, 0, 0, 0}};
  s21_set_scale(&d_1, 2);
  s21_set_scale(&d_2, 3);

  s21_set_sign(&d_1, 1);

  s21_decimal d_3 = s21_get_null_decimal();

  s21_mul(d_1, d_2, &d_3);

  s21_from_decimal_to_float(d_3, &result);

  ck_assert_float_eq(result, expected);
}
END_TEST

// -0.105 * -1.22 = 0.1281
START_TEST(mul_test_3) {
  float result = 0.0f, expected = 1281e-4f;

  s21_decimal d_1 = {{105, 0, 0, 0}}, d_2 = {{122, 0, 0, 0}};
  s21_set_scale(&d_1, 3);
  s21_set_scale(&d_2, 2);

  s21_set_sign(&d_2, 1);
  s21_set_sign(&d_1, 1);

  s21_decimal d_3 = s21_get_null_decimal();

  s21_mul(d_1, d_2, &d_3);

  s21_from_decimal_to_float(d_3, &result);

  ck_assert_float_eq(result, expected);
}
END_TEST

// -0.15 * -1.22 = 0.183
START_TEST(mul_test_4) {
  float result = 0.0f, expected = 183e-3f;

  s21_decimal d_1 = {{15, 0, 0, 0}}, d_2 = {{122, 0, 0, 0}};
  s21_set_scale(&d_1, 2);
  s21_set_scale(&d_2, 2);

  s21_set_sign(&d_1, 1);
  s21_set_sign(&d_2, 1);

  s21_decimal d_3 = s21_get_null_decimal();

  s21_mul(d_1, d_2, &d_3);

  s21_from_decimal_to_float(d_3, &result);

  ck_assert_float_eq(result, expected);
}
END_TEST

// -0.15 * -1.22 = 0.183
START_TEST(mul_test_5) {
  float v_1 = -0.15f, v_2 = -1.22f, result = 0.0f, expected = 183e-3f;

  s21_decimal d_1 = s21_get_null_decimal(), d_2 = s21_get_null_decimal();
  s21_from_float_to_decimal(v_1, &d_1);
  s21_from_float_to_decimal(v_2, &d_2);

  s21_decimal d_3 = s21_get_null_decimal();

  s21_mul(d_1, d_2, &d_3);

  s21_from_decimal_to_float(d_3, &result);

  ck_assert_float_eq(result, expected);
}
END_TEST

START_TEST(mul_test_6) {
  // 0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x100000}};
  // 0.0000000000000025000000000000
  //  s21_decimal decimal_check = {{0xC41E9000, 0x16BC, 0x0, 0x1C0000}};

  s21_decimal res = {0};

  int code = s21_mul(decimal1, decimal2, &res);

  //  s21_print_decimal(decimal_check);
  //  s21_print_decimal(res);
  ck_assert_int_eq(code, OK);
}
END_TEST

Suite *s21_mul_suite(void) {
  Suite *s;
  s = suite_create("\033[33ms21_mul\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("s21_mul_core");
  tcase_add_test(tc_core, mul_test_1);
  tcase_add_test(tc_core, mul_test_2);
  tcase_add_test(tc_core, mul_test_3);
  tcase_add_test(tc_core, mul_test_4);
  tcase_add_test(tc_core, mul_test_5);
  tcase_add_test(tc_core, mul_test_6);

  suite_add_tcase(s, tc_core);
  return s;
}
