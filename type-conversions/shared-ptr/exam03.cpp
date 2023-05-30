/*
 * Conversion from boost::shared_ptr to std::shared_ptr?
 * https://stackoverflow.com/questions/6326757/conversion-from-boostshared-ptr-to-stdshared-ptr
 * https://stackoverflow.com/questions/71572186/question-on-converting-boost-shared-pointer-to-standard-shared-pointer/71575543#71575543
 *
 */

#include <boost/shared_ptr.hpp>

#include <iostream>
#include <memory>

template <class T>
std::shared_ptr<T> to_std(boost::shared_ptr<T>& p) {
    return std::shared_ptr<T>(p.get(), [p](...) mutable { p.reset(); });
}

template <class T>
boost::shared_ptr<T> to_boost(std::shared_ptr<T>& p) {
    return boost::shared_ptr<T>(p.get(), [p](...) mutable { p.reset(); });
}

struct Student {
    Student() { std::cout << "ctor" << std::endl; }

    void wal() { std::cout << "Write-Ahead Logging" << std::endl; }

    ~Student() { std::cout << "dtor" << std::endl; }
};

int main() {
    {  // basics
        boost::shared_ptr<Student> st0(new Student);
        std::shared_ptr<Student> st1(new Student);

        // conversion from ‘boost::shared_ptr<Student>’ to non-scalar type ‘std::shared_ptr<Student>’ requested
        // decltype(st1) st2 = st0;

        decltype(st1) st2 = to_std(st0);
        decltype(st0) st3 = to_boost(st1);
    }

    {  // go deeper
        std::cout << "====== deeper ======" << std::endl;
        boost::shared_ptr<Student> d_st0;
        {
            std::shared_ptr<Student> st(new Student);
            d_st0 = to_boost(st);
        }
        d_st0->wal();  // the st is dtor at the end of its lifetime instead of inner-most.
    }

    return 0;
}
