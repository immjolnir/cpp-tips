/*
 * https://www.tutorialspoint.com/cplusplus/cpp_operators.htm
 * An operator is a symbol that tells the compiler to perform specific mathematical or logical manipulations.
 * C++ is rich in built-in operators and provide the following types of operators
 * - Arithmetic Operators: +, -, *, /, %, ++, --
 * - Relational Operators: ==, !=, <, >, <=, >=
 * - Logical Operators: &&, ||, !
 * - Bitwise Operators: &,|,^,~,<<,>>
 * - Assignment Operators: =,+=,-=,/=,%=,<<=, >>=,&=,^=,|=
 * - Misc Operators: sizeof,?:,,,&,*,
 *
 * Operator overloading
 * https://en.cppreference.com/w/cpp/language/operators
 *
 * Function call operator
 * When a user-defined class overloads the function call operator, operator(), it becomes a FunctionObject type.
 * An object of such a type can be used in a function call expression:
 */

// An object of this type represents a linear function of one variable `a * x + b`.

#include <iostream>

struct Linear {
    double a, b;

    double operator()(double x) const { return a * x + b; }
};

int main() {
    Linear f{2, 1};   // Represents function 2x + 1.
    Linear g{-1, 0};  // Represents function -x.
    // f and g are objects that can be used like a function.

    double f_0 = f(0);
    double f_1 = f(1);

    double g_0 = g(0);
    std::cout << f_0 << ", " << f_1 << ", " << g_0 << ", " << Linear({2, 1})(1) << std::endl;
}
