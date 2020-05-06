#include <stdio.h>

void __attribute__ ((destructor)) destructor() { printf("%s\n", __FUNCTION__); }

int main(void) { return 0; }


