#include "Teksty.hpp"


void Teksty::draw(sf::RenderWindow& okienko) {
    for (auto& tekst:vectorTekstow) {
        okienko.draw(tekst);
    }

}
void Teksty::updateTekst(int i, std::string nowyTekst){
    vectorTekstow[i].setString(nowyTekst);
}
void Teksty::ustawPozycje(int i,sf::Vector2f pozycja){
    vectorTekstow[i].setPosition(pozycja);
}
