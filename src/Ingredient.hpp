/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Ingredient
*/

#ifndef INGREDIENT_HPP_
#define INGREDIENT_HPP_

#include <iostream>
#include <string>
#include <unordered_map>
#include "IPizza.hpp"

class Ingredient {
    public:
        Ingredient(int refillTime);


        bool makePizza(Plazza::IPizza *pizza);
        ~Ingredient();

    protected:
    private:
        // std::size_t _dough;
        // std::size_t _tomato;
        // std::size_t _gruyere;
        // std::size_t _ham;
        // std::size_t _mushrooms;
        // std::size_t _steak;
        // std::size_t _eggplant;
        // std::size_t _goatCheese;
        // std::size_t _chiefLove;
        std::size_t _refillTime;
        std::unordered_map<std::string, std::size_t> _ingredient;
};

#endif /* !INGREDIENT_HPP_ */
