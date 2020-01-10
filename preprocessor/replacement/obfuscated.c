#include "stdio.h"
#define assemble(a, b, c, d)  c##a##d##b(void)
#define function              int
#define alert(msg)            puts(msg)

function assemble(a, n, m, i) {
    alert("hello");
}
