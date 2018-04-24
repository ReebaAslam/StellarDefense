//
//  Bullet.hpp
//  OOP_Project
//
//  Created by Aiman Khan on 04/11/2017.
//  Copyright © 2017 Aiman Khan. All rights reserved.
//
#ifndef Bullet_hpp
#define Bullet_hpp
#include <stdio.h>
#endif /* Bullet_hpp */
#pragma once
#include<math.h>
#include"LTexture.h"
//#include"GameObject.hpp"
#include  "Ammunition.hpp"

class Bullet : public Ammunition
{
private:
    enum ANIMATION_FRAMES { FIRING_FRAMES = 1 };
    SDL_Rect spriteClips[FIRING_FRAMES];
public:
    Bullet(LTexture* image, float, float, int, int, int, int,float);
    virtual ~Bullet();
    void Render(long int&, SDL_Renderer*, SDL_RendererFlip,float);
};


