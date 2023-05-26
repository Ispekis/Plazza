/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

Plazza::Kitchen::Kitchen(float mutiplier, int nbCooks, int time, int pid) : _workDuration(5), _rPid(pid)
{
    std::cout << "Kitchen start with pid:" << getpid() << std::endl;
    _order = std::make_shared<SafeQueue<Plazza::Order>>();
    _ingredient = std::make_shared<Ingredient>(time);
    _mutiplier = mutiplier;
    _nbCooks = nbCooks;
    availableCooks = _nbCooks;
    _orderCapacity = _nbCooks * 2;
    // for (int i = 0; i < _nbCooks; i++) {
    //     _cooks.push_back(Plazza::Cook(_ingredient, _order));
    // }
    // std::cout << _msgQueue.recvOrder(getpid()).getPizza().get()->getName() << std::endl;
    run();
}

Plazza::Kitchen::~Kitchen()
{
    // Envoie messageuene Pour retirer le pid kitchen dans le queue
    _msgQueue.sendClosure(getpid(), _rPid);
    std::cout << "Kitchen closed" << std::endl;
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
}

void Plazza::Kitchen::run()
{
    kitchenLoop();
}

void Plazza::Kitchen::receiveOrder(std::vector<Plazza::Order> orderList)
{
    while (_orderCapacity != 0) {
        if (!orderList.empty()) {
            _order->push(orderList.front());
            orderList.erase(orderList.begin());
            _orderCapacity--;
            std::cout << orderList.front().getPizza().get()->getName() << "Added into Kitchen queue" << std::endl;
        } else
            break;
    }
}

bool Plazza::Kitchen::isStaturated()
{
    if (_orderCapacity == 0)
        return true;
    return false;
}