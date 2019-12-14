#ifndef XVZD_OBJECT_H_
#define XVZD_OBJECT_H_


#include <iostream>
#include "xvzd_base.h"

namespace xvzd {


class Object : public Base {
public:
  Object() {}
  virtual ~Object() {}
  virtual const char* CStr() const {
    return "[object Object]";
  }
  friend std::ostream& operator<<(std::ostream& os, const Object& self) {
    os << self.CStr();
    return os;
  }
};


}  // namespace xvzd


#endif  // XVZD_OBJECT_H_
