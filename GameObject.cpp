//
//  GameObject.cpp
//  OOP_Project
//
//  Created by Aiman Khan on 03/11/2017.
//  Copyright © 2017 Aiman Khan. All rights reserved.
//

#include "GameObject.hpp"
GameObject::~GameObject()
{
    spriteSheetTexture = NULL;
    printf("GameObject Destroyed\n");
}
GameObject::GameObject(LTexture* image, float x, float y,int xsheet, int ysheet,int widthsheet,int heightsheet,float angle)
{
    spriteSheetTexture = image;
    position.x = x;
    position.y = y;
    friction = 0.0f;
    speedx = 0;
    speedy = 0;
    name = "gameobject";
    alive  = true;
	this->angle = angle;
}
void GameObject::Move(float plane_x, float plane_y)
{
	Point direction;
	direction.x = plane_x - GetCenter().x;
	direction.y = plane_y - GetCenter().y;
	float hyp = sqrt(direction.x*direction.x + direction.y*direction.y);
	direction.x /= hyp;
	direction.y /= hyp;
	if (hyp > 150.0)
	{
		position.x += direction.x * speedx;
		position.y += direction.y * speedy;
	}
}
void GameObject::Move(int direction)
{
	if (direction == LEFT)
	{
		speedx = -5;
		position.x += speedx;
	}
	if (direction == RIGHT)
	{
		speedx = 5;
		position.x += speedx;
	}
	if (direction == UP)
	{
		speedy = -5;
		position.y += speedy;
	}
	if (direction == DOWN)
	{
		speedy = 5;
		position.y += speedy;
	}
}
Point GameObject::GetCenter()
{
	Point p;
	p.x = static_cast<float>(GetCurrentObjectPosition().x + GetCurrentObjectPosition().w / 2);
	p.y = static_cast<float>(GetCurrentObjectPosition().y + GetCurrentObjectPosition().h / 2);
	return p;
}
std::string GameObject::GetName()
{
    return name;
}

void GameObject::SetName(std::string string)
{
	name = string;
}
bool GameObject::CheckCollision(GameObject* gameObject)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = this->GetCurrentObjectPosition().x;
    rightA = this->GetCurrentObjectPosition().x + this->GetCurrentObjectPosition().w;
    topA = this->GetCurrentObjectPosition().y;
    bottomA = this->GetCurrentObjectPosition().y + this->GetCurrentObjectPosition().h;

    //Calculate the sides of rect B
    leftB = gameObject->GetCurrentObjectPosition().x;
    rightB = gameObject->GetCurrentObjectPosition().x + gameObject->GetCurrentObjectPosition().w;
    topB = gameObject->GetCurrentObjectPosition().y;
    bottomB = gameObject->GetCurrentObjectPosition().y + gameObject->GetCurrentObjectPosition().h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
        return false;
    if( topA >= bottomB )
        return false;
    if( rightA <= leftB )
        return false;
    if( leftA >= rightB )
        return false;
    return true;
}

bool GameObject::CheckAlive()
{
    return this->alive;
}

void GameObject::SetAngle(int x, int y) {}
float GameObject::GetAngle() { return angle; }
SDL_Rect& GameObject::GetCurrentObjectPosition()
{
	currentPostion = { static_cast<int>(position.x) - widthSheet / 2, static_cast<int>(position.y) - heightSheet / 2, widthSheet, heightSheet };
	return currentPostion;
}
void GameObject::setFriction(float friction)
{
	this->friction = friction;
}
void GameObject::SetSpeedxy(float speedx, float speedy)
{
	this->speedx = speedx;
	this->speedy = speedy;
}
void GameObject::Attacked(int harmValue)
{
	int Health = health.getHealth();
	for (int i = 0 ; i <harmValue; i++)
		health.setHealth(--Health);
	if (health.getHealth() <= 0)
		alive = false;
}
