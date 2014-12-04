#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;

mutex mtx;

void printId() {
    mtx.lock();
    static int x = 0;
    cout << x++ << endl;
    mtx.unlock();
}

int main()
{
    for (int i=0; i<100; ++i)
        thread(printId).detach();
    
  // cout << "Hello World" << endl; 
  this_thread::sleep_for (std::chrono::seconds(1));
   
   return 0;
}