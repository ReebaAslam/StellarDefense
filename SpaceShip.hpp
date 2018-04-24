//
//  SpaceShip.hpp
//  OOP_Project
//
//  Created by Aiman Khan on 03/11/2017.
//  Copyright © 2017 Aiman Khan. All rights reserved.
//

#ifndef SpaceShip_hpp
#define SpaceShip_hpp

#include <stdio.h>

#endif /* SpaceShip_hpp */
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "LTexture.h"
#include "GameObject.hpp"
#include "Beam.hpp"
#include "Bullet.hpp"
class SpaceShip : public GameObject
{
private:
	//static bool instanceFlag;
	//static SpaceShip* spaceship;
	//SpaceShip(LTexture* image, float, float, int, int, int, int, float);
private:
    SDL_Rect spriteClips[1];
    int bulletCount = 0;
    int cash = 0;
    int chemCount=0;
    int plantCount=0;
    int waterCount=0;
public:
	SpaceShip(LTexture* image, float, float, int, int, int, int, float);
	//static SpaceShip* getInstance(LTexture* image, float x, float y, int xsheet, int ysheet, int widthsheet, int heightsheet, float angle);
    virtual ~SpaceShip();
    void Move();
    void Render(long int& frame, SDL_Renderer* gRenderer,SDL_RendererFlip,float);
	virtual GameObject* Fire(LTexture*,std::string);
	virtual void SetAngle(int,int);
	int GetCash();
	void SetCash(int);
    void increaseResource(std::string);
	void decreaseResource(std::string);
	int chemCountf(){return chemCount;}
	int plantCountf(){return plantCount;}
	int waterCountf(){return waterCount;}
	void setchem(int x) {chemCount = x;}
	void setplant(int x) {plantCount = x;}
	void setwater(int x) {waterCount = x;}
	void setPosition(float x, float y){position.x=x;position.y=y;}
};
