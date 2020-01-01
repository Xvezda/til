#ifndef XVZD_INTERFACE_H_
#define XVZD_INTERFACE_H_

namespace xvzd {
class Object;
class String;
}  // namespace xvzd}

namespace xvzd {


template <typename T>
class Assignable {
public:
  virtual ~Assignable() {}
  virtual const T& Assign(const T& other) = 0;
};


template <typename T>
class Comparable {
public:
  virtual ~Comparable() {}
  virtual int Compare(const T& other) const = 0;
  virtual bool Equal(const T& other) const = 0;
};


class Callable {
public:
  virtual ~Callable() {}
  virtual Object Call() = 0;
};


template <typename T>
class Collection {
public:
  virtual ~Collection() {}
  virtual const T& At(int idx) const = 0;
  virtual const Collection<T>& Push(const T& item) = 0;
};


class Printable {
public:
  virtual ~Printable() {}
  virtual const char *Cstr() const = 0;
  virtual const String ToString() const = 0;
};


class Iterable {
public:
  virtual ~Iterable() {}
  virtual const Iterable& Next() = 0;
};


}  // namespace xvzd

#endif  // XVZD_INTERFACE_H_
