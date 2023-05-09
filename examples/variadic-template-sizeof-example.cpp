/*
 * https://en.cppreference.com/w/cpp/language/parameter_pack
 */

#include <iostream>

template <typename... T>
struct Student {
    static constexpr size_t N = sizeof...(T);
};

int main() {
    std::cout << Student<int, float, double, uint32_t, uint16_t>::N << std::endl;
    std::cout << Student<uint32_t, uint16_t>::N << std::endl;
}
