/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Ingredient
*/

#include "Ingredient.hpp"

Ingredient::Ingredient(int refillTime) : _refillTime(refillTime)
{
    _dough = 5;
    _tomato = 5;
    _gruyere = 5;
    _ham = 5;
    _mushrooms = 5;
    _steak = 5;
    _eggplant = 5;
    _goatCheese = 5;
    _chiefLove = 5;
    std::cout << "Ingredient Filled and will be refilled by one every" << refillTime << " ms" << std::endl;
}

Ingredient::~Ingredient()
{
}
