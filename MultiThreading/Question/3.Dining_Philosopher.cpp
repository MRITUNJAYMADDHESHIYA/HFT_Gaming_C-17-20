#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

const int N = 5;
mutex chopsticks[N];

void philosopher(int id) {
    int left = id;
    int right = (id + 1) % N;

    while (true) {
        cout << "Philosopher " << id << " is thinking..." << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));

        // Deadlock avoidance: always pick lower-numbered chopstick first
        if (id % 2 == 0) {
            chopsticks[left].lock();
            chopsticks[right].lock();
        } else {
            chopsticks[right].lock();
            chopsticks[left].lock();
        }

        cout << "Philosopher " << id << " is eating..." << endl;
        this_thread::sleep_for(chrono::milliseconds(1500));

        chopsticks[left].unlock();
        chopsticks[right].unlock();
    }
}

int main() {
    vector<thread> philosophers;
    for (int i = 0; i < N; ++i) {
        philosophers.emplace_back(philosopher, i);
    }

    for (auto& t : philosophers) {
        t.join();
    }

    return 0;
}
