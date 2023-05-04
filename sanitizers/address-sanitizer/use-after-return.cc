// By default, AddressSanitizer does not try to detect
// stack-use-after-return bugs.
// It may still find such bugs occasionally
// and report them as a hard-to-explain stack-buffer-overflow.

// You need to run the test with ASAN_OPTIONS=detect_stack_use_after_return=1
/*
$ clang++ -O -g -fsanitize=address use-after-return.cc
$ ASAN_OPTIONS=detect_stack_use_after_return=1 ./a.out
=================================================================
==26077==ERROR: AddressSanitizer: stack-use-after-return on address 0x7fad15700024 at pc
0x55b8490d26dc bp 0x7fffa271f450 sp 0x7fffa271f448
*/

int* ptr;
__attribute__((noinline)) void FunctionThatEscapesLocalObject() {
    int local[100];
    ptr = &local[0];
}

int main(int argc, char** argv) {
    FunctionThatEscapesLocalObject();
    return ptr[argc];
}
