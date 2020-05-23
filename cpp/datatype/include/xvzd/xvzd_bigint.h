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
    String ret = "";

    // Make copy of this and other
    BigInt cpy(*this);
    BigInt other_cpy(other);

    // Padding gap with zeros
    size_t gap;
    if (Length() < other_cpy.Length()) {
      gap = other_cpy.Length() - cpy.Length();
      cpy.Assign(cpy.Lpad(gap, "0"));
    } else {
      gap = cpy.Length() - other_cpy.Length();
      other_cpy.Assign(other_cpy.Lpad(gap, "0"));
    }

    // Now both are same length
    bool carriage = false;
    for (size_t i = 0, len = cpy.Length(); i < len; ++i) {
      int sum;
      int offset = len - i - 1;

      int a = ctoi(cpy[offset]);
      int b = ctoi(other_cpy[offset]);

      sum = a + b;

      if (carriage) {
        sum += 1;
      }

      if (sum / 10) {
        carriage = true;
      } else {
        carriage = false;
      }
      ret.Push(itoc(sum % 10));
    }

    if (carriage) {
      ret.Push('1');
    } else if (ret.Length() == 0) {
      ret = "0";
    }

    return ret.Reverse();
  }

  const BigInt operator+(const BigInt& other) {
    return Add(other);
  }
private:
  bool negative;
};

}  // namespace xvzd

#endif  // XVZD_BIGINT_H_
