/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Pizza
*/

#include "Pizza.hpp"

Plazza::Pizza::Pizza()
{
}

Plazza::Pizza::~Pizza()
{
}

// void Plazza::Pizza::setBakeTime(int time)
// {

// }

// void Plazza::Pizza::setIngredients(std::vector<std::string> ingredients)
// {

// }

int Plazza::Pizza::getBakeTime()
{
    return _bakeTime;
}

std::vector<std::string> Plazza::Pizza::getIngredients()
{
    return _ingredients;
}

std::string Plazza::Pizza::getName()
{
    return _name;
}
