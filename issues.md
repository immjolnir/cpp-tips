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
