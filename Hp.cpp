#include "Hp.hpp"
Hp::Hp(sf::Vector2f const& wyglad, sf::Color const& kolor):kolor(kolor),czyUzyte(false){
    ksztalt.setSize(wyglad);
}
void Hp::draw(sf::RenderWindow &okno){
    //okno.draw(ksztalt);
    okno.draw(wyglad);
}
