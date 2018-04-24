#pragma once
#include "Resource.h"
#include "LTexture.h"


class Chemical: public Resource
{
public:
    Chemical(LTexture*, float, float);
    ~Chemical();
};
