#include <stdio.h>
#if defined(_WIN32)
#include <windows.h>
#else
#include <unistd.h>
#endif


#define PRINT_MSG(src, id) \
    printf(#src ": %d\n", id)


int main(void)
{
#if defined(_WIN32)
	/* Windows implementation */
#else
    pid_t pid;

    puts("=Before fork=");
    if((pid=fork()) == 0) {
        // If pid == 0, it's parent process
        PRINT_MSG(parent, pid);
    } else {
        PRINT_MSG(child, pid);
    }
#endif
    return 0;
}


