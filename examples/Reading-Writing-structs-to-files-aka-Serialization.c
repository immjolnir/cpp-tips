/*
 * Reading/Writing structs to files (aka Serialization)
 * https://www.youtube.com/watch?v=QrKpqdBiFRI
 *
 * */

// * https://en.cppreference.com/w/c/io/fopen
// * https://en.cppreference.com/w/c/io/fprintf
// As with all bounds-checked functions, fopen_s only guaranteed to be available if __STDC_LIB_EXT1__ is defined by the
// implementation and if the user defines __STDC_WANT_LIB_EXT1__ to the integer constant 1 before including <stdio.h>.
// But the gcc -std=c11 sitll not be supported on ubuntu
// #define __STDC_LIB_EXT1__ 1
// #define __STDC_WANT_LIB_EXT1__ 1

// $ clang -std=c11 -static Reading-Writing-structs-to-files-aka-Serialization.c

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* PERSON_FORMAT_IN = "(%[^,], %d, %c)\n";
const char* PERSON_FORMAT_OUT = "(%s, %d, %c)\n";
// TODO: json format

typedef struct Person {
    char name[20];
    int age;
    char gender;
} Person;

int main() {
    const Person p1 = {.name = "Andrew", .age = 20, .gender = 'M'};

    Person p2;
    FILE* file = fopen("person.data", "w+");
    // FILE *file;
    // errno_t err = fopen_s(&file, "person.data", "w+");
    if (!file) {
        return 1;
    }

    /**
     * https://gcc.gnu.org/bugzilla/show_bug.cgi?id=65999
     * Also note the _s functions are an optional part of C11 and are not required.
     * And nothing is returned by the commands below:
     * grep fopen_s -r *
     * grep __STDC_LIB_EXT1__ -r *
     * in glibc-2.35 source code.
     *
    fprintf_s(file, PERSON_FORMAT_OUT, p1.name, p1.age, p1.gender);
    fseek(file, 0, SEEK_SET);
    fscanf_s(file, PERSON_FORMAT_IN, p2.name, 20, &p2.age, &p1.gender);
    */
    fprintf(file, PERSON_FORMAT_OUT, p1.name, p1.age, p1.gender);
    fseek(file, 0, SEEK_SET);
    fscanf(file, PERSON_FORMAT_IN, p2.name, &p2.age, &p2.gender);
    printf("name=%s, age=%d, gender=%c\n", p2.name, p2.age, p2.gender);
    return 0;
}

/*
 *
$ clang -std=C11 Reading-Writing-structs-to-files-aka-Serialization.c
error: invalid value 'C11' in '-std=C11'
note: use 'c89', 'c90', or 'iso9899:1990' for 'ISO C 1990' standard
note: use 'iso9899:199409' for 'ISO C 1990 with amendment 1' standard
note: use 'gnu89' or 'gnu90' for 'ISO C 1990 with GNU extensions' standard
note: use 'c99' or 'iso9899:1999' for 'ISO C 1999' standard
note: use 'gnu99' for 'ISO C 1999 with GNU extensions' standard
note: use 'c11' or 'iso9899:2011' for 'ISO C 2011' standard
note: use 'gnu11' for 'ISO C 2011 with GNU extensions' standard
note: use 'c17', 'iso9899:2017', 'c18', or 'iso9899:2018' for 'ISO C 2017' standard
note: use 'gnu17' or 'gnu18' for 'ISO C 2017 with GNU extensions' standard
note: use 'c2x' for 'Working Draft for ISO C2x' standard
note: use 'gnu2x' for 'Working Draft for ISO C2x with GNU extensions' standard

https://stackoverflow.com/questions/4925012/can-i-get-a-report-of-all-the-libraries-linked-when-building-my-c-executable

$ clang -std=c11 Reading-Writing-structs-to-files-aka-Serialization.c  -Wl,--verbose

https://gcc.gnu.org/onlinedocs/gcc/Link-Options.html

https://docs.oracle.com/cd/E88353_01/html/E37843/sprintf-s-3c.html
https://en.cppreference.com/w/c/io/fprintf
      //
$ clang -std=c11 Reading-Writing-structs-to-files-aka-Serialization.c -v

*/
