/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** MessageQueue
*/

#include "MessageQueue.hpp"

Plazza::MessageQueue::MessageQueue()
{
    _msgKey = ftok(".", ORDER_KEY);
    _capKey = ftok(".", CAPACITY_KEY);
    _closureKey = ftok(".", CLOSURE_KEY);
}

Plazza::MessageQueue::~MessageQueue()
{
}

void Plazza::MessageQueue::sendOrder(Order order, int id)
{
    int msgid;
    msg_data msgData;

    // Remove padding
    std::memset(&msgData, sizeof(msgData), 0);

    // Init struct
    msgData.mesg_type = id;

    // serialize data
    std::stringstream serializedStream;
    serializedStream << order;
    std::string serializedString = serializedStream.str();

    // Deserialize data to struct
    std::stringstream deserializedStream(serializedString);
    deserializedStream >> msgData;

    // Send data to queue
    msgid = msgget(_msgKey, 0666 | IPC_CREAT);
    if (msgid == -1) {
        std::cout << "msgget error" << std::endl;
        perror("");
    }
    //  else {
    //     std::cout << "msg success" << std::endl;
    // }
    if (msgsnd(msgid, &msgData, sizeof(msgData) - sizeof(long), 0) == -1) {
        std::cout << "message send " << id << std::endl;
    }
    //  else {
    //     std::cout << "message not send" << std::endl;
    //     perror("");
    // }
};

Plazza::Order Plazza::MessageQueue::recvOrder(int id)
{
    int msgid;
    msg_data rcvData;

    // Remove padding
    std::memset(&rcvData, sizeof(rcvData), 0);

    // Receive queue
    msgid = msgget(_msgKey, 0666 | IPC_CREAT);
    if (msgrcv(msgid, &rcvData, sizeof(rcvData) - sizeof(long), id, IPC_NOWAIT) != -1) {
        std::cout << rcvData.type << std::endl;
        std::cout << rcvData.size << std::endl;
        std::cout << rcvData.nbr << std::endl;
        // Delete message from queue
        msgctl(msgid, IPC_RMID, NULL);
        return Plazza::Order((Plazza::PizzaType) rcvData.type, (Plazza::PizzaSize) rcvData.size, rcvData.nbr);
    } else {
        // TODO : implement throw
        perror("");
    }
}

void Plazza::MessageQueue::sendCapacity(int nbr, int id)
{
    sendOneInfo(nbr, id, _capKey);
}

int Plazza::MessageQueue::recvCapacity(int id)
{
    return recvOneInfo(id, _capKey);
}

void Plazza::MessageQueue::sendClosure(int value, int id)
{
    sendOneInfo(value, id, _closureKey);
}

int Plazza::MessageQueue::recvClosure(int id)
{
    return recvOneInfo(id, _closureKey);
}

void Plazza::MessageQueue::sendOneInfo(int value, int id, key_t key)
{
    int msgid;
    capacity_data data;

    // Remove padding
    std::memset(&data, sizeof(data), 0);

    // Init struct
    data.mesg_type = id;
    data.value = value;

    // Send data to queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        std::cout << "msgget error" << std::endl;
        perror("");
    }

    if (msgsnd(msgid, &data, sizeof(data) - sizeof(long), 0) == -1) {
        std::cout << "message not send " << id << std::endl;
    } else {
        std::cout << "send" << std::endl;
    }
}

int Plazza::MessageQueue::recvOneInfo(int id, key_t key)
{
    int msgid;
    capacity_data data;

    // Remove padding
    std::memset(&data, sizeof(data), 0);

    // Receive queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgrcv(msgid, &data, sizeof(data) - sizeof(long), id, IPC_NOWAIT) != -1) {
        // std::cout << data.type << std::endl;
        // std::cout << data.size << std::endl;
        // std::cout << data.nbr << std::endl;
        // Delete message from queue
        msgctl(msgid, IPC_RMID, NULL);
        return data.value;
    } else {
        // TODO : implement throw
        perror("");
    }
}