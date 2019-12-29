#include "xvzd_test.h"
#include "xvzd_float.h"


namespace xvzd {

TEST(xvzd_float_test, float_ctors) {
  Float f1;
  EXPECT_TRUE(f1 == 0);
  Float f2(123.456);
  EXPECT_TRUE(f2 == 123.456);
  Float f3 = 456.789;
  EXPECT_TRUE(f3 == 456.789);
}

}  // namespace xvzd
