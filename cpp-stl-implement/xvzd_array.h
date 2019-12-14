#ifndef XVZD_ARRAY_H_
#define XVZD_ARRAY_H_


#include <cstdlib>
#include <cmath>
#include "xvzd_object.h"


namespace xvzd {


const size_t LOWEST_CAPACITY = 0x10;

template <typename T>
class Array : public Object {
public:
  Array() {
    Init();
  }

  Array(size_t size) {
    Init(size);
  }

  ~Array() {
    if (items) {
      delete[] items;
      items = nullptr;
    }
  }

  Array& Push(T item) {
    items[idx++] = item;
    ++size;
    if (size > capacity_) IncCapacity();
    return *this;
  }

  Array& Append(T item) {
    return push(item);
  }

  T Pop() {
    --size;
    return items[idx--];
  }

  const T& operator[](int idx) {
    if (idx >= static_cast<int>(size)) {
      // TODO: Throw error
    } else if (idx < 0) {
      int new_idx = size - std::abs(idx);
      if (new_idx < 0) {
        // TODO: Throw error
        new_idx = 0;
      }
      idx = new_idx;
    }
    return items[idx];
  }

  inline size_t Size() {
    return size;
  }

  virtual const char* CStr() const {
    const char* ret = "[object Array]";
    return ret;
  }

private:
  inline void IncCapacity() {
    // Double current capacity
    capacity_ <<= 1;
  }

  void Init() {
    capacity_ = LOWEST_CAPACITY;
    items = new T[capacity_];
    size = 0;
    unit = sizeof(T *);
    idx = 0;
  }

  void Init(size_t size_) {
    capacity_ = size_ & ~(LOWEST_CAPACITY | 1);
    items = new T[capacity_];
    size = size_;
    unit = sizeof(T *);
    idx = 0;
  }

  size_t capacity_;
  size_t size;
  size_t unit;
  int idx;
  T *items;
};


}  // namespace xvzd

#endif  // XVZD_ARRAY_H_