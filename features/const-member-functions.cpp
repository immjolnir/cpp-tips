/*
 这个例子说明，在定义函数的时候，如果确认不会修改对象，那么就在函数定义末尾加上  const.
 这中情况，对于 std::shared_ptr 友好
 * */
#include <memory>
// https://stackoverflow.com/questions/16691207/c-c-nan-constant-literal
#include <iostream>
#include <limits>  //  quiet_NaN

class Student {
  public:
    typedef std::shared_ptr<const Student> ConstPtr;
    typedef std::shared_ptr<Student> Ptr;

    void set_refined_yaw(float yaw) { _refined_yaw = yaw; }

    float get_refined_yaw() { return _refined_yaw; }

    void set_filtered(bool enabled) { _filtered = enabled; }

    bool get_filtered() {
        std::cout << "without const specifier" << std::endl;
        return _filtered;
    }

    // bool get_filtered() const {
    //     std::cout << "with const specifier" << std::endl;
    //     return _filtered;
    // }

  private:
    float _refined_yaw = std::numeric_limits<float>::quiet_NaN();
    bool _filtered = false;
};

int main() {
    {
        Student* st0 = new Student();
        st0->get_filtered();
    }

    {
        const Student* st0 = new Student();
        /*
         error: passing ‘const Student’ as ‘this’ argument discards qualifiers [-fpermissive]
         42 |         st0->get_filtered();
        */
        st0->get_filtered();
    }

#ifdef XX
    // std::shared_ptr
    {
        Student::ConstPtr st0(new Student());
        /*
        error: passing ‘std::__shared_ptr_access<const Student, __gnu_cxx::_S_atomic, false, false>::element_type’ {aka
        ‘const Student’} as ‘this’ argument discards qualifiers [-fpermissive] 25 |     bool filtered =
        st0->get_filtered();
         */
        bool filtered = st0->get_filtered();
    }

#endif
    {
        Student::Ptr st1(new Student());
        bool filtered = st1->get_filtered();
    }

    return 0;
}
