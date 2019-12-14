#include <iostream>
#include "xvzd_string.h"


using xvzd::String;

int main(void) {
  String str_arr[] = {
    String("foo bar"),
    String(1234),
    String('c')
  };

  for (auto i = 0; i < 3; ++i) {
    std::cout << str_arr[i] << std::endl;
  }

  String str("Hello");

  std::cout << str << std::endl;
  std::cout << str.append(", World!") << std::endl;

  str += " :)";
  std::cout << str << std::endl;

  std::cout << str + " LOL" << std::endl;
  std::cout << str << std::endl;

  return 0;
}
