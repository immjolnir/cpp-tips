#include <functional>
#include <iostream>

int triple(int a) { return 3 * a; }

int apply(int (*f)(int), int n) { return f(n); }

int main() {
    std::cout << apply(triple, 7) << "\n";
    std::cout << apply(&triple, 7) << "\n";
}
