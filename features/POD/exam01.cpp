// https://stackoverflow.com/questions/23808357/brace-initialization-for-inherited-pod
#include <iostream>
#include <type_traits>

struct base_pod_t {
    unsigned x;
};

struct der_pod_t : public base_pod_t {};

int main() {
    std::cout << "base_pod_t is POD: " << std::is_pod<base_pod_t>::value << std::endl;  // 1
    std::cout << "der_pod_t  is POD: " << std::is_pod<der_pod_t>::value << std::endl;   // 1

    base_pod_t b1 = {};   // OK
    base_pod_t b2 = {3};  // OK

    der_pod_t p1 = {};  // OK
    //    der_pod_t p2 = {4};   // ERROR!
}
