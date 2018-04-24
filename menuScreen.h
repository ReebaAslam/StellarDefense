#pragma once
#include "Screen.h"

class menuScreen:public Screen
{
public:
    menuScreen();
    menuScreen(LTexture*,LTexture*, int, int);
    void Render(SDL_Renderer*,int scrollingOffset=0,long int frame1=0);
    ~menuScreen();
};
