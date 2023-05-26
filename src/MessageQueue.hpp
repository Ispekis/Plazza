/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** MessageQueue
*/

#ifndef MESSAGEQUEUE_HPP_
    #define MESSAGEQUEUE_HPP_
    #include <sys/ipc.h>
    #include <sys/msg.h>
    #include "plazza.hpp"
    #include <iostream>
    #include <sstream>
    #include "Order.hpp"
    #include <cstring>
    #define ORDER_KEY 65
    #define CAPACITY_KEY 66
    #define CLOSURE_KEY 67

namespace Plazza {
    class MessageQueue {
        public:
            MessageQueue();
            ~MessageQueue();

            /**
             * @brief Send the order data to the messsage queue
             *
             * @param order
             * @param id
             */
            void sendOrder(Order order, int id);

            /**
             * @brief Receive the order data from the message queue
             *
             * @param id
             * @return std::unique_ptr<Plazza::Order>
             */
            std::unique_ptr<Plazza::Order> recvOrder(int id);

            /**
             * @brief Send the capacity left in the kitchen
             *
             * @param nbr
             * @param id
             */
            void sendCapacity(int nbr, int id);

            /**
             * @brief Receive the capacity left in the kitchen
             *
             * @param id
             * @return int
             */
            int recvCapacity(int id);

            /**
             * @brief Send the value of closure of a kitchen
             *
             * @param value
             * @param id
             */
            void sendClosure(int value, int id);

            /**
             * @brief Receive the closure boolean of the kitchen, return 0 if the kitchen is closed, 1 if its open, -1 if its not received by the reception
             *
             * @param id
             * @return true
             * @return false
             */
            int recvClosure(int id);

        protected:
        private:

            /**
             * @brief Send one data in queue
             *
             * @param value
             * @param id
             * @param key
             */
            void sendOneInfo(int value, int id, key_t key);

            /**
             * @brief Receive one data from queue
             *
             * @param value
             * @param id
             * @param key
             */
            int recvOneInfo(int id, key_t key);

            key_t _msgKey;
            key_t _capKey;
            key_t _closureKey;
    };
}

#endif /* !MESSAGEQUEUE_HPP_ */
