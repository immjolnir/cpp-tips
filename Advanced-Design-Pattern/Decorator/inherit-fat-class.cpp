#include <iostream>

struct Foo {
    int i;
};

struct Bar: public Foo {
    int j;
    Foo *foo;
};

int main() {
    std::cout << sizeof(Foo) << std::endl;
    std::cout << sizeof(Bar) << std::endl;

}
