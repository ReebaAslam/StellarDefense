#include"Planet.h"
Planet::Planet(LTexture* gSpriteSheetTexture, float x, float y, int xSheet, int ySheet, int widthsheet, int heightsheet, float angle) : GameObject(gSpriteSheetTexture, x, y, xSheet, ySheet, widthsheet, heightsheet, angle)
{
	spriteClips[0].x = xSheet;
    spriteClips[0].y = ySheet;
    spriteClips[0].w = widthsheet;
    spriteClips[0].h = heightsheet;
	widthSheet = spriteClips[0].w;
	heightSheet = spriteClips[0].h;
	name = "planet";
	SDL_Rect rect = { 1050,60,200,20 };
	health.setRect(&rect);
}
Planet::~Planet()
{
	spriteSheetTexture = NULL;
	printf("Planet destructed\n");
}
void Planet::Render(long int& frame, SDL_Renderer* gRenderer, SDL_RendererFlip flip,float angle)
{
	health.Render("yellow", gRenderer);
	spriteSheetTexture->RenderTexture(position.x - widthSheet / 2, position.y - heightSheet / 2, gRenderer, &spriteClips[frame %1], flip, angle, NULL);
}
