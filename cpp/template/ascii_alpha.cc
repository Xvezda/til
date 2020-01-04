#include <iostream>


struct CStrImpl {
  const char* c_str() {
    return const_cast<const char*>(reinterpret_cast<char*>(this));
  }
protected:
  CStrImpl() {}
};

template <char C = '!'>
struct Ascii : public CStrImpl {
  const char value;
  Ascii<C+1> next_;

  Ascii() : value(C) {}
};

template <>
struct Ascii<'~'> {
  const char value;
  const char next_;

  Ascii() : value('~'), next_('\0') {}
};


template <char C = 'A'>
struct Alpha : public CStrImpl {
  const char value;
  Alpha<C+1> next_;

  Alpha() : value(C) {}
};

template <>
struct Alpha<'Z'> {
  const char value;
  const char next_;

  Alpha() : value('Z'), next_('\0') {}
};

template <>
struct Alpha<'z'> {
  const char value;
  const char next_;

  Alpha() : value('z'), next_('\0') {}
};


int main(void) {
  Ascii<> ascii;  // Instanciatation
  std::cout << ascii.c_str() << std::endl;

  Alpha<> alpha_upper;
  Alpha<'a'> alpha_lower;
  std::cout << alpha_upper.c_str() << std::endl;
  std::cout << alpha_lower.c_str() << std::endl;

  return 0;
}

