#pragma once
#include "Screen.h"

class quitScreen:public Screen
{
private:
    Point position;                     ///position of Quit Screen on the whole screen
    int screenWidth,screenHeight;       ///width and height of the WHOLE screen
public:
    quitScreen();
    quitScreen(LTexture*,LTexture*,int,int);
    void Render(SDL_Renderer*,int scrollingOffset=0,long int frame1=0);
    ~quitScreen();
};
