#include "xvzd_test.h"


namespace xvzd {

TEST(xvzd_int_test, ctors) {
  Int n1;
  Int n2(123);
}

TEST(xvzd_int_test, compare_value) {
  Int n1;
  EXPECT_TRUE(n1 == 0);
  Int n2(123);
  EXPECT_TRUE(n2 == 123);
}

TEST(xvzd_int_test, print_value) {
  Int n(123);
  LOGGER(n);
}

TEST(xvzd_int_test, assign_value) {
  Int n(123);
  LOGGER(n);
  EXPECT_TRUE(n == 123);
  n = 321;
  LOGGER(n);
  EXPECT_TRUE(n == 321);
}

TEST(xvzd_int_test, ptr_test) {
  Int* intptr = new Int(12345);

  LOGGER(*intptr);
  EXPECT_TRUE(intptr != nullptr);
  EXPECT_TRUE(*intptr == 12345);

  delete intptr;
}


}  // namespace xvzd
