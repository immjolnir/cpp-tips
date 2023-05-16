
# linkage-sepcifiction


# designated-initializers
* What's the aggregate type in c++?

Definitions

An aggregate is one of the following types:

* array type
* class type (typically, struct or union), that has
    * no user-declared constructors (until C++11)
    * no user-provided, inherited, or explicit constructors
    * no user-declared or inherited constructors
    * no private or protected non-static data members
    * no base classes (until C++17)
    * no virtual base classes
    * no private or protected direct base classes
    * no virtual member functions
    * no default member initializers (until C++14)


## [Aggregate Initialization](https://en.cppreference.com/w/cpp/language/aggregate_initialization)
Syntax
```c++
T object = { arg1, arg2, ... };	(1)	
T object { arg1, arg2, ... };	(2)	(since C++11)
T object = { .des1 = arg1 , .des2 { arg2 } ... };	(3)	(since C++20)
T object { .des1 = arg1 , .des2 { arg2 } ... };	(4)	(since C++20)
```

1,2) Initializing an aggregate with an `ordinary initializer list`.
3,4) Initializing an aggregate with `designated initializers` (aggregate class only).

## [Designated initializers](https://en.cppreference.com/w/cpp/language/aggregate_initialization#Designated_initializers)

>  The syntax forms (3,4) are known as `designated initializers`: each `designator` must name a direct non-static data member of T, and all `designator`s used in the expression must appear in the **same order** as the data members of T.

* exam01.cpp

For a non-union aggregate, elements for which a designated initializer is not provided are initialized the same as described above for when the number of initializer clauses is less than the number of members (default member initializers where provided, empty list-initialization otherwise):

* exam02.cpp


* exam03.c vs exam03.cpp

Note: out-of-order designated initialization, nested designated initialization, mixing of designated initializers and regular initializers, and designated initialization of arrays are all supported in the C programming language, but are not allowed in C++.


* exam04.cpp and exam04-fixed.cpp
See [refer](https://stackoverflow.com/questions/58876020/designated-initializers-in-c20).

## Other Resources
* https://hackingcpp.com/cpp/lang/aggregates.html

Member variables are stored in the same order as they are declared.

### Why Custom Types / Data Aggregation?
* Interfaces become easier to use correctly
* semantic data grouping: point, date, …
* avoids many function parameters and thus, confusion
* can return multiple values from function with one dedicated type instead of multiple non-const reference output parameters

### Copying
* Copies are always deep copies of all members!
* Copy Construction = create new object with same values as source
* Copy Assignment = overwrite existing object's values with that of source

# POD

```
exam01.cpp:12:48: warning: ‘template<class _Tp> struct std::is_pod’ is deprecated: use is_standard_layout && is_trivial instead [-Wdeprecated-declarations]
   12 |     std::cout << "base_pod_t is POD: " << std::is_pod<base_pod_t>::value << std::endl;
```