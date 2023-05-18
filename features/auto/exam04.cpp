#include <iostream>
#include <utility>  // std::pair

int main() {
    std::pair p{0, 0};
    auto [x, y] = p;
    y = 1;
    std::cout << p.first << ',' << p.second << '\n';  // 0,0

    std::cout << std::endl;
}
