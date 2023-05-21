/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Cook
*/

#ifndef COOK_HPP_
    #define COOK_HPP_
    #include <cstddef>
    #include "Order.hpp"

namespace Plazza {
    class Cook {
        public:
            Cook();
            ~Cook();

            /**
             * @brief Check if the cook is overwhelmed of order
             *
             * @return true
             * @return false
             */
            bool isOverwhelmed();

            /**
             * @brief Number of order that the cook can take
             *
             * @return size_t
             */
            std::size_t availableOrderCapacity();

            /**
             * @brief Add a order to the cook
             *
             * @param order
             */
            void addOrder(Plazza::Order order);

        protected:
        private:
            std::size_t _orderCapacity = 2;
            std::vector<Plazza::Order> _orderList;
    };
}

#endif /* !COOK_HPP_ */
