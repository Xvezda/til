#include "xvzd.h"


int main(void) {
  xvzd::Int n(31337);
  xvzd::Char c('A');

  std::cout << n << std::endl;
  std::cout << c << std::endl;

  c = 'B';
  std::cout << c << std::endl;

  xvzd::Object o;
  std::cout << o << std::endl;

  xvzd::Float f(123.456);
  std::cout << f << std::endl;

  xvzd::Int* intptr = new xvzd::Int(12345);
  std::cout << *intptr << std::endl;
  delete intptr;

  xvzd::Array<xvzd::Int> arr;

  arr += 123;
  arr += 456;
  arr += 789;

  std::cout << arr[0] << std::endl;
  std::cout << arr[1] << std::endl;
  std::cout << arr[-1] << std::endl;

  std::cout << arr << std::endl;

  /* Array<Int> arrcpy; */
  /* arrcpy = arr; */
  xvzd::Array<xvzd::Int> arrcpy = arr;
  std::cout << arrcpy << std::endl;
  std::cout << arr + arrcpy << std::endl;

  xvzd::String str("hello");
  std::cout << str << std::endl;

  // FIXME: Pointer array error
  /*
  Array<Object*> oarr;
  oarr.Push(new Int(123));
  oarr.Push(new String("foobar"));

  std::cout << oarr << std::endl;

  for (size_t i = 0; i < oarr.Size(); ++i) {
    delete oarr.Pop();
  }
  */

  xvzd::String sc('c');
  std::cout << sc << std::endl;

  xvzd::String divider('-', 10);
  std::cout << divider.Concat(xvzd::String('+', 10)) << std::endl;
  std::cout << divider.Append(xvzd::String('-', 20)) << std::endl;

  xvzd::String s1("abc");
  xvzd::String s2(s1);

  std::cout << (s2 + "def") * 2 << std::endl;
  std::cout << xvzd::Char('z') * 10 << std::endl;

  xvzd::String sentence = "The quick brown fox jumps over the lazy dog";
  std::cout << sentence.Slice(5, -4) << std::endl;

  std::cout << xvzd::String("hello").Substr(-2, 2) << std::endl;
  std::cout << xvzd::String("hello").Substring(3, 1) << std::endl;
  std::cout << xvzd::String("hello").Substring(-2, 1) << std::endl;

  std::cout << "fox idx: " << sentence.Find("fox") << std::endl;

  xvzd::Array<xvzd::String> sa = xvzd::String("foo|bar|baz").Split("|");
  std::cout << sa << std::endl;
  std::cout << sa.Join(", ") << std::endl;
  std::cout << xvzd::String(":").Join(sa) << std::endl;

  xvzd::String s3("asdf");
  xvzd::String s4("asdf");
  std::cout << (s3 == s4) << std::endl;

  xvzd::Array<xvzd::Int> a1;
  xvzd::Array<xvzd::Int> a2;

  a1.Push(1);
  a2.Push(1);
  a1.Push(2);
  a2.Push(2);
  a1.Push(3);
  a2.Push(3);

  std::cout << (a1 == a2) << std::endl;

  a2.Pop();
  std::cout << (a1 == a2) << std::endl;

  std::cout << xvzd::String("hello").Lpad(10).Rpad(5) + \
    xvzd::String("world") << std::endl;

  std::cout << xvzd::String("1234").IsDigit() << std::endl;
  std::cout << xvzd::String("1234a").IsDigit() << std::endl;

  std::cout << xvzd::String("").Length() << std::endl;

  xvzd::BigInt ia("1099511627776");
  xvzd::BigInt ib("1073741824");

  std::cout << ia + ib << std::endl;

  ia = "123456789123456789123456789";
  ib = "987654321987654321987654321";

  std::cout << ia + ib << std::endl;

  std::cout << xvzd::String("hello").Reverse() << std::endl;

  return 0;
}
