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

  /*
  Array<Object*> oarr;
  oarr.Push(new Int(123));
  oarr.Push(new String("foobar"));

  std::cout << oarr << std::endl;

  for (size_t i = 0; i < oarr.Size(); ++i) {
    delete oarr.Pop();
  }
  */

  String sc('c');
  std::cout << sc << std::endl;

  String divider('-', 10);
  std::cout << divider.Concat(String('+', 10)) << std::endl;
  std::cout << divider.Append(String('-', 20)) << std::endl;

  String s1("abc");
  String s2(s1);

  std::cout << (s2 + "def") * 2 << std::endl;
  std::cout << Char('z') * 10 << std::endl;

  String sentence = "The quick brown fox jumps over the lazy dog";
  std::cout << sentence.Slice(5, -4) << std::endl;

  std::cout << String("hello").Substr(-2, 2) << std::endl;
  std::cout << String("hello").Substring(3, 1) << std::endl;
  std::cout << String("hello").Substring(-2, 1) << std::endl;

  std::cout << "fox idx: " << sentence.Find("fox") << std::endl;

  std::cout << String("foo|bar|baz").Split("|") << std::endl;
  String s3("asdf");
  String s4("asdf");
  std::cout << (s3 == s4) << std::endl;

  Array<Int> a1;
  Array<Int> a2;

  a1.Push(1);
  a2.Push(1);
  a1.Push(2);
  a2.Push(2);
  a1.Push(3);
  a2.Push(3);

  std::cout << (a1 == a2) << std::endl;

  return 0;
}
