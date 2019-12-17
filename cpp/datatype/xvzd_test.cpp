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

  arr += 123;
  arr += 456;
  arr += 789;

  std::cout << arr[0] << std::endl;
  std::cout << arr[1] << std::endl;
  std::cout << arr[-1] << std::endl;

  std::cout << arr << std::endl;

  /* Array<Int> arrcpy; */
  /* arrcpy = arr; */
  Array<Int> arrcpy = arr;
  std::cout << arrcpy << std::endl;
  std::cout << arr + arrcpy << std::endl;

  String str("hello");
  std::cout << str << std::endl;

  Array<Object*> oarr;
  oarr.Push(new Int(123));
  oarr.Push(new String("foobar"));

  std::cout << oarr << std::endl;

  for (size_t i = 0; i < oarr.Size(); ++i) {
    delete oarr.Pop();
  }

  String sc('c');
  std::cout << sc << std::endl;

  String divider('-', 10);
  std::cout << divider.Concat(String('+', 10)) << std::endl;
  std::cout << divider.Append(String('-', 20)) << std::endl;

  String s1("abc");
  String s2(s1);

  std::cout << (s2 + "def") * 2 << std::endl;

  return 0;
}
