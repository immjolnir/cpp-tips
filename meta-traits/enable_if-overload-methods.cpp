#include <type_traits>
#include <iostream>

template <typename T>
void print(typename std::enable_if<std::is_integral<T>::value, T>::type i)
{
  std::cout << "Integral: " << i << '\n';
}

template <typename T>
void print(typename std::enable_if<std::is_floating_point<T>::value, T>::type f)
{
  std::cout << "Floating point: " << f << '\n';
}

int main()
{
  print<short>(1);
  print<long>(2);
  print<double>(3.14);
  print<float>(15.926);
}
