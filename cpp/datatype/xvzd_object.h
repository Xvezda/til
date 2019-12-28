#ifndef XVZD_OBJECT_H_
#define XVZD_OBJECT_H_

#include "xvzd_base.h"
#include "xvzd_interfaces.h"

namespace xvzd {


class Object
  : public Base, public Printable, public Comparable<Object> {
public:
  Object() : size(0), fmt(nullptr), cstr_ptr(nullptr), ptr(nullptr) {
#ifdef DEBUG
    std::cout << __FILE__ << ':' << __LINE__ << ": "
      << "new object" << std::endl;
#endif
  }

  virtual ~Object() {
#ifdef DEBUG
    std::cout << __FILE__ << ':' << __LINE__ << ": "
      << "del object" << std::endl;
#endif
  }

  virtual int Compare(const Object& other) const {
    return reinterpret_cast<std::uintptr_t>(ptr) \
      - reinterpret_cast<std::uintptr_t>(other.ptr);
  }

  virtual bool Equal(const Object& other) const {
    if (ptr == other.ptr) return true;
    return false;
  }

  virtual const char* Cstr() const {
    return GetFmt();
  }

  virtual size_t Size() const {
    return GetSize();
  }

  virtual size_t GetSize() const {
    return size;
  }

  virtual const char* GetFmt() const {
    return "[object Object]";
  }

  friend std::ostream& operator<<(std::ostream& os, const Object& self) {
    os << self.Cstr();
    return os;
  }
protected:
  size_t size;
  char* fmt;

  mutable char* cstr_ptr;
  void* ptr;
};


}  // namespace xvzd

#endif  // XVZD_OBJECT_H_
