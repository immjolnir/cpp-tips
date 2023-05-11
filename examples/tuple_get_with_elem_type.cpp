#include <cxxabi.h>
#include <iostream>
#include <string>
#include <tuple>
#include <typeinfo>  // for typeid
#include <vector>

struct Course {
    std::string name;
    float score;
};

struct Student {
    std::string name;
    std::vector<Course> courses;
};

std::ostream& operator<<(std::ostream& out, const Student& obj) {
    out << "Student{name=" << obj.name << "}";
    return out;
}

std::ostream& operator<<(std::ostream& out, const Course& obj) {
    out << "Course{name=" << obj.name << "}";
    return out;
}

int main() {
    Student st{"Scott"};
    Course math{"Math", 90};
    Course chinese{"Chinese", 90};

    // clang-format off
/*
/usr/include/c++/11/tuple: In instantiation of ‘constexpr _Tp& std::get(std::tuple<_Types ...>&) [with _Tp = Course; _Types = {Student, Course, Course, int}]’:
tuple_get_with_elem_type.cpp:35:104:   required from here
/usr/include/c++/11/tuple:1456:27: error: static assertion failed: the type T in std::get<T> must occur exactly once in the tuple
 1456 |       static_assert(__idx < sizeof...(_Types),
      |                     ~~~~~~^~~~~~~~~~~~~~~~~~~
/usr/include/c++/11/tuple:1456:27: note: ‘(((long unsigned int)__idx) < 4)’ evaluates to false
/usr/include/c++/11/tuple:1458:38: error: use of deleted function ‘std::__enable_if_t<(__i >= sizeof... (_Types))> std::__get_helper(const std::tuple<_Types ...>&) [with long unsigned int __i = 4; _Types = {Student, Course, Course, int}; std::__enable_if_t<(__i >= sizeof... (_Types))> = void]’
 1458 |       return std::__get_helper<__idx>(__t);
      |              ~~~~~~~~~~~~~~~~~~~~~~~~^~~~~
/usr/include/c++/11/tuple:1392:5: note: declared here
 1392 |     __get_helper(const tuple<_Types...>&) = delete;
      |     ^~~~~~~~~~~~
*/
    // clang-format on
    // std::tuple<Student, Course, Course, int> t{st, math, chinese, 10};

    // https://en.cppreference.com/w/cpp/utility/tuple/get
    // clang-format off
    /*
    tuple_get_with_elem_type.cpp:53:52: error: cannot bind rvalue reference of type ‘Student&&’ to lvalue of type ‘Student’
    53 |     auto t = std::make_tuple<Student, Course, int>(st, math, 10);
       |    
    
    template< class... Types >
    std::tuple<VTypes...> make_tuple( Types&&... args );
    */
    // clang-format on
    // auto t = std::make_tuple<Student, Course, int>(st, math, 10);

    std::tuple<Student, Course, int> t{st, math, 10};

    std::cout << "int=" << std::get<int>(t) << ", " << std::get<Student>(t) << ", " << std::get<Course>(t) << std::endl;

    return 0;
}
