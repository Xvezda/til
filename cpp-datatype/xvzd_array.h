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

  const T& At(int idx) const {
    if (idx < 0) {
      idx = Size() + idx;
      if (idx < 0) {
        idx = 0;
      }
    }
    return items[idx];
  }

  virtual size_t Size() const {
    return idx;
  }

  const T& operator[](int idx) {
    return At(idx);
  }

private:
  size_t cap;
  int idx;

  T* items;
};

}  // namespace xvzd


#endif  // XVZD_ARRAY_H_
