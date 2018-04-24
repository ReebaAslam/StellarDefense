#include"pauseScreen.h"

pauseScreen::pauseScreen()
{
    width=height=0;
    ButtonCount=0;
    buttons=NULL;
}

pauseScreen::pauseScreen(LTexture* bgImage,LTexture* fontSprite,int screenWidth, int screenHeight)
{
    this->fontSprite=fontSprite;
    this->bgImage=bgImage;
    this->screenHeight=screenHeight;
    this->screenWidth=screenWidth;
    this->width=500;
    this->height=500;
    this->position.x=screenWidth/2-width/2;
    this->position.y=screenHeight/2-height/2;
    ButtonCount=3;
    buttons=new Button[3];
    std::string ButtonText[3]={" RESUME ","RESTART","  QUIT  "};        ///text on buttons
    int posX=screenWidth/2;
    int posY=(screenHeight/2)-100;
    for(int i=0; i<3; i++)
    {
        Button temp(fontSprite,ButtonText[i],posX, posY);
        buttons[i]=temp;
        posY+=100;
    }

}

void pauseScreen::Render(SDL_Renderer* gRenderer, int scrollingOffset, long int frame1)
{
    bgImage->RenderTexture( position.x, position.y,gRenderer,NULL );
    for(int i=0; i<ButtonCount; i++)
    {
        buttons[i].Render(gRenderer);
    }
}

pauseScreen::~pauseScreen()
{
    delete []buttons;
    std::cout<<"Pause Screen Destroyed"<<std::endl;
}
