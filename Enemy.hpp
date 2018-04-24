//
//  Enemy.hpp
//  OOP_Project
//
//  Created by Aiman Khan on 03/11/2017.
//  Copyright © 2017 Aiman Khan. All rights reserved.
//
#pragma once
#ifndef Enemy_hpp
#define Enemy_hpp

#include <stdio.h>

#endif /* Enemy_hpp */
#include "LTexture.h"
#include "GameObject.hpp"
#include <math.h>
#include "Bullet.hpp"
#include "Beam.hpp"
class Enemy : public GameObject
{
	SDL_Rect spriteClips[1];
public:
    Enemy(LTexture* image, float, float, int, int, int, int,float);
    virtual ~Enemy();
	void Move();
    void Render(long int& frame, SDL_Renderer* gRenderer,SDL_RendererFlip,float);
	virtual void SetAngle(int, int);
	virtual GameObject* Fire(LTexture*, std::string);
	virtual void Repel(GameObject*);
};
