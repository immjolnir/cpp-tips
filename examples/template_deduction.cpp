/**
 * Template argument deduction
 * 
 * https://www.ibm.com/docs/en/zos/2.3.0?topic=only-variadic-templates-c11
 * 
 * Parameter packs can be deduced by template argument deduction in the same way as other normal template parameters. 
*/

#include <cstdio>

template <int... A>
struct container {
    void display() { printf("YIKES\n"); }
};

template <int B, int... C>
struct container<B, C...> {
    void display() {
        printf("spec %d\n", B);
        container<C...> test;
        test.display();
    }
};

template <int C>
struct container<C> {
    void display() { printf("spec %d\n", C); }
};

int main(void) {
    printf("start\n\n");
    container<1, 2, 3, 4, 5, 6, 7, 8, 9, 10> test;
    test.display();
    return 0;
}