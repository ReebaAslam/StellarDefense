#pragma once
#include "Resource.h"
#include "LTexture.h"


class Plant: public Resource
{
public:
    Plant(LTexture*, float, float);
    ~Plant();
    void Render(long int&, SDL_Renderer*, SDL_RendererFlip,double);
};
