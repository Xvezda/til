#ifndef XVZD_ITEM_H_
#define XVZD_ITEM_H_

#include "xvzd_common.h"
#include "xvzd_object.h"

namespace xvzd {


template <typename T>
class Item
  : public Object, public Assignable< Item<T> >, public Comparable< Item<T> > {
public:

  using Object::Compare;
  using Object::Equal;

  Item(const T& other) : Object() {
    Assign(other);
#ifdef DEBUG
    std::cout << __FILE__ << ':' << __LINE__ << ": "
      << "new item - addr: " << ptr << std::endl;
#endif
  }

  Item(const Item<T>& other) : Object() {
    Assign(other);
#ifdef DEBUG
    std::cout << __FILE__ << ':' << __LINE__ << ": "
      << "copy item - addr: " << ptr << std::endl;
#endif
  }

  virtual ~Item() {
    if (ptr) {
#ifdef DEBUG
      std::cout << __FILE__ << ':' << __LINE__ << ": "
        << "del item - addr: " << ptr << std::endl;
#endif
      delete static_cast<T*>(ptr);
      ptr = nullptr;
    }

    if (cstr_ptr) {
      delete[] cstr_ptr;
      cstr_ptr = nullptr;
    }
  }

  const Item<T>& Assign(const Item<T>& other) {
    return Assign(static_cast<T>(other));
  }

  const Item<T>& Assign(const T& other) {
    if (!ptr) {
      ptr = new T;
    }
    *static_cast<T*>(ptr) = other;

    return *this;
  }

  virtual int Compare(const Item<T>& other) const {
    return static_cast<int>(*static_cast<T*>(ptr) - static_cast<T>(other));
  }

  virtual bool Equal(const Item<T>& other) const {
    return !Compare(other);
  }

  const Item<T>& operator=(const Item<T>& other) {
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
private:
  Item() : Object() {}
};


}  // namespace xvzd

#endif  // XVZD_ITEM_H_
