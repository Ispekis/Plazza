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
    #include "IPizza.hpp"
    #include "Pizza/Regina.hpp"
    #include "Pizza/Americana.hpp"
    #include "Pizza/Fantasia.hpp"
    #include "Pizza/Margarita.hpp"
    #include <memory>

namespace Plazza {
    class Order {
        public:
            Order();
            Order(Plazza::PizzaType type, Plazza::PizzaSize size);
            ~Order();

            //* Getters *//
            Plazza::PizzaType getType() const;
            std::string getName() const;
            Plazza::PizzaSize getSize() const;
            std::string getSizeName() const;
            std::shared_ptr<Plazza::IPizza> getPizza() const;

            //* Setters *//
            void setType(Plazza::PizzaType type);
            void setSize(Plazza::PizzaSize size);

        protected:
        private:
            Plazza::PizzaType _pizzaType;
            Plazza::PizzaSize _pizzaSize;
            std::string _pizzaName;
            std::string _pizzaSizeName;
            std::shared_ptr<Plazza::IPizza> _pizzas;
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
