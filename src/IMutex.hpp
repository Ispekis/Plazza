/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** IMutex
*/

#include "plazza.hpp"
    #include "pthread.h"

class IMutex {
    public:
        virtual ~IMutex() = default;
        //  ~Imutex() = default;
        virtual void lock() = 0;
        virtual void unlock() = 0;
        virtual void trylock() = 0;
};

class Pthread_Mutex : public IMutex
{
    public:
        Pthread_Mutex() {
            pthread_mutex_init(&_mutex, NULL);
        };
        ~Pthread_Mutex() {
            pthread_mutex_destroy(&_mutex);
        };
        void lock() {
            pthread_mutex_lock(&_mutex);
        };
    
        void unlock() {
            pthread_mutex_unlock(&_mutex);
        }
    
        void trylock() {
            pthread_mutex_trylock(&_mutex);
        }

private:
    pthread_mutex_t _mutex;
};