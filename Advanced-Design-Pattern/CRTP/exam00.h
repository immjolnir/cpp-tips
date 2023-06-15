/*
https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern

The main purpose of an object counter is retrieving statistics of object creation and destruction for a given class.

This can be easily solved using CRTP:

Each time an object of class X is created, the constructor of counter<X> is called, incrementing both the created and
alive count. Each time an object of class X is destroyed, the alive count is decremented. It is important to note that
counter<X> and counter<Y> are two separate classes and this is why they will keep separate counts of Xs and Ys. In this
example of CRTP, this distinction of classes is the only use of the template parameter (T in counter<T>) and the reason
why we cannot use a simple un-templated base class.
*/
#include <iostream>
#include <ostream>

template <typename T>
struct counter {
    static inline int objects_created = 0;
    static inline int objects_alive = 0;

    counter() {
        ++objects_created;
        ++objects_alive;
    }

    counter(const counter&) {
        ++objects_created;
        ++objects_alive;
    }

    static void metric() { std::cout << objects_created << ", " << objects_alive << std::endl; }

  protected:
    ~counter()  // objects should never be removed through pointers of this type
    {
        --objects_alive;
    }
};

class X : public counter<X> {
    // ...
  public:
    void print();
};

class Y : public counter<Y> {
    // ...
};
