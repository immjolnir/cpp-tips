/*
 * https://www.techiedelight.com/retrieve-all-keys-from-a-map-in-cpp/
 * */

// Starting with C++14, we can replace decltype()::value_type with auto.

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
 
int main()
{
    std::map<int, char> map = {
        {1, 'A'}, {2, 'B'}, {3, 'C'}, {4, 'B'}
    };
 
    std::vector<int> keys;
    std::transform(map.begin(), map.end(), std::back_inserter(keys),
        [](const auto &pair){
            return pair.first;
        });
 
 
    for (const auto &key: keys) {
        std::cout << key << std::endl;
    }
 
    return 0;
}
