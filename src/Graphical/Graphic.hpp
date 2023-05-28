/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Graphic
*/

#include "Error.hpp"
#include "chrono"
#include "thread"
#include "plazza.hpp"
#include "MessageQueue.hpp"
#include <sys/types.h>
#include <unistd.h>
#include <memory>
#include "SFML/Graphics.hpp"
#include <iostream>
#include <map>
#ifndef GRAPHIC_HPP_
#define GRAPHIC_HPP_

#define HOVEN 0
#define BACKGROUND 1

class Graphic {
    public:
        Graphic(int capacityMax);
        ~Graphic();

        void run();
        void draw();
        void event();
        void drawKitchen();
        void drawCooks(int x, int y, int sizes, int pid);
        void loadSpriteFromFile(std::string path, sf::Sprite &sprite, sf::Texture &texture);
        void setKitchen(std::shared_ptr<std::vector<int>> kitchen);
        bool pidIsOn(int pid);

    protected:
    private:
        // std::map<int, sf::Sprite> _sprites;
        // std::map<int, sf::Texture> _texture;

        sf::Texture _hovenT;
        sf::Texture _backgroundT;
        sf::Sprite _backgroundS;
        sf::Sprite _hovenS;
        sf::RenderWindow _window;
        sf::Event _event;
        std::shared_ptr<std::vector<int>> _kitchen;
        int _capacityMax;

        Plazza::MessageQueue<capacity_data> _capacityMsgQ;
        key_t _capacityKey;

};

#endif /* !GRAPHIC_HPP_ */
