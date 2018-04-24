#ifndef Explosion_hpp
#define Explosion_hpp
#include <stdio.h>
#endif /* Explosion_hpp */
#include "Point.h"
#include "SDL.h"
#include "LTexture.h"
#pragma once
class Explosion
{
private:
	int explosion_frames;
	int frame;
	Point position;
	SDL_Rect* EX_spriteClips;
	LTexture* spriteSheetTexture;
	int widthSheet, heightSheet;
public:
	Explosion(LTexture*, float, float,int);
	~Explosion();
	bool EndExplosion();
	void Render(long int& frame, SDL_Renderer* gRenderer, SDL_RendererFlip flip);
};
