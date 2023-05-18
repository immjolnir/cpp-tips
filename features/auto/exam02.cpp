#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{0, 0, 0};
    auto x = v[1];
    x = 1;
    std::cout << v[0] << ' ' << v[1] << ' ' << v[2] << '\n';  // 0, 0, 0
    // Since we have used a bare auto, the type of x will be int, so we get a copy.
    // Therefore, the code prints 0 0 0, as you would expect.
    std::cout << std::endl;
    return 0;
}
