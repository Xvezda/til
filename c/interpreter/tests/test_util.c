#include "util.h"


int main(void) {
    sb_t *sb = new_sb(NULL);
    for (;;) {
        char *input = readline();
        if (!input) break;

        sb_append(sb, input);
        printf("text: %s\n", sb_to_str(sb));
        printf("len: %d\n", sb_len(sb));
    }
    del_sb(sb);

    return 0;
}

