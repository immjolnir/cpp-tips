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
    std::cout << std::boolalpha << std::is_aggregate_v<Person> << '\n';    // true is printed
    std::cout << std::boolalpha << std::is_aggregate_v<Employee> << '\n';  // true is printed

    Person p{.name{"John"}, .surname{"Wick"}, .age{40}};                     // it's ok
    Employee e1{.name{"John"}, .surname{"Wick"}, .age{40}, .salary{50000}};  // doesn't compile, WHY ?
    // Employee e1{{.name{"John"}, .surname{"Wick"}, .age{40}}, {.salary{50000}}};  // doesn't compile, WHY ?

    // For e2 compiler prints a warning "missing initializer for member 'Employee::<anonymous>'
    // [-Wmissing-field-initializers]"
    Employee e2{.salary{55000}};
}
