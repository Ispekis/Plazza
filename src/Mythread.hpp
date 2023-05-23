/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Mythread
*/

#include <thread>
#include <iostream>
#include <condition_variable>
#include <mutex>
#include "Ingredient.hpp"
#include "Order.hpp"

#ifndef MYTHREAD_HPP_
#define MYTHREAD_HPP_

class Mythread {
    public:
        Mythread();
        ~Mythread();

        void start(Plazza::Order order);

        bool isRunning();

        void endThread();
        void fillOrder(std::vector<Plazza::Order>);
        void cookingPizza();

    protected:
    private:
        std::thread _thread;
        std::vector<Plazza::Order> _order;
        bool _isRunning;
        bool _isCooking;
        std::shared_ptr<Ingredient> _ingredient;
        std::condition_variable conditionVariable;
        std::mutex mutex;
};

#endif /* !MYTHREAD_HPP_ */
