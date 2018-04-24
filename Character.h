#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include"LTexture.h"
#include"Point.h"

class Character
{
private:
    Point position;                          ///Position of the Character
    int character_value;                    ///ascii value of the Character
    int width;                              ///width of character
    int height;                             ///height of character
    SDL_Rect spriteClips;                  ///clip specific to the Character
    LTexture* spriteSheetTexture;
public:
    Character();
    Character(LTexture* image, float x, float y, int ascii);
    Character(const Character&);
    ~Character();
    void Render(SDL_Renderer* gRenderer, bool debug);
    void SetPosition(Point&);
    void SetPosition(float,float);              ///sets position of the Character
    int GetFrameWidth();
    int GetFrameHeight();
    void GetPosition();
};

