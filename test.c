#include "minunit/minunit.h"
#include "src/field.h"
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

MU_TEST(screen_pos_zero) {
  mu_check(CellScreenPosition(0).x == 0 && CellScreenPosition(0).y == 0);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(screen_pos_zero);
}

int main(void) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
