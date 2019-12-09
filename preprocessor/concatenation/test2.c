#include <stdio.h>

#define SPACE_TEST(msg) printf("%s\n", #msg);


int main(int argc, char **argv) {
    SPACE_TEST(hello world foo bar baz);  // It works. interesting :)

    return 0;
}


