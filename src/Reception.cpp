/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Plazza
*/

#include "Reception.hpp"

Plazza::Reception::Reception(Parsing &data) : _data(data)
{
}

Plazza::Reception::~Reception()
{
}

void Plazza::Reception::start()
{
    std::string line;

    while (std::getline(std::cin, line)) {
        parsingInput(line);
    }
}

static Plazza::PizzaType getPizzaType(std::string &pizza)
{
    std::vector<std::string> pizzaType = {"regina", "margarita", "america", "fantasia"};
    std::vector<Plazza::PizzaType> pizzaEnum = { Plazza::PizzaType::Regina, Plazza::PizzaType::Margarita, Plazza::PizzaType::Americana, Plazza::PizzaType::Fantasia};

    for (std::size_t i = 0; i != pizzaType.size(); i++) {
        if (pizzaType[i].compare(pizza))
            return pizzaEnum[i];
    }
    throw Error("Pizza Enum Not Found", pizza);
}

static Plazza::PizzaSize getPizzaSize(std::string &size)
{
    std::array<std::string, 5> pizzaSize = {"S", "M", "L", "XL", "XXL"};
    std::array<Plazza::PizzaSize, 5> sizeEnum = { Plazza::PizzaSize::S, Plazza::PizzaSize::M, Plazza::PizzaSize::L, Plazza::PizzaSize::XL, Plazza::PizzaSize::XXL};

    for (std::size_t i = 0; i != pizzaSize.size(); i++) {
        if (pizzaSize[i].compare(size) == 0)
            return sizeEnum[i];
    }
    throw Error("Pizza Size Not Found", size);
}

static int getPizzaNumber(std::string &number)
{
    number.erase(0, 1);
    return std::stoi(number);
}

void Plazza::Reception::parseEnum()
{
    for (auto a : _receiptList) {
        PizzaType type = getPizzaType(a[0]);
        PizzaSize size = getPizzaSize(a[1]);
        int number = getPizzaNumber(a[2]);
        Plazza::Order new_order(type, size, number);
        _orderList.push_back(new_order);
    }
}

void Plazza::Reception::splitInput(std::string &line)
{
    std::istringstream iss(line);
    std::vector<std::string> words;
    std::string word;
    _receiptList.clear();
    while (std::getline(iss, word, ';')) {
        std::istringstream iss1(word);
        while (std::getline(iss1, word, ' ')) {
            if (!word.empty())
                words.push_back(word);
        }
        _CheckError.checkVectorLength(3, words);
        _CheckError.checkReceiptArg(words);
        _receiptList.push_back(words);
        words.clear();
    }
    parseEnum();
    for (auto order : _orderList) {
        std::cout << "Order : | " << order.getName() << "\t | " << order.getSizeName() << "\t | x" << order.getNumber() << " |" << std::endl;
        // std::cout << order << std::endl;
    }
}

static void printVector(std::vector<std::vector<std::string>> &vector)
{
    for (auto& row : vector) {
        for (auto& element : row) {
            std::cout << "[ " << element << " ] ";
        }
        std::cout << std::endl;
    }
}

void Plazza::Reception::parsingInput(std::string &line)
{
    try {
        splitInput(line);
    } catch (const Error &error) {
        std::cout << error.what() << ": " << error.message() << "." << std::endl;
    }
    // printVector(_receiptList);
}