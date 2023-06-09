#include <future>
#include <iostream>

int find_the_answer_to_ltuae();
void do_other_stuff();

int main() {
    std::future<int> the_anwer = std::async(find_the_answer_to_ltuae);
    do_other_stuff();
    // get will block the current thread unitl std::future returns.
    std::cout << "The answer is " << the_answer.get() << std::endl;
}
