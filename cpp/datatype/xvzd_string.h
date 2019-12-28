#ifndef XVZD_STRING_H_
#define XVZD_STRING_H_


#include "xvzd_common.h"
#include "xvzd_int.h"
#include "xvzd_float.h"
#include "xvzd_char.h"
#include "xvzd_array.h"

namespace xvzd {
template <typename T> class Array;
}  // namespace xvzd


namespace xvzd {

class String
  : public Array<Char>,
    public Assignable<String>, public Comparable<String> {
public:

  using Array<Char>::Assign;
  using Array<Char>::Compare;
  using Array<Char>::Equal;

  String() : Array() {
    Push('\0');
  }

  String(const char* other) : Array() {
    size_t len = std::strlen(other);
    for (size_t i = 0; i < len; ++i) {
      Push(other[i]);
    }
  }

  String(char chr) : String(Char(chr)) {}

  String(const String& other) : Array() {
    for (size_t i = 0; i < other.Length(); ++i) {
      Push(other[i]);
    }
  }

  String(const int other) : String(Int(other)) {}

  template <typename T>
  String(const T& other) : String(other.Cstr()) {}

  String(const Char& chr) : Array() {
    Push(chr);
  }

  String(const String& other, size_t repeat)
    : Array(other.Size() * repeat) {
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

  int IndexOf(const String& needle) const {
    return Find(needle);
  }

  template <typename T>
  const String Join(const Array<T>& arr) const {
    String ret("");

    if (!Length()) {
      for (size_t i = 0; i < arr.Size(); ++i) {
        ret += arr[i];
      }
    } else {
      for (size_t i = 0; i < arr.Size(); ++i) {
        ret += arr[i] + String(i != arr.Size() - 1
            ? String(*this).Cstr()
            : "");
      }
    }
    return ret;
  }

  const String Lpad(size_t repeat) const {
    return Lpad(repeat, String(' '));
  }

  const String Lpad(size_t repeat, const String& character) const {
    String ret("");
    ret = character.Repeat(repeat) + String(*this);

    return ret;
  }

  const String Rpad(size_t repeat) const {
    return Rpad(repeat, String(' '));
  }

  const String Rpad(size_t repeat, const String& character) const {
    String ret("");
    ret = String(*this) + character.Repeat(repeat);

    return ret;
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

  const String Reverse() const {
    return String("").Join(Array<Char>::Reverse());
  }

  bool IsDigit() const {
    for (size_t i = 0; i < Size(); ++i) {
      if ('0' > At(i) || '9' < At(i)) return false;
    }
    return true;
  }

  bool IsAlpha() const {
    for (size_t i = 0; i < Size(); ++i) {
      if (!(('A' <= At(i) && 'Z' >= At(i)) ||
            ('a' <= At(i) && 'z' >= At(i)))) return false;
    }
    return false;
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

  explicit operator bool() const {
    return Size();
  }
private:
};

}  // namespace xvzd

#endif  // XVZD_STRING_H_
