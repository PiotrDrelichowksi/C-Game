#pragma once
#include <vector>
#include <iostream>
#include "SFML/Graphics.hpp"

struct Teksty {
    std::vector<sf::Text> vectorTekstow;
    void draw(sf::RenderWindow& okienko);
    void updateTekst(int i, std::string nowyTekst);
    void ustawPozycje(int i,sf::Vector2f pozycja);

};
