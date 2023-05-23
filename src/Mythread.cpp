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
    _thread = std::thread(&Mythread::cookingPizza, this);
}

Mythread::~Mythread()
{
    std::cout << "thread is running: " << _isRunning << std::endl;
    _thread.join();
    std::cout << "Thread Joined" << std::endl;
}

void Mythread::fillOrder(std::vector<Plazza::Order> order)
{
    _order = order;
}

void Mythread::start(Plazza::Order order)
{
    _isRunning = true;
}

bool Mythread::isRunning()
{
    if (_isRunning == false)
        if (_thread.joinable())
            _thread.join();
    return _isRunning;
}

void Mythread::endThread()
{
    {
        std::lock_guard<std::mutex> lock(mutex);
        _isRunning = false;
    }
    conditionVariable.notify_one();
}

void Mythread::cookingPizza()
{
    std::unique_lock<std::mutex> lock(mutex);
    while (_isRunning == true)
    {
        if (!_order.empty())
            std::cout << "cooc" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << _isRunning << std::endl;
        conditionVariable.wait(lock, [this] { return _isRunning; });
    }
    std::cout << "Cook is going to sleep" << std::endl;
}
