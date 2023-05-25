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
    _orderCapacity = _nbCooks * 2;
    for (int i = 0; i != _nbCooks + 6; i++) {
        _cooks.push_back(Plazza::Cook(_ingredient, _order));
    }
        std::cout << "End of while" << std::endl;
    int tmp[2] = {pipefd.front(), pipefd.back()};
    if (pipe(tmp) == -1) {
        throw Error("Failed to pipe", "pipe");
    }
    _start = std::chrono::steady_clock::now();
}

Plazza::Kitchen::~Kitchen()
{
    printf("kitchen destroy\n");
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

void Plazza::Kitchen::kitchenLoop()
{
    _start = std::chrono::steady_clock::now();
    while (true) {
        _ingredient->refillIngredient();
        if (timeOut())
            break;
    }
    stopCooks();
}

void Plazza::Kitchen::run()
{
    pid_t pid = fork();
    if (pid == -1)
        throw Error("Failed to fork", "fork");
    if (pid == 0) { // Child
        // std::cout << "Kitchen start" << std::endl;
        kitchenLoop();
        // std::cout << "Kitchen closed" << std::endl;
    }
    else { // Parent
        std::cout << "from parent" << std::endl;
    }
}

void Plazza::Kitchen::receiveOrder(std::vector<Plazza::Order> orderList)
{
    while (_orderCapacity != 0) {
        if (!orderList.empty()) {
            _order->push(orderList.front());
            orderList.erase(orderList.begin());
            _orderCapacity--;
            std::cout << orderList.front().getName() << "Added into Kitchen queue" << std::endl;
        } else
            break;
    }
}

void Plazza::Kitchen::stopCooks()
{
    std::cout << "Cook size before clear " << _cooks.size() << std::endl;
    _cooks.clear();
    std::cout << "Cook size after clear " << _cooks.size() << std::endl;
}

bool Plazza::Kitchen::isStaturated()
{
    if (_orderCapacity == 0)
        return true;
    return false;
}