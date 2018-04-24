//
//  Bullet.cpp
//  OOP_Project
//
//  Created by Aiman Khan on 04/11/2017.
//  Copyright © 2017 Aiman Khan. All rights reserved.
//

#include "Bullet.hpp"

Bullet::Bullet(LTexture* image, float x, float y, int xsheet, int ysheet, int widthsheet, int heightsheet,float angle) : Ammunition(image, x, y, xsheet, ysheet, widthSheet, heightSheet,angle)
{
    spriteSheetTexture = image;

    spriteClips[0].x = xsheet;
	spriteClips[0].y = ysheet;
	spriteClips[0].w = widthsheet;
    spriteClips[0].h = heightsheet;
    name = "bullet";

    position.x = x;
    position.y = y;

    widthSheet = spriteClips[0].w/4;
    heightSheet = spriteClips[0].h/4;
	this->angle = angle;
	harmValue = 1;
	///Bullets.push_back(this);
}
Bullet::~Bullet()
{
	printf("Bullet Destructed\n");
    spriteSheetTexture = NULL;
}


void Bullet::Render(long int& frame, SDL_Renderer* gRenderer,SDL_RendererFlip flip,float angle)
{
    spriteSheetTexture->RenderTexture(position.x - 2*widthSheet , position.y - 2*heightSheet, gRenderer, &spriteClips[frame % FIRING_FRAMES], flip, this->angle, NULL);
}
