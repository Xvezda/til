#include <stdio.h>
#include <unistd.h>

int main(void) {
    // It will emulate fully buffered mode which happens on piping.
    // So, output of `./fork-fbf` and `./fork-fbf | cat` becomes equivalent.
	setvbuf(stdout, NULL, _IOFBF, 0);

	printf("starting...\n");
	printf("forked %d\n", fork());

	return 0;
}

