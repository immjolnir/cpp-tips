# Meta Traits

# Commands

* Code template
```
void bbegin();

Here are the contents we care.

void eend();
```

* Compile
```
$ clang++ xx.cpp
```

* print the ast
```
$ clang++ -Xclang -ast-print -fsyntax-only xx.cpp
```

* run example
```
clang++ -o build/blist.exe  src/driver.cpp -O0 -g -Wall -Wno-unused-parameter -Wextra -Wconversion -Wold-style-cast -std=c++14 -pedantic -Wold-style-cast
```

# Chapter 1
## 1.4.4.0.cpp

The `Wrap_<10>::value<2>` cannot reuse the specialization instances of the template: `Wrap_<3>::value<2>`.
Because they are owned by `Wrap_<3>`.

This will leads to too many instance and finally cuase Instantiate burst and compile crash.

## 1.4.4.1.cpp
It's a fix to the issue as above.

Moving the loop(template substitution) out of the `Wrap_` struct.

Better putting them under a namespace.
