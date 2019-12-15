#ifndef XVZD_ITEM_H_
#define XVZD_ITEM_H_

#include "xvzd_object.h"

namespace xvzd {


template <typename T>
class Item : public Object {
public:
  Item(const T& other) {
    ptr = new T;
    *static_cast<T*>(ptr) = other;
  }
  virtual ~Item() {
    if (ptr) {
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
