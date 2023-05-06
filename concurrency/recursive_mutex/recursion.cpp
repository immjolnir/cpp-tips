#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

std::recursive_mutex mtx;
int buffer = 0;

void recursion(char c, int loopFor) {
  if (loopFor < 0) {
    return;
  }

  mtx.lock();
  cout << "Thread " << c << ": " << buffer++ << endl;
  recursion(c, --loopFor);
  mtx.unlock();
  cout << "Unlock by thread " << c << endl;
}

int main() {
  thread t1(recursion, '1', 10);
  thread t2(recursion, '2', 10);
  t1.join();
  t2.join();
  return 0;
}
/*
 * 在同一个线程里递归地调用.因为它在同一个线程里，只能顺序执行，所以是安全的。
 */
