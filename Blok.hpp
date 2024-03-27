#pragma once
#include <SFML/Graphics.hpp>
struct Blok {
    sf::RectangleShape ksztalt;
    sf::Sprite wyglad;
    sf::Color kolor;
    Blok(sf::Vector2f const& wyglad,sf::Color const& kolor);
    void draw(sf::RenderWindow &okno);
};