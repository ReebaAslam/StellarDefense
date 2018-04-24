#pragma once
#include"LTexture.h"
#include"GameObject.hpp"
class Planet : public GameObject
{
private:
	//enum ANIMATION_FRAMES { MOVING_FRAMES = 12 };
	SDL_Rect spriteClips[1];
public:
	Planet(LTexture*, float, float, int, int, int, int, float);
	virtual ~Planet();
	virtual void Render(long int&, SDL_Renderer*, SDL_RendererFlip,float);
};
