// https://stackoverflow.com/questions/71138329/stdinitializer-list-and-stdmake-shared-too-many-arguments-3-expected-0
//
#include <initializer_list>
#include <memory>
#include <vector>

struct S {
    int j;
    double y;
    std::vector<int> data;

    S(int i, double x, std::initializer_list<int> list) : j(i), y(x), data(list) {}
};

auto make_shared_s(int x, double y, std::initializer_list<int> l) { return std::make_shared<S>(x, y, l); }

int main() {
    using ints = std::initializer_list<int>;
    auto ptr1 = std::make_shared<S>(2, 8.3, ints{1, 2, 3});
    auto ptr2 = make_shared_s(1, 1.2, {1, 2, 3});
}
