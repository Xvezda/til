#ifndef XVZD_CHAR_H_
#define XVZD_CHAR_H_


#include "xvzd_common.h"
#include "xvzd_item.h"

#define STRNULL_(s) ((!std::strlen(s) ? "(null)" : (s)))


namespace xvzd {
class String;
}  // namespace xvzd

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
    char* tmp = new char[1+1];
    tmp[0] = chr;
    tmp[1] = '\0';
    std::cout << __FILE__ << ':' << __LINE__ << ": "
      << "new char: " << STRNULL_(tmp) << std::endl;
    delete[] tmp;
#endif
  }
  virtual ~Char() {
#ifdef DEBUG
    std::cout << __FILE__ << ':' << __LINE__ << ": "
      << "del char: " << STRNULL_(Cstr()) << std::endl;
#endif
  }

  virtual const char* GetFmt() const {
    return "%c";
  }

  const String Repeat(size_t n) const;
  const String operator*(int n) const;
  const String operator+(const String& other) const;
};


}  // namespace xvzd

#undef STRNULL_

#endif  // XVZD_CHAR_H_
