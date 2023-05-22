#include <iostream>
#include <thread>

class ThreadWrapper {
private:
    std::thread my_thread;

public:
    ThreadWrapper() {}

    ~ThreadWrapper() {
        if (my_thread.joinable()) {
            my_thread.join();
        }
    }

    void startThread() {
        my_thread = std::thread(&ThreadWrapper::threadFunction, this);
    }

    void joinThread() {
        if (my_thread.joinable()) {
            my_thread.join();
        }
    }

private:
    void threadFunction() {
        std::cout << "Hello from thread!" << std::endl;
    }
};

int main() {
    ThreadWrapper my_thread_wrapper;
    my_thread_wrapper.startThread();
    my_thread_wrapper.joinThread();
    
    return 0;
}