#ifndef XVZD_ARRAY_H_
#define XVZD_ARRAY_H_

#include "xvzd_common.h"
#include "xvzd_object.h"

namespace xvzd {


const auto kMinimumCapacity = 0x10;

template <typename T>
class Array : public Object {
public:
  Array() : Array(kMinimumCapacity) {}

  Array(size_t size) : Object(), idx(0) {
    cap = size;
    items = new T[cap];
#ifdef DEBUG
    std::cout << __FILE__ << ':' << __LINE__ << ": "
      << "new array -> capacity: " << cap << std::endl;
#endif
  }

  virtual ~Array() {
    if (items) {
#ifdef DEBUG
      std::cout << __FILE__ << ':' << __LINE__ << ": "
        << "del array" << std::endl;
#endif
      delete[] items;
      items = nullptr;
      cap = 0;
    }

    if (cstr_ptr) {
      delete[] cstr_ptr;
      cstr_ptr = nullptr;
    }
  }

  const Array<T>& Push(const T& item) {
    items[idx++] = item;

    if (idx > static_cast<int>(cap)) {
      size_t inc = cap << 1;
      T* tmp = new T[inc];
      for (size_t i = 0; i < inc; ++i) {
        tmp[i] = At(i);
      }
      delete[] items;
      items = tmp;
    }
    return *this;
  }

  const T& Pop() {
    return items[--idx];
  }

  T& At(int idx) const {
    if (idx < 0) {
      idx = Size() + idx;
      if (idx < 0) {
        idx = 0;
      }
    }
    return items[idx];
  }

  virtual xvzd_inline__ size_t Size() const {
    return idx;
  }

  const T& operator[](int idx) {
    return At(idx);
  }

  virtual const char* Cstr() {
    size_t total = 0;

    total += std::strlen("[");
    for (size_t i = 0; i < Size(); ++i) {
      total += (std::strlen(At(i).Cstr()) + \
          (i != Size() - 1 ? std::strlen(", ") : 0));
    }
    total += std::strlen("]");
#ifdef DEBUG
    std::cout << __FILE__ << ':' << __LINE__ << ": "
      << "total: " << total << std::endl;
#endif
    cstr_ptr = new char[total+1];
    cstr_ptr[0] = '\0';

    std::strncat(cstr_ptr, "[", std::strlen("["));
    for (size_t i = 0; i < Size(); ++i) {
      std::strncat(cstr_ptr, At(i).Cstr(), std::strlen(At(i).Cstr()));
      const char* sep = (i != Size() - 1 ? ", " : "");
      std::strncat(cstr_ptr, sep, std::strlen(sep));
    }
    std::strncat(cstr_ptr, "]", std::strlen("]"));
    cstr_ptr[total] = '\0';

    return cstr_ptr;
  }

private:
  size_t cap;
  int idx;

  T* items;
};

template <>
const char* Array<Object*>::Cstr() {
  size_t total = 0;

  total += std::strlen("[");
  for (size_t i = 0; i < Size(); ++i) {
    total += (std::strlen(At(i)->Cstr()) + \
        (i != Size() - 1 ? std::strlen(", ") : 0));
  }
  total += std::strlen("]");
#ifdef DEBUG
  std::cout << __FILE__ << ':' << __LINE__ << ": "
    << "total: " << total << std::endl;
#endif
  cstr_ptr = new char[total+1];
  cstr_ptr[0] = '\0';

  std::strncat(cstr_ptr, "[", std::strlen("["));
  for (size_t i = 0; i < Size(); ++i) {
    std::strncat(cstr_ptr, At(i)->Cstr(), std::strlen(At(i)->Cstr()));
    const char* sep = (i != Size() - 1 ? ", " : "");
    std::strncat(cstr_ptr, sep, std::strlen(sep));
  }
  std::strncat(cstr_ptr, "]", std::strlen("]"));
  cstr_ptr[total] = '\0';

  return cstr_ptr;
}


}  // namespace xvzd

#endif  // XVZD_ARRAY_H_
