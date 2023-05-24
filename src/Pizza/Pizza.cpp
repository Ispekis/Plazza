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

void Plazza::Pizza::setNbrIngredient(int nbr)
{
    _nbrIngredient = nbr;
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

int Plazza::Pizza::getNbrIngredient() const
{
    return _nbrIngredient;
}

// std::ostream& operator<<(std::ostream &os, const pizza_data &pizzaData)
// {
//     pizza_data pd;

//     return os;
// }

std::ostream& operator<<(std::ostream &os, const Plazza::Pizza &pizza)
{
    os << pizza.getName() << std::string(" ");

    return os;
}

std::istream& operator>>(std::istream &is, Plazza::Pizza &pizza)
{
    std::string name;
    is >> name;
    pizza.setName(name);
    return is;
}
