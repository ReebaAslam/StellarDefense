#pragma once
#include "LTexture.h"
#include "Button.h"

class Screen
{
protected:
    int width;                      ///width of the screen
    int height;                     ///height of the screen
    LTexture* bgImage;              ///background image of the screen
    LTexture* fontSprite;           ///image consisting of fonts, buttons and money bag
    int ButtonCount;                ///no. of Buttons to be rendered
    Button* buttons;                ///pointer of Button class(either kept null or used to create dynamic array of buttons)
public:
    virtual void Render(SDL_Renderer*,int scrollingOffset=0,long int frame1=0)=0;       ///Render the Screen
    Button* getButtons()            ///returns array of buttons
    {
        return buttons;
    }
    int getButtonCount()           ///return the no. of buttons rendered
    {
        return ButtonCount;
    }
    void ChangeButtonState(State val, int ind)      ///changes the state of Button on the index
    {
        buttons[ind].changeState(val);
    }

};

