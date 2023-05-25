/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Pizza
*/

#include "Pizza.hpp"
#include <iostream>

Plazza::Pizza::Pizza()
{
}

Plazza::Pizza::~Pizza()
{
}

void Plazza::Pizza::setName(std::string name)
{
    _name = name;
}

void Plazza::Pizza::setBakeTime(int time)
{
    _bakeTime = time;
}

void Plazza::Pizza::setIngredients(std::vector<std::string> ingredients)
{
    _ingredients = ingredients;
}

int Plazza::Pizza::getBakeTime() const
{
    return _bakeTime;
}

std::vector<std::string> Plazza::Pizza::getIngredients() const
{
    return _ingredients;
}

std::string Plazza::Pizza::getName() const
{
    return _name;
}

// std::ostream& operator<<(std::ostream &os, const pizza_data &pizzaData)
// {
//     pizza_data pd;

//     return os;
// }

// std::ostream& operator<<(std::ostream &os, const Plazza::IPizza &pizza)
// {
//     os << pizza.getName() << "\n";
//     os << pizza.getBakeTime() << "\n";
//     os << pizza.getNbrIngredient() << "\n";
//     for (auto ingredient : pizza.getIngredients()) {
//         os << ingredient << "\n";
//     }
//     return os;
// }

// std::istream& operator>>(std::istream &is, Plazza::IPizza &pizza)
// {
//     std::string name;
//     is >> name;
//     pizza.setName(name);
//     return is;
// }
