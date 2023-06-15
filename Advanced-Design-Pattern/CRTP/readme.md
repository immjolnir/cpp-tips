# [CRTP: Curiously Recurring Template Pattern](https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern)

The curiously recurring template pattern (CRTP) is an idiom, originally in C++, in which a class X derives from a class template instantiation using X itself as a template argument.[1] More generally it is known as F-bound polymorphism, and it is a form of F-bounded quantification.

* General form
```c++
// The Curiously Recurring Template Pattern (CRTP)
template <class T>
class Base
{
    // methods within Base can use template to access members of Derived
};
class Derived : public Base<Derived>
{
    // ...
};
```

It also figures prominently in the C++ implementation of the *Data*, *Context*, and *Interaction* paradigm. In addition, CRTP is used by the C++ standard library to implement the `std::enable_shared_from_this `functionality.

# exam01: Object counter
The main purpose of an object counter is retrieving statistics of object creation and destruction for a given class.[11] This can be easily solved using CRTP:

# exam02: Static Polymorphism
This technique achieves a similar effect to the use of virtual functions, without the costs (and some flexibility) of dynamic polymorphism. This particular use of the CRTP has been called "simulated dynamic binding" by some.

To elaborate on the above example, consider a base class with no virtual functions. Whenever the base class calls another member function, it will always call its own base class functions. When we derive a class from this base class, we inherit all the member variables and member functions that were not overridden (no constructors or destructors). If the derived class calls an inherited function which then calls another member function, then that function will never call any derived or overridden member functions in the derived class.

However, if base class member functions use CRTP for all member function calls, the overridden functions in the derived class will be selected at compile time. This effectively emulates the virtual function call system at compile time without the costs in size or function call overhead (VTBL structures, and method lookups, multiple-inheritance VTBL machinery) at the disadvantage of not being able to make this choice at runtime.

