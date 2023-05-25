/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Cook
*/

#include "Cook.hpp"

Plazza::Cook::Cook(std::shared_ptr<Ingredient> ingredient, std::shared_ptr<SafeQueue<Plazza::Order>> order) : _ingredient(ingredient), _order(order)
{
    _cooking = false;
    std::cout << "\tCook Constructor" << std::endl;
}

Plazza::Cook::~Cook()
{
    std::cout << "\tCook Desctructor" << std::endl;
}