#include "xvzd.h"


using xvzd::Object;

using xvzd::Int;
using xvzd::Char;

int main(void) {
  Int n(31337);
  Char c('A');

  std::cout << n << std::endl;
  std::cout << c << std::endl;

  Object o;

  std::cout << o << std::endl;

  return 0;
}
