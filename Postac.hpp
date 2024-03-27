#pragma once
#include <SFML/Graphics.hpp>
struct Postac {
    sf::RectangleShape ksztalt;
    sf::Sprite wyglad;
    int hp;
    int score;
    int boostStrzelania;
    sf::Vector2f ruch;
    Postac(sf::Vector2f const& rozmiar,int const& zycie,sf::Texture& tekstura);
    void draw(sf::RenderWindow &okno);
    void dd();
    sf::Clock klok;
    float predkosc;
};
