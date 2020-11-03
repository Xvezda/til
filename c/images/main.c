// Copyright (c) 2020 Xvezda <xvezda@naver.com>
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#define  _POSIX_C_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>


#ifdef DEBUG
#   define DEBUG_PRINTF(fmt, ...) \
    do { \
        fprintf(stderr, "%s:%d:" fmt, __FILE__, __LINE__, __VA_ARGS__); \
    } while (0)
#else
#   define DEBUG_PRINTF(fmt, ...) \
    do {} while (0)
#endif


typedef enum IMAGE_TYPE {
    XXX = -1, JPG, PNG, GIF
} IMAGE_TYPE;

typedef int (*imgcmp_cb)(const void *bufptr);

typedef struct IMAGE_FILE {
    IMAGE_TYPE type;
    size_t size;
    size_t capacity;
    uint8_t *data;
} IMAGE_FILE;

IMAGE_FILE *image_open(const char *path);
int image_close(IMAGE_FILE *fp);

int analyze_image(const char *path);
IMAGE_TYPE imgcmp(const void *bufptr);

static int jpgcmp(const void *bufptr);
static int pngcmp(const void *bufptr);
static int gifcmp(const void *bufptr);

int png_info(IMAGE_FILE *png);


// Keep explicit and synchronized
static const imgcmp_cb imgcmp_table[] = {
    [JPG] = jpgcmp,
    [PNG] = pngcmp,
    [GIF] = gifcmp,
    NULL
};


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s [images ...]\n", argv[0]);

        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        if (analyze_image(argv[i])) return 1;
    }
    return 0;
}


IMAGE_FILE *image_open(const char *path) {
    FILE *fp = fopen(path, "rb");
    if (!fp) goto error;

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    IMAGE_FILE *ret = malloc(sizeof *ret);
    if (!ret) goto error;

    size_t capacity = size / BUFSIZ + BUFSIZ;
    ret->data = malloc(capacity);

    if (!ret->data) {
        free(ret);
        goto error;
    }

    ret->capacity = capacity;
    ret->size = size;

    fread(ret->data, 1, ret->size, fp);
    fclose(fp);

    ret->type = imgcmp(ret->data);

    return ret;

error:
    return NULL;
}


int image_close(IMAGE_FILE *fp) {
    if (!fp) return 1;

    free(fp->data);
    free(fp);

    return 0;
}


int analyze_image(const char *path) {
    IMAGE_FILE *image = image_open(path);
    if (!image) {
        fprintf(stderr, "error occurred while open file '%s'\n", path);
        return 1;
    }

    // It should be safe to access byte range 0-3
    // Because buffer size must be at least BUFSIZ
    DEBUG_PRINTF("first 4 bytes: %02X %02X %02X %02X\n",
        image->data[0], image->data[1],
        image->data[2], image->data[3]);

    switch (image->type) {
        case PNG:
            puts("png file detected");
            png_info(image);
            break;
        case JPG:
            puts("jpg file detected");
            break;
        case GIF:
            puts("gif file detected");
            break;
        case XXX:
        default:
            fprintf(stderr, "unknown file type\n");
            break;
    }
    image_close(image);

    return 0;
}


IMAGE_TYPE imgcmp(const void *bufptr) {
    if (!bufptr) goto error;

    for (int i = 0; imgcmp_table[i]; ++i) {
        imgcmp_cb callback = imgcmp_table[i];
        if (!callback(bufptr)) return i;
    }

error:
    return XXX;
}


int jpgcmp(const void *bufptr) {
    const uint8_t magic[] = { 0XFF, 0xD8, 0xFF };
    return memcmp(bufptr, magic, sizeof magic);
}


int pngcmp(const void *bufptr) {
    const uint8_t magic[] = {
        0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A
    };
    return memcmp(bufptr, magic, sizeof magic);
}


int gifcmp(const void *bufptr) {
    // GIF has multiple magic numbers
    const char *magics[] = {
        "GIF87a", "GIF89a", NULL
    };

    int result;
    for (int i = 0; magics[i]; ++i) {
        result = memcmp(bufptr, magics[i], strlen(magics[i]));
        if (!result) break;
    }
    return result;
}


int png_info(IMAGE_FILE *png) {
#define CHECK_EOF(ptr, amount, eofptr) \
    (!(ptr) || !(eofptr) || (ptr) > (eofptr))

#define FORWARD(ptr, amount, eofptr) \
    (/* IF */ !CHECK_EOF((ptr), (amount), (eofptr)) ?  \
     /* TRUE: INC */ (ptr) += (amount) : \
     /* FALSE: NOP */ 0, \
     /* ENDIF, RET ERR */ CHECK_EOF((ptr), (amount), (eofptr)))

    if (!png) return 1;

    printf("%s\n", "analyzing png file...");

    if (png->size < 8) return 1;
    uint8_t *ptr = png->data;
    uint8_t *eofptr = ptr + png->size;

    // Skip header
    if (FORWARD(ptr, 8, eofptr)) return 1;

    // https://en.wikipedia.org/wiki/Portable_Network_Graphics#%22Chunks%22_within_the_file
    //
    // After the header comes a series of chunks,
    // each of which conveys certain information about the image.
    struct {
        uint32_t length;
        union {
            uint32_t type;
            char name[4];
        };
        void *data;
        uint32_t crc;
    } chunk;

    do {
        chunk.length = ntohl(*(uint32_t*)ptr);
        if (FORWARD(ptr, 4, eofptr)) return 1;

        printf("chunk.length: %u\n", (uint32_t)chunk.length);

        memcpy(chunk.name, ptr, sizeof chunk.name);

        if (FORWARD(ptr, 4, eofptr)) return 1;
        printf("chunk.name: %c%c%c%c\n",
                chunk.name[0], chunk.name[1],
                chunk.name[2], chunk.name[3]);

        // Break if image end
        if (!memcmp(chunk.name, "IEND", sizeof chunk.name)) {
            DEBUG_PRINTF("%s\n", "END OF IMAGE");
            break;
        }
        // Allocate chunk data buffer
        uint8_t chunk_data[chunk.length];

        printf("%s", "chunk.data: uint8_t { ");
        for (int i = 0, n = chunk.length; n; --n, ++i) {
            printf("%02X ", ptr[i]);
            chunk_data[i] = ptr[i];
        }
        printf("%s\n", "}");
        chunk.data = chunk_data;

        if (FORWARD(ptr, chunk.length, eofptr)) return 1;

        // TODO: CRC
        if (FORWARD(ptr, 4, eofptr)) return 1;

        if (!memcmp(chunk.name, "IHDR", sizeof chunk.name)) {
            uint32_t width = ntohl(*(uint32_t*)chunk_data);
            printf("image width: %u\n", width);

            uint32_t height = ntohl(*(uint32_t*)&chunk_data[4]);
            printf("image height: %u\n", height);

            uint8_t bit_depth = chunk_data[8];
            printf("bit depth: %u\n", bit_depth);

            uint8_t color_type = chunk_data[9];
            printf("color type: %u\n", color_type);

            uint8_t compression_method = chunk_data[10];
            printf("compression method: %u\n", compression_method);

            uint8_t filter_method = chunk_data[11];
            printf("filter method: %u\n", filter_method);

            uint8_t interlace_method = chunk_data[12];
            printf("interlace method: %u\n", interlace_method);
        }
    } while (1);

    return 0;
#undef CHECK_EOF
#undef FORWARD
}
