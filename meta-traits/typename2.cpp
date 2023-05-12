/*
 * C++ template argument without a name: unnamed template.
 *
 * See https://stackoverflow.com/questions/60399275/c-template-argument-without-a-name
 * This is used for specializations in conjunction with SFINAE. Doing this allows you to have code like
 *
 * See https://en.cppreference.com/w/cpp/language/sfinae
 */

#include <iostream>
#include <type_traits>

/*
Without the typename = void, we would not be able to add these specializations because there would be no second
parameter the enable_if_t part could "fill in".

Also, the default type (= void) is useful to handle cases which are neither integral nor floating point.

After removing the struct with `typename = void` or the struct definition, the error as below will be raised:

typename2.cpp:25:8: error: explicit specialization of undeclared template struct 'test'
struct test<T, std::enable_if_t<std::is_integral<T>::value>> {
       ^   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
typename2.cpp:31:8: error: too many template arguments for class template 'test'
struct test<T, std::enable_if_t<std::is_floating_point<T>::value>> {
       ^       ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
typename2.cpp:25:8: note: template is declared here
struct test<T, std::enable_if_t<std::is_integral<T>::value>> {
*/
template <typename T, typename = void>
struct test {
    static constexpr int SIZE = sizeof(T);
};

template <typename T>
struct test<T, std::enable_if_t<std::is_integral<T>::value>> {
    //             ^^  this part "fills in" the void    ^^
    static constexpr int SIZE = 42;
};

template <typename T>
struct test<T, std::enable_if_t<std::is_floating_point<T>::value>> {
    //             ^^     this part "fills in" the void       ^^
    static constexpr int SIZE = 21;
};

struct Student {
    int i : 1;
    int j : 2;
    int k : 3;
};

int main() {
    std::cout << test<int>::SIZE << "\n";     // 42
    std::cout << test<double>::SIZE << "\n";  // 21
    std::cout << test<float>::SIZE << "\n";   // 21
    std::cout << test<bool>::SIZE << "\n";    // 42, 这个bool，被当作了 integral 类型了
    // std::cout << test<Student>::SIZE << "\n";  // 4
    std::cout << std::endl;
}
