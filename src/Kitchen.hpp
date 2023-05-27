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

            /**
             * @brief Main Loop for the kitchen
             * 
             */
            void kitchenLoop();

            /**
             * @brief receive order from the reception and remove it from the list
             *
             * @param orderList
             */
            void receiveOrder(Plazza::Order order);

            /**
             * @brief Check if the itchen has been running for 5 seconds 
             * 
             * @return true 
             * @return false 
             */
            bool timeOut();

            /**
             * @brief Receive messagequeue and handling data from messagequeue
             * 
             */
            void messageQueueReception();

        protected:
        private:

            /**
             * @brief Close the kitchen, send closing messagequeue to reception 
             * 
             */
            void closeKitchen();

            float _mutiplier;
            int _nbCooks;
            size_t _orderCapacityMax;
            size_t _orderCapacity;
            int _receptionPid;

            SafeQueue<Plazza::Order> _order;
            std::shared_ptr<Ingredient> _ingredient;

            // Timer
            std::chrono::steady_clock::time_point _start;
            std::chrono::seconds _workDuration;

            // Ipc's data
            MessageQueue<msg_data> _orderMsgQ;
            MessageQueue<closure_data> _closureMsgQ;
            MessageQueue<capacity_data> _capacityMsgQ;
            key_t _orderKey;
            key_t _capacityKey;
            key_t _closureKey;

    };
}

#endif /* !KITCHEN_HPP_ */
