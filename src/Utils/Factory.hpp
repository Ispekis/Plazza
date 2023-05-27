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
    #include "IPizza.hpp"
    #include "Pizza.hpp"

class Factory {
    public:
        Factory(std::string _file, float mult);
        ~Factory();

        void setPizzaDefault(float mult);
        void setPizzaByFile(float mult);
        void setConfigFile(std::string configFile, float mult);

    protected:
    private:
        std::ifstream _file;
        std::vector<std::string> _ingredients;
        std::string _configFile;
        std::map<std::string, std::shared_ptr<Plazza::IPizza>> _pizzaInfo;
};

#endif /* !FACTORY_HPP_ */
