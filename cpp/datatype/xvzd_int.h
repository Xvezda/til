#ifndef XVZD_INT_H_
#define XVZD_INT_H_

#include "xvzd_item.h"

namespace xvzd {


class Int : public Item<int> {
public:
  Int() : Int(0) {
#ifdef DEBUG
    std::cout << __FILE__ << ':' << __LINE__ << ": "
      << "new int" << std::endl;
#endif
  }

  Int(const int& num) : Item<int>(num) {
#ifdef DEBUG
    std::cout << __FILE__ << ':' << __LINE__ << ": "
      << "new int: " << num << std::endl;
#endif
  }

  virtual ~Int() {
#ifdef DEBUG
    std::cout << __FILE__ << ':' << __LINE__ << ": "
      << "del int: " << Cstr() << std::endl;
#endif
  }

  virtual const char* GetFmt() const {
    return "%d";
  }
};

}  // namespace xvzd

#endif  // XVZD_INT_H_
