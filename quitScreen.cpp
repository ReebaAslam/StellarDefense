#include "quitScreen.h"

quitScreen::quitScreen()
{
    width=height=0;
    ButtonCount=0;
    buttons=NULL;
}

quitScreen::quitScreen(LTexture* bgImage,LTexture* fontSprite,int screenWidth, int screenHeight)
{
    this->fontSprite=fontSprite;
    this->bgImage=bgImage;
    this->screenHeight=screenHeight;
    this->screenWidth=screenWidth;
    this->width=800;
    this->height=300;
    this->position.x=screenWidth/2-width/2;
    this->position.y=screenHeight/2-height/2;
    ButtonCount=3;
    buttons=new Button[3];
    std::string ButtonText[3]={" YES ","  NO  ","CANCEL"};      ///text on buttons
    int posX=screenWidth/2-240;
    int posY=position.y+200;
    for(int i=0; i<3; i++)
    {
        Button temp(fontSprite,ButtonText[i],posX, posY);
        buttons[i]=temp;
        posX+=240;
    }

}

void quitScreen::Render(SDL_Renderer* gRenderer, int scrollingOffset, long int frame1)
{
    bgImage->RenderTexture( position.x, position.y,gRenderer,NULL );
    for(int i=0; i<ButtonCount; i++)
    {
        buttons[i].Render(gRenderer);
    }
}

quitScreen::~quitScreen()
{
    delete []buttons;
    std::cout<<"Pause Screen Destroyed"<<std::endl;
}

