#include <iostream>
#include <tuple>    // std::tie, Creates a tuple of lvalue references to its arguments or instances of std::ignore.
#include <utility>  // std::pair

int main() {
    int a = 0, b = 0;
    auto [x, y] = std::tie(a, b);
    y = 1;
    std::cout << a << ',' << b << '\n';  // 0,1

    std::cout << std::endl;
}
