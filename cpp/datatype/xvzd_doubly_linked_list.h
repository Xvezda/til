#ifndef XVZD_DOUBLY_LINKED_LIST_H_
#define XVZD_DOUBLY_LINKED_LIST_H_

#include "xvzd_common.h"
#include "xvzd_object.h"
#include "xvzd_linked_list.h"


namespace xvzd {

template <typename T>
struct dnode : public node<T> {
  struct node<T>* prev;
};

template <typename T>
class DoublyLinkedList : public LinkedList<T>, public Collection<T> {
public:
  DoublyLinkedList() : LinkedList<T>() {}
  virtual ~DoublyLinkedList() {}

  virtual const LinkedList<T>& Push(const T& item) {
    dnode_t* new_node_ptr = new dnode_t;
    new_node_ptr->data = item;
    new_node_ptr->next = nullptr;

    if (!head) {
      new_node_ptr->prev = nullptr;
      head = new_node_ptr;
      tail = head;
    } else {
      new_node_ptr->prev = tail;
      tail->next = new_node_ptr;
      tail = tail->next;
    }
    ++size;

    return *this;
  }
protected:
  using dnode_t = struct dnode<T>;

  // TODO: What is dependent name?
  using LinkedList<T>::size;
  using LinkedList<T>::head;
  using LinkedList<T>::tail;
};


}  // namespace xvzd

#endif  // XVZD_DOUBLY_LINKED_LIST_H_
