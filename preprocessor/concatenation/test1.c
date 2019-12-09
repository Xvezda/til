#include <stdio.h>

#define CONCAT_MESSAGE(msg) "Hello " #msg " :)"

#define _DEFINE_PRINT_FUNC(name) \
    void print_ ## name(char *msg) { \
        printf("this is %s func \\w message: %s\n", #name, msg); \
    }
#define CALL_PRINT(suffix, msg) print_ ## suffix(#msg)


_DEFINE_PRINT_FUNC(foo)
_DEFINE_PRINT_FUNC(bar)


int main(void) {
    printf("%s\n", CONCAT_MESSAGE("james"));
    printf("%s\n", CONCAT_MESSAGE("mike"));
    printf("%s\n", CONCAT_MESSAGE("chris"));

    CALL_PRINT(foo, hello);
    CALL_PRINT(bar, world);

    return 0;
}


