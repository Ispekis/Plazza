/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

Plazza::Kitchen::Kitchen(float mutiplier, int nbCooks, int time, int pid, std::vector<std::string> ingredients) : _threadPool(nbCooks), _workDuration(5), _factory("data/Pizza.conf")
{
    std::cout << GREEN << "--- Start Kitchen " << Process::getpid() << COLOR << std::endl;
    _ingredient = std::make_shared<Ingredient>(time, ingredients);
    _mutiplier = mutiplier;
    _nbCooks = nbCooks;
    _orderCapacity = _nbCooks * 2;
    _orderCapacityMax = _orderCapacity;
    _orderMsgQ.createIpc(IPC::ftok(".", ORDER_KEY));
    _closureMsgQ.createIpc(IPC::ftok(".", CLOSURE_KEY));
    _capacityMsgQ.createIpc(IPC::ftok(".", CAPACITY_KEY));
    _receptionPid = pid;
    run();
}

Plazza::Kitchen::~Kitchen()
{
    _orderThread.join();
    _capacityThread.join();
    // std::cout << "--- Close Kitchen:" << Process::getpid() << std::endl;
}

bool Plazza::Kitchen::timeOut()
{
    auto current = std::chrono::steady_clock::now();
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
    std::memset(&data, 0, sizeof(data));

    _isRunning = false;
    data.id = Process::getpid();
    _closureMsgQ.push(data, _receptionPid);
}

void Plazza::Kitchen::getOrderThread()
{
    while (_isRunning) {
        std::unique_ptr<msg_data> data = _orderMsgQ.pop(Process::getpid(), 0);
        if (data != nullptr)
        {
            Plazza::Order order;
            order = Plazza::Order::unpack(*data);
            receiveOrder(order);
        }
    }
}

void capacityMessage(int capacity)
{
    std::cout << "[Kitchen " << Process::getpid() << "] : I can take " << capacity << " orders !" << std::endl;
}

void Plazza::Kitchen::getCapacityThread()
{
    while (_isRunning) {
        std::unique_ptr<capacity_data> capacity = _capacityMsgQ.pop(Process::getpid(), 0);
        // Check kitchen have received a message
        if (capacity != nullptr) {
            capacityMessage(_orderCapacity);
            capacity_data data;
            std::memset(&data, 0, sizeof(data));
            data.value = _orderCapacity;
            _capacityMsgQ.push(data, _receptionPid);
        }
    }
}

void Plazza::Kitchen::kitchenLoop()
{
    _start = std::chrono::steady_clock::now();
    while (_isRunning) {
        _ingredient->refillIngredient();
        if (timeOut())
            break;
    }
    closeKitchen();
}

void Plazza::Kitchen::cookPizzas(Plazza::Order order)
{
    std::shared_ptr<Plazza::IPizza> pizza = _factory.getPizza(order.getType());
    float bakeTime = pizza->getBakeTime() * _mutiplier;
    bakeTime *= 1000;
    bool make = _ingredient->makePizza(pizza);
    if (!make) {
        std::cout << "cannot make" << std::endl;
        while (!_ingredient->checkEnoughIngredient(pizza));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(bakeTime)));

    // Send pizza back to reception
    orderReadyMessage(order);
    msg_data data;
    data = Plazza::Order::pack(order);
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
    receiveOrderMessage(order);
    int totalOrder = order.getAmount();
    order.setAmount(1);
    for (int i = 0; i < totalOrder; i++) {
        _threadPool.enqueue([=] {cookPizzas(order);});
        _orderCapacity--;
    }
}

void Plazza::Kitchen::orderReadyMessage(Plazza::Order order)
{
    std::shared_ptr<Plazza::IPizza> pizza = _factory.getPizza(order.getType());
    std::cout << "[Cook] : The " << pizza->getName() << " " << _factory.getSizeName(order.getSize()) << " is ready !" << std::endl;
}

void Plazza::Kitchen::receiveOrderMessage(Plazza::Order order)
{
    std::cout << "[Kitchen " << Process::getpid() << "] : I got " << order.getAmount() << " orders." << std::endl;
}