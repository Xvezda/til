#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


#define UTF8_BYTE1 0x80
#define UTF8_BYTE2 0xC0
#define UTF8_BYTE3 0xE0
#define UTF8_BYTE4 0xF0

int main(int argc, char **argv)
{
    int idx = 0;
    uint32_t code = 0;
    for (;; ++idx) {
        char c = getchar();
        // You can specify end of string by null even on utf-8
        // Because of it has backward compatibility with ASCII
        if (c == EOF || c == '\n' || c == '\0') break;

        printf("idx: %d\n", idx);

        uint8_t uc = (uint8_t) c;
        uint8_t mask  = 0xF0;

        if (!(0x80 & uc)) {
            printf("current idx is ascii -> %d\n", idx);
            code = (uint32_t) c;

            printf("code: 0x%02X\n", code);
        } else {
            int len;
            switch (mask & uc) {
            case UTF8_BYTE2:
                len = 2;
                code = 0x1F & uc;
                break;
            case UTF8_BYTE3:
                len = 3;
                code = 0x0F & uc;
                break;
            case UTF8_BYTE4:
                len = 4;
                code = 0x07 & uc;
                break;
            default:
                fprintf(stderr, "invalid utf8 character found: 0x%02X\n", uc);
                return EXIT_FAILURE;
            }
            for (int i = 1; i < len; ++i) {
                code <<= 6;

                char c = getchar();
                uint8_t uc = (uint8_t) c;

                if ((0xC0 & uc) & 0x40) {
                    fprintf(stderr, "invalid utf8 character found");
                    return EXIT_FAILURE;
                }
                code |= 0x3F & uc;
            }
            printf("code: U+%02X\n", code);
        }
        code = 0;
    }
    return EXIT_SUCCESS;
}
