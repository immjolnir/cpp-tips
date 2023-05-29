# Issues

## fatal error: 'array' file not found when `#include <array>`
* Get the GCC Installation Path

Use: `$ clang++ -E -x c++ - -v` or `$ clang++ -v`. Below is my case:
```
$ clang++ -E -x c++ - -v
Ubuntu clang version 14.0.0-1ubuntu1
...
#include "..." search starts here:
#include <...> search starts here:
 /usr/bin/../lib/gcc/x86_64-linux-gnu/12/../../../../include/c++
 /usr/lib/llvm-14/lib/clang/14.0.0/include
 /usr/local/include
 /usr/include/x86_64-linux-gnu
 /usr/include
```

We get the line: `Selected GCC installation: /usr/bin/../lib/gcc/x86_64-linux-gnu/12` but only `g++-11` is installed.

* Solution:
```
$ sudo apt install g++-12
Reading package lists... Done
Building dependency tree... Done
Reading state information... Done
The following additional packages will be installed:
  libstdc++-12-dev
Suggested packages:
  g++-12-multilib gcc-12-doc libstdc++-12-doc
The following NEW packages will be installed:
  g++-12 libstdc++-12-dev
```

* Rerun it
```
$ clang++ -E -x c++ - -v
...
include "..." search starts here:
#include <...> search starts here:
 /usr/bin/../lib/gcc/x86_64-linux-gnu/12/../../../../include/c++/12
 /usr/bin/../lib/gcc/x86_64-linux-gnu/12/../../../../include/x86_64-linux-gnu/c++/12
 /usr/bin/../lib/gcc/x86_64-linux-gnu/12/../../../../include/c++/12/backward
 /usr/lib/llvm-14/lib/clang/14.0.0/include
 /usr/local/include
 /usr/include/x86_64-linux-gnu
 /usr/include
```


## How to fix GCC error: invalid use of incomplete type ‘class …’?
* Problem:
You are compiling a C/C++ program using GCC. You get an error message similar to this:
```
error: invalid use of incomplete type ‘class SomeType’
```

* Solution:
There are multiple possible issues, but in general this error means that GCC can’t find the full declaration of the given class or struct.

The most common issue is that you are missing an `#include` clause. Find out in which header file the declaration resides, i.e. if the error message mentions class Map, look for something like
```
class Map {
   // ...
};
```

Usually the classes reside in header files that are similar to their name, e.g. `MyClass` might reside in a header file that is called `MyClass.h`, `MyClass.hpp` or` MyClass.hxx`, so be sure to look for those files first. 

Note that you might also be looking for a type from a library.
Often the best approach is to google C++ <insert the missing type here> to find out where it might be located.

Another possible reason is that you have your `#include` clause after the line where the error occurs. If this is the case, ensure that all required types are included before they are used.


