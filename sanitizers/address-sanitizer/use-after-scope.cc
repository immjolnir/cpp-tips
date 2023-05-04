// RUN: clang -O -g -fsanitize=address -fsanitize-address-use-after-scope \
//    use-after-scope.cpp -o /tmp/use-after-scope
// RUN: /tmp/use-after-scope

// Check can be disabled in run-time:
// RUN: ASAN_OPTIONS=detect_stack_use_after_scope=0 /tmp/use-after-scope

/*
$ clang++ -O -g -fsanitize=address use-after-scope.cc
$ ./a.out
=================================================================
==26355==ERROR: AddressSanitizer: stack-use-after-scope on address 0x7ffe80ce95a0 at pc
0x56047f20d62e bp 0x7ffe80ce9570 sp 0x7ffe80ce9568
...
HINT: this may be a false positive if your program uses some custom stack unwind mechanism, swapcontext or vfork
      (longjmp and C++ exceptions *are* supported)
*/

volatile int* p = 0;

int main() {
    {
        int x = 0;
        p = &x;
    }
    *p = 5;
    return 0;
}
