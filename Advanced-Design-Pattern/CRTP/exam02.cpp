#include "exam02.h"

#include <iostream>

void Derived::implementation() { std::cout << "Derived::implementation" << std::endl; }

void Derived::static_sub_func() { std::cout << "Derived static_sub_func" << std::endl; }
