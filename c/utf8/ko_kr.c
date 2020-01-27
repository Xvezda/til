#include <stdio.h>


int main(int argc, char **argv)
{
    char ca[] = { 0xEA, 0xB0, 0x80 };

    for (int i = 0; i < sizeof(ca) / sizeof(ca[0]); ++i) {
        printf("%c", ca[i]);
    }
    printf("\n");

    return 0;
}
