#include <iostream>
#include <unistd.h> // Include for fork()

class Process {
public:
    void spawnChildProcess() {
        pid_t pid = fork();
        std::cout << pid << std::endl;
        if (pid == -1)
        {
            std::cerr << "Fork failed!" << std::endl;
            return;
        }
        else if (pid == 0)
        {
            // Child process
            std::cout << "Child process" << std::endl;
            // ... Do child process tasks ...
        }
        else
        {
            // Parent process
            std::cout << "Parent process" << std::endl;
            // ... Do parent process tasks ...
        }
    }
};

int main() {
    Process myProcess;
    myProcess.spawnChildProcess();

    return 0;
}
