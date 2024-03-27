#include "Przeciwnik.hpp"
Przeciwnik::Przeciwnik(int hp, int dmg,sf::Vector2f predkosc,sf::Vector2f rozmiar,sf::Texture& tekstura):hp(hp),dmg(dmg),predkosc(predkosc),
                                                                                                         laser(LaserZOczu(sf::Vector2f (5,15),5,2,sf::Color::Red)){
    ksztalt.setSize(rozmiar);
    wyglad.setTexture(tekstura);
}
void Przeciwnik::draw(sf::RenderWindow &okno) {
    //okno.draw(ksztalt);
    okno.draw(wyglad);
}
void Przeciwnik::dd() {
    ruch.x=0;
    ruch.y+=predkosc.y;

    ruch.x+=predkosc.x;

}