#include "test.h"

// for all scale range
START_TEST(dtof_test_1) {
  int code, rnd = rand();
  s21_decimal test = {{rnd, 0, 0, 0}};
  float tolerance = rnd * 0.01;
  for (int j = 0; j < 100; j++) {
    rnd = rand();
    test.bits[0] = rnd;
    for (int i = 0; i < 29; i++) {
      s21_set_scale(&test, i);
      float test_float = (float)rnd / pow(10, i);
      float result_float = 0.0;
      code = s21_from_decimal_to_float(test, &result_float);
      ck_assert_float_eq_tol(test_float, result_float, tolerance);
      ck_assert_int_eq(code, OK);
    }
  }
}
END_TEST

// MAX DEC -> Float
START_TEST(dtof_test_2) {
  s21_decimal test = {{-1, -1, -1, 0}};
  float check_res = 79228162514264337593543950335.0f;
  float result_float = 0.0;
  int code;
  code = s21_from_decimal_to_float(test, &result_float);
  ck_assert_float_eq(check_res, result_float);
  ck_assert_int_eq(code, OK);
}
END_TEST

START_TEST(dtof_test_3) {
  // -1012308.0780731047111141553152
  s21_decimal decimal = {{0x6F5AF400, 0xBC59A53E, 0x20B59DBC, 0x80160000}};
  float check_res = -1012308.0f;

  float result_float = 0.0;
  int code;
  code = s21_from_decimal_to_float(decimal, &result_float);

  ck_assert_float_eq_tol(check_res, result_float, 0.1);
  ck_assert_int_eq(code, OK);

  //  test_from_decimal_to_float(decimal, check);
}

Suite *s21_dtof_suite(void) {
  Suite *s;
  s = suite_create("\033[33ms21_dtof\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("s21_dtof_core");
  tcase_add_test(tc_core, dtof_test_1);
  tcase_add_test(tc_core, dtof_test_2);
  tcase_add_test(tc_core, dtof_test_3);

  suite_add_tcase(s, tc_core);
  return s;
}
