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
    template <typename T>
    class MessageQueue {
        public:
            MessageQueue() {};
            ~MessageQueue() {};

            /**
             * @brief Send the message data to the messsage queue
             *
             * @param order
             * @param id
             */
            void push(T msgData, int id, key_t key) {
                int msgid;

                // Remove padding
                std::memset(&msgData, sizeof(msgData), 0);

                // Init struct
                msgData.mesg_type = id;

                // serialize data
                // std::stringstream serializedStream;
                // serializedStream << order;
                // std::string serializedString = serializedStream.str();

                // // Deserialize data to struct
                // std::stringstream deserializedStream(serializedString);
                // deserializedStream >> msgData;

                // Send data to queue
                msgid = msgget(key, 0666 | IPC_CREAT);
                if (msgid == -1) {
                    std::cout << "msgget error" << std::endl;
                    perror("");
                    return;
                }
                if (msgsnd(msgid, &msgData, sizeof(msgData) - sizeof(long), 0) == -1) {
                    std::cout << "message not send " << id << std::endl;
                    return;
                }
            }

            /**
             * @brief Receive the message data from the message queue
             *
             * @param id
             * @return std::unique_ptr<Plazza::Order>
             */
            std::unique_ptr<T> pop(int id, key_t key) {
                int msgid;
                T rcvData;

                // Remove padding
                std::memset(&rcvData, sizeof(rcvData), 0);

                // Receive queue
                msgid = msgget(key, 0666 | IPC_CREAT);

                if (msgid == -1) {
                    perror("msgid");
                }
                if (msgrcv(msgid, &rcvData, sizeof(rcvData) - sizeof(long), id, IPC_NOWAIT) != -1) {
                    // std::cout << rcvData.type << std::endl;
                    // std::cout << rcvData.size << std::endl;
                    // std::cout << rcvData.nbr << std::endl;
                    // Delete message from queue
                    msgctl(msgid, IPC_RMID, NULL);
                    return std::make_unique<T>(rcvData);
                }
                // Delete message from queue
                msgctl(msgid, IPC_RMID, NULL);
                return nullptr;
            }

            // /**
            //  * @brief Send the capacity left in the kitchen
            //  *
            //  * @param nbr
            //  * @param id
            //  */
            // void sendCapacity(int nbr, int id);

            // /**
            //  * @brief Receive the capacity left in the kitchen
            //  *
            //  * @param id
            //  * @return int
            //  */
            // int recvCapacity(int id);

            // /**
            //  * @brief Send the value of closure of a kitchen
            //  *
            //  * @param value
            //  * @param id
            //  */
            // void sendClosure(int value, int id);

            // /**
            //  * @brief Receive the closure boolean of the kitchen, return 0 if the kitchen is closed, 1 if its open, -1 if its not received by the reception
            //  *
            //  * @param id
            //  * @return true
            //  * @return false
            //  */
            // int recvClosure(int id);

        protected:
        private:

            // /**
            //  * @brief Send one data in queue
            //  *
            //  * @param value
            //  * @param id
            //  * @param key
            //  */
            // void sendOneInfo(int value, int id, key_t key);

            // /**
            //  * @brief Receive one data from queue
            //  *
            //  * @param value
            //  * @param id
            //  * @param key
            //  */
            // int recvOneInfo(int id, key_t key);

            // key_t _msgKey;
            // key_t _capKey;
            // key_t _closureKey;
    };
}

#endif /* !MESSAGEQUEUE_HPP_ */
