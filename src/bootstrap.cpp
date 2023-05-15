/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** bootstrap
*/

#include "plazza.hpp"

void incrementCounter(int *counter, int n)
{
    for (int i = 0; i != n; i++)
    {
        *counter += 1;
    }
}