#include "service.h"
#include "v2/student.h"

#include <iostream>

int main() {
    Student scott;
    scott.update("Scott", 1, 70.0);
    scott.upgrade();
    std::cout << scott << std::endl;

    Service service;
    service.music();
}
