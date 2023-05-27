/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** plazza
*/

#ifndef PLAZZA_HPP_
    #define PLAZZA_HPP_
    #define ORDER_KEY 65
    #define CAPACITY_KEY 66
    #define CLOSURE_KEY 67
    #define MAX_COOK_PER_KITCHEN 2

    #define RED "\033[31m"
    #define GREEN "\033[32m"
    #define YELLOW "\033[33m"
    #define BLUE "\033[34m"
    #define MAGENTA "\033[35m"
    #define CYAN "\033[36m"
    #define COLOR "\033[0m"

typedef struct msg_data {
    long mesg_type;
    int type;
    int size;
    int nbr;
} msg_data;

typedef struct capacity_data {
    long mesg_type;
    int value;
} capacity_data;

typedef struct closure_data {
    long mesg_type;
    int id;
} closure_data;

#endif /* !PLAZZA_H_ */
