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

        protected:
        private:
            Parsing _data;
            ErrorHandling _CheckError;
            std::vector<std::vector<std::string>> _receiptList;
            std::vector<Order> _orderList;
            std::vector<Kitchen> _kitchens;
            std::vector<std::array<int, 2>> _pipefds;
    };
}
#endif /* !PLAZZA_HPP_ */
