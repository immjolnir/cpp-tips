// https://stackoverflow.com/questions/58598763/how-to-assign-variadic-template-arguments-to-stdarray
#include <array>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

using namespace std;

template <class... Values, size_t N>
void assign_values(std::array<int, N>& arr, Values... vals) {
    int j = 0;
    for (int i : {vals...}) arr[j++] = i;
}

template <typename T, typename... Args>
void func(Args... args) {
    static constexpr size_t N = sizeof...(Args);
    std::cout << "N=" << N << std::endl;
    std::array<T, N> arr{args...};
    static_assert(N == arr.size(), "They must have the same size");
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << "arr[" << i << "]=" << arr[i] << std::endl;
    }
}

/*
template <typename... Args>
void foo(Args... args) {
    static constexpr size_t N = sizeof...(Args);
    std::cout << "N=" << N << std::endl;
    std::array<decltype(args), N> arr{args...};
    static_assert(N == arr.size(), "They must have the same size");
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << "arr[" << i << "]=" << arr[i] << std::endl;
    }
}
*/

// 遍历 tuple
// https://blog.csdn.net/yockie/article/details/89511498
template <typename Tuple, std::size_t... Is>
void bar_impl(const Tuple& t, std::index_sequence<Is...>) {
    std::stringstream ss;
    ((ss << (Is == 0 ? "" : ", ") << std::get<Is>(t)), ...);
    std::cout << ss.str() << std::endl;
}

template <typename... Args>
void bar(Args... args) {
    std::tuple<Args...> t{args...};
    // std::size_t size = std::tuple_size_v<t>;
    bar_impl(t, std::index_sequence_for<Args...>{});
}

int main() {
    std::array<int, 3> a;
    std::array<int, 5> b;

    assign_values(a, 1, 2, 3);
    assign_values(b, 1, 2, 3, 4, 5);

    for (int i : b) {
        std::cout << i << std::endl;
    }

    func<int>(1, 2, 3, 4);

    // foo(1, 2, 3, 4);
    bar(1, 2, 3, 4);
}
