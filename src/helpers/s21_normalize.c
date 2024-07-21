#include "s21_helpers.h"

int s21_normalize(s21_big_decimal *v1, s21_big_decimal *v2) {
  int code = 5, scale_v1 = s21_get_scale_big(*v1),
      scale_v2 = s21_get_scale_big(*v2);

  if (scale_v1 == scale_v2) code = OK;

  if (code == 5) {
    int scale_max = scale_v1 > scale_v2 ? scale_v1 : scale_v2;

    if (s21_scale_update(v1, scale_max) || s21_scale_update(v2, scale_max)) {
      code = 1;
    } else {
      code = OK;
    }
  }
  return code;
}

int s21_scale_update(s21_big_decimal *src, int scale) {
  int code = OK;
  int current_scale = s21_get_scale_big(*src);
  if (scale < 0 || scale > 28) code = CONVERTATION_ERR;
  while (current_scale < scale && code == OK) {
    s21_multiply_by_10(*src, src);
    current_scale++;
  }
  s21_set_scale_big(src, current_scale);
  return code;
}

int s21_multiply_by_10(s21_big_decimal src, s21_big_decimal *result) {
  s21_big_decimal v1 = s21_get_null_big_decimal(),
                  v2 = s21_get_null_big_decimal();

  s21_shift_left_big(src, 3, &v1);  // умножение на 8
  s21_shift_left_big(src, 1, &v2);  // Умножение на 2
  for (int i = 0, temp = 0; i < 224; i++) {
    int result_bit = s21_get_bit_big(v1, i) + s21_get_bit_big(v2, i) + temp;
    temp = result_bit / 2;
    result_bit %= 2;
    s21_set_bit_big(result, i, result_bit);
  }
  return s21_overflow_check(result);
}

// int normalize_non_big(s21_decimal *v1, s21_decimal *v2) {
//   int code = OK;
//   s21_big_decimal temp_1, temp_2;

//   s21_to_big_decimal(*v1, &temp_1);
//   s21_to_big_decimal(*v2, &temp_2);

//   code = s21_normalize(&temp_1, &temp_2);

//   if (code || s21_to_decimal(temp_1, v1) || s21_to_decimal(temp_2, v2)) {
//     code = 1;
//   }
//   return code;
// }
