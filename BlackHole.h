#pragma once
#include"LTexture.h"
#include"GameObject.hpp"
class BlackHole : public GameObject
{
private:
	//enum ANIMATION_FRAMES { MOVING_FRAMES = 7 };
	SDL_Rect spriteClips[1];// [MOVING_FRAMES];
public:
	BlackHole(LTexture*, float, float, int, int, int, int, float);
	virtual ~BlackHole();
	virtual void Render(long int&, SDL_Renderer*, SDL_RendererFlip,float);
};
