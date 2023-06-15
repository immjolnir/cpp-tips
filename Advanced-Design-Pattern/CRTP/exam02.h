// Static polymorphism
// Typically, the base class template will take advantage of the fact that member function bodies (definitions) are not
// instantiated until long after their declarations, and will use members of the derived class within its own member
// functions, via the use of a cast; e.g.:

template <class T>
struct Base {
    void interface() {
        // ...
        static_cast<T*>(this)->implementation();
        // ...
    }

    static void static_func() {
        // ...
        T::static_sub_func();
        // ...
    }
};

struct Derived : Base<Derived> {
    void implementation();
    static void static_sub_func();
};