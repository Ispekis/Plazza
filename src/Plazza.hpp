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
        void parsingInput(std::string &line);
    protected:
    private:
        Parsing _data;
};

enum PizzaType
{
    Regina = 1,
    Margarita = 2,
    Americana = 4,
    Fantasia = 8
};

enum PizzaSize
{
    S = 1,
    M = 2,
    L = 4,
    XL = 8,
    XXL = 16
};
#endif /* !PLAZZA_HPP_ */
