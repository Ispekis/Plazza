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
    #include "Order.hpp"

namespace Plazza {
    class MessageQueue {
        public:
            MessageQueue() {};
            ~MessageQueue() {};

            void push(Order order) {
                key_t key;
                int msgid;
                pizza_data pizdata;

                // serialize data
                std::stringstream serializedStream;
                serializedStream << order;
                std::string serializedString = serializedStream.str();

                // Deserialize data to struct
                std::stringstream deserializedStream(serializedString);
                deserializedStream >> pizdata;

                // std::cout << pizdata.name << std::endl;
                // std::cout << pizdata.bakeTime << std::endl;
                // std::cout << pizdata.nbrIngredient << std::endl;
                // for (int i = 0; i < pizdata.nbrIngredient; i++) {
                //     std::cout << pizdata.ingredients[i] << std::endl;
                // }
                // std::cout << pizdata.type << std::endl;
                // std::cout << pizdata.size << std::endl;
                // key = ftok(".", 65);

                // msgid = msgget(key, 0666 | IPC_CREAT);
                // pizdata.msg_type = 1;
                // std::cout << key << std::endl;
            };

        protected:
        private:
    };
}

#endif /* !MESSAGEQUEUE_HPP_ */
