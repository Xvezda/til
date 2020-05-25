#ifndef XVZD_COMMON_H_
#define XVZD_COMMON_H_

#include <iostream>
#include <fstream>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <cmath>
#include <cassert>

#include "xvzd_interfaces.h"

namespace xvzd {

#define xvzd_inline__ inline


#define MAX(x, y) ((x) < (y) ? (y) : (x))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

#define ctoi(c) (static_cast<int>(('0' <= (c) && (c) <= '9') ? ((c) - '0') : 0))
#define itoc(i) (static_cast<char>((i) + '0'))


#define XVZD_DEFAULT_BUFFER_SIZE 0x200
#if XVZD_DEFAULT_BUFFER_SIZE < 2
  #error buffer size must bigger than 2
#endif
const auto kDefaultBufferSize = XVZD_DEFAULT_BUFFER_SIZE;

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
