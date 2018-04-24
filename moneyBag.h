#pragma once
#include "LTexture.h"
#include "Point.h"

class moneyBag
{
private:
    int width,height;               ///width and height of money bag
    Point position;                 ///position of money bag on screen
    LTexture* image;                ///image consisting of money bag
    SDL_Rect spriteClip;            ///sprite clip specific to money bag
public:
    moneyBag();
    moneyBag(LTexture*,float, float);
    moneyBag(const moneyBag&);
    void Render(SDL_Renderer*);         ///function to render the money bag on screen

    ///functions to access private attributes of the money bag
    int getWidth();
    int getHeight();
    Point getPosition();
};
