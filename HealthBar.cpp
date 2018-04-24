#include "HealthBar.hpp"

HealthBar::HealthBar()
{
	health = 198;
}

HealthBar::~HealthBar()
{
	printf("HealthBar destructed\n");
}

int HealthBar::getHealth()
{
	return health;
}
void HealthBar::setRect(SDL_Rect* rect)
{
	this->Rect = *rect;
}
SDL_Rect* HealthBar::getRect()
{
	return &Rect;
}
void HealthBar::setHealth(int x)
{
	if (!(x < 0))
		health = x;
}

void HealthBar::Render(std::string color,SDL_Renderer* gRenderer)
{
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, this->alpha);
	SDL_RenderDrawRect(gRenderer, &Rect);

	SDL_Rect fillRect = { Rect.x + 1,Rect.y + 1,health,Rect.h - 2 };
	if (color == "green")
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, this->alpha);
	else if (color == "red")
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, this->alpha);
	else if (color == "yellow")
		SDL_SetRenderDrawColor(gRenderer, 255, 242, 0x00, this->alpha);
	else if (color == "blue")
		SDL_SetRenderDrawColor(gRenderer, 40,219,219, this->alpha);
	SDL_RenderFillRect(gRenderer, &fillRect);
}
