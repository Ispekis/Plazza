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
    #include <array>
    #include "SafeQueue.hpp"

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

            void kitchenLoop();

            /**
             * @brief receive order from the reception and remove it from the list
             *
             * @param orderList
             */
            void receiveOrder(std::vector<Plazza::Order> orderList);

            /**
             *
             * @brief check if the kitchen is saturated
             *
             * @return true
             * @return false
             */


            void stopCooks();
            bool isStaturated();
            bool timeOut();


            size_t getAvailableCooks() {
                return availableCooks - _nbCooks;
            }

            std::unordered_map<std::string, std::size_t> getIngredient() {
                return _ingredient.get()->getIngredient();
            }

        protected:
        private:
            float _mutiplier;
            int _nbCooks;
            size_t availableCooks;
            size_t _orderCapacity;

            std::vector<std::shared_ptr<Plazza::Cook>> _cooks;
            std::shared_ptr<Ingredient> _ingredient;
            std::shared_ptr<SafeQueue<Plazza::Order>> _order;

            std::chrono::steady_clock::time_point _start;
            std::chrono::seconds _workDuration;

    };
}

#endif /* !KITCHEN_HPP_ */
