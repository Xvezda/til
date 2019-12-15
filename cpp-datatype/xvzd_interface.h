#ifndef XVZD_INTERFACE_H_
#define XVZD_INTERFACE_H_

namespace xvzd {

class Printable {
public:
  virtual ~Printable() {}
  const char *Cstr() = 0;
private:
};

}  // namespace xvzd

#endif  // XVZD_INTERFACE_H_
