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
  }

  String(const char* other) : Array() {
    size_t len = std::strlen(other);
    for (size_t i = 0; i < len; ++i) {
      Push(other[i]);
    }
  }

  String(const String& other) : Array() {
    for (size_t i = 0; i < other.Length(); ++i) {
      Push(other[i]);
    }
  }

  String(Char chr) : Array() {
    Push(chr);
  }

  String(Char other, size_t repeat) : Array() {
    for (size_t i = repeat; i > 0; --i) {
      Push(other);
    }
  }

  String(const String& other, size_t repeat) : Array() {
    for (size_t i = repeat; i > 0; --i) {
      Append(other);
    }
  }

  virtual ~String() {
    if (cstr_ptr) {
      delete[] cstr_ptr;
      cstr_ptr = nullptr;
    }
  }

  virtual const char* Cstr() const {
    cstr_ptr = new char[Length() + 1];
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

  const String Concat(const String& other) const {
    String ret(*this);
    return ret.Append(other);
  }

  const String Repeat(size_t repeat) const {
    return String(*this, repeat);
  }

  const String& operator+=(const String& other) {
    return Append(other);
  }

  const String operator+(const String& other) const {
    return Concat(other);
  }

  const String operator*(size_t n) const {
    return Repeat(n);
  }
};

}  // namespace xvzd

#endif  // XVZD_STRING_H_
