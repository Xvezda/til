#ifndef XVZD_ITEM_H_
#define XVZD_ITEM_H_

#include <iostream>
#include "xvzd_object.h"

namespace xvzd {


template <typename T>
class Item : public Object {
public:
  Item(const T& other) {
#ifdef DEBUG
    std::cout << __FILE__ << ':' << __LINE__ << ": "
      << "new item" << std::endl;
#endif
    ptr = new T;
    *static_cast<T*>(ptr) = other;
  }
  virtual ~Item() {
    if (ptr) {
#ifdef DEBUG
      std::cout << __FILE__ << ':' << __LINE__ << ": "
        << "del item" << std::endl;
#endif
      delete static_cast<T*>(ptr);
      ptr = nullptr;
    }
  }
  operator T() {
    return *static_cast<T*>(ptr);
  }
private:
};


}  // namespace xvzd

#endif  // XVZD_ITEM_H_
