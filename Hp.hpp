#pragma once
#include <SFML/Graphics.hpp>
struct Hp {
    sf::RectangleShape ksztalt;
    sf::Sprite wyglad;
    sf::Color kolor;
    bool czyUzyte;
    Hp(sf::Vector2f const& wyglad,sf::Color const& kolor);
    void draw(sf::RenderWindow &okno);
};

