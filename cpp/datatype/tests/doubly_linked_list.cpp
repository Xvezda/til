#include "xvzd_test.h"


namespace xvzd {

TEST(xvzd_doubly_linked_list_test, doubly_linked_list_ctor) {
  DoublyLinkedList<String> dll;
}

TEST(xvzd_doubly_linked_list_test, doubly_linked_list_mutate) {
  DoublyLinkedList<String> dll;
  dll.Push("the");
  dll.Push("quick");
  dll.Push("brown");
  dll.Push("fox");

  EXPECT_TRUE(dll.At(1) == "quick");
  EXPECT_TRUE(dll.At(2) == "brown");

  String ret = dll.Pop();
  EXPECT_TRUE(ret == "fox");

  dll.Poll();
  EXPECT_TRUE(dll.At(1) == "brown");
}


}  // namespace xvzd
