#include <iostream>
#include <thread>

class ThreadLauncher {
public:
    ThreadLauncher() : isRunning(false) {
        startThread();
    }

    ~ThreadLauncher() {
        stopThread();
    }

    void startThread() {
        if (!isRunning) {
            isRunning = true;
            thread = std::thread(&ThreadLauncher::threadFunction, this);
        }
    }

    void stopThread() {
        if (isRunning) {
            isRunning = false;
            thread.join();
        }
    }

private:
    void threadFunction() {
        while (isRunning) {
            // Perform thread tasks
            std::cout << "Thread is running!" << std::endl;
        }
    }

    std::thread thread;
    bool isRunning;
};

int main() {
    ThreadLauncher launcher;

    // Perform other operations...
    // sleep(1);
    int i = 0;
    while (i < 1000000)
        i++;
    launcher.stopThread();

    return 0;
}