#ifndef XVZD_STRING_H_
#define XVZD_STRING_H_


#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cmath>

#include "xvzd_object.h"

namespace xvzd {

/**
 * TODO: Add exceptions
 */
typedef struct StringMeta {
  size_t len;
  char  *ptr;
} str_meta_t;


class String : public Object {
public:
  String() {
    Init();
  }

  String(char other) {
    String();
    CopyStr(&other, 1);
  }

  String(const char* other) {
    String();
    CopyStr(other);
  }

  String(const String& other, int repeat) {
    String();
    *this = String(other.CStr(), repeat);
  }

  String(const char* other, int repeat) {
    assert(other != nullptr);

    String();
    size_t len = std::strlen(other);
    size_t new_len = len * repeat;

    meta.ptr = new char[new_len+1];
    meta.ptr[0] = '\0';
    for (int i = repeat; i > 0; --i) {
      std::strncat(meta.ptr, other, len);
    }
    meta.len = new_len;
  }

  String(char chr, int repeat) {
    String();
    size_t len = 1;
    size_t new_len = len * repeat;

    meta.ptr = new char[new_len+1];
    std::memset(meta.ptr, chr, new_len);
    SetEnd(new_len);
  }

  String(const String& other) {
    String();
    CopyStr(other);
  }

  String(int number) {
    String();
    NumToStr("%d", number);
  }

  String(long number) {
    String();
    NumToStr("%ld", number);
  }

  String(double number) {
    String();
    NumToStr("%lf", number);
  }

  ~String() {
    if (meta.ptr && meta.len) {
      Clear();
    }
  }

  size_t SetLength(size_t len) {
    if (meta.ptr) {
      if (meta.len < len) {
        len = meta.len;
      } else if (len < 0) {
        len = 0;
      }
      SetEnd(len);
    }
    return GetLength();
  }

  inline size_t GetLength() const {
    return meta.len;
  }

  inline size_t Length() const {
    return GetLength();
  }

  inline const char* CStr() const {
    return meta.ptr;
  }

  String& Append(const char *other) {
    return Append(String(other));
  }

  String& Append(const String& other) {
    size_t other_len = other.Length();
    // Make temporal copy
    char *tmp = new char[meta.len + other_len + 1];
    std::memcpy(tmp, meta.ptr, meta.len);
    std::memcpy(tmp+meta.len, other.CStr(), other_len);
    tmp[meta.len + other_len] = '\0';

    DelStr();
    meta.ptr = tmp;

    meta.len += other_len;

    return *this;
  }

  String Concat(const String& other) {
    String cpy(*this);
    cpy += other;
    return cpy;
  }

  String Repeat(int repeat) {
    String tmp = String(*this);
    String result = String();

    for (int cnt = repeat; cnt > 0; --cnt) {
      result += tmp;
    }
    return result;
  }

  String Slice(int start) {
    if (!meta.ptr) return String();
    if (start < 0) {
      String ret = String(*this);
      int offset = ret.Length() + start;
      if (offset < 0) {
        offset = 0;
      }
      return ret.Slice(offset);
    }
    return String(meta.ptr+start);
  }

  String Slice(int start, int end) {
    if (start < 0) {
      start = 0;
    }
    if (end <= start) return String();
    String ret = String(*this).Slice(start);

    size_t len = ret.Length();
    char *tmp = new char[len+1];

    std::memcpy(tmp, ret.CStr(), len);
    tmp[end-start] = '\0';

    ret = String(tmp);
    delete[] tmp;
    tmp = nullptr;

    return ret;
  }

  String Substr(int from, size_t len) {
    String ret = String(*this).Slice(from);
    ret.SetLength(len);

    return ret;
  }

  String& operator=(const String& other) {
    if (this == &other) return *this;

    Clear();
    CopyStr(other.CStr(), other.Length());

    return *this;
  }

  const String operator+(const String& other) {
    String cpy(*this);
    return cpy.Concat(other);
  }

  String& operator+=(const String& other) {
    Append(other);
    return *this;
  }

  inline int CharCodeAt(int idx) const {
    return CharAt(idx);
  }

  char CharAt(int idx) const {
    if (idx < 0) {
      size_t len = Length();
      int new_idx = len - std::abs(idx);
      if (new_idx < 0) return '\0';
      return meta.ptr[new_idx];
    }
    return meta.ptr[idx];
  }

  char operator[](int idx) const {
    return CharAt(idx);
  }

  friend std::ostream& operator<<(std::ostream& os, const String& self) {
    os << self.CStr();
    return os;
  }

private:
  str_meta_t meta;

  inline void Init() {
    Reset();
    meta.ptr = new char[1];
    meta.ptr[0] = '\0';
  }

  inline void Reset() {
    meta.ptr = nullptr;
    meta.len = 0;
  }

  inline void DelStr() {
    if (!meta.ptr) return;
#ifdef DEBUG
    std::cout << __FILE__ << ':' << __LINE__
      << ": deallocate string -> " << CStr() << std::endl;
#endif
    delete[] meta.ptr;
    meta.ptr = nullptr;
  }

  inline void Clear() {
    DelStr();
    Reset();
  }

  inline void SetEnd(size_t end) {
    meta.ptr[end] = '\0';
    meta.len = end;
  }

  template <typename T>
  void NumToStr(const char* fmt, T number) {
    size_t len = std::snprintf(nullptr, 0, fmt, number);
    char *tmp = new char[len+1];
    std::snprintf(tmp, len+1, fmt, number);
    tmp[len] = '\0';

    CopyStr(tmp, len);

    assert(tmp != nullptr);
    delete[] tmp;
    tmp = nullptr;
  }

  void CopyStr(const char *src, size_t size) {
    if (!src) return;
    meta.ptr = new char[size+1];

    assert(meta.ptr != nullptr && src);
    std::memcpy(meta.ptr, src, size);

    SetEnd(size);
  }

  void CopyStr(const char *src) {
    if (!src) return;
    size_t other_len = std::strlen(src);
    CopyStr(src, other_len);
  }

  void CopyStr(const String& other) {
    if (!other.CStr()) return;
    size_t other_len = other.Length();
    CopyStr(other.CStr(), other_len);
  }
};

}  // namespace xvzd


#endif  // XVZD_STRING_H_
