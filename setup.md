# cpp-tips

* Options: [cppinsights](https://cppinsights.io/) and clang


## clang setup
* [Reducing Template Compilation Overhead, Using C++11, 14](https://www.youtube.com/watch?v=TyiiNVA1syk)


```
apt install clang clang-tidy clang-tools clang-format cppcheck doxygen graphviz
```
* libgtest-dev
* libgoogle-glog-dev

* cppcheck
```
Description: tool for static C/C++ code analysis (CLI)
 Cppcheck is a command-line tool that tries to detect bugs that your
 C/C++ compiler doesn't see. It is versatile, and can check non-standard
 code including various compiler extensions, inline assembly code, etc.
 Its internal preprocessor can handle includes, macros, and several
 preprocessor commands. While Cppcheck is highly configurable,
 you can start using it just by giving it a path to the source code.
 .
 It includes checks for:
  * pointers to out-of-scope auto variables;
  * assignment of auto variables to an effective parameter of a function;
  * out-of-bounds errors in arrays and STL;
  * missing class constructors;
  * variables not initialized by a constructor;
  * use of memset, memcpy, etcetera on a class;
  * non-virtual destructors for base classes;
  * operator= not returning a constant reference to itself;
  * use of deprecated functions (mktemp, gets, scanf);
  * exceptions thrown in destructors;
  * memory leaks in class or function variables;
  * C-style pointer cast in C++ code;
  * redundant if;
  * misuse of the strtol or sprintf functions;
  * unsigned division or division by zero;
  * unused functions and struct members;
  * passing parameters by value;
  * misuse of signed char variables;
  * unusual pointer arithmetic (such as "abc" + 'd');
  * dereferenced null pointers;
  * incomplete statements;
  * misuse of iterators when iterating through a container;
  * dereferencing of erased iterators;
  * use of invalidated vector iterators/pointers;
 .
 This package contains the command-line interface for cppcheck.
```
* doxygen
```
Description: Documentation system for C, C++, Java, Python and other languages
 Doxygen is a documentation system for C, C++, Java, Objective-C, Python, IDL
 and to some extent PHP, C#, and D.  It can generate an on-line class browser
 (in HTML) and/or an off-line reference manual (in LaTeX) from a set of
 documented source files. There is also support for generating man pages
 and for converting the generated output into Postscript, hyperlinked PDF
 or compressed HTML.  The documentation is extracted directly from the sources.
 .
 Install the doxygen-latex package to build LaTeX based documents.
```


## [Clang-Format Style](https://clang.llvm.org/docs/ClangFormatStyleOptions.html)
* https://www.clangpowertools.com/blog/getting-started-with-clang-format-style-options.html


