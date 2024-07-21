#include "test.h"

// 1.2 - 0.2 = 1.0
START_TEST(sub_test_1) {
  float value_1 = 12e-1f, value_2 = 2e-1f, value_3 = 0.0f, expected = 1.0f;
  s21_decimal value_1_decimal = s21_get_null_decimal(),
              value_2_decimal = s21_get_null_decimal(),
              value_3_decimal = s21_get_null_decimal();

  s21_from_float_to_decimal(value_1, &value_1_decimal);
  s21_from_float_to_decimal(value_2, &value_2_decimal);

  s21_sub(value_1_decimal, value_2_decimal, &value_3_decimal);

  s21_from_decimal_to_float(value_3_decimal, &value_3);

  ck_assert_float_eq(value_3, expected);
}
END_TEST

// 1.2 - 0.2 = 1.0
START_TEST(sub_test_2) {
  float result = 0.0f, expected = 1.08f;

  // d_1 = 1.2, d_2 = 0.12, d3 = d_1 - d_2 = 1.08
  s21_decimal d_1 = {{12, 0, 0, 0}}, d_2 = {{12, 0, 0, 0}};
  s21_set_scale(&d_1, 1);
  s21_set_scale(&d_2, 2);

  s21_decimal d_3 = s21_get_null_decimal();

  s21_sub(d_1, d_2, &d_3);

  s21_from_decimal_to_float(d_3, &result);

  ck_assert_float_eq(result, expected);
}
END_TEST

// -0.103 - 0.104 = -0.207
START_TEST(sub_test_3) {
  float value_1 = -103e-3f, value_2 = 104e-3f, value_3 = 0.0f,
        expected = -0.207f;
  s21_decimal value_1_decimal = s21_get_null_decimal(),
              value_2_decimal = s21_get_null_decimal(),
              value_3_decimal = s21_get_null_decimal();

  s21_from_float_to_decimal(value_1, &value_1_decimal);
  s21_from_float_to_decimal(value_2, &value_2_decimal);

  s21_sub(value_1_decimal, value_2_decimal, &value_3_decimal);

  s21_from_decimal_to_float(value_3_decimal, &value_3);

  ck_assert_float_eq(value_3, expected);
}
END_TEST

// -0.103 - (-0.104) = 0.001
START_TEST(sub_test_4) {
  float value_1 = -103e-3f, value_2 = -104e-3f, value_3 = 0.0f,
        expected = 0.001f;
  s21_decimal value_1_decimal = s21_get_null_decimal(),
              value_2_decimal = s21_get_null_decimal(),
              value_3_decimal = s21_get_null_decimal();

  s21_from_float_to_decimal(value_1, &value_1_decimal);
  s21_from_float_to_decimal(value_2, &value_2_decimal);

  s21_sub(value_1_decimal, value_2_decimal, &value_3_decimal);

  s21_from_decimal_to_float(value_3_decimal, &value_3);

  ck_assert_float_eq(value_3, expected);
}
END_TEST

Suite *s21_sub_suite(void) {
  Suite *s;
  s = suite_create("\033[33ms21_sub\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("s21_sub_core");
  tcase_add_test(tc_core, sub_test_1);
  tcase_add_test(tc_core, sub_test_2);
  tcase_add_test(tc_core, sub_test_3);
  tcase_add_test(tc_core, sub_test_4);

  suite_add_tcase(s, tc_core);
  return s;
}
