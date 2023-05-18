#include <iostream>

int main() {
    int i = 0;
    auto j = i;
    j = 1;
    std::cout << i << ", " << j << std::endl;  // 0, 1 So j is not a reference.

    return 0;
}
