#include "xvzd_test.h"
#include "../xvzd_int.h"

TEST(xvzd_int_test, ctors) {
  xvzd::Int n1;
  xvzd::Int n2(123);
}

TEST(xvzd_int_test, compare_value) {
  xvzd::Int n(123);
  EXPECT_TRUE(n == 123);
}

TEST(xvzd_int_test, print_value) {
  xvzd::Int n(123);
  LOGGER(n);
}


