#include"Asteroid.h"
Asteroid::Asteroid(LTexture* gSpriteSheetTexture, float x, float y, int xSheet, int ySheet, int widthsheet, int heightsheet, float angle) : GameObject(gSpriteSheetTexture, x, y, xSheet, ySheet, widthsheet, heightsheet, angle)
{
	//for (int i = 0; i<MOVING_FRAMES; i++)
	//{
		spriteClips[0].x = xSheet;// +((i + 1)*widthsheet);
		spriteClips[0].y = ySheet;
		spriteClips[0].w = widthsheet;
		spriteClips[0].h = heightsheet;
	//}
	friction = 1.0f;
	widthSheet = spriteClips[0].w;
	heightSheet = spriteClips[0].h;
	name = "asteroid";
}
Asteroid::~Asteroid()
{
	spriteSheetTexture = NULL;
	printf("Asteroid destroyed\n");
}
void Asteroid::Render(long int& frame, SDL_Renderer* gRenderer, SDL_RendererFlip flip,float angle)
{
	spriteSheetTexture->RenderTexture(position.x - widthSheet / 2, position.y - heightSheet / 2, gRenderer, &spriteClips[frame %1], flip,angle, NULL);
}
void Asteroid::Move()
{
	position.x = position.x + speedx;
	position.y = position.y + speedy;
}
void Asteroid::BoundaryCollision()
{
	if (position.x < 0 || position.y < 0)
	{
		this->SetAlive(false);
	}
}
