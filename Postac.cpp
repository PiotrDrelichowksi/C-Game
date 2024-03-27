#include "Postac.hpp"
#include "iostream"
Postac::Postac(sf::Vector2f const& rozmiar,int const& zycie,sf::Texture& tekstura):hp(zycie),predkosc(3),score(0),boostStrzelania(0){

    ksztalt.setSize(rozmiar);
    wyglad.setTexture(tekstura);


}

void Postac::draw(sf::RenderWindow &okno) {
    //okno.draw(ksztalt);
    okno.draw(wyglad);
}

void Postac::dd() {
    ruch.x=0;
    ruch.y+=predkosc/23;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        ruch.x+=predkosc;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        ruch.x-=predkosc;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&klok.getElapsedTime().asSeconds()>0.8) {
        ruch.y-=predkosc*3;
        klok.restart();
    }

}