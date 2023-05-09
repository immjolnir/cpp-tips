#include <iostream>
#include <tuple>

// /home/insights/insights.cpp:4:19: error: template parameter pack must be the last template parameter
template <class... Types, size_t... I>
struct Tuple {};

int main() {
    Tuple<int, bool, 1, 2, 3> t0;
    return 0;
}
