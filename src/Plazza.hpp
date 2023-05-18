/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Plazza
*/

#include "Parsing.hpp"

#ifndef PLAZZA_HPP_
#define PLAZZA_HPP_

class Plazza {
    public:
        Plazza(Parsing &data);
        ~Plazza();

        void runPlazza();

    protected:
    private:
        Parsing _data;
};

#endif /* !PLAZZA_HPP_ */
