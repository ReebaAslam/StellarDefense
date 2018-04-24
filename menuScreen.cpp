#include "menuScreen.h"

menuScreen::menuScreen()
{
    width=height=0;
    ButtonCount=0;
    buttons=NULL;
}

menuScreen::menuScreen(LTexture* bgImage, LTexture* fontSprite, int width, int height)
{
    this->bgImage=bgImage;
    this->fontSprite=fontSprite;
    this->width=width;
    this->height=height;
    std::string ButtonText[3]={"CONTINUE", "NEW GAME","  EXIT  "};          ///Text on the buttons
    float posX=(float)width/2;
    float posY=((float)height/2);
    ButtonCount=3;
    buttons=new Button[3];
    for(int i=0; i<3; i++)
    {
        Button temp(fontSprite,ButtonText[i],posX, posY);
        buttons[i]=temp;
        posY+=70;
    }

}

void menuScreen::Render(SDL_Renderer* gRenderer, int scrollingOffset, long int frame1)
{
    bgImage->RenderTexture( 0, 0,gRenderer, NULL);
    for(int i=0; i<ButtonCount; i++)
    {
        buttons[i].Render(gRenderer);
    }
}

menuScreen::~menuScreen()
{
    delete[] buttons;
    std::cout<<"Menu Screen Destroyed"<<endl;
}
