#include "test.h"

// conversion with sign flip
START_TEST(dtoi_test_1) {
  int y = 0, code = 3, rnd = rand();
  s21_decimal test = {{rnd, 0, 0, 0}};

  code = s21_from_decimal_to_int(test, &y);
  ck_assert_int_eq(rnd, y);
  ck_assert_int_eq(code, 0);

  test.bits[3] |= (1u << 31);
  code = s21_from_decimal_to_int(test, &y);
  ck_assert_int_eq((rnd * -1), y);
  ck_assert_int_eq(code, 0);
}
END_TEST

// incorrect conversion with overflow
START_TEST(dtoi_test_2) {
  int y = 0;
  int rnd = rand();
  s21_decimal test = {{rnd, rnd, 0, 0}};
  int code = s21_from_decimal_to_int(test, &y);

  // код ошибки должен быть 1
  ck_assert_int_eq(code, 1);

  // переменная для записи должна остаться неизменной
  ck_assert_int_eq(0, y);
}
END_TEST

// conversion with truncate decimal part after dot
START_TEST(dtoi_test_3) {
  int scale = 2, y = 0, z = 128;

  s21_decimal test = {
      {z, 0, 0,
       0}};  // z = 128, scale = 2, float value from decimal = 128 / 10^2 = 1.28
  s21_set_scale(&test, scale);

  int code = s21_from_decimal_to_int(test, &y);  // 1.28 to int = 1

  // код ошибки должен быть 0
  ck_assert_int_eq(code, 0);

  // переменная для записи должна остаться неизменной
  ck_assert_int_eq(1, y);
}
END_TEST

// conversion with truncate decimal part after dot
START_TEST(dtoi_test_4) {
  int scale = 1 + (int)(28.0 * rand() / (RAND_MAX + 1.0));
  int y = 0;
  int rnd = rand();
  int expected = (int)(rnd / (pow(10, scale)));  // (int) (rnd / 10^scale)
  s21_decimal test = {{rnd, 0, 0, 0}};
  s21_set_scale(&test, scale);

  int code = s21_from_decimal_to_int(test, &y);

  // код ошибки должен быть 0
  ck_assert_int_eq(code, 0);

  // переменная для записи должна остаться неизменной
  ck_assert_int_eq(expected, y);
}
END_TEST

START_TEST(dtoi_test_5) {
  int y = 0, code = 3, rnd = 1u << 31;
  s21_decimal test = {{rnd, 0, 0, 1u << 31}};

  code = s21_from_decimal_to_int(test, &y);
  ck_assert_int_eq(rnd, y);
  ck_assert_int_eq(code, 0);

  test.bits[3] |= (1u << 31);
  code = s21_from_decimal_to_int(test, &y);
  ck_assert_int_eq((rnd * -1), y);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(dtoi_test_6) {
  float y = 875.45612345;
  int answer;
  s21_decimal test = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(y, &test);
  int code = s21_from_decimal_to_int(test, &answer);
  printf("%d", answer);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(875, answer);
}
END_TEST

Suite *s21_dtoi_suite(void) {
  Suite *s;
  s = suite_create("\033[33ms21_dtoi\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("s21_dtoi_core");
  tcase_add_test(tc_core, dtoi_test_1);
  tcase_add_test(tc_core, dtoi_test_2);
  tcase_add_test(tc_core, dtoi_test_3);
  tcase_add_test(tc_core, dtoi_test_4);
  tcase_add_test(tc_core, dtoi_test_5);
  tcase_add_test(tc_core, dtoi_test_6);

  suite_add_tcase(s, tc_core);
  return s;
}
