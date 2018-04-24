//
//  GameObject.hpp
//  OOP_Project
//
//  Created by Aiman Khan on 03/11/2017.
//  Copyright © 2017 Aiman Khan. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>

#endif /* GameObject_hpp */

#pragma once
#include <stdio.h>
#include <iostream>
#include "LTexture.h"
#include "Point.h"
#include "GlobalFunctions.h"
#include <string>
#include "HealthBar.hpp"
#include <math.h>
#include <vector>

enum MOTION { RIGHT, LEFT, UP, DOWN };
class GameObject
{
protected:
    ///Current top-left position of GameObject
    Point position;
    ///Loaded image
    LTexture* spriteSheetTexture;
	HealthBar health;
	///Width and height of part of image to be loaded
    int widthSheet, heightSheet;
    bool alive;
    float speedx;
    float speedy;
    float friction; //gives a feel of gravity in case of blackholes. Otherwise implemented to control movement
    std::string name;
    SDL_Rect currentPostion;
	float angle;
public:
    GameObject(LTexture*, float, float,int,int,int,int,float);
	Point GetCenter();
    std::string GetName();
	void SetName(std::string);
    virtual ~GameObject();
    bool CheckAlive();
	void SetAlive(bool set) { alive = set; }
    bool CheckCollision(GameObject* gameObject);
    void Move(int);
	void Move(float,float);
	virtual void Move() {}
    virtual void Render(long int&, SDL_Renderer*, SDL_RendererFlip,float) = 0;
    SDL_Rect& GetCurrentObjectPosition();
	void SetSpeedxy(float, float);
	virtual GameObject* Fire(LTexture*,std::string) { return {}; }
	virtual void SetAngle(int,int);
	float GetAngle();
	virtual void Attacked(int);
	virtual void Repel(GameObject*) {} //correct this
	void setFriction(float);
	//virtual bool endAnimation() { return false; }
	virtual void BoundaryCollision() {}
	float GetSpeedx() { return speedx; }
	float GetSpeedy() { return speedy; }
	HealthBar GetHealthBar() { return health; }
	void setHealth(int x){health.setHealth(x);}
	virtual int getHarmValue() { return 0; }
	virtual int GetCash() {return 0;}
	virtual void SetCash(int) {}
	virtual void increaseResource(std::string){}
	virtual void decreaseResource(std::string){}
    virtual int chemCountf(){return 0;}
	virtual int plantCountf(){return 0;}
	virtual int waterCountf(){return 0;}
    virtual void setchem(int x) {}
	virtual void setplant(int x) {}
	virtual void setwater(int x) {}
	virtual void setPosition(float x, float y){}
};

