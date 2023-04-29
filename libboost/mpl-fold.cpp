#include <boost/mpl/fold.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_float.hpp>

namespace mpl = boost::mpl;

void bbegin();

typedef mpl::list<long, float, short, double, float, long, long double> types;
typedef mpl::fold<types, mpl::int_<0>,
                  mpl::if_<boost::is_float<mpl::_2>, mpl::next<mpl::_1>, mpl::_1> >::type
    number_of_floats;

void eend();

int main() {
  static_assert(number_of_floats::value == 4, "it should has 4 floats.");

  return 0;
}