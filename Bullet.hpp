#pragma once
struct Bullet {
    int radius;
    sf::CircleShape ksztalt;
    int demage;
    int predkosc;
    sf::Color kolor;
    float kat;
    bool walnela;
    Bullet(int radius,int demage,int const& speed, sf::Color kolor);
};
