#include "xvzd_test.h"

namespace xvzd {


TEST(xvzd_char_test, ctors) {
  Char c1;
  Char c2('a');
}

TEST(xvzd_char_test, compare_value) {
  Char c1;
  EXPECT_TRUE(c1 == '\0');
  Char c2('a');
  EXPECT_TRUE(c2 == 'a');
}

TEST(xvzd_char_test, print_value) {
  Char c('a');
  LOGGER(c);
}

TEST(xvzd_char_test, assign_value) {
  Char c('a');
  LOGGER(c);
  EXPECT_TRUE(c == 'a');
  c = 'b';
  LOGGER(c);
  EXPECT_TRUE(c == 'b');
}


}  // namespace xvzd

