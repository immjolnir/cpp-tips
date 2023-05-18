
# too many arguments to function ‘void f(Ts&& ...)

## exam01.cpp
* https://stackoverflow.com/questions/61058942/too-many-arguments-to-function-stdmake-sharedvector

This case is described in the C++ Standard in [temp.deduct.call/1](http://eel.is/c++draft/temp.deduct.call#1):

> Template argument deduction is done by comparing each function template parameter type (call it P) that contains template-parameters that participate in template argument deduction with the type of the corresponding argument of the call (call it A) as described below. If removing references and cv-qualifiers from P gives std::initializer_list<P′> or P′[N] for some P′ and N and the argument is a non-empty initializer list ([dcl.init.list]), then deduction is performed instead for each element of the initializer list independently, taking P′ as separate function template parameter types P′i and the ith initializer element as the corresponding argument. In the P′[N] case, if N is a non-type template parameter, N is deduced from the length of the initializer list. Otherwise, an initializer list argument causes the parameter to be considered a non-deduced context ([temp.deduct.type]).

* example 1:
```
template<class T> void f(std::initializer_list<T>);
f({1,2,3});                     // T deduced as int
f({1,"asdf"});                  // error: T deduced as both int and const char*

template<class T> void g(T);
g({1,2,3});                     // error: no argument deduced for T

```

* Example 2:

> For a function parameter pack that occurs at the end of the parameter-declaration-list, deduction is performed for each remaining argument of the call, taking the type P of the declarator-id of the function parameter pack as the corresponding function template parameter type. Each deduction deduces template arguments for subsequent positions in the template parameter packs expanded by the function parameter pack. When a function parameter pack appears in a non-deduced context ([temp.deduct.type]), the type of that pack is never deduced.
```
template<class ... Types> void f(Types& ...);
template<class T1, class ... Types> void g(T1, Types ...);
template<class T1, class ... Types> void g1(Types ..., T1);

void h(int x, float& y) {
  const int z = x;
  f(x, y, z);                   // Types deduced as int, float, const int
  g(x, y, z);                   // T1 deduced as int; Types deduced as float, int
  g1(x, y, z);                  // error: Types is not deduced
  g1<int, int, int>(x, y, z);   // OK, no deduction occurs
}
```


## exam02.cpp 
* https://stackoverflow.com/questions/71138329/stdinitializer-list-and-stdmake-shared-too-many-arguments-3-expected-0

`{1,2,3}` can be multiple things, and make_shared has no possibility of knowing what it is at the time parameter pack is expanded.
```
auto make_shared_S(int x, double y, std::initializer_list<int> l)
{
    return std::make_shared<S>(x, y, l);
}
```


