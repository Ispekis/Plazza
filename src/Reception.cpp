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
    _orderKey = ftok(".", ORDER_KEY);
    _closureKey = ftok(".", CLOSURE_KEY);
    _capacityKey = ftok(".", CAPACITY_KEY);
}

Plazza::Reception::~Reception()
{
}

void Plazza::Reception::userInput()
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

void Plazza::Reception::start()
{
    std::thread closingKitchen = std::thread(&Plazza::Reception::checkClosures, std::ref(*this));
    userInput();
    closingKitchen.join();
}

int Plazza::Reception::getCapacity(int pid)
{
    capacity_data data;
    std::memset(&data, sizeof(data), 0);
    _capacityMsgQ.push(data, pid, _capacityKey);

    std::unique_ptr<capacity_data> a = nullptr;

    while (a == nullptr)
        a = _capacityMsgQ.pop(getpid(), _capacityKey);
    std::cout << a->value << std::endl;
    return a->value;
}

void Plazza::Reception::checkClosures()
{
    while (true) {
        auto closedPid = _closureMsgQ.pop(getpid(), _closureKey);
        if (closedPid != nullptr)
            for (int i = 0; i != _kitchenPids.size(); i++)
                if (closedPid->id = _kitchenPids.at(i)) {
                    _kitchenPids.erase(_kitchenPids.begin() + i);
                    break;
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
    pid_t pid = fork();

    if (pid == -1)
        throw Error("Failed to fork", "fork");
    if (pid == 0) { // Child
        Kitchen kitchen(_data.getMultiplier(), _data.getNbCooks(), _data.getRefillTime(), _receptionPid);
        // std::cout << "Kitchen closed" << std::endl;
        exit(0);
    } else { // Parent
        _kitchenPids.push_back(pid);
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

static int getNeededKitchen(int dis, int max)
{
    int res = static_cast<int>(max / dis);

    double tmp = static_cast<float>(max) / dis - res;

    if (tmp > 0) {
        res++;
    }
    return res;
}

/**
 * @brief Serialize the order
 *
 * @param order
 * @return msg_data
 */
static msg_data serializeOrder(Plazza::Order order)
{
    msg_data data;

    std::memset(&data, sizeof(data), 0);

    // serialize data
    std::stringstream serializedStream;
    serializedStream << order;
    std::string serializedString = serializedStream.str();

    // Deserialize data to struct
    std::stringstream deserializedStream(serializedString);
    deserializedStream >> data;
    return data;
}

void Plazza::Reception::dispatchOrder(Plazza::Order order)
{
    int total_amount = order.getAmount();
    int amout_iter = MAX_COOK_PER_KITCHEN * _data.getNbCooks();

    // Get the total number of kitchens and substract the existing kitchen
    int needed_kitchen = getNeededKitchen(amout_iter, total_amount) - _kitchenPids.size();
    for (int i = 0; i < needed_kitchen; i++) {
        create_kitchen();
    }

    int tmp = total_amount;

        getCapacity(_kitchenPids.at(0));
    // for (int i = 0; i < _kitchenPids.size(); i++) {
    //     if (tmp < amout_iter) {
    //         order.setAmount(tmp);
    //         _orderMsgQ.push(serializeOrder(order), _kitchenPids.at(i), _orderKey);
    //     } else {
    //         tmp -= amout_iter;
    //         order.setAmount(amout_iter);
    //         _orderMsgQ.push(serializeOrder(order), _kitchenPids.at(i), _orderKey);
    //     }
    //     // getCapacity(_kitchenPids[i]);
    // }
}
