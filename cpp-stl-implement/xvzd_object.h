#ifndef XVZD_OBJECT_H_
#define XVZD_OBJECT_H_


#include <iostream>

namespace xvzd {


class Object {
public:
  Object() {}
  virtual ~Object() {}
  virtual const char* CStr() const {
    const char* ret = "[object Object]";
    return ret;
  }
  friend std::ostream& operator<<(std::ostream& os, const Object& self) {
    os << self.CStr();
    return os;
  }
};


}  // namespace xvzd


#endif  // XVZD_OBJECT_H_
