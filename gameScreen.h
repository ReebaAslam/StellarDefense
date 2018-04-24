#pragma once
#include "Screen.h"
#include "moneyBag.h"

class gameScreen:public Screen
{
private:
    moneyBag Bag;                               ///money bag to be rendered
    LTexture* ResourceInfo;                     ///image of the Resources info icons to be rendered at the bottom
public:
    gameScreen();
    gameScreen(LTexture*,LTexture*,LTexture*,int, int);
    void Render(SDL_Renderer*,int scrollingOffset=0,long int frame1=0);
    ~gameScreen();
};
