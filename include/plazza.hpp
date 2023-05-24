/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** plazza
*/

#ifndef PLAZZA_HPP_
    #define PLAZZA_HPP_

typedef struct pizza_data {
    long msg_type;
    std::string name;
    std::vector<std::string> ingredients;
    int bakeTime;
    int nbrIngredient;
    int type;
    int size;
} pizza_data;

#endif /* !PLAZZA_H_ */
