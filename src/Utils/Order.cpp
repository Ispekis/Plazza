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

Plazza::Order::Order(Plazza::PizzaType type, Plazza::PizzaSize size, std::size_t amount)
{
    this->setType(type);
    this->setSize(size);
    this->setAmount(amount);
}

Plazza::Order::Order(const Plazza::Order &other)
{
    this->_amount = other._amount;
    this->_pizzas = other._pizzas;
    this->_pizzaSize = other._pizzaSize;
    this->_pizzaType = other._pizzaType;
}

Plazza::Order::~Order()
{
}

Plazza::Order &Plazza::Order::operator=(const Plazza::Order &other)
{
    this->setType(other._pizzaType);
    this->setSize(other._pizzaSize);
    this->setAmount(other._amount);
    return *this;
}

Plazza::PizzaType Plazza::Order::getType() const
{
    return _pizzaType;
}

Plazza::PizzaSize Plazza::Order::getSize() const
{
    return _pizzaSize;
}

std::size_t Plazza::Order::getAmount() const
{
    return _amount;
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
}

void Plazza::Order::setAmount(std::size_t amount)
{
    _amount = amount;
}

msg_data &operator<<(msg_data &data, Plazza::Order order)
{
    std::memset(&data, 0, sizeof(data));

    data.type = order.getType();
    data.size = order.getSize();
    data.nbr = order.getAmount();
    return data;
}

Plazza::Order &operator>>(msg_data data, Plazza::Order &order)
{
    order = Plazza::Order(static_cast<Plazza::PizzaType>(data.type), static_cast<Plazza::PizzaSize>(data.size), data.nbr);
    return order;
}
