// $ g++ -O -g -fsanitize=address heap-out-of-bounds.cc 
// $ ./a.out
// =================================================================
// ==25203==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x6140000001d4 at pc
// 0x559ce9758261 bp 0x7ffee158a7d0 sp 0x7ffee158a7c0

int main(int argc, char** argv) {
    int* array = new int[100];
    array[0] = 0;

    int res = array[argc + 100];  // BOOM
    delete[] array;
    return res;
}
