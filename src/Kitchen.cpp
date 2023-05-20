/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

Plazza::Kitchen::Kitchen() : _workDuration(5)
{
}

Plazza::Kitchen::~Kitchen()
{
}

void Plazza::Kitchen::run()
{
    pid_t pid = fork();
    if (pid == -1) {
        throw Error("Failed to fork", "fork");
    }

    if (pid == 0) { // Child
        auto start =  std::chrono::steady_clock::now();
        std::cout << "Kitchen start" << std::endl;
        while (true) {
            auto current =  std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(current - start);
            // std::cout << "child" << std::endl;
            if (elapsed >= _workDuration) {
                std::cout << "Kitchen closed" << std::endl;
                break;
            }
        }
    } else { //Parent
        std::cout << "from parent" << std::endl;
    }
}