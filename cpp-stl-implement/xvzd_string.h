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
    meta.ptr[new_len] = '\0';
    meta.len = new_len;
  }

  String(const String& other) {
    String();
    CopyStr(other);
  }

  String(int number) {
    String();
    size_t len = std::snprintf(nullptr, 0, "%d", number);
    char *tmp = new char[len+1];
    std::snprintf(tmp, len+1, "%d", number);
    tmp[len] = '\0';

    CopyStr(tmp, len);

    assert(tmp != nullptr);
    delete[] tmp;
    tmp = nullptr;
  }

  ~String() {
    if (meta.ptr && meta.len) {
      Clear();
    }
  }

  size_t Length() const {
    return meta.len;
  }

  const char* CStr() const {
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

  const String Concat(const String& other) {
    String cpy(*this);
    cpy += other;
    return cpy;
  }

  const String Repeat(int repeat) {
    String tmp = String(*this);
    String result = String();

    for (int cnt = repeat; cnt > 0; --cnt) {
      result += tmp;
    }
    return result;
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

  char operator[](int idx) const {
    if (idx < 0) {
      size_t len = Length();
      int new_idx = len - std::abs(idx);
      if (new_idx < 0) return '\0';
      return meta.ptr[new_idx];
    }
    return meta.ptr[idx];
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

  void CopyStr(const char *src, size_t size) {
    if (!src) return;
    meta.ptr = new char[size+1];

    assert(meta.ptr != nullptr && src);
    std::memcpy(meta.ptr, src, size);

    meta.ptr[size] = '\0';
    meta.len = size;
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
