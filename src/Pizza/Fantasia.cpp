/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Fantasia
*/

#include "Fantasia.hpp"

Plazza::FantasiaPizza::FantasiaPizza()
{
    _name = "fantasia";
    _ingredients = {"dough", "tomato", "gruyere", "steak"};
    _bakeTime = 2;
    _nbrIngredient = _ingredients.size();
}

Plazza::FantasiaPizza::~FantasiaPizza()
{
}
