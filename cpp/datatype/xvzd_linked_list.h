#ifndef XVZD_LINKED_LIST_H_
#define XVZD_LINKED_LIST_H_

#include "xvzd_common.h"
#include "xvzd_object.h"
#include "xvzd_item.h"


namespace xvzd {

template <typename T>
struct node {
  T data;
  struct node* next;
};

template <typename T>
class LinkedList : public Object {
public:
  LinkedList() : Object() {
    entry.next = nullptr;
  }

  const LinkedList<T> Push(const T& item) {
    node_t* current = entry.next;
    for (; current->next != nullptr; current = current->next);

    node_t* new_node_ptr = new node_t;
    new_node_ptr->data = item;
    new_node_ptr->next = nullptr;

    current->next = new_node_ptr;

    return *this;
  }

  const T Poll() {
    T ret;

    ret = entry.data;
    node_t* next = entry.next;

    entry.data = next->data;
    entry.next = next->next;

    return ret;
  }

  virtual ~LinkedList() {}
private:
  using node_t = struct node<T>;
  node_t entry;
};

}  // namespace xvzd


#endif  // XVZD_LINKED_LIST_H_
