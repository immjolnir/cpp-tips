#include <functional>
#include <iostream>

int triple(int a) { return 3 * a; }

int main() {
    int (*p1)(int) = &triple;
    std::cout << p1(7) << "\n";  // 21

    int (*p2)(int) = triple;         // same as &f
    std::cout << triple(7) << "\n";  // 21
}
