#ifndef XVZD_INT_H_
#define XVZD_INT_H_

#include "xvzd_item.h"

namespace xvzd {


class Int : public Item<int> {
public:
  Int(const int& num) : Item<int>(num) {}
};

}  // namespace xvzd

#endif  // XVZD_INT_H_
