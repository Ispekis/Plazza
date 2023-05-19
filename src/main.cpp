/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** main
*/

#include <iostream>
#include <string>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <memory>
#include <condition_variable>
#include "SafeQueue.hpp"
#include "Parsing.hpp"
#include "IMutex.hpp"
#include "Reception.hpp"
#include "Usage.hpp"

std::mutex mutex;

typedef struct data_s
{
    std::thread thread;
    std::shared_ptr<SafeQueue<int>> queue;
    int t;
    int id;
} data_t;

void *call_producer(data_t *info)
{
    for (int i = -3; i != 10; i++)
    {
        int a = 5 * info->id;
        info->queue->push(a);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Producer "<< info->id << " left" << std::endl;
    return (void *)info;
}

void *call_consumer(void *arg)
{
    data_t *info = (data_t *)arg;
    for (int tmp = 0; tmp != 30;tmp++)
    {
        {
            auto a = info->queue->pop();
            std::cout << "consumer" << info->id << ": " << a << std::endl;
        }
    }
    return (void *)info;
}

// int main(int ac __attribute__((unused)), char **av)
// {
//     int a = std::stoi(av[1]);
//     int b = std::stoi(av[2]);

//     data_t producer[a];
//     data_t consumer[b];
//     std::shared_ptr<SafeQueue<int>> queue = std::make_shared<SafeQueue<int>>();
//     std::cout << "Producer: " << a;
//     std::cout << " Consumer: " << b << std::endl;
//     // INIT PRODUCER
//     for (int i = 0; i != a; i++) {
//         producer[i].t = b;
//         producer[i].queue = queue;
//         producer[i].id = i;
//     }
// // INIT CONSUMER
//     for (int i = 0; i != b; i++) {
//         consumer[i].t = b;
//         consumer[i].queue = queue;
//         consumer[i].id = i;
//     }
//         for (int i = 0; i != a; i++) {
//         producer[i].thread = std::thread(call_producer, &producer[i]);
//     }
//     for (int i = 0; i != b; i++) {
//         consumer[i].thread = std::thread(call_consumer, (void *)&consumer[i]);
//     }
//     for (int i = 0; i != a; i++) {
//         consumer[i].thread.join();
//     }
//     for (int i = 0; i != b; i++) {
//         producer[i].thread.join();
//     }
// }

int main (int ac, char **av)
{
    try {
        std::string av1(av[1]);
        if (ac == 2 && av1.compare("-h") == 0) {
            Usage::display_usage(std::cout);
            return 0;
        }

        Parsing data(ac, av);
        Plazza::Reception reception(data);
        reception.start();
    }
    catch (const Error &error) {
        std::cout << error.what() << ": " << error.message() << "." << std::endl;
        return 84;
    }
    return 0;
}