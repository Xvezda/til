#include "xvzd_test.h"

namespace xvzd {

TEST(xvzd_object_test, object_print) {
  Object o;
  LOGGER(o);
  EXPECT_TRUE(o.ToString() == "[object Object]");
}

}  // namespace xvzd
