#ifndef XVZD_CHAR_H_
#define XVZD_CHAR_H_


#include "xvzd_common.h"
#include "xvzd_item.h"

namespace xvzd {


class Char : public Item<char> {
public:
  Char() : Item<char>() {}
  Char(const char& chr) : Item<char>(chr) {}
  virtual ~Char() {}

  virtual xvzd_inline__ const char* GetFmt() const {
    return "%c";
  }
};

}  // namespace xvzd

#endif  // XVZD_CHAR_H_
