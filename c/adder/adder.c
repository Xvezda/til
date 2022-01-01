#include <stdio.h>

/*
int add(int a, int b) {
    while (b) {
        int carry = a & b;
        a ^= b;
        b = carry << 1;
    }
    return a;
}
*/

struct adder_input {
    int a;
    int b;
    int c;
};

struct adder_output {
    int carry;
    int sum;
};

struct adder_output adder(struct adder_input input) {
    input.a = input.a && 1;
    input.b = input.b && 1;
    input.c = input.c && 1;

    return (struct adder_output){
        .carry =
            ((input.a & input.c) |
             (input.b & input.c) |
             (input.a & input.b)) && 1,
        .sum = (input.a ^ input.b ^ input.c) && 1
    };
}

int add(int a, int b) {
    int result = 0;
    struct adder_output output = { .sum = 0, .carry = 0 };

#define ADD_BIT(a, b, n) \
    output = adder((struct adder_input){ \
            .a = a & (1<<n), .b = b & (1<<n), .c = output.carry \
            }); \
    result |= (output.sum << n);

    ADD_BIT(a, b, 0);
    ADD_BIT(a, b, 1);
    ADD_BIT(a, b, 2);
    ADD_BIT(a, b, 3);
    ADD_BIT(a, b, 4);
    ADD_BIT(a, b, 5);
    ADD_BIT(a, b, 6);
    ADD_BIT(a, b, 7);
    ADD_BIT(a, b, 8);
    ADD_BIT(a, b, 9);
    ADD_BIT(a, b, 10);
    ADD_BIT(a, b, 11);
    ADD_BIT(a, b, 12);
    ADD_BIT(a, b, 13);
    ADD_BIT(a, b, 14);
    ADD_BIT(a, b, 15);
    ADD_BIT(a, b, 16);
    ADD_BIT(a, b, 17);
    ADD_BIT(a, b, 18);
    ADD_BIT(a, b, 19);
    ADD_BIT(a, b, 20);
    ADD_BIT(a, b, 21);
    ADD_BIT(a, b, 22);
    ADD_BIT(a, b, 23);
    ADD_BIT(a, b, 24);
    ADD_BIT(a, b, 25);
    ADD_BIT(a, b, 26);
    ADD_BIT(a, b, 27);
    ADD_BIT(a, b, 28);
    ADD_BIT(a, b, 29);
    ADD_BIT(a, b, 30);
    ADD_BIT(a, b, 31);

    return result;
#undef ADD_BIT
}

int main() {
    int a, b;

    printf("a: ");
    scanf("%d", &a);

    printf("b: ");
    scanf("%d", &b);

    printf("%d + %d = %d\n", a, b, add(a, b));

    return 0;
}
