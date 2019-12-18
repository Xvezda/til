#ifndef XVZD_COMMON_H_
#define XVZD_COMMON_H_

#include <iostream>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>

#include "xvzd_interfaces.h"

namespace xvzd {

#define xvzd_inline__ inline

/**
 * Dereference function
 * https://stackoverflow.com/a/36918194
 */
template <typename T>
std::enable_if_t< std::is_pointer<T>::value,
  std::remove_pointer_t<T>& > dereference(T& t) {
  return *t;
}

template <typename T>
std::enable_if_t< !std::is_pointer<T>::value, T& > dereference(T& t) {
  return t;
}

}  // namespace xvzd

#endif  // XVZD_COMMON_H_
