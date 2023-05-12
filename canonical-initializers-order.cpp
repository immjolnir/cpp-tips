// https://wiki.sei.cmu.edu/confluence/display/cplusplus/OOP53-CPP.+Write+constructor+member+initializers+in+the+canonical+order
/**
 * The member initializer list for a class constructor allows members to be initialized to specified values and for base class constructors to be called with specific arguments. However, the order in which initialization occurs is fixed and does not depend on the order written in the member initializer list. The C++ Standard, [class.base.init], paragraph 11 [ISO/IEC 14882-2014], states the following:

In a non-delegating constructor, initialization proceeds in the following order:
— First, and only for the constructor of the most derived class, virtual base classes are initialized in the order they appear on a depth-first left-to-right traversal of the directed acyclic graph of base classes, where “left-to-right” is the order of appearance of the base classes in the derived class base-specifier-list.
— Then, direct base classes are initialized in declaration order as they appear in the base-specifier-list (regardless of the order of the mem-initializers).
— Then, non-static data members are initialized in the order they were declared in the class definition (again regardless of the order of the mem-initializers).
— Finally, the compound-statement of the constructor body is executed.
[Note: The declaration order is mandated to ensure that base and member subobjects are destroyed in the reverse order of initialization. —end note]

Consequently, the order in which member initializers appear in the member initializer list is irrelevant. The order in which members are initialized, including base class initialization, is determined by the declaration order of the class member variables or the base class specifier list. Writing member initializers other than in canonical order can result in undefined behavior, such as reading uninitialized memory.

Always write member initializers in a constructor in the canonical order: first, direct base classes in the order in which they appear in the base-specifier-list for the class, then nonstatic data members in the order in which they are declared in the class definition.

 * */
