/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Plazza
*/

#include "Reception.hpp"

Plazza::Reception::Reception(Parsing &data) : _data(data)
{
    _receptionPid = Process::getpid();
    _orderMsgQ.createIpc(IPC::ftok(".", ORDER_KEY));
    _closureMsgQ.createIpc(IPC::ftok(".", CLOSURE_KEY));
    _capacityMsgQ.createIpc(IPC::ftok(".", CAPACITY_KEY));
}

Plazza::Reception::~Reception()
{
    _closingKitchen.join();
    _receiveReadyOrder.join();
}

void Plazza::Reception::sendPizzaToKitchen(int Capacity, int KitchenPid)
{
    int pizzaToRemove = Capacity;
    auto &singleOrderList = _orderList.at(0);
    int pizzaQty = singleOrderList.getAmount();

    // Set the Quantity of pizza that we can sent to the kitchen
    if (Capacity >= pizzaQty)
        pizzaToRemove = pizzaQty;
    Plazza::Order orderToSend = _orderList.at(0); // Do a copy the Order that is going to be sent
    orderToSend.setAmount(pizzaToRemove);

    // prepare struct data
    msg_data data;
    data = Plazza::Order::pack(orderToSend);

    _orderMsgQ.push(data, KitchenPid);
    std::cout << "[Reception] : Kitchen " << KitchenPid << ", make me " << pizzaToRemove << " " << orderToSend.getPizza()->getName() << " " << orderToSend.getSize() << "." << std::endl;
    singleOrderList.setAmount(pizzaQty - pizzaToRemove);

    // If there is no pizza Left in the order remove the order
    if (singleOrderList.getAmount() == 0)
        _orderList.erase(_orderList.begin());
}

void Plazza::Reception::manageKitchen()
{
    while (_orderList.size() != 0) {
        for (std::size_t i = 0; i != _kitchenPids.size(); i++) {
            int Capacity = getCapacityLeft(_kitchenPids.at(i));
            if (Capacity != 0) {
                sendPizzaToKitchen(Capacity, _kitchenPids.at(i));
            }
            if (_orderList.size() == 0)
                break;
        }
        if (_orderList.size() == 0)
                break;
        create_kitchen();
    }
}

void Plazza::Reception::create_kitchen()
{
    pid_t pid = Process::fork();
    if (pid == -1) {
        throw Error("Failed to fork", "Reception");
    }
    if (pid == 0) { // Child
        Kitchen kitchen(_data.getMultiplier(), _data.getNbCooks(), _data.getRefillTime(), _receptionPid);
        kitchen.~Kitchen();
        Platform::exit(0);
    } else { // Parent
        _kitchenPids.push_back(pid);
    }
}

static void receiveOrderMessage(Plazza::Order order)
{
    std::cout << "[Reception] : I have a " << order.getPizza()->getName() << " " << order.getSize() << " ready to go !" << std::endl;
}

void Plazza::Reception::receiveReadyOrder()
{
    while (_isRunning) {
        std::unique_ptr<msg_data> data = _orderMsgQ.pop(Process::getpid(), 0);
        if (data != nullptr) {
            Plazza::Order order;
            order = Plazza::Order::unpack(*data);
            receiveOrderMessage(order);
        }
    }
}

bool Plazza::Reception::parsingInput(std::string &line)
{
    try {
        splitInput(line);
    }
    catch (const Error &error) {
        std::cout << error.what() << ": " << error.message() << "." << std::endl;
        return false;
    }
    return true;
}

void Plazza::Reception::userInput()
{
    std::string line;
    while (std::getline(std::cin, line)) {
        if (parsingInput(line))
            manageKitchen();
    }
}

void Plazza::Reception::start()
{
    _closingKitchen = std::thread(&Plazza::Reception::checkClosures, std::ref(*this));
    _receiveReadyOrder = std::thread(&Plazza::Reception::receiveReadyOrder, std::ref(*this));
    userInput();
}

int Plazza::Reception::getCapacityLeft(int pid)
{
    capacity_data data;
    std::memset(&data, 0, sizeof(data));
    _capacityMsgQ.push(data, pid);

    std::unique_ptr<capacity_data> a = nullptr;

    while (a == nullptr)
        a = _capacityMsgQ.pop(Process::getpid(), IPC_NOWAIT);
    std::cout << "[Reception] : Got it Kitchen " << pid << " !" << std::endl;
    return a->value;
}

static Plazza::PizzaType getPizzaType(std::string &pizza)
{
    std::vector<std::string> pizzaType = {"margarita", "regina", "americana", "fantasia"};
    std::vector<Plazza::PizzaType> pizzaEnum = { Plazza::PizzaType::Margarita, Plazza::PizzaType::Regina, Plazza::PizzaType::Americana, Plazza::PizzaType::Fantasia};

    for (std::size_t i = 0; i != pizzaType.size(); i++) {
        if (toLower(pizza) == pizzaType[i]) {
            // std::cout << pizzaType[i] << " = " << i << std::endl;
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

void Plazza::Reception::convertToOrder(std::vector<std::array<std::string, 3>> &allOrder)
{
    for (auto singleOrder : allOrder) {
        Plazza::PizzaType type = getPizzaType(singleOrder.at(0));
        Plazza::PizzaSize size = getPizzaSize(singleOrder.at(1));
        int number = getPizzaNumber(singleOrder.at(2));
        _orderList.push_back(Plazza::Order(type, size, number));
    }
    allOrder.clear();
}

void Plazza::Reception::splitInput(std::string &line)
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
        for (std::size_t i = 0; i < words.size(); i++) {
            tmp[i] = words[i];
        }
        result.push_back(tmp);
        words.clear();
    }
    convertToOrder(result);
}

void Plazza::Reception::checkClosures()
{
    // Trying to read closure message and close Kitchen
    while (_isRunning) {
        auto closedPid = _closureMsgQ.pop(Process::getpid(), IPC_NOWAIT);
        if (closedPid != nullptr)
            for (std::size_t i = 0; i != _kitchenPids.size(); i++)
                if (closedPid->id == _kitchenPids.at(i)) {
                    _kitchenPids.erase(_kitchenPids.begin() + i);
                    std::cout << RED << "[Reception] : Kitchen " << closedPid->id << " has closed"<< COLOR <<std::endl;
                    break;
                }
    }
}