#ifndef XVZD_LINKED_LIST_H_
#define XVZD_LINKED_LIST_H_

#include "xvzd_common.h"
#include "xvzd_object.h"


namespace xvzd {

template <typename T>
struct node {
  T data;
  struct node* next;
};

template <typename T>
class LinkedList : public Object, public Collection<T> {
public:
  LinkedList() : Object(), head(nullptr), tail(nullptr) {}

  virtual ~LinkedList() {
    for (size_t i = Size(); i != 0; --i) {
      Poll();
    }
  }

  virtual const LinkedList<T>& Push(const T& item) {
    node_t* new_node_ptr = new node_t;
    new_node_ptr->data = item;
    new_node_ptr->next = nullptr;

    if (!head) {
      head = new_node_ptr;
      tail = head;
    } else {
      tail->next = new_node_ptr;
      tail = tail->next;
    }
    ++size;

    return *this;
  }

  const T Poll() {
    T ret = head->data;
    node_t* next = head->next;

    delete head;
    if (!next) {
      head = nullptr;
    } else {
      head = next;
    }
    --size;

    return ret;
  }

  const T Pop() {
    T ret = tail->data;

    node_t* current = head;
    for (; current && current->next != tail; current = current->next);

    delete tail;
    tail = current;

    --size;

    return ret;
  }

  const T& At(int idx) const {
    node_t* current = head;
    for (int i = 0; i < idx; ++i) {
      if (!current->next) break;
      current = current->next;
    }
    return current->data;
  }

  const T& operator[](int idx) const {
    return At(idx);
  }

  size_t Size() const {
    return size;
  }
protected:
  using node_t = struct node<T>;
  node_t* head;
  node_t* tail;
};

}  // namespace xvzd


#endif  // XVZD_LINKED_LIST_H_
