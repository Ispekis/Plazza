/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Cook
*/

#include "Cook.hpp"

Plazza::Cook::Cook()
{
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