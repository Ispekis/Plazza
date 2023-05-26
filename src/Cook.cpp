/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Cook
*/

#include "Cook.hpp"

Plazza::Cook::Cook(std::shared_ptr<Ingredient> ingredient, std::shared_ptr<SafeQueue<Plazza::Order>> order) : _ingredient(ingredient), _order(order)
{
    // _orderCapacity = 2;
    _cooking = false;
    // _thread = Mythread>();
}

Plazza::Cook::~Cook()
{
    std::cout << "destroyed" << std::endl;
}

// void Plazza::Cook::stopCook()
// {
//     std::cout << "Stop thread" << std::endl;
//     _thread.stopThread();
// }

void Plazza::Cook::cookPizza()
{

}