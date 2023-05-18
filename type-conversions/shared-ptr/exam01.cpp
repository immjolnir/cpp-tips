/*
 * Example to convert the shard_ptr<T const> to shared_ptr<T>.
 */
#include <memory>

struct Student {
    typedef std::shared_ptr<Student> Ptr;
    typedef std::shared_ptr<const Student> ConstPtr;
};

int main() {
    Student::ConstPtr const_ptr;
    const_ptr.reset(new Student);

    // error: no viable conversion from 'shared_ptr<const Student>' to 'shared_ptr<Student>'
    // Student::Ptr ptr = const_ptr;

    // error: reinterpret_cast from 'Student::ConstPtr' (aka 'shared_ptr<const Student>') to 'Student::Ptr' (aka
    // 'shared_ptr<Student>') is not allowed
    // Student::Ptr ptr = reinterpret_cast<Student::Ptr>(const_ptr);

    // https://stackoverflow.com/questions/9960292/can-i-cast-shared-ptrt-to-shared-ptrt-const-without-changing-use-count
    // warning: use of function template name with no prior declaration in function call with explicit template
    // arguments is a C++20 extension [-Wc++20-extensions]
    // Student::Ptr ptr = static_pointer_cast<Student::Ptr>(const_ptr);

    Student::Ptr ptr;
    ptr.reset(new Student(*const_ptr));

    return 0;
}
