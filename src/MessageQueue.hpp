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

            void push(Order order, int id) {
                int msgid;
                pizza_data pizdata;

                // Init struct
                pizdata.mesg_type = id;

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

                // Send data to queue
                // msgid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);
                // if (msgid == -1) {
                //     std::cout << "msgget error" << std::endl;
                // } else {
                //     std::cout << "msg success" << std::endl;
                // }
                // if (msgsnd(msgid, &pizdata, sizeof(pizdata), 0) != -1) {
                //     std::cout << "message send" << std::endl;
                // } else {
                //     std::cout << "message not send" << std::endl;
                //     perror("");
                // }
            };

            void pop(int id) {
                int msgid;
                pizza_data rcvPizza;

                // Receive queue
                msgid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);
                if (msgrcv(msgid, &rcvPizza, sizeof(rcvPizza), id, IPC_NOWAIT) != -1) {
                    std::cout << "ok2" << std::endl;

                    std::cout << rcvPizza.name << std::endl;
                    std::cout << rcvPizza.bakeTime << std::endl;
                    std::cout << rcvPizza.nbrIngredient << std::endl;
                    for (int i = 0; i < rcvPizza.nbrIngredient; i++) {
                        std::cout << rcvPizza.ingredients[i] << std::endl;
                    }
                    std::cout << rcvPizza.type << std::endl;
                    std::cout << rcvPizza.size << std::endl;
                }
            }

        protected:
        private:
    };
}

#endif /* !MESSAGEQUEUE_HPP_ */
