#include <cstdio>

int main() {
#ifdef __SANITIZE_ADDRESS__
    printf("Address sanitizer enabled");
#else
    printf("Address sanitizer not enabled");
#endif
    return 1;
}
