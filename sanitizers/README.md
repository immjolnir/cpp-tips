
# [sanitizers](https://github.com/google/sanitizers)

The documentation for our tools:

* AddressSanitizer (detects addressability issues) and LeakSanitizer (detects memory leaks)

* ThreadSanitizer (detects data races and deadlocks) for C++ and Go

* MemorySanitizer (detects use of uninitialized memory)

* HWASAN, or Hardware-assisted AddressSanitizer, a newer variant of AddressSanitizer that consumes much less memory

* UBSan, or UndefinedBehaviorSanitizer

## [AddressSanitizer](https://github.com/google/sanitizers/wiki/AddressSanitizer) 

AddressSanitizer (aka ASan) is a memory error detector for C/C++.

AddressSanitizer is a part of __LLVM__ and __GCC__.

In order to use AddressSanitizer you will need to compile and link your program using clang with the `-fsanitize=address` switch. To get a reasonable performance add `-O1` or higher. To get nicer stack traces in error messages add `-fno-omit-frame-pointer`. 

* g++
```
$ g++ -std=c++14 -g -O1 sanitizer-checker.cc && ./a.out 
Address sanitizer not enabled

$ g++ -std=c++14 -fsanitize=address -g -O1 sanitizer-checker.cc && ./a.out 
Address sanitizer enabled
```

* clang++
```
$ clang++ -std=c++14 -g -O1 sanitizer-checker.cc && ./a.out 
Address sanitizer not enabled

$ clang++ -std=c++14 -fsanitize=address -g -O1  sanitizer-checker.cc && ./a.out 
Address sanitizer not enabled
```
It just proved that the clang++ doesn't have the `__SANITIZE_ADDRESS__`.

* use-after-free-dangling-pointer-dereference.cc

* heap-out-of-bounds.cc

* stack-out-of-bounds.cc

* global-out-of-bounds.cc

* use-after-return.cc

### use-after-scope.cc

### init-order

__Static initialization order fiasco__ is a common issue in C++ programs relating to the order in which global objects are constructed. The order in which constructors for global objects in different source files run is unspecified.

Here the value if x depends on the value of extern_global, which may or may not be initialized with "42" depending on the order in which the initializers for translation units run:
```
$ clang++ a.cc b.cc && ./a.out 
1

$ clang++ b.cc a.cc && ./a.out 
43
```

Such bugs are hard to spot and may stay unnoticed until some irrelevant changes in the code (or compiler, or link strategy) change the code behavior, often breaking it in an unexpected way.

#### Loose init-order checking
This mode reports an error if initializer for a global variable accesses dynamically initialized global from another translation unit, which is not yet initialized. Use `check_initialization_order=true` to activate it:

```
$ clang++ -fsanitize=address -g a.cc b.cc && ASAN_OPTIONS=check_initialization_order=true ./a.out 
=================================================================
==28457==ERROR: AddressSanitizer: initialization-order-fiasco on address 0x5615df21e9a0 at pc 0x5615de81365a bp 0x7fff13c47fc0 sp 0x7fff13c47fb8
```

In some sense, this mode reports existing problems. It may not report an error if the order of initialization changes:
```
$ clang++ -fsanitize=address -g b.cc a.cc && ASAN_OPTIONS=check_initialization_order=true ./a.out 
43
```
#### Strict init-order checking
* refers: http://www.parashift.com/c++-faq/static-init-order.html

This mode reports an error if initializer for a global variable accesses any dynamically initialized global from another translation unit. Use additional variable  `strict_init_order=true` to activate it:
```
$ clang++ -fsanitize=address -g a.cc b.cc && ASAN_OPTIONS=check_initialization_order=true:strict_init_order=true ./a.out 
=================================================================
==28696==ERROR: AddressSanitizer: initialization-order-fiasco on address 0x5636428909a0 at pc 0x563641e8565a bp 0x7ffe8a866280 sp 0x7ffe8a866278
```
In this way you may also find potential initialization-order problems after changing its order.

```
$ clang++ -fsanitize=address -g b.cc a.cc && ASAN_OPTIONS=check_initialization_order=true:strict_init_order=true ./a.out 
=================================================================
==28711==ERROR: AddressSanitizer: initialization-order-fiasco on address 0x555bfd369980 at pc 0x555bfc95e6ba bp 0x7ffdd2b74470 sp 0x7ffdd2b74468
```

#### False positives
strict init-order checking may report false positives when the access to already-initialized globals from another translation units is expected, or when the specific order of construction is enforced by, e.g. using shared libraries.
loose init-order checking may report false positives on dynamically initialized globals, which can still be safely accessed before initialization (e.g. if their constructor does nothing).

#### Ignorelist
You may suppress false positives of init-order checker on certain global variables by using the `-fsanitize-ignorelist=path/to/ignorelist.txt` option. Relevant ignorelist entries are:
```
# Disable init-order checking for a single variable:
global:bad_variable=init

# Disable checking for all variables of a given type:
type:Namespace::ClassName=init

# Disable checking for all variables in given files:
src:path/to/bad/files/*=init
```

### memory-leak.c
```
$ clang -fsanitize=address -g memory-leak.c 
$ ./a.out 

=================================================================
==29250==ERROR: LeakSanitizer: detected memory leaks
```

LeakSanitizer is enabled by default in ASan builds of x86_64 Linux, and can be enabled with `ASAN_OPTIONS=detect_leaks=1` on x86_64 OS X. 
If you want to run an ASan-instrumented program without leak detection, you can pass `detect_leaks=0` in the `ASAN_OPTIONS` environment variable.

#### Stand-alone mode
If you just need leak detection, and don't want to bear the ASan slowdown, you can build with `-fsanitize=leak` instead of `-fsanitize=address`. This will link your program against a runtime library containing just the bare necessities required for LeakSanitizer to work. No compile-time instrumentation will be applied.


## [MemorySanitizer](https://github.com/google/sanitizers/wiki/MemorySanitizer)
MemorySanitizer (MSan) is a detector of uninitialized memory reads in C/C++ programs.

Uninitialized values occur when stack- or heap-allocated memory is read before it is written. MSan detects cases where such values affect program execution.

MSan is bit-exact: it can track uninitialized bits in a bitfield. It will tolerate copying of uninitialized memory, and also simple logic and arithmetic operations with it. In general, MSan silently tracks the spread of uninitialized data in memory, and reports a warning when a code branch is taken (or not taken) depending on an uninitialized value.

```
$ clang++ -fsanitize=memory -fPIE -pie -fno-omit-frame-pointer -g -O2 uninitialized-memory-read.cc  && ./a.out 
==30931==WARNING: MemorySanitizer: use-of-uninitialized-value
```

### Origins tracking
MemorySanitizer can track back each uninitialized value to the memory allocation where it was created, and use this information in reports. This behaviour is enabled with the -fsanitize-memory-track-origins flag. It comes with additional 1.5x-2.5x slowdown, and makes the report from the previous example look like this:
```
$ clang++ -fsanitize=memory -fsanitize-memory-track-origins -fPIE -pie -fno-omit-frame-pointer -g -O2 uninitialized-memory-read.cc  && ./a.out 
==31058==WARNING: MemorySanitizer: use-of-uninitialized-value
    #0 0x556116ed2491 in main /home/zhishan/iwork/cpp-tips/sanitizers/memory-sanitizer/uninitialized-memory-read.cc:6:9
    #1 0x7fafa9536d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
    #2 0x7fafa9536e3f in __libc_start_main csu/../csu/libc-start.c:392:3
    #3 0x556116e4a2a4 in _start (/home/zhishan/iwork/cpp-tips/sanitizers/memory-sanitizer/a.out+0x1e2a4) (BuildId: dbf4b332e711d72e32eb24deb18b03564d5e2821)

  Uninitialized value was created by a heap allocation
    #0 0x556116ed1599 in operator new[](unsigned long) (/home/zhishan/iwork/cpp-tips/sanitizers/memory-sanitizer/a.out+0xa5599) (BuildId: dbf4b332e711d72e32eb24deb18b03564d5e2821)
```
* MemorySanitizer algorithm Paper: [MemorySanitizer: fast detector of C uninitialized memory use in C++](https://static.googleusercontent.com/media/research.google.com/en//pubs/archive/43308.pdf)
## [ThreadSanitizer](https://github.com/google/sanitizers/wiki/ThreadSanitizerCppManual)

Use `g++` or `clang++`

* simple_race.cc