#pragma once
#include "Screen.h"

class pauseScreen:public Screen
{
    Point position;                 ///position of the Pause Screen on the whole screen
    int screenWidth,screenHeight;   ///actual width and height of the WHOLE screen
public:
    pauseScreen();
    pauseScreen(LTexture*,LTexture*,int,int);
    void Render(SDL_Renderer*,int scrollingOffset=0,long int frame1=0);
    ~pauseScreen();
};
