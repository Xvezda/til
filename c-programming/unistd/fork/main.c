#include <stdio.h>
#if (defined(WIN32) || defined(_WIN32) || \
     defined(__WIN32__) || defined(__NT__))
#include <windows.h>
#else
#include <unistd.h>
#endif


#define PRINT_MSG(src, id) \
    printf(#src ": %d\n", id)


int main(void)
{
    pid_t pid;

    puts("=Before fork=");
    if((pid=fork()) == 0) {
        // If pid == 0, it's parent process
        PRINT_MSG(parent, pid);
    } else {
        PRINT_MSG(child, pid);
    }
    return 0;
}


