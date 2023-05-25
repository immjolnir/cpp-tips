#include "service.h"
#include "v1/student.h"

#include <iostream>

void Service::music() {
    Student student;
    student.update(1, 100);
    std::cout << student << std::endl;

    student.upgrade();
    std::cout << "Upgrade successfully.\n" << student << std::endl;
}
