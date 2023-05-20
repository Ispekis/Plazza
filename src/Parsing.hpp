/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Parsing
*/

#ifndef PARSING_HPP_
#define PARSING_HPP_

#include "Error.hpp"

class Parsing {
    public:
        Parsing(int ac, char **av);
        ~Parsing();

        int getNbCooks();
        float getMultiplier();
        int getRefillTime();

    protected:
    private:
        float _multiplier;
        int _nbCooks;
        int _refillTimer;
};

#endif /* !PARSING_HPP_ */
