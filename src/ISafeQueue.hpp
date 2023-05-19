/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** ISafeQueue
*/

#ifndef ISAFEQUEUE_HPP_
#define ISAFEQUEUE_HPP_

class ISafeQueue {
    public:
        virtual ~ISafeQueue() = default;
        virtual void push(int value) = 0;
        virtual bool tryPop(int &value) = 0;

    protected:
    private:
};

#endif /* !SAFEQUEUE_HPP_ */
