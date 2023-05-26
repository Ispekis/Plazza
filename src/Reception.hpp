/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Plazza
*/

#ifndef RECEPTION_HPP_
    #define RECEPTION_HPP_
    #include "Order.hpp"
    #include "Parsing.hpp"
    #include "ErrorHandling.hpp"
    #include <sstream>
    #include <iostream>
    #include <tuple>
    #include <vector>
    #include "Kitchen.hpp"
    #include <array>
    #include <string>
    #include <unistd.h>
    #include <chrono>
    #include "MessageQueue.hpp"

namespace Plazza {
    class Reception {
        public:
            Reception(Parsing &data);
            ~Reception();

            void start();
            Plazza::Order convertToOrder(std::array<std::string, 3> stringOrder);

            /**
             * @brief Seprate orders
             *
             * @param line
             * @return std::vector<std::array<std::string, 3>>
             */
            std::vector<std::array<std::string, 3>> splitInput(std::string &line);
            void create_kitchen();

        protected:
        private:
            /**
             * @brief Check if the reception needs more kitchen
             *
             * @return true
             * @return false
             */
            bool needKitchen();

            /**
             * @brief dispatch orders
             *
             */
            void dispatchOrder(Plazza::Order order);

            Parsing _data;
            ErrorHandling _CheckError;
            pid_t _receptionPid = 0;
            MessageQueue _msgQueue;
            std::vector<int> _kitchenPids;
    };
}
#endif /* !PLAZZA_HPP_ */
