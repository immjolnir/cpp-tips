# [What's the effect of extern "C" in c++?](https://stackoverflow.com/questions/1041866/what-is-the-effect-of-extern-c-in-c)
What exactly does putting extern "C" into C++ code do?

For example:
```c++
extern "C" {
   void foo();
}
```

`extern "C"` makes a function-name in C++ have C linkage (compiler does not mangle the name) so that client C code can link to (use) your function using a C compatible header file that contains just the declaration of your function. Your function definition is contained in a binary format (that was compiled by your C++ compiler) that the client C linker will then link to using the C name.

Since C++ has overloading of function names and C does not, the C++ compiler cannot just use the function name as a unique id to link to, so it mangles the name by adding information about the arguments. A C compiler does not need to mangle the name since you can not overload function names in C. When you state that a function has `extern "C"` linkage in C++, the C++ compiler does not add argument/parameter type information to the name used for linkage.

Just so you know, you can specify `extern "C"` linkage to each individual declaration/definition explicitly or use a block to group a sequence of declarations/definitions to have a certain linkage:
```c++
extern "C" void foo(int);
extern "C"
{
   void g(char);
   int i;
}
```
If you care about the technicalities, they are listed in section 7.5 of the C++03 standard, here is a brief summary (with emphasis on `extern "C"`):

* `extern "C"` is a linkage-specification

* Every compiler is required to provide "C" linkage

* A linkage specification shall occur only in namespace scope

* Only function names and variable names with external linkage have a language linkage

* Two function types with distinct language linkages are distinct types even if otherwise identical

* Linkage specs nest, inner one determines the final linkage

* `extern "C"` is ignored for class members

* At most one function with a particular name can have "C" linkage (regardless of namespace)


## extern-c.cpp
Decompile a g++ generated binary to see what is going on

```
$ g++ -std=c++11 -Wall -Wextra -pedantic -c extern-c.cpp 
```

Compile and disassemble the generated ELF output:

```
$ readelf -s extern-c.o 

Symbol table '.symtab' contains 8 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS extern-c.cpp
     2: 0000000000000000     0 SECTION LOCAL  DEFAULT    1 .text
     3: 0000000000000000    11 FUNC    GLOBAL DEFAULT    1 _Z1fv
     4: 000000000000000b    11 FUNC    GLOBAL DEFAULT    1 ef
     5: 0000000000000016    21 FUNC    GLOBAL DEFAULT    1 _Z1hv
     6: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND _Z1gv
     7: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND eg
```

* Interpretation

We see that: `ef` and `eg` were stored in symbols with the same name as in the code.

the other symbols were mangled. Let's unmangle them:
```
$ c++filt _Z1fv
f()
$ c++filt _Z1hv
h()
$ c++filt _Z1gv
g()
```

* Conclusion: both of the following symbol types were not mangled:
    * defined
    * declared but undefined (Ndx = UND), to be provided at link or run time from another object file

