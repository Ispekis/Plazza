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

void Plazza::Reception::userInput()
{
    std::string line;
    while (std::getline(std::cin, line))
    {
        if (parsingInput(line)) {
            // dispatchOrder();
            // Create new kitchen if there is not
            manageKitchen();
            // kitchens receive orders
            // std::cout << "Kitchen size:" << _kitchenPids.size() << std::endl;
        }
    }
}

void Plazza::Reception::start()
{
    auto closingKitchen = std::thread(&Plazza::Reception::closeKitchen, std::ref(*this));
    userInput();
    closingKitchen.join();
}

void Plazza::Reception::closeKitchen()
{
    while (1) {
    auto closedPid = _msgQueue.recvClosure(0);
    for (std::size_t i = 0; i != _kitchenPids.size(); i++)
        if (_kitchenPids[i] == closedPid) {
            _kitchenPids.erase(_kitchenPids.begin() + i);
            break;
        }
    }
}

int Plazza::Reception::getCapacityLeft(int pid)
{
    _msgQueue.sendCapacity(0 , pid);
    // std::cout << "Capacity left" << _msgQueue.recvCapacity((int)getpid()) << " pid :" << pid << std::endl;
    return _msgQueue.recvCapacity((int)getpid());
}

void Plazza::Reception::sendPizzaToKitchen(int pid)
{

}

void Plazza::Reception::manageKitchen()
{
    if (_kitchenPids.size() == 0)
    {
        create_kitchen();
    }
    while (_orderList.size() != 0) {
        for (int i = 0; i != _kitchenPids.size(); i++) {
        int Capacity = getCapacityLeft(_kitchenPids[i]);
        if (Capacity != 0)
            sendPizzaToKitchen(Capacity);
        }
        break;
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
        Plazza::Order new_order(type, size, number);
        _orderList.push_back(new_order);
    }
}

void Plazza::Reception::create_kitchen()
{
    std::chrono::seconds workDuration(5);
    Process child;
    pid_t pid = child.spawnChildProcess();

    if (pid == 0)
    { // Child
        Kitchen kitchen(_data.getMultiplier(), _data.getNbCooks(), _data.getRefillTime(), _receptionPid);
        kitchen.~Kitchen();
        exit(0);
    }
    else { // Parent
        _kitchenPids.push_back(pid);
        std::cout << "Parent Pid :" << pid << std::endl;
        // std::cout << "Parent Pid :" << getpid() << std::endl;
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

bool Plazza::Reception::needKitchen()
{
    return false;
}

void Plazza::Reception::dispatchOrder()
{

}
