#include <numeric>
#include <string>
#include <vector>

// https://en.cppreference.com/w/cpp/string/basic_string/to_string
// numeric only
template <typename T>
std::string join(std::vector<T> const& vec, const std::string& delim) {
    if (vec.empty()) {
        return "";
    }
    return std::accumulate(vec.begin() + 1, vec.end(), std::to_string(vec[0]),
                           [&delim](const std::string& a, T b) { return a + delim + std::to_string(b); });
}

// std::string only
// Because of std::to_string(vec[0]) cannot work on a string&
template <>
std::string join<std::string>(std::vector<std::string> const& vec, const std::string& delim) {
    if (vec.empty()) {
        return "";
    }
    return std::accumulate(vec.begin() + 1, vec.end(), vec[0],
                           [&delim](const std::string& a, const std::string& b) { return a + delim + b; });
}
