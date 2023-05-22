/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Mythread
*/

#include <thread>
#include <iostream>
#include "Order.hpp"

#ifndef MYTHREAD_HPP_
#define MYTHREAD_HPP_

class Mythread {
    public:
        Mythread();
        ~Mythread();

        void start(Plazza::Order order);

        void end();

        void cookingPizza();

    protected:
    private:
        std::thread _thread;
        Plazza::Order _order;
};

#endif /* !MYTHREAD_HPP_ */
