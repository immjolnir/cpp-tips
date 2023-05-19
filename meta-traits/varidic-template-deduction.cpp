#include <cstdio>

template <int... A>
struct container;

template <int B, int... C>
struct container<B, C...> {
    void display() {
        container<B>().display();
        container<C...>().display();
    }
};

template <int C>
struct container<C> {
    void display() { printf("spec %d\n", C); }
};

void bbegin();
container<1, 2, 3, 4, 5> test;
void eend();

int main(void) {
    printf("start\n\n");
    test.display();
    printf("\n\nend\n");
    return 0;
}
/*
 * $ clang++ -Xclang -ast-print -fsyntax-only varidic-template-deduction.cpp

template <int ...A> struct container
template<> struct container<<1, 2, 3, 4, 5>> {
    void display() {
        container<1>().display();
        container<2, 3, 4, 5>().display();
    }
}
template<> struct container<<1>> {
    void display() {
        printf("spec %d\n", 1);
    }
}
template<> struct container<<2, 3, 4, 5>> {
    void display() {
        container<2>().display();
        container<3, 4, 5>().display();
    }
}
template<> struct container<<2>> {
    void display() {
        printf("spec %d\n", 2);
    }
}
template<> struct container<<3, 4, 5>> {
    void display() {
        container<3>().display();
        container<4, 5>().display();
    }
}
template<> struct container<<3>> {
    void display() {
        printf("spec %d\n", 3);
    }
}
template<> struct container<<4, 5>> {
    void display() {
        container<4>().display();
        container<5>().display();
    }
}
template<> struct container<<4>> {
    void display() {
        printf("spec %d\n", 4);
    }
}
template<> struct container<<5>> {
    void display() {
        printf("spec %d\n", 5);
    }
};
 */