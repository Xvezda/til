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

    // Make copy of this and other
    BigInt cpy(*this);
    BigInt other_cpy(other);

    // Padding gap with spaces
    size_t gap;
    if (cpy.Length() < other_cpy.Length()) {
      gap = other_cpy.Length() - cpy.Length();
      cpy.Assign(cpy.Lpad(gap));
    } else {
      gap = cpy.Length() - other_cpy.Length();
      other_cpy.Assign(other_cpy.Lpad(gap));
    }
    // Now both are same length
    bool up = false;
    for (size_t i = cpy.Length(); i != 0; --i) {
      if (cpy.At(i-1) == ' ' && other_cpy.At(i-1) == ' ') break;
      int sum = ctoi(cpy.At(i-1)) + ctoi(other_cpy.At(i-1)) + \
                (up ? 1 : 0);
      if (sum / 10) {
        up = true;
      } else {
        up = false;
      }
      sum %= 10;
      // Write down calculation result
      if (ret == 0 && (!up || i == cpy.Length())) {
        ret.Assign(String(sum));
      } else {
        ret.Append(sum);
      }
    }
    if (up) ret.Append(1);
    return ret.Reverse();
  }

  const BigInt operator+(const BigInt& other) {
    return Add(other);
  }

  const BigInt Sub(const BigInt& other) {
    bool neg = false;

    BigInt ret;

    // Make copy of this and other
    BigInt cpy(*this);
    BigInt other_cpy(other);

    // Padding gap with spaces
    size_t gap;
    if (cpy.Length() < other_cpy.Length()) {
      gap = other_cpy.Length() - cpy.Length();
      cpy.Assign(cpy.Lpad(gap));
    } else {
      gap = cpy.Length() - other_cpy.Length();
      other_cpy.Assign(other_cpy.Lpad(gap));
    }
    // Now both are same length
    bool down = false;
    for (size_t i = cpy.Length(); i != 0; --i) {
      if (cpy.At(i-1) == ' ' && other_cpy.At(i-1) == ' ') break;
      int sub = (ctoi(cpy.At(i-1)) - (down ? 1 : 0)) - \
                ctoi(other_cpy.At(i-1));
      if (sub < 0) {
        if (i-1 != 0 && cpy.At(i-2)) {
          sub = 10 + sub;
        } else {
          sub = std::abs(sub);
        }
        down = true;
      } else {
        down = false;
      }
      /* sum %= 10; */
      if (ret == 0) {
        ret.Assign(String(sub));
      } else {
        ret.Append(sub);
      }
    }
    if (neg || down) ret.Append('-');
    return ret.Reverse();
  }

  const BigInt operator-(const BigInt& other) {
    return Sub(other);
  }

  bool IsNegative() const {
    return Slice(0, 1) == '-';
  }
private:
};

}  // namespace xvzd

#endif  // XVZD_BIGINT_H_
