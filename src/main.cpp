/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** main
*/

#include "SafeQueue.hpp"
#include <iostream>
#include "IMutex.hpp"
#include <thread>
#include <random>
#include <chrono>

void producer_thread(SafeQueue &queue)
{
    while (true) {
        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> dis(0, 15);

        int random_nbr = dis(gen);
        queue.push(random_nbr);
        std::cout << "producer pushed " << random_nbr <<  std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void customer_thread(SafeQueue &queue)
{
    while (true) {
        int value;
        if (queue.tryPop(value)) {
            std::cout << "Customer unstack from queue as " << value << std::endl;
        } else {
            std::cout << "Queue is empty" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

int main(int ac, char **av)
{
    SafeQueue queue;

    std::thread Producer(producer_thread, std::ref(queue));
    std::thread Producer2(producer_thread, std::ref(queue));
    std::thread Customer(customer_thread, std::ref(queue));
    Producer.join();
    Producer2.join();
    Customer.join();
    int va = 0;

    std::cout << queue.tryPop(va) << " and " <<  va <<  std::endl;
    return 0;
}