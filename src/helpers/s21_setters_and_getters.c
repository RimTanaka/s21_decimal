#include "s21_helpers.h"

// setters and getters for scale
void s21_set_scale(s21_decimal *num, unsigned value) {
  num->bits[3] &= ~(0xFF << 16);
  num->bits[3] |= (value & 0xFF) << 16;
}

void s21_set_scale_big(s21_big_decimal *num, unsigned value) {
  num->bits[7] &= ~(0xFF << 16);
  num->bits[7] |= (value & 0xFF) << 16;
}

int s21_get_scale(s21_decimal num) { return (num.bits[3] >> 16) & 0x7F; }
int s21_get_scale_big(s21_big_decimal num) {
  return (num.bits[7] >> 16) & 0xFF;
}

// setters and getters for sign
int s21_get_sign(s21_decimal value) {
  return (value.bits[3] & (1u << 31)) != 0;
}

// 0 - possitive, 1 - negative
void s21_set_sign(s21_decimal *num, unsigned value) {
  s21_set_bit(num, 127, value);
}

// 0 - possitive, 1 - negative
void s21_set_sign_big(s21_big_decimal *num, unsigned value) {
  s21_set_bit_big(num, 255, value);
}

// setters and getters for bit
int s21_get_bit_big(s21_big_decimal value, int bit) {
  return (value.bits[bit / 32] >> (bit % 32)) & 1;
}

int s21_get_bit(s21_decimal value, int bit) {
  return (value.bits[bit / 32] >> (bit % 32)) & 1;
}

void s21_set_bit(s21_decimal *num, int bit, int value) {
  if (value) {
    num->bits[bit / 32] |= (1 << (bit % 32));
  } else {
    num->bits[bit / 32] &= ~(1 << (bit % 32));
  }
}

void s21_set_bit_big(s21_big_decimal *num, int bit, unsigned value) {
  if (value) {
    num->bits[bit / 32] |= (1 << (bit % 32));
  } else {
    num->bits[bit / 32] &= ~(1 << (bit % 32));
  }
}
