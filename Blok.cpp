#include "Blok.hpp"
Blok::Blok(sf::Vector2f const& wyglad, sf::Color const& kolor):kolor(kolor){
    ksztalt.setSize(wyglad);
}
void Blok::draw(sf::RenderWindow &okno){
    //okno.draw(ksztalt);
    okno.draw(wyglad);
}
