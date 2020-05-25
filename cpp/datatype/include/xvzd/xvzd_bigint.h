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

  virtual const BigInt& Assign(const BigInt& other) {
    if (this == &other) return *this;
    Clear();
    for (size_t i = 0; i < other.Length(); ++i) {
      Push(other[i]);
    }
    return *this;
  }

  virtual int Compare(const BigInt& other) const {
    if (negative == other.negative) {
      if (Length() != other.Length()) {
        if (negative) {
          return other.Length() - Length();
        }
        return Length() - other.Length();
      }
      for (size_t i = 0; i < Length(); ++i) {
        int a = ctoi(At(i));
        int b = ctoi(other.At(i));
        if (a == b) continue;
        if (negative) {
          if (a > b) return -1;
          if (a < b) return 1;
        } else {
          if (a < b) return -1;
          if (a > b) return 1;
        }
      }
    } else {
      if (negative) {
        return -1;
      } else if (other.negative) {
        return 1;
      }
    }
    return 0;
  }

  const BigInt Add(const BigInt& other) const {
    BigInt ret;

    // Make copy of this and other
    BigInt a(*this);
    BigInt b(other);

    // Padding gap with zeros
    int gap;
    gap = a.Length() - b.Length();
    if (0 < gap) {
      b.Assign(b.Lpad(std::abs(gap), "0"));
    } else {
      a.Assign(a.Lpad(std::abs(gap), "0"));
    }

    // Now both are same length
    bool carriage = false;
    for (size_t i = 0, len = b.Length(); i < len; ++i) {
      int sum;
      int offset = len - i - 1;

      int a_ = ctoi(a[offset]);
      int b_ = ctoi(b[offset]);

      sum = a_ + b_;

      if (carriage) {
        sum += 1;
      }

      if (sum / 10) {
        carriage = true;
      } else {
        carriage = false;
      }

      if (!i) {
        ret.Assign(String(itoc(sum % 10)));
      } else {
        ret.Push(itoc(sum % 10));
      }
    }

    if (carriage) {
      ret.Push('1');
    }
    return ret.Reverse();
  }

  const BigInt Sub(const BigInt& other) const {
    BigInt ret;

    // Make copy of this and other
    BigInt a(*this);
    BigInt b(other);

    if ((a.negative && !b.negative) || (!a.negative && b.negative)) {
      ret = a.Add(b);
      ret.negative = negative;
      return ret;
    }

    if (a.Compare(b) < 0) {
      BigInt tmp = a;
      a = b;
      b = tmp;

      ret.negative = true;
    }

    // Padding gap with zeros
    int gap;
    gap = a.Length() - b.Length();
    if (0 < gap) {
      b.Assign(b.Lpad(std::abs(gap), "0"));
    } else {
      a.Assign(a.Lpad(std::abs(gap), "0"));
    }

    // Now both are same length
    bool carriage = false;
    for (size_t i = 0, len = b.Length(); i < len; ++i) {
      int sub;
      int offset = len - i - 1;

      int a_ = ctoi(a[offset]);
      int b_ = ctoi(b[offset]);

      sub = a_ + (10 - b_);

      if (carriage) {
        sub -= 1;
      }

      if (sub / 10) {
        carriage = false;
      } else {
        carriage = true;
      }

      if (!i) {
        ret.Assign(String(itoc(sub % 10)));
      } else {
        ret.Push(itoc(sub % 10));
      }
    }
    ret = ret.Reverse();

    if (Compare(other) < 0) {
      ret.negative = true;
    }
    return ret;
  }

  const BigInt operator+(const BigInt& other) {
    return Add(other);
  }

  const BigInt operator-(const BigInt& other) {
    return Sub(other);
  }

  const String ToString() const {
    if (negative) {
      return String("-") + String::ToString();
    }
    return String::ToString();
  }

protected:
  using String::Assign;
  using String::Compare;
  using String::Equal;
private:
  bool negative;
};

}  // namespace xvzd

#endif  // XVZD_BIGINT_H_
