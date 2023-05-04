/*
$ clang++ -O -g -fsanitize=address stack-out-of-bounds.cc
$ ./a.out
=================================================================
==25626==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7ffe6246fcd4 at pc
0x5649c35d86fd bp 0x7ffe6246fb10 sp 0x7ffe6246fb08
*/

int main(int argc, char** argv) {
    int stack_array[100];
    stack_array[1] = 0;
    return stack_array[argc + 100];  // BOOM
}
