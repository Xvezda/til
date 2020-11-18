#include <stdio.h>

void ctor(void);
void setup(void);


__attribute__((constructor))
void ctor() {
    puts("plugin loaded");
}

void setup() {
    puts("hello from plugin");
}
