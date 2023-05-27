/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Factory
*/

#include "Factory.hpp"

Factory::Factory(std::string file, float mult)
{
    setConfigFile(file, mult);
}

Factory::~Factory()
{
    _file.close();
}

void Factory::setConfigFile(std::string configFile, float mult)
{
    if (_file.is_open())
        _file.close();

    _configFile = configFile;

    _file.open(_configFile);

    if (_file.fail()) {
        setPizzaDefault(mult);
    }
    setPizzaByFile(mult);
}

void Factory::setPizzaDefault(float mult)
{
    std::vector<int> pizzaEnum = { 1, 2, 8, 4};
    std::vector<std::string> pizzaName = {"margarita", "regina", "fantasia", "americana"};
    std::vector<std::vector<std::string>> pizzaIngredients = {{"dough","tomato","gruyere"}, {"dough","tomato","gruyere","ham","mushrooms"}, {"dough","tomato","eggplant","goat_cheese","chief_love"}, {"dough","tomato","gruyere","steak"}};
    std::vector<float> cookTime = {1, 2, 4, 2};

    _ingredients = {"dough","tomato","gruyere","ham","mushrooms","steak","eggplant","goat_Cheese","chief_Love"};
    for (int i = 0; i != pizzaName.size(); i++) {
        std::shared_ptr<Plazza::IPizza> _pizza = std::make_shared<Plazza::Pizza>();

        _pizza.get()->setBakeTime(cookTime[i] * mult);
        _pizza.get()->setIngredients(pizzaIngredients[i]);
        _pizza.get()->setType(pizzaEnum[i]);
        _pizzaInfo[pizzaName[i]] = _pizza;
    }
}

void Factory::setPizzaByFile(float mult)
{
}