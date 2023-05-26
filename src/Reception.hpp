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
            bool parsingInput(std::string &line);
            void parseEnum();
            void splitInput(std::string &line);
            void create_kitchen();
            void manageKitchen();
            void closeKitchen();

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
            void dispatchOrder();

            Parsing _data;
            ErrorHandling _CheckError;
            std::vector<std::vector<std::string>> _receiptList;
            std::vector<Order> _orderList;
            pid_t _receptionPid = 0;
            MessageQueue _msgQueue;
            std::vector<int> _kitchenPids;
    };
}
#endif /* !PLAZZA_HPP_ */