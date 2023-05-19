// Generate a tuple with the different type and size.
#include "utility/typeinfo.h"

#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>

template <typename T, typename I>
struct n_tuple_helper {};

template <typename T>
struct n_tuple_helper<T, std::index_sequence<I...>> {
    using type = std::tuple<std::enable_if_t<I || true, T>...>;
};

static constexpr std::size_t N = 5;
void bbegin();

typedef n_tuple_helper<int, std::make_index_sequence<N>>::type Tuple;
Tuple instance;

void eend();

int main() {
    std::cout << utility::typeInfo<Tuple>() << std::endl;
    // Type Signature: St5tupleIJiiiiiEE	=> std::tuple<int, int, int, int, int>	: 0
    return 0;
}

/*
 * $ clang++ -Xclang -ast-print -fsyntax-only n_tuple_helper.cpp
template <typename T, typename I> struct n_tuple_helper {
};
template<> struct n_tuple_helper<int, std::integer_sequence<unsigned long, 0, 1, 2, 3, 4>> {
    using type = std::tuple<std::enable_if_t<0UL || true, int>, std::enable_if_t<1UL || true, int>, std::enable_if_t<2UL
|| true, int>, std::enable_if_t<3UL || true, int>, std::enable_if_t<4UL || true, int>>;
};
template <typename T, std::size_t ...I> struct n_tuple_helper<T, std::index_sequence<I...>> {
    using type = std::tuple<std::enable_if_t<I || true, T>...>;
};

 * */
