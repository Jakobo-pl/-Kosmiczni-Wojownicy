#include<iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class Wrog: public sf::Sprite
{
public:
    Wrog (const sf::Sprite){}

    void movy (float czas)
    {
        if(this->getGlobalBounds().top<80) {move(0,60*czas);}
    }
    void movx(float czas)
    {
        move(-10*czas,0);
    }
};
std::vector<Wrog> W;




class Myobiekt: public sf::Sprite
{
public:
    Myobiekt (const sf::Sprite){}
    void mov (float elaps){ move(0,-250*elaps);};
};
std::vector<Myobiekt> V;



class Pociskprzeciwnika: public sf::Sprite
{
public:
    Pociskprzeciwnika (const sf::Sprite) {}
    void mov (float elaps){ move(0,250*elaps);};
};
std::vector<Pociskprzeciwnika> P;



class Meteoryt: public sf::Sprite
{
public:
    Meteoryt (const sf::Sprite){}
    int v= rand()%200-100;
    void movm (float elaps) {move(v*elaps,180*elaps);};
    void rota(float elaps) {rotate((v/1.5)*elaps);}
    bool kolizjazpociskiem(std::vector<Myobiekt> M)
    {
        for(auto &r : M)
        {
            if(abs(r.getPosition().x - this->getPosition().x)<100 && abs(r.getPosition().y - this->getPosition().y)<100)
            {
                return true;
            }
            return false;

        }
    }
};
std::vector<Meteoryt> M;
