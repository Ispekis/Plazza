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
            void receiveOrder(Plazza::Order order);

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
            void messageQueueReception();

        protected:
        private:

            /**
             * @brief Close the kitchen
             * 
             */
            void closeKitchen();

            float _mutiplier;
            int _nbCooks;
            size_t availableCooks;
            size_t _orderCapacity;
            int _receptionPid;
            SafeQueue<Plazza::Order> _order;

            std::vector<std::shared_ptr<Plazza::Cook>> _cooks;
            std::shared_ptr<Ingredient> _ingredient;

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
