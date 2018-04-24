#include"BlackHole.h"
BlackHole::BlackHole(LTexture* gSpriteSheetTexture, float x, float y, int xSheet, int ySheet, int widthsheet, int heightsheet, float angle) : GameObject(gSpriteSheetTexture, x, y, xSheet, ySheet, widthsheet, heightsheet, angle)
{
	//for (int i = 0; i<MOVING_FRAMES; i++)
	{
		spriteClips[0].x = xSheet;//widthsheet*i;//xSheet + ((i + 1)*widthsheet);
		spriteClips[0].y = ySheet;
		spriteClips[0].w = widthsheet;
		spriteClips[0].h = heightsheet;
	}
	widthSheet = spriteClips[0].w;
	heightSheet = spriteClips[0].h;
	name = "blackhole";
}
BlackHole::~BlackHole()
{
	spriteSheetTexture = NULL;
	printf("Black hole destructed\n");
}
void BlackHole::Render(long int& frame, SDL_Renderer* gRenderer, SDL_RendererFlip flip,float angle)
{
	spriteSheetTexture->RenderTexture(position.x - widthSheet / 2, position.y - heightSheet / 2, gRenderer, &spriteClips[frame %1], flip, angle, NULL);
}
