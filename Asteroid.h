#pragma once
#include"LTexture.h"
#include"GameObject.hpp"
class Asteroid : public GameObject
{
private:
	SDL_Rect spriteClips[1];
public:
	Asteroid(LTexture*, float, float, int, int, int, int, float);
	virtual ~Asteroid();
	virtual void Render(long int&, SDL_Renderer*, SDL_RendererFlip,float);
	virtual void Move();
	void BoundaryCollision();
};
