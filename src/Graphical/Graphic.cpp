/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Graphic
*/

#include "Graphic.hpp"

Graphic::Graphic(int capacityMax) : _window(sf::VideoMode(1920, 1080), "Plazza"), _capacityMax(capacityMax)
{
    // const char *path[] = {"assets/four.png", "assets/background.jpg"};
    // int size = sizeof(path) / sizeof(char *);
    // for (int i = 0; i != size; i++) {
    //     sf::Texture texture;
    //     if (!texture.loadFromFile(path[i])) {
    //         std::cout << "error load:" << path[i] << std::endl;
    //     }
    //     sf::Sprite sprite;
    //     sprite.setTexture(texture);
    //     _window.draw(sprite);
    // }
    _capacityKey = ftok(".", CAPACITY_KEY);
    try
    {
        loadSpriteFromFile("assets/background.jpg", _backgroundS, _backgroundT);
        loadSpriteFromFile("assets/four.png", _hovenS, _hovenT);
        _backgroundS.setScale(3.f, 3.f);
        _hovenS.setScale(2.5f, 2.5f);
    }
    catch (const Error &e)
    {
    std::cout << e.what() << ":" << e.message() << std::endl;
    }
}

void Graphic::loadSpriteFromFile(std::string path, sf::Sprite &sprite, sf::Texture &texture)
{
    if (!texture.loadFromFile(path))
        throw Error("Error Loading Sprite", path);
    sprite.setTexture(texture);
}

Graphic::~Graphic()
{
}

void Graphic::event()
{
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            _window.close();
    }
}

void Graphic::drawKitchen()
{
    int x = 0;
    int y = 0;
    int size = _kitchen->size();
    for (int i = 0; i != size; i++)
    {
        _hovenS.setPosition(x, y);
        _window.draw(_hovenS);
        drawCooks(x, y, 100, _kitchen->at(i));
        x += 100 * 2.5;
        if (x >= 1920 - 100*2.5) {
            x = 0;
            y += 100*2.5;
        }
    }
}

void Graphic::draw()
{
    _window.clear();
    _window.draw(_backgroundS);
    drawKitchen();
    _window.display();
}

void Graphic::run()
{
    while (_window.isOpen()) {
        event();
        draw();
    }
}

void Graphic::setKitchen(std::shared_ptr<std::vector<int>> kitchen)
{
    _kitchen = kitchen;
}

void Graphic::drawCooks(int x, int y, int sizes, int pid)
{
    float size = 10;
    sf::RectangleShape rect(sf::Vector2f(size, size));
    int tmpX = x;
    int tmpY = y;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        capacity_data data;
    std::memset(&data, sizeof(data), 0);
    _capacityMsgQ.push(data, pid, _capacityKey);

    std::unique_ptr<capacity_data> a = nullptr;

    while (a == nullptr)
        a = _capacityMsgQ.pop(getpid(), _capacityKey, IPC_NOWAIT);
    int capacityLeft = _capacityMax - a->value;

    for (int i = 0; i != _capacityMax; i++)
    {
        rect.setPosition(tmpX + size * 2.5, tmpY+ size * 2.5);

        if (i < capacityLeft)
            rect.setFillColor(sf::Color::Red);
        else 
            rect.setFillColor(sf::Color::Green);
        _window.draw(rect);
        tmpX += size * 2.5;
        if (tmpX >= x + sizes * 2.5 - size * 2.5) {
            tmpX = x;
            tmpY += size * 2.5;
        }
    }
}