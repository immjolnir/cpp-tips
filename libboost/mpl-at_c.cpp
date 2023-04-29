#include <iostream>
#include <string>

#include "header.h"

/*
* Synopsis
template<typename Sequence, long n >
struct at_c {
    typedef unspecified type;
};

* Description
    Returns a type identical to the nth element from the beginning of the sequence.
    `at_c<Sequence,n>::type` is a shorcut notation for `at<Sequence, long_<n>>::type`.
*/

struct NullType {};

namespace mpl = boost::mpl;

template <typename M0, typename M1, typename M2 = NullType, typename M3 = NullType,
          typename M4 = NullType, typename M5 = NullType, typename M6 = NullType>
class Student {
  typedef mpl::vector<M0, M1, M2, M3, M4, M5, M6> Messages;

 public:
  typedef typename mpl::fold<Messages, mpl::int_<0>,
                             mpl::if_<mpl::not_<boost::is_same<mpl::_2, NullType> >,
                                      mpl::next<mpl::_1>, mpl::_1> >::type RealTypeCount;
  uint32_t count() { return (uint32_t)RealTypeCount::value; }

 public:
  template <int i, typename T>
  bool same() {
    typedef typename mpl::at_c<Messages, i>::type iType;
    return boost::is_same<T, iType>::value;
  }
};

int main() {
  Student<int, double> st;
  std::cout << "RealTypeCount = " << st.count() << std::endl;

  bool same_index0 = st.same<0, int>();
  bool same_index1 = st.same<1, double>();
  std::cout << same_index0 << ", " << same_index1 << std::endl;

  bool not_same_index0 = st.same<0, double>();
  bool not_same_index1 = st.same<1, int>();
  std::cout << not_same_index0 << ", " << not_same_index1 << std::endl;

  Student<int, double, std::string> st3;
  bool same_index3 = st.same<3, std::string>();

  std::cout << "RealTypeCount = " << st3.count() << ", same_index3=" << same_index3 << std::endl;
  return 0;
}
