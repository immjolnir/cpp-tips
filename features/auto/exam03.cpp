#include <iostream>
#include <vector>

int main() {
    std::vector<bool> v{0, 0, 0};
    auto x = v[1];
    x = 1;
    std::cout << v[0] << ' ' << v[1] << ' ' << v[2] << '\n';  // 0, 1, 0
    // Surprisingly, it prints 0 1 0.
    // The reason is that a vector of bools is special.
    // It is a partial specialization of std::vector<T, Allocator> that should be space-efficient.
    // https://en.cppreference.com/w/cpp/container/vector_bool
    
    std::cout << std::endl;
    return 0;
}
