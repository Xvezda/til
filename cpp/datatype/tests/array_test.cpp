#include "xvzd_test.h"


namespace xvzd {

TEST(xvzd_array_test, array_ctor) {
  Array<Int> arr;
}

TEST(xvzd_array_test, array_append) {
  Array<Int> arr;

  arr += 123;
  arr += 456;
  arr += 789;

  LOGGER(arr[0]);
  EXPECT_TRUE(arr[0] == 123);
  LOGGER(arr[1]);
  EXPECT_TRUE(arr[1] == 456);
  LOGGER(arr[-1]);
  EXPECT_TRUE(arr[-1] == 789);

  LOGGER(arr);
  EXPECT_TRUE(arr.ToString() == "[123, 456, 789]");
}

}  // namespace xvzd
