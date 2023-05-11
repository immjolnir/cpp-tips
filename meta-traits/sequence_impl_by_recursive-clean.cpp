/*
$ clang++ -Xclang -ast-print -fsyntax-only sequence_impl_by_recursive-clean.cpp  > ast.cpp
*/

#include <cxxabi.h>

#include <type_traits>
#include <utility>  // index_sequence

#include <array>
#include <cmath>
#include <iostream>
#include <memory>

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
        _impl<0>(filter...);
    }

  private:
    template <size_t I, typename Filter>
    void _impl(Filter& filter) {
        std::cout << I << ": " << filter->signature() << std::endl;
    }

    template <size_t I, typename Filter, typename... Filters>
    void _impl(Filter& filter, Filters... filters) {
        // call head: filter
        std::cout << I << ": " << filter->signature() << std::endl;
        // call others: filters
        _impl<I + 1>(filters...);
    }
};

auto st0 = std::make_shared<Scott>();
auto st1 = std::make_shared<David>();
auto st2 = std::make_shared<Mario>();

void bbegin();
Message m(st0, st1, st2);  // Scott, David, Mario
void eend();

/*  Valid AST as below

class Message {
  public:
    template <class... Filter>
    Message(Filter... filter) {
        _impl<0>(filter...);
    }

    template <>
      Message << std::shared_ptr<Scott>,
      std::shared_ptr<David>,
      std::shared_ptr < Mario >>>
        (std::shared_ptr<Scott> filter, std::shared_ptr<David> filter, std::shared_ptr<Mario> filter) {
        this->_impl<0>(filter, filter, filter);
    }

  private:
    template <size_t I, typename Filter>
    void _impl(Filter& filter) {
        std::cout << I << ": " << filter->signature() << std::endl;
    }

    template <>
    void _impl<2UL, std::shared_ptr<Mario>>(std::shared_ptr<Mario>& filter) {
        std::cout << 2UL << ": " << filter->signature() << std::endl;
    }

    template <size_t I, typename Filter, typename... Filters>
    void _impl(Filter& filter, Filters... filters) {
        std::cout << I << ": " << filter->signature() << std::endl;
        static constexpr size_t N = I + 1;
        _impl<N>(filters...);
    }

    template <>
    void _impl<0UL, std::shared_ptr<Scott>, <std::shared_ptr<David>, std::shared_ptr<Mario>>>(
      std::shared_ptr<Scott>& filter, std::shared_ptr<David> filters, std::shared_ptr<Mario> filters) {
        std::cout << 0UL << ": " << filter->signature() << std::endl;
        static constexpr size_t N = 0UL + 1;
        this->_impl<N>(filters, filters);
    }

    template <>
    void _impl<1UL, std::shared_ptr<David>, <std::shared_ptr<Mario>>>(std::shared_ptr<David>& filter,
                                                                      std::shared_ptr<Mario> filters) {
        std::cout << 1UL << ": " << filter->signature() << std::endl;
        static constexpr size_t N = 1UL + 1;
        this->_impl<N>(filters);
    }
    template <>
    void _impl<2UL, std::shared_ptr<Mario>, <>>(std::shared_ptr<Mario>& filter)
};
*/

int main() { return 0; }
