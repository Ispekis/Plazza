/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Order
*/

#include "Order.hpp"

Plazza::Order::Order()
{

}

Plazza::Order::Order(Plazza::PizzaType type, Plazza::PizzaSize size)
{
    this->setType(type);
    this->setSize(size);
}

Plazza::Order::~Order()
{
}

Plazza::PizzaType Plazza::Order::getType() const
{
    return _pizzaType;
}

Plazza::PizzaSize Plazza::Order::getSize() const
{
    return _pizzaSize;
}

std::string Plazza::Order::getSizeName() const
{
    return _pizzaSizeName;
}
std::shared_ptr<Plazza::IPizza> Plazza::Order::getPizza() const
{
    return _pizzas;
}

void Plazza::Order::setType(Plazza::PizzaType type)
{
    _pizzaType = type;

    // set pizza class
    switch (_pizzaType) {
        case Regina:
            _pizzas = std::make_shared<Plazza::ReginaPizza>();
            break;
        case Fantasia:
            _pizzas = std::make_shared<Plazza::FantasiaPizza>();
            break;
        case Americana:
            _pizzas = std::make_shared<Plazza::AmericanaPizza>();
            break;
        case Margarita:
            _pizzas = std::make_shared<Plazza::MargaritaPizza>();
            break;
    }
}

void Plazza::Order::setSize(Plazza::PizzaSize size)
{
    _pizzaSize = size;
    _pizzaSizeName = pizzaSizesMap[size];
}

std::ostream &operator<<(std::ostream &os, const Plazza::Order &order)
{

    // Serialize pizza
    os << *order.getPizza();
    os << order.getType() << "\n";
    os << order.getSize() << "\n";
    return os;
}

std::istream& operator>>(std::istream &is, pizza_data &pizzaData)
{
    // Deserialize pizza
    is >> pizzaData.name;
    is >> pizzaData.bakeTime;
    is >> pizzaData.nbrIngredient;
    std::vector<std::string> ings;
    std::string tmp;
    for (int i = 0; i < pizzaData.nbrIngredient; i++) {
        is >> tmp;
        ings.push_back(tmp);
    }
    pizzaData.ingredients = ings;

    // Deserialize others
    is >> pizzaData.type;
    is >> pizzaData.size;
    return is;
}