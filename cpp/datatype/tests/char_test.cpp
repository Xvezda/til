#include "xvzd_test.h"
#include "../xvzd_char.h"

namespace xvzd {


TEST(xvzd_int_test, ctors) {
  Char c1;
  Char c2('a');
}

TEST(xvzd_int_test, compare_value) {
  Char c1;
  EXPECT_TRUE(c1 == '\0');
  Char c2('a');
  EXPECT_TRUE(c2 == 'a');
}

TEST(xvzd_int_test, print_value) {
  Char c('a');
  LOGGER(c);
}


}  // namespace xvzd

