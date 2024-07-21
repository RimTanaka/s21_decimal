#include "test.h"

// 12 / 2 = 6
START_TEST(div_test_1) {
  int value_1 = 12, value_2 = 2, result = 0, expected = 6;
  s21_decimal value_1_decimal = s21_get_null_decimal(),
              value_2_decimal = s21_get_null_decimal(),
              value_3_decimal = s21_get_null_decimal();

  s21_from_int_to_decimal(value_1, &value_1_decimal);
  s21_from_int_to_decimal(value_2, &value_2_decimal);

  s21_div(value_1_decimal, value_2_decimal, &value_3_decimal);

  s21_from_decimal_to_int(value_3_decimal, &result);

  ck_assert_float_eq_tol(result, expected, 0.001);
}
END_TEST

// 0.6 / 0.6 = 1.0
START_TEST(div_test_2) {
  float value_1 = 0.6f, value_2 = 0.6f, result = 0.0f, expected = 1.0f;
  s21_decimal value_1_decimal = s21_get_null_decimal(),
              value_2_decimal = s21_get_null_decimal(),
              value_3_decimal = s21_get_null_decimal();

  s21_from_float_to_decimal(value_1, &value_1_decimal);
  s21_from_float_to_decimal(value_2, &value_2_decimal);

  s21_div(value_1_decimal, value_2_decimal, &value_3_decimal);

  s21_from_decimal_to_float(value_3_decimal, &result);

  ck_assert_float_eq_tol(result, expected, 0.001);
}
END_TEST

// 0.4 / 2.0 = 0.2
START_TEST(div_test_3) {
  float value_1 = 40e-2, value_2 = 20e-1, result = 0.0f, expected = 0.2;
  s21_decimal value_1_decimal = s21_get_null_decimal(),
              value_2_decimal = s21_get_null_decimal(),
              value_3_decimal = s21_get_null_decimal();

  s21_from_float_to_decimal(value_1, &value_1_decimal);
  s21_from_float_to_decimal(value_2, &value_2_decimal);

  s21_div(value_1_decimal, value_2_decimal, &value_3_decimal);

  s21_from_decimal_to_float(value_3_decimal, &result);

  ck_assert_float_eq_tol(result, expected, 0.001);
}
END_TEST

// -0.6 / 0.3 = -2.0
START_TEST(div_test_4) {
  float result = 0.0f, expected = -2.0f;

  s21_decimal d_1 = {{60, 0, 0, 0}}, d_2 = {{3, 0, 0, 0}};
  s21_set_scale(&d_1, 2);
  s21_set_scale(&d_2, 1);

  s21_set_sign(&d_1, 1);

  s21_decimal d_3 = s21_get_null_decimal();

  s21_div(d_1, d_2, &d_3);

  s21_from_decimal_to_float(d_3, &result);

  ck_assert_float_eq_tol(result, expected, 0.001);
}
END_TEST

// -0.6 / 0.3 = -2.0
START_TEST(div_test_5) {
  float v_1 = -0.6f, v_2 = 0.3f, result = 0.0f, expected = -2.0f;

  s21_decimal d_1 = s21_get_null_decimal(), d_2 = s21_get_null_decimal();
  s21_from_float_to_decimal(v_1, &d_1);
  s21_from_float_to_decimal(v_2, &d_2);

  s21_decimal d_3 = s21_get_null_decimal();

  s21_div(d_1, d_2, &d_3);

  s21_from_decimal_to_float(d_3, &result);

  ck_assert_float_eq_tol(result, expected, 0.001);
}
END_TEST

// -0.3 / -0.2 = 1.5
START_TEST(div_test_6) {
  float result = 0.0f, expected = 1.5f;

  s21_decimal d_1 = {{30, 0, 0, 0}}, d_2 = {{2, 0, 0, 0}};
  s21_set_scale(&d_1, 2);
  s21_set_scale(&d_2, 1);

  s21_set_sign(&d_1, 1);
  s21_set_sign(&d_2, 1);

  s21_decimal d_3 = s21_get_null_decimal();

  s21_div(d_1, d_2, &d_3);

  s21_from_decimal_to_float(d_3, &result);

  ck_assert_float_eq_tol(result, expected, 0.001);
}
END_TEST

// -0.3 / -0.2 = 1.5
START_TEST(div_test_7) {
  float v_1 = -0.3f, v_2 = -0.2f, result = 0.0f, expected = 1.5f;

  s21_decimal d_1 = s21_get_null_decimal(), d_2 = s21_get_null_decimal();
  s21_from_float_to_decimal(v_1, &d_1);
  s21_from_float_to_decimal(v_2, &d_2);

  s21_decimal d_3 = s21_get_null_decimal();

  s21_div(d_1, d_2, &d_3);

  s21_from_decimal_to_float(d_3, &result);

  ck_assert_float_eq_tol(result, expected, 0.001);
}
END_TEST

START_TEST(div_test_8) {
  s21_decimal d_1 = {{-1, -1, -1, 0}}, d_2 = {{1, 0, 0, 0}};
  s21_set_scale(&d_2, 1);

  s21_decimal d_3 = s21_get_null_decimal();

  int code = s21_div(d_1, d_2, &d_3);

  ck_assert_int_eq(code, 1);
}
END_TEST

// (int)100 / (int)10 = 10
START_TEST(divide_by_10_test_1) {
  s21_big_decimal test = {{100, 0, 0, 0, 0, 0, 0, 0}};

  int ost;
  s21_div_10(&test, &ost);

  ck_assert_int_eq(test.bits[0], 10);

  for (int i = 1; i < 8; i++) {
    ck_assert_int_eq(test.bits[i], 0);
  }
}
END_TEST

// ()1.28 / 10 -> 0
START_TEST(divide_by_10_test_2) {
  s21_big_decimal test = {{128, 0, 0, 0, 0, 0, 0, 0}};
  s21_set_scale_big(&test, 2);

  int ost;
  s21_div_10(&test, &ost);

  ck_assert_int_eq(test.bits[0], 12);

  for (int i = 1; i < 7; i++) {
    ck_assert_int_eq(test.bits[i], 0);
  }
}
END_TEST

Suite *s21_div_suite(void) {
  Suite *s;
  s = suite_create("\033[33ms21_div\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("s21_div_core");
  tcase_add_test(tc_core, div_test_1);
  tcase_add_test(tc_core, div_test_2);
  tcase_add_test(tc_core, div_test_3);
  tcase_add_test(tc_core, div_test_4);
  tcase_add_test(tc_core, div_test_5);
  tcase_add_test(tc_core, div_test_6);
  tcase_add_test(tc_core, div_test_7);
  tcase_add_test(tc_core, div_test_8);
  tcase_add_test(tc_core, divide_by_10_test_1);
  tcase_add_test(tc_core, divide_by_10_test_2);

  suite_add_tcase(s, tc_core);
  return s;
}
