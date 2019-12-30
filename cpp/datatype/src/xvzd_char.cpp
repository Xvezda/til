#include "xvzd/xvzd_char.h"
#include "xvzd/xvzd_string.h"


namespace xvzd {


const String Char::Repeat(size_t n) const {
  return String(*this, n);
}

const String Char::operator*(int n) const {
  return Repeat(n);
}

const String Char::operator+(const String& other) const {
  return String(String(*this) + String(other));
}


}  // namespace xvzd
