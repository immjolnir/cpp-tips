// https://stackoverflow.com/questions/67477403/making-an-index-sequence-tuple
// If you insist on std::apply, it understands std::array out of the box.
// https://devblogs.microsoft.com/oldnewthing/20200625-00/?p=103903
// https://en.cppreference.com/w/cpp/language/parameter_pack
#include <cxxabi.h>
#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>

template <typename T, typename I>
struct n_tuple_helper {};

template <typename T, std::size_t... I>
struct n_tuple_helper<T, std::index_sequence<I...>> {
    using type = std::tuple<std::enable_if_t<I || true, T>...>;
};

template <typename T, std::size_t N>
using n_tuple = typename n_tuple_helper<T, std::make_index_sequence<N>>::type;

template <typename T, std::size_t N>
struct Student {
    // using Type = n_tuple<T, N>;
    using Type = typename n_tuple_helper<T, std::make_index_sequence<N>>::type;
};

template <typename T>
void echo(const T& t) {
    int status;
    char* realname;
    const std::type_info& ti = typeid(t);
    realname = abi::__cxa_demangle(ti.name(), NULL, NULL, &status);
    std::cout << "Type Signature: " << ti.name() << "\t=> " << realname << "\t: " << status << '\n' << std::endl;
}

/*
41:56: warning: fold-expressions only available with ‘-std=c++17’ or ‘-std=gnu++17’
   41 |     ((os << (Is == 0 ? "" : ", ") << std::get<Is>(t)), ...)
*/
// https://en.cppreference.com/w/cpp/utility/integer_sequence
// pretty-print a tuple
template <class Ch, class Tr, class Tuple, std::size_t... Is>
void print_tuple_impl(std::basic_ostream<Ch, Tr>& os, const Tuple& t, std::index_sequence<Is...>) {
    ((os << (Is == 0 ? "" : ", ") << std::get<Is>(t)), ...);
}
template <class Ch, class Tr, class... Args>
auto& operator<<(std::basic_ostream<Ch, Tr>& os, const std::tuple<Args...>& t) {
    os << "(";
    print_tuple_impl(os, t, std::index_sequence_for<Args...>{});
    return os << ")";
}

int main() {
    Student<int, 3>::Type tuple3;
    echo(tuple3);

    std::get<0>(tuple3) = 1;
    std::get<1>(tuple3) = 2;
    std::get<2>(tuple3) = 3;
    std::cout << "(" << std::get<0>(tuple3) << ", " << std::get<1>(tuple3) << ", " << std::get<2>(tuple3) << ")\n"
              << std::endl;

    Student<std::string, 3>::Type str3;
    echo(str3);
    std::get<0>(str3) = "Scott";
    std::get<1>(str3) = "David";
    std::get<2>(str3) = "Mario";
    std::cout << str3 << std::endl;
}
