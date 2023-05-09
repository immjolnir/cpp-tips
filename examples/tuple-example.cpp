#include <cxxabi.h>
#include <iostream>
#include <tuple>
#include <typeinfo>  // for typeid

template <typename... Args>
struct Student {
    typedef std::tuple<Args...> Type;
    Type t;

    void echo() {
        int status;
        char* realname;
        const std::type_info& ti = typeid(t);
        realname = abi::__cxa_demangle(ti.name(), NULL, NULL, &status);
        std::cout << "Type Signature: " << ti.name() << "\t=> " << realname << "\t: " << status << '\n';
    }
};



// https://en.cppreference.com/w/cpp/utility/integer_sequence
// convert array into a tuple
template <typename Array, std::size_t... I>
auto a2t_impl(const Array& a, std::index_sequence<I...>) {
    return std::make_tuple(a[I]...);
}

template <typename T, std::size_t N, typename Indices = std::make_index_sequence<N>>
auto a2t(const std::array<T, N>& a) {
    return a2t_impl(a, Indices{});
}

int main() {
    std::tuple<int, double, float> t;

    // https://gcc.gnu.org/onlinedocs/libstdc++/manual/ext_demangling.html
    int status;
    char* realname;
    const std::type_info& ti = typeid(t);
    realname = abi::__cxa_demangle(ti.name(), NULL, NULL, &status);

    std::cout << "Type Signature: " << ti.name() << "\t=> " << realname << "\t: " << status << '\n';

    // https://en.cppreference.com/w/cpp/utility/tuple/get
    // Return value:
    // A reference to the selected element of t.
    std::get<0>(t) = 1;
    std::get<1>(t) = 0.1;
    std::get<2>(t) = 0.11;

    std::cout << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << ")\n" << std::endl;

    Student<int, double, float> st;
    st.echo();

    auto seq_t = std::make_integer_sequence<int, 3>{};
    echo(seq_t);

    std::tuple<std::make_integer_sequence<int, 3>> t3;
    echo(t3);

    // std::make_integer_sequence<int, 3> Array{};
    // echo(Array[0]);
    // echo(Array[1]);
    // echo(Array[2]);

    // std::get<0>(t3) =
    // auto tuple = a2t();

    return 0;
}
