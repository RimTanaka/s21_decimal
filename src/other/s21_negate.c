#include "s21_other.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (!result) return CONVERTATION_ERR;
  int flag = OK;
  int scale = s21_get_scale(value);
  if (scale < 0 || scale > 28) flag = CONVERTATION_ERR;
  if (flag == OK) {
    *result = value;
    s21_set_bit(result, 127, !s21_get_bit(*result, 127));
  }
  return flag;
}
