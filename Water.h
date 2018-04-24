#pragma once
#include "Resource.h"
#include "LTexture.h"


class Water: public Resource
{
public:
    Water(LTexture*, float, float);
    ~Water();
};
