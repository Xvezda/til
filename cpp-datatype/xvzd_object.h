#ifndef XVZD_OBJECT_H_
#define XVZD_OBJECT_H_

#include "xvzd_base.h"
#include "xvzd_interface.h"

namespace xvzd {


class Object : public Base, public Printable {
public:
  Object() : size(0), fmt(nullptr), cstr_ptr(nullptr) {}
  virtual ~Object() {}

  virtual xvzd_inline__ const char* Cstr() {
    return GetFmt();
  }

  virtual size_t GetSize() const {
    return size;
  }

  virtual const char* GetFmt() const {
    return "[object Object]";
  }

  friend std::ostream& operator<<(std::ostream& os, Object& self) {
    os << self.Cstr();
    return os;
  }
protected:
  size_t size;
  char* fmt;

  char* cstr_ptr;
  void *ptr;
};


}  // namespace xvzd

#endif  // XVZD_OBJECT_H_
