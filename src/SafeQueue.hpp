/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** SafeQueue
*/

#ifndef SAFEQUEUE_HPP_
    #define SAFEQUEUE_HPP_
    #include "ISafeQueue.hpp"
    #include <vector>

class SafeQueue : public ISafeQueue {
    public:
        SafeQueue();
        ~SafeQueue();
        void push(int value);
        bool tryPop(int &value);

    protected:
    private:
        std::vector<int> _ints;
};

#endif /* !SAFEQUEUE_HPP_ */
