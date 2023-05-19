/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Plazza
*/

#include "Plazza.hpp"

Plazza::Plazza(Parsing &data) : _data(data)
{
}

Plazza::~Plazza()
{
}

void Plazza::runPlazza()
{
    std::string line;

    while (std::getline(std::cin, line)) {
        parsingInput(line);
    }
}

void Plazza::splitInput(std::string &line)
{
    std::istringstream iss(line);
    std::vector<std::string> words;
    std::string word;
    std::string tmp;
    std::vector<std::vector<std::string>> list;

    while (std::getline(iss, word, ';')) {
        std::istringstream iss1(word);
        while (std::getline(iss1, word, ' '))
            words.push_back(word);
        _CheckError.checkVectorLength(3, words);
        _CheckError.checkReceiptArg(words);
        list.push_back(words);
        words.clear();
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

void Plazza::parsingInput(std::string &line)
{
    std::vector<std::vector<std::string>> list;
    try {
        splitInput(line);
    } catch (const Error &error) {
        std::cout << error.what() << ": " << error.message() << "." << std::endl;
    } 
    printVector(list);
}