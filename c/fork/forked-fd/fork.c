#include <stdio.h>
#include <unistd.h>

int main(void) {
	printf("starting...\n");
	printf("forked %d\n", fork());

	return 0;
}

