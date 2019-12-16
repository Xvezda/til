#ifndef XVZD_CHAR_H_
#define XVZD_CHAR_H_


#include "xvzd_common.h"
#include "xvzd_item.h"

namespace xvzd {


class Char : public Item<char> {
public:
  Char() : Char('\0') {
#ifdef DEBUG
    std::cout << __FILE__ << ':' << __LINE__ << ": "
      << "new char" << std::endl;
#endif
  }
  Char(const char& chr) : Item<char>(chr) {
#ifdef DEBUG
    std::cout << __FILE__ << ':' << __LINE__ << ": "
      << "new char: " << chr << std::endl;
#endif
  }
  virtual ~Char() {
#ifdef DEBUG
    std::cout << __FILE__ << ':' << __LINE__ << ": "
      << "del char: " << Cstr() << std::endl;
#endif
  }

  virtual xvzd_inline__ const char* GetFmt() const {
    return "%c";
  }
};

}  // namespace xvzd

#endif  // XVZD_CHAR_H_
