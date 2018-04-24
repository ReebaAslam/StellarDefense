//
//  Beam.cpp
//  OOP_Project
//
//  Created by Aiman Khan on 04/11/2017.
//  Copyright © 2017 Aiman Khan. All rights reserved.
//

#include "Beam.hpp"
Beam::Beam(LTexture* image, float x, float y, int xsheet, int ysheet, int widthsheet, int heightsheet,float angle) : Ammunition(image, x, y, xsheet, ysheet, widthSheet, heightSheet,angle)
{
	spriteSheetTexture = image;
	spriteClips[0].x = xsheet;
	spriteClips[0].y = ysheet;
	spriteClips[0].w = widthsheet;
	spriteClips[0].h = heightsheet;
	name = "beam";

	position.x = x;
	position.y = y;

	widthSheet = spriteClips[0].w; // widthSheet+8
	heightSheet = spriteClips[0].h;
	this->angle = angle;
	harmValue = 39;
}
Beam::~Beam()
{
	printf("Beam Destructed\n");
	spriteSheetTexture = NULL;
}
void Beam::Render(long int& frame, SDL_Renderer* gRenderer, SDL_RendererFlip flip, float angle)
{
	spriteSheetTexture->RenderTexture(position.x - widthSheet/2, position.y - heightSheet/2, gRenderer,&spriteClips[frame % 1], flip,this->angle, NULL);
}
