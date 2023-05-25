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
        if (parsingInput(line)) {
            // for (auto order : _orderList) {
            //     std::cout << order << std::endl;
            // }
            // Create new kitchen if there is not
            if (_kitchenPids.size() == 0) {
                create_kitchen();
            //     _msgQueue.push(_orderList.at(0));
            }
            // kitchens receive orders
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

void Plazza::Reception::parseEnum()
{
    for (auto a : _receiptList) {
        PizzaType type = getPizzaType(a[0]);
        PizzaSize size = getPizzaSize(a[1]);
        int number = getPizzaNumber(a[2]);
        for (int i = 0; i < number; i++) {
            Plazza::Order new_order(type, size);
            _orderList.push_back(new_order);
        }
    }
}

void Plazza::Reception::create_kitchen()
{
    std::chrono::seconds workDuration(5);
    pid_t pid = fork();

    if (pid == -1)
        throw Error("Failed to fork", "fork");
    if (pid == 0) { // Child
        // std::cout << "Kitchen start" << std::endl;
        Kitchen kitchen(_data.getMultiplier(), _data.getNbCooks(), _data.getRefillTime(), _receptionPid);
        // auto start = std::chrono::steady_clock::now();
        // while (true) {
        //     _msgQueue.pop(getpid());
        //     auto current =  std::chrono::steady_clock::now();
        //     auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(current - start);
        //     if (elapsed >= workDuration) {
        //         break;
        //     }
        // }
        std::cout << "Kitchen closed" << std::endl;
    }
    else { // Parent
        _kitchenPids.push_back(pid);
        // std::cout << "from parent" << std::endl;
        // for (auto pid : _kitchenPids) {
        //     std::cout << pid << std::endl;
        // }
        // _msgQueue.push(_orderList.at(0), _kitchenPids.at(0));
        // std::cout << "send to msg" << std::endl;
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

bool Plazza::Reception::parsingInput(std::string &line)
{
    try {
        splitInput(line);
    } catch (const Error &error) {
        std::cout << error.what() << ": " << error.message() << "." << std::endl;
        return false;
    }
    return true;
}