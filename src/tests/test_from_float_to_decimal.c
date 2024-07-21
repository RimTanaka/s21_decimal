#include "test.h"

START_TEST(ftod_test_1) {
  s21_decimal result_decimal = {{0, 0, 0, 0}};
  float result = 0.;
  float expected = -1.234567;
  float tolerance = 0.001;
  int code =
      s21_from_float_to_decimal(expected, &result_decimal);  // val = temp
  ck_assert_int_eq(OK, code);

  code = s21_from_decimal_to_float(result_decimal, &result);  // val -> res
  ck_assert_int_eq(OK, code);

  ck_assert_float_eq_tol(result, expected, tolerance);
}
END_TEST

START_TEST(ftod_test_2) {
  s21_decimal result_decimal = {{0, 0, 0, 0}};
  float result = 0.;
  float expected = 1.234567;
  float tolerance = 0.001;
  int code =
      s21_from_float_to_decimal(expected, &result_decimal);  // val = temp
  ck_assert_int_eq(OK, code);

  code = s21_from_decimal_to_float(result_decimal, &result);  // val -> res
  ck_assert_int_eq(OK, code);

  ck_assert_float_eq_tol(result, expected, tolerance);
}
END_TEST

START_TEST(ftod_test_3) {
  s21_decimal result_decimal = {{0, 0, 0, 0}};
  float result = 0.;
  float expected = 1.2345678;  // 7 значимых цифр после точки
  float tolerance = 0.001;
  int code =
      s21_from_float_to_decimal(expected, &result_decimal);  // val = temp
  ck_assert_int_eq(OK, code);

  code = s21_from_decimal_to_float(result_decimal, &result);  // val -> res
  ck_assert_int_eq(OK, code);

  ck_assert_float_eq_tol(result, expected, tolerance);
}
END_TEST

START_TEST(ftod_test_4) {
  s21_decimal result_decimal = {{0, 0, 0, 0}};
  float result = 0.;
  float expected = -1.2345678;  // 7 значимых цифр после точки
  float tolerance = 0.001;
  int code =
      s21_from_float_to_decimal(expected, &result_decimal);  // val = temp
  ck_assert_int_eq(OK, code);

  code = s21_from_decimal_to_float(result_decimal, &result);  // val -> res
  ck_assert_int_eq(OK, code);

  ck_assert_float_eq_tol(result, expected, tolerance);
}
END_TEST

START_TEST(ftod_test_5) {
  s21_decimal result_decimal = {{0, 0, 0, 0}};
  float result = 0.;
  float expected = -12345678.0;  // 7 значимых цифр после точки
  float tolerance = 10;
  int code =
      s21_from_float_to_decimal(expected, &result_decimal);  // val = temp
  ck_assert_int_eq(OK, code);

  code = s21_from_decimal_to_float(result_decimal, &result);  // val -> res
  ck_assert_int_eq(OK, code);

  ck_assert_float_eq_tol(result, expected, tolerance);
}
END_TEST

START_TEST(ftod_test_6) {
  float f = 1234567890123456789012345678.0;
  s21_decimal result_decimal = {{0x5000000, 0x62516078, 0x3FD35F1, 0x0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(f, &result);  // val -> res
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result_decimal.bits[i], result.bits[i]);
}

START_TEST(ftod_test_7) {
  float f = 989989898989898989898989898989898989898.9;
  s21_decimal result = {{0, 0, 0, 0}};
  int code = s21_from_float_to_decimal(f, &result);  // f -> res
  ck_assert_int_eq(code, CONVERTATION_ERR);
}

START_TEST(ftod_test_8) {
  float f = 9899898989898989898989898989898989.9f;
  s21_decimal result = {{0, 0, 0, 0}};
  int code = s21_from_float_to_decimal(f, &result);  // f -> res
  ck_assert_int_eq(code, CONVERTATION_ERR);
}

START_TEST(ftod_test_unnormal1) {
  float f = 0.0;
  s21_decimal result;
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  int code = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(ftod_test_unnormal2) {
  float f = -0.0;
  s21_decimal result;
  s21_decimal check = {{0x0, 0x0, 0x0, 0x80000000}};

  int code = s21_from_float_to_decimal(f, &result);

  int sign_check = s21_get_sign(check);
  int sign_result = s21_get_sign(result);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(sign_check, sign_result);
}
END_TEST

START_TEST(ftod_test_unnormal3) {
  float f = INFINITY;
  s21_decimal result;

  int code = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(code, CONVERTATION_ERR);
}
END_TEST

START_TEST(ftod_test_unnormal4) {
  float f = -INFINITY;
  s21_decimal result;

  int code = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(code, CONVERTATION_ERR);
}
END_TEST

START_TEST(ftod_test_unnormal5) {
  float f = NAN;
  s21_decimal result;

  int code = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(code, CONVERTATION_ERR);
}
END_TEST

START_TEST(ftod_test_unnormal6) {
  float f = -NAN;
  s21_decimal result;

  int code = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(code, CONVERTATION_ERR);
}
END_TEST

START_TEST(ftod_test_unnormal7) {
  float f = -1.91731719E-25;
  s21_decimal result;

  int code = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(code, OK);
}
END_TEST

// 7.0000000000000032

Suite *s21_ftod_suite(void) {
  Suite *s;
  s = suite_create("\033[33ms21_ftod\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("s21_ftod_core");
  tcase_add_test(tc_core, ftod_test_1);
  tcase_add_test(tc_core, ftod_test_2);
  tcase_add_test(tc_core, ftod_test_3);
  tcase_add_test(tc_core, ftod_test_4);
  tcase_add_test(tc_core, ftod_test_5);
  tcase_add_test(tc_core, ftod_test_6);
  tcase_add_test(tc_core, ftod_test_7);
  tcase_add_test(tc_core, ftod_test_8);
  tcase_add_test(tc_core, ftod_test_unnormal1);
  tcase_add_test(tc_core, ftod_test_unnormal2);
  tcase_add_test(tc_core, ftod_test_unnormal3);
  tcase_add_test(tc_core, ftod_test_unnormal4);
  tcase_add_test(tc_core, ftod_test_unnormal5);
  tcase_add_test(tc_core, ftod_test_unnormal6);
  tcase_add_test(tc_core, ftod_test_unnormal7);

  suite_add_tcase(s, tc_core);
  return s;
}
