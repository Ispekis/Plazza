/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** ErrorHandling
*/

#include "ErrorHandling.hpp"

ErrorHandling::ErrorHandling()
{
}

ErrorHandling::~ErrorHandling()
{
}

template<typename U>
void ErrorHandling::checkVectorLength(std::size_t size, std::vector<U> &vector)
{
    if ((vector.size()) != size)
        throw Error("Vector", "BadLength");
}

std::string toLower(std::string &str)
{
    std::string res = str;
    std::transform(res.begin(), res.end(), res.begin(),
    [](unsigned char c)
    {
        return std::tolower(c);
    });
    return res;
}

static void findType(std::string word, std::vector<std::string>wordList)
{
    for (std::size_t i = 0; i != wordList.size(); i++)
        if (toLower(word) == wordList[i])
            return;
    throw Error("Pizza Not found", word);
}

static void findSize(std::string word, std::vector<std::string>wordList)
{
    for (std::size_t i = 0; i != wordList.size(); i++)
        if (toLower(word) == wordList[i])
            return;
    throw Error("Invalid Pizza size", word);
}

static void findNumber(std::string word)
{
    if (word[0] != 'x' || word.size() == 1)
        throw Error("Invalid Number", word);
    for (std::size_t i = 1; i != word.size() - 1; i++)
    {
        if (std::isdigit(word[i]) == true) {
            if (word[i] == '0' && i == 1)
                throw Error("Invalid Number", word);
        }
        else 
            throw Error("Invalid Number", word);
    }

}

void ErrorHandling::checkReceiptArg(std::vector<std::string> words)
{
    std::vector<std::string> pizza = {"regina", "margarita", "americana", "fantasia"};
    std::vector<std::string> size = {"s", "m", "l", "xl", "xxl"};

    findType(words[0], pizza);
    findSize(words[1], size);
    findNumber(words[2]);
}

template void ErrorHandling::checkVectorLength(std::size_t size, std::vector<std::string> &vector);
template void ErrorHandling::checkVectorLength(std::size_t size, std::vector<int> &vector);