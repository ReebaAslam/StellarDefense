#include"Resource.h"
#include<iostream>

/*Character::Character()
{
    width = 44;
    height = 48;
    character_value = 0;
}
*/

Resource::Resource(LTexture* image, float x, float y)
{

}

Resource::~Resource()
{

}


void Resource::Render(long int& frame, SDL_Renderer* gRenderer, SDL_RendererFlip flip, double integer)
{
    spriteSheetTexture->RenderTexture( position.x - width/2, position.y - height/2, gRenderer, &spriteClips[frame%9] ,SDL_FLIP_NONE, 0.0 , NULL );
    SDL_RenderPresent(gRenderer);
}
