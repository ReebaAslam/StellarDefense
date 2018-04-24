#include "excerptScreen.h"

excerptScreen::excerptScreen()
{
    width=height=0;
    ButtonCount=0;
    buttons=NULL;
}

excerptScreen::excerptScreen(LTexture* bgImage, int width, int height)
{
    ButtonCount=0;
    buttons=NULL;
    this->bgImage=bgImage;
    this->fontSprite=NULL;
    this->width=width;
    this->height=height;
}

void excerptScreen::Render(SDL_Renderer* gRenderer,int scrollingOffset,long int frame1)
{
     bgImage->RenderTexture( 0, 0,gRenderer,NULL );
}

excerptScreen::~excerptScreen()
{
    std::cout<<"Splash Screen Destroyed"<<std::endl;
}

