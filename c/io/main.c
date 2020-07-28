#include <stdio.h>
#include <stdlib.h>


struct foobar {
    int ham;
    double egg;
};


void foobar_write(struct foobar *self, const char *path);
void foobar_read(struct foobar *ref, const char *path);


int main(void) {
    struct foobar fb = {
        .ham = 31337,
        .egg = 987.654
    };
    printf("size -> ham: %zu, egg: %zu\n", sizeof fb.ham, sizeof fb.egg);
    printf("fb = { .ham = %d, .egg = %lf }\n", fb.ham, fb.egg);

    foobar_write(&fb, "foobar.bin");

    struct foobar fbclone;
    foobar_read(&fbclone, "foobar.bin");

    printf("fbclone = { .ham = %d, .egg = %lf }\n",
            fbclone.ham, fbclone.egg);

    struct foobar *fbptr = malloc(sizeof *fbptr);
    if (!fbptr) return 1;
    fbptr->ham = 0;
    fbptr->egg = 0;

    printf("before: fbptr = { .ham = %d, .egg = %lf }\n",
            fbptr->ham, fbptr->egg);

    foobar_read(fbptr, "foobar.bin");

    printf("after: fbptr = { .ham = %d, .egg = %lf }\n",
            fbptr->ham, fbptr->egg);

    return 0;
}


void foobar_write(struct foobar *self, const char *path) {
    FILE *bin = fopen(path, "wb");
    if (!bin) return;

    size_t size = sizeof *self;
    size_t n = fwrite(self, size, 1, bin);
    printf("size of %zu writed\n", size * n);

    fclose(bin);
}


void foobar_read(struct foobar *ref, const char *path) {
    FILE *bin = fopen(path, "rb");
    if (!bin) return;

    fread(ref, sizeof *ref, 1, bin);
    fclose(bin);
}
