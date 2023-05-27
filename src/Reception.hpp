/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Plazza
*/

#ifndef RECEPTION_HPP_
    #define RECEPTION_HPP_
    #include "Process.hpp"
    #include "Order.hpp"
    #include "Parsing.hpp"
    #include "ErrorHandling.hpp"
    #include <sstream>
    #include <iostream>
    #include <tuple>
    #include <vector>
    #include "Kitchen.hpp"
    #include <array>
    #include <string>
    #include <unistd.h>
    #include <chrono>
    #include "MessageQueue.hpp"
    #include <sys/select.h>
    

namespace Plazza {
    class Reception {
        public:
            Reception(Parsing &data);
            ~Reception();

            void start();
            void convertToOrder(std::vector<std::array<std::string, 3>> &allOrder);

            /**
             * @brief Seprate orders
             *
             * @param line
             * @return std::vector<std::array<std::string, 3>>
             */

            bool parsingInput(std::string &line);
            void splitInput(std::string &line);
            void create_kitchen();

            void manageKitchen();
            void parseOrder(std::vector<std::array<std::string, 3>> order);
            void sendPizzaToKitchen(int Capacity, int KitchenPid);

        protected:
        private:
            int getCapacityLeft(int pid);
             
            /**
             * @brief Check if a restaurant has closed
             *
             */
            void checkClosures();

            /**
             * @brief Check if the reception needs more kitchen
             *
             * @return true
             * @return false
             */
            bool needKitchen();

            /**
             * @brief dispatch orders
             *
             */
            void dispatchOrder(Plazza::Order order);

            void userInput();

            Parsing _data;
            ErrorHandling _CheckError;
            pid_t _receptionPid = 0;
            std::vector<int> _kitchenPids;
            std::vector<Order> _orderList;
            // Message Queues for ipc
            MessageQueue<msg_data> _orderMsgQ;
            MessageQueue<closure_data> _closureMsgQ;
            MessageQueue<capacity_data> _capacityMsgQ;

            // Keys for ipc
            key_t _orderKey;
            key_t _capacityKey;
            key_t _closureKey;
    };
}
#endif /* !PLAZZA_HPP_ */
