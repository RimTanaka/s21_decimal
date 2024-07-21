#include "s21_other.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  if (!result) return CONVERTATION_ERR;
  int code = OK;
  unsigned int sign = s21_get_sign(value);
  if (sign) s21_set_sign(&value, 0);  // abs(value)

  s21_decimal fract = s21_get_null_decimal(), half_of_one = {{5, 0, 0, 0}},
              one = {{1, 0, 0, 0}};
  s21_set_scale(&half_of_one, 1);
  if (s21_truncate(value, result) || s21_sub(value, *result, &fract)) {
    code = 1;
  }

  if (!code && s21_is_greater_or_equal(fract, half_of_one)) {
    s21_add(*result, one, result);
  }
  s21_set_sign(result, sign);
  return code;
}
