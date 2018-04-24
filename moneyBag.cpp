#include "moneyBag.h"

moneyBag::moneyBag()
{
    width=height=0;
    image=NULL;
    position.x=0;
    position.y=0;
}

moneyBag::moneyBag(LTexture* image,float x, float y)
{
    this->image=image;
    spriteClip.x=150;
    spriteClip.y=326;
    spriteClip.w=50;
    spriteClip.h=60;
    width=spriteClip.w;
    height=spriteClip.h;
    position.x=x;
    position.y=y;
}

moneyBag::moneyBag(const moneyBag& cpy)
{
    image=cpy.image;
    spriteClip=cpy.spriteClip;
    width=cpy.width;
    height=cpy.height;
    position.x=cpy.position.x;
    position.y=cpy.position.y;
}

void moneyBag::Render(SDL_Renderer* gRenderer)
{
    image->RenderTexture(position.x-width/2,position.y-height/2,gRenderer,&spriteClip);
}

int moneyBag::getWidth()
{
    return width;
}

int moneyBag::getHeight()
{
    return height;
}

Point moneyBag::getPosition()
{
    return position;
}
