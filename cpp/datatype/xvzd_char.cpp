#include "xvzd_char.h"
#include "xvzd_string.h"


using xvzd::Char;
using xvzd::String;

const String Char::Repeat(size_t n) const {
  return String(*this, n);
}

const String Char::operator*(int n) const {
  return Repeat(n);
}


