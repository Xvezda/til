#ifndef XVZD_TEST_H_
#define XVZD_TEST_H_

#include <gtest/gtest.h>
#include <iostream>

#include "xvzd_common.h"


#define LOGGER(var)                                           \
  std::cerr <<  "\033[0;36m"                                  \
    << "[  LOGGER  ] " << __FILE__ << ':' << __LINE__ << ": " \
    << #var << ": " << var                                    \
    << "\033[0;0m" << std::endl


#endif  // XVZD_TEST_H_
