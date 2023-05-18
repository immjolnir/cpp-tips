/* munmap_chunk(): invalid pointer
 *
* https://stackoverflow.com/questions/32118545/munmap-chunk-invalid-pointer
*
munmap_chunk() is an internal function of the libc's memory management routine. This error message means that by writing into memory that does not belong to an object (but belongs to your process so no segfault), you corrupted internal data structures belonging to these routines. Trying to use these corrupted data structures, the internal routines crash.

free(): invalid pointer
Aborted

*/
#include <stdio.h>
#include <stdlib.h>

char * first()
{
    char * word = malloc(sizeof(char) * 10);
    word[0] = 'a';
    word[1] = 'b';
    word[2] = '\0';
    return word;
}

char * second ()
{
    char * word = malloc(sizeof(char) * 10);
    word = "ab";
    return word;
}

int main ()
{
    char * out = first();
    printf("%s", out);
    free(out);
    out = second();
    printf("%s", out);
    free(out);
    return 0;
}
