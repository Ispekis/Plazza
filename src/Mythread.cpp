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
    std::cout << "Cook is ready to cook pizza" << std::endl;
    _thread = std::thread(&Mythread::cookingPizza, std::ref(*this));
}

Mythread::~Mythread()
{
    std::cout << "thread is running: " << _isRunning << std::endl;
    _thread.join();
    std::cout << "Thread Joined" << std::endl;
}

void Mythread::fillOrder(Plazza::Order order)
{
    _order = order;
}

bool Mythread::isRunning()
{

    // if (_isRunning == false)
    //     if (_thread.joinable())
    //         _thread.join();
    // return _isRunning;
}

// bool Mythread::isCooking()
// {
//     return _isCooking;
// }

void Mythread::endThread()
{
    // {
    //     std::lock_guard<std::mutex> lock(mutex);
    //     _isRunning = false;
    // }
    // conditionVariable.notify_one();
}

void Mythread::cookingPizza()
{
    // std::unique_lock<std::mutex> lock(mutex);
    while (_isRunning)
    {
        std::cout << "waiting for pizza: " << &_isRunning << std::endl;
                std::cout <<"test3 "<<_thread.get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Cook is going to sleep" << std::endl;
}

void Mythread::stopThread()
{
        if (_isRunning)
    {
        _isRunning = false;
    std::cout << "test: " << &_isRunning << std::endl;
        std::cout <<"test2 "<<_thread.get_id() << std::endl;
        _thread.join();
    }
}