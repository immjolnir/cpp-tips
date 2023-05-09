#include <iostream>
#include <memory>
#include <string>

#include "message_filters.h"

using namespace ros::message_filters;

int main() {
    typedef int PivotalType;
    auto filter0 = std::make_shared<Filter<PivotalType, int>>();
    auto filter1 = std::make_shared<Filter<PivotalType, float>>();

    Message<PivotalType, 2> message(filter0, filter1);

    filter0->addPivot(2001, 1);
    filter1->addPivot(2001, 2);

    filter0->addMessage(1, 100);
    filter1->addMessage(2, 100.1);

    auto v0 = filter0->getMessage();
    auto v1 = filter1->getMessage();
    std::cout << "v0=" << v0 << ", v1=" << v1 << std::endl;
}