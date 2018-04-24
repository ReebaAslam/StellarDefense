#include "splashScreen.h"

splashScreen::splashScreen()
{
    width=height=0;
    ButtonCount=0;
    buttons=NULL;
}

splashScreen::splashScreen(LTexture* bgImage, int width, int height)
{
    ButtonCount=0;
    buttons=NULL;
    this->bgImage=bgImage;
    this->fontSprite=NULL;
    this->width=width;
    this->height=height;
}

void splashScreen::Render(SDL_Renderer* gRenderer,int scrollingOffset,long int frame1)
{
     bgImage->RenderTexture( 0, 0,gRenderer,NULL );
    /* float logoWidth=logoSprite.w;
     float logoHeight=logoSprite.h;
     Logo->RenderTexture((float)width/2-logoWidth/2, (float)height/2-logoHeight/2,gRenderer,NULL);*/
}

splashScreen::~splashScreen()
{
    std::cout<<"Splash Screen Destroyed"<<std::endl;
}
