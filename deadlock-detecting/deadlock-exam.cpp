
#include <chrono>
#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <thread>

std::mutex gMutex;

int Reenter() {
    std::lock_guard<std::mutex> lLock(gMutex);
    return 10;
}

int Callback() {
    std::lock_guard<std::mutex> lLock(gMutex);
    return Reenter();
}

int main(int argc, char** argv) {
    // Prints hello message...
    std::cout << "Hello CMake World!" << std::endl;
    std::thread lThread(Callback);
    lThread.join();
    std::cout << "sub thread is gone!" << std::endl;
    return 0;
}
