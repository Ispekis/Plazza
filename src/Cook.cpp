/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Cook
*/

#include "Cook.hpp"

Plazza::Cook::Cook(std::shared_ptr<Ingredient> ingredient) : _ingredient(ingredient)
{
    _orderCapacity = 2;
    _cooking = false;
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
    return _cooking;
}

void Plazza::Cook::cookPizza()
{
    _cooking = true;
    auto order = _orderList.front();
    _orderList.erase(_orderList.begin());
    auto pizza = order.getPizza();
}