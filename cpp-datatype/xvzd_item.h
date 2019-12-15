#ifndef XVZD_ITEM_H_
#define XVZD_ITEM_H_

#include <iostream>
#include "xvzd_object.h"

namespace xvzd {


template <typename T>
class Item : public Object {
public:
  Item() : Object() {}
  Item(const T& other) : Item() {
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
    if (cstr_ptr) {
      delete[] cstr_ptr;
      cstr_ptr = nullptr;
    }
  }

  operator T() {
    return *static_cast<T*>(ptr);
  }

  operator T() const {
    return *static_cast<T*>(ptr);
  }

  virtual const char* Cstr() {
    cstr_ptr = new char[GetSize() + 1 /* Null terminated */];
    std::snprintf(cstr_ptr, GetSize()+1, GetFmt(), static_cast<T>(*this));
    cstr_ptr[GetSize()] = '\0';

    return cstr_ptr;
  }

  virtual xvzd_inline__ size_t GetSize() const {
    return std::snprintf(nullptr, 0, GetFmt(), static_cast<T>(*this));
  }
};


}  // namespace xvzd

#endif  // XVZD_ITEM_H_
