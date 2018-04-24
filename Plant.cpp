#include "Plant.h"

Plant::Plant(LTexture* image, float x, float y):Resource::Resource(image,x,y)
{
    spriteSheetTexture = image;

    int wid = 140;
    int heig = 185;
/*
    //Frame 0
    spriteClips[0].x = 0;
    spriteClips[0].y = 60;
    spriteClips[0].w = wid;
    spriteClips[0].h = heig;

    //Frame 1
    spriteClips[1].x = 60;
    spriteClips[1].y = 60;
    spriteClips[1].w = wid;
    spriteClips[1].h = heig;

    //Frame 2
    spriteClips[2].x = 120;
    spriteClips[2].y = 60;
    spriteClips[2].w = wid+10;
    spriteClips[2].h = heig;

    //Frame 3
    spriteClips[3].x = 195;
    spriteClips[3].y = 60;
    spriteClips[3].w = wid+40;
    spriteClips[3].h = heig;

    //Frame 4
    spriteClips[4].x = 290;
    spriteClips[4].y = 60;
    spriteClips[4].w = wid+60;
    spriteClips[4].h = heig;
*/

    //Frame 0
    spriteClips[2].x = 10;
    spriteClips[2].y = 10;
    spriteClips[2].w = wid;
    spriteClips[2].h = heig;

    //Frame 1
    spriteClips[1].x = 178;
    spriteClips[1].y = 10;
    spriteClips[1].w = wid;
    spriteClips[1].h = heig;

    //Frame 2
    spriteClips[0].x = 346;
    spriteClips[0].y = 10;
    spriteClips[0].w = wid;
    spriteClips[0].h = heig;

    position.x = x;
    position.y = y;

    this->width = wid;
    this->height = heig;
}

Plant::~Plant()
{

}

void Plant::Render(long int& frame, SDL_Renderer* gRenderer, SDL_RendererFlip flip, double integer)
{
    spriteSheetTexture->RenderTexture( position.x - width/2, position.y - height/2, gRenderer, &spriteClips[frame%3] ,SDL_FLIP_NONE, 0.0 , NULL );
    SDL_RenderPresent(gRenderer);
}

