//
//  SpaceShip.cpp
//  OOP_Project
//
//  Created by Aiman Khan on 03/11/2017.
//  Copyright © 2017 Aiman Khan. All rights reserved.
//

#include "SpaceShip.hpp"
//SpaceShip* SpaceShip::getInstance(LTexture* image, float x, float y, int xsheet, int ysheet, int widthsheet, int heightsheet, float angle)
//{
//	if (!instanceFlag)
//	{
//		spaceship = new SpaceShip(image, x, y, xsheet, ysheet, widthSheet, heightSheet, angle);
//		instanceFlag = true;
//		return spaceship;
//	}
//	else
//	{
//		return spaceship;
//	}
//}
SpaceShip::SpaceShip(LTexture* image,float x,float y, int xsheet, int ysheet, int widthsheet, int heightsheet,float angle) : GameObject(image,x,y,xsheet,ysheet,widthSheet,heightSheet,angle)
{
    spriteSheetTexture = image;

    //Frame 0
    spriteClips[ 0 ].x =   xsheet;
    spriteClips[ 0 ].y =   ysheet;
    spriteClips[ 0 ].w = widthsheet;
    spriteClips[ 0 ].h = heightsheet;

    position.x = x; //uses point attribute of the gameobject
    position.y = y;

    widthSheet = spriteClips[0].w;
    heightSheet = spriteClips[0].h;

    name = "spaceship";
    speedx = 0;
    speedy = 0;
    alive = true;
	friction = 0.97f;
    bulletCount = 100;
	this->angle = angle;
	SDL_Rect rect = { 1050,10,200,20 };
	health.setRect(&rect);
}
SpaceShip::~SpaceShip()
{
	printf("SpaceShip destructed\n");
    spriteSheetTexture = NULL;
}
void SpaceShip::Move()
{
	if (position.x >= GlobalFunctions::GetSCREEN_WIDTH())
		position.x = GlobalFunctions::GetSCREEN_WIDTH();
	else if (position.y >= GlobalFunctions::GetSCREEN_HEIGHT())
		position.y = GlobalFunctions::GetSCREEN_HEIGHT();
	else if (position.x <= 0)
		position.x = 0;
	else if (position.y <= 0)
		position.y = 0;
	else
	{
		speedx = speedx * friction;
		speedy = speedy * friction;
		position.x = position.x + speedx;
		position.y = position.y + speedy;
	}
}
void SpaceShip::Render(long int& frame, SDL_Renderer* gRenderer,SDL_RendererFlip flip,float angle )
{
	health.Render("green",gRenderer);
    spriteSheetTexture->RenderTexture(position.x - widthSheet / 2, position.y - heightSheet / 2, gRenderer,&spriteClips[frame % 1], flip,angle, NULL);
}
GameObject* SpaceShip::Fire(LTexture* image,std::string weapon_name)
{
	GameObject* ammunition = NULL;
	if (weapon_name == "bullet")
	{
		ammunition = new Bullet(image, GetCenter().x,GetCenter().y, 30, 0, 30, 63,GetAngle());
	}
	else if (weapon_name == "beam")
	{
		ammunition = new Beam(image, GetCenter().x, GetCenter().y, 20,180,35,55, GetAngle());
	}
	return ammunition;
}
void SpaceShip::SetAngle(int point_x, int point_y)
{
	angle = static_cast<float>(90- (atan2((-(point_y - GetCenter().y)), (point_x - GetCenter().x)) * 180 / M_PI));
}
int SpaceShip::GetCash()
{
    return cash;
}
void SpaceShip::SetCash(int x)
{
    cash= x;
}

void SpaceShip::increaseResource(std::string resourceName)
{
    if(resourceName=="Chemical")
        chemCount++;
    else if(resourceName=="Water")
        waterCount++;
    else if(resourceName=="Plant")
        plantCount++;
}

void SpaceShip::decreaseResource(std::string resourceName)
{
    if(resourceName=="Chemical")
        chemCount--;
    else if(resourceName=="Water")
        waterCount--;
    else if(resourceName=="Plant")
        plantCount--;
}
