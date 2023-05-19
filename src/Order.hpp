/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Order
*/

#ifndef ORDER_HPP_
    #define ORDER_HPP_
    #include <string>
    #include <iostream>
    #include <map>
    #include "PizzaEnum.hpp"

namespace Plazza {
    class Order {
        public:
            Order();
            Order(Plazza::PizzaType type, Plazza::PizzaSize size, std::size_t number);
            ~Order();

            //* Getters *//
            Plazza::PizzaType getType() const;
            std::string getName() const;
            Plazza::PizzaSize getSize() const;
            std::size_t getNumber() const;
            std::string getSizeName() const;

            //* Setters *//
            void setType(Plazza::PizzaType type);
            void setSize(Plazza::PizzaSize size);
            void setNumber(std::size_t number);

        protected:
        private:
            Plazza::PizzaType _pizzaType;
            Plazza::PizzaSize _pizzaSize;
            std::size_t _pizzaNumber;
            std::string _pizzaName;
            std::string _pizzaSizeName;
            // TODO Make it generic to use
            std::map<Plazza::PizzaType, std::string> pizzaNamesMap = {
                {Plazza::PizzaType::Regina, "regina"},
                {Plazza::PizzaType::Margarita, "margarita"},
                {Plazza::PizzaType::Americana, "americana"},
                {Plazza::PizzaType::Fantasia, "fantasia"}
            };
            std::map<Plazza::PizzaSize, std::string> pizzaSizesMap = {
                {Plazza::PizzaSize::S, "S"},
                {Plazza::PizzaSize::M, "M"},
                {Plazza::PizzaSize::L, "L"},
                {Plazza::PizzaSize::XL, "XL"},
                {Plazza::PizzaSize::XXL, "XXL"}
            };
    };
}

std::ostream& operator<<(std::ostream& os, const Plazza::Order& order);

#endif /* !ORDER_HPP_ */
