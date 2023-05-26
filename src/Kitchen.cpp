/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

Plazza::Kitchen::Kitchen(float mutiplier, int nbCooks, int time, int pid) : _workDuration(5)
{
    std::cout << "Kitchen start" << std::endl;
    // _order = std::make_shared<SafeQueue<Plazza::Order>>();
    // _ingredient = std::make_shared<Ingredient>(time);
    _mutiplier = mutiplier;
    _nbCooks = nbCooks;
    availableCooks = _nbCooks;
    _orderCapacity = _nbCooks * 2;
    _orderKey = ftok(".", ORDER_KEY);
    // for (int i = 0; i < _nbCooks; i++) {
    //     _cooks.push_back(std::make_shared<Plazza::Cook>(_ingredient, _order));
    // }
    // std::cout << _msgQueue.recvOrder(getpid()).getPizza().get()->getName() << std::endl;
    kitchenLoop();
}

Plazza::Kitchen::~Kitchen()
{
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
        std::unique_ptr<msg_data> data = _orderMsgQueue.pop(getpid(), _orderKey);
        // Check kitchen have received a message
        if (data != nullptr) {
            // TODO : replace
            receiveOrder(Plazza::Order(static_cast<Plazza::PizzaType>(data->type), static_cast<Plazza::PizzaSize>(data->size), data->nbr));
        }
        // _ingredient->refillIngredient();
        if (timeOut())
            break;
    }
    stopCooks();
    std::cout << "Kitchen closed" << std::endl;
}

void Plazza::Kitchen::run()
{
}

void Plazza::Kitchen::receiveOrder(Plazza::Order order)
{
    // if (_pid != 0) {
        // for (auto &cook : _cooks) {
        //     while (!cook.isOverwhelmed()) {
        //         if (!orderList.empty()) {
        //             cook.addOrder(orderList.front());
        //             orderList.erase(orderList.begin());
        //             std::cout << orderList.front().getName() << " receive" << std::endl;
        //         } else
        //             break;
        //     }
        // }
    // }
    for (int i = 0; i < order.getAmount(); i++) {
        order.setAmount(1);
        _order.push(order);
    }
    // while (_orderCapacity != 0) {
    //     if (!orderList.empty()) {
    //         _order.push(orderList.front());
    //         orderList.erase(orderList.begin());
    //         _orderCapacity--;
    //         std::cout << orderList.front().getPizza()->getName() << "Added into Kitchen queue" << std::endl;
    //     } else
    //         break;
    // }
}

void Plazza::Kitchen::stopCooks()
{
    // for (auto &cook : _cooks) {
        // cook->stopCook();
    // }
    _cooks.clear();
}

bool Plazza::Kitchen::isStaturated()
{
    if (_orderCapacity == 0)
        return true;
    return false;
}