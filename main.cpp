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
    sf::Texture NAMIAR;
    NAMIAR.loadFromFile("NAMIAR.png");
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
    sf::Sprite pocisk,mete, zlydron, rakieta, auton;

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
    int rundy=0;
    bool autopilot=false;

    sf::Clock clock;

        while (window.isOpen())
        {
            rectangle_bounds = dron.getGlobalBounds();
            startbounds = newgame.getGlobalBounds();

            sf::Time elapsed = clock.restart();

            sf::Event event;

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                window.close();
            }

            if(gameover==1)
            {
                sf::Vector2i globalPosition = sf::Mouse::getPosition(window);
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
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&globalPosition.x>=startbounds.left && globalPosition.y>=startbounds.top && globalPosition.y<=startbounds.top+startbounds.height && globalPosition.x<=startbounds.left+startbounds.width)
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
                    V.back().setOrigin(8.5, 20);
                    V.back().setTextureRect(sf::IntRect(0,0, 17, 40));

                    if(V.size()>8)
                    {
                        V.erase(V.begin());
                    }
                    czas=0;
                }

                if(czas_deszczu<10)
                {
                     if(czas_meteor>0.8)
                     {
                         M.push_back(Meteoryt(mete));
                         M.back().setPosition(rand()%1800,-150);
                         M.back().setOrigin(70,67.5);
                         M.back().setTexture(lecimeteor);
                         M.back().setTextureRect(sf::IntRect(metx(),mety(), 140, 135));
                         if(M.size()>20)
                         {
                             M.erase(M.begin());
                         }
                     czas_meteor=0;
                     }

                 }

                if((czas_deszczu<8.82)&&(czas_deszczu>8.80))
                {
                    auton.setTexture(NAMIAR);
                    auton.setScale(0.15, 0.15);
                    auton.setTextureRect(sf::IntRect(0, 0, 512, 512));
                    auton.setOrigin(256,256);
                    auton.setPosition(rand()%1800,-200);
                }

                if(czas_deszczu>10)
                {
                    if(czas_meteor>1.5)
                    {
                        for(auto &c : W)
                        {
                        P.push_back(Pociskprzeciwnika(rakieta));
                        P.back().setPosition(c.getPosition().x-10,c.getPosition().y+50);
                        P.back().setTexture(zlypocisk);
                        P.back().setTextureRect(sf::IntRect(0,0, 20, 35));
                        }
                        if(P.size()>10*(rundy+1))
                        {
                            P.erase(P.begin());
                        }
                        for(int i=0; i<rundy+2; i++)
                        {
                            Pred.push_back(rand()%200-100);
                        }
                        if(Pred.size()>4)
                        {
                            for(int i=0; i<rundy+2; i++)
                            {
                                Pred.erase(Pred.begin());
                            }
                        }

                        czas_meteor=0;

                        if(wrogowie==0)
                        {
                            for(int i=0; i<rundy+1; i++)
                            {
                                W.push_back(Wrog(zlydron));
                                W.back().setPosition(rand()%1800,-200);
                                W.back().setOrigin(49.5,47.5);
                                W.back().setScale(1.4,1.4);
                                W.back().setTexture(wrogistatek);
                                W.back().setTextureRect(sf::IntRect(1,2, 99, 95));
                            }
                            wrogowie=1;
                        }
                    }
                }
            window.clear();
            window.draw(niebo);

            for(int i=0; i<V.size(); i++)
            {
                window.draw(V[i]);

                if(autopilot==true)
                {
                  V[i].mov(elapsed.asSeconds(),predkosckoncowa(V[i].getPosition().x,W[0].getPosition().x,V[i].getPosition().y,W[0].getPosition().y,-100*elapsed.asSeconds()),-250);
                  V[i].setRotation(kat(V[i].getPosition().x, W[0].getPosition().x, V[i].getPosition().y, W[0].getPosition().y));
                  if(abs(W[0].getPosition().x-V[i].getPosition().x)<70 && abs(W[0].getPosition().y-V[i].getPosition().y)<30)
                  {
                     autopilot=false;
                  }
                }
                if(autopilot==false)
                {
                  V[i].mov(elapsed.asSeconds(),0,-250);
                  V[i].setRotation(0);
                }

                for(auto &m:M)
                {
                    if(abs(V[i].getPosition().x-m.getPosition().x)<65 && abs(V[i].getPosition().y-m.getPosition().y)<45)
                    {
                    V.erase(V.begin()+i);
                    M.push_back(Meteoryt(mete));
                    M.back().setPosition(m.getPosition().x-30,m.getPosition().y);
                    M.back().setScale(0.7,0.7);
                    M.back().setOrigin(70,67.5);
                    M.back().setTexture(lecimeteor);
                    M.back().setTextureRect(sf::IntRect(metx(),mety(), 140, 135));
                    }
                }

                for(int j=0;j<W.size(); j++)

                {
                    if(abs(W[j].getPosition().x-V[i].getPosition().x)<70 && abs(W[j].getPosition().y-V[i].getPosition().y)<30)
                    {
                    W.erase(W.begin()+j);
                    V.erase(V.begin()+i);
                    }
                }
            }

            for(auto &c:P)
            {
                window.draw(c);
                c.mov(elapsed.asSeconds());
                if(abs(c.getPosition().x-dron.getPosition().x)<60 && abs(c.getPosition().y-dron.getPosition().y)<60)
                {
                    gameover=1;
                    czas=0;
                    autopilot=false;
                    czas_meteor=0;
                    czas_deszczu=0;
                    rundy=0;
                    wrogowie=0;
                    auton.setPosition(-200,-200);
                }
            }

            for(int i=0; i<W.size(); i++)

            {
                if(W[i].getPosition().x>1820)
                {
                   Pred[i]=-60;
                }
                if(W[i].getPosition().x<75)
                {
                    Pred[i]=60;
                }
                if(rundy>0)
                {
                    for(int j=0; j<W.size(); j++)
                    {
                        if((abs(W[i].getPosition().x-W[j].getPosition().x)<150)&&(i!=j))
                        {
                             Pred[j]=-Pred[j];
                             Pred[i]=Pred[i];
                        }
                    }
                }
                window.draw(W[i]);
                W[i].movy(elapsed.asSeconds());
                W[i].movx(elapsed.asSeconds(),Pred[i]);
            }

            for(auto &c:M)
            {
                window.draw(c);
                c.movm(elapsed.asSeconds());
                c.rota(elapsed.asSeconds());

                if(abs(c.getPosition().x-dron.getPosition().x)<100 && abs(c.getPosition().y-dron.getPosition().y)<90)
                {
                    gameover=1;
                    czas=0;
                    autopilot=false;
                    czas_meteor=0;
                    czas_deszczu=0;
                    wrogowie=0;
                    auton.setPosition(-200,-200);
                }
            }

            if((abs(dron.getPosition().x-auton.getPosition().x)<70)&&(abs(dron.getPosition().y-auton.getPosition().y)<70))
            {
                auton.setPosition(-200,-200);
                autopilot=true;
            }

            if((W.size() == 0)&&(czas_deszczu>11.5))
            {
            czas_deszczu=0;
            wrogowie=0;
            rundy++;
            }


            window.draw(auton);
            auton.move(0, 200*elapsed.asSeconds());
            window.draw(dron);

            }

            window.display();

        }

        return 0;

    }

