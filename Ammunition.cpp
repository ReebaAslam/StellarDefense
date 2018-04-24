#include "Ammunition.hpp"

Ammunition::Ammunition(LTexture* image, float x, float y, int xsheet, int ysheet, int widthsheet, int heightsheet, float angle) : GameObject(image, x, y, xsheet, ysheet, widthSheet, heightSheet, angle)
{

}
Ammunition::~Ammunition()
{
	printf("Ammunition destructed\n");
	spriteSheetTexture = NULL;
}
void Ammunition::Move()
{
	position.x += static_cast<float>(cos(angle*M_PI / 180 - (M_PI / 2))) * speedx;
	position.y += static_cast<float>(-sin(angle*M_PI / 180 - (M_PI / 2))) * speedy;
}
void Ammunition::BoundaryCollision()
{
	if (position.x > GlobalFunctions::GetSCREEN_WIDTH() || position.y > GlobalFunctions::GetSCREEN_HEIGHT() || position.x < 0 || position.y < 0)
	{
		this->SetAlive(false);
	}
}
