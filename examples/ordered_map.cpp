#include <algorithm>
#include <iostream>
#include <map>
#include <type_traits>
#include <vector>

#define ROS_PLUS_MESSAGE_TRAITS(msgType)                                  \
    namespace ros {                                                       \
    namespace message_traits {                                            \
    template <>                                                           \
    struct TimeStamp<msgType> {                                           \
        static ros::Time value(const msgType& m) { return m.header.seq; } \
    };                                                                    \
    }                                                                     \
    }

void test_contains(const std::map<int, char>& example) {
    for (int x : {2, 5}) {
        // contains: 	(since C++20)
        if (example.contains(x)) {
            std::cout << x << ": Found\n";
        } else {
            std::cout << x << ": Not found\n";
        }
    }
}

void test_order(std::map<int, char>& m) {
    m.emplace(1, 'c');
    m.emplace(2, 'd');
    m.emplace(10, 'e');
    m.emplace(0, '0');
    for (const auto& p : m) {
        std::cout << p.first << " => " << p.second << "\n";
    }
    std::cout << std::endl;
}

void test_find(const std::map<int, char>& m) {
    auto search = m.find(2);
    if (search != m.end()) {
        std::cout << "Found " << search->first << " " << search->second << '\n';
    } else {
        std::cout << "Not found\n";
    }
}

/*
https://stackoverflow.com/questions/40900530/how-to-find-min-max-in-stdmap-like-in-stdset
Dereference first from the iterator for the key, like this:

// for std::map<int,string> s
auto minKey = s.begin()->first;
auto maxKey = s.rbegin()->first;
This works only for keys, not values, because maps are sorted only on their keys.
*/
void get_min_max_keys(const std::map<int, char>& m) {
    // const auto& elem= *(m.begin());
    int min = m.begin()->first;
    int max = m.rbegin()->first;

    std::cout << "The element with min key is (" << min << " => " << m.at(min) << ") and the max is (" << max << " => "
              << m.at(max) << ")" << std::endl;
}

/*
* https://stackoverflow.com/questions/2659248/how-can-i-find-the-minimum-value-in-a-map

*/
void get_minimum_value(const std::map<int, char>& m) {
    // Since C++11
    using Type = std::remove_const_t<std::remove_reference_t<decltype(m)>>;

    // https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c
    std::cout << "****" << typeid(Type).name() << "****" << std::endl;

    // ordered_map.cpp:65:27: note: candidate function not viable: 1st argument ('const
    // std::pair<const int, char>') would lose const qualifier
    typedef std::add_const_t<Type::value_type> ValueType;

    auto it =
      std::min_element(m.begin(), m.end(), [](ValueType& l, ValueType& r) -> bool { return l.second < r.second; });

    // Since c++14
    // auto it = std::min_element(m.begin(), m.end(),
    //                            [](const auto& l, const auto& r) { return l.second < r.second; });
    std::cout << "The element with minimum value is " << it->first << " => " << it->second << std::endl;
}

void get_erase(std::map<int, char>& m) {
    auto next = m.erase(m.begin());
    std::cout << "After erase the beginning elem, the second element is " << next->first << " => " << next->second
              << std::endl;
}

void retrieve_keys(const std::map<int, char>& map) {
    std::vector<int> keys;
    std::transform(map.begin(), map.end(), std::back_inserter(keys), [](const auto& pair) { return pair.first; });

    for (const auto& key : keys) {
        std::cout << key << std::endl;
    }
}

int main() {
    std::map<int, char> example = {{-1, 'a'}, {-2, 'b'}};
    get_min_max_keys(example);
    get_minimum_value(example);

    test_contains(example);
    test_order(example);
    test_find(example);

    get_min_max_keys(example);
    get_minimum_value(example);

    get_erase(example);
    get_min_max_keys(example);
    get_minimum_value(example);

    // error: value of type 'std::map<int, char>::iterator' (aka '_Rb_tree_iterator<std::pair<const int, char>>') is not
    // contextually convertible to 'bool'
    // if (example.end()) {
    // assignment is lower precedence than !=.
    // https://en.cppreference.com/w/cpp/language/operator_precedence
    // if (auto found = example.find(100) != example.end()) {
    // not work
    // if ((auto found = example.find(100)) != example.end()) {
    //
    // https://en.cppreference.com/w/cpp/language/if
    if (auto found = example.find(1); found != example.end()) {  // Since C++17
        std::cout << "Still be true: " << found->first << " => " << found->second << std::endl;
    } else {
        std::cout << "Its false now!" << std::endl;
    }

    retrieve_keys(example);

    return 0;
}
