/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Parsing
*/

#include "Parsing.hpp"

static bool isPositiveInt(const std::string &str)
{
    for (char c : str) {
        if (!std::isdigit(c)) {
            return ERR;
        }
    }
    return NO_ERR;
}

static bool isPositiveFloat(const std::string &str)
{
    std::size_t pointIndex = -1;
    bool gotPoint = false;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '.') {
            if (gotPoint == true)
                return ERR;
            pointIndex = i;
            gotPoint = true;
        }
        else {
            if (!std::isdigit(str[i]))
                return ERR;
        }
    }
    if (pointIndex == 0 || pointIndex == str.size() - 1)
        return ERR;
    return NO_ERR;
}

static bool error_handling(int ac, char **av)
{
    if (ac != 4)
        return ERR;
    if (isPositiveFloat(av[1]) == ERR)
        return ERR;
    for (int i = 2; i != ac; i++)
    {
        if (isPositiveInt(av[i]) == ERR)
            return ERR;
    }
    return NO_ERR;
}

Parsing::Parsing(int ac, char **av)
{
    if (error_handling(ac, av) == ERR)
        throw Error("./Plazza <Float> <Int> <Int>\n\t./Plazza <Multiplier> <Cooks> <Refills times>", "Parsing Error");
    _multiplier = std::stof(av[1]);
    _nbCooks = std::stoi(av[2]);
    _refillTimer = std::stoi(av[3]);
}

Parsing::~Parsing()
{
}
