#include "gameScreen.h"

gameScreen::gameScreen()
{
    width=height=0;
    ButtonCount=0;
    buttons=NULL;
}

gameScreen::gameScreen(LTexture* bgImage,LTexture* fontSprite,LTexture* ResourceInfo,int width, int height)
{
    this->fontSprite=fontSprite;
    this->bgImage=bgImage;
    this->ResourceInfo=ResourceInfo;
    this->width=width;
    this->height=height;
    ButtonCount=2;
    buttons=new Button[2];
    std::string ButtonText[2]={"INVENTORY","PAUSE"};                ///text on Buttons
    Button Inventory(fontSprite,ButtonText[0],width-220, height-70);
    buttons[1]=Inventory;
    Button Pause(fontSprite,ButtonText[1],150,height-70);
    buttons[0]=Pause;
    moneyBag money(fontSprite,30,50);
    Bag=money;
}

void gameScreen::Render(SDL_Renderer* gRenderer, int scrollingOffset, long int frame1)
{
    bgImage->RenderTexture( scrollingOffset, 0,gRenderer,NULL );
    for(int i=0; i<ButtonCount; i++)
    {
        buttons[i].Render(gRenderer);
    }
    Bag.Render(gRenderer);
    float posX=buttons[0].getPosition().x+buttons[0].getWidth()-32;
    ResourceInfo->RenderTexture(posX,height-100,gRenderer,NULL);
}

gameScreen::~gameScreen()
{
    delete buttons;
    //delete[]buttons;
    std::cout<<"Game Screen Destroyed"<<std::endl;
}

