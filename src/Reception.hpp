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

            /**
             * @brief Run the Reception
             * 
             */
            void start();

            /**
             * @brief Convert userInput into order
             * 
             * @param allOrder 
             */
            void convertToOrder(std::vector<std::array<std::string, 3>> &allOrder);

            /**
             * @brief Convert input into order
             * 
             * @param line 
             * @return true 
             * @return false 
             */
            bool parsingInput(std::string &line);

            /**
             * @brief Split input into parsable data
             * 
             * @param line 
             */
            void splitInput(std::string &line);
            /**
             * @brief Loop for user input from the std::cin
             * 
             */
            void userInput();

            void create_kitchen();
            void manageKitchen();
            void sendPizzaToKitchen(int Capacity, int KitchenPid);

        protected:
        private:
            /**
             * @brief Get the capacity left of the kitchenPid
             * 
             * @param pid 
             * @return int 
             */
            int getCapacityLeft(int kitchenPid);
             
            /**
             * @brief Check if a restaurant has closed
             *
             */
            void checkClosures();


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
