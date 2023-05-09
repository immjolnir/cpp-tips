#include <iostream>
#include <numeric>
#include <vector>

int func(const std::vector<int>& v) {
    const static int init_sum = [](const std::vector<int>& init_vec) {
        return std::accumulate(init_vec.begin(), init_vec.end(), 0, [](int sum, int next_elem) {
            sum += next_elem;
            return sum;
        });
    }(v);

    return init_sum;
}

int main() {
    std::vector<int> vec0{1, 2, 3, 4};
    std::vector<int> vec1{5, 6, 7, 8};

    int res0 = func(vec0);  // 10
    int res1 = func(vec1);  // still be 10
    std::cout << res0 << ", " << res1 << std::endl;
    return 0;
}
