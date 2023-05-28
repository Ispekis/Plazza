/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

Plazza::Kitchen::Kitchen(float mutiplier, int nbCooks, int time, int pid) : _workDuration(5), _threadPool(nbCooks)
{
    std::cout << GREEN << "--- Start Kitchen " << getpid() << COLOR << std::endl;
    _ingredient = std::make_shared<Ingredient>(time);
    _mutiplier = mutiplier;
    _nbCooks = nbCooks;
    _orderCapacity = _nbCooks * 2;
    _orderCapacityMax = _orderCapacity;
    _orderMsgQ.createIpc(ftok(".", ORDER_KEY));
    _closureMsgQ.createIpc(ftok(".", CLOSURE_KEY));
    _capacityMsgQ.createIpc(ftok(".", CAPACITY_KEY));
    _receptionPid = pid;
    run();
}

Plazza::Kitchen::~Kitchen()
{
    _orderThread.join();
    _capacityThread.join();
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
    _closureMsgQ.push(data, _receptionPid);
}

void Plazza::Kitchen::getOrderThread()
{
    while (_isRunning) {
        std::unique_ptr<msg_data> data = _orderMsgQ.pop(getpid(), 0);
        if (data != nullptr)
        {
            Plazza::Order order;
            *data >> order;
            receiveOrder(order);
        }
    }
}

void Plazza::Kitchen::getCapacityThread()
{
    while (_isRunning) {
        std::unique_ptr<capacity_data> capacity = _capacityMsgQ.pop(getpid(), 0);
        // Check kitchen have received a message
        if (capacity != nullptr) {
            capacity_data data;
            std::memset(&data, sizeof(data), 0);
            data.value = _orderCapacity;
            _capacityMsgQ.push(data, _receptionPid);
        }
    }
}

void Plazza::Kitchen::kitchenLoop()
{
    _start = std::chrono::steady_clock::now();
    while (_isRunning) {
        // _ingredient->refillIngredient();
        if (timeOut())
            break;
    }
}

static void orderReadyMessage(Plazza::Order order)
{
    std::cout << "[Cook] : The " << order.getPizza()->getName() << " " << order.getSize() << " is ready !";
}

void Plazza::Kitchen::cookPizzas(Plazza::Order order)
{
    size_t bakeTime = order.getPizza()->getBakeTime() * _mutiplier;
    std::this_thread::sleep_for(std::chrono::milliseconds(bakeTime * 1000));

    // Send pizza back to reception
    orderReadyMessage(order);
    msg_data data;
    data << order;
    _orderMsgQ.push(data, _receptionPid);
    _orderCapacity++;
}

void Plazza::Kitchen::run()
{
    _orderThread = std::thread(&Plazza::Kitchen::getOrderThread, std::ref(*this));
    _capacityThread = std::thread(&Plazza::Kitchen::getCapacityThread, std::ref(*this));
    kitchenLoop();
}

void Plazza::Kitchen::receiveOrder(Plazza::Order order)
{
    int totalOrder = order.getAmount();
    order.setAmount(1);
    for (int i = 0; i < totalOrder; i++) {
        _threadPool.enqueue([=] {cookPizzas(order);});
        _orderCapacity--;
    }
}