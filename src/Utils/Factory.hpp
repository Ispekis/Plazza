/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Factory
*/

#ifndef FACTORY_HPP_
#define FACTORY_HPP_
    #include <fstream>
    #include <iostream>
    #include <memory>
    #include <map>
    #include <sstream>
    #include "IPizza.hpp"
    #include "Pizza.hpp"

class Factory {
    public:
        Factory(std::string _file);
        ~Factory();

        void setPizzaDefault();
        void setPizzaByFile();
        void setConfigFile(std::string configFile);

        void fillPizza(std::string line);

        std::vector<std::string> getPizzaList() const;
        std::vector<std::string> getAllIngredient() const;
        std::shared_ptr<Plazza::IPizza> getPizza(std::string pizza) const;
    protected:
    private:
        std::vector<std::string> _pizzaList;
        std::ifstream _file;
        std::vector<std::string> _ingredients;
        std::string _configFile;
        std::map<std::string, std::shared_ptr<Plazza::IPizza>> _pizzaInfo;
};

#endif /* !FACTORY_HPP_ */
