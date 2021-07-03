#include <iostream>

/*
 * See: https://www.cplusplus.com/reference/ios/ios/tie/
 */

int main(void)
{
  // Print what is tied to iostream by default
  std::cout << "cout: " << &std::cout << " -> " << std::cout.tie() << std::endl;
  std::cout << "cin: " << &std::cin << " -> " << std::cin.tie() << std::endl;
  std::cout << "cerr: " << &std::cerr << " -> " << std::cerr.tie() << std::endl;
  std::cout << "clog: " << &std::clog << " -> " << std::clog.tie() << std::endl;

  return 0;
}
