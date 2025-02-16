#include "s21_helpers.h"

void s21_to_big_decimal(s21_decimal src, s21_big_decimal* result) {
  for (int i = 0; i < 3; i++) result->bits[i] = src.bits[i];
  for (int i = 3; i < 7; i++) result->bits[i] = 0;
  result->bits[7] = src.bits[3];
}

int s21_to_decimal(s21_big_decimal src, s21_decimal* result) {
  int result_code = OK;
  if ((result_code = s21_overflow_check(&src)) && s21_get_scale_big(src) > 0)
    result_code = s21_bank(&src);  // банк окргул (возвр Err при переполнении)
  if (result_code == OK) {
    *result = s21_get_null_decimal();
    for (int i = 0; i < 3; i++) result->bits[i] = src.bits[i];
    result->bits[3] = src.bits[7];
    s21_set_scale(result, s21_get_scale_big(src));
  }
  return result_code;
}
