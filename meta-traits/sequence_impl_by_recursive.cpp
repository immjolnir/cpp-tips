/*

*/
#include <cxxabi.h>

#include <type_traits>
#include <utility>  // index_sequence

#include <array>
#include <cmath>
#include <iostream>
#include <memory>

#ifdef G11
class Message {
  public:
    template <class... Filters>
    Message(Filters... filters) {
        std::tuple<Filters...> t{filters...};
        registerImpl(t, std::index_sequence_for<Filters...>{});
    }

  private:
    template <typename Tuple, std::size_t... Is>
    void registerImpl(Tuple& t, std::index_sequence<Is...>) {
        /*
        $ g++ --version
        g++ (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0

        // Not supported, But how to make it runnable with g++-7.5?
        $ g++ --version
        g++ (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
        */
        (std::get<Is>(t)->registerCallback([this](uint32_t seq, T pivot) { return this->template set<Is>(seq, pivot); },
                                           [this]() { return this->template get<Is>(); }),
         ...);
    }
};
#endif

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

class Student {
  public:
    Student(const std::string& name) : _name(name) {}

    std::string signature() const { return _name; }

  private:
    std::string _name;
};

#ifdef WORKED
class Message {
  public:
    template <class... Filters>
    Message(Filters... filters) {
        std::tuple<Filters...> t{filters...};
        registerImpl(t, std::index_sequence_for<Filters...>{});
    }

  private:
    template <typename Tuple, std::size_t... Is>
    void registerImpl(Tuple& t, std::index_sequence<Is...>) {
        ((std::cout << (Is == 0 ? "" : ", ") << std::get<Is>(t)->signature()), ...);
        std::cout << std::endl;
    }
};
#endif

#ifdef FAILED
class Message {
  public:
    template <class... Filters>
    Message(Filters... filters) {
        static constexpr size_t N = sizeof...(Filters);
        std::tuple<Filters...> t{filters...};
        registerImpl(t);
    }

  private:
    template <typename Tuple>
    void registerImpl(Tuple& t) {
        static constexpr size_t size = std::tuple_size<Tuple>::value;
        for (size_t i = 0; i < size; ++i) {
            // template argument deduction/substitution failed:
            // error: the value of ‘i’ is not usable in a constant expression
            std::cout << (i == 0 ? "" : ", ") << std::get<i>(t)->signature();
        }
        std::cout << std::endl;
    }
};
#endif

class Scott {
  public:
    std::string signature() const { return "Scott"; }
};

class David {
  public:
    std::string signature() const { return "David"; }
};

class Mario {
  public:
    std::string signature() const { return "Mario"; }
};

class Message {
  public:
    template <class... Filter>
    Message(Filter... filter) {
        static constexpr size_t N = sizeof...(Filter);
        // std::tuple<Filters...> t{filters...};
        // https://en.cppreference.com/w/cpp/language/fold
        // ( ... op pack )
        // 2) unary left fold
        (..., impl<N>(filter));

        _impl<0>(filter...);
    }

  private:
    template <size_t I, typename Filter>
    void impl(Filter& filter) {
        std::cout << I << ": " << filter->signature() << std::endl;
    }

    template <size_t I, typename Filter>
    void _impl(Filter& filter) {
        std::cout << I << ": " << filter->signature() << std::endl;
    }

    template <size_t I, typename Filter, typename... Filters>
    void _impl(Filter& filter, Filters... filters) {
        std::cout << I << ": " << filter->signature() << std::endl;
        static constexpr size_t N = I + 1;
        _impl<N>(filters...);
    }
};

int main() {
    auto st0 = std::make_shared<Scott>();
    auto st1 = std::make_shared<David>();
    auto st2 = std::make_shared<Mario>();

    Message m(st0, st1, st2);  // Scott, David, Mario

    return 0;
}
