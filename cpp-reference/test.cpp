#include <iostream>


using std::cout;

class Test
{
public:
  Test() : foo(123) {};
  ~Test() {};
  int& get_foo();
  void show_foo();
private:
  int foo;
};


int& Test::get_foo()
{
  return foo;
}


void Test::show_foo()
{
  cout << foo << '\n';
}


int main(void)
{
  Test t;

  int& ref = t.get_foo();
  t.show_foo();

  // Try to access private property
  ref = 321;
  // It works...
  t.show_foo();  // 321

  return 0;
}
