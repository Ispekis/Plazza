/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Process
*/

#include "Process.hpp"

Process::Process()
{
    
}

Process::~Process()
{
            //     if (this->_pid > 0)
            // kill(this->_pid, SIGKILL);

}

pid_t Process::spawnChildProcess()
{
    std::cout << "forked" << std::endl;
    pid_t pid = fork();
    std::cout << pid << std::endl;
    if (pid == -1)
        throw Error("Fork", "Failed to create Process");
    // _pid = std::copy(pid);
    return pid;
}