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
#include <chrono>
#include <unordered_map>
#include "IPizza.hpp"

class Ingredient {
    public:
        Ingredient(int refillTime);

        /**
         * @brief Check if there is enough ingredient to make the pizza then remove ingredient if yes
         * 
         * @param pizza 
         * @return true 
         * @return false 
         */
        bool makePizza(Plazza::IPizza *pizza);

        /**
         * @brief Refill Ingredient every _refillTime in ms
         *
         */
        void refillIngredient();
        ~Ingredient();

    protected:
    private:
        std::chrono::steady_clock::time_point _start;
        std::chrono::milliseconds _refillTime;
        std::unordered_map<std::string, std::size_t> _ingredient;
};

#endif /* !INGREDIENT_HPP_ */
