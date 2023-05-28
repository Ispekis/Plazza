/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Process
*/

#include "Error.hpp"
#include "signal.h"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>

#ifndef PROCESS_HPP_
#define PROCESS_HPP_

class Process {
    public:
        Process();
        pid_t spawnChildProcess();
        ~Process();
        static int getpid() {
            return ::getpid();
        };

    protected:
    private:
};

#endif /* !PROCESS_HPP_ */
