/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP_
    #define KITCHEN_HPP_
    #include <unistd.h>
    #include <chrono>
    #include "Error.hpp"
    #include <iostream>

namespace Plazza {
    class Kitchen {
        public:
            Kitchen();
            ~Kitchen();

            void run();

        protected:
        private:
            std::chrono::seconds _workDuration;
    };
}

#endif /* !KITCHEN_HPP_ */
