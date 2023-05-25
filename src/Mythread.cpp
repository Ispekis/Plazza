/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Mythread
*/

#include "Mythread.hpp"

Mythread::Mythread()
{
    _isRunning = true;
    std::cout << "Thread Started" << std::endl;
    _thread = std::thread(&Mythread::cookingPizza, std::ref(*this));
}

Mythread::~Mythread()
{
    _isRunning = false;
    std::cout << "thread is running: " << _isRunning << std::endl;
    // _thread.join();
    std::cout << "Thread Joined" << std::endl;
}

void Mythread::cookingPizza()
{
    // std::unique_lock<std::mutex> lock(mutex);
    // while (_isRunning)
    // {
        // std::cout << "waiting for pizza: " << &_isRunning << std::endl;
                // std::cout <<"test3 "<<_thread.get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(10));
    // }
    std::cout << "Cook is going to sleep" << std::endl;
}