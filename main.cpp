#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include <SFML/Audio.hpp>
#include "Klasy.cpp"
#include "Pomocnicze.cpp"

int main()
{

    sf::Texture wrogistatek;
    wrogistatek.loadFromFile("wrogistatek.png");
    sf::Texture wstep;
    wstep.loadFromFile("log.png");
    sf::Texture newg;
    newg.loadFromFile("butt.png");
    sf::Texture tlo;
    tlo.loadFromFile("niebo.jpg");
    sf::Texture statek;
    statek.loadFromFile("texture.png");
    sf::Texture lecistrzal;
    lecistrzal.loadFromFile("rrr.png");
    sf::Texture lecimeteor;
    lecimeteor.loadFromFile("meteor.png");
    sf::Texture zlypocisk;
    zlypocisk.loadFromFile("zlypocisk.png");

    sf::Sprite niebo;
    niebo.setTexture(tlo);
    niebo.setTextureRect(sf::IntRect(0, 0, 1900, 1080));
    niebo.setPosition(0, 0);

    sf::Sprite newgame;
    newgame.setTexture(newg);
    newgame.setTextureRect(sf::IntRect(20, 20, 920, 390));
    newgame.setPosition(450, 600);
    newgame.setScale(0.4,0.4);

    sf::Sprite logo;
    logo.setTexture(wstep);
    logo.setTextureRect(sf::IntRect(0, 0, 1000, 500));
    logo.setPosition(200, 0);

    sf::Sprite dron;
    dron.setTexture(statek);
    dron.setOrigin(57.5, 50);
    dron.setTextureRect(sf::IntRect(0, 0, 115, 100));
    dron.setPosition(917, 880);

    sf::Sprite pocisk;
    sf::Sprite mete;
    sf::Sprite zlydron;
    sf::Sprite rakieta;

    sf::Music music;
    if (!music.openFromFile("doom.ogg"))
        return EXIT_FAILURE;
    music.setLoop(EXIT_FAILURE);
    music.setVolume(10);
    music.play();

    sf::SoundBuffer buffer;
    buffer.loadFromFile("strzal.ogg");

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.setVolume(3);


    sf::RenderWindow window(sf::VideoMode(1900, 1080), "Kosmiczni Wojownicy");
    sf::FloatRect pocisk_bounds;
    sf::FloatRect rectangle_bounds;
    sf::FloatRect startbounds;

    window.setFramerateLimit(60);

    int gameover=1;
    int wrogowie=0;

    sf::Clock clock;


        while (window.isOpen())
        {

            rectangle_bounds = dron.getGlobalBounds();
            startbounds = newgame.getGlobalBounds();;



            sf::Time elapsed = clock.restart();
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                window.close();
            }


            if(gameover==1)
            {

                sf::Vector2i globalPosition = sf::Mouse::getPosition();
                window.clear();
                window.draw(niebo);
                window.draw(logo);
                dron.setScale(2.0, 2.0);
                dron.setTextureRect(sf::IntRect(0, 0, 300, 300));
                dron.setPosition(1290, 600);
                window.draw(dron);
                window.draw(newgame);
                M.clear();
                W.clear();
                V.clear();
                P.clear();
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&globalPosition.x>=startbounds.left+18 && globalPosition.y>=startbounds.top+18 && globalPosition.y<=startbounds.top+startbounds.height+18 && globalPosition.x<=startbounds.left+startbounds.width+18)
                {
                gameover=0;
                }


            }
            if((gameover==0)||(gameover==2))
            {
                if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D))&&(rectangle_bounds.left+rectangle_bounds.width<1898)){dron.move(500 * elapsed.asSeconds(), 0);}
                if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A))&&(rectangle_bounds.left>0)) {dron.move(-500 * elapsed.asSeconds(), 0); }


                float czas=elapsed.asSeconds()+czas;
                float czas_meteor=elapsed.asSeconds()+czas_meteor;
                float czas_deszczu=elapsed.asSeconds()+czas_deszczu;

                if(gameover==0)
                {
                    dron.setScale(1.0, 1.0);
                    dron.setTexture(statek);
                    dron.setTextureRect(sf::IntRect(0, 0, 115, 100));
                    dron.setPosition(917, 910);
                    gameover=2;
                }


                if((sf::Mouse::isButtonPressed(sf::Mouse::Left))&&(czas>0.5))
                {
                    sound.play();
                    V.push_back(Myobiekt(pocisk));
                    V.back().setPosition(dron.getPosition().x-4,dron.getPosition().y-50);
                    V.back().setTexture(lecistrzal);
                    V.back().setTextureRect(sf::IntRect(0,0, 17, 40));
                    if(V.size()>10)
                    {
                        V.erase(V.begin());
                    }
                    czas=0;
                }
                if(czas_deszczu<30)
                {
                     if(czas_meteor>0.8)
                     {
                         M.push_back(Meteoryt(mete));
                         M.back().setPosition(rand()%1800,-150);
                         M.back().setOrigin(70,67.5);
                         M.back().setTexture(lecimeteor);
                         M.back().setTextureRect(sf::IntRect(metx(),mety(), 140, 135));
                         if(M.size()>10)
                         {
                             M.erase(M.begin());
                         }
                     czas_meteor=0;
                     }
                 }
                if(czas_deszczu>30)
                {

                    if(czas_meteor>1.5)
                    {
                        P.push_back(Pociskprzeciwnika(rakieta));
                        P.back().setPosition(200,-150);
                        P.back().setOrigin(10,17.5);
                        P.back().setTexture(zlypocisk);
                        P.back().setTextureRect(sf::IntRect(0,0, 20, 35));
                        if(P.size()>10)
                        {
                            P.erase(P.begin());
                        }
                        czas_meteor=0;

                        if(wrogowie==0)
                        {
                        W.push_back(Wrog(zlydron));
                        W.back().setPosition(rand()%1800,-200);
                        W.back().setOrigin(49.5,47.5);
                        W.back().setScale(1.4,1.4);
                        W.back().setTexture(wrogistatek);
                        W.back().setTextureRect(sf::IntRect(1,2, 99, 95));
                        wrogowie=1;
                        }
                    }
                }



            window.clear();
            window.draw(niebo);
            for(auto &c:M)
            {
                window.draw(c);
                c.movm(elapsed.asSeconds());
                c.rota(elapsed.asSeconds());
                if(abs(c.getPosition().x-dron.getPosition().x)<100 && abs(c.getPosition().y-dron.getPosition().y)<90)
                {
                    gameover=1;
                    czas=0;
                    czas_meteor=0;
                    czas_deszczu=0;
                }
            }
            for(auto &c:W)
            {
                window.draw(c);
                c.movy(elapsed.asSeconds());
                c.movx(elapsed.asSeconds());
            }
            for(auto &c:V)
            {
                window.draw(c);
                c.mov(elapsed.asSeconds());
            } 
            for(auto &c:P)
            {
                window.draw(c);
                c.mov(elapsed.asSeconds());
            }
            window.draw(dron);
            }

            window.display();
        }
        return 0;
    }
