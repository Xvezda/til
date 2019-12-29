#include "xvzd_test.h"
#include "xvzd_object.h"

namespace xvzd {

TEST(xvzd_object_test, object_print) {
  char type[] = "[object Object]";
  Object o;
  LOGGER(o);
  EXPECT_TRUE(!std::strncmp(o.Cstr(), type, sizeof(type)));
}

}  // namespace xvzd
