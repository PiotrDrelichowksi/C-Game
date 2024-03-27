#pragma once
#include <SFML/Graphics.hpp>
#include "LaserZOczu.hpp"
struct Przeciwnik {
    int hp;
    int dmg;
    sf::Vector2f predkosc;
    sf::Vector2f ruch;
    LaserZOczu laser;
    sf::Clock czasStrzalu;
    sf::RectangleShape ksztalt;
    sf::Sprite wyglad;
    Przeciwnik(int hp, int dmg,sf::Vector2f predkosc,sf::Vector2f rozmiar,sf::Texture& tekstura);
    void draw(sf::RenderWindow &okno);
    void dd();
};