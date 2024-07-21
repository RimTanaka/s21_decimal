#include "s21_other.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (!result) return CONVERTATION_ERR;
  int sign = s21_get_sign(value);
  int flag = OK;
  int scale = s21_get_scale(value);
  if (scale < 0 || scale > 28) flag = CONVERTATION_ERR;
  if (flag == OK) {
    // получаем unsigned_value
    s21_decimal unsigned_value = s21_get_null_decimal();
    s21_copy_decimal(value, &unsigned_value);
    s21_set_sign(&unsigned_value, 0);

    // получаем модуль truncated_unsigned_value
    s21_decimal truncated_unsigned_value = s21_get_null_decimal();
    s21_copy_decimal(unsigned_value, &truncated_unsigned_value);

    // отбрасываем всю дробную часть
    s21_truncate(truncated_unsigned_value, &truncated_unsigned_value);

    s21_decimal fractal = s21_get_null_decimal(),
                zero_decimal = s21_get_null_decimal();

    // получаем дробную часть
    flag = s21_sub(unsigned_value, truncated_unsigned_value, &fractal);

    // если дробная часть больше 0 и число было отрицательным то добавляем
    // единицу
    if (flag == OK && s21_is_greater(fractal, zero_decimal) && sign == 1) {
      s21_decimal one = {{1, 0, 0, 0}};
      flag = s21_add(truncated_unsigned_value, one, &truncated_unsigned_value);
    }

    s21_set_sign(&truncated_unsigned_value, sign);

    s21_copy_decimal(truncated_unsigned_value, result);
  }

  return flag;  // TODO неверно, должно быть преобразование из big_decimal и
                // проверка overflow
}
