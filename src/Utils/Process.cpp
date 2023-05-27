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
}

pid_t Process::spawnChildProcess()
{
    pid_t pid = fork();
    if (pid == -1)
        throw Error("Fork", "Failed to create Process");
    return pid;
}