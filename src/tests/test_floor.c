#include "test.h"

START_TEST(floor_test_1) {
  float value = -1.2, expected = -2.0, result_float = 0;
  s21_decimal float_decimal = s21_get_null_decimal(),
              result_decimal = s21_get_null_decimal();

  s21_from_float_to_decimal(value, &float_decimal);

  s21_floor(float_decimal, &result_decimal);

  s21_from_decimal_to_float(result_decimal, &result_float);

  ck_assert_float_eq(result_float, expected);
}
END_TEST

// -1.2 -> -2
START_TEST(floor_test_2) {
  s21_decimal float_decimal = {{12, 0, 0, 0}},
              expected_decimal = {{2, 0, 0, 0}}, result_decimal = {{0}};

  s21_set_scale(&float_decimal, 1);
  s21_set_sign(&float_decimal, 1);

  s21_set_sign(&expected_decimal, 1);

  s21_floor(float_decimal, &result_decimal);

  ck_assert_int_eq(s21_is_decimal_identical(result_decimal, expected_decimal),
                   1);
}
END_TEST

START_TEST(floor_test_3) {
  s21_decimal float_decimal = {{12, 0, 0, 0}},
              expected_decimal = {{1, 0, 0, 0}}, result_decimal = {{0}};

  s21_set_scale(&float_decimal, 1);

  s21_floor(float_decimal, &result_decimal);

  ck_assert_int_eq(s21_is_decimal_identical(result_decimal, expected_decimal),
                   1);
}
END_TEST

START_TEST(floor_test_4) {
  float value = 1.2, expected = 1.0, result_float = 0;
  s21_decimal float_decimal = s21_get_null_decimal(),
              result_decimal = s21_get_null_decimal();

  s21_from_float_to_decimal(value, &float_decimal);

  s21_floor(float_decimal, &result_decimal);

  s21_from_decimal_to_float(result_decimal, &result_float);

  ck_assert_float_eq(result_float, expected);
}
END_TEST

START_TEST(floor_test_5) {
  // 79228162514264337593543950335
  s21_decimal decimal = {0};
  //  s21_set_sign(decimal, 1);
  s21_big_decimal dec = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0, 0, 0, 0}};
  s21_set_sign_big(&dec, 1);
  s21_to_decimal(dec, &decimal);
  int code = s21_floor(decimal, NULL);

  ck_assert_int_eq(code, 1);
}

Suite *s21_floor_suite(void) {
  Suite *s;
  s = suite_create("\033[33ms21_floor\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("s21_floor_core");
  tcase_add_test(tc_core, floor_test_1);
  tcase_add_test(tc_core, floor_test_2);
  tcase_add_test(tc_core, floor_test_3);
  tcase_add_test(tc_core, floor_test_4);
  tcase_add_test(tc_core, floor_test_5);

  suite_add_tcase(s, tc_core);
  return s;
}
