// Copyright (c) 2020 Xvezda <xvezda@naver.com>
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


#ifdef DEBUG
#   define DEBUG_PRINTF(fmt, ...) \
    do { \
        fprintf(stderr, "%s:%d:" fmt, __FILE__, __LINE__, __VA_ARGS__); \
    } while (0)
#else
#   define DEBUG_PRINTF(fmt, ...) \
    do {} while (0)
#endif


static const uint8_t jpg_magic[] = {
    0XFF, 0xD8, 0xFF
};

static const uint8_t png_magic[] = {
    0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A
};

typedef enum IMAGE_TYPE {
    XXX = -1, JPG, PNG
} IMAGE_TYPE;

static const uint8_t *magic_table[] = {
    [JPG] = jpg_magic,
    [PNG] = png_magic,
    NULL
};


int analyze_image(const char *path);
IMAGE_TYPE imgcmp(const void *bufptr);
int analyze_png(const void *bufptr);


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s [images ...]\n", argv[0]);

        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        analyze_image(argv[i]);
    }
    return 0;
}


int analyze_image(const char *path) {
    FILE *image_fp = fopen(path, "rb");
    if (!image_fp) return 1;

    fseek(image_fp, 0, SEEK_END);
    long image_size = ftell(image_fp);
    rewind(image_fp);

    // Make buffer with image size
    int is_malloc = 0;
    uint8_t stack_buffer[BUFSIZ];
    uint8_t *image_buffer = stack_buffer;

    if (image_size > BUFSIZ) {
        image_buffer = malloc(image_size);
        if (!image_buffer) return 1;
        is_malloc = 1;
    }
    fread(image_buffer, 1, image_size, image_fp);

    // It is safe to access byte range 0-3
    // Because buffer size must be at least BUFSIZ
    DEBUG_PRINTF("first 4 bytes: %02X %02X %02X %02X\n",
        image_buffer[0], image_buffer[1], image_buffer[2], image_buffer[3]);

    IMAGE_TYPE image_type = imgcmp(image_buffer);
    switch (image_type) {
        case PNG:
            puts("this is png :)");
            break;
        case JPG:
            puts("this is jpg :)");
            break;
        case XXX:
        default:
            puts("unknown file type :(");
            break;
    }

    if (is_malloc) free(image_buffer);

    return 0;
}


IMAGE_TYPE imgcmp(const void *bufptr) {
    if (!bufptr) goto error;

    for (int i = 0; magic_table[i]; ++i) {
        if (!memcmp(bufptr, magic_table[i], sizeof *magic_table[i]))
            return i;
    }
error:
    return XXX;
}


int analyze_png(const void *bufptr) {
    (void) bufptr;  // TODO

    return 0;
}
