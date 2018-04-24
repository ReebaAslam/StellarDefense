#include "Chemical.h"
#include "LTexture.h"


Chemical::Chemical(LTexture* image, float x, float y):Resource::Resource(image,x,y)
{

 spriteSheetTexture = image;

    int wid = 70;
    int heig = 75;

    //Frame 0
    spriteClips[0].x = 0;
    spriteClips[0].y = 0;
    spriteClips[0].w = wid;
    spriteClips[0].h = heig;

    //Frame 1
    spriteClips[1].x = 70;
    spriteClips[1].y = 0;
    spriteClips[1].w = wid;
    spriteClips[1].h = heig;

    //Frame 2
    spriteClips[2].x = 140;
    spriteClips[2].y = 0;
    spriteClips[2].w = wid;
    spriteClips[2].h = heig;

    //Frame 3
    spriteClips[3].x = 0;
    spriteClips[3].y = 75;
    spriteClips[3].w = wid;
    spriteClips[3].h = heig;

    //Frame 4
    spriteClips[4].x = 70;
    spriteClips[4].y = 75;
    spriteClips[4].w = wid;
    spriteClips[4].h = heig;

    //Frame 5
    spriteClips[5].x = 140;
    spriteClips[5].y = 75;
    spriteClips[5].w = wid;
    spriteClips[5].h = heig;

    //Frame 6
    spriteClips[6].x = 0;
    spriteClips[6].y = 150;
    spriteClips[6].w = wid;
    spriteClips[6].h = heig;

    //Frame 7
    spriteClips[7].x = 70;
    spriteClips[7].y = 150;
    spriteClips[7].w = wid;
    spriteClips[7].h = heig;

    //Frame 8
    spriteClips[8].x = 140;
    spriteClips[8].y = 150;
    spriteClips[8].w = wid;
    spriteClips[8].h = heig;

    position.x = x;
    position.y = y;

    this->width = wid;
    this->height = heig;
}


Chemical::~Chemical()
{

}


