#include <boost/io/ios_state.hpp>
#include <boost/math/special_functions/round.hpp>
#include <cmath>
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
    bool operator<(const Time& rhs) const {
        std::cout << "operator<" << std::endl;
        if (sec < rhs.sec)
            return true;
        else if (sec == rhs.sec && nsec < rhs.nsec)
            return true;
        return false;
    }

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

int main() {
    ros::Time time0 = ros::Time(1681726505, 254979123);
    std::cout << "time0(as str)=" << time0 << std::setw(9) << std::setfill('0') << ", toSec=" << time0.toSec()
              << ", sec=" << time0.sec << ", nsec=" << time0.nsec << std::endl;

    ros::Time time1 = ros::Time(1681726505.254979123);
    std::cout << "time1(as str)=" << time1 << std::setw(9) << std::setfill('0') << ", toSec=" << time1.toSec()
              << ", sec=" << time1.sec << ", nsec=" << time1.nsec << std::endl;
    // Why time0 is not equals time1?

    std::map<ros::Time, std::string> m = {
      {ros::Time(1681726505.254979123), "A"},
      {ros::Time(1681726504.855274456), "B"},
      {ros::Time(1681726500.355335789), "C"},
    };

    // https://en.cppreference.com/w/cpp/container/map/find
    auto found = m.find(time0);  // why find still call std::less(operator<)?
    if (found != m.end()) {      // Not found
        std::cout << "Found. value=" << found->second << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    auto found1 = m.find(time1);
    if (found1 != m.end()) {  // Found
        std::cout << "Found. value=" << found1->second << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }
}
