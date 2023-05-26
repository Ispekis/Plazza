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

std::map<std::string, std::pair<std::vector<std::string>, int>> Factory::Factory::getConfigData()
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
    std::vector<std::string> pizzaType = {"margarita", "regina", "fantasia", "americana"};
    std::vector<std::vector<std::string>> pizzaIngredients = {{"dough","tomato","gruyere"}, {"dough","tomato","gruyere","ham","mushrooms"}, {"dough","tomato","eggplant","goat_cheese","chief_love"}, {"dough","tomato","gruyere","steak"}};
    std::vector<float> cookTime = {1, 2, 4, 2};

    for (int i = 0; i != pizzaType.size(); i++)
        _pizzaInfo[pizzaType[i]] = std::make_pair(pizzaIngredients[i], cookTime[i] * cook);
}

void Factory::storeConfigToMap(float cook)
{
    std::string line;

    while (std::getline(_file, line)) {
        if (line[0] != '#' && line.size() != 0) {
            std::stringstream ss(line);
            std::string name;
            std::string ingredient_s;
            std::vector<std::string> ingredients;
            std::string cookName;
            float cookTime;

            // Get the name
            ss >> name;

            // Then the ingredient
            ss >> ingredient_s;
            ingredients = fillIngredient(ingredient_s);

            ss >> cookName;
            cookTime = std::stof(cookName) * cook;

            _pizzaInfo[name] = std::make_pair(ingredients, cookTime);
        }
    }
}

