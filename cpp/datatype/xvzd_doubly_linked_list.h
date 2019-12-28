#ifndef XVZD_DOUBLY_LINKED_LIST_H_
#define XVZD_DOUBLY_LINKED_LIST_H_

#include "xvzd_common.h"
#include "xvzd_object.h"
#include "xvzd_linked_list.h"

namespace xvzd {

template <typename T>
struct dnode : public node<T>, public Collection<T> {
  struct node<T>* prev;
};

template <typename T>
class DoublyLinkedList : public LinkedList<T> {
public:
  DoublyLinkedList() {}
  ~DoublyLinkedList() {}
private:
};


}  // namespace xvzd

#endif  // XVZD_DOUBLY_LINKED_LIST_H_
