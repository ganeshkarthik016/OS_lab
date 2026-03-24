#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex m1, m2;

void thread1()
{
    lock_guard<mutex> lock1(m1);
    this_thread::sleep_for(chrono::milliseconds(100));

    lock_guard<mutex> lock2(m2);

    cout << "T1 working safely\n";
}

void thread2()
{
    lock_guard<mutex> lock1(m1);
    this_thread::sleep_for(chrono::milliseconds(100));

    lock_guard<mutex> lock2(m2);

    cout << "T2 working safely\n";
}

int main()
{
    thread t1(thread1);
    thread t2(thread2);

    t1.join();
    t2.join();

    cout << "Program completed without deadlock\n";
}