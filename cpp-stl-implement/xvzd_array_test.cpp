#include <iostream>

#include "xvzd_object.h"
#include "xvzd_array.h"
#include "xvzd_string.h"

using xvzd::Object;
using xvzd::Array;
using xvzd::String;


int main(void) {
  Array<String> arr;

  arr.Push("foo");
  arr.Push("bar");
  arr.Push("baz");

  std::cout << arr[-1] << std::endl;
  std::cout << arr[-2] << std::endl;

  std::cout << arr << std::endl;

  return 0;
}

