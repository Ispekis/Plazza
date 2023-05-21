/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Ingredient
*/

#include "Ingredient.hpp"

Ingredient::Ingredient(int refillTime) : _refillTime(refillTime)
{
    // "dough", = 5;
    // "tomato", = 5;
    // "gruyere", = 5;
    // "ham", = 5;
    // "mushrooms", = 5;
    // "steak", = 5;
    // "eggplant", = 5;
    // "goatCheese", = 5;
    // "chiefLove", = 5;
    std::vector<std::string> ingredient = { "dough", "tomato", "gruyere", "ham", "mushrooms", "steak", "eggplant", "goatCheese", "chiefLove" };

    for (auto element : ingredient) {
        _ingredient[element] = 5;
    }
    std::cout << "Ingredient Filled and will be refilled by one every" << refillTime << " ms" << std::endl;
}

Ingredient::~Ingredient()
{
}

bool makePizza(Plazza::IPizza *pizza)
{
    auto ingredient = pizza->getIngredients();
}