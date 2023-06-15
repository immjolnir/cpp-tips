#include "exam00.h"

int main() {
    X x0, x1;
    X::metric();  // 2, 2

    { X x2, x3; }
    X::metric();  // 4, 2
    x0.print();

    Y y0, y1, y2;
    Y::metric();  // 3, 3
}
