/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** ErrorHandling
*/

#include "ErrorHandling.hpp"

ErrorHandling::ErrorHandling()
{
}

ErrorHandling::~ErrorHandling()
{
}

template<typename U>
void ErrorHandling::checkVectorLength(std::size_t size, std::vector<U> &vector)
{
    if (vector.size() != size + 1)
        throw Error("Vector", "BadLength");
}

template void ErrorHandling::checkVectorLength(std::size_t size, std::vector<std::string> &vector);
template void ErrorHandling::checkVectorLength(std::size_t size, std::vector<int> &vector);