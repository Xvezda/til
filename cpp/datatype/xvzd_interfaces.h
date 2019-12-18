#ifndef XVZD_INTERFACE_H_
#define XVZD_INTERFACE_H_

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


class Collection {
public:
  virtual ~Collection() {}
};


class Printable {
public:
  virtual ~Printable() {}
  virtual const char *Cstr() const = 0;
};


class Iterable {
public:
  virtual ~Iterable() {}
  virtual const Iterable& Next() = 0;
};


}  // namespace xvzd

#endif  // XVZD_INTERFACE_H_
