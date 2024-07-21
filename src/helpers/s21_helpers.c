#include "s21_helpers.h"

// debug
// void print_big_decimal(s21_big_decimal value) {
//   for (int i = 255; i >= 0; i--) {
//     if ((i < 240 && i > 223) || (i < 255 && i > 247)) {
//       printf("*");
//     } else {
//       printf("%d", get_bit_big(value, i));
//     }
//     if (i == 32 || i == 64 || i == 96 || i == 128 || i == 160 || i == 224)
//       printf(" ");
//   }
//   printf("\n");
// }
//
// void print_decimal(s21_decimal value) {
//  for (int i = 127; i >= 0; i--) {
//    if ((i < 112 && i > 95) || (i < 127 && i > 119)) {
//      printf("*");
//    } else {
//      printf("%d", get_bit(value, i));
//    }
//    if (i == 32 || i == 64 || i == 96) printf(" ");
//  }
//  printf("\n");
//}

// manipulations with decimal

int s21_shift_left_big(s21_big_decimal value, int num,
                       s21_big_decimal* result) {
  *result = s21_get_null_big_decimal();
  for (int i = 0; i < 224 - num; i++) {
    s21_set_bit_big(result, i + num, s21_get_bit_big(value, i));
  }

  return OK;
}

void s21_swap(s21_decimal* value_1, s21_decimal* value_2) {
  s21_decimal buf = *value_1;
  *value_1 = *value_2;
  *value_2 = buf;
}

void s21_copy_decimal(s21_decimal src, s21_decimal* dst) {
  for (int i = 0; i < 4; i++) {
    dst->bits[i] = src.bits[i];
  }
}

s21_decimal s21_get_null_decimal() {
  s21_decimal result = {{0, 0, 0, 0}};
  return result;
}

s21_big_decimal s21_get_null_big_decimal() {
  s21_big_decimal result = {{0}};
  for (size_t i = 0; i < 8; i++) result.bits[i] = 0;
  return result;
}

// other
int s21_overflow_check(s21_big_decimal* value) {
  return value->bits[3] || value->bits[4] || value->bits[5] || value->bits[6];
}

void s21_div_10(s21_big_decimal* value, int* ost) {
  unsigned long long remainder = 0;
  for (int i = 6; i >= 0; --i) {
    unsigned long long current = (remainder << 32) | value->bits[i];
    value->bits[i] = current / 10;
    remainder = current % 10;
  }
  *ost = (int)remainder;
  if (s21_get_scale_big(*value) > 0)
    s21_set_scale_big(value, s21_get_scale_big(*value) - 1);
}

int s21_bank(s21_big_decimal* value) {
  int err = OK;
  int ost = 0;
  while ((s21_overflow_check(value) && s21_get_scale_big(*value) > 0) ||
         s21_get_scale_big(*value) > 28) {
    s21_div_10(value, &ost);
  }
  if (s21_overflow_check(value)) err = 1;
  if (!err && (ost > 5 || (ost == 5 && s21_get_bit_big(*value, 0)))) {
    for (int i = 0, temp = 1; i < 224; i++) {
      int result_bit = s21_get_bit_big(*value, i) + temp;
      temp = result_bit / 2;
      result_bit %= 2;
      s21_set_bit_big(value, i, result_bit);
    }
  }
  if (s21_overflow_check(value)) err = 1;
  return err;
}

int s21_compare_big(s21_big_decimal val1, s21_big_decimal val2) {
  int result_code = 0;
  for (int i = 223; i >= 0 && !result_code; i--) {
    result_code = s21_get_bit_big(val1, i) - s21_get_bit_big(val2, i);
  }
  return result_code;
}

int s21_get_length_big(s21_big_decimal value) {
  int result = 0;
  for (int i = 223; i >= 0 && !result; i--) {
    if (s21_get_bit_big(value, i)) result = i + 1;
  }
  return result;
}

void s21_add_bit(s21_big_decimal* value, int bit) {
  s21_shift_left_big(*value, 1, value);
  for (int i = 0, temp = 1; i < 224 && bit; i++) {
    int result_bit = s21_get_bit_big(*value, i) + temp;
    temp = result_bit / 2;
    result_bit %= 2;
    s21_set_bit_big(value, i, result_bit);
  }
}

void s21_stolbik(s21_big_decimal value_1, s21_big_decimal value_2,
                 s21_big_decimal* result, s21_big_decimal* ost) {
  if (s21_compare_big(value_1, value_2) == -1) {
    *result = s21_get_null_big_decimal();
    *ost = value_1;
    return;
  }
  int length = s21_get_length_big(value_1);
  int count = 0;
  int flag = 0;
  *ost = s21_get_null_big_decimal();
  while (count < length) {
    int iterations = 0;
    for (int i = length - 1 - count;
         i >= 0 && s21_compare_big(*ost, value_2) == -1; i--) {
      s21_add_bit(ost, s21_get_bit_big(value_1, i));
      iterations++;
      if (flag && iterations > 1) s21_add_bit(result, 0);
    }
    count += iterations;
    int buf2 = s21_compare_big(*ost, value_2);
    for (int i = 0, temp = 0; i < 224 && buf2 != -1; i++) {
      int result_bit =
          s21_get_bit_big(*ost, i) - s21_get_bit_big(value_2, i) - temp;
      temp = result_bit < 0;
      if (temp) result_bit += 2;
      s21_set_bit_big(ost, i, result_bit);
    }
    s21_add_bit(result, buf2 != -1);
    flag = 1;
  }
}
