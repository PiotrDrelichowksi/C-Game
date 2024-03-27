#pragma once

#include "Blok.hpp"

struct Kolce: Blok {
    int dmg;
    Kolce(sf::Vector2f const& wyglad,sf::Color const& kolor);
};
