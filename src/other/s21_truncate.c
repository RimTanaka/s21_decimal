#include "s21_other.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (!result) return 1;
  int code = OK;

  // копируем память из value в result
  for (int i = 0; i < 4; i++) {
    result->bits[i] = value.bits[i];
  }

  // объявляем временную переменную big
  s21_big_decimal temp = s21_get_null_big_decimal();
  s21_to_big_decimal(value, &temp);

  int scale = s21_get_scale_big(temp);
  if (scale < 0 || scale > 28) code = CONVERTATION_ERR;
  if (code == OK && scale > 0) {
    for (int i = 0; i < scale; ++i) {
      int ost;
      s21_div_10(&temp, &ost);
    }

    s21_set_scale_big(&temp, 0);
    code = s21_to_decimal(temp, result);
  }
  return code;
}
