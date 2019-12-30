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

TEST(xvzd_array_test, array_copy) {
  Array<Int> arr;

  arr += 123;
  arr += 456;
  arr += 789;

  Array<Int> arrcpy = arr;
  LOGGER(arrcpy);
  LOGGER(arr + arrcpy);

  EXPECT_TRUE((arr+arrcpy).ToString() == "[123, 456, 789, 123, 456, 789]");
}

TEST(xvzd_array_test, array_operator) {
  Array<Int> a1;
  Array<Int> a2;

  a1.Push(1);
  a2.Push(1);
  a1.Push(2);
  a2.Push(2);
  a1.Push(3);
  a2.Push(3);

  EXPECT_TRUE(a1 == a2);

  a2.Pop();
  EXPECT_FALSE(a1 == a2);
}

}  // namespace xvzd
