#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include "Resource.h"
#include "Plant.h"
#include "Chemical.h"
#include "Water.h"
#include"Screen.h"
#include "moneyBag.h"
#include "word.h"
#include <string>

class InventoryScreen:public Screen
{
private:
    moneyBag Bags[3];                       ///Money Bags icon for each price
    Word Price[3];                          ///Word showing Price of each resource
    string resourceName[3];                 ///array of strings consisting of Resource Names
    string prices[3];                       ///array of strings consisting of Prices of each resource
    Point position;
    int screenWidth,screenHeight;
    Resource* resources[3];                 ///array of pointers to resources
public:
    InventoryScreen(LTexture*, LTexture*, LTexture*, LTexture*,LTexture*,float,float);
    ~InventoryScreen();
    void Render(SDL_Renderer*,int scrollingoffset=0,long int frame1=0);
    string whichResource(int index);                        ///returns the name of Resource on the index
    string whatPrice(int index);                            ///returns the price of Resource on the index
};
