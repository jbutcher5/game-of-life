#include "minunit/minunit.h"
#include "src/field.h"
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

MU_TEST(screen_pos_zero) {
  mu_check(CellScreenPosition(0).x == 0 && CellScreenPosition(0).y == 0);
}

MU_TEST(screen_pos_normal) {
  mu_check(CellScreenPosition(2002).x == 20 && CellScreenPosition(2002).y == 20);
}

MU_TEST(buffer_index_normal) {
  mu_check(BufferIndex(12, 11) == 1001);
}

MU_TEST(buffer_index_boundary) {
  mu_check(BufferIndex(0, 21) == 2000);
}

MU_TEST(buffer_index_erroneous) {
  mu_check(BufferIndex(-200, 50) == -1);
}

MU_TEST_SUITE(test_suite) {
  MU_RUN_TEST(screen_pos_zero);
  MU_RUN_TEST(screen_pos_normal);
  MU_RUN_TEST(buffer_index_normal);
  MU_RUN_TEST(buffer_index_boundary);
  MU_RUN_TEST(buffer_index_erroneous);
}

int main(void) {
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  return MU_EXIT_CODE;
}
