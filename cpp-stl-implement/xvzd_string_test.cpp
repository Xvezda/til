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

  std::cout << String("-", 10) << std::endl;

  str = String("The quick brown fox jumps over the lazy dog.");
  std::cout << str.Slice(4, 19) << std::endl;
  std::cout << str.Slice(-28) << std::endl;
  std::cout << str.Substr(-24, 11).Repeat(3) << std::endl;

  char word[] = "fox";
  int idx = str.IndexOf(word);
  std::cout << "IndexOf(" << word << "): " << idx << std::endl;

  str = String("A");
  std::cout << str.CharCodeAt(0) << std::endl;

  std::cout << String(123.456) << std::endl;

  str = "no alloc no alloc no alloc no alloc no alloc";
  str = "no new memory allocation";
  std::cout << str << std::endl;

  str = "foo baz";
  str = str.Insert(4, "bar ");
  std::cout << str << std::endl;
  /* std::cout << str.Insert(4, 'z') << std::endl; */

  str.Erase(0, 4);
  std::cout << str << std::endl;


  return 0;
}
