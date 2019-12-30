#include "xvzd_test.h"

namespace xvzd {

TEST(xvzd_object_test, object_print) {
  Object o;
  LOGGER(o);
  EXPECT_TRUE(o.ToString() == "[object Object]");
}

TEST(xvzd_object_test, object_ptr) {
  Array<Object*> oarr;
  oarr.Push(new Int(123));
  oarr.Push(new String("foobar"));

  LOGGER(oarr);
  EXPECT_TRUE(oarr.ToString() == "[123, foobar]");

  for (size_t i = 0; i < oarr.Size(); ++i) {
    delete oarr.Pop();
  }
}

}  // namespace xvzd
