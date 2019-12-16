#ifndef XVZD_INTERFACE_H_
#define XVZD_INTERFACE_H_

namespace xvzd {

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


class Comparable {
public:
  virtual ~Comparable() {}
  virtual bool Equal(const Comparable& other) const = 0;
};


class Collection {
public:
  virtual ~Collection() {}
};


}  // namespace xvzd

#endif  // XVZD_INTERFACE_H_
