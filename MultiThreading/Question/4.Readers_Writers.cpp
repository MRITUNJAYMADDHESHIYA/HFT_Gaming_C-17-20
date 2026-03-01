#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <chrono>

using namespace std;

shared_mutex rw_lock;
int data = 0;

void reader(int id) {
    while (true) {
        shared_lock<shared_mutex> lock(rw_lock);
        cout << "Reader " << id << " reads data: " << data << endl;
        this_thread::sleep_for(chrono::milliseconds(700));
    }
}

void writer(int id) {
    while (true) {
        unique_lock<shared_mutex> lock(rw_lock);
        data++;
        cout << "Writer " << id << " writes data: " << data << endl;
        this_thread::sleep_for(chrono::milliseconds(1200));
    }
}

int main() {
    thread readers[3], writers[2];

    for (int i = 0; i < 3; ++i)
        readers[i] = thread(reader, i + 1);

    for (int i = 0; i < 2; ++i)
        writers[i] = thread(writer, i + 1);

    for (int i = 0; i < 3; ++i)
        readers[i].join();

    for (int i = 0; i < 2; ++i)
        writers[i].join();

    return 0;
}
