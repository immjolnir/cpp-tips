/*
 * Example to convert the shard_ptr<T> to shared_ptr<const T>.
 */
#include <memory>

struct Student {
    typedef std::shared_ptr<Student> Ptr;
    typedef std::shared_ptr<const Student> ConstPtr;
};

int main() {
    Student::Ptr mutable_ptr = std::make_shared<Student>();

    Student::ConstPtr immutable = mutable_ptr; // It's safe.

    return 0;
}
