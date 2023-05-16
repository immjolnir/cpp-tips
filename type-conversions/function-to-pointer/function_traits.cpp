/*
https://stackoverflow.com/questions/54357936/implicit-cast-from-function-to-function-pointer

*/
#include "utility/typeinfo.h"

#include <iostream>

struct Student {
    using FuncType = double(int, double);

    void operator()(int i, double j) { std::cout << "operator: i=" << i << ", j=" << j << std::endl; }

    void operator()(FuncType* func, int i, double j) {
        std::cout << "operator with FuncType: " << func(i, j) << std::endl;
    }

    // It's ok enable it. For there is an implicit convertion from Function to Function Pointer.
    //
    // void operator()(FuncType func, int i, double j) {
    //     std::cout << "operator with FuncType: " << func(i, j) << std::endl;
    // }
};

double Add(int i, double j) { return i + j; }

int main() {
    std::cout << "TypeInfo: " << utility::typeInfo<Student::FuncType>() << std::endl;
    std::cout << "TypeInfo: " << utility::typeInfo<Student::FuncType*>() << std::endl;

    Student st;
    st(1, 2);

    auto func = [](int i, double j) { return i + j; };

    st(func, 1, 2);
    st(Add, 1, 2);
}
