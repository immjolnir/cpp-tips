
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

std::recursive_mutex mtx;

int main() {
  int loopFor = 5;

  for (int i = 0; i <= loopFor; i++) {
    mtx.lock();
    cout << "Lock N°" << i << endl;
  }

  for (int i = 0; i <= loopFor; i++) {
    mtx.unlock();
    cout << "Unlock N°" << i << endl;
  }
  return 0;
}
