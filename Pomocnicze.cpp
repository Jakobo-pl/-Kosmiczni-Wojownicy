#include<iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int losowanie()
{
    int v= rand()%200-100;
    return v;
}

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
