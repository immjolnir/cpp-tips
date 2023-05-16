// clang-format off
/* 
$ g++  -c exam01.cpp 
exam01.cpp:10:19: error: designator order for field ‘A::x’ does not match declaration order in ‘A’
   10 | A a{.y = 2, .x = 1};  // error; designator order does not match declaration order
*/
// clang-format on
struct A {
    int x;
    int y;
    int z;
};

A a{.y = 2, .x = 1};  // error; designator order does not match declaration order
A b{.x = 1, .z = 2};  // ok, b.y initialized to 0
