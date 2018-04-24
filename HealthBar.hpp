#ifndef HealthBar_hpp
#define HealthBar_hpp

#include <stdio.h>

#endif /* HealthBar_hpp */
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
class HealthBar
{
private:
	int health;
	SDL_Rect Rect;
	int alpha = 255;
public:
	HealthBar();
	~HealthBar();
	int getHealth();
	void setRect(SDL_Rect*);
	SDL_Rect* getRect();
	void setHealth(int);
	void SetAlpha(int alpha) {this->alpha = alpha;}
	void Render(std::string,SDL_Renderer*);
};
