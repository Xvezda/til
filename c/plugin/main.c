#include <dlfcn.h>


int main(void) {
    void *handle = dlopen("./plugin.so", RTLD_NOW);
    if (!handle) return 1;

    void (*plugin_setup)(void) = dlsym(handle, "setup");
    if (!plugin_setup) return 1;

    plugin_setup();

    dlclose(handle);

    return 0;
}
