#include <boost/io/ios_state.hpp>
#include <boost/math/special_functions/round.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

// https://github.com/strawlab/ros_comm/blob/master/utilities/rostime/include/ros/time.h
namespace ros {
struct Time {
    uint32_t sec, nsec;

    Time(uint32_t sec_, uint32_t nsec_) : sec(sec_), nsec(nsec_) {}

    explicit Time(double t) { fromSec(t); }

    double toSec() const { return (double)sec + 1e-9 * (double)nsec; };

    Time& fromSec(double t) {
        sec = (uint32_t)floor(t);
        nsec = (uint32_t)boost::math::round((t - sec) * 1e9);
        return *static_cast<Time*>(this);
    }

    /* when using ros::Time as the key
    error: invalid operands to binary expression ('const ros::Time' and 'const ros::Time')
      { return __x < __y; }
               ~~~ ^ ~~~
    /usr/bin/../lib/gcc/x86_64-linux-gnu/12/../../../../include/c++/12/bits/stl_tree.h:2220:11: note: in instantiation
    of member function 'std::less<ros::Time>::operator()' requested here
              && _M_impl._M_key_compare(_S_key(_M_rightmost()), __k))
                 ^
    candidate template ignored: could not match 'const reverse_iterator<_Iterator>' against 'const ros::Time'
    operator<(const reverse_iterator<_Iterator>& __x,
    ^
    */
    // We know that the third template parameter of std::map defaults to std::less, which will delegate to operator<.
    // https://www.techiedelight.com/use-std-pair-key-std-map-cpp/
    //
    // Don't provide such method
    // bool operator<(const Time& rhs) const {
    //     std::cout << "operator<" << std::endl;
    //     if (sec < rhs.sec)
    //         return true;
    //     else if (sec == rhs.sec && nsec < rhs.nsec)
    //         return true;
    //     return false;
    // }

    // bool operator==(const Time& rhs) const {
    //     std::cout << "operator==" << std::endl;
    //     return sec == rhs.sec && nsec == rhs.nsec;
    // }
};
}  // namespace ros

std::ostream& operator<<(std::ostream& os, const ros::Time& rhs) {
    boost::io::ios_all_saver s(os);
    os << rhs.sec << "." << std::setw(9) << std::setfill('0') << rhs.nsec;
    return os;
}

// https://www.techiedelight.com/use-std-pair-key-std-map-cpp/
// Using a comparison object
// We can also pass a comparison object as the third template parameter to std::map to override its default order. The
// comparison object takes two pair objects and defines the ordering of the map’s keys by comparing the first and second
// elements of both pairs. If it returns true, the first pair appears before the second pair, and vice versa.
// struct comp {
//     template <typename T>
//     bool operator()(const T& l, const T& r) const {
//         if (l.sec == r.sec) {
//             return l.nsec > r.nsec;
//         }
//         return l.sec < r.sec;
//     }
// };

// https://cplusplus.com/reference/map/map/find/
//
// Two keys are considered equivalent if the container's comparison object returns false reflexively (i.e., no matter
// the order in which the elements are passed as arguments).
// 如果容器的比较对象自反地返回 false（即，无论元素作为参数传递的顺序如何），则两个键被认为是等价的。
//
// https://stackoverflow.com/questions/20168173/when-using-stdmap-should-i-overload-operator-for-the-key-type
// std::map does not care about literal unicity of the keys. It cares about keys equivalence.
// The keys a and b are equivalent by definition when neither `a < b` nor `b < a` is true.
// You should overload operator<.
// The std::map will compare keys using `!(a < b) && !(b < a)` as a test for uniqueness.

struct comp {
    template <typename T>
    bool operator()(const T& l, const T& r) const {
        if (l.sec == r.sec) {
            return l.nsec > r.nsec + 1000;  // Solve the float comparation issue.
        }
        return l.sec < r.sec;
    }
};

int main() {
    ros::Time time0 = ros::Time(1681726505, 254979123);
    std::cout << "time0(as str)=" << time0 << std::fixed << std::setw(9) << std::setfill('0')
              << ", toSec=" << time0.toSec() << ", sec=" << time0.sec << ", nsec=" << time0.nsec
              << std::endl;  // 1681726505.2549791230

    ros::Time time1 = ros::Time(1681726505.254979123);
    std::cout << "time1(as str)=" << time1 << std::fixed << std::setw(9) << std::setfill('0')
              << ", toSec=" << time1.toSec() << ", sec=" << time1.sec << ", nsec=" << time1.nsec
              << std::endl;  // 1681726505.2549791340

    std::cout << "returns false reflexively: " << comp()(time0, time1) << std::endl;
    std::cout << "returns false reflexively: " << comp()(time1, time0) << std::endl;

    std::map<ros::Time, std::string, comp> m = {
      {ros::Time(1681726505.254979123), "A"},
      {ros::Time(1681726504.855274456), "B"},
      {ros::Time(1681726500.355335789), "C"},
    };

    auto found = m.find(time0);  // No
    if (found != m.end()) {
        std::cout << "Found. value=" << found->second << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    auto found1 = m.find(time1);
    if (found1 != m.end()) {
        std::cout << "Found. value=" << found1->second << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    auto found2 = m.find(ros::Time(1681726505.25497));
    if (found2 != m.end()) {
        std::cout << "Found. value=" << found2->second << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }
}
