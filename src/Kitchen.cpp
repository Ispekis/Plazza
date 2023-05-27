/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

Plazza::Kitchen::Kitchen(float mutiplier, int nbCooks, int time, int pid) : _workDuration(5)
{
    std::cout << GREEN << "--- Start Kitchen " << getpid() << COLOR << std::endl;
    _ingredient = std::make_shared<Ingredient>(time);
    _mutiplier = mutiplier;
    _nbCooks = nbCooks;
    _orderCapacity = _nbCooks * 2;
    _orderCapacityMax = _orderCapacity;
    _orderKey = ftok(".", ORDER_KEY);
    _closureKey = ftok(".", CLOSURE_KEY);
    _capacityKey = ftok(".", CAPACITY_KEY);
    _receptionPid = pid;
    run();
}

Plazza::Kitchen::~Kitchen()
{
    closeKitchen();
    // std::cout << "--- Close Kitchen:" << getpid() << std::endl;
}

bool Plazza::Kitchen::timeOut()
{
    auto current =  std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(current - _start);

    if (_orderCapacity != _orderCapacityMax)
        _start = current;
    if (elapsed >= _workDuration)
        return true;
    return false;
}

void Plazza::Kitchen::closeKitchen()
{
    closure_data data;
    std::memset(&data, sizeof(data), 0);

    data.id = getpid();
    _closureMsgQ.push(data, _receptionPid, _closureKey);
}

void Plazza::Kitchen::messageQueueReception()
{
    std::unique_ptr<msg_data> data = _orderMsgQ.pop(getpid(), _orderKey);
    std::unique_ptr<capacity_data> capacity = _capacityMsgQ.pop(getpid(), _capacityKey);
    // Check kitchen have received a message
    if (data != nullptr)
    {
        // TODO : replace
        // std::cout << "--- Kitchen " << getpid() << ": Pizza received" << std::endl;
        receiveOrder(Plazza::Order(static_cast<Plazza::PizzaType>(data->type), static_cast<Plazza::PizzaSize>(data->size), data->nbr));
    }
    if (capacity != nullptr) {
        capacity_data data;
        std::memset(&data, sizeof(data), 0);
        data.value = _orderCapacity;
        _capacityMsgQ.push(data, _receptionPid, _capacityKey);
    }
}

void Plazza::Kitchen::kitchenLoop()
{
    _start = std::chrono::steady_clock::now();
    while (true) {
        messageQueueReception();
        _ingredient->refillIngredient();
        if (timeOut())
            break;
    }
}

void Plazza::Kitchen::run()
{
    kitchenLoop();
}

void Plazza::Kitchen::receiveOrder(Plazza::Order order)
{
    for (int i = 0; i < order.getAmount(); i++) {
        _order.push(order);
        _orderCapacity--;
    }
}