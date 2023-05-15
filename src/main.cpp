/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** main
*/

#include <iostream>
#include <string>
    #include "stdbool.h"
    #include "stdlib.h"
    #include "stdio.h"
    #include "semaphore.h"
    #include "pthread.h"
#include "plazza.hpp"
#include "IMutex.hpp"

typedef struct data_s {
    pthread_t thread;
    int *countervalue;
    IMutex *mutex;
    int t;
} data_t;

void *call_incrementation(void *arg)
{
    data_t *info = (data_t *)arg;

    info->mutex->lock();
    incrementCounter(info->countervalue, info->t);
    info->mutex->unlock();

}

int main(int ac __attribute__((unused)), char **av)
{
    int a = std::stoi(av[1]);
    int b = std::stoi(av[2]);

    data_t info[a];
    int inc = 0;

    IMutex *mutext = new Pthread_Mutex();
    // pthread_mutex_t mutex;
    for (int i = 0; i != a; i++)
    {
        info[i].countervalue = &inc;
        info[i].t = b;
        info[i].mutex = mutext;
    }
    for (int i = 0; i != a; i++) {
        pthread_create(&info[i].thread, NULL, call_incrementation, (void *)&info[i]);
    }
    for (int i = 0; i != a; i++) {
        pthread_join(info[i].thread, NULL);
    }
    std::cout << "Got:" << *info[0].countervalue << " Expected:" << a * b << std::endl;
}