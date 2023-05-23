#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class MyClass {
public:
    void threadFunction() {
        std::unique_lock<std::mutex> lock(mutex);
        while (!stop) {
            // Perform thread work
            std::cout << "Thread is running!" << std::endl;
            // Wait until notified or stop is true
            conditionVariable.wait(lock, [this] { return stop; });
        }
    }

    void startThread() {
        stop = false;
        _thread = std::thread(&MyClass::threadFunction, this);
    }

    void stopThread() {
        // {
        //     std::lock_guard<std::mutex> lock(mutex);
        //     stop = true;
        // }
        // conditionVariable.notify_one();
        if (_thread.joinable()) {
            _thread.join();
        }
        std::cout << "joined" << std::endl;
    }

    void setStopFlag() {
        {
            std::lock_guard<std::mutex> lock(mutex);
            stop = true;
        }
        conditionVariable.notify_one();
    }

private:
    std::thread _thread;
    bool stop;
    std::mutex mutex;
    std::condition_variable conditionVariable;
};

int main() {
    MyClass myObject;
    MyClass myObject1;
    myObject.startThread();
    myObject1.startThread();

    // Simulate some work
    std::this_thread::sleep_for(std::chrono::seconds(2));

    myObject.setStopFlag();
    myObject.stopThread();
    myObject1.stopThread();

    return 0;
}