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
    _order = order;
    _thread = std::thread(&Mythread::cookingPizza, this);
}

void Mythread::end()
{
    _thread.join();
}

void Mythread::cookingPizza()
{
    std::cout << "Going to cook" << std::endl;
    auto pizza = _order.getPizza();
    auto size = _order.getSize();
    auto cookTime = pizza->getBakeTime();
    std::this_thread::sleep_for(std::chrono::seconds(cookTime));
    std::cout << "Cooked" << std::endl;
}
