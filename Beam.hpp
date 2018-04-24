#ifndef Beam_hpp
#define Beam_hpp
#include <stdio.h>
#endif /* Beam_hpp */
#pragma once
#include<math.h>
#include"LTexture.h"
//#include"GameObject.hpp"
#include  "Ammunition.hpp"
class Beam : public Ammunition
{
private:
	SDL_Rect spriteClips[1];
public:
	Beam(LTexture* image, float, float, int, int, int, int,float);
	virtual ~Beam();
	void Render(long int&, SDL_Renderer*, SDL_RendererFlip,float);
};
