#pragma once
#include "Screen.h"

class splashScreen:public Screen
{
public:
    splashScreen();
    splashScreen(LTexture*, int, int);
    void Render(SDL_Renderer*,int scrollingOffset=0,long int frame1=0);
    ~splashScreen();
};
