#ifndef XVZD_CHAR_H_
#define XVZD_CHAR_H_


#include "xvzd_item.h"

namespace xvzd {


class Char : public Item<char> {
public:
  Char(const char& chr) : Item<char>(chr) {}
};

}  // namespace xvzd

#endif  // XVZD_CHAR_H_
