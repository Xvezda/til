#ifndef XVZD_TEST_H_
#define XVZD_TEST_H_

#include <gtest/gtest.h>
#include <iostream>

#define LOGGER(var) \
  std::cerr <<  "\033[0;36m" \
    << "[  LOGGER  ] " << __FILE__ << ':' << __LINE__ << ": " \
    << #var << ": " << var << std::endl


#endif  // XVZD_TEST_H_
