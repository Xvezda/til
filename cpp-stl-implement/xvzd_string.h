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
    meta.len = 0;
    meta.ptr = nullptr;
  }

  String(char other) {
    copy_str(&other, 1);
  }

  String(const char* other) {
    copy_str(other);
  }

  String(const String& other) {
    copy_str(other);
  }

  String(int number) {
    size_t len = std::snprintf(nullptr, 0, "%d", number);
    char *tmp = new char[len+1];
    std::snprintf(tmp, len+1, "%d", number);
    tmp[len] = '\0';

    copy_str(tmp, len);

    delete[] tmp;
  }

  ~String() {
    if (!meta.ptr && meta.len) {
      clear();
    }
  }

  size_t length() const {
    return meta.len;
  }

  const char* c_str() const {
    return meta.ptr;
  }

  String& append(const String& other) {
    size_t other_len = other.length();
    // Make temporal copy
    char *tmp = new char[meta.len + other_len + 1];
    std::memcpy(tmp, meta.ptr, meta.len);
    std::memcpy(tmp+meta.len, other.c_str(), other_len);
    tmp[meta.len + other_len] = '\0';

    del_str();
    meta.ptr = tmp;

    meta.len += other_len;

    return *this;
  }

  String& operator=(const String& other) {
    if (this == &other) return *this;

    clear();
    copy_str(other.c_str(), other.length());

    return *this;
  }

  const String operator+(const String& other) {
    String cpy(*this);
    cpy += other;
    return cpy;
  }

  String& operator+=(const String& other) {
    append(other);
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, const String& self) {
    os << self.c_str();
    return os;
  }

private:
  str_meta_t meta;

  void reset() {
    meta.ptr = nullptr;
    meta.len = 0;
  }

  void del_str() {
    delete[] meta.ptr;
  }

  void clear() {
    del_str();
    reset();
  }

  void copy_str(const char *src, size_t size) {
    meta.ptr = new char[size+1];

    assert(meta.ptr != nullptr && src);
    std::memcpy(meta.ptr, src, size);

    meta.ptr[size] = '\0';
    meta.len = size;
  }

  void copy_str(const char *src) {
    size_t other_len = std::strlen(src);
    copy_str(src, other_len);
  }

  void copy_str(const String& other) {
    size_t other_len = other.length();
    copy_str(other.c_str(), other_len);
  }
};

} /* xvzd */


#endif  // XVZD_STRING_H_
