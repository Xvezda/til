#include <stdio.h>
#include <unistd.h>

#define PRINT_MSG(src, id) \
    printf(#src ": %d\n", id)


int main(void)
{
    pid_t pid;

    if((pid=fork()) == 0) {
        // If pid == 0, it's parent process
        PRINT_MSG(parent, pid);
    } else {
        PRINT_MSG(child, pid);
    }
    return 0;
}


