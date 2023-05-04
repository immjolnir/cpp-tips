/*
$ clang++ -O -g -fsanitize=address global-out-of-bounds.cc
$ ./a.out
=================================================================
==25829==ERROR: AddressSanitizer: global-buffer-overflow on address 0x55ee536cacf4 at pc
0x55ee5369354c bp 0x7fffb050d010 sp 0x7fffb050d008
*/
int global_array[100] = {-1};

int main(int argc, char** argv) {
    return global_array[argc + 100];  // BOOM
}
