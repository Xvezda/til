#define  _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>


int print_shape(const char *utf8str);


int main(void) {
    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
    while ((linelen = getline(&line, &linecap, stdin)) > 0) {
        if (line[linelen-1] == '\n') {
            line[linelen-1] = '\0';
        }
        print_shape(line);
    }
    free(line);

    return 0;
}


int print_shape(const char *utf8str) {
    if (!utf8str) return 1;

    const int cell_width = 4;
    const int cell_height = 2;
    const int base_bits = cell_width * cell_height;

    const char *cell_block = "█";
    const char *cell_empty = " ";

    int len = strlen(utf8str);

    int cells[cell_height][len * cell_width + cell_width];
    memset(cells, 0, sizeof cells);

    uint8_t c;
    for (int i = 0; i < len; ++i) {
        c = utf8str[i];
        for (int j = 0; j < base_bits; ++j) {
            int row = j / cell_width;
            int col = i * cell_width + j % cell_width;
            cells[row][col] = (0x80 & (c << j)) ? 1 : 0;
        }
    }

    for (int j = 0; j < cell_height; ++j) {
        for (int i = 0; i < len * cell_width; ++i) {
            printf("%s", cells[j][i] ? cell_block : cell_empty);
        }
        puts("");
    }
    return 0;
}

