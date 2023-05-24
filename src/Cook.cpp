/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Cook
*/

#include "Cook.hpp"

Plazza::Cook::Cook(std::shared_ptr<Ingredient> ingredient, std::shared_ptr<SafeQueue<Plazza::Order>> order) : _ingredient(ingredient), _order(order)
{
    _orderCapacity = 2;
    _cooking = false;
    _thread = std::make_shared<Mythread>();
}

Plazza::Cook::~Cook()
{
}

bool Plazza::Cook::isOverwhelmed()
{
    if (_orderCapacity == 0) {
        return true;
    }
    return false;
}

std::size_t Plazza::Cook::availableOrderCapacity()
{
    return _orderCapacity;
}

void Plazza::Cook::addOrder(Plazza::Order order)
{
    _orderList.push_back(order);
    _orderCapacity--;
}

bool Plazza::Cook::isCooking()
{
    _cooking = _thread->isRunning();
    return _cooking;
}

void Plazza::Cook::closeThread()
{
    _thread->endThread();
}

void Plazza::Cook::endThread()
{
    _thread->~Mythread();
}

void Plazza::Cook::cookPizza()
{
    _cooking = true;
    auto order = _orderList.front();
    auto pizza = order.getPizza();
    if (_ingredient->makePizza(pizza)) {
        std::cout << "Cooking a " << _orderList.front().getName() << std::endl;
        _orderList.erase(_orderList.begin());
        _thread->start(order);
    }
}