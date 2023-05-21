/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

Plazza::Kitchen::Kitchen(float mutiplier, int nbCooks, int time, std::array<int, 2> pipefd) : _workDuration(5), _ingredient(time)
{
    _mutiplier = mutiplier;
    _nbCooks = nbCooks;
    availableCooks = _nbCooks;
    for (int i = 0; i < _nbCooks; i++) {
        _cooks.push_back(Plazza::Cook());
    }
    int tmp[2] = {pipefd.front(), pipefd.back()};
    if (pipe(tmp) == -1) {
        throw Error("Failed to pipe", "pipe");
    }
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
            // restart the chrono
            // if () {
            //     start =  std::chrono::steady_clock::now();
            // }
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

void Plazza::Kitchen::receiveOrder(std::vector<Plazza::Order> &orderList)
{
    // if (_pid != 0) {
        for (auto cook : _cooks) {
            while (!cook.isOverwhelmed()) {
                if (!orderList.empty()) {
                    cook.addOrder(orderList.front());
                    orderList.erase(orderList.begin());
                    std::cout << "ok receive" << std::endl;
                }
            }
        }
    // }
}

bool Plazza::Kitchen::isStaturated()
{
    return false;
}