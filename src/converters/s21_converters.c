#include "s21_converters.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (!dst) return CONVERTATION_ERR;
  if (src < 0) {
    dst->bits[0] = ~src + 1;
  } else {
    dst->bits[0] = src;
  }
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  dst->bits[3] = 0;
  if (src < 0) s21_set_sign(dst, 1);
  return OK;
}
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (!dst) return CONVERTATION_ERR;
  int flag = OK;
  if (s21_get_scale(src) > 0) s21_truncate(src, &src);
  if (src.bits[1] == 0 && src.bits[2] == 0) {
    if (s21_get_bit(src, 31) == 0 && s21_get_bit(src, 127) == 0)
      *dst = src.bits[0];
    else if (s21_get_bit(src, 31) == 0 && s21_get_bit(src, 127) == 1)
      *dst = ~src.bits[0] + 1;
    else if (s21_get_bit(src, 127) == 1 && src.bits[0] == INT_MIN)
      *dst = INT_MIN;
  } else
    flag = CONVERTATION_ERR;
  return flag;
}
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (!dst) return CONVERTATION_ERR;
  double result = 0;
  for (int i = 95; i >= 0; i--) {
    double tmp_powers = pow(2.0, i);
    result += tmp_powers * s21_get_bit(src, i);
  }
  int mashtab = s21_get_scale(src);
  double power = pow(10.0, mashtab);
  result = result / power;
  if (s21_get_bit(src, 127))
    *dst = (float)result * -1;
  else
    *dst = (float)result;
  return OK;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (!dst || isinf(src) || isnan(src)) {
    return CONVERTATION_ERR;
  }
  dst->bits[0] = 0;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  dst->bits[3] = 0;
  int flag = OK;
  if (fabsf(src) > MAX_FLOAT_TO_CONVERT ||
      (fabsf(src) < MIN_FLOAT_TO_CONVERT && fabsf(src) > 0))
    flag = CONVERTATION_ERR;
  if (src == -0.0) {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0x80000000;
    flag = OK;
  }
  if (flag == OK && src != -0.0) {
    int sign = 0;
    char buffer[25];
    sprintf(buffer, "%.6E", src);
    int integer_part = atoi(strtok(buffer, "."));
    if (integer_part < 0) {
      integer_part *= -1;
      sign = 1;
    }
    int fractional_part = atoi(strtok(buffer + 2 + sign, "E"));
    int exponent = atoi(strtok(NULL, "E"));
    integer_part = integer_part * 1000000 + fractional_part;
    if (integer_part != 0) exponent -= 6;
    while (integer_part % 10 == 0 && integer_part != 0) {
      integer_part /= 10;
      exponent++;
    }
    int tmp = 0;
    while (exponent < -28) {
      tmp = integer_part % 10;
      integer_part /= 10;
      exponent++;
    }
    if (tmp >= 5) integer_part++;
    s21_from_int_to_decimal(integer_part, dst);
    s21_decimal _ten = {{10, 0, 0, 0}};
    while (exponent > 0) {
      s21_mul(*dst, _ten, dst);
      exponent--;
    }
    exponent *= -1;
    s21_set_scale(dst, (unsigned int)exponent);
    if (sign) s21_set_sign(dst, 1);
  }
  return flag;
}
