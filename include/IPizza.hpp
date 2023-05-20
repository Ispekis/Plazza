/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** IPizza
*/

#ifndef IPIZZA_HPP_
    #define IPIZZA_HPP_
    #include <vector>
    #include <string>

namespace Plazza {
    class IPizza {
        public:
            virtual ~IPizza() = default;

            /**
             * @brief Set the Bake Time in second
             *
             * @param time
             */
            // virtual void setBakeTime(int time) = 0;
            /**
             * @brief Set the Ingredients
             *
             * @param ingredients
             */
            // virtual void setIngredients(std::vector<std::string> ingredients) = 0;
            /**
             * @brief Get the Bake Time of the pizza in second
             *
             * @return int
             */
            virtual int getBakeTime() = 0;
            /**
             * @brief Get the Ingredients of pizza
             *
             * @return std::vector<std::string>
             */
            virtual std::vector<std::string> getIngredients() = 0;
            /**
             * @brief Get the Pizza's name
             *
             * @return std::string
             */
            virtual std::string getName() = 0;

        protected:
        private:
    };
}

#endif /* !IPIZZA_HPP_ */
