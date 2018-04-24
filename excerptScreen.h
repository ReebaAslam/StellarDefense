#pragma once

#include "Screen.h"

class excerptScreen:public Screen
{
public:
    excerptScreen();
    excerptScreen(LTexture*, int, int);
    void Render(SDL_Renderer*,int scrollingOffset=0,long int frame1=0);
    ~excerptScreen();
};
