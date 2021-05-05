#include <stdio.h>
#include <unistd.h>

int main(void) {
	printf("starting...\n");
	fflush(stdout);
	printf("forked %d\n", fork());

	return 0;
}

