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
    #include <cstring>

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

                // Init struct
                msgData.mesg_type = id;

                // Send data to queue
                msgid = msgget(key, 0666 | IPC_CREAT);
                if (msgid == -1) {
                    std::cout << "msgget error" << std::endl;
                    perror("");
                    return;
                }
                // std::cout << msgid << std::endl;
                if (msgsnd(msgid, &msgData, sizeof(msgData) - sizeof(long), 0) == -1) {
                    std::cout << "message not send " << id << std::endl;
                    perror("");
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
                    // Delete message from queue
                    msgctl(msgid, IPC_RMID, NULL);
                    return std::make_unique<T>(rcvData);
                }
                // Delete message from queue
                // msgctl(msgid, IPC_RMID, NULL);
                return nullptr;
            }
    };
}

#endif /* !MESSAGEQUEUE_HPP_ */
