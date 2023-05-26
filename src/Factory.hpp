/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Factory
*/

#ifndef CONFHANDLER_HPP_
    #define CONFHANDLER_HPP_
    #include <string>
    #include <fstream>
    #include <iostream>
    #include <sstream>
    #include <map>
    #include <vector>

class Factory {
    public:
        Factory(std::string configFile, float cook);
        ~Factory();

        void setConfigFile(std::string configFile, float cook);
        void setDefaultFile(float cook);

        std::map<std::string, std::pair<std::vector<std::string>, int>> getConfigData();

        class ConfHandlerError : public std::exception {
            public:
                ConfHandlerError(std::string message) {
                    _message = message;
                }
                virtual const char* what() const noexcept {
                    return _message.c_str();
            }
            private:
                std::string _message;
        };
    protected:
    private:
        void storeConfigToMap(float cook);
        std::string _configFile;
        std::ifstream _file;
        std::map<std::string, std::pair<std::vector<std::string>, int>> _pizzaInfo;
};

#endif /* !CONFHANDLER_HPP_ */
