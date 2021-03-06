#ifndef XVZD_ARRAY_H_
#define XVZD_ARRAY_H_

#include "xvzd_common.h"
#include "xvzd_object.h"
#include "xvzd_item.h"

namespace xvzd {
class String;
}  // namespace xvzd


namespace xvzd {


const auto kMinimumCapacity = 0x10;

template <typename T>
class Array
  : public Object, public Collection<T>,
    public Comparable< Array<T> >, public Assignable< Array<T> > {
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

  Array(const Array<T>& other) : Array(other.Size()) {
    Assign(other);
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

  virtual const Array<T>& Assign(const Array<T>& other) override {
    if (this == &other) return *this;

    for (size_t i = 0; i < other.Size(); ++i) {
      Push(other[i]);
    }
    return *this;
  }

  const T& At(int idx) const override {
    if (idx < 0) {
      idx = Size() + idx;
      if (idx < 0) {
        idx = 0;
      }
    }
    return items[idx];
  }

  const Array<T>& Append(const Array<T>& other) {
    for (size_t i = 0; i < other.Size(); ++i) {
      Push(other[i]);
    }
    return *this;
  }

  const Array<T> Concat(const Array<T>& other) const {
    Array<T> ret(*this);
    ret.Append(other);

    return ret;
  }

  virtual int Compare(const Array<T>& other) const override {
    int result = -1;
    for (size_t i = 0; i < Size() && i < other.Size(); ++i) {
      result = dereference(At(i)).Compare(dereference(other.At(i)));
      if (result) return result;
    }
    // If all elements are same in minimum range
    // return value by size comparison
    if (Size() < other.Size()) {
      return -1;
    } else if (Size() > other.Size()) {
      return 1;
    }
    return 0;
  }

  virtual bool Equal(const Array<T>& other) const override {
    if (Size() != other.Size()) return false;
    for (size_t i = 0; i < Size() && i < other.Size(); ++i) {
      if (At(i) != other.At(i)) return false;
    }
    return true;
  }

  int Find(const T& needle) const {
    for (size_t i = 0; i < needle.Size(); ++i) {
      if (At(i) == needle.At(i)) return i;
    }
    return -1;
  }

  int IndexOf(const T& needle) const {
    return Find(needle);
  }

  const String Join(const String& sep) const;

  const Collection<T>& Push(const T& item) override {
    items[idx++] = item;

    if (idx >= static_cast<int>(cap)) {
      size_t inc = cap << 1;
      T* tmp = new T[inc];
      for (int i = 0; i < idx; ++i) {
        tmp[i] = At(i);
      }
      delete[] items;
      items = tmp;

      cap = inc;
    }
    return *this;
  }

  const T& Pop() {
    return items[--idx];
  }

  const Array<T> Reverse() const {
    Array<T> ret;

    for (size_t i = Size(); i != 0; --i) {
      ret.Push(At(i-1));
    }
    return ret;
  }

  size_t Size() const override {
    return idx;
  }

  const Array<T>& operator=(const Array<T>& other) {
    return Assign(other);
  }

  bool operator==(const Array<T>& other) {
    return Equal(other);
  }

  bool operator!=(const Array<T>& other) {
    return !(*this == other);
  }

  const Array<T> operator+(const Array<T>& other) {
    return Array(*this).Concat(other);
  }

  const Array<T>& operator+=(const T& other) {
    Push(other);
    return *this;
  }

  const T& operator[](int idx) const {
    return At(idx);
  }

  virtual const char* Cstr() const override {
    size_t total = 0;

    total += std::strlen("[");
    for (size_t i = 0; i < Size(); ++i) {
      total += (std::strlen(dereference(At(i)).Cstr()) + \
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
      std::strncat(cstr_ptr,
          dereference(At(i)).Cstr(),
          std::strlen(dereference(At(i)).Cstr()));
      const char* sep = (i != Size() - 1 ? ", " : "");
      std::strncat(cstr_ptr, sep, std::strlen(sep));
    }
    std::strncat(cstr_ptr, "]", std::strlen("]"));
    cstr_ptr[total] = '\0';

    return cstr_ptr;
  }

protected:
  using Object::Compare;
  using Object::Equal;

private:
  size_t cap;
  int idx;

  T* items;
};


}  // namespace xvzd
#endif  // XVZD_ARRAY_H_
