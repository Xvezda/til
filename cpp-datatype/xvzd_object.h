#ifndef XVZD_OBJECT_H_
#define XVZD_OBJECT_H_

#include "xvzd_base.h"

namespace xvzd {


class Object : public Base {
public:
  Object() {}
  virtual ~Object() {}
protected:
  void *ptr;
};


}  // namespace xvzd

#endif  // XVZD_OBJECT_H_
