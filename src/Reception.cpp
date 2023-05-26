/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Plazza
*/

#include "Reception.hpp"

Plazza::Reception::Reception(Parsing &data) : _data(data)
{
    _receptionPid = getpid();
}

Plazza::Reception::~Reception()
{
}

void Plazza::Reception::start()
{
    std::string line;

    while (std::getline(std::cin, line)) {
        try {
            std::vector<std::array<std::string, 3>> stringOrder = splitInput(line);
            for (auto str : stringOrder) {
                Plazza::Order order = convertToOrder(str);
                dispatchOrder(order);
            }
            stringOrder.clear();
        } catch (const Error &error) {
            std::cout << error.what() << ": " << error.message() << "." << std::endl;
        }
    }
}

static Plazza::PizzaType getPizzaType(std::string &pizza)
{
    std::vector<std::string> pizzaType = {"margarita", "regina", "americana", "fantasia"};
    std::vector<Plazza::PizzaType> pizzaEnum = { Plazza::PizzaType::Margarita, Plazza::PizzaType::Regina, Plazza::PizzaType::Americana, Plazza::PizzaType::Fantasia};

    for (std::size_t i = 0; i != pizzaType.size(); i++) {
        if (toLower(pizza) == pizzaType[i]) {
            std::cout << pizzaType[i] << " = " << i << std::endl;
            return pizzaEnum[i];
        }
    }
    throw Error("Pizza Enum Not Found", pizza);
}

static Plazza::PizzaSize getPizzaSize(std::string &size)
{
    std::array<std::string, 5> pizzaSize = {"s", "m", "l", "xl", "xxl"};
    std::array<Plazza::PizzaSize, 5> sizeEnum = { Plazza::PizzaSize::S, Plazza::PizzaSize::M, Plazza::PizzaSize::L, Plazza::PizzaSize::XL, Plazza::PizzaSize::XXL};

    for (std::size_t i = 0; i != pizzaSize.size(); i++) {
        if (toLower(size) == pizzaSize[i])
            return sizeEnum[i];
    }
    throw Error("Pizza Size Not Found", size);
}

static int getPizzaNumber(std::string &number)
{
    number.erase(0, 1);
    return std::stoi(number);
}

Plazza::Order Plazza::Reception::convertToOrder(std::array<std::string, 3> stringOrder)
{
    Plazza::PizzaType type = getPizzaType(stringOrder.at(0));
    Plazza::PizzaSize size = getPizzaSize(stringOrder.at(1));
    int number = getPizzaNumber(stringOrder.at(2));
    return Plazza::Order(type, size, number);
}

void Plazza::Reception::create_kitchen()
{
    std::chrono::seconds workDuration(5);
    pid_t pid = fork();

    if (pid == -1)
        throw Error("Failed to fork", "fork");
    if (pid == 0) { // Child
        Kitchen kitchen(_data.getMultiplier(), _data.getNbCooks(), _data.getRefillTime(), _receptionPid);
        std::cout << "Kitchen closed" << std::endl;
    }
    else { // Parent
        _kitchenPids.push_back(pid);
        // std::cout << "from parent" << std::endl;
        // for (auto pid : _kitchenPids) {
        //     std::cout << pid << std::endl;
        // }
        // _msgQueue.sendCapacity(-1, pid);
        // _msgQueue.sendOrder(_orderList.at(0), _kitchenPids.at(0));
        // std::cout << "send to msg" << std::endl;
    }
}

std::vector<std::array<std::string, 3>> Plazza::Reception::splitInput(std::string &line)
{
    std::istringstream iss(line);
    std::vector<std::string> words;
    std::string word;
    std::vector<std::array<std::string, 3>> result;
    while (std::getline(iss, word, ';')) {
        std::istringstream iss1(word);
        while (std::getline(iss1, word, ' ')) {
            if (!word.empty())
                words.push_back(word);
        }
        _CheckError.checkVectorLength(3, words);
        _CheckError.checkReceiptArg(words);
        std::array<std::string, 3> tmp;
        for (int i = 0; i < words.size(); i++) {
            tmp[i] = words[i];
        }
        result.push_back(tmp);
        words.clear();
    }
    return result;
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

bool Plazza::Reception::needKitchen()
{
    return false;
}

void Plazza::Reception::dispatchOrder(Plazza::Order order)
{
    
}
