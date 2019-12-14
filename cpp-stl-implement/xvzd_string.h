#ifndef XVZD_STRING_H_
#define XVZD_STRING_H_


#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>

namespace xvzd {

typedef struct StringMeta {
  size_t len;
  char *ptr;
} str_meta_t;

class String {
public:
  String() {
    Init();
  }

  String(char other) {
    CopyStr(&other, 1);
  }

  String(const char* other) {
    CopyStr(other);
  }

  String(const String& other) {
    CopyStr(other);
  }

  String(int number) {
    size_t len = std::snprintf(nullptr, 0, "%d", number);
    char *tmp = new char[len+1];
    std::snprintf(tmp, len+1, "%d", number);
    tmp[len] = '\0';

    CopyStr(tmp, len);

    delete[] tmp;
  }

  ~String() {
    if (!meta.ptr && meta.len) {
      Clear();
    }
  }

  size_t Length() const {
    return meta.len;
  }

  const char* CStr() const {
    return meta.ptr;
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

  String& operator=(const String& other) {
    if (this == &other) return *this;

    Clear();
    CopyStr(other.CStr(), other.Length());

    return *this;
  }

  const String operator+(const String& other) {
    String cpy(*this);
    cpy += other;
    return cpy;
  }

  String& operator+=(const String& other) {
    Append(other);
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, const String& self) {
    os << self.CStr();
    return os;
  }

private:
  str_meta_t meta;

  inline void Init() {
    Reset();
  }

  inline void Reset() {
    meta.ptr = nullptr;
    meta.len = 0;
  }

  inline void DelStr() {
    delete[] meta.ptr;
  }

  inline void Clear() {
    DelStr();
    Reset();
  }

  void CopyStr(const char *src, size_t size) {
    meta.ptr = new char[size+1];

    assert(meta.ptr != nullptr && src);
    std::memcpy(meta.ptr, src, size);

    meta.ptr[size] = '\0';
    meta.len = size;
  }

  void CopyStr(const char *src) {
    size_t other_len = std::strlen(src);
    CopyStr(src, other_len);
  }

  void CopyStr(const String& other) {
    size_t other_len = other.Length();
    CopyStr(other.CStr(), other_len);
  }
};

} /* xvzd */


#endif  // XVZD_STRING_H_
