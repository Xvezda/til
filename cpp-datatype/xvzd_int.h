#ifndef XVZD_INT_H_
#define XVZD_INT_H_

#include "xvzd_item.h"

namespace xvzd {


class Int : public Item<int> {
public:
  Int(const int& num) : Item<int>(num) {}
  virtual ~Int() {}

  virtual xvzd_inline__ const char* GetFmt() const {
    return "%d";
  }
};

}  // namespace xvzd

#endif  // XVZD_INT_H_
