/*
https://stackoverflow.com/questions/1965487/does-the-restrict-keyword-provide-significant-benefits-in-gcc-g

In the C programming language, restrict is a keyword, introduced by the C99 standard, that can be used in pointer
declarations. By adding this type qualifier, a programmer hints to the compiler that for the lifetime of the pointer, no
other pointer will be used to access the object to which it points.

This allows the compiler to make optimizations (for example, vectorization) that would not otherwise have been possible.

restrict limits the effects of pointer aliasing, aiding optimizations. If the declaration of intent is not followed and
the object is accessed by an independent pointer, this will result in undefined behavior.
*/

#include <math.h>

#ifdef USE_RESTRICT
#else
#define __restrict
#endif

void transform(float* __restrict dest, float* __restrict src, float* __restrict matrix, int n)
  __attribute__((noinline));

void transform(float* __restrict dest, float* __restrict src, float* __restrict matrix, int n) {
    int i;

    // simple transform loop.

    // written with aliasing in mind. dest, src and matrix
    // are potentially aliasing, so the compiler is forced to reload
    // the values of matrix and src for each iteration.

    for (i = 0; i < n; i++) {
        dest[0] = src[0] * matrix[0] + src[1] * matrix[1] + src[2] * matrix[2] + src[3] * matrix[3];

        dest[1] = src[0] * matrix[4] + src[1] * matrix[5] + src[2] * matrix[6] + src[3] * matrix[7];

        dest[2] = src[0] * matrix[8] + src[1] * matrix[9] + src[2] * matrix[10] + src[3] * matrix[11];

        dest[3] = src[0] * matrix[12] + src[1] * matrix[13] + src[2] * matrix[14] + src[3] * matrix[15];

        src += 4;
        dest += 4;
    }
}

float srcdata[4 * 10000];
float dstdata[4 * 10000];

int main(int argc, char** args) {
    int i, j;
    float matrix[16];

    // init all source-data, so we don't get NANs
    for (i = 0; i < 16; i++) matrix[i] = 1;
    for (i = 0; i < 4 * 10000; i++) srcdata[i] = i;

    // do a bunch of tests for benchmarking.
    for (j = 0; j < 10000; j++) transform(dstdata, srcdata, matrix, 10000);
}

/*
$ gcc -O3 restrict.c
$ ./a.out
$ time ./a.out

real	0m0.128s
user	0m0.128s
sys	    0m0.000s

$ gcc -O3 -DUSE_RESTRICT restrict.c
$ time ./a.out

real	0m0.110s
user	0m0.110s
sys	    0m0.000s

*/
