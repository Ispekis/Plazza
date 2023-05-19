/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** IMutex
*/

#ifndef IMUTEX_HPP_
#define IMUTEX_HPP_

class IMutex {
    public:
        virtual ~IMutex() = default;
        virtual void lock() = 0;
        virtual void unlock() = 0;
        virtual void trylock() = 0;

    protected:
    private:
};


#endif /* !IMUTEX_HPP_ */
