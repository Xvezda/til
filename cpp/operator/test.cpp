#include <iostream>


class TestClass {
public:
  TestClass() {
    msg = const_cast<char*>("hello world");
    num = 31337;
  }
  virtual ~TestClass() {}
  operator char*() {
    return msg;
  }
  operator int() {
    return num;
  }
private:
  char* msg;
  int num;
};


int main(void) {
  TestClass t;

  std::cout << static_cast<int>(t) << std::endl;
  std::cout << static_cast<char*>(t) << std::endl;

  return 0;
}
