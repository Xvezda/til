#ifndef XVZD_STRING_H_
#define XVZD_STRING_H_


#include "xvzd_common.h"
#include "xvzd_char.h"
#include "xvzd_array.h"

namespace xvzd {

class String : public Array<Char> {
public:
  String() {
    Push('\0');
    cstr_ptr = new char[1];
    std::memset(cstr_ptr, 0, 1);
  }
  String(const char* other) {
    size_t len = std::strlen(other);
    for (size_t i = 0; i < len; ++i) {
      Push(other[i]);
    }
    cstr_ptr = new char[Size()+1];
  }

  virtual ~String() {
    if (cstr_ptr) {
      delete[] cstr_ptr;
      cstr_ptr = nullptr;
    }
  }

  virtual const char* Cstr() const {
    if (!cstr_ptr) return nullptr;
    cstr_ptr[Size()] = '\0';

    for (size_t i = 0; i < Size(); ++i) {
      cstr_ptr[i] = At(i);
    }
    return cstr_ptr;
  }
};

}  // namespace xvzd

#endif  // XVZD_STRING_H_
