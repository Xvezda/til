#ifndef XVZD_STRING_H_
#define XVZD_STRING_H_


#include "xvzd_common.h"
#include "xvzd_char.h"
#include "xvzd_array.h"

namespace xvzd {
template <typename T> class Array;
}  // namespace xvzd


namespace xvzd {

class String
  : public Array<Char>, public Assignable<String>, public Comparable<String> {
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

  String(const Char& chr) : Array() {
    Push(chr);
  }

  String(const Char& other, size_t repeat) : Array(repeat) {
    for (size_t i = repeat; i > 0; --i) {
      Push(other);
    }
  }

  String(const String& other, size_t repeat) : Array(other.Size() * repeat) {
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

  virtual const String& Assign(const String& other) {
    if (this == &other) return *this;
    Clear();
    for (size_t i = 0; i < other.Length(); ++i) {
      Push(other[i]);
    }
    return *this;
  }

  const String& Append(const String& other) {
    for (size_t i = 0; i < other.Length(); ++i) {
      Push(other[i]);
    }
    return *this;
  }

  void Clear() {
    for (size_t i = Length(); i > 0; --i) {
      Pop();
    }
  }

  const String Concat(const String& other) const {
    String ret(*this);
    return ret.Append(other);
  }

  virtual int Compare(const String& other) const {
    return std::strcmp(Cstr(), other.Cstr());
  }

  virtual bool Equal(const String& other) const {
    return !Compare(other);
  }

  int Find(const String& needle) const {
    for (size_t i = 0; i < Length() - needle.Length(); ++i) {
      if (Substr(i, needle.Length()) == needle) return i;
    }
    return -1;
  }

  const String Slice(int start, int end) const {
    String ret("");
    if (start < 0) {
      start = Length() + start;
      if (start < 0) {
        start = 0;
      }
    }
    if (end < 0) {
      end = Length() + end;
      if (end < 0) {
        end = 0;
      }
    } else if (end > static_cast<int>(Length())) {
      end = Length();
    }
    for (int i = start; i < end; ++i) {
      ret.Push(At(i));
    }
    return ret;
  }

  const String Slice(int start) const {
    return Slice(start, Length());
  }

  const String Substr(int from, int length) const {
    return Slice(from).Slice(0, length);
  }

  const String Substring(int start, int end) const {
    String ret(*this);

    if (start > end) {
      int tmp = start;
      start = end;
      end = tmp;
    }
    if (start < 0 && end < 0) {
      return ret;
    }
    if (start < 0 || end < 0) {
      start = 0;
    }
    return ret.Slice(0, end).Slice(start);
  }

  const Array<String> Split(String token) const;


  const String Repeat(size_t repeat) const {
    return String(*this, repeat);
  }

  const String& operator=(const String& other) {
    return Assign(other);
  }

  bool operator==(const String& other) const {
    return Equal(other);
  }

  bool operator!=(const String& other) const {
    return !(*this == other);
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
private:
  using Array<Char>::Assign;
  using Array<Char>::Compare;
  using Array<Char>::Equal;
};

}  // namespace xvzd

#endif  // XVZD_STRING_H_
