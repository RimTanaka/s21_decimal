#include "test.h"

int s21_is_decimal_identical(s21_decimal v1, s21_decimal v2) {
  int is_eq = 1;

  for (int i = 0; i < 4; i++) {
    if (v1.bits[i] != v2.bits[i]) {
      is_eq = 0;
      break;
    }
  }

  return is_eq;
}

int main() {
  srand(time(NULL));
  int all = 0, successed = 0, failed = 0;
  Suite *suite[] = {s21_floor_suite(),
                    s21_negate_suite(),
                    s21_round_suite(),
                    s21_truncate_suite(),
                    s21_dtoi_suite(),
                    s21_dtof_suite(),
                    s21_add_suite(),
                    s21_sub_suite(),
                    s21_shift_left_suite(),
                    s21_normalize_suite(),
                    s21_itod_suite(),
                    s21_ftod_suite(),
                    s21_compare_suite(),
                    s21_bank_round_suite(),
                    s21_mul_suite(),
                    s21_div_suite(),
                    NULL};

  for (int i = 0; suite[i] != NULL; i++) {
    SRunner *sr = srunner_create(suite[i]);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    all += srunner_ntests_run(sr);
    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }

  successed = all - failed;

  printf(
      "========= ALL: %d ========= SUCCESSED: %d ========= FAILED: %d "
      "=========\n",
      all, successed, failed);
  return failed == 0 ? 0 : 1;
}
