/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Pizza
*/

#ifndef PIZZA_HPP_
    #define PIZZA_HPP_
    #include "IPizza.hpp"

namespace Plazza {
    class Pizza : public Plazza::IPizza {
        public:
            Pizza();
            ~Pizza();

            // void setBakeTime(int time);
            // void setIngredients(std::vector<std::string> ingredients);
            int getBakeTime();
            std::vector<std::string> getIngredients();
            std::string getName();

        protected:
            std::string _name = "pizza";
            std::vector<std::string> _ingredients;
            int _bakeTime = 0;
        private:
    };
}

#endif /* !PIZZA_HPP_ */
