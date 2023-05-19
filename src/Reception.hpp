/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Plazza
*/

#include "Parsing.hpp"
#include "ErrorHandling.hpp"
#include "PizzaEnum.hpp"
#include <sstream>
#include <iostream>
#include <tuple>
#include <vector>
#ifndef RECEPTION_HPP_
    #define RECEPTION_HPP_

namespace Plazza {
    class Reception {
        public:
            Reception(Parsing &data);
            ~Reception();

            void start();
            void parsingInput(std::string &line);
            void parseEnum();
            void splitInput(std::string &line);

        protected:
        private:
            Parsing _data;
            ErrorHandling _CheckError;
            std::vector<std::vector<std::string>> _receiptList;
            std::vector<std::tuple<PizzaType, PizzaSize, int>> _receiptEnum;
    };
}
#endif /* !PLAZZA_HPP_ */
