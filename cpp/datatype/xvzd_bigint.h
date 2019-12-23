#ifndef XVZD_BIGINT_H_
#define XVZD_BIGINT_H_

#include "xvzd_common.h"
#include "xvzd_string.h"

namespace xvzd {


class BigInt : public String {
public:
  BigInt() : String("0") {}

  template <typename T>
  BigInt(const T& other) : String(other) {}

  virtual ~BigInt() {}

  using String::Assign;

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

    // Padding gap with space
    size_t gap;
    if (Length() < other.Length()) {
      gap = other.Length() - Length();
      Assign(Lpad(gap));
    } else {
      gap = Length() - other.Length();
      other.Assign(other.Lpad(gap));
    }
    // Now both are same length
    bool up = false;
    for (size_t i = Length(); i != 0; --i) {
      if (At(i-1) == ' ' && other.At(i-1) == ' ') break;

      int sum = ctoi(At(i-1)) + ctoi(other.At(i-1)) + (up ? 1 : 0);
      if (sum / 10) {
        up = true;
      } else {
        up = false;
      }
      sum %= 10;
      if (ret == "0") ret.Assign(String(itoc(sum)));
      else ret.Append(String(itoc(sum)));
    }
    return ret.Reverse();
  }
private:
};

}  // namespace xvzd

#endif  // XVZD_BIGINT_H_
