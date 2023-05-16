/*
$ g++ -std=c++20 -Wmissing-field-initializers exam04-fixed.cpp
*/
#include <ios>
#include <iostream>
#include <string>
#include <type_traits>

struct Person {
    std::string name{};
    std::string surname{};
    unsigned age{};
};

constexpr unsigned DEFAULT_SALARY{10000};

struct Employee : Person {
    unsigned salary{DEFAULT_SALARY};
};

int main() {
    std::cout << "Person is POD: " << std::is_pod<Person>::value << std::endl;
    std::cout << "Employee is POD: " << std::is_pod<Employee>::value << std::endl;

    std::cout << std::boolalpha << std::is_aggregate_v<Person> << '\n';    // true is printed
    std::cout << std::boolalpha << std::is_aggregate_v<Employee> << '\n';  // true is printed

    Person p{.name{"John"}, .surname{"Wick"}, .age{40}};  // it's ok

    Employee e0{"John", "Wick", 40, 50000};
    Employee e1{{"John", "Wick", 40}, 50000};

    // In this case the direct base class is initialized by a designated initializer list while the class Employe in
    // whole is initialised by a non-designated initializer list.
    Employee e1_fixed{{.name{"John"}, .surname{"Wick"}, .age{40}}, 50000};

    // error: either all initializer clauses should be designated or none of them should be
    // Employee e11{{.name{"John"}, .surname{"Wick"}, .age{40}}, .salary = 50000};  // failed.

    // For e2 compiler prints a warning "missing initializer for member 'Employee::<anonymous>'
    // [-Wmissing-field-initializers]"
    Employee e2{.salary{55000}};
}
