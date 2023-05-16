 
# Aggregate Classes
From "C++ Primer, Fifth Edition"

An aggregate class gives users direct access to its members and has special initialization syntax. A class is an aggregate if

• All of its data members are public

• It does not define any constructors

• It has no in-class initializers (§ 2.6.1, p. 73)

• It has no base classes or virtual functions, which are class-related features that we’ll cover in Chapter 15


For example, the following class is an aggregate:
```c++
struct Data {
    int ival;
    string s;
};
```

We can initialize the data members of an aggregate class by providing a braced list of member initializers:
```
// val1.ival = 0; val1.s = string("Anna");
Data val1 = { 0, "Anna"};
```


## [is_aggregate](https://en.cppreference.com/w/cpp/types/is_aggregate)

* exam01.cpp
* https://stackoverflow.com/questions/4178175/what-are-aggregates-and-pods-and-how-why-are-they-special
