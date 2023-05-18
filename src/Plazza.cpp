/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Plazza
*/

#include "Plazza.hpp"

Plazza::Plazza(Parsing &data) : _data(data)
{
}

Plazza::~Plazza()
{
}

void Plazza::runPlazza()
{
    std::string line;

    while (std::getline(std::cin, line)) {
        std::cout << line << std::endl;
        parsingInput(line);
    }
}

void Plazza::parsingInput(std::string &line)
{
    
}