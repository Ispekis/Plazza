/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Parsing
*/

#ifndef PARSING_HPP_
#define PARSING_HPP_

#include <string>
#include <iostream>
#include <unordered_map>
#include "Error.hpp"

#define ERR 1
#define NO_ERR 0

class Parsing {
    public:
        Parsing(int ac, char **av);
        ~Parsing();

    protected:
    private:
        // std::unordered_map<> args;
        float _multiplier;
        int _nbCooks;
        int _refillTimer;
};

#endif /* !PARSING_HPP_ */
