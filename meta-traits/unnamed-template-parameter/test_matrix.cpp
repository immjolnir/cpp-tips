#include "matrix.h"

#include <iostream>

int main() {
    Matrix<int> m(3, 5);
    std::cout << m.rows() << ", " << m.cols() << std::endl;
}