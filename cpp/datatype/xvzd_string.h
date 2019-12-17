#ifndef XVZD_STRING_H_
#define XVZD_STRING_H_


#include "xvzd_common.h"
#include "xvzd_char.h"
#include "xvzd_array.h"

namespace xvzd {

class String : public Array<Char> {
public:
  String() : Array() {
    Push('\0');
    cstr_ptr = new char[1];
    std::memset(cstr_ptr, 0, 1);
  }

  String(const char* other) : Array() {
    size_t len = std::strlen(other);
    for (size_t i = 0; i < len; ++i) {
      Push(other[i]);
    }
    cstr_ptr = new char[Length() + 1];
  }

  String(char chr) : Array() {
    Push(chr);
    Push('\0');
    cstr_ptr = new char[2];
    std::memset(cstr_ptr, 0, 2);
  }

  String(char other, size_t repeat) : Array() {
    size_t len = 1;
    for (size_t i = repeat; i > 0; --i) {
      Push(other);
    }
    cstr_ptr = new char[len * repeat + 1];
  }

  virtual ~String() {
    if (cstr_ptr) {
      delete[] cstr_ptr;
      cstr_ptr = nullptr;
    }
  }

  virtual const char* Cstr() const {
    if (!cstr_ptr) return nullptr;
    cstr_ptr[Length()] = '\0';

    for (size_t i = 0; i < Length(); ++i) {
      cstr_ptr[i] = At(i);
    }
    return cstr_ptr;
  }

  size_t Length() const {
    return Size();
  }

  const String& Append(const String& other) {
    for (size_t i = 0; i < other.Length(); ++i) {
      Push(other[i]);
    }
    return *this;
  }
};

}  // namespace xvzd

#endif  // XVZD_STRING_H_
