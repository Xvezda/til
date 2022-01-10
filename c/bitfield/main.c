#include <stdio.h>

struct block {
    unsigned int width : 4;
    unsigned int height : 4;

    struct {
        unsigned int b0 : 1;
        unsigned int b1 : 1;
        unsigned int b2 : 1;
        unsigned int b3 : 1;

        unsigned int b4 : 1;
        unsigned int b5 : 1;
        unsigned int b6 : 1;
        unsigned int b7 : 1;

        unsigned int b8 : 1;
        unsigned int b9 : 1;
        unsigned int b10 : 1;
        unsigned int b11 : 1;

        unsigned int b12 : 1;
        unsigned int b13 : 1;
        unsigned int b14 : 1;
        unsigned int b15 : 1;
    };
};

#define FULL_BLOCK "██"
#define EMPTY_BLOCK "  "

#define PICK_PIECE(block, position) (block.b##position)
#define B_STRINGIFY(buffer, block) \
    snprintf((buffer), sizeof(buffer), \
            "%s%s%s%s\n"  \
            "%s%s%s%s\n"  \
            "%s%s%s%s\n"  \
            "%s%s%s%s\n", \
    ((PICK_PIECE(block, 0) ? FULL_BLOCK : EMPTY_BLOCK)), \
    ((PICK_PIECE(block, 1) ? FULL_BLOCK : EMPTY_BLOCK)), \
    ((PICK_PIECE(block, 2) ? FULL_BLOCK : EMPTY_BLOCK)), \
    ((PICK_PIECE(block, 3) ? FULL_BLOCK : EMPTY_BLOCK)), \
    ((PICK_PIECE(block, 4) ? FULL_BLOCK : EMPTY_BLOCK)), \
    ((PICK_PIECE(block, 5) ? FULL_BLOCK : EMPTY_BLOCK)), \
    ((PICK_PIECE(block, 6) ? FULL_BLOCK : EMPTY_BLOCK)), \
    ((PICK_PIECE(block, 7) ? FULL_BLOCK : EMPTY_BLOCK)), \
    ((PICK_PIECE(block, 8) ? FULL_BLOCK : EMPTY_BLOCK)), \
    ((PICK_PIECE(block, 9) ? FULL_BLOCK : EMPTY_BLOCK)), \
    ((PICK_PIECE(block, 10) ? FULL_BLOCK : EMPTY_BLOCK)), \
    ((PICK_PIECE(block, 11) ? FULL_BLOCK : EMPTY_BLOCK)), \
    ((PICK_PIECE(block, 12) ? FULL_BLOCK : EMPTY_BLOCK)), \
    ((PICK_PIECE(block, 13) ? FULL_BLOCK : EMPTY_BLOCK)), \
    ((PICK_PIECE(block, 14) ? FULL_BLOCK : EMPTY_BLOCK)), \
    ((PICK_PIECE(block, 15) ? FULL_BLOCK : EMPTY_BLOCK)))

int main() {
    struct block block = {
        .width = 3,
        .height = 2,

        1, 0, 0, 0,
        1, 1, 0, 0,
        0, 1, 0, 0,
        0, 0, 0, 0,
    };
    printf("width: %d, height: %d\n", block.width, block.height);
    printf("size: %zu\n", sizeof block);

    char buffer[0x100];
    B_STRINGIFY(buffer, block);
    printf("%s\n", buffer);

    return 0;
}
