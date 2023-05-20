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

Plazza::Order::Order(Plazza::PizzaType type, Plazza::PizzaSize size, std::size_t number)
{
    this->setType(type);
    this->setSize(size);
    this->setNumber(number);
}

Plazza::Order::~Order()
{
}

Plazza::PizzaType Plazza::Order::getType() const
{
    return _pizzaType;
}

std::string Plazza::Order::getName() const
{
    return _pizzaName;
}

Plazza::PizzaSize Plazza::Order::getSize() const
{
    return _pizzaSize;
}

std::string Plazza::Order::getSizeName() const
{
    return _pizzaSizeName;
}

std::size_t Plazza::Order::getNumber() const
{
    return _pizzaNumber;
}

void Plazza::Order::setType(Plazza::PizzaType type)
{
    _pizzaType = type;
    auto iter = pizzaNamesMap.find(type);

    _pizzaName = iter->second;
    // std::cout << pizzaNamesMap[type] << std::endl;
    // _pizzaName = pizzaNamesMap[type];

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

void Plazza::Order::setNumber(std::size_t number)
{
    _pizzaNumber = number;
}

std::ostream &operator<<(std::ostream &os, const Plazza::Order &order)
{
    os << "Order : | " << order.getName() << "\t | " << order.getSizeName() << "\t | x" << order.getNumber() << " |";
    return os;
}