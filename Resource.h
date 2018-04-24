#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include"LTexture.h"
#include"Point.h"

class Resource
{
protected:
    int Cost;
    int HealthValue;
    Point position;
    int width;
    int height;
    enum ANIMATION_FRAMES{MOVING_FRAMES=9};                         ///depends on the sprite sheet being used
    SDL_Rect spriteClips[MOVING_FRAMES];
    LTexture* spriteSheetTexture;
public:
    Resource(LTexture*,float,float);
    virtual void Render(long int& , SDL_Renderer*, SDL_RendererFlip, double);   ///renders object to screen            ///Child-class implements
    SDL_Rect& GetCurrentObjectPosition();
    virtual ~Resource();
    int GetCost();
};



