#include <SFML/Graphics.hpp>
#include "Bullet.hpp"
Bullet::Bullet(int radius,int demage, int const&  speed, sf::Color kolor):predkosc(speed),demage(demage),walnela(false) {
    ksztalt.setRadius(radius);
    ksztalt.setFillColor(kolor);

};
