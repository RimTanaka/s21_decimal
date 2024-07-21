#include "s21_compares.h"

// операторы сравнения
int s21_compare(s21_decimal val_1, s21_decimal val_2) {
  int flag = 5;
  int sign_val_1 = s21_get_sign(val_1);
  int sign_val_2 = s21_get_sign(val_2);

  // Обработка случая +0 и -0
  if (s21_is_zero(val_1) && s21_is_zero(val_2)) {
    flag = 0;
  }

  if (flag == 5 && sign_val_1 != sign_val_2) {
    flag = sign_val_1 ? -1 : 1;
  }

  if (flag == 5) {
    s21_big_decimal big_val1, big_val2;
    s21_to_big_decimal(val_1, &big_val1);
    s21_to_big_decimal(val_2, &big_val2);

    s21_normalize(&big_val1, &big_val2);

    // Сравнение битов от старшего к младшему, исключая бит знака
    flag = s21_compare_big(big_val1, big_val2);

    // Сравнение старшего слова без учета бита знака
    int value_1 = big_val1.bits[7] & 0x7FFFFFFF;
    int value_2 = big_val2.bits[7] & 0x7FFFFFFF;
    if (flag == 5 && (unsigned)value_1 > (unsigned)value_2) flag = 1;
    if (flag == 5 && (unsigned)value_1 < (unsigned)value_2) flag = -1;
    if (flag == 5) flag = OK;
  }
  if (sign_val_1 && sign_val_2 && flag != 0) flag *= -1;
  return flag;
}

int s21_is_zero(s21_decimal value) {
  return value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0;
}

int s21_is_less(s21_decimal val_1, s21_decimal val_2) {
  return s21_compare(val_1, val_2) == -1;
}

int s21_is_less_or_equal(s21_decimal val_1, s21_decimal val_2) {
  int cmp = s21_compare(val_1, val_2);
  return cmp == -1 || cmp == 0;
}

int s21_is_greater(s21_decimal val_1, s21_decimal val_2) {
  return s21_compare(val_1, val_2) == 1;
}

int s21_is_greater_or_equal(s21_decimal val_1, s21_decimal val_2) {
  int cmp = s21_compare(val_1, val_2);
  return cmp == 1 || cmp == 0;
}

int s21_is_equal(s21_decimal val_1, s21_decimal val_2) {
  return s21_compare(val_1, val_2) == 0;
}

int s21_is_not_equal(s21_decimal val_1, s21_decimal val_2) {
  return s21_compare(val_1, val_2) != 0;
}
