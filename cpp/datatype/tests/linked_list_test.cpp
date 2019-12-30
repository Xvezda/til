#include "xvzd_test.h"


namespace xvzd {

TEST(xvzd_linked_list_test, linked_list_at) {
  LinkedList<String> ll;
  ll.Push("foo");
  ll.Push("bar");
  ll.Push("baz");

  EXPECT_TRUE(ll.At(0) == "foo");
  EXPECT_TRUE(ll.At(2) == "baz");

  ll.Poll();
  EXPECT_TRUE(ll.At(0) == "bar");
}

}  // namespace xvzd
