#include "LaserZOczu.hpp"
LaserZOczu::LaserZOczu(sf::Vector2f wielkosc,int demage,int const& speed, sf::Color kolor):predkosc(speed),demage(demage),walnela(false),kat(90) {
    ksztalt.setSize(wielkosc);
    ksztalt.setFillColor(kolor);

};