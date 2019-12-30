#ifndef XVZD_BIGINT_H_
#define XVZD_BIGINT_H_

#include "xvzd_common.h"
#include "xvzd_string.h"

namespace xvzd {


class BigInt : public String {
public:
  using String::Assign;

  BigInt() : String("0") {}

  template <typename T>
  BigInt(const T& other) : String(other) {}

  virtual ~BigInt() {}

  virtual const BigInt& Assign(const BigInt& other) {
    if (this == &other) return *this;
    Clear();
    for (size_t i = 0; i < other.Length(); ++i) {
      Push(other[i]);
    }
    return *this;
  }

  const BigInt Add(const BigInt& other) const {
    BigInt ret;

    // Make copy of this and other
    BigInt cpy(*this);
    BigInt other_cpy(other);

    // Padding gap with spaces
    size_t gap;
    if (Length() < other_cpy.Length()) {
      gap = other_cpy.Length() - cpy.Length();
      cpy.Assign(cpy.Lpad(gap));
    } else {
      gap = cpy.Length() - other_cpy.Length();
      other_cpy.Assign(other_cpy.Lpad(gap));
    }
    // Now both are same length
    bool up = false;
    for (size_t i = cpy.Length(); i != 0; --i) {
      if (cpy.At(i-1) == ' ' && other_cpy.At(i-1) == ' ') {
        if (up) ret.Append('1');
        break;
      }
      int sum = ctoi(cpy.At(i-1)) + ctoi(other_cpy.At(i-1)) + (up ? 1 : 0);
      if (sum / 10) {
        up = true;
      } else {
        up = false;
      }
      sum %= 10;
      if (ret == "0") {
        ret.Assign(String(sum));
      } else {
        ret.Append(sum);
      }
    }
    return ret.Reverse();
  }
private:
};

}  // namespace xvzd

#endif  // XVZD_BIGINT_H_