#include <iostream>

#include "xvzd_object.h"
#include "xvzd_array.h"
#include "xvzd_string.h"

using xvzd::Object;
using xvzd::Array;
using xvzd::String;


int main(void) {
  Array<Object*> arr;

  arr.Push(new String("foo"));
  arr.Push(new String("bar"));
  arr.Push(new String("baz"));

  std::cout << *arr[-1] << std::endl;
  std::cout << *arr[-2] << std::endl;

  std::cout << arr << std::endl;

  for (int i = 0, size = arr.Size(); i < size; ++i) {
    Object *ptr = arr[i];
    delete ptr;

    arr.Pop();
  }
  return 0;
}

