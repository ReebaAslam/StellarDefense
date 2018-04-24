#include"Star.h"

Star::Star(LTexture* gSpriteSheetTexture, float x, float y, int xSheet, int ySheet, int widthsheet, int heightsheet, float angle) : GameObject(gSpriteSheetTexture, x, y, xSheet, ySheet, widthsheet, heightsheet, angle)
{
	for (int i = 0; i<MOVING_FRAMES; i++)
	{
		spriteClips[i].x = xSheet + (widthsheet+120)*i;
		spriteClips[i].y = ySheet;
		spriteClips[i].w = widthsheet;
		spriteClips[i].h = heightsheet;
	}
	widthSheet = spriteClips[0].w/2;
	heightSheet = spriteClips[0].h/2;
	name = "star";
}
Star::~Star()
{
	spriteSheetTexture = NULL;
	printf("Star destroyed\n");
}
void Star::Render(long int& frame, SDL_Renderer* gRenderer, SDL_RendererFlip flip,float angle)
{
	spriteSheetTexture->RenderTexture(position.x - widthSheet, position.y - heightSheet, gRenderer, &spriteClips[frame % MOVING_FRAMES], flip, angle, NULL);
}
