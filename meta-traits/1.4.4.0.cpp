#include <array>
#include <cstddef>
#include <iostream>

void bbegin();
template <size_t A>
struct Wrap_ {
  template <size_t ID, typename TDummy = void>
  struct imp {
    constexpr static size_t value = ID + imp<ID - 1>::value;
  };

  template <typename TDummy>
  struct imp<0, TDummy> {
    constexpr static size_t value = 0;
  };

  template <size_t ID>
  constexpr static size_t value = imp<A + ID>::value;
};

size_t v0 = Wrap_<3>::value<2>;
size_t v1 = Wrap_<10>::value<2>;
void eend();

int main() {
  std::cerr << v0 << std::endl;
  std::cerr << v1 << std::endl;
}
