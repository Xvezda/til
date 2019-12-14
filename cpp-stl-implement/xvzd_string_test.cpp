#include <iostream>
#include "xvzd_string.h"


using xvzd::String;

int main(void) {
  String str_arr[] = {
    String("foo bar"),
    String(1234),
    String('c')
  };

  for (int i = 0; i < 3; ++i) {
    std::cout << str_arr[i] << std::endl;
  }

  String str("Hello");

  std::cout << str << std::endl;
  std::cout << str.Append(", World!") << std::endl;

  str += " :)";
  std::cout << str << std::endl;

  std::cout << str + " LOL" << std::endl;
  std::cout << str << std::endl;

  std::cout << String('-', 10) << std::endl;

  for (int i = 0, len = str.Length(); i < len; ++i) {
    std::cout << str[i] << std::endl;
  }

  std::cout << String('-', 10) << std::endl;

  str = "asdf";
  std::cout << str[-1] << str[-2] << std::endl;

  std::cout << String("qwerty", 3) << std::endl;
  std::cout << String("zxcv").Repeat(5) << std::endl;
  std::cout << String(String("a")) << std::endl;
  std::cout << String(String("uiop"), 3) << std::endl;

  return 0;
}
