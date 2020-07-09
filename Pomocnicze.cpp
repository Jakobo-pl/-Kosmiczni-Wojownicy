#include<iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>

int metx()
{
    int X;
    int x= rand()%3;
    if(x==0) {X=45;}
    if(x==1) {X=235;}
    if(x==2) {X=425;}
    return X;
}

int mety()
{
    int Y;
    int y= rand()%3;
    if(y==0){ Y=30;}
    if(y==1){ Y=210;}
    if(y==2){ Y=375;}
    return Y;
}

float kat(float xS, float xW, float yS, float yW)
{
    if(xS>xW)
    {
        float kx = xS-xW;
        float ky = yS-yW;
        float dobrykat = atan(kx/ky);
        return -((dobrykat*360)/(2*M_PI));
    }
    if(xS<xW)
    {
        float kx = xW-xS;
        float ky = yS-yW;
        float dobrykat = atan(kx/ky);
        return ((dobrykat*360)/(2*M_PI));
    }
}

float predkosckoncowa(float pociskx,float wrogx, float pocisky,float wrogy,float elapsed)
{
    float predkosckoncowa=(pociskx-wrogx)/ ((pocisky-wrogy)/(250*elapsed));
    return predkosckoncowa;
}



