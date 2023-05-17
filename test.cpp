#include <iostream>
#include <thread>
#include <condition_variable>

std::condition_variable cv;
std::mutex mutex;

bool ready = false;

void worker_thread() {
    std::unique_lock<std::mutex> lock(mutex);
    // Do some work...
    ready = true;
    lock.unlock();
    cv.notify_one();
}

int main() {
    std::unique_lock<std::mutex> lock(mutex);
    while (!ready) {
        cv.wait(lock);
    }
    std::cout << "Worker thread finished." << std::endl;
    return 0;
}