#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Postac.hpp"
#include "Blok.hpp"
#include "Bullet.hpp"
#include "Przeciwnik.hpp"
#include <cmath>
#include "Teksty.hpp"
#include "Hp.hpp"
#include "LaserZOczu.hpp"
#include<cstdlib>
#include "Kolce.hpp"

void kolizje(auto& niewolnik, const std::vector<Blok>&  grupaBlokow){
    for (auto &blok:grupaBlokow) {
        sf::FloatRect playerBounds = niewolnik.ksztalt.getGlobalBounds();
        sf::FloatRect blokBounds = blok.ksztalt.getGlobalBounds();
        sf::FloatRect nastepnaPoz;
        nastepnaPoz = playerBounds;
        nastepnaPoz.left += niewolnik.ruch.x;
        nastepnaPoz.top += niewolnik.ruch.y;

        if (nastepnaPoz.intersects(blok.ksztalt.getGlobalBounds())) {
            if (playerBounds.top < blokBounds.top
                && playerBounds.top + playerBounds.height < blokBounds.top + blokBounds.height
                && playerBounds.left < blokBounds.left + blokBounds.width
                && playerBounds.left + playerBounds.width > blokBounds.left) {
                niewolnik.ruch.y = 0.f;
                niewolnik.ksztalt.setPosition(playerBounds.left, blokBounds.top - playerBounds.height);
            } else if (playerBounds.top > blokBounds.top
                       && playerBounds.top + playerBounds.height > blokBounds.top + blokBounds.height
                       && playerBounds.left < blokBounds.left + blokBounds.width
                       && playerBounds.left + playerBounds.width > blokBounds.left) {
                niewolnik.ruch.y = 0.f;
                niewolnik.ksztalt.setPosition(playerBounds.left, blokBounds.top + blokBounds.height);
            }
            if (playerBounds.left < blokBounds.left
                && playerBounds.left + playerBounds.width < blokBounds.left + blokBounds.width
                && playerBounds.top < blokBounds.top + blokBounds.height
                && playerBounds.top + playerBounds.height > blokBounds.top) {
                niewolnik.ruch.x = 0.f;
                niewolnik.ksztalt.setPosition(blokBounds.left - playerBounds.width, playerBounds.top);
            } else if (playerBounds.left > blokBounds.left
                       && playerBounds.left + playerBounds.width > blokBounds.left + blokBounds.width
                       && playerBounds.top < blokBounds.top + blokBounds.height
                       && playerBounds.top + playerBounds.height > blokBounds.top) {
                niewolnik.ruch.x = 0.f;
                niewolnik.ksztalt.setPosition(blokBounds.left + blokBounds.width, playerBounds.top);
            }

        }
    }
}






int main() {
    ///-------------------------------Inicjalizacja-------------------------------------------

    std::string gdziePlik="C:\\PJC\\ProjektSemestrGra";

    int pozycjamyszyWswiecieY;
    int pozycjamyszyWswiecieX;
    sf::Font font;


    if (!font.loadFromFile(gdziePlik+"\\Tekstury\\RubikBurned-Regular.ttf"))
    {
        std::cout<<"nie dziala "<<"\n";
    }
    sf::Font font2;
    if (!font2.loadFromFile(gdziePlik+"\\Tekstury\\Roboto-Black.ttf"))
    {
        std::cout<<"nie dziala "<<"\n";
    }

    ///---------TEKSTY-------------------------------------------------
    Teksty teksty;


    sf::Text hpText;
    hpText.setFont(font);
    hpText.setCharacterSize(30);
    hpText.setFillColor(sf::Color::Red);
    hpText.setOutlineThickness(3);
    teksty.vectorTekstow.push_back(hpText);

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(sf::Color::Red);
    scoreText.setOutlineThickness(3);
    teksty.vectorTekstow.push_back(scoreText);

    sf::Text sklepText;
    sklepText.setFont(font2);
    sklepText.setCharacterSize(30);
    sklepText.setFillColor(sf::Color::Red);
    sklepText.setOutlineThickness(3);
    teksty.vectorTekstow.push_back(sklepText);

    sf::Text gameOver;
    gameOver.setFont(font);
    gameOver.setCharacterSize(300);
    gameOver.setFillColor(sf::Color::Red);
    gameOver.setOutlineThickness(5);
    gameOver.setString("GAME OVER");

    sf::Text youWIN;
    youWIN.setFont(font);
    youWIN.setCharacterSize(300);
    gameOver.setFillColor(sf::Color::Red);
    youWIN.setOutlineThickness(5);
    youWIN.setString("YOU WIN");


    ///--------ZEGARY--------------------
    sf::Clock czesiowyZegar;
    sf::Clock zegar;
    sf::Clock spawnTimer;
    sf::Clock spawnTimer2;
    sf::Clock obrazeniaStwora;
    sf::Clock obrazeniaKolcow;
    sf::Clock obrazeniaBOSS;
    sf::Clock miniBOSSTimer;
    sf::Clock obrazeniaMiniBOSS;
    sf::Clock zegarZkupuZdrowia;
    ///----------OKIENKO------------
    sf::RenderWindow okienko(sf::VideoMode(1920,1080),"XD");
    okienko.setFramerateLimit(144);
    sf::View widok;
    widok.setSize(sf::Vector2f(okienko.getSize().x,okienko.getSize().y));
    ///-----------POSTACIE-------------
    sf::Texture ziomek;
    ziomek.loadFromFile(gdziePlik+"\\Tekstury\\babmo2.png");
    Postac niewolnik(sf::Vector2f(20,40),100,ziomek);
    niewolnik.ksztalt.setFillColor(sf::Color::Transparent);
    niewolnik.ksztalt.setOutlineColor(sf::Color::Transparent);
    niewolnik.ksztalt.setOutlineThickness(-5);
    niewolnik.ksztalt.setPosition(101,700);

    sf::Texture czesioTekstura;
    czesioTekstura.loadFromFile(gdziePlik+"\\Tekstury\\zlyCzesiek.png");
    Przeciwnik czesio(20,5,sf::Vector2f (3.5,1),sf::Vector2f(30,30),czesioTekstura);
    std::vector<Przeciwnik> gromadaczesiow;

    sf::Texture latajacyCzesioTekstura;
    latajacyCzesioTekstura.loadFromFile(gdziePlik+"\\Tekstury\\latajacyPrzeciwnik.png");
    Przeciwnik latajacyCzesio(10,3,sf::Vector2f (2,0),sf::Vector2f (30,13),latajacyCzesioTekstura);
    std::vector<Przeciwnik> vectorLatajacych;

    sf::Texture strasznyStworTekstura;
    strasznyStworTekstura.loadFromFile(gdziePlik+"\\Tekstury\\strasznystwor.png");
    Przeciwnik strasznyStwor(50,40,sf::Vector2f (0,1),sf::Vector2f (100,100),strasznyStworTekstura);
    std::vector<Przeciwnik> vectorStrasznegoStwora;

    sf::Texture trojnogiBOSSTekstura;
    trojnogiBOSSTekstura.loadFromFile(gdziePlik+"\\Tekstury\\trojnogiBOSS.png");
    Przeciwnik trojnogiBOSS(650,100,sf::Vector2f (1,1),sf::Vector2f (150,200),trojnogiBOSSTekstura);
    trojnogiBOSS.ksztalt.setPosition(5500,2600);
    trojnogiBOSS.wyglad.setPosition(trojnogiBOSS.ksztalt.getPosition());

    sf::Texture miniBOSSTekstura;
    miniBOSSTekstura.loadFromFile(gdziePlik+"\\Tekstury\\miniBOSS.png");
    Przeciwnik miniBOSS(90,50,sf::Vector2f (3,1),sf::Vector2f (50,100),miniBOSSTekstura);
    std::vector<Przeciwnik> vectorMiniBOSSOW;


    ///BULLET-----------------------------------------
    Bullet standardowa_kulka(5,10,20,sf::Color::Green);

    std::vector<Bullet> bullets;

    std::vector<LaserZOczu> lasery;

    ///BLOKI I MAPA--------------------------------------------------------------------------------
    sf::Texture bloki;
    bloki.loadFromFile(gdziePlik+"\\Tekstury\\blok3.png");
    Blok blok(sf::Vector2f(100,100),sf::Color::Black);
    blok.wyglad.setTexture(bloki);

    sf::Texture kolcetexture;
    kolcetexture.loadFromFile(gdziePlik+"\\Tekstury\\kolce.png");
    Kolce kolce(sf::Vector2f(100,100),sf::Color(100,100,255));
    kolce.wyglad.setTexture(kolcetexture);
    std::vector<Kolce> vectorKolcow;

    sf::Texture zwyklyPortaltekstura;
    zwyklyPortaltekstura.loadFromFile(gdziePlik+"\\Tekstury\\Portal.png");
    Blok zwyklyPortal(sf::Vector2f(100,100),sf::Color::Blue);
    zwyklyPortal.wyglad.setTexture(zwyklyPortaltekstura);

    sf::Texture portalLatajacychTekstura;
    portalLatajacychTekstura.loadFromFile(gdziePlik+"\\Tekstury\\portalLatajacych.png");
    Blok portalLatajacych(sf::Vector2f(100,100),sf::Color::Green);
    portalLatajacych.wyglad.setTexture(portalLatajacychTekstura);

    sf::Texture hpTekstura;
    hpTekstura.loadFromFile(gdziePlik+"\\Tekstury\\hp.png");
    Hp hp(sf::Vector2f(100,100),sf::Color(50,50,50));
    hp.wyglad.setTexture(hpTekstura);
    std::vector<Hp> vectorHp;






    std::vector<Blok> grupaBlokow;
    for (int k = 0; k <100 ; ++k) {
        int x=(rand() % 60);
        int y=(rand()%30);
        hp.ksztalt.setPosition(x*100,y*100);
        hp.wyglad.setPosition(x*100,y*100);
        vectorHp.push_back(hp);
    }


    sf::Image podloga;
    podloga.loadFromFile(gdziePlik+"\\Tekstury\\podloga2.png");
    for (int i = 0; i <podloga.getSize().x ; ++i) {
        for (int j = 0; j <podloga.getSize().y ; ++j) {
            if (podloga.getPixel(i,j)==blok.kolor){
                blok.ksztalt.setPosition(i*100,j*100);
                blok.wyglad.setPosition(blok.ksztalt.getPosition());
                grupaBlokow.push_back(blok);
            }
            else if (podloga.getPixel(i,j)==kolce.kolor){
                kolce.ksztalt.setPosition(i*100,j*100);
                kolce.wyglad.setPosition(kolce.ksztalt.getPosition());
                vectorKolcow.push_back(kolce);
            }
            else if (podloga.getPixel(i,j)==zwyklyPortal.kolor){
                zwyklyPortal.ksztalt.setPosition(i*100,j*100);
                zwyklyPortal.wyglad.setPosition(zwyklyPortal.ksztalt.getPosition());
                grupaBlokow.push_back(zwyklyPortal);
            }
            else if (podloga.getPixel(i,j)==portalLatajacych.kolor){
                portalLatajacych.ksztalt.setPosition(i*100,j*100);
                portalLatajacych.wyglad.setPosition(portalLatajacych.ksztalt.getPosition());
                grupaBlokow.push_back(portalLatajacych);
            }
            else if (podloga.getPixel(i,j)==sf::Color(255,255,100)){
                strasznyStwor.ksztalt.setPosition(i*100,j*100);
                strasznyStwor.wyglad.setPosition(strasznyStwor.ksztalt.getPosition());
                vectorStrasznegoStwora.push_back(strasznyStwor);
            }


        }
    }



    ///----------------------Update-----------------------------------------------------------

    while (okienko.isOpen()) {
        sf::Event event;
        while (okienko.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                okienko.close();
        }
        if(niewolnik.hp>0&&trojnogiBOSS.hp>0) {
            niewolnik.dd();
            trojnogiBOSS.dd();

            for (auto &czesio: gromadaczesiow) {
                czesio.dd();
            }
            for (auto &czesio: vectorLatajacych) {
                czesio.dd();
            }
            for(auto &mini:vectorMiniBOSSOW){
                mini.dd();
            }


            for (auto &bullet: bullets) {


                if (bullet.ksztalt.getGlobalBounds().intersects(trojnogiBOSS.ksztalt.getGlobalBounds())){
                    bullet.walnela=true;
                    trojnogiBOSS.hp-=bullet.demage;
                }
                for(auto &mini:vectorMiniBOSSOW){
                    if (bullet.ksztalt.getGlobalBounds().intersects(mini.ksztalt.getGlobalBounds())){
                        bullet.walnela=true;
                        mini.hp-=bullet.demage;
                        std::cout<<mini.hp<<"\n";
                    }
                }
                for (auto &stwor: vectorStrasznegoStwora) {
                    if (bullet.ksztalt.getGlobalBounds().intersects(stwor.ksztalt.getGlobalBounds())) {
                        bullet.walnela = true;
                        stwor.hp -= bullet.demage;
                    }
                }
                for (auto &czesio: gromadaczesiow) {
                    if (bullet.ksztalt.getGlobalBounds().intersects(czesio.ksztalt.getGlobalBounds())) {
                        bullet.walnela = true;
                        czesio.hp -= bullet.demage;
                    }
                }
                for (auto &czesio: vectorLatajacych) {
                    if (bullet.ksztalt.getGlobalBounds().intersects(czesio.ksztalt.getGlobalBounds())) {
                        bullet.walnela = true;
                        czesio.hp -= bullet.demage;
                    }
                }


                for (auto &blok: grupaBlokow) {
                    if (bullet.ksztalt.getGlobalBounds().intersects(blok.ksztalt.getGlobalBounds()))
                        bullet.walnela = true;
                }

            }
            for (auto &czesio: vectorLatajacych) {
                if (czesio.czasStrzalu.getElapsedTime().asSeconds() >= 4) {
                    lasery.push_back(czesio.laser);
                    lasery.back().ksztalt.setPosition(czesio.ksztalt.getPosition());
                    czesio.czasStrzalu.restart();
                }
            }
            for (auto &hp: vectorHp) {
                if (niewolnik.ksztalt.getGlobalBounds().intersects(hp.ksztalt.getGlobalBounds())) {
                    niewolnik.hp += 5;
                    hp.czyUzyte = true;
                }
            }

            for (auto &laser: lasery) {
                if (laser.ksztalt.getGlobalBounds().intersects(niewolnik.ksztalt.getGlobalBounds())) {
                    niewolnik.hp -= laser.demage;
                    laser.walnela = true;
                }
                for (auto &blok: grupaBlokow) {
                    if (laser.ksztalt.getGlobalBounds().intersects(blok.ksztalt.getGlobalBounds()))
                        laser.walnela = true;
                }
            }



            auto miniBOSSUmiera=[](auto const &mini){return mini.hp<=0;};
            std::erase_if(vectorMiniBOSSOW, miniBOSSUmiera);
            auto laserWalnal = [](LaserZOczu laser) { return laser.walnela; };
            std::erase_if(lasery, laserWalnal);


            auto czyuzyto = [](auto const &hp) { return hp.czyUzyte; };
            std::erase_if(vectorHp, czyuzyto);

            if (spawnTimer.getElapsedTime().asSeconds() >= 2 && gromadaczesiow.size() <= 30) {

                czesio.ksztalt.setPosition(
                        zwyklyPortal.ksztalt.getPosition().x + zwyklyPortal.ksztalt.getGlobalBounds().width,
                        zwyklyPortal.ksztalt.getPosition().y);
                czesio.wyglad.setPosition(czesio.ksztalt.getPosition());
                gromadaczesiow.push_back(czesio);
                spawnTimer.restart();
            }
            if (spawnTimer2.getElapsedTime().asSeconds() >= 5 && vectorLatajacych.size() <= 30) {

                latajacyCzesio.ksztalt.setPosition(
                        portalLatajacych.ksztalt.getPosition().x - portalLatajacych.ksztalt.getGlobalBounds().width,
                        portalLatajacych.ksztalt.getPosition().y);
                latajacyCzesio.wyglad.setPosition(latajacyCzesio.ksztalt.getPosition());
                vectorLatajacych.push_back(latajacyCzesio);
                spawnTimer2.restart();
            }
            auto czyStworZdycha=[](auto const &strasznyStwor){return strasznyStwor.hp<=0;};
            for (auto &stwor: vectorStrasznegoStwora) {
                if (czyStworZdycha(stwor)) {
                    niewolnik.score += 50;
                }
            }
            std::erase_if(vectorStrasznegoStwora, czyStworZdycha);

            auto czyZdycha = [](auto const &czesio) { return czesio.hp <= 0; };
            for (auto &czesio: gromadaczesiow) {
                if (czyZdycha(czesio)) {
                    niewolnik.score += 30;
                }
            }
            for (auto &czesio: vectorLatajacych) {
                if (czyZdycha(czesio)) {
                    niewolnik.score += 20;
                }
            }
            std::erase_if(gromadaczesiow, czyZdycha);


            std::erase_if(vectorLatajacych, czyZdycha);

            auto czydotknela = [](auto const &kulka) { return kulka.walnela; };
            std::erase_if(bullets, czydotknela);


            teksty.updateTekst(1, "SCORE: " + std::to_string(niewolnik.score));

            teksty.updateTekst(2,
                               "Demage boost LVL1-100 points-press1""\n""Demage boost LVL2-200 points-press2""\n""Demage boost LVL3-300 points-press3""\n""Demage boost LVL4-500 points-press4""\n""+100HP-100pts Press5(20s)");
            if (sf::Keyboard().isKeyPressed(sf::Keyboard::Num1) && niewolnik.score >= 100 &&
                niewolnik.boostStrzelania < 1) {
                niewolnik.boostStrzelania = 1;
                niewolnik.score -= 100;
            }
            if (sf::Keyboard().isKeyPressed(sf::Keyboard::Num2) && niewolnik.score >= 200 &&
                niewolnik.boostStrzelania < 2) {
                niewolnik.boostStrzelania = 2;
                niewolnik.score -= 200;
            }
            if (sf::Keyboard().isKeyPressed(sf::Keyboard::Num3) && niewolnik.score >= 300 &&
                niewolnik.boostStrzelania < 3) {
                niewolnik.boostStrzelania = 3;
                niewolnik.score -= 300;
            }
            if (sf::Keyboard().isKeyPressed(sf::Keyboard::Num4) && niewolnik.score >= 500 &&
                niewolnik.boostStrzelania < 4) {
                niewolnik.boostStrzelania = 4;
                niewolnik.score -= 500;
            }
            if (sf::Keyboard().isKeyPressed(sf::Keyboard::Num5) && niewolnik.score >= 100&&zegarZkupuZdrowia.getElapsedTime().asSeconds()>=20 ) {
                niewolnik.hp+=100;
                niewolnik.score -= 100;
                zegarZkupuZdrowia.restart();
            }


            kolizje(niewolnik, grupaBlokow);
            kolizje(trojnogiBOSS, grupaBlokow);
            if (trojnogiBOSS.ruch.x == 0)
                trojnogiBOSS.predkosc.x *= -1;
            if (trojnogiBOSS.ksztalt.getGlobalBounds().intersects(niewolnik.ksztalt.getGlobalBounds())&&obrazeniaBOSS.getElapsedTime().asSeconds()>=1){
                niewolnik.hp-=trojnogiBOSS.dmg;
                obrazeniaBOSS.restart();
            }
            if (miniBOSSTimer.getElapsedTime().asSeconds() >= 4 && vectorMiniBOSSOW.size() <= 7) {

                miniBOSS.ksztalt.setPosition(
                        trojnogiBOSS.ksztalt.getPosition().x - trojnogiBOSS.ksztalt.getGlobalBounds().width,
                        trojnogiBOSS.ksztalt.getPosition().y);
                miniBOSS.wyglad.setPosition(miniBOSS.ksztalt.getPosition());
                vectorMiniBOSSOW.push_back(miniBOSS);
                miniBOSSTimer.restart();
            }
            for (auto &mini:vectorMiniBOSSOW) {
                kolizje(mini, grupaBlokow);
                if(mini.ruch.x==0)
                    mini.predkosc.x*=-1;
            }



            for (auto &czesio: gromadaczesiow) {
                kolizje(czesio, grupaBlokow);
                if (czesio.ruch.x == 0)
                    czesio.predkosc.x *= -1;
            }
            for (auto &czesio: vectorLatajacych) {
                kolizje(czesio, grupaBlokow);
                if (czesio.ruch.x == 0)
                    czesio.predkosc.x *= -1;
            }

            for ( auto &mini:vectorMiniBOSSOW) {
                if (mini.ksztalt.getGlobalBounds().intersects(niewolnik.ksztalt.getGlobalBounds())&&obrazeniaMiniBOSS.getElapsedTime().asSeconds()>=0.4){
                    niewolnik.hp -= mini.dmg;
                    obrazeniaMiniBOSS.restart();
                }
            }


            for (auto &czesio: gromadaczesiow) {
                if (czesio.ksztalt.getGlobalBounds().intersects(niewolnik.ksztalt.getGlobalBounds()) &&
                    zegar.getElapsedTime().asSeconds() > 0.4) {
                    niewolnik.hp -= czesio.dmg;
                    zegar.restart();
                }
            }
            for (auto &stwor: vectorStrasznegoStwora) {
                if (stwor.ksztalt.getGlobalBounds().intersects(niewolnik.ksztalt.getGlobalBounds()) &&
                    obrazeniaStwora.getElapsedTime().asSeconds() > 0.4) {
                    niewolnik.hp -= stwor.dmg;
                    obrazeniaStwora.restart();
                }
            }

            for (auto &czesio: vectorLatajacych) {
                if (czesio.ksztalt.getGlobalBounds().intersects(niewolnik.ksztalt.getGlobalBounds()) &&
                    zegar.getElapsedTime().asSeconds() > 0.4) {
                    niewolnik.hp -= czesio.dmg;
                    zegar.restart();
                }
            }
            teksty.updateTekst(0, "HP: " + std::to_string(niewolnik.hp));


            pozycjamyszyWswiecieY = sf::Mouse::getPosition(okienko).y - okienko.getSize().y / 2;
            pozycjamyszyWswiecieX = sf::Mouse::getPosition(okienko).x - okienko.getSize().x / 2;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && zegar.getElapsedTime().asSeconds() > 0.4) {
                bullets.push_back(standardowa_kulka);
                if (niewolnik.boostStrzelania == 1) {
                    bullets.back().demage = 20;
                    bullets.back().ksztalt.setFillColor(sf::Color::White);
                    bullets.back().ksztalt.setRadius(7);
                }
                if (niewolnik.boostStrzelania == 2) {
                    bullets.back().demage = 40;
                    bullets.back().ksztalt.setFillColor(sf::Color::Magenta);
                    bullets.back().ksztalt.setRadius(9);
                }
                if (niewolnik.boostStrzelania == 3) {
                    bullets.back().demage = 60;
                    bullets.back().ksztalt.setFillColor(sf::Color::Red);
                    bullets.back().ksztalt.setRadius(10);
                }
                if (niewolnik.boostStrzelania == 4) {
                    bullets.back().demage = 80;
                    bullets.back().ksztalt.setFillColor(sf::Color::Black);
                    bullets.back().ksztalt.setRadius(11);
                }

                bullets.back().ksztalt.setOrigin(5, 5);
                bullets.back().ksztalt.setPosition(
                        niewolnik.wyglad.getPosition() + niewolnik.wyglad.getGlobalBounds().getSize() / 2.f);
                bullets.back().kat = (atan2(pozycjamyszyWswiecieY, pozycjamyszyWswiecieX));
                //https://www.youtube.com/watch?v=j9kS8CGuFhg&t=433s
                zegar.restart();

            }
            for (auto &czesio: gromadaczesiow) {
                czesio.ksztalt.move(czesio.ruch);
                czesio.wyglad.setPosition(czesio.ksztalt.getPosition());
            }
            for (auto &czesio: vectorLatajacych) {
                czesio.ksztalt.move(czesio.ruch);
                czesio.wyglad.setPosition(czesio.ksztalt.getPosition());
            }
            for(auto &mini:vectorMiniBOSSOW){
                mini.ksztalt.move(mini.ruch);
                mini.wyglad.setPosition(mini.ksztalt.getPosition());
            }
            for (auto &kolec: vectorKolcow) {
                if (kolec.ksztalt.getGlobalBounds().intersects(niewolnik.ksztalt.getGlobalBounds())&&obrazeniaKolcow.getElapsedTime().asSeconds()>=3) {
                    niewolnik.hp -= kolec.dmg;
                    obrazeniaKolcow.restart();
                }
            }
            trojnogiBOSS.ksztalt.move(trojnogiBOSS.ruch);
            trojnogiBOSS.wyglad.setPosition(trojnogiBOSS.ksztalt.getPosition());

            niewolnik.ksztalt.move(niewolnik.ruch);
            niewolnik.wyglad.setPosition(niewolnik.ksztalt.getPosition());
            teksty.ustawPozycje(0, niewolnik.ksztalt.getPosition() - sf::Vector2f(40, 40));
            widok.setCenter(niewolnik.ksztalt.getPosition().x + niewolnik.ksztalt.getGlobalBounds().width / 2,
                           niewolnik.ksztalt.getPosition().y + niewolnik.ksztalt.getGlobalBounds().height / 2);
            teksty.ustawPozycje(1, widok.getCenter() - sf::Vector2f(okienko.getSize().x / 2, okienko.getSize().y / 2));
            teksty.ustawPozycje(2, widok.getCenter() -
                                   sf::Vector2f(okienko.getSize().x / 2, okienko.getSize().y / 2 - 150));
        }
        gameOver.setPosition(widok.getCenter() - sf::Vector2f(okienko.getSize().x / 2 - 10, okienko.getSize().y / 2 - 200));
        youWIN.setPosition(widok.getCenter() - sf::Vector2f(okienko.getSize().x / 2 - 10, okienko.getSize().y / 2 - 200));
        ///----------------------------------------------------Rysowanko----------------------------
        if (niewolnik.hp>0) {
            okienko.clear(sf::Color(60, 80, 245));
            okienko.setView(widok);
            for (auto &hp: vectorHp) {
                hp.draw(okienko);
            }

            for (auto &blok: grupaBlokow) {
                blok.draw(okienko);
            }
            for (auto &kolec: vectorKolcow) {
                kolec.draw(okienko);
            }
            for (int i = 0; i < bullets.size(); ++i) {
                okienko.draw(bullets[i].ksztalt);
                bullets[i].ksztalt.move(standardowa_kulka.predkosc * cos(bullets[i].kat),
                                        standardowa_kulka.predkosc * sin(bullets[i].kat));
            }
            for (int i = 0; i < lasery.size(); ++i) {
                okienko.draw(lasery[i].ksztalt);
                lasery[i].ksztalt.move(lasery[i].predkosc * cos(lasery[i].kat),
                                       lasery[i].predkosc * sin(lasery[i].kat));
            }
            niewolnik.draw(okienko);
            for (auto &czesio: gromadaczesiow) {
                czesio.draw(okienko);
            }
            for (auto &czesio: vectorLatajacych) {
                czesio.draw(okienko);
            }
            for(auto &strasznyStwor:vectorStrasznegoStwora) {
                strasznyStwor.draw(okienko);
            }
            for(auto &mini:vectorMiniBOSSOW){
                mini.draw(okienko);
            }
            okienko.draw(trojnogiBOSS.wyglad);
            teksty.draw(okienko);
            okienko.display();
        }
        if (trojnogiBOSS.hp<=0){
            okienko.setView(widok);
            okienko.clear(sf::Color::Black);
            okienko.draw(youWIN);
            okienko.display();

        }
        if (niewolnik.hp<=0){
            okienko.setView(widok);
            okienko.clear(sf::Color::Black);
            okienko.draw(gameOver);
            okienko.display();
        }

    }
}

