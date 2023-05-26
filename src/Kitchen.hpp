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
    #include "Process.hpp"
    #include "Order.hpp"
    #include "Cook.hpp"
    #include <array>
    #include "SafeQueue.hpp"
    #include "MessageQueue.hpp"

namespace Plazza {
    class Kitchen {
        public:
            Kitchen(float mutiplier, int nbCooks, int time, int pid);
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
            void getMessage();
            void stopCooks();
            bool isStaturated();
            bool timeOut();


        protected:
        private:
            float _mutiplier;
            int _nbCooks;
            size_t availableCooks;
            size_t _orderCapacity;
            MessageQueue _msgQueue;
            int _rPid;
            // std::vector<Plazza::Cook> _cooks;
            std::shared_ptr<Ingredient> _ingredient;
            std::shared_ptr<SafeQueue<Plazza::Order>> _order;

            std::chrono::steady_clock::time_point _start;
            std::chrono::seconds _workDuration;

    };
}

#endif /* !KITCHEN_HPP_ */
