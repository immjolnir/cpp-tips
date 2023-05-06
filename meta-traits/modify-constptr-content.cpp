#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>

struct Course {
    std::string name;
    float score;

    friend std::ostream& operator<<(std::ostream& out, const Course& obj) {
        out << "Course [" << obj.name << ", " << std::fixed << std::setprecision(3) << obj.score << "]";
        return out;
    }
};

// Removing const from std::shared_ptr<const T>.
// https://stackoverflow.com/questions/71984022/removing-const-casting-from-stdshared-ptrconst-t-to-t
template <typename T>
void doModification(T& t) {
    typedef std::remove_cv_t<typename T::element_type> element_type;
    std::cout << "element_type is " << typeid(element_type).name() << ", prior is "
              << typeid(typename T::element_type).name() << std::endl;

    std::cout << typeid(decltype(t.get())).name() << ", " << typeid(Course*).name() << ", "
              << typeid(const Course*).name() << std::endl;

    // error: no viable conversion from 'shared_ptr<const Course>' to 'shared_ptr<element_type>'
    element_type* elem = const_cast<element_type*>(t.get());  // drop const qualifier
    elem->score = 100;
    elem->name = "Chinese";
}

void remove_constness() {
    char* const str1 = "david";
    char* str2 = const_cast<char*>(str1);
    str2 = "tna";
}

int main() {
    std::shared_ptr<const Course> immutable = nullptr;
    immutable.reset(new Course{"math", 99});

    // error: cannot assign to return value because function 'operator->' returns a const value
    // immutable->score = 100;

    // no matching conversion for static_cast from 'std::shared_ptr<const Course>' to 'std::shared_ptr<Course>'
    // std::shared_ptr<Course> mutable_obj = static_cast<std::shared_ptr<Course>>(immutable);
    // mutable_obj->score = 100;

    remove_constness();

    std::cout << "imutable=" << *immutable << std::endl;
    doModification(immutable);
    std::cout << "modification is done. imutable=" << *immutable << std::endl;

    // Course& mutable_obj = *immutable;
    // mutable_obj.score = 100;

    const Course* c0 = new Course({"math", 99});

    Course* c1 = const_cast<Course*>(c0);
    c1->score = 100;

    return 0;
}
