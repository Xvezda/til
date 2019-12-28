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
  LinkedList() : Object(), head(nullptr) {}

  const LinkedList<T> Push(const T& item) {
    node_t* current;

    for (current = head;
        current && current->next; current = current->next);

    node_t* new_node_ptr = new node_t;
    new_node_ptr->data = item;
    new_node_ptr->next = nullptr;

    if (!head) {
      head = new_node_ptr;
    } else {
      current->next = new_node_ptr;
    }
    return *this;
  }

  const T Poll() {
    T ret;

    ret = head->data;
    node_t* next = head->next;

    if (next) {
      head->next = next->next;
      head->data = next->data;
    } else {
      head->next = nullptr;
    }

    return ret;
  }

  virtual ~LinkedList() {}
private:
  using node_t = struct node<T>;
  node_t* head;
};

}  // namespace xvzd


#endif  // XVZD_LINKED_LIST_H_
