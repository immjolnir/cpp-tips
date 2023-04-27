#include <array>
#include <cstddef>
#include <iostream>

void bbegin();
template<std::size_t ID>
struct imp
{
  constexpr static std::size_t value = ID + imp<ID - 1>::value;
};

template<>
struct imp<0>
{
  constexpr static std::size_t value = 0;
};

template<std::size_t A>
struct Wrap_
{
  template<std::size_t ID>
  constexpr static std::size_t value = imp<A + ID>::value;
};

std::size_t nums = Wrap_<10>::value<10>;
void eend();

int main()
{
  //   std::array<std::size_t, Wrap_<10>::value<10>> nums = { 0, 1, 2, 3 };
  //   std::cout << "nums contains " << nums.size() << " elements.\n"; // 210 elements

  std::cout << "nums contains " << nums << " elements.\n"; // 210 elements
  return 0;
}
