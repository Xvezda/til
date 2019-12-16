#ifndef XVZD_INTERFACE_H_
#define XVZD_INTERFACE_H_

namespace xvzd {

class Printable {
public:
  virtual ~Printable() {}

  virtual const char *Cstr() const = 0;
  virtual size_t GetSize() const = 0;
  virtual const char* GetFmt() const = 0;
private:
};


class Iterable {
public:
  Iterable() {}
  virtual ~Iterable() {}
private:
};


}  // namespace xvzd

#endif  // XVZD_INTERFACE_H_
