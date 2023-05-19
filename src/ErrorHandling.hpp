/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** ErrorHandling
*/

#ifndef ERRORHANDLING_HPP_
#define ERRORHANDLING_HPP_
#include <iostream>
#include "Error.hpp"
#include <vector>

class ErrorHandling {
    public:
        ErrorHandling();
        ~ErrorHandling();
        template<typename U>
        void checkVectorLength(std::size_t size, std::vector<U>&);

    private:
};

#endif /* !ERRORHANDLING_HPP_ */
