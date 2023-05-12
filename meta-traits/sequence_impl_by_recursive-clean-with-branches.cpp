/*
$ clang++ -Xclang -ast-print -fsyntax-only sequence_impl_by_recursive-clean-with-branches.cpp  > ast.cpp
# 在生成 ast 的同时，也会执行编译
*/

#include "common/utility/typeinfo.h"

#include <type_traits>
#include <utility>  // index_sequence

#include <array>
#include <cmath>
#include <iostream>
#include <memory>

class Scott : public std::false_type {
  public:
    std::string signature() const { return "Scott"; }
};

class David : public std::true_type {
  public:
    std::string signature() const { return "David"; }
};

class Mario : public std::false_type {
  public:
    std::string signature() const { return "Mario"; }
};

template <typename Test, typename T = void>
using EnableIf = typename std::enable_if_t<Test::value, T>;

template <typename Test, typename T = void>
using DisableIf = typename std::enable_if_t<!Test::value, T>;

template <typename T>
struct Filter : public T {
    // using underlying_type = T;
    static constexpr bool isDavid = T::value;
};

class Message {
  public:
    template <class... Filter>
    Message(Filter... filter) {
        _impl<0>(filter...);
    }

  private:
    template <size_t I>
    void _impl() {
        std::cout << "who call it? I=" << I << std::endl;  // who call it? I=3
    }

    // 1st work
    // template <size_t I, typename Filter>
    // void _impl(Filter& filter) {
    //     if (Filter::value) {  // because of std::enable_if cannot use to overload a method.
    //         std::cout << I << ": SEPECIAL CASE : " << filter.signature() << std::endl;
    //     } else {
    //         std::cout << I << ": " << filter.signature() << std::endl;
    //     }
    // }

    // 2nd, not work.
    // clang-format off
    /* error: call of overloaded ‘_impl(David&)’ is ambiguous

   65:10: note: candidate: ‘void Message::_impl(Filter&) [with long unsigned int I = 1; Filter = David; typename std::enable_if<Filter::value, Filter>::type* <anonymous> = 0]’
   65 |     void _impl(Filter& filter) {
      |          ^~~~~
   70:10: note: candidate: ‘void Message::_impl(Filter&) [with long unsigned int I = 1; Filter = David]’
   70 |     void _impl(Filter& filter) {
      |          ^~~~~
   75:10: note: candidate: ‘void Message::_impl(Filter&, Filters ...) [with long unsigned int I = 1; Filter = David; Filters = {}]’
   75 |     void _impl(Filter& filter, Filters... filters) {
      |          ^~~~~
    */
   // clang-format on 
    // template <size_t I, typename Filter>
    // void _impl(Filter& filter) {
    //     std::cout << I << ": SEPECIAL CASE : " << filter.signature() << std::endl;
    // }

    // template <size_t I, typename Filter, typename std::enable_if<Filter::value, Filter>::type* = nullptr>
    // void _impl(Filter& filter) {
    //     std::cout << I << ": " << filter.signature() << std::endl;
    // }

    // 3.
    // clang-format off
    /*
    :106:9: error: call to member function '_impl' is ambiguous
        _impl<I>(filter);
        ^~~~~~~~
    sequence_impl_by_recursive-clean-with-branches.cpp:93:10: note: candidate function [with I = 1, Filter = David]
    void _impl(Filter& filter) {
         ^
    sequence_impl_by_recursive-clean-with-branches.cpp:98:10: note: candidate function [with I = 1, Filter = David, $2 = void]
    void _impl(Filter& filter) {
         ^
    */
    // clang-format on
    // template <size_t I, typename Filter>
    // void _impl(Filter& filter) {
    //     std::cout << I << ": " << filter.signature() << std::endl;
    // }

    // template <size_t I, typename Filter, typename = EnableIf<Filter>>
    // void _impl(Filter& filter) {
    //     std::cout << I << ": SEPECIAL CASE : " << filter.signature() << std::endl;
    // }

    // 4. failed
    // clang-format off
    /*
    :120:10: error: class member cannot be redeclared
    void _impl(Filter& filter) {
         ^
    :115:10: note: previous definition is here
    void _impl(Filter& filter) {

    when the code is 
    template <size_t I, typename Filter, typename = std::enable_if_t<!Filter::isDavid>>
    void _impl(Filter& filter) {
        std::cout << I << ": " << filter.signature() << std::endl;
    }

    template <size_t I, typename Filter, typename = std::enable_if_t<!Filter::isDavid, typename Filter::underlying_type>>
    void _impl(Filter& filter) {
        std::cout << I << ": SEPECIAL CASE : " << filter.signature() << std::endl;
    }
    */
    // clang-format on

    // 认真思考之后，还是没有办法对其进行overloads，原因是：
    // 假如可以正常overloads， 那么在模板特化之后, 这两个方法分别是:
    // `void _impl(Filter& filter);` 和 `void _impl(Filter& filter);`
    // 函数签名还是一样的. 所以，假设不成立。
    // 但为什么函数签名一样呢，不应该是
    // `void _impl(Filter<David>& filter);` 和 `void _impl(Filter<Not David>& filter);` 吗？
    // 难道是因为 Filter<David> 和 Filter<Not David> 会被当作同一个类型？

    // 5. one more try.
    template <size_t I, typename Filter, typename = std::enable_if_t<!Filter::isDavid>>
    void _impl(Filter& filter) {
        std::cout << I << ": " << filter.signature() << std::endl;
    }

    template <size_t I, typename Filter, typename SomeType = std::enable_if_t<Filter::isDavid, int>>
    void _impl(Filter& filter, SomeType* i = nullptr) {
        std::cout << I << ": SEPECIAL CASE : " << filter.signature() << std::endl;
    }

    template <size_t I, typename Filter, typename... Filters>
    void _impl(Filter& filter, Filters... filters) {
        // call head: filter
        _impl<I>(filter);
        // call others: filters
        _impl<I + 1>(filters...);
    }
};

void bbegin();
Filter<Scott> st0;
Filter<David> st1;
Filter<Mario> st2;
Message m(st0, st1, st2);  // Scott, David, Mario
void eend();

int main() {
    std::cout << utility::typeInfo(st0) << std::endl;  // Filter<Scott>
    std::cout << utility::typeInfo(st1) << std::endl;  // Filter<David>
    std::cout << utility::typeInfo(st2) << std::endl;  // Filter<Mario>
    return 0;
}

// clang-format off
/** AST

    template<> void _impl<0UL, Filter<Scott>, void>(Filter<Scott> &filter) {
        std::cout << 0UL << ": " << filter.signature() << std::endl;
    }
    template<> void _impl<2UL, Filter<Mario>, void>(Filter<Mario> &filter) {
        std::cout << 2UL << ": " << filter.signature() << std::endl;
    }
    template<> void _impl<1UL, Filter<David>, int>(Filter<David> &filter, int *i = nullptr) {
        std::cout << 1UL << ": SEPECIAL CASE : " << filter.signature() << std::endl;
    }
*
 * Result
0: Scott
1: SEPECIAL CASE : David
2: Mario
Type Signature: 6FilterI5ScottE	=> Filter<Scott>	: 0
Type Signature: 6FilterI5DavidE	=> Filter<David>	: 0
Type Signature: 6FilterI5MarioE	=> Filter<Mario>	: 0

* And to view the signature of function members, I get this:
* 
$ nm a.out  | grep _impl | c++filt 
0000000000002870 W void Message::_impl<0ul, Filter<Scott>, Filter<David>, Filter<Mario> >(Filter<Scott>&, Filter<David>, Filter<Mario>)
00000000000028b0 W void Message::_impl<0ul, Filter<Scott>, void>(Filter<Scott>&)
0000000000002a10 W void Message::_impl<1ul, Filter<David>, int>(Filter<David>&, int*)
0000000000002950 W void Message::_impl<1ul, Filter<David>, Filter<Mario> >(Filter<David>&, Filter<Mario>)
0000000000002ac0 W void Message::_impl<2ul, Filter<Mario>, void>(Filter<Mario>&)
*/
// clang-format on