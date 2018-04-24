//
//  Enemy.cpp
//  OOP_Project
//
//  Created by Aiman Khan on 03/11/2017.
//  Copyright © 2017 Aiman Khan. All rights reserved.
//

#include "Enemy.hpp"
using namespace std;
Enemy::~Enemy()
{
	cout << "Enemy Deallocated" << endl;
	spriteSheetTexture = NULL;
}

Enemy::Enemy(LTexture* image, float x, float y,int xsheet, int ysheet, int widthsheet, int heightsheet,float angle) : GameObject(image, x, y, xsheet, ysheet, widthSheet, heightSheet,angle)
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

    name = "enemy";
    friction = 1.0f;
    speedx = 0;
    speedy = 0;
    alive = true;
	this->angle = angle;
	health.setHealth(78);
}
void Enemy::Render(long int& frame, SDL_Renderer* gRenderer,SDL_RendererFlip flip,float angle)
{
	SDL_Rect rect = { GetCurrentObjectPosition().x,GetCurrentObjectPosition().y,80,8 };
	health.setRect(&rect);
	health.Render("red",gRenderer);
    spriteSheetTexture->RenderTexture(position.x - widthSheet / 2, position.y - heightSheet / 2, gRenderer, &spriteClips[frame % 1], flip,angle, NULL);
}
void Enemy::SetAngle(int plane_x, int plane_y)
{
	angle = static_cast<float>(90 - (atan2((-GetCenter().y + plane_y), (GetCenter().x - plane_x)) * 180 / M_PI));
}
GameObject* Enemy::Fire(LTexture* image, std::string weapon_name)
{
	GameObject* ammunition = NULL;
	if (weapon_name == "bullet")
	{
		ammunition = new Bullet(image, GetCenter().x, GetCenter().y, 0, 0, 32, 64, GetAngle());
		ammunition->SetName("enemy bullet");
	}
	else if (weapon_name == "beam")
	{
		ammunition = new Beam(image, GetCenter().x, GetCenter().y, 130, 0, 51, 187, GetAngle());
		ammunition->SetName("enemy bullet");
	}
	return ammunition;
}
void Enemy::Repel(GameObject* object)
{
	object->SetSpeedxy(-1, -1);
	object->Move();
}
void Enemy::Move()
{
	position.x = position.x + speedx;
	position.y = position.y + speedy;
}

