#include <iostream>

class foo {
    int x_;

  public:
    foo(int const x = 0) : x_{x} {}

    int& get() { return x_; }
};

int main() {
    foo f(42);
    auto x = f.get();
    x = 100;
    std::cout << f.get() << std::endl;  // prints 42

    auto& y = f.get();
    y = 100;
    std::cout << f.get() << std::endl;  // prints 100
}
