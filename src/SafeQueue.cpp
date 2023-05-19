/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** SafeQueue
*/

#include "SafeQueue.hpp"

SafeQueue::SafeQueue()
{
}

SafeQueue::~SafeQueue()
{
}

void SafeQueue::push(int value)
{
    _ints.push_back(value);
}

bool SafeQueue::tryPop(int &value)
{
    if (_ints.empty()) {
        return false;
    }
    value = _ints.at(0);
    _ints.erase(_ints.begin());
    return true;
}
