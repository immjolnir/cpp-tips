# [Function-to-pointer conversion](https://en.cppreference.com/w/cpp/language/implicit_conversion#Function_to_pointer)

An `lvalue` of function type T can be implicitly converted to a `prvalue` pointer to that function. This does not apply to non-static member functions because `lvalues` that refer to non-static member functions do not exist.


* [exam01.cpp](https://stackoverflow.com/questions/54357936/implicit-cast-from-function-to-function-pointer)

I have a function that accepts as an argument a function pointer. Surprisingly, I can pass in both a function pointer and an ordinary function.

I'm confused about why this works. Is there an implicit conversion from functions to function pointers?

> An lvalue of function type T can be implicitly converted to a prvalue pointer to that function. This does not apply to non-static member functions because lvalues that refer to non-static member functions do not exist.


* exam02.cpp

> A pointer to function can be initialized with an address of a non-member function or a static member function. Because of the function-to-pointer implicit conversion, the address-of operator is optional:
```
void f(int);
void (*p1)(int) = &f;
void (*p2)(int) = f; // same as &f
```

That means when being used in context requiring a function pointer, function (except for non-static member function) would convert to function pointer implicitly, and the usage of `operator&` is optional.

