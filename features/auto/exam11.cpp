#include <iostream>

class foo {
    int x_;

  public:
    foo(int const x = 0) : x_{x} {}

    int& get() { return x_; }
};

// error: non-const lvalue reference to type 'int' cannot bind to a temporary of type 'int'
// auto proxy_get(foo& f) { return f.get(); }

decltype(auto) proxy_get(foo& f) { return f.get(); }

int main() {
    auto f = foo{42};
    auto x = proxy_get(f);  // cannot convert from 'int' to 'int &'
    x = 100;
    std::cout << f.get() << std::endl;  // prints 42

    auto& y = proxy_get(f);  // cannot convert from 'int' to 'int &'
    y = 100;
    std::cout << f.get() << std::endl;  // prints 100
}
