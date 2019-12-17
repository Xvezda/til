#ifndef XVZD_ITEM_H_
#define XVZD_ITEM_H_

#include <iostream>
#include "xvzd_object.h"

namespace xvzd {


template <typename T>
class Item : public Object {
public:
  Item(const T& other) : Object() {
    ptr = static_cast<T*>(new T);
    assert(ptr != nullptr);
    *static_cast<T*>(ptr) = other;
#ifdef DEBUG
    std::cout << __FILE__ << ':' << __LINE__ << ": "
      << "new item" << std::endl;
#endif
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

    if (cstr_ptr) {
      delete[] cstr_ptr;
      cstr_ptr = nullptr;
    }
  }

  Item<T>& Assign(const Item<T>& other) {
    if (this == &other) return *this;

    assert(ptr != nullptr);
    *static_cast<T*>(ptr) = other;

    return *this;
  }

  Item<T>& operator=(const Item<T>& other) {
    return Assign(other);
  }

  operator T() {
    return *static_cast<T*>(ptr);
  }

  operator T() const {
    return *static_cast<T*>(ptr);
  }

  virtual const char* Cstr() const {
    cstr_ptr = new char[GetSize() + 1 /* Null terminated */];
    std::snprintf(cstr_ptr, GetSize()+1, GetFmt(), static_cast<T>(*this));
    cstr_ptr[GetSize()] = '\0';

    return cstr_ptr;
  }

  virtual size_t GetSize() const {
    return std::snprintf(nullptr, 0, GetFmt(), static_cast<T>(*this));
  }
};


}  // namespace xvzd

#endif  // XVZD_ITEM_H_
