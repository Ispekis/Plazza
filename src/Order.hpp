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
    #include "plazza.hpp"

namespace Plazza {
    class Order {
        public:

            /**
             * @brief Construct a new Order object
             * 
             */
            Order();

            /**
             * @brief Construct a new Order object
             * 
             * @param type 
             * @param size 
             * @param amount 
             */
            Order(Plazza::PizzaType type, Plazza::PizzaSize size, std::size_t amount);

            /**
             * @brief Copy construct a new Order
             * 
             * @param other 
             */
            Order(const Plazza::Order &other);

            /**
             * @brief Destroy the Order object
             *
             */
            ~Order();

            //* Getters *//
            Plazza::PizzaType getType() const;
            Plazza::PizzaSize getSize() const;
            std::size_t getAmount() const;
            std::shared_ptr<Plazza::IPizza> getPizza() const;

            //* Setters *//
            void setType(Plazza::PizzaType type);
            void setSize(Plazza::PizzaSize size);
            void setAmount(std::size_t amount);

        protected:
        private:
            Plazza::PizzaType _pizzaType;
            Plazza::PizzaSize _pizzaSize;
            std::size_t _amount;
            std::shared_ptr<Plazza::IPizza> _pizzas;
    };
}

/**
 * @brief Deserialize to struct
 *
 * @param is
 * @param pizzaData
 * @return std::istream&
 */
std::istream& operator>>(std::istream &is, msg_data &msgData);


/**
 * @brief Serialize order
 *
 * @param os
 * @param order
 * @return std::ostream&
 */
std::ostream& operator<<(std::ostream& os, const Plazza::Order& order);

#endif /* !ORDER_HPP_ */
