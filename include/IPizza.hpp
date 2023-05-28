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
             * @brief Set the type
             *
             * @param type
             */
            virtual void setType(int type) = 0;

            /**
             * @brief Set the Bake Time in second
             *
             * @param time
             */
            virtual void setBakeTime(float time) = 0;

            /**
             * @brief Set the Ingredients
             *
             * @param ingredients
             */
            virtual void setIngredients(std::vector<std::string> ingredients) = 0;

            /**
             * @brief Set the Name of Pizza
             *
             * @param name
             */
            virtual void setName(std::string name) = 0;

            /**
             * @brief Get the Name of the pizza
             *
             * @return string
             */
            virtual std::string getName() const = 0;

            /**
             * @brief Get the Bake Time of the pizza in second
             *
             * @return float
             */
            virtual float getBakeTime() const = 0;

            /**
             * @brief Get the Ingredients of pizza
             *
             * @return std::vector<std::string>
             */
            virtual std::vector<std::string> getIngredients() const = 0;

            /**
             * @brief Get the type of pizza
             *
             * @return int
             */
            virtual int getPizzaType() const = 0;
            // /**
            //  * @brief Serialize data
            //  *
            //  * @return pizza_data
            //  */
            // virtual pizza_data pack() = 0;

            // /**
            //  * @brief Unserialize data
            //  *
            //  * @param data
            //  */
            // virtual void unpack(pizza_data data) = 0;

        protected:
        private:
    };
}

#endif /* !IPIZZA_HPP_ */
