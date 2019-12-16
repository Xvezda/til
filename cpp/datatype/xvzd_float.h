#ifndef XVZD_FLOAT_H_
#define XVZD_FLOAT_H_

#include "xvzd_item.h"

namespace xvzd {


class Float : public Item<double> {
public:
  Float() : Float(0.0) {}
  Float(double num) : Item<double>(num) {
#ifdef DEBUG
    std::cout << __FILE__ << ':' << __LINE__ << ": "
      << "new float: " << num << std::endl;
#endif
  }
  virtual ~Float() {
#ifdef DEBUG
    std::cout << __FILE__ << ':' << __LINE__ << ": "
      << "del float: " << Cstr() << std::endl;
#endif
  }

  virtual const char* GetFmt() const {
    return "%lf";
  }
private:
};

}  // namespace xvzda

#endif  // XVZD_FLOAT_H_
