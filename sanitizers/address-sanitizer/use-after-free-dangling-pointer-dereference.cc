// $ g++ -O -g -fsanitize=address use-after-free-dangling-pointer-dereference.c
// ./a.out
// ==24667==ERROR: AddressSanitizer: heap-use-after-free on address 0x614000000044 at pc
// 0x559ee430d21f bp 0x7fff632b68f0 sp 0x7fff632b68e0

int main(int argc, char** argv) {
    int* array = new int[100];
    delete[] array;
    return array[argc];  // BOOM
}
