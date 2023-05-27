/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-joseph.yu
** File description:
** Factory
*/

#include "Factory.hpp"

Factory::Factory(std::string configFile, float cook)
{
    setConfigFile(configFile, cook);
}

Factory::~Factory()
{
    _file.close();
}

std::map<std::string, std::shared_ptr<Plazza::IPizza>>Factory::Factory::getConfigData()
{
    return _pizzaInfo;
}

void Factory::setConfigFile(std::string configFile, float cook)
{
    if (_file.is_open()) {
        _file.close();
    }

    _configFile = configFile;

    _file.open(_configFile);

    if (_file.fail()) {
        setDefaultFile(cook);
    }
    storeConfigToMap(cook);
}

std::vector<std::string> fillIngredient(std::string line)
{
    std::vector<std::string> res;
    std::string tmp;
    std::stringstream ss(line);

    while (std::getline(ss, tmp, ','))
        res.push_back(tmp);
    return res;
}

void Factory::setDefaultFile(float cook)
{
    std::vector<Plazza::PizzaType> pizzaEnum = { Plazza::PizzaType::Margarita, Plazza::PizzaType::Regina, Plazza::PizzaType::Americana, Plazza::PizzaType::Fantasia};
    std::vector<std::string> pizzaName = {"margarita", "regina", "fantasia", "americana"};
    std::vector<std::vector<std::string>> pizzaIngredients = {{"dough","tomato","gruyere"}, {"dough","tomato","gruyere","ham","mushrooms"}, {"dough","tomato","eggplant","goat_cheese","chief_love"}, {"dough","tomato","gruyere","steak"}};
    std::vector<float> cookTime = {1, 2, 4, 2};

    for (int i = 0; i != pizzaName.size(); i++) {
        std::shared_ptr<Plazza::IPizza> _pizza;

        _pizza.get()->setBakeTime(cookTime[i] * cook);
        _pizza.get()->setIngredients(pizzaIngredients[i]);
        _pizza.get()->setType(pizzaEnum[i]);
        _pizzaInfo[pizzaName[i]] = _pizza;
    }
}

void Factory::storeConfigToMap(float cook)
{
    std::string line;

    while (std::getline(_file, line)) {
        if (line[0] != '#' && line.size() != 0) {
            std::stringstream ss(line);
            std::string name;
            std::string ingredient_s;
            std::string type;
            std::string cookName;
            std::shared_ptr<Plazza::IPizza> _pizza;

            ss >> type;
            _pizza.get()->setType(static_cast<Plazza::PizzaType>(std::stoi(type)));

            // Get the name
            ss >> name;

            // Then the ingredient
            ss >> ingredient_s;
            _pizza.get()->setIngredients(fillIngredient(ingredient_s));

            ss >> cookName;
            _pizza.get()->setBakeTime(std::stof(cookName) * cook);

            _pizzaInfo[name] = _pizza;
        }
    }
}

