#include "minunit/minunit.h"
#include "src/field.h"
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

MU_TEST(screen_pos_zero) {
  // Check that the 0th index is translated to a position of (0, 0)
  mu_check(CellScreenPosition(0).x == 0 && CellScreenPosition(0).y == 0);
}

MU_TEST(screen_pos_normal) {
  // Check that the 2002nd index is translated to a position of (20, 20)
  mu_check(CellScreenPosition(2002).x == 20 && CellScreenPosition(2002).y == 20);
}

MU_TEST(buffer_index_normal) {
  // Check that a point at (12, 11) is translated to the 1001st index
  mu_check(BufferIndex(12, 11) == 1001);
}

MU_TEST(buffer_index_boundary) {
  // Check that a point at (0, 21) is translated to the 2000st index
  mu_check(BufferIndex(0, 21) == 2000);
}

MU_TEST(buffer_index_erroneous) {
  // Check that an out-of-bounds click translates to an error code of -1
  mu_check(BufferIndex(-200, 50) == -1);
}

MU_TEST_SUITE(test_suite) {
  // Queue tests
  MU_RUN_TEST(screen_pos_zero);
  MU_RUN_TEST(screen_pos_normal);
  MU_RUN_TEST(buffer_index_normal);
  MU_RUN_TEST(buffer_index_boundary);
  MU_RUN_TEST(buffer_index_erroneous);
}

int main(void) {
  // Run tests and report results
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  return MU_EXIT_CODE;
}
