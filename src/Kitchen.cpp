/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

Plazza::Kitchen::Kitchen(float mutiplier, int nbCooks, int time, std::array<int, 2> pipefd) : _workDuration(5)
{
    _order = std::make_shared<SafeQueue<Plazza::Order>>();
    _ingredient = std::make_shared<Ingredient>(time);
    _mutiplier = mutiplier;
    _nbCooks = nbCooks;
    availableCooks = _nbCooks;
    for (int i = 0; i < _nbCooks; i++) {
        _cooks.push_back(Plazza::Cook(_ingredient, _order));
    }
    int tmp[2] = {pipefd.front(), pipefd.back()};
    if (pipe(tmp) == -1) {
        throw Error("Failed to pipe", "pipe");
    }
    _start = std::chrono::steady_clock::now();
}

Plazza::Kitchen::~Kitchen()
{
}

bool Plazza::Kitchen::timeOut()
{
    auto current =  std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(current - _start);
    if (elapsed >= _workDuration) {
        return true;
    }
    return false;
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
            _ingredient->refillIngredient();
            runCooks();
            if (timeOut())
                break;
        }
        for (auto &cook : _cooks) {
            cook.closeThread();
        }
        for (auto &cook : _cooks) {
            cook.endThread();
        }
        std::cout << "Kitchen closed" << std::endl;
    }
    else
    { // Parent
        // std::cout << "from parent" << std::endl;
    }
}

void Plazza::Kitchen::receiveOrder(std::vector<Plazza::Order> orderList)
{
    // if (_pid != 0) {
        for (auto &cook : _cooks) {
            while (!cook.isOverwhelmed()) {
                if (!orderList.empty()) {
                    cook.addOrder(orderList.front());
                    orderList.erase(orderList.begin());
                    std::cout << orderList.front().getName() << " receive" << std::endl;
                } else
                    break;
            }
        }
    // }
}

void Plazza::Kitchen::runCooks()
{
    for (auto &cook : _cooks) {
        if (!cook.isCooking()) {
            cook.cookPizza();
        }
    }
}

bool Plazza::Kitchen::stopCooks()
{
    for (auto &cook : _cooks) {
        if (cook.isCooking() == true)
            return false;
    }
    return true;
}

bool Plazza::Kitchen::isStaturated()
{
    return false;
}