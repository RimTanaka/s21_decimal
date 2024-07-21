#ifndef HELPERS_H
#define HELPERS_H

#include "../s21_decimal.h"

/******** converters from and to big decimal ********/
void s21_to_big_decimal(s21_decimal src, s21_big_decimal *result);

// Возвращает 1 если overflow, иначе 0
int s21_to_decimal(s21_big_decimal src, s21_decimal *result);

/******** setters and getters for scale ********/
void s21_set_scale(s21_decimal *num, unsigned value);
void s21_set_scale_big(s21_big_decimal *num, unsigned value);
int s21_get_scale(s21_decimal num);
int s21_get_scale_big(s21_big_decimal num);

/******** setters and getters for sign ********/
int s21_get_sign(s21_decimal value);
void s21_set_sign(s21_decimal *num, unsigned value);
void s21_set_sign_big(s21_big_decimal *num, unsigned value);

/******** setters and getters for bit ********/
int s21_get_bit_big(s21_big_decimal value, int bit);
int s21_get_bit(s21_decimal value, int bit);
void s21_set_bit(s21_decimal *num, int bit, int value);
void s21_set_bit_big(s21_big_decimal *num, int bit, unsigned value);

/******** manipulations with decimal ********/

int s21_shift_left_big(s21_big_decimal value, int num, s21_big_decimal *result);
void s21_swap(s21_decimal *value_1, s21_decimal *value_2);
void s21_copy_decimal(s21_decimal src, s21_decimal *dst);

/********  normalization ********/

// нормализует два decimal числа, возвращает 1 в случае overflow, 0 в случае
// успеха
int s21_normalize(s21_big_decimal *v1, s21_big_decimal *v2);

// return 1 if any errors, else return 0

// возвращает 1 в случае если src не умещается в decimal
int s21_scale_update(s21_big_decimal *src, int scale);

// возвращает 1 в случае если result не умещается в decimal
int s21_multiply_by_10(s21_big_decimal src, s21_big_decimal *result);

/******** debug ********/
// void print_big_decimal(s21_big_decimal value);
// void print_decimal(s21_decimal value);

/******** others ********/
// Возвращает 1 если big_decimal не умещается в decimal, 0 если иначе
int s21_overflow_check(s21_big_decimal *value);

s21_decimal s21_get_null_decimal();
s21_big_decimal s21_get_null_big_decimal();

/******** Banking rounding ********/

// банковское огругление к ближайшему четному числу, возвращает 1 в случае
// overflow
int s21_bank(s21_big_decimal *value);

void s21_div_10(s21_big_decimal *value, int *ost);

/// Функции для деления
int s21_compare_big(s21_big_decimal val1, s21_big_decimal val2);
int s21_get_length_big(s21_big_decimal value);
void s21_add_bit(s21_big_decimal *value, int bit);
void s21_stolbik(s21_big_decimal value_1, s21_big_decimal value_2,
                 s21_big_decimal *result, s21_big_decimal *ost);

#endif
