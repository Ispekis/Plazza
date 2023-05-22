/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Mythread
*/

#include "Mythread.hpp"

Mythread::Mythread()
{
}

Mythread::~Mythread()
{
    if (_thread.joinable())
        _thread.join();
}

void Mythread::start(Plazza::Order order)
{
    _thread = std::thread(&Mythread::cookingPizza, this);
    _order = order;
}

void Mythread::end()
{
    _thread.join();
}

void Mythread::cookingPizza()
{
    std::cout << "Going to cook" << std::endl;
}
