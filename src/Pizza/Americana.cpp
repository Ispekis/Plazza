/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Americana
*/

#include "Americana.hpp"

Plazza::AmericanaPizza::AmericanaPizza()
{
    _name = "americana";
    _ingredients = {"dough", "tomato", "eggplant", "goat cheese", "chief love"};
    _bakeTime = 4;
    _nbrIngredient = _ingredients.size();
}

Plazza::AmericanaPizza::~AmericanaPizza()
{
}
