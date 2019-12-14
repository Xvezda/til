#ifndef XVZD_BASE_H_
#define XVZD_BASE_H_

namespace xvzd {

class Base {
public:
  Base() {}
  virtual ~Base() {}
  virtual const char* CStr() const = 0;
};


}  // namespace xvzd

#endif  // XVZD_BASE_H_
