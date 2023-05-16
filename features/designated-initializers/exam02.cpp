#include <string>

struct A {
    std::string str;
    int n = 42;
    int m = -1;
};

A a{.m = 21};
// Initializes str with {}, which calls the default constructor
// then initializes n with = 42
// then initializes m with = 21

A b{.n = 21};  // OK

/*
 error: designator order for field ‘A::n’ does not match declaration order in ‘A’
   14 | A b{.m = 21, .n = 21};
*/
// A b{.m = 21, .n = 21};
