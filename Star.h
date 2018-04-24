#pragma once
#include"LTexture.h"
#include"GameObject.hpp"
class Star : public GameObject
{
private:
	enum ANIMATION_FRAMES { MOVING_FRAMES = 1 };                     ///depends on the sprite sheet being used
	SDL_Rect spriteClips[MOVING_FRAMES];
public:
	Star(LTexture*, float, float, int, int, int, int, float);         ///initializes values
	virtual ~Star();                                                          ///destroys asteroid
	virtual void Render(long int&, SDL_Renderer*, SDL_RendererFlip,float);
};

