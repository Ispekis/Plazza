/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Process
*/

#ifndef PROCESS_HPP_
#define PROCESS_HPP_

#include "Error.hpp"
#include "signal.h"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>

class Process {
    public:
        Process();
        pid_t spawnChildProcess();
        ~Process();

    protected:
    private:
        pid_t _pid;
};

#endif /* !PROCESS_HPP_ */
