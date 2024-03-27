#pragma once

#include "SFML/Graphics.hpp"

struct LaserZOczu {
    sf::Vector2f wielkosc;
    sf::RectangleShape ksztalt;
    int demage;
    int predkosc;
    sf::Color kolor;
    float kat;
    bool walnela;
    LaserZOczu(sf::Vector2f wielkosc,int demage,int const& speed, sf::Color kolor);
};
