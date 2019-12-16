#include "xvzd.h"


using xvzd::Object;
using xvzd::Array;
using xvzd::String;

using xvzd::Int;
using xvzd::Char;
using xvzd::Float;

int main(void) {
  Int n(31337);
  Char c('A');

  std::cout << n << std::endl;
  std::cout << c << std::endl;

  c = 'B';
  std::cout << c << std::endl;

  Object o;
  std::cout << o << std::endl;

  Float f(123.456);
  std::cout << f << std::endl;

  Int* intptr = new Int(12345);
  std::cout << *intptr << std::endl;
  delete intptr;

  Array<Int> arr;
  arr.Push(123);
  arr.Push(456);
  arr.Push(789);

  std::cout << arr[0] << std::endl;
  std::cout << arr[1] << std::endl;
  std::cout << arr[-1] << std::endl;

  std::cout << arr << std::endl;

  String str("hello");
  std::cout << str << std::endl;

  Array<Object*> oarr;
  oarr.Push(new Int(123));
  oarr.Push(new String("foobar"));

  std::cout << oarr << std::endl;

  return 0;
}
