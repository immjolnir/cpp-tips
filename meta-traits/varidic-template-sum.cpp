// Folds
// https://www.scs.stanford.edu/~dm/blog/param-pack.html
//
// Template deduction
// https://en.cppreference.com/w/cpp/language/template_argument_deduction
#include <concepts>  // since c++ 20, for convertable_to_v
#include <type_traits>

#include <iostream>

template <typename... T>
// constexpr int sum(std::convertable_to<T, int> auto... i) {
auto sum(T... i) {
    return (0 + ... + i);
}

int main() {
    int total = sum(1, 2, 3, 4, 5);  // 15
    std::cout << "total: " << total << std::endl;
}
