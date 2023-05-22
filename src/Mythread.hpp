/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Mythread
*/

#include <thread>
#include <iostream>

#ifndef MYTHREAD_HPP_
#define MYTHREAD_HPP_

class Mythread {
    public:
        Mythread();
        ~Mythread()
        {
            if (_thread.joinable())
                _thread.join();
        }

        void start()
        {
            _thread = std::thread(&Mythread::cookingPizza, this);
        }

        void cookingPizza()
        {
            std::cout << "Going to cook" << std::endl;
        }

    protected:
    private:
        std::thread _thread;
};

#endif /* !MYTHREAD_HPP_ */
