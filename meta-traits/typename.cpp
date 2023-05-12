#include <type_traits>

#include <iostream>

namespace std {
    template <class T>
    // warning: inline variables are a C++17 extension [-Wc++17-extensions]
    // inline constexpr bool is_integral_v = is_integral<T>::value;
    constexpr bool is_integral_v = is_integral<T>::value;
}

template <typename Test, typename T = void>
using EnableIf = typename std::enable_if_t<Test::value, T>;

template <typename Test, typename T = void>
using DisableIf = typename std::enable_if_t<!Test::value, T>;

template <typename T>
auto compute(T const a, T const b) {
    static_assert(std::is_integral_v<T>, "An integral type expected");
    return a + b;
}

template <typename T, typename = void>
auto compute(T const a, T const b) {
    static_assert(!std::is_integral_v<T>, "A non-integral type expected");
    return a * b;
}

template <typename T, typename = EnableIf<std::is_integral<T>>>
auto compute2(T const a, T const b) {
    return a * b;  // multipy
}

// typename = void 是额外的参数, 当是 float时，这个也有效果. 此时的就变成了
// template<float, typename = float, typename = void>
template <typename T, typename = DisableIf<std::is_integral<T>>, typename = void>
auto compute2(T const a, T const b) {
    return a + b;  // addition
}

int main() {
    {

      // auto v1 = compute(1, 2); // error: ambiguous call to overloaded function
      // auto v2 = compute(1.0, 2.0); // error: ambiguous call to overloaded function
      // std::cout << "v1=" << v1 << ", v2=" << v2 << std::endl;
    }  // case 2

    {
        [[maybe_unused]] auto v1 = compute2(1, 2);      // v1 = 2
        [[maybe_unused]] auto v2 = compute2(1.0, 2.0);  // v2 = 3.0
        std::cout << "v1=" << v1 << ", v2=" << v2 << std::endl;
    }
}
