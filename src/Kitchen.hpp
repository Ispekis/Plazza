/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP_
    #define KITCHEN_HPP_
    #include <unistd.h>
    #include <chrono>
    #include "Ingredient.hpp"
    #include "Error.hpp"
    #include <iostream>
    #include "Order.hpp"
    #include "Cook.hpp"

namespace Plazza {
    class Kitchen {
        public:
            Kitchen(float mutiplier, int nbCooks, int time, std::array<int, 2> pipefd);
            ~Kitchen();

            /**
             * @brief Run the kitchen
             *
             */
            void run();

            /**
             * @brief receive order from the reception and remove it from the list
             *
             * @param orderList
             */
            void receiveOrder(std::vector<Plazza::Order> &orderList);

            /**
             *
             * @brief check if the kitchen is saturated
             *
             * @return true
             * @return false
             */
            bool isStaturated();

        protected:
        private:
            float _mutiplier;
            int _nbCooks;
            // int _refillTime;
            size_t availableCooks;
            std::vector<Plazza::Cook> _cooks;
            std::chrono::seconds _workDuration;
            Ingredient _ingredient;
    };
}

#endif /* !KITCHEN_HPP_ */
